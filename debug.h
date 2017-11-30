#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
# include <stdio.h>
# define debug(x) printf x; printf("\n")
#else
# define debug(x) do {} while (0)
#endif

#endif // DEBUG_H
