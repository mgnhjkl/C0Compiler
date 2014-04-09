#ifndef LEXICAL_ANALYSIS_H
#define LEXICAL_ANALYSIS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE_OF_STRING 10000
#define MAX_SIZE_OF_CHARACTERTABLE 1000
#define MAX_SIZE_OF_TOKEN 100
#define MAX_SIZE_OF_LEVEL 3
#define MAX_SIZE_OF_PCODE 1000
#define	MAX_SIZE_OF_ERROR 100

struct Charactertable
{
	char name[MAX_SIZE_OF_TOKEN];
	int lev, kind, addr, type;
	int num;
};

static struct Charactertable ctbl[MAX_SIZE_OF_CHARACTERTABLE];
static int numOfCtbl;
static int numOfVarInLev[MAX_SIZE_OF_CHARACTERTABLE];
struct oper
{
	int op;
	int lev;
	int x;
};
static struct oper pcode[MAX_SIZE_OF_PCODE];
static int numOfPcode;
static char mystring[MAX_SIZE_OF_STRING];
static char token[MAX_SIZE_OF_TOKEN];
static char char_pointed;
static int lev;
static int token_p;
static int num;
static int symbol;
static int errorline;
static int errorchar;
static int errorflag;
static const char *reserver_ls[] = {
	"main",
	"const",
	"int",
	"char",
	"void",
	"if",
	"else",
	"while",
	"scanf",
	"printf",
	"return",
};
static const char *operation[] = {
	"LIT",
	"OPR",
	"LOD",
	"STO",
	"CAL",
	"INT",
	"JMP",
	"JPC",
	"RED",
	"WRT"
};
static const char *error_msg[] = {
	"invalid symbol",
	"lacking semicolon",
	"invalid identifier",
	"invalid declaration",
	"lacking const",
	"lacking identifier",
	"lacking '='",
	"lacking integer",
	"multiple decleration",
	"character table overflow",
	"lacking '('",
	"lacking 'int'",
	"lacking ')'",
	"lacking '{'",
	"lacking '}'",
	"invalid factor",
	"wrong kind identifier",
	"undeclared identifier",
	"wrong number of parameters",
	"invalid judgement",
	"lacking statement",
	"lacking ','",
	"pcode overflow"
};
static void getchar1();
static void clearToken();
static bool isSpace();
static bool isnum();
static bool isletter();
static bool ismore();
static bool isless();
static bool isLpar();
static bool isRpar();
static bool islLpar();
static bool islRpar();
static bool isapos();
static bool isquata();
static bool issemi();
static bool isplus();
static bool isminus();
static bool ismul();
static bool isdivi();
static bool iscomma();
static bool isassign();
static bool iscolon();
static bool ismoe();
static bool isloe();
static bool isequ();
static bool isunequ();
static int isreserver();
static void addToToken();
static void retract();
static int getsym();
static void error(int msg_id, int cx);
#endif