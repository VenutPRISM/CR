/* Eta vesh onositsya k skanneru*/
%{
#include "parser.h" 
/* Include obshee opredelenie parsera i skannera */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static const int MAX_STR_LEN = 1023;
static char curstr[MAX_STR_LEN+1];
static int curstr_len = 0;
static bool longString = false;
void scanError(const char *s, int lineno);

%}
        /* Makros, opredelyayushchiy pokazatel' v dvoynoy konstante */
EXP     ((E|e)("+"|"-")?[0-9]+)

%option yylineno
%Start S CCOMM CPPCOMM STR
%%
            {
                BEGIN S;
            }
<S>"if"     {
                // printf ("scan: IF\n");
                return IF; 
            }
<S>"else"   { return ELSE; }
<S>"elseif" { return ELSEIF; }
<S>"endif"  { return ENDIF; }
<S>"while"  { return WHILE; }
<S>"break"  { return BREAK; }
<S>"continue" { return CONTINUE; }
<S>"endwhile" { return ENDWHILE; }
<S>"input"  { return INPUT; }
<S>"output" { return OUTPUT; }
<S>"outputln" { return OUTPUTLN; }
<S>"end"    { return END; }
<S>"int"    {
                // printf ("scan: TYPE (int)\n");
                yylval.int_value = TYPE_INT;
                return TYPE;
            }
<S>"double" {
                // printf ("scan: TYPE (double)\n");
                yylval.int_value = TYPE_DOUBLE;
                return TYPE;
            }
<S>"string" {
                // printf ("scan: TYPE (string)\n");
                yylval.int_value = TYPE_STRING;
                return TYPE;
            }
<S>"+"      { return PLUS; }
<S>"-"      { return MINUS; }
<S>"*"      { return MUL; }
<S>"/"      { return DIV; }
<S>"%"      { return MOD; }
<S>"("      {
                // printf ("scan: LPAR\n");
                return LPAR; 
            }
<S>")"      {
                // printf ("scan: RPAR\n");
                return RPAR;
            }
<S>"["      { return LBR; }
<S>"]"      { return RBR; }
<S>","      { return CM; }
<S>";"      { return SM; }
<S>"="      { return ASG; }
<S>"=="     {
                // printf ("scan: RELOP_EQ\n");
                yylval.int_value = RELOP_EQ;
                return RELOP;
            }
<S>"!="     {
                // printf ("scan: RELOP_NE\n");
                yylval.int_value = RELOP_NE;
                return RELOP;
            }
<S>">"      {
                // printf ("scan: RELOP_GT\n");
                yylval.int_value = RELOP_GT;
                return RELOP;
            }
<S>">="     {
                // printf ("scan: RELOP_GE\n");
                yylval.int_value = RELOP_GE;
                return RELOP;
            }
<S>"<"      {
                // printf ("scan: RELOP_LT\n");
                yylval.int_value = RELOP_LT;
                return RELOP;
            }
<S>"<="     {
                // printf ("scan: RELOP_LE\n");
                yylval.int_value = RELOP_LE;
                return RELOP;
            }
<S>"||"     { return LOR; }
<S>"&&"     { return LAND; }
<S>"!"      { return LNOT; }

<S>[a-zA-Z][a-zA-Z0-9]* {
                // printf("NAME %s\n", yytext);

                yylval.name = yytext;

                // printf("NAME %s is added to string pool\n", yytext);
                return NAME;
            }

<S>(" "|\t)*   {}                  /* Propustit' probel */

            /* Tselochislennaya konstanta */
<S>[0-9]+   {
                yylval.int_value = atoi(yytext);
                return INT_CONST;
            }

            /* Dvoynaya konstanta mozhet byt' v odnoy iz sleduyushchikh 3 form:        */
            /* 1) .5, .5e-20, 1.2, 123.456E+10 (obyazatel'nyy punkt i drob') */
            /* 2) 1., 123.e+10, 0.2E-20, 35.3  (obyazatel'noye tseloye chislo i tochka)  */
            /* 3) 1e+10, 2e20, 1E-12        (obyazatel'noye tseloye chislo i pokazatel' stepeni)  */
            /* Vyrazheniye dlya double yavlyayetsya ob"yedineniyem "|" iz 3 podvyrazheniy */

<S>([0-9]*"."[0-9]+{EXP}?)|([0-9]+"."[0-9]*{EXP}?)|([0-9]+{EXP}) {
                yylval.double_value = atof(yytext);
                return DOUBLE_CONST;
            }

<S>\n|\r\n  { /* return ENDL; */ } /* Konets stroki v forme Unix ili MS DOS */

<S>\"       {
                BEGIN STR;
                curstr_len = 0; longString = false;
            }

<STR>[^"\n\r\t] {
                if (curstr_len < MAX_STR_LEN) {
                    curstr[curstr_len] = yytext[0];
                    ++curstr_len;
                } else {
                    LLongString: ;
                    if (!longString) {
                        longString = true;
                        scanError(
                            "String constant is too long",
                            yylineno
                        );
                    }
                }
            }
<STR>\\\"   {
                if (curstr_len < MAX_STR_LEN) {
                    curstr[curstr_len] = '\"';
                    ++curstr_len;
                } else {
                    goto LLongString;
                }
            }
<STR>\\n    {
                if (curstr_len < MAX_STR_LEN) {
                    curstr[curstr_len] = '\n';
                    ++curstr_len;
                } else {
                    goto LLongString;
                }
            }
<STR>\\r    {
                if (curstr_len < MAX_STR_LEN) {
                    curstr[curstr_len] = '\r';
                    ++curstr_len;
                } else {
                    goto LLongString;
                }
            }
<STR>\\t    {
                if (curstr_len < MAX_STR_LEN) {
                    curstr[curstr_len] = '\t';
                    ++curstr_len;
                } else {
                    goto LLongString;
                }
            }
<STR>\"     {
                LOffString: ;
                curstr[curstr_len] = 0;
                yylval.name = curstr;
                // printf("scan: STRING_CONST: %s\n", yylval.name.c_str());
                BEGIN S;
                return STRING_CONST;
            }
<STR>\n|\r\n {
                scanError(
                    "Nonterminated string constant", 
                    yylineno-1
                );
                goto LOffString;
            }
<S>"/*"     { BEGIN CCOMM; }
<CCOMM>(.|\n) {}
<CCOMM>"*/" { BEGIN S; }
<S>"//"     { BEGIN CPPCOMM; }
<CPPCOMM>.  {}
<CPPCOMM>\n { BEGIN S; }
<S>.        { return ILLEGAL; } /* Lyuboy drugoy char */

%%
            /*============= Razdel pol'zovatel'skikh programm ===================*/

int yywrap() { return 1; }      /* Stop v kontse fayla */

void scanError(const char *s, int line) {
    fprintf(
        stderr, "Scanner error: %s in line %d\n", 
        s, line
    );
}
