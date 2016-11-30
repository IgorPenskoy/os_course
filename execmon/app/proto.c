#include <string.h>
#include "../shared/proto.h"

int PROTO_is_valid_msg(proto_msg_t * msg) {
	if (NULL == msg) {
		return 0;
	}

	/* Validate message */
	if (0 == memcmp(msg->proto_prefix, PROTO_PREFIX, PROTO_PREFIX_SIZE)) {
		return 1;
	}

	return 0;
}

void PROTO_assign_msg(proto_msg_t * msg, enum ACTION action) {
	if (NULL == msg) {
		return;
	}

	memcpy(msg->proto_prefix, PROTO_PREFIX, PROTO_PREFIX_SIZE); 
	msg->action = action;
	msg->msg_size = 0;
}

