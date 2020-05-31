
/*  parser Bison, sozdan is comp.y 
  */

#define YYBISON 1  /* Opredelit' vykhod.  */

#define	NAME	258
#define	INT_CONST	259
#define	DOUBLE_CONST	260
#define	STRING_CONST	261
#define	WHILE	262
#define	ENDWHILE	263
#define	IF	264
#define	ENDIF	265
#define	ELSE	266
#define	ELSEIF	267
#define	TYPE	268
#define	BREAK	269
#define	CONTINUE	270
#define	SM	271
#define	CM	272
#define	LBR	273
#define	RBR	274
#define	LPAR	275
#define	RPAR	276
#define	ILLEGAL	277
#define	INPUT	278
#define	OUTPUT	279
#define	OUTPUTLN	280
#define	END	281
#define	ASG	282
#define	RELOP	283
#define	LOR	284
#define	LAND	285
#define	LNOT	286
#define	PLUS	287
#define	MINUS	288
#define	MUL	289
#define	DIV	290
#define	MOD	291
#define	UMINUS	292

#line 1 "comp.y"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "parser.h"
#include "interpret.h"

static int base_type = TYPE_UNDEFINED;
NameTable name_table;
LabelTable label_table;
IProgram icode;
static char error_text[128];

static int binOper = 0;

static const Label* breakLabel = 0;
static const Label* continueLabel = 0;
static const Label* endifLabel = 0;

static void genExpr(const TreeNode* tree);

// Either trueLabel or falseLabel == 0
static void genLExpr(
    const TreeNode* tree,   // Predstavlyayet logicheskoye vyrazheniye
    const Label* trueLabel,
    const Label* falseLabel
);

static void genNop(const Label* label);
static void genGoto(const Label* label);
static const Label* genLabel();
static void checkNames();
static void printWarning(const char *text);
static void printError(const char *text);


#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		126
#define	YYFLAG		-32768
#define	YYNTBASE	38

#define YYTRANSLATE(x) ((unsigned)(x) <= 292 ? yytranslate[x] : 67)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     5,     7,    10,    12,    14,    17,    20,    23,
    27,    29,    31,    35,    37,    42,    44,    46,    48,    51,
    54,    56,    58,    60,    65,    67,    72,    74,    78,    82,
    86,    90,    94,    97,    99,   104,   106,   108,   110,   114,
   118,   119,   125,   126,   132,   137,   139,   142,   144,   147,
   150,   153,   158,   162,   166,   170,   173,   177,   181,   186,
   190,   192,   196,   200,   203,   207,   209
};

static const short yyrhs[] = {    39,
     0,    39,    26,     0,    40,     0,    39,    40,     0,    41,
     0,    45,     0,     1,    16,     0,     1,    10,     0,     1,
     8,     0,    42,    43,    16,     0,    13,     0,    44,     0,
    43,    17,    44,     0,     3,     0,     3,    18,    49,    19,
     0,    46,     0,    50,     0,    60,     0,    14,    16,     0,
    15,    16,     0,    62,     0,    64,     0,    65,     0,    47,
    27,    49,    16,     0,    48,     0,    48,    18,    49,    19,
     0,     3,     0,    49,    32,    49,     0,    49,    33,    49,
     0,    49,    34,    49,     0,    49,    35,    49,     0,    49,
    36,    49,     0,    33,    49,     0,     3,     0,     3,    18,
    49,    19,     0,     4,     0,     5,     0,     6,     0,    20,
    49,    21,     0,    53,    39,    10,     0,     0,    53,    39,
    51,    56,    10,     0,     0,    53,    39,    52,    54,    10,
     0,     9,    20,    59,    21,     0,    55,     0,    55,    56,
     0,    57,     0,    55,    57,     0,    11,    39,     0,    58,
    39,     0,    12,    20,    59,    21,     0,    49,    28,    49,
     0,    59,    29,    59,     0,    59,    30,    59,     0,    31,
    59,     0,    20,    59,    21,     0,    61,    39,     8,     0,
     7,    20,    59,    21,     0,    23,    63,    16,     0,    47,
     0,    63,    17,    47,     0,    24,    66,    16,     0,    25,
    16,     0,    25,    66,    16,     0,    49,     0,    66,    17,
    49,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    54,    59,    68,    71,    76,    79,    82,    85,    88,    93,
    98,   103,   106,   111,   131,   156,   157,   158,   159,   166,
   173,   174,   175,   178,   189,   190,   197,   208,   217,   221,
   225,   229,   233,   239,   247,   259,   265,   271,   277,   280,
   284,   292,   296,   304,   310,   319,   320,   323,   324,   327,
   330,   336,   343,   351,   358,   365,   371,   376,   386,   403,
   406,   411,   414,   417,   427,   430,   437
};

static const char * const yytname[] = {   "$","error","$undefined.","NAME","INT_CONST",
"DOUBLE_CONST","STRING_CONST","WHILE","ENDWHILE","IF","ENDIF","ELSE","ELSEIF",
"TYPE","BREAK","CONTINUE","SM","CM","LBR","RBR","LPAR","RPAR","ILLEGAL","INPUT",
"OUTPUT","OUTPUTLN","END","ASG","RELOP","LOR","LAND","LNOT","PLUS","MINUS","MUL",
"DIV","MOD","UMINUS","program","stms","stm","decl","type","defs","def","oper",
"assign","lval","lval_name","expr","if","@1","@2","ifh","elseifs","elseiflist",
"else","elseif","elseifh","lexpr","while","whileh","input","inputlst","output",
"outputln","outputlst",""
};
#endif

static const short yyr1[] = {     0,
    38,    38,    39,    39,    40,    40,    40,    40,    40,    41,
    42,    43,    43,    44,    44,    45,    45,    45,    45,    45,
    45,    45,    45,    46,    47,    47,    48,    49,    49,    49,
    49,    49,    49,    49,    49,    49,    49,    49,    49,    50,
    51,    50,    52,    50,    53,    54,    54,    55,    55,    56,
    57,    58,    59,    59,    59,    59,    59,    60,    61,    62,
    63,    63,    64,    65,    65,    66,    66
};

static const short yyr2[] = {     0,
     1,     2,     1,     2,     1,     1,     2,     2,     2,     3,
     1,     1,     3,     1,     4,     1,     1,     1,     2,     2,
     1,     1,     1,     4,     1,     4,     1,     3,     3,     3,
     3,     3,     2,     1,     4,     1,     1,     1,     3,     3,
     0,     5,     0,     5,     4,     1,     2,     1,     2,     2,
     2,     4,     3,     3,     3,     2,     3,     3,     4,     3,
     1,     3,     3,     2,     3,     1,     3
};

static const short yydefact[] = {     0,
     0,    27,     0,     0,    11,     0,     0,     0,     0,     0,
     0,     3,     5,     0,     6,    16,     0,    25,    17,     0,
    18,     0,    21,    22,    23,     9,     8,     7,     0,     0,
    19,    20,    61,     0,    34,    36,    37,    38,     0,     0,
    66,     0,    64,     0,     2,     4,    14,     0,    12,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    60,     0,
     0,     0,    33,     0,     0,     0,     0,     0,    63,     0,
    65,     0,    10,     0,     0,     0,    40,     0,     0,    58,
     0,     0,    56,     0,    59,     0,     0,    45,    62,     0,
    39,    28,    29,    30,    31,    32,    67,     0,    13,    24,
    26,     0,     0,     0,     0,    46,    48,     0,    57,    53,
    54,    55,    35,    15,     0,    42,     0,    44,    47,    49,
     0,     0,    52,     0,     0,     0
};

static const short yydefgoto[] = {   124,
    11,    12,    13,    14,    48,    49,    15,    16,    17,    18,
    56,    19,    78,    79,    20,   105,   106,   103,   107,   108,
    57,    21,    22,    23,    34,    24,    25,    42
};

static const short yypact[] = {   194,
    11,-32768,   -14,     0,-32768,    24,    28,    50,    52,     6,
    92,-32768,-32768,    68,-32768,-32768,    47,    55,-32768,   194,
-32768,   194,-32768,-32768,-32768,-32768,-32768,-32768,    12,    12,
-32768,-32768,-32768,     7,    66,-32768,-32768,-32768,    52,    52,
   241,    14,-32768,    19,-32768,-32768,    69,    30,-32768,    52,
    52,   118,   156,    12,    12,   236,   -16,     4,-32768,    50,
    52,   227,-32768,    52,    52,    52,    52,    52,-32768,    52,
-32768,    52,-32768,    68,   178,   196,-32768,    75,    76,-32768,
   222,    46,-32768,    52,-32768,    12,    12,-32768,-32768,   201,
-32768,    45,    45,-32768,-32768,-32768,   241,   206,-32768,-32768,
-32768,   194,    80,    74,    86,    39,-32768,   194,-32768,   241,
    67,-32768,-32768,-32768,   175,-32768,    12,-32768,-32768,-32768,
   137,    48,-32768,    98,   100,-32768
};

static const short yypgoto[] = {-32768,
   -19,   -11,-32768,-32768,-32768,    29,-32768,-32768,    -6,-32768,
    -2,-32768,-32768,-32768,-32768,-32768,-32768,    -4,     2,-32768,
   -26,-32768,-32768,-32768,-32768,-32768,-32768,    99
};


#define	YYLAST		277


static const short yytable[] = {    46,
    52,    33,    53,    58,    85,    29,    41,    41,    35,    36,
    37,    38,    86,    87,    35,    36,    37,    38,    26,    30,
    27,    43,    59,    60,    88,    39,    28,    82,    83,    69,
    70,    54,    86,    87,    71,    70,    62,    63,    40,    31,
    46,    46,    55,    32,    40,    73,    74,    75,    76,   102,
   104,    81,     2,    89,    35,    36,    37,    38,    90,   111,
   112,    92,    93,    94,    95,    96,   109,    97,   123,    98,
    47,    39,    51,    50,    86,    87,    86,    87,    66,    67,
    68,   110,   115,    61,    40,   102,    72,   104,   121,   116,
   122,    -1,     1,   117,     2,   118,    87,   125,     3,   126,
     4,   119,    99,    46,     5,     6,     7,   120,    44,    46,
     0,     0,     0,     0,     8,     9,    10,    45,     1,     0,
     2,     0,     0,     0,     3,     0,     4,    77,   -41,   -43,
     5,     6,     7,     0,     0,     0,     0,     1,     0,     2,
     8,     9,    10,     3,     0,     4,   -51,   -51,   -51,     5,
     6,     7,     0,     0,     0,     0,     1,     0,     2,     8,
     9,    10,     3,    80,     4,     0,     0,     0,     5,     6,
     7,     0,     0,     0,     0,     1,     0,     2,     8,     9,
    10,     3,     0,     4,   -50,     0,     0,     5,     6,     7,
     0,     0,     0,   100,     1,     0,     2,     8,     9,    10,
     3,     0,     4,     0,     0,     0,     5,     6,     7,    64,
    65,    66,    67,    68,   101,     0,     8,     9,    10,   113,
     0,     0,     0,     0,   114,     0,     0,    64,    65,    66,
    67,    68,    64,    65,    66,    67,    68,    64,    65,    66,
    67,    68,    91,     0,     0,     0,     0,    91,     0,    84,
     0,     0,     0,    64,    65,    66,    67,    68,    64,    65,
    66,    67,    68,    84,     0,     0,     0,    64,    65,    66,
    67,    68,    64,    65,    66,    67,    68
};

static const short yycheck[] = {    11,
    20,     8,    22,    30,    21,    20,     9,    10,     3,     4,
     5,     6,    29,    30,     3,     4,     5,     6,     8,    20,
    10,    16,    16,    17,    21,    20,    16,    54,    55,    16,
    17,    20,    29,    30,    16,    17,    39,    40,    33,    16,
    52,    53,    31,    16,    33,    16,    17,    50,    51,    11,
    12,    54,     3,    60,     3,     4,     5,     6,    61,    86,
    87,    64,    65,    66,    67,    68,    21,    70,    21,    72,
     3,    20,    18,    27,    29,    30,    29,    30,    34,    35,
    36,    84,   102,    18,    33,    11,    18,    12,   108,    10,
   117,     0,     1,    20,     3,    10,    30,     0,     7,     0,
     9,   106,    74,   115,    13,    14,    15,   106,    10,   121,
    -1,    -1,    -1,    -1,    23,    24,    25,    26,     1,    -1,
     3,    -1,    -1,    -1,     7,    -1,     9,    10,    11,    12,
    13,    14,    15,    -1,    -1,    -1,    -1,     1,    -1,     3,
    23,    24,    25,     7,    -1,     9,    10,    11,    12,    13,
    14,    15,    -1,    -1,    -1,    -1,     1,    -1,     3,    23,
    24,    25,     7,     8,     9,    -1,    -1,    -1,    13,    14,
    15,    -1,    -1,    -1,    -1,     1,    -1,     3,    23,    24,
    25,     7,    -1,     9,    10,    -1,    -1,    13,    14,    15,
    -1,    -1,    -1,    16,     1,    -1,     3,    23,    24,    25,
     7,    -1,     9,    -1,    -1,    -1,    13,    14,    15,    32,
    33,    34,    35,    36,    19,    -1,    23,    24,    25,    19,
    -1,    -1,    -1,    -1,    19,    -1,    -1,    32,    33,    34,
    35,    36,    32,    33,    34,    35,    36,    32,    33,    34,
    35,    36,    21,    -1,    -1,    -1,    -1,    21,    -1,    28,
    -1,    -1,    -1,    32,    33,    34,    35,    36,    32,    33,
    34,    35,    36,    28,    -1,    -1,    -1,    32,    33,    34,
    35,    36,    32,    33,    34,    35,    36
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  kolichestvo tokenov, kotoryye nuzhno sdvinut' do vklyucheniya soobshcheniy ob oshibkakh */
  int yychar1 = 0;		/*  eksema v kachestve vnutrennego (perevedennogo) nomera tokena */

  short	yyssa[YYINITDEPTH];	/*  stek sostoyaniy			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  stek semanticheskikh znacheniy		*/

  short *yyss = yyssa;		/*  obrashenie' k stekam cherez otdel'nyye ukazateli */
  YYSTYPE *yyvs = yyvsa;	/*  chtoby pozvolit' yyoverflow pereraspredelit' ikh v drugom meste */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  stek mestopolozheniya			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  peremennaya, ispol'zuyemaya dlya vozvrata		*/
				/*  semanticheskiye tsennosti iz deystviya	*/
				/*  podprogrammy				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Zastavit' token byt' prochitannym  */

  /* Initsializiruyte ukazateli steka.
     Poteryat' odin element stoimosti i steka mestopolozheniya
     chtoby oni ostavalis' na odnom urovne so stekom sostoyaniy.
     Poteryannyye elementy nikogda ne initsializiruyutsya.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* vnesti novoye sostoyaniye, kotoroye nakhoditsya v yystate  .  */
/* Vo vsekh sluchayakh, kogda vy popadayete syuda, znacheniye i mestopolozheniye skladyvayutsya
   tol'ko chto push. tak chto prodvizheniye state zdes' vyravnivayet stek.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Dayte pol'zovatelyu vozmozhnost' pereraspredelit' stek*/
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Poluchite tekushchiy ispol'zuyemyy razmer trekh stekov v elementakh.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Sdelayte sootvetstvuyushchuyu obrabotku s uchetom tekushchego sostoyaniya.  */
/* Prochitayte leksem, yesli on nam nuzhen, a u nas yego yeshche net.  */
/* yyresume: */

  /* Snachala popytaytes' reshit', chto delat', ne obrashchayas' k tokenu predprosmotra.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Preobrazovat' token vo vnutrennyuyu formu (v yychar1) dlya indeksatsii tablits s */

  if (yychar <= 0)		/* Eto oznachayet konets vvoda. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* ne vizivat' YYLEX bolshe */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn chto delat' dlya etogo tipa tokena v etom sostoyanii.
     Otritsatel'nyy => umen'shit', -yyn - nomer pravila.
     Polozhitel'nyy => sdvig, yyn - novoye sostoyaniye.
       Novoye sostoyaniye yavlyayetsya konechnym sostoyaniyem => ne bespokoytes' o sdvige,
       prosto vernite uspekh.
     0 ili samoye otritsatel'noye chislo => oshibka. */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Sdvin'te token ozhidaniya  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Otkazhites' ot sdvigayemogo tokena, yesli on ne byl eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* chislo tokenov smeshcheno s momenta oshibki; posle trekh vyklyuchite status oshibki.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Vypolnite deystviye po umolchaniyu dlya tekushchego sostoyaniya.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Sdelat' sokrashcheniye. yyn - nomer pravila, s kotorym nuzhno umen'shit'.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* realizovat' znacheniye po umolchaniyu dlya deystviya */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 54 "comp.y"
{
              checkNames();
              icode.print();
              printf("--------\n\n");
          ;
    break;}
case 2:
#line 59 "comp.y"
{
              checkNames();
              icode.print();
              printf("--------\n\n");
              // YYACCEPT;
              return 0;
          ;
    break;}
case 3:
#line 68 "comp.y"
{
              // printf("stms: stm\n"); 
          ;
    break;}
case 4:
#line 71 "comp.y"
{ 
              // printf("stms: stms stm\n");
          ;
    break;}
case 5:
#line 76 "comp.y"
{
              // printf("stm: decl\n");
          ;
    break;}
case 6:
#line 79 "comp.y"
{
              // printf("stm: oper\n"); 
          ;
    break;}
case 7:
#line 82 "comp.y"
{
              // printf("stm: error SM\n"); 
          ;
    break;}
case 8:
#line 85 "comp.y"
{
              // printf("stm: error ENDIF\n"); 
          ;
    break;}
case 9:
#line 88 "comp.y"
{ 
              // printf("stm: error WHILE\n"); 
          ;
    break;}
case 10:
#line 93 "comp.y"
{
              // printf("decl\n"); 
          ;
    break;}
case 11:
#line 98 "comp.y"
{
              base_type = yyvsp[0].int_value;
          ;
    break;}
case 12:
#line 103 "comp.y"
{
              // printf("def\n"); 
          ;
    break;}
case 13:
#line 106 "comp.y"
{
              // printf("defs CM def\n"); 
          ;
    break;}
case 14:
#line 111 "comp.y"
{
              NameDef* n = name_table.addName(yyvsp[0].name);
              n->baseType = base_type;
              n->dimension = 0;
              ++(n->numDefinitions);
              n->modifiers |= NameDef::NAME_VARIABLE;
              if (n->numDefinitions > 1) {
                  sprintf(
                      error_text, "Multiple definition of %s",
                      n->name.c_str()
                  );
                  yyerror(error_text);
              }
              // printf("variable %s\n", n->name);

              IProgram::iterator c = icode.addNewCommand();
              c->type = ICommand::def_variable;
              c->ext = base_type;
              c->name_ptr = n;
          ;
    break;}
case 15:
#line 131 "comp.y"
{
              // $3.tree->print();
              genExpr(yyvsp[-1].tree);

              NameDef* n = name_table.addName(yyvsp[-3].name);
              n->baseType = base_type;
              n->dimension = 1; // Array
              ++(n->numDefinitions);
              n->modifiers |= NameDef::NAME_ARRAY;
              if (n->numDefinitions > 1) {
                  sprintf(
                      error_text, "Multiple definition of %s",
                      n->name.c_str()
                  );
                  yyerror(error_text);
              }
              // printf("variable %s\n", n->name);

              IProgram::iterator c = icode.addNewCommand();
              c->type = ICommand::def_array;
              c->ext = base_type;
              c->name_ptr = n;
          ;
    break;}
case 19:
#line 159 "comp.y"
{
              if (breakLabel == 0) {
                  yyerror("break out of loop");
              } else {
                  genGoto(breakLabel);
              }
          ;
    break;}
case 20:
#line 166 "comp.y"
{
              if (continueLabel == 0) {
                  yyerror("continue out of loop");
              } else {
                  genGoto(continueLabel);
              }
          ;
    break;}
case 24:
#line 178 "comp.y"
{
              // printf("assign: right expr:\n");
              // $3.tree->print();

              genExpr(yyvsp[-1].tree);

              IProgram::iterator c = icode.addNewCommand();
              c->type = ICommand::assign;
          ;
    break;}
case 26:
#line 190 "comp.y"
{
              genExpr(yyvsp[-1].tree);
              IProgram::iterator c = icode.addNewCommand();
              c->type = ICommand::array_lvalue;
          ;
    break;}
case 27:
#line 197 "comp.y"
{
                NameDef* n = name_table.addName(yyvsp[0].name);
                // printf("l-value %s\n", n->name);
                ++(n->numWrites);

                IProgram::iterator c = icode.addNewCommand();
                c->type = ICommand::name_lvalue;
                c->name_ptr = n;
            ;
    break;}
case 28:
#line 208 "comp.y"
{
              binOper = TreeNode::plus;
              LBinOper: ;
              TreeNode* t = new TreeNode();
              t->nodeType = binOper;
              t->addLeftSon(yyvsp[-2].tree);
              t->addRightSon(yyvsp[0].tree);
              yyval.tree = t;
          ;
    break;}
case 29:
#line 217 "comp.y"
{
              binOper = TreeNode::minus;
              goto LBinOper;
          ;
    break;}
case 30:
#line 221 "comp.y"
{
              binOper = TreeNode::mul;
              goto LBinOper;
          ;
    break;}
case 31:
#line 225 "comp.y"
{
              binOper = TreeNode::div;
              goto LBinOper;
          ;
    break;}
case 32:
#line 229 "comp.y"
{
              binOper = TreeNode::mod;
              goto LBinOper;
          ;
    break;}
case 33:
#line 233 "comp.y"
{
              TreeNode* t = new TreeNode();
              t->nodeType = TreeNode::uminus;
              t->addLeftSon(yyvsp[0].tree);
              yyval.tree = t;
          ;
    break;}
case 34:
#line 239 "comp.y"
{
              TreeNode* t = new TreeNode();
              NameDef* n = name_table.addName(yyvsp[0].name);
              ++(n->numReads);
              t->nodeType = TreeNode::name;
              t->nameDef = n;
              yyval.tree = t;
          ;
    break;}
case 35:
#line 247 "comp.y"
{
              TreeNode* t = new TreeNode();
              t->nodeType = TreeNode::array_idx;
              NameDef* n = name_table.addName(yyvsp[-3].name);
              ++(n->numReads);
              TreeNode* t1 = new TreeNode();
              t1->nodeType = TreeNode::name;
              t1->nameDef = n;
              t->addLeftSon(t1);
              t->addRightSon(yyvsp[-1].tree);
              yyval.tree = t;
          ;
    break;}
case 36:
#line 259 "comp.y"
{
              TreeNode* t = new TreeNode();
              t->nodeType = TreeNode::int_const;
              t->intValue = yyvsp[0].int_value;
              yyval.tree = t;
          ;
    break;}
case 37:
#line 265 "comp.y"
{
              TreeNode* t = new TreeNode();
              t->nodeType = TreeNode::double_const;
              t->doubleValue = yyvsp[0].double_value;
              yyval.tree = t;
          ;
    break;}
case 38:
#line 271 "comp.y"
{
              TreeNode* t = new TreeNode();
              t->nodeType = TreeNode::string_const;
              t->stringValue = yyvsp[0].name;
              yyval.tree = t;
          ;
    break;}
case 39:
#line 277 "comp.y"
{ yyval.tree = yyvsp[-1].tree; ;
    break;}
case 40:
#line 280 "comp.y"
{ 
              // printf("if: ifh stmd ENDIF\n");
              genNop(yyvsp[-2].label1);        // Label of endif
          ;
    break;}
case 41:
#line 284 "comp.y"
{
              const Label* endif_label = genLabel();
              yyvsp[-1].label2 = endif_label;
              yyvsp[-1].saved_label2 = endifLabel;
              endifLabel = endif_label;
              genGoto(endif_label);
              genNop(yyvsp[-1].label1);
          ;
    break;}
case 42:
#line 292 "comp.y"
{
              genNop(yyvsp[-4].label2);
              endifLabel = yyvsp[-4].saved_label2;
          ;
    break;}
case 43:
#line 296 "comp.y"
{
              const Label* endif_label = genLabel();
              yyvsp[-1].label2 = endif_label;
              yyvsp[-1].saved_label2 = endifLabel;  // Save previous endif label
              endifLabel = endif_label;
              genGoto(endif_label);
              genNop(yyvsp[-1].label1);
          ;
    break;}
case 44:
#line 304 "comp.y"
{
              genNop(yyvsp[-4].label2);
              endifLabel = yyvsp[-4].saved_label2;
          ;
    break;}
case 45:
#line 310 "comp.y"
{ 
              // printf("ifh\n");
              const Label* l = genLabel();
              // $3.tree->print();
              genLExpr(yyvsp[-1].tree, 0, l);
              yyval.label1 = l;
          ;
    break;}
case 51:
#line 330 "comp.y"
{
              genGoto(endifLabel);
              genNop(yyvsp[-1].label1);
          ;
    break;}
case 52:
#line 336 "comp.y"
{
              const Label* l = genLabel();
              genLExpr(yyvsp[-1].tree, 0, l);
              yyval.label1 = l;
          ;
    break;}
case 53:
#line 343 "comp.y"
{
              TreeNode* t = new TreeNode();
              t->nodeType = TreeNode::relop;
              t->intValue = yyvsp[-1].int_value; // operation: RELOP_EQ, etc.
              t->addLeftSon(yyvsp[-2].tree);
              t->addRightSon(yyvsp[0].tree);
              yyval.tree = t;
          ;
    break;}
case 54:
#line 351 "comp.y"
{
              TreeNode* t = new TreeNode();
              t->nodeType = TreeNode::lor;
              t->addLeftSon(yyvsp[-2].tree);
              t->addRightSon(yyvsp[0].tree);
              yyval.tree = t;
          ;
    break;}
case 55:
#line 358 "comp.y"
{
              TreeNode* t = new TreeNode();
              t->nodeType = TreeNode::land;
              t->addLeftSon(yyvsp[-2].tree);
              t->addRightSon(yyvsp[0].tree);
              yyval.tree = t;
          ;
    break;}
case 56:
#line 365 "comp.y"
{
              TreeNode* t = new TreeNode();
              t->nodeType = TreeNode::lnot;
              t->addLeftSon(yyvsp[0].tree);
              yyval.tree = t;
          ;
    break;}
case 57:
#line 371 "comp.y"
{
              yyval.tree = yyvsp[-1].tree;
          ;
    break;}
case 58:
#line 376 "comp.y"
{ 
              // printf("while\n");
              // Restore loop labels
              genGoto(yyvsp[-2].label1);
              genNop(yyvsp[-2].label2);
              continueLabel = yyvsp[-2].saved_label1;
              breakLabel = yyvsp[-2].saved_label2;
          ;
    break;}
case 59:
#line 386 "comp.y"
{ 
              // printf("whileh\n");
              const Label* beginLab = genLabel();
              const Label* endLab = genLabel();
              yyval.label1 = beginLab;
              yyval.label2 = endLab;

              genNop(beginLab);
              genLExpr(yyvsp[-1].tree, 0, endLab);

              yyval.saved_label1 = continueLabel;
              yyval.saved_label2 = breakLabel;
              continueLabel = beginLab;
              breakLabel = endLab;
          ;
    break;}
case 61:
#line 406 "comp.y"
{
              LInput: ;
              IProgram::iterator c = icode.addNewCommand();
              c->type = ICommand::input;
          ;
    break;}
case 62:
#line 411 "comp.y"
{ goto LInput; ;
    break;}
case 64:
#line 417 "comp.y"
{
              LNewLine: ;   
              // Output the "new line" character
              IProgram::iterator c = icode.addNewCommand();
              c->type = ICommand::string_const;
              c->string_value = "\n";
                
              c = icode.addNewCommand();
              c->type = ICommand::output;
          ;
    break;}
case 65:
#line 427 "comp.y"
{ goto LNewLine; ;
    break;}
case 66:
#line 430 "comp.y"
{
              LOutput: ;
              genExpr(yyvsp[0].tree);

              IProgram::iterator c = icode.addNewCommand();
              c->type = ICommand::output;
          ;
    break;}
case 67:
#line 437 "comp.y"
{ goto LOutput; ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Teper' «smestim» rezul'tat sokrashcheniya.
     Opredelite, v kakom sostoyanii eto proiskhodit,
     osnovannyy na sostoyanii my vernulis' k
     i nomer pravila umen'shayetsya na  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* zdes' pri obnaruzhenii oshibki!!!!! */

  if (! yyerrstatus)
    /* Yesli vy ne vosstanavlivayetes' posle oshibki, soobshchite ob etoy oshibke.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 440 "comp.y"


int main(int argc, char *argv[]) {
    FILE* f = NULL;
    if (argc > 1) {
        // Open an input file
        FILE* f = fopen(argv[1], "r");
        if (f != NULL)
            yyin = f;
    }
    yyparse();
    if (f != NULL)
        fclose(f);

    ICodeInterpretator interpretator;
    interpretator.initialize(&icode);
    try {
        interpretator.execute();
        /*
        printf("stack depth = %d\n", interpretator.stack.size());
        if (interpretator.stack.size() > 0) {
            printf("stack top: ");
            interpretator.printStackTop();
            printf("\n");
        }
        */
    } catch (InterpretatorException& e) {
        printf(
            "InterpretatorException: %s\n",
            e.reason
        );
        exit(1);
    } catch (StackException& e) {
        printf(
            "StackException: %s\n",
            e.reason
        );
        exit(1);
    } catch (OutOfRangeException& e) {
        printf(
            "OutOfRangeException: %s\n",
            e.reason
        );
        exit(1);
    }
    return 0;
}

int yyerror(const char *s) {
    printf("%s in line %d\n", s, yylineno);
    return 0;
}

static void genExpr(const TreeNode* tree) {
    if (tree == 0)
        return;
    IProgram::iterator c;
    int binop;

    switch(tree->nodeType) {
    case TreeNode::int_const:
        c = icode.addNewCommand();
        c->type = ICommand::int_const;
        c->int_value = tree->intValue;
        break;
    case TreeNode::double_const:
        c = icode.addNewCommand();
        c->type = ICommand::double_const;
        c->double_value = tree->doubleValue;
        break;
    case TreeNode::string_const:
        c = icode.addNewCommand();
        c->type = ICommand::string_const;
        c->string_value = tree->stringValue;
        break;
    case TreeNode::name:
        c = icode.addNewCommand();
        c->type = ICommand::name;
        c->name_ptr = tree->nameDef;
        break;
    case TreeNode::array_idx:
        if (tree->left == 0 || tree->right == 0) {
            yyerror("Illegal expression");
            return;
        }
        c = icode.addNewCommand();
        c->type = ICommand::name_lvalue;
        c->name_ptr = tree->left->nameDef;

        genExpr(tree->right);

        c = icode.addNewCommand();
        c->type = ICommand::array_element;
        break;
    case TreeNode::plus:
        binop = ICommand::plus;
        LBinOp: ;
        if (tree->left == 0 || tree->right == 0) {
            yyerror("Illegal expression");
            return;
        }
        genExpr(tree->left);
        genExpr(tree->right);
        c = icode.addNewCommand();
        c->type = binop;
        break;
    case TreeNode::minus:
        binop = ICommand::minus;
        goto LBinOp;
    case TreeNode::mul:
        binop = ICommand::mul;
        goto LBinOp;
    case TreeNode::div:
        binop = ICommand::div;
        goto LBinOp;
    case TreeNode::mod:
        binop = ICommand::mod;
        goto LBinOp;
    case TreeNode::uminus:
        if (tree->left == 0) {
            yyerror("Illegal expression");
            return;
        }
        genExpr(tree->left);
        c = icode.addNewCommand();
        c->type = ICommand::uminus;
        break;
    default:
        yyerror("Illegal expression");
    }
}

static void genNop(const Label* label) {
    IProgram::iterator c = icode.addNewCommand();
    label->location = c;
    c->type = ICommand::nop;
    c->label_ptr = label;
    c->label = label->number;
}

static void genGoto(const Label* label) {
    IProgram::iterator c = icode.addNewCommand();
    c->type = ICommand::go_to;
    c->goto_label_ptr = label;
    c->goto_label = label->number;
}

static int baseLabel = 0;

static const Label* genLabel() {
    ++baseLabel;
    const Label* lab = label_table.addLabel(baseLabel);
    return lab;
}

static void genLExpr(
    const TreeNode* tree,   // Represents a logical expression
    const Label* trueLabel,
    const Label* falseLabel
) {
    IProgram::iterator c;

    switch (tree->nodeType) {
    case TreeNode::relop:
        if (tree->left == 0 || tree->right == 0) {
            yyerror("Illegal comparing");
            return;
        }
        genExpr(tree->left);
        genExpr(tree->right);
        c = icode.addNewCommand();
        c->type = ICommand::cmp;        // Compare

        c = icode.addNewCommand();
        c->type = ICommand::if_goto;

        if (trueLabel != 0) {
            switch (tree->intValue) {   // relation
                case RELOP_EQ: c->ext = ICommand::eq; break;
                case RELOP_NE: c->ext = ICommand::ne; break;
                case RELOP_LT: c->ext = ICommand::lt; break;
                case RELOP_LE: c->ext = ICommand::le; break;
                case RELOP_GT: c->ext = ICommand::gt; break;
                case RELOP_GE: c->ext = ICommand::ge; break;
            }
            c->goto_label_ptr = trueLabel;
            c->goto_label = trueLabel->number;
        } else {
            assert(falseLabel != 0);
            switch (tree->intValue) {  // relation
                case RELOP_EQ: c->ext = ICommand::ne; break; // Inverse
                case RELOP_NE: c->ext = ICommand::eq; break;
                case RELOP_LT: c->ext = ICommand::ge; break;
                case RELOP_LE: c->ext = ICommand::gt; break;
                case RELOP_GT: c->ext = ICommand::le; break;
                case RELOP_GE: c->ext = ICommand::lt; break;
            }
            c->goto_label_ptr = falseLabel;
            c->goto_label = falseLabel->number;
        }
        break;
    case TreeNode::lor:
        if (tree->left == 0 || tree->right == 0) {
            yyerror("Illegal logical expression");
            return;
        }
        if (trueLabel != 0) {
            genLExpr(tree->left, trueLabel, 0);
            genLExpr(tree->right, trueLabel, 0);
        } else {
            const Label* lab = genLabel();
            genLExpr(tree->left, lab, 0);
            genLExpr(tree->right, 0, falseLabel);
            genNop(lab);
        }
        break;
    case TreeNode::land:
        if (falseLabel != 0) {
            genLExpr(tree->left, 0, falseLabel);
            genLExpr(tree->right, 0, falseLabel);
        } else {
            const Label* lab = genLabel();
            genLExpr(tree->left, 0, lab);
            genLExpr(tree->right, trueLabel, 0);
            genNop(lab);
        }
        break;
    case TreeNode::lnot:
        genLExpr(tree->left, falseLabel, trueLabel);
        break;
    }
}

static void checkNames() {
    NameTable::const_iterator i = name_table.begin();
    while (i != name_table.end()) {
        const NameDef* n = &(*i);
        if ((n->modifiers & NameDef::NAME_FUNCTION) == 0) {
            // n is not a name of function
            if (n->numDefinitions == 0) {
                sprintf(
                    error_text, "Udefined variable %s", 
                    n->name.c_str()
                );
                printError(error_text);
            }
            if (n->numReads == 0) {
                sprintf(
                    error_text, "Unused variable %s", 
                    n->name.c_str()
                );
                printWarning(error_text);
            }
            if (
                n->numWrites == 0 && 
                (n->modifiers & NameDef::NAME_ARRAY) == 0
            ) {
                sprintf(
                    error_text, 
                    "Variable %s was never assigned any value",
                    n->name.c_str()
                );
                printWarning(error_text);
            }
        }
        ++i;
    }
}

static void printWarning(const char *text) {
    fprintf(stderr, "Warning: %s\n", text);
}

static void printError(const char *text) {
    fprintf(stderr, "Error: %s\n", text);
}
