#ifndef __SYSCALLS_H__
#define __SYSCALLS_H__

#define SYM_SYS_CALL_TABLE ("sys_call_table")

#define MAX_RELATIVE_CALL_OFFSET (150)
 
int SYSCALLS_set_hooks(void);
int SYSCALLS_remove_hooks(void);

#endif /* __SYSCALLS_H__ */



