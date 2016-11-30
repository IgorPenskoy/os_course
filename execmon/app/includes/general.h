#ifndef __GENERAL_H__
#define __GENERAL_H__

/* Application parameters */
#define DEBUG (0)

#define SUCCESS (0)
#define ERROR (-1)

/* Bool typedef */
typedef enum {
	false = 0,
	true
} bool;


#if DEBUG
	#define DBG_PRINT(fmt, args...) do { fprintf(stderr, "[*] DEBUG: " fmt "\n" \
						, ##args); } while (false)
#else
	#define DBG_PRINT(...) do {} while (false)
#endif

#define UNUSED(expr) do { (void)(expr); } while (false)

#endif /* __GENERAL_H__ */



