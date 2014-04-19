#ifndef _DEBUG_H 
#define _DEBUG_H

// Handy macros to quickly test expressions

#define co(x)    fprintf(stderr, #x ": <%d>\n", (x))
#define coc(x)   fprintf(stderr, #x ": <%c>\n", (x))
#define cop(x)   fprintf(stderr, #x ": <%p>\n", (x))
#define costr(x) fprintf(stderr, #x ": <%s>\n", (x))
//#define cob(x)    fprintf(stderr, #x ": <%b>\n", (x))
 
 
#endif
