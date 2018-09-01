#ifndef __MYUART_H
#define __MYUART_H

#include <stdio.h>

// Specify that a new putchar function will be used instead of the one from stdio.h
#define _ALTERNATE_PUTCHAR_

void uartInit(unsigned char line);

#endif
