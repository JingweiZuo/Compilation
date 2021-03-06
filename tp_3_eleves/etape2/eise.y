%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "ast.h"

int yylex(void);
void yyerror(char *s);
nodeType *programRoot;

%}


%union {
	float f;
	char *s;
	nodeType *np;
};
%left '+' '-'
%left '*' '/'

%token T_BEGIN T_END
%token T_NUMERIC T_PROGRAM
%token T_SKIP T_VARIABLE T_WRITE

%type <f> T_NUMERIC
%type <s> T_VARIABLE 
%type <np> program_eise
%type <np> skip_instruction 
%type <np> instruction_composee 
%type <np> liste_instructions 
%type <np> instruction
%type <np> instruction1 
%type <np> bloc_principal
%type <np> expr


%%

program_eise: T_PROGRAM T_VARIABLE ';' bloc_principal '.' { programRoot = $4; printf("root=%p\n",programRoot) ; }
	; 

bloc_principal : instruction_composee	
	;

instruction_composee : T_BEGIN liste_instructions T_END { printf("instru\n");$$ = $2 ; }
	;

liste_instructions : liste_instructions instruction ';' { $$ = createOperatorNode(OPER_SEQUENCE,2,$1,$2); }
	| instruction ';'
	;

instruction : instruction_composee 
	| skip_instruction
	| instruction1
	;

instruction1: T_WRITE expr ';' { printf("write\n");$$ = createOperatorNode(OPER_WRITE,1,$2); };

skip_instruction : T_SKIP { $$ = createOperatorNode(OPER_SKIP,0); }
	;

expr: T_NUMERIC { $$ = createNumericNode($1); }
| expr'+'expr { $$ = createOperatorNode(OPER_ADD,2,$1,$3); }
| expr'-'expr { $$ = createOperatorNode(OPER_SUB,2,$1,$3); }
| expr'*'expr { $$ = createOperatorNode(OPER_MULT,2,$1,$3); }
| expr'/' expr { $$ = createOperatorNode(OPER_DIV,2,$1,$3); }
| '('expr ')'{ $$ = $2; }
;

%%

void yyerror(char *s) {
    fprintf(stdout, "%s\n", s);
}

int main(void) {
    	yyparse();
		generateDigraph(programRoot);
		generateAsm(programRoot,"res.asm");
    	return 0;
}
