﻿

static int progress();
static int constinstr();
static int funcdef();
static int constdef(char *name, int *count);
static int enter(char const*name, int type, int kind, int count);
static int funcid(char *name);
static int funcinteger(int *count);
//static int funcchar();
static int funcnum();
//static int declareheader();
static int funcwithreturn(char const*name);
static int varinstr(char *name);
static int mulstatement();
static int statementseq();
//static int parameter();
//static int parametertbl();
static int funcmain();
static int expr();
static int term();
static int factor();
static int funccall(int funcinctbl);
static int ifstatement();
static int whilestatement();
static int assignstatement();
static int returnstatement();
static int readstatement();
static int writestatement();
static int funcif();
//static int valuetbl();

static int lookup(char *name);
static int gen(int op, int lev, int x);
static int pushdir(int x);
static int pushbyaddr(int lev, int x);
static int add();
static int subt();
static int mul();
static int div();
static int sto(int lev, int x);
static int reverse();
static int jmp(int x);
static int jmc(int x);
static int wrt();
static int backout();


