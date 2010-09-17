#ifndef         _CONST_H
#define         _CONST_H



#define         BMP_HEADER_SIZE         sizeof (BMP_HEADER)
#define         G_LEVEL                 256

#define         UP                      50
#define         LEFT                    50
#define         SPOT                    0

#define         PI                      3.1415926


#define         RADIAN(angle)           ((angle) * PI / 180.0)

#define         MAX(a, b)               (a) > (b) ? (a) : (b)

/* #define		DBG */
#ifdef		DBG
#define		DBGMSG(...) \
		do { \
			printf(__VA_ARGS__); \
			fflush(stdout); \
		} while (0)
#else
#define 	DBGMSG			/* nop */
#endif

#endif
