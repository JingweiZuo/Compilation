%{
#include <stdlib.h>
#include "ast.h"
#include "y.tab.h"

%}

%%

"begin"         {return T_BEGIN;}
"end"           {return T_END;}
"program"       {return T_PROGRAM;}
"skip"          {return T_SKIP;}
"write"         {return T_WRITE;}

[a-zA-Z][a-zA-Z0-9_]*   {
                		yylval.s = strdup(yytext);
                		return T_VARIABLE;
            		}

[0-9]* 			{
                		yylval.f = atof(yytext);
                		return T_NUMERIC;
            		}

[0-9]+\.[0-9]+ 			{
                		yylval.f = atof(yytext);
                		return T_NUMERIC;
            		}

[ \t\n]+
.               { return *yytext; }

%%
int yywrap(void) {
    return 1;
}
