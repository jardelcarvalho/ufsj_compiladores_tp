#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include <stdlib.h>

int io_read(char *file_name, char **buffer, long long int *buff_size);
int io_write();

#endif
