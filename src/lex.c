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
static int next_symbol = true;

int lex_tokenize(char *buffer, long long int buff_size, char **tokens, int *err_line) {
	int curr_state = 0, accepted, line = 1;
	char sym[2] = {0};
	bool (*f)(char *) = NULL;
	
	*err_line = 0;
	for(int i = 0; i < buff_size;) {
		if(buffer[i] == '\n') {
			line++;
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
			*err_line = line;
			return 1;
		}
		if(next_symbol) {
			i++;
		}
	}
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
	for(int i = 0; i < 14; i++) {
        if(!strcmp(sym, __symbol__[i])) {
            return true;
        }
    }
	return false;
}

bool _0_0(char *sym) {
	next_symbol = true;
	if(!strcmp(sym, COMMA)) { printf("0->0 %s %d COMMA\n", sym, 1); return true; }
	else if(!strcmp(sym, PCOMMA)) { printf("0->0 %s %d PCOMMA\n", sym, 1); return true; }
	else if(!strcmp(sym, LBRACE)) { printf("0->0 %s %d LBRACE\n", sym, 1); return true; }
	else if(!strcmp(sym, RBRACE)) { printf("0->0 %s %d RBRACE\n", sym, 1); return true; }
	else if(!strcmp(sym, LBRACKET)) { printf("0->0 %s %d LBRACKET\n", sym, 1); return true; }
	else if(!strcmp(sym, RBRACKET)) { printf("0->0 %s %d RBRACKET\n", sym, 1); return true; }
	else if(!strcmp(sym, LCOL)) { printf("0->0 %s %d LCOL\n", sym, 1); return true; }
	else if(!strcmp(sym, RCOL)) { printf("0->0 %s %d RCOL\n", sym, 1); return true; }
	else if(!strcmp(sym, PLUS)) { printf("0->0 %s %d PLUS\n", sym, 1); return true; }
	else if(!strcmp(sym, MINUS)) { printf("0->0 %s %d MINUS\n", sym, 1); return true; }
	else if(!strcmp(sym, MULT)) { printf("0->0 %s %d MULT\n", sym, 1); return true; }
	else if(!strcmp(sym, DIV)) { printf("0->0 %s %d DIV\n", sym, 1); return true; }
	else if(!strcmp(sym, "\n") || !strcmp(sym, " ") || !strcmp(sym, "\t")) { printf("0->0 %s %d\n", sym, !strcmp(sym, "\n") || !strcmp(sym, " ") || !strcmp(sym, "\t")); return true; }
    return false;
}

bool _0_1(char *sym) {
	next_symbol = true;
	printf("0->1 %s %d\n", sym, lex_is_letter(sym));
	return lex_is_letter(sym);
}

bool _0_2(char *sym) {
	next_symbol = true;
	printf("0->2 %s %d\n", sym, lex_is_number(sym));
	return lex_is_number(sym);
}

bool _0_5(char *sym) {
	next_symbol = true;
	printf("0->5 %s %d\n", sym, !strcmp(sym, LT));
	if(!strcmp(sym, LT)) {
		return true;
	}
	return false;
}

bool _0_6(char *sym) {
	next_symbol = true;
	printf("0->6 %s %d\n", sym, !strcmp(sym, GT));
	if(!strcmp(sym, GT)) {
		return true;
	}
	return false;
}

bool _0_7(char *sym) {
	next_symbol = true;
	printf("0->7 %s %d\n", sym, !strcmp(sym, ATTR));
	if(!strcmp(sym, ATTR)) {
		return true;
	}
	return false;
}

bool _0_8(char *sym) {
	next_symbol = true;
	if(!strcmp(sym, "!")) {
		printf("0->8 %s %d\n", sym, 1);
		return true;
	}
	return false;
}

bool _0_9(char *sym) {
	next_symbol = true;
	if(!strcmp(sym, "&")) {
		printf("0->9 %s %d\n", sym, 1);
		return true;
	}
	return false;
}

bool _0_10(char *sym) {
	next_symbol = true;
	if(!strcmp(sym, "|")) {
		printf("0->10 %s %d\n", sym, 1);
		return true;
	}
	return false;
}

bool _1_0(char *sym) {
	next_symbol = false;
	printf("1->0 %s %d id ou palavra reservada\n", sym, !lex_is_letter(sym) && !lex_is_number(sym));
	if(!lex_is_letter(sym) && !lex_is_number(sym)) {
		//token ID ou palavra reservada
		return true;
	}
	return false;
}

bool _1_1(char *sym) {
	next_symbol = true;
	printf("1->1 %s %d\n", sym, lex_is_letter(sym) || lex_is_number(sym));
	bool accepted = lex_is_letter(sym) ? true : lex_is_number(sym);
	if(accepted) {
		__lexem__.buffer[__lexem__.n++] = sym[0];
	}
	return accepted;
}

bool _2_0(char *sym) {
	next_symbol = false;
	printf("2->0 %s %d INT_CONST\n", sym, !lex_is_number(sym) && strcmp(sym, "."));
	if(!lex_is_number(sym) && strcmp(sym, ".")) {
		//token INTEGER_CONST
		return true;
	}
	return false;
}

bool _2_2(char *sym) {
	next_symbol = true;
	printf("2->2 %s %d\n", sym, lex_is_number(sym));
	return lex_is_number(sym);
}

bool _2_3(char *sym) {
	next_symbol = true;
	printf("2->3 %s %d\n", sym, !strcmp(sym, "."));
	if(!strcmp(sym, ".")) {
		return true;
	}
	return false;
}

bool _3_4(char *sym) {
	next_symbol = true;
	printf("3->4 %s %d\n", sym, lex_is_number(sym));
	return lex_is_number(sym);
}

bool _4_4(char *sym) {
	next_symbol = true;
	printf("4->4 %s %d\n", sym, lex_is_number(sym));
	return lex_is_number(sym);
}

bool _4_0(char *sym) {
	next_symbol = false;
	printf("4->0 %s %d FLOAT_CONST\n", sym, !lex_is_number(sym));
	if(!lex_is_number(sym)) {
		//token FLOAT_CONST
		return true;
	}
	return false;
}

bool _5_0(char *sym) {
	if(!strcmp(sym, ATTR)) {
		printf("5->0 %s %d LE\n", sym, 1);
		//token LE
	} else {
		printf("5->0 %s %d LT\n", sym, 1);
		//token LT
	}
	return true;
}

bool _6_0(char *sym) {
	if(!strcmp(sym, ATTR)) {
		printf("6->0 %s %d GE\n", sym, 1);
		//token GE
	} else {
		printf("6->0 %s %d GT\n", sym, 1);
		//token GT
	}
	return true;
}

bool _7_0(char *sym) {
	if(!strcmp(sym, ATTR)) {
		next_symbol = true;
		printf("7->0 %s %d EQ\n", sym, 1);
		//token EQ
	} else {
		next_symbol = false;
		printf("7->0 %s %d ATTR\n", sym, 1);
		//token ATTR
	}
	return true;
}

bool _8_0(char *sym) {
	next_symbol = true;
	if(!strcmp(sym, ATTR)) {
		printf("8->0 %s %d NE\n", sym, 1);
		//token NE
		return true;
	}
	return false;
}

bool _9_0(char *sym) {
	next_symbol = true;
	if(!strcmp(sym, "&")) {
		printf("9->0 %s %d AND\n", sym, 1);
		//token AND
		return true;
	}
	return false;
}

bool _10_0(char *sym) {
	next_symbol = true;
	if(!strcmp(sym, "|")) {
		printf("10->0 %s %d OR\n", sym, 1);
		//token OR
		return true;
	}
	return false;
}
