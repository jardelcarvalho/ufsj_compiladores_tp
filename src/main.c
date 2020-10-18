#include "io.h"
#include "lex.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	char *buffer;
	int err, err_line;
	long long int buff_size;
	struct lex_tokens *tokens_list;
	
	err = io_read(argv[1], &buffer, &buff_size);
	if(err) {
		printf("Erro: Arquivo ''   %s   '' não encontrado", argv[1]);
		return 0;
	} else {
		printf("Ok: Leitura concluída\n");
	}

	err = lex_tokenize(buffer, buff_size, &tokens_list, &err_line);
	if(err) {
		printf("Erro: Expressão inapropriada na linha %d\n", err_line);
	} else {

		printf("Ok: Análise léxica concluída\n\n");
		for(int i = 0; i < tokens_list->n; i++) {
			printf("%s %s %d\n", tokens_list->tokens[i].buffer, tokens_list->lexems[i].buffer, tokens_list->lines[i]);
		}
	}
	return 0;
}
