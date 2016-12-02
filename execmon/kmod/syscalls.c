#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/delay.h>
#include <linux/kallsyms.h>
#include <asm/unistd.h>
#include <linux/vmalloc.h>
#include <linux/timex.h>
#include <linux/time.h>
#include "includes/general.h"
#include "includes/mem.h"
#include "includes/syscalls.h"
#include "includes/comm.h"
#include "udis86.h"

asmlinkage long (*orig_sys_execve_fn)(const char __user * filename,
				const char __user * const __user * argv,
				const char __user * const __user * envp);

static int obtain_sys_call_table_addr(unsigned long * sys_call_table_addr) {
	int ret = SUCCESS;
	unsigned long temp_sys_call_table_addr;

	temp_sys_call_table_addr = kallsyms_lookup_name(SYM_SYS_CALL_TABLE);
	
	/* Return error if the symbol doesn't exist */
	if (0 == sys_call_table_addr) {
		ret = ERROR;
		goto cleanup;
	}
	
	DBG_PRINT("Found sys_call_table: %p", (void *) temp_sys_call_table_addr);
	*sys_call_table_addr = temp_sys_call_table_addr;
		
cleanup:
	return ret;
}

char *get_timestamp(void) {
	struct timeval now;
	struct tm format_time;
	char *time_string = vmalloc(9);
	do_gettimeofday(&now);
	time_to_tm(now.tv_sec, 0, &format_time);
	snprintf(time_string, 9, "%d:%d.%d", (format_time.tm_hour + 3) % 24, 
			format_time.tm_min, format_time.tm_sec);
	return time_string;
}

static asmlinkage long new_sys_execve(const char __user * filename,
				const char __user * const __user * argv,
				const char __user * const __user * envp) {
	size_t exec_line_size = 512;
	char * exec_str = NULL;
	char ** p_argv = (char **) argv;
	char *time_string = NULL;
	int my_uid = (int)current->cred->uid.val;
	int my_pid = (int)current->pid;
	char *time_flag = "ВРЕМЯ:";
	char *uid_flag = "UID:";
	char *pid_flag = "PID:";
	char *file_path_flag = "ФАЙЛ:";
	char *arguments_flag = "АРГУМЕНТЫ:";
	char *uid_str = vmalloc(10);
	char *pid_str = vmalloc(10);
	snprintf(uid_str, 10, "%d", my_uid);
	snprintf(pid_str, 10, "%d", my_pid);

	/* Allocate enough memory for the execution string */
	time_string = get_timestamp();
	exec_str = vmalloc(exec_line_size);
	if (NULL != exec_str) {
		snprintf(exec_str, exec_line_size, "%s %s", time_flag, time_string);
		snprintf(exec_str, exec_line_size, "%s %s %s", exec_str, uid_flag, uid_str);
		snprintf(exec_str, exec_line_size, "%s %s %s", exec_str, pid_flag, pid_str);
		snprintf(exec_str, exec_line_size, "%s %s %s", exec_str, file_path_flag, filename);
		vfree(time_string);
		vfree(uid_str);
		vfree(pid_str);
		/* Iterate through the execution arguments */
		snprintf(exec_str, exec_line_size, "%s %s", exec_str, arguments_flag);
		p_argv = (char **) argv;
		while (NULL != *p_argv) {
			/* Concatenate each argument with our execution line */
			snprintf(exec_str, exec_line_size,
					"%s %s", exec_str, *p_argv);
			(char **) p_argv++;	
		}

		/* Send execution line to the user app */
		COMM_nl_send_exec_msg(exec_str);
	}


	/* Finally, call the original sys_execve */
	return orig_sys_execve_fn(filename, argv, envp);

}

static int hook_sys_execve(unsigned long sys_call_table_addr) {
	int ret = SUCCESS;
	unsigned long orig_stub_execve_addr;
	unsigned long orig_call_addr;

	/* Get stub_execve address */
	orig_stub_execve_addr = ((unsigned long * ) (sys_call_table_addr))[__NR_execve];

	/* Patch the relative call instruction.
	 * Replace sys_execve with new_sys_execve */
	ret = MEM_patch_relative_call(orig_stub_execve_addr,
					MAX_RELATIVE_CALL_OFFSET,
					(unsigned long) new_sys_execve, &orig_call_addr);
	if (SUCCESS != ret) {
		goto cleanup;
	}

	/* Backup the original sys_execve address */
	orig_sys_execve_fn = (void * ) orig_call_addr;

cleanup:
	return ret;
}

static void remove_hook_sys_execve(unsigned long sys_call_table_addr) {
	unsigned long orig_stub_execve_addr;

	/* Get stub_execve address */
	orig_stub_execve_addr = ((unsigned long * ) (sys_call_table_addr))[__NR_execve];

	/* Patch the relative call instruction.
	 * Replace new_sys_execve with the original sys_execve */
	MEM_patch_relative_call(orig_stub_execve_addr,
					MAX_RELATIVE_CALL_OFFSET,
					(unsigned long) orig_sys_execve_fn, NULL);
}

int SYSCALLS_set_hooks(void)
{
	int ret = SUCCESS;
	int call_rv;
	unsigned long sys_call_table_addr;

	DBG_PRINT("Setting syscalls hooks");
	
	/* Obtain syscall table address */
	call_rv = obtain_sys_call_table_addr(&sys_call_table_addr);
	if (SUCCESS != call_rv) {
		ret = call_rv;
		goto cleanup;
	}

	/* Fix stub_execve to call our new execve function */
	hook_sys_execve(sys_call_table_addr);

cleanup:
	return ret;
}

int SYSCALLS_remove_hooks(void)
{
	int ret = SUCCESS;
	int call_rv;
	unsigned long sys_call_table_addr;

	DBG_PRINT("Removing syscalls hooks");
	
	/* Obtain syscall table address */
	call_rv = obtain_sys_call_table_addr(&sys_call_table_addr);
	if (SUCCESS != call_rv) {
		ret = call_rv;
		goto cleanup;
	}

	/* Fix stub_execve to call the original execve function */
	remove_hook_sys_execve(sys_call_table_addr);

cleanup:
	return ret;


}

