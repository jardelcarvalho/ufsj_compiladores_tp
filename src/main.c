#include "io.h"
#include "lex.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	char *buffer, **tokens, *err_expr;
	int err, n, err_line;
	long long int buff_size;
	
	printf("#iniciado\n");
	err = io_read(argv[1], &buffer, &buff_size);
	if(err) {
		printf("Erro: Arquivo ''   %s   '' não encontrado", argv[1]);
		return 0;
	} else {
		printf("Ok: Leitura concluída\n");
	}

	// for(int i = 0; i < buff_size; i++) {
	// 	printf("%c", buffer[i]);
	// }

	//err_expr é um pedaço da string que ocorreu o erro com um \0 no final
	err = lex_tokenize(buffer, buff_size, tokens, &err_line);
	if(err) {
		printf("Erro: Expressão inapropriada na linha %d\n", err_line);
	} else {
		printf("Ok: Análise léxica concluída\n");
	}
	
	/*
	err = synt_analyze(tokens, err_sym, &line);
	if(err) {
		printf("ERRO: Operação mal formada ''   %s   '' linha %d", err_sym, line);
	} else {
		printf("Ok: Análise sintática concluída\n");
	}
	*/
	printf("#terminado\n");

	return 0;
}
