#include "lex.h"

static const char *__letter__[52] = {
	"a", "b", "c", "d", "e", "f", 
	"g", "h", "i", "j", "k", "l", 
	"m", "n", "o", "p", "q", "r", 
	"s", "t", "u", "v", "w", "x", 
	"y", "z", "A", "B", "C", "D", 
	"E", "F", "G", "H", "I", "J", 
	"K", "L", "M", "N", "O", "P", 
	"Q", "R", "S", "T", "U", "V", 
	"W", "X", "Y", "Z"
};

static const char *__number__[10] = {
	"0", "1", "2", "3", "4", 
	"5", "6", "7", "8", "9"
};

static const char *__symbol__[16] = {
	"(", ")", "{", "}", ",", ";",
	"+", "-", "*", "/", "=", "|", 
	"&", "!", "[", "]"
};

static const bool (*__lex_trans_funct__[11][11])(char *) = {
	{_0_0, _0_1, _0_2, NULL, NULL, _0_5, _0_6, _0_7, _0_8, _0_9, _0_10},
	{_1_0, _1_1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{_2_0, NULL, _2_2, _2_3, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{NULL, NULL, NULL, NULL, _3_4, NULL, NULL, NULL, NULL, NULL, NULL},
	{_4_0, NULL, NULL, NULL, _4_4, NULL, NULL, NULL, NULL, NULL, NULL},
	{_5_0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{_6_0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{_7_0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{_8_0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{_9_0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
	{_10_0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}
};

static struct lex_buffer __lexem__ = {0};
static struct lex_buffer __token__ = {0};
static struct lex_tokens __tokens_list__ = {0};
static int __next_symbol__ = true;
static int __line__ = 1;

int lex_tokenize(char *buffer, long long int buff_size, struct lex_tokens **tokens, int *err_line) {
	int curr_state = 0, accepted;
	char sym[2] = {0};
	bool (*f)(char *) = NULL;
	
	*err_line = 0;
	for(int i = 0; i < buff_size;) {
		if(buffer[i] == '\n') {
			__line__++;
		}
		sym[0] = buffer[i];
		accepted = false;
		for(int t = 0; t < 11; t++) {
			f = __lex_trans_funct__[curr_state][t];
			if(f) {
				accepted = (*f)(sym);
				if(accepted) {
					curr_state = t;
					break;
				}
			}
		}
		if(!accepted) {
			*err_line = __line__;
			*tokens = NULL;
			return 1;
		}
		if(__next_symbol__) {
			i++;
		}
	}
	*err_line = -1;
	*tokens = &__tokens_list__;
	return 0;
}

bool lex_is_letter(char *sym) {
	for(int i = 0; i < 52; i++) {
        if(!strcmp(sym, __letter__[i])) {
            return true;
        }
    }
    return false;
}

bool lex_is_number(char *sym) {
	for(int i = 0; i < 10; i++) {
        if(!strcmp(sym, __number__[i])) {
            return true;
        }
    }
    return false;
}

bool lex_is_symbol(char *sym) {
	for(int i = 0; i < 16; i++) {
        if(!strcmp(sym, __symbol__[i])) {
            return true;
        }
    }
	return false;
}

void lex_add_to_lexem(char *sym) {
	if(__lexem__.n != LEXEM_MAX_SIZE - 1) {
		__lexem__.buffer[__lexem__.n++] = sym[0];
	}
}

void lex_flush_to_list() {
	__tokens_list__.lexems[__tokens_list__.n] = __lexem__;
	__tokens_list__.tokens[__tokens_list__.n] = __token__;
	__tokens_list__.lines[__tokens_list__.n] = __line__;
	__tokens_list__.n++;

	struct lex_buffer empty = {0};
	__lexem__ = empty;
	__token__ = empty;
}

void lex_id_or_keyword_set_token() {
	__token__.n = __lexem__.n;
	if(!strcmp(__lexem__.buffer, MAIN)) { memcpy(__token__.buffer, ToKEN(MAIN), __token__.n); return; }
	else if(!strcmp(__lexem__.buffer, INT)) { memcpy(__token__.buffer, ToKEN(INT), __token__.n); return; }
	else if(!strcmp(__lexem__.buffer, FLOAT)) { memcpy(__token__.buffer, ToKEN(FLOAT), __token__.n); return; }
	else if(!strcmp(__lexem__.buffer, IF)) { memcpy(__token__.buffer, ToKEN(IF), __token__.n); return; }
	else if(!strcmp(__lexem__.buffer, ELSE)) { memcpy(__token__.buffer, ToKEN(ELSE), __token__.n); return; }
	else if(!strcmp(__lexem__.buffer, WHILE)) { memcpy(__token__.buffer, ToKEN(WHILE), __token__.n); return; }
	else if(!strcmp(__lexem__.buffer, FOR)) { memcpy(__token__.buffer, ToKEN(FOR), __token__.n); return; }
	else if(!strcmp(__lexem__.buffer, READ)) { memcpy(__token__.buffer, ToKEN(READ), __token__.n); return; }
	else if(!strcmp(__lexem__.buffer, PRINT)) { memcpy(__token__.buffer, ToKEN(PRINT), __token__.n); return; }
	__token__.n = 2;
	memcpy(__token__.buffer, "ID", __token__.n);
}

void lex_set_token(char *token) {
	__token__.n = strlen(token);
	memcpy(__token__.buffer, token, __token__.n);
}


bool _0_0(char *sym) {
	__next_symbol__ = true;
	bool accepted = true;
	bool flush = true;
	if(!strcmp(sym, COMMA)) lex_set_token(ToKEN(COMMA));
	else if(!strcmp(sym, PCOMMA)) lex_set_token(ToKEN(PCOMMA));
	else if(!strcmp(sym, LBRACE)) lex_set_token(ToKEN(LBRACE));
	else if(!strcmp(sym, RBRACE)) lex_set_token(ToKEN(RBRACE));
	else if(!strcmp(sym, LBRACKET)) lex_set_token(ToKEN(LBRACKET));
	else if(!strcmp(sym, RBRACKET)) lex_set_token(ToKEN(RBRACKET));
	else if(!strcmp(sym, LCOL)) lex_set_token(ToKEN(LCOL));
	else if(!strcmp(sym, RCOL)) lex_set_token(ToKEN(RCOL));
	else if(!strcmp(sym, PLUS)) lex_set_token(ToKEN(PLUS));
	else if(!strcmp(sym, MINUS)) lex_set_token(ToKEN(MINUS));
	else if(!strcmp(sym, MULT)) lex_set_token(ToKEN(MULT));
	else if(!strcmp(sym, DIV)) lex_set_token(ToKEN(DIV));
	else if(!strcmp(sym, "\n") || !strcmp(sym, " ") || !strcmp(sym, "\t")) flush = false;
	else accepted = false;

	if(flush && accepted) {
		lex_add_to_lexem(sym);
		lex_flush_to_list();
	}
    return accepted;
}

bool _0_1(char *sym) {
	__next_symbol__ = true;
	if(lex_is_letter(sym)) { 
		lex_add_to_lexem(sym); 
		return true; 
	}
	return false;
}

bool _0_2(char *sym) {
	__next_symbol__ = true;
	if(lex_is_number(sym)) { 
		lex_add_to_lexem(sym); 
		return true; 
	}
	return false;
}

bool _0_5(char *sym) {
	__next_symbol__ = true;
	if(!strcmp(sym, LT)) {
		lex_add_to_lexem(sym);
		return true;
	}
	return false;
}

bool _0_6(char *sym) {
	__next_symbol__ = true;
	if(!strcmp(sym, GT)) {
		lex_add_to_lexem(sym);
		return true;
	}
	return false;
}

bool _0_7(char *sym) {
	__next_symbol__ = true;
	if(!strcmp(sym, ATTR)) {
		lex_add_to_lexem(sym);
		return true;
	}
	return false;
}

bool _0_8(char *sym) {
	__next_symbol__ = true;
	if(!strcmp(sym, "!")) {
		lex_add_to_lexem(sym);
		return true;
	}
	return false;
}

bool _0_9(char *sym) {
	__next_symbol__ = true;
	if(!strcmp(sym, "&")) {
		lex_add_to_lexem(sym);
		return true;
	}
	return false;
}

bool _0_10(char *sym) {
	__next_symbol__ = true;
	if(!strcmp(sym, "|")) {
		lex_add_to_lexem(sym);
		return true;
	}
	return false;
}

bool _1_0(char *sym) {
	__next_symbol__ = false;
	if(!lex_is_letter(sym) && !lex_is_number(sym)) {
		//token ID ou palavra reservada
		lex_id_or_keyword_set_token();
		lex_flush_to_list();
		return true;
	}
	return false;
}

bool _1_1(char *sym) {
	__next_symbol__ = true;
	if(lex_is_letter(sym) || lex_is_number(sym)) {
		lex_add_to_lexem(sym);
		return true;
	}
	return false;
}

bool _2_0(char *sym) {
	__next_symbol__ = false;
	if(!lex_is_number(sym) && strcmp(sym, ".")) {
		//token INTEGER_CONST
		lex_set_token("INTEGER_CONST");
		lex_flush_to_list();
		return true;
	}
	return false;
}

bool _2_2(char *sym) {
	__next_symbol__ = true;
	if(lex_is_number(sym)) {
		lex_add_to_lexem(sym);
		return true;
	}
	return false;
}

bool _2_3(char *sym) {
	__next_symbol__ = true;
	if(!strcmp(sym, ".")) {
		lex_add_to_lexem(sym);
		return true;
	}
	return false;
}

bool _3_4(char *sym) {
	__next_symbol__ = true;
	if(lex_is_number(sym)) {
		lex_add_to_lexem(sym);
		return true;
	}
	return false;
}

bool _4_4(char *sym) {
	__next_symbol__ = true;
	if(lex_is_number(sym)) {
		lex_add_to_lexem(sym);
		return true;
	}
	return false; 
}

bool _4_0(char *sym) {
	__next_symbol__ = false;
	if(!lex_is_number(sym)) {
		//token FLOAT_CONST
		lex_set_token("FLOAT_CONST");
		lex_flush_to_list();
		return true;
	}
	return false;
}

bool _5_0(char *sym) {
	if(!strcmp(sym, ATTR)) {
		//token LE
		__next_symbol__ = true;
		lex_add_to_lexem(sym);
		lex_set_token(ToKEN(LE));
	} else {
		//token LT
		__next_symbol__ = false;
		lex_set_token(ToKEN(LT));
	}
	lex_flush_to_list();
	return true;
}

bool _6_0(char *sym) {
	if(!strcmp(sym, ATTR)) {
		//token GE
		__next_symbol__ = true;
		lex_add_to_lexem(sym);
		lex_set_token(ToKEN(GE));
	} else {
		//token GT
		__next_symbol__ = false;
		lex_set_token(ToKEN(GT));
	}
	lex_flush_to_list();
	return true;
}

bool _7_0(char *sym) {
	if(!strcmp(sym, ATTR)) {
		//token EQ
		__next_symbol__ = true;
		lex_add_to_lexem(sym);
		lex_set_token(ToKEN(EQ));
	} else {
		//token ATTR
		__next_symbol__ = false;
		lex_set_token(ToKEN(ATTR));
	}
	lex_flush_to_list();
	return true;
}

bool _8_0(char *sym) {
	__next_symbol__ = true;
	if(!strcmp(sym, ATTR)) {
		//token NE
		lex_add_to_lexem(sym);
		lex_set_token(ToKEN(NE));
		lex_flush_to_list();
		return true;
	}
	return false;
}

bool _9_0(char *sym) {
	__next_symbol__ = true;
	if(!strcmp(sym, "&")) {
		//token AND
		lex_add_to_lexem(sym);
		lex_set_token(ToKEN(AND));
		lex_flush_to_list();
		return true;
	}
	return false;
}

bool _10_0(char *sym) {
	__next_symbol__ = true;
	if(!strcmp(sym, "|")) {
		//token OR
		lex_add_to_lexem(sym);
		lex_set_token(ToKEN(OR));
		lex_flush_to_list();
		return true;
	}
	return false;
}
