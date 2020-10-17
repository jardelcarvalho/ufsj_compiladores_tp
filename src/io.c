#include "io.h"

int	io_read(char *file_name, char **buffer, long long int *buff_size) {
	FILE *f = fopen(file_name, "r");
	if(!f) {
		return 1;
	}

	fseek(f, 0, SEEK_END);
	*buff_size = ftell(f);
	rewind(f);	
	
	char *b = malloc(*buff_size + 1);
	fread(b, 1, *buff_size, f);
	b[*buff_size] = 0;
	*buffer = b;
	
	fclose(f);
	return 0;
}

int io_write() {
	return 0;
}
