#ifndef __COMM_H__
#define __COMM_H__

#include <sys/socket.h>
#include <linux/netlink.h>

struct comm_nl {
	struct sockaddr_nl src_addr;
	struct sockaddr_nl dst_addr;
	int nl_sock;
};

#define NETLINK_EXECMON (31) /* Last possible netlink */

int COMM_nl_request_conn(void);
int COMM_nl_send(void * send_msg, size_t len);
int COMM_nl_recv(void * recv_buff, size_t len);
int COMM_nl_init();
int COMM_nl_destruct();

#endif /* __COMM_H__ */



