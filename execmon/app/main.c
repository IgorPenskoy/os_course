#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include "includes/general.h"
#include "includes/comm.h"
#include "../shared/proto.h"

static void handle_exec_event(proto_msg_t * msg) {
	int call_rv;
	char * exec_line;
	if (NULL == msg) {
		return;
	}
	
	/* Allocate memory for the message data */
	exec_line = malloc(msg->msg_size);	
	if (NULL == exec_line) {
		return;
	}

	call_rv = COMM_nl_recv(exec_line, msg->msg_size);
	if (0 >= call_rv) {
		free(exec_line);
		return;

	}
	FILE *f = fopen("exec_log.txt", "a");
	fprintf(f, "ЗАПУСК -- %s\n\n", exec_line);
	fclose(f);
	free(exec_line);
}

static void monitor_execs() {
	int call_rv;
	proto_msg_t msg;

	/* Endlessly receive information about executions */
	while(true) {
		memset(&msg, 0, sizeof(proto_msg_t));	
		call_rv = COMM_nl_recv(&msg, sizeof(proto_msg_t));
		if (0 >= call_rv) {
			continue;
		}

		/* Validate received message */	
		if (false == PROTO_is_valid_msg(&msg)) {
			continue;
		}
		
		/* Determine message type and act accordingly */
		switch(msg.action) {
			case KEEP_ALIVE:
				/* Alive */
				continue;

			case EXEC_EVENT:
				/* New program execution */
				handle_exec_event(&msg);

			default:
				/* Unknown packet */
				continue;
		}
	}
}

int main(int argc, char * argv[])
{
	int ret = SUCCESS;
	int call_rv;

	/* Eliminate unused warnings */
	UNUSED(argc);
	UNUSED(argv);
	FILE *f = fopen("exec_log.txt", "w");
	fprintf(f, "Запуск мониторинга программ ...\n");
	fclose(f);
	/* Init communication struct */
	call_rv = COMM_nl_init();
	if (SUCCESS != call_rv) {
		ret = ERROR;
		goto cleanup;
	}

	/* Connect to the kernel module */	
	call_rv = COMM_nl_request_conn();
	if (ERROR == call_rv) {
		f = fopen("exec_log.txt", "a");
		fprintf(f, "Ошибка во время установления соединения с модулем ядра.\n");
		fclose(f);
		ret = call_rv;
		goto cleanup;
	}
	f = fopen("exec_log.txt", "a");
	fprintf(f, "Журнал мониторинга программ запущен.\n\n");
	fclose(f);
	monitor_execs();

cleanup:
	COMM_nl_destruct();
	return ret;

}

