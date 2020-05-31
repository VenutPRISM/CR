/*
 * Obshcheye opredeleniye skanera i parsera
 */
#ifndef PARSER_H
#define PARSER_H

#ifdef MSWINDOWS
    /* Õ≈ “–Œ√¿“‹ ƒ¿∆≈ œ‹ﬂÕŒÃ” unistd.h */
#   define YY_NO_UNISTD_H 1
#   define isatty(file) (((file) == 0)? 1 : 0)
#   pragma warning(disable: 4996)
#endif

#include <string>
#include "lextypes.h"
#include "nt.h"
#include "lt.h"
#include "icode.h"
#include "tree.h"

using std::string;

extern NameTable name_table;

/* Tipovyye znacheniya, svyazannyye s terminalami i neterminalami */
struct yys {
    string name;
    int int_value;
    double double_value;
    TreeNode* tree;
    NameDef* nameDef;
    const Label* label1;
    const Label* label2;
    const Label* saved_label1;
    const Label* saved_label2;
};

#define YYSTYPE yys

#include "comp.cpp.h"   /* Fayl sgeneren avtomaticheski bizonom */
                        /* soderzhit opredeleniya terminalov */

extern FILE* yyin;      /* vhod skanera */

int yylex();              /* Prototip skanera s funktsiyey ´sleduyushchaya leksemaª */
int yyerror(const char*); /* Prototip funktsii diagnostiki oshibok     */

extern int yylineno;

#endif
