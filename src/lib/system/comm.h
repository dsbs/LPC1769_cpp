#ifndef _COMMFUNC
#define _COMMFUNC

#ifdef __cplusplus
 extern "C" {
#endif

void comm_init (void);
int  comm_test (void);
void comm_put (unsigned char);
unsigned char comm_get (void);

#ifdef __cplusplus
 }
#endif

#endif

