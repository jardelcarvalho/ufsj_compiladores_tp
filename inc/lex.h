#ifndef __LEX_H__
#define __LEX_H__

#include "tokens.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

typedef int bool;

#define LEXEM_MAX_SIZE 1024
#define NUM_MAX_TOKENS 4096

struct lex_buffer {
    char buffer[LEXEM_MAX_SIZE];
    int n;
};

struct lex_tokens {
    struct lex_buffer tokens[NUM_MAX_TOKENS];
    struct lex_buffer lexems[NUM_MAX_TOKENS];
    int lines[NUM_MAX_TOKENS];
    int n;
};

int lex_tokenize(char *buffer, long long int buff_size, struct lex_tokens **tokens, int *err_line);

bool lex_is_letter(char *sym);
bool lex_is_number(char *sym);
bool lex_is_symbol(char *sym);

void lex_add_to_lexem(char *sym);
void lex_flush_to_list();
void lex_id_or_keyword_set_token();
void lex_set_token(char *token);

bool _0_0(char *sym);
bool _0_1(char *sym);
bool _0_2(char *sym);
bool _0_5(char *sym);
bool _0_6(char *sym);
bool _0_7(char *sym);
bool _0_8(char *sym);
bool _0_9(char *sym);
bool _0_10(char *sym);
bool _1_0(char *sym);
bool _1_1(char *sym);
bool _2_0(char *sym);
bool _2_2(char *sym);
bool _2_3(char *sym);
bool _3_4(char *sym);
bool _4_4(char *sym);
bool _4_0(char *sym);
bool _5_0(char *sym);
bool _6_0(char *sym);
bool _7_0(char *sym);
bool _8_0(char *sym);
bool _9_0(char *sym);
bool _10_0(char *sym);

#endif
