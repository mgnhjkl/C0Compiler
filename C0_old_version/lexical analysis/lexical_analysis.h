#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE_OF_STRING 10000
#define MAX_SIZE_OF_CHARACTERTABLE 1000
#define MAX_SIZE_OF_TOKEN 100
#define MAX_SIZE_OF_LEVEL 20
#define MAX_SIZE_OF_PCODE 1000
#define MAX_SIZE_OF_ERROR 100
/*********  lexical analysis *********




*************************************/
struct Charactertable
{
	char name[MAX_SIZE_OF_TOKEN];
	int lev, kind, addr, type;
	int num;
};
/******type**********
1 	int 	
2 	void
*******kind**********
0	para
1 	const
2 	var
3 	funcwithreturn
4	funcvoid
*/
static struct Charactertable ctbl[MAX_SIZE_OF_CHARACTERTABLE];
static int numOfCtbl;
static int numOfVarInLev[MAX_SIZE_OF_LEVEL];
struct oper
{
	int op;
	int lev;
	int x; 
};
static struct oper pcode[MAX_SIZE_OF_PCODE];
//static op 
static int numOfPcode;
static char mystring[MAX_SIZE_OF_STRING];
static char token[MAX_SIZE_OF_TOKEN];      //string to store words 
static char char_pointed;
//char *token_p = mystring + 1;		 //pointer of the whole string
static int lev;
static int token_p;
static int num;			 //int to store target intager
static int symbol;
static int errorline;
static int errorchar;
static int errorflag;
static const char *reserver_ls[] = {
	"main",		//0
	"const",	//1
	"int", 		//2
	"char", 	//3
	"void", 	//4
	"if", 		//5
	"else", 	//6
	"while", 	//7
	"scanf", 	//8
	"printf", 	//9
	"return"	//10
};
//	1 	)
//	2 	}
//	3 	;
//	4 	,
static const char *operation[] = {
	"LIT",		// 0
	"OPR",		// 1
	"LOD",		// 2
	"STO",		// 3
	"CAL",		// 4
	"INT",		// 5
	"JMP",		// 6
	"JPC",		// 7
	"RED",		// 8
	"WRT"		// 9
};
static const char *error_msg[] = {
	"invalid symbol",				//0
	"lacking semicolon",			//1
	"invalid identifier",			//2
	"invalid declaration",			//3
	"lacking const",				//4
	"lacking identifier",			//5
	"lacking '='",					//6
	"lacking integer",				//7
	"double decleration",			//8
	"character table overflow",		//9
	"lacking '('",					//10
	"lacking 'int'",				//11
	"lacking ')'",					//12
	"lacing '{'",					//13
	"lacking '}'",					//14
	"invalid factor",				//15
	"wrong kind identifier",		//16
	"undeclared identifier",		//17
	"wrong number of parameters",	//18
	"invalid judgement",			//19
	"lacking statement",			//20
	"lacking ','",					//21
	"pcode overflow"				//22
};
static void getchar1();
static void clearToken();
static bool isSpace();			//if the char is space or tab or newline
static bool isnum();
static bool isletter();
static bool isdot();
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
static bool	isminus();
static bool ismul();
static bool isdivi();
static bool	iscomma();
static bool isassign();
static bool iscolon();
static bool ismoe();
static bool isloe();
static bool isequ();
static bool isunequ();
static int isreserver();			//if token is a reserver, return the index, if not, return 0;
static void addToToken();		//add the char to token which token_p is pointing to
static void retract();			//token_p - 1;
static int getsym();
static void error(int msg_id, int cx);