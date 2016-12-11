#include <asm/unistd.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/delay.h>
#include <linux/kallsyms.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>
#include <net/sock.h>

#include "includes/general.h"
#include "includes/syscalls.h"
#include "includes/comm.h"
#include "udis86.h"

MODULE_LICENSE("GPL");

static int mod_main(void)
{
	int ret = SUCCESS;
	int call_rv;


	/* Setup netlink kernel<->user communication */
	call_rv = COMM_nl_init();
	if (SUCCESS != call_rv) {
		KLOG_PRINT("Cannot set netlink socket, exiting...");
		ret = call_rv;
		return ret;		
	}

	/* Set needed hooks */	
	call_rv = SYSCALLS_set_hooks();
	if (SUCCESS != call_rv) {
		KLOG_PRINT("Cannot set hooks, exiting...");
		ret = call_rv;
		return ret;
	}

	KLOG_PRINT("kmod started successfully");

	return ret;
}

static void mod_exit(void)
{
	KLOG_PRINT("Exiting");
	
	/* Restore original syscalls */
	SYSCALLS_remove_hooks();

	/* Close netlink socket */
	COMM_nl_destruct();

	return;	
}

/* Init main entrypoints of the kernel module */
module_init(mod_main);
module_exit(mod_exit);
