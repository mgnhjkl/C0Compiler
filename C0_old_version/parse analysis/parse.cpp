#include "parse.h"
#include "../lexical analysis/lexical_analysis.cpp"



static int progress()
{
	numOfPcode = 0;
	numOfCtbl = 0;
	numOfVarInLev[0] = 0;
	char name[MAX_SIZE_OF_TOKEN];
	gen(6, 0, 0);
	if(symbol == 1)
	{
		constinstr();
	}
	label :
	if (symbol == 2)
	{
		getsym();
		if (symbol == 11)
		{
			strcpy(name, token);
			getsym();
			if (symbol == 15)
			{
				if(!funcwithreturn(name))
					goto label;
				else 
					return 0;
			}
			else
			{
				varinstr(name);
				goto label;
			}
		}
		else if(symbol == 0)
		{
			pcode[0].x = numOfPcode;

			funcwithreturn("main");
			return 1;
		}	
		else 
		{
			error(3, 0);
			return 0;
		}
	}
	else
	{
		if(symbol == 4)
		{
			getsym();
			strcpy(name, token);
			if(symbol == 11)
			{
				getsym();
				if(symbol == 15)
				{
					error(10, 5);
				}
				else
				{
					getsym();
				}
				funcwithreturn(name);
				goto label;
			}
			else if(symbol == 0)
			{
				pcode[0].x = numOfPcode;
				funcwithreturn("main");
				return 1;
			}
			else 
			{
				error(2, 0);
				goto label;
			}
		}
		else 
		{
			error(3 ,0);
			return 0;
		}
	}
	return 0;
}

static int constinstr()
{
	int c;
	char n[MAX_SIZE_OF_TOKEN];
	getsym();
	if (symbol != 11)
	{
		error(5, 3);
		return 0;
	}
	if(!constdef(n, &c))
	{
		return 0;
	}
	enter(n, 1, 1, c);
	while (symbol == 26)
	{
		getsym();
		if(!constdef(n, &c))
			return 0;
		enter(n, 1, 1, c);
	}
	if(symbol != 21)
	{
		error(1, 5);
	}
	else
		getsym();
	return 1;
}


static int constdef(char *name, int *count)
{
	strcpy(name, token);
	getsym();
	if (symbol != 27)
	{
		error(6, 5);
	}
	else
		getsym();
	if(!funcinteger(count))
		return 0;
	return 1;
}

static int funcinteger(int *const count)
{
	bool op = 1;
	if (symbol == 22 || symbol == 23)
	{
		if(symbol == 23) op = 0;
		getsym();
	}
	if (symbol != 12)
	{
		error(7, 0);
		return 0;
	}
	if(op == 0)
	{
		*count = - atoi(token);
	}
	else
		*count = atoi(token);
	getsym();
	return 1;
}

static int funcid(char *name)
{
	if (symbol != 11)
	{
		error(5, 0);
		return 0;
	}
	strcpy(name, token);
	getsym();
	return 1;
}
static int varinstr(char *name)
{
	enter(name, 1, 2, 0);
	char name2[MAX_SIZE_OF_TOKEN];
	while (symbol == 26)
	{
		getsym();
		if(!funcid(name2))
			return 0;
		enter(name2, 1, 2, 0);
	}
	if (symbol != 21)
	{
		error(1, 5);
	}
	else
		getsym();
	return 1;
}


/*
static int funcdef()
{
	if (symbol == 4)
	{
		getsym();
		//funcid();
	}
	else declareheader();
	parameter();
	mulstatement();
	return 1;
}
*/
/***************************************************************************
＜函数定义部分＞ ::=  （＜声明头部＞｜void ＜标识符＞）＜参数＞＜复合语句＞
＜复合语句＞ ::=  ‘{’〔＜常量说明部分＞〕〔＜变量说明部分＞〕＜语句序列＞‘}’
＜参数＞ ::=  ‘(’＜参数表＞‘)’
＜参数表＞ ::=  int ＜标识符＞｛，int ＜标识符＞} | 空
                  //参数表可以为空
****************************************************************************/
static int funcwithreturn(char const*name)
{

	int countOfParameter = 0, label1 = numOfCtbl;
	if(!enter(name, 1, 3, 0))
	{
		return 0;
	}
	ctbl[numOfCtbl - 1].addr = numOfPcode;
	if (strcmp(name, "main") == 0)
	{
		//ctbl[numOfCtbl - 1].addr = numOfPcode;
		getsym();
	}
	if (symbol != 15)
	{
		error(10, 2);
		return 0;
	} 
	getsym();
	/****************parameter*****************/
	lev = lev + 1;
	while(symbol == 2)
	{
		getsym();
		if(symbol != 11)
		{
			error(5, 2);
			continue;
		}
		if(enter(token, 1, 0, 0))
		{
			countOfParameter = countOfParameter + 1;
			getsym();
		}
		else
		{
			return 0;
		}
		if (symbol != 26)
		{
			break;
		}
		getsym();
		if (symbol != 2)
		{
			error(11, 2);
			return 0;
		}
	}
	lev = lev - 1;
	ctbl[label1].num = countOfParameter;
	if (symbol != 16)
	{
		error(12, 5);
	}
	else
	getsym();
	/****************body of function************/
	if (symbol != 17)
	{
		error(13, 5);
	}
	else
	getsym();
	lev = lev + 1;
	if (symbol == 1)
	{
		constinstr();
	}
	if (symbol == 2)
	{
		char name[MAX_SIZE_OF_TOKEN];
		getsym();
		if (symbol != 11)
		{
			error(5, 2);
			return 0;
		}
		strcpy(name, token);
		getsym();
		/************var declaration************/
		if (symbol == 26 || symbol == 21)
		{
			if(!varinstr(name))
				return 0;
		}
		else
		{
			error(1, 5);
		}
	}
	//allocate addresses for vars and parameters
	gen(5, 0, numOfVarInLev[lev]);
	//store 
	for (int i = 0; i < countOfParameter; i++)
	{
		sto(lev, i);
	}
	statementseq();
	//end of function
	if(symbol != 18)
	{
		error(14, 5);
	}
	else
	getsym();
	backout();
	lev = lev - 1;
	gen(1, 0, 0);
	return 1;
}
/*
static int mulstatement()
{
	if (symbol != 17)
	{
		error(13, 5);
		return 0;
	}
	lev = lev + 1;
	if (symbol == 1)
	{
		constinstr();
	}
	if (symbol == 2)
	{
		char name[MAX_SIZE_OF_TOKEN];
		getsym();
		if (symbol != 11)
		{
			error();
			return 0;
		}
		strcpy(name, token);
		getsym();
		if (symbol == 21 || symbol == 26)
		{
			varinstr(name);
		}
		
	}
	statementseq();
	if (symbol != 18)
	{
		error();
		return 0;
	}
	lev = lev - 1;
	getsym();
	return 1;
}
*/
/*
static int parameter()
{
	if (symbol != 15)
	{
		error();
		return 0;
		

	}
	getsym();
	/*if (symbol == 16)	//when parametertbl is empty
	{
		getsym();
		return 1;
	}
*/		
/*	parametertbl();
	if (symbol != 16)
	{
		error();
		return 0;
	}
	getsym();
	return 1;
}

static int parametertbl()
{
	if (symbol != 2)
	{
		return 1;		//when parametertbl is empty

	}
	getsym();
	if (symbol != 11)
	{
		error();
		return 0;
		
	}
	getsym();
	while (symbol == 26)
	{
		getsym();
		if (symbol != 11)
		{
			error();
			return 0;
		}
		getsym();
	}
	return 1;
}
*/
/*******************************************************
＜主函数＞ ::=  ( void ｜int ) main ＜参数＞＜复合语句＞
*******************************************************/
/*static int funcmain(int x)
{

	if(symbol != 15)
	{
		error();
		return 0;
	}

}
/*******************************************************
＜表达式＞ ::=  〔＋｜－〕＜项＞｛＜加法运算符＞＜项＞@addorsubt｝
＜项＞ ::=  ＜因子＞{＜乘法运算符＞＜因子＞@mulordiv}
＜因子＞ ::=  ＜标识符＞@lookup@pushbyaddr｜‘（’＜表达式＞‘）’｜＜整数＞@pushdir｜＜函数调用语句＞
**********************************************************/
static int expr()
{
	bool ifreverse = 0;
	if(symbol == 22 )
	{
		getsym();
	}
	else if(symbol == 23)
	{
		ifreverse = 1;
		getsym();
	}
	if(!term())
		return 0;
	while (symbol == 22 || symbol == 23)
	{
		int sym = symbol;
		getsym();
		if(!term())
			return 0;
		if(sym == 22)
			add();
		if(sym == 23)
			subt();
	}
	if (ifreverse)
	{
		reverse();
	}
	return 1;
}

static int term()
{
	if(!factor())
		return 0;
	while (symbol == 24 || symbol == 25)
	{
		int sym = symbol;
		getsym();
		if(!factor())
		{
			return 0;
		}
		if (sym == 24)
			mul();
		if (sym == 25)
			div();
	}
	return 1;
}

static int factor()
{
	int count, id;
	if (symbol == 11)
	{
		id = lookup(token);
		if(id >= 0)
		{
			if(ctbl[id].kind == 1)
			{
				pushdir(ctbl[id].num);
				getsym();
				return 1;
			}
			else if(ctbl[id].kind == 2 || ctbl[id].kind == 0)
			{	
				pushbyaddr(ctbl[id].lev, ctbl[id].addr);
				getsym();
				return 1;
			}
			else if(ctbl[id].kind == 3)
			{
				getsym();
				funccall(id);
				if(symbol != 21)
				{
					error(1, 5);	//lacking ;
				}
				else
					getsym();
			}
			else
			{
				error(16, 0);	//wrong kind
				return 0;
			}
			getsym();
			return 1;
		}
		else
		{
			error(17, 0);
			return 0;
		}
	}
	else if (symbol == 15)
	{
		getsym();
		if(!expr())
			return 0;
		if (symbol != 16)
		{
			error(12, 5);
		}
		else
			getsym();
		return 1;
	}
	else if (symbol == 12)
	{
		if(!funcinteger(&count))
			return 0;
		pushdir(count);
		return 1;
	}
	else
	{
		error(15, 0);
		return 0;
	}
	/*
	else 
	{
		funccall();
		if(symbol != 21)
		{
			error();
			return 0;
		}
		getsym();
	}
	*/
	return 1;
}



/***************************************************
＜函数调用语句＞ ::=  ＜标识符＞‘（’＜值参数表＞‘）’
***************************************************/
static int funccall(int funcinctbl)
{
	int paracount = 0;
	oper optmp;
	if(symbol != 15)
	{
		error(10, 5);
	}
	else
		getsym();
	//push the values of vars and prarameters to the stack
	for(int i = 1; i <= ctbl[funcinctbl].num; i++)
	{
		if(symbol != 11)
		{
			error(5, 0);
			return 0;
		}
		if(!expr())
		{
			return 0;
		}
		paracount = paracount + 1;
		if(symbol == 26)
		{
			getsym();
			continue;
		}
	}
	if (paracount != ctbl[funcinctbl].num)
	{
		error(18, 0);	//lack parameter;
		return 0;
	}
	for(int i = 1;i <= ctbl[funcinctbl].num/2; i++)
	{
		optmp = pcode[numOfPcode - i];
		pcode[numOfPcode - i] = pcode[numOfPcode - ctbl[funcinctbl].num -1 + i];
		pcode[numOfPcode - ctbl[funcinctbl].num -1 + i] = optmp;
	}
	
	if (symbol != 16)
	{
		error(12, 5);
	}
	else
		getsym();
	//call funcinctbl.lev funcinctbl.x
	gen(4, ctbl[funcinctbl].lev, ctbl[funcinctbl].addr);
	return 1;
}


/*********************************************************************************
＜语句＞::=& nbsp; ＜条件语句＞｜＜循环语句＞｜‘{’<语句序列>‘}’｜＜函数调用语句＞;
｜＜赋值语句＞; | <返回语句>;｜＜读语句＞;｜＜写语句＞;｜＜空＞
*********************************************************************************/
static int statement()
{
	if (symbol == 5)
	{
		getsym();
		ifstatement();
		return 1;
	}
	else if (symbol == 7)
	{
		getsym();
		whilestatement();
		return 1;
	}
	else if (symbol == 17)
	{
		lev = lev + 1;
		getsym();
		statementseq();
		if (symbol != 18)
		{
			error(14, 5);
		}
		else
			getsym();
		lev = lev - 1;
		return 1;
	}
	else if (symbol == 10)
	{
		getsym();
		returnstatement();
		if (symbol != 21)
		{
			error(1, 5);
		}
		else
			getsym();
		return 1;
	}
	else if (symbol == 8)
	{
		getsym();
		readstatement();
		if (symbol != 21)
		{
			error(1, 5);
		}
		else
			getsym();
		return 1;
	}
	else if (symbol == 9)
	{
		getsym();
		writestatement();
		if (symbol != 21)
		{
			error(1, 5);
		}
		else
			getsym();
		return 1;
	}
	else if (symbol == 11)
	{
		int id = lookup(token);
		if (id == -1)
		{
			error(17, 0);	//undeclared identifier
			return 0;
		}
		/**************assignstatement**********/
		if (ctbl[id].kind == 2 || ctbl[id].kind == 0)
		{
			getsym();
			if (symbol == 27)
			{
				getsym();
				if(!expr())
					return 0;
				sto(ctbl[id].lev, ctbl[id].addr);
				if (symbol != 21)
				{
					error(1, 5);
				}
				else
					getsym();
				return 1;
			}
		}
		/**************funccall**************/
		if (ctbl[id].kind == 3)
		{
			getsym();
			if(!funccall(id))
				return 0;
			//getsym();
			if (symbol != 21)
			{
				error(1, 5);
			}
			else 
				getsym();
			return 1;
		}
		/*
		else if (symbol == 15)
		{
			getsym();
			valuetbl();
			if (symbol != 16)
			{
				error();
				return 0;
				
			}
			getsym();
			return 1;
		}
		*/
	}
	else if (symbol == 21)
		getsym();
	return 1;
}

static int ifstatement()
{
	int oplab1, oplab2;
	if (symbol != 15)
	{
		error(10, 5);
	}
		getsym();
	if(!funcif())
		return 0;
	oplab1 = numOfPcode;
	jmc(0);						//set op.x = 0, but will fill in x after statement
	if (symbol != 16)
	{
		error(12, 5);
	}
	else
		getsym();
	if(!statement())
		return 0;
	if (symbol == 6)			//else statement
	{
		oplab2 = numOfPcode;
		jmp(0);					//same as above
		pcode[oplab1].x = numOfPcode;
		getsym();
		if(!statement())
			return 0;
		pcode[oplab2].x = numOfPcode;
	}
	else pcode[oplab1].x = numOfPcode;
	return 1;
}

static int funcif()
{
	int cmpsym;
	if(!expr())
	{
		error(2, 19);
		return 0;
	}
	cmpsym = symbol;
	if (symbol == 13 || symbol == 14 || (symbol >= 29 && symbol <=32))
	{
		getsym();
		if(!expr())
		{
			error(2, 19);
			return 0;
		}
		if(cmpsym == 13)
		{
			gen(1, 0, 10);
		}
		if(cmpsym == 14)
		{
			gen(1, 0, 12);
		}
		if(cmpsym == 29)
		{
			gen(1, 0, 11);
		}
		if(cmpsym == 30)
		{
			gen(1, 0, 13);
		}
		if(cmpsym == 31)
		{
			gen(1, 0, 8);
		}
		if(cmpsym == 32)
		{
			gen(1, 0, 9);
		}
	}
	else
	{
		pushdir(0);
		gen(1, 0, 8);
	}
	return 1;
}

/*************************************************
＜循环语句＞ ::=  while‘（’＜条件＞‘）’＜语句＞
*************************************************/
static int whilestatement()
{
	int oplab1, oplab2;
	if (symbol != 15)
	{
		error(1, 5);
	}
	else
		getsym();
	oplab1 = numOfPcode;
	if(!funcif())
		return 0;
	oplab2 = numOfPcode;
	jmc(0);
	if (symbol != 16)
	{
		error(12, 5);
	}
	else
		getsym();
	statement();
	jmp(oplab1);
	pcode[oplab2].x = numOfPcode;
	return 1;
}
/*
static int valuetbl()
{
	if (symbol == 16)
	{
		return 1;		//when valuetbl is empty
	}
	expr();
	while (symbol == 26)
	{
		getsym();
		expr();
	}
	return 1;
}
*/
static int statementseq()
{
	if (symbol == 5 || symbol == 7 || symbol == 17 || symbol == 11 || symbol == 10 || symbol == 8 || symbol == 9 || symbol == 21)
	{
		statement(); 
	}
	else 
	{
		error(20, 2);
		return 0;
	}
	while (symbol == 5 || symbol == 7 || symbol == 17 || symbol == 11 || symbol == 10 || symbol == 8 || symbol == 9 || symbol == 21)
	{
		statement();
	}		
	return 1;
}
/****************************************
＜读语句＞ ::=  scanf‘(’＜标识符＞‘）’
****************************************/
static int readstatement()
{
	int id;
	if (symbol != 15)
	{
		error(10, 5);
	}
	else
		getsym();
	if (symbol != 11)
	{
		error(5, 5);
	}
	else
	{
		id = lookup(token);
		getsym();
	}
	if(id == -1)
	{
		error(17, 0);			//undeclared identifier
		return 0;
	}
	else
	{
		gen(8, ctbl[id].lev, ctbl[id].addr);	//RED id.lev id.x
	}
	if (symbol != 16)
	{
		error(12, 5);
	}
	else
		getsym();
	return 1;
}
/*
static int writestatement()
{
	if (symbol == 9)
	{
		getsym();
	}
	else
	{
		error();
		return 0;
	}
	if (symbol == 15)
	{
		getsym();
	}
	else
	{
		error();
		return 0;
	}
	if (symbol == 50)
	{
		getsym();
		if (symbol == 26)
		{
			getsym();
			expr();
		}
		if (symbol == 16)
		{
			getsym();
			return 1;
		}
		else
		{
			error();
			return 0;
		}
	}
	else if (symbol == 16)
	{
		getsym();
		return 1;
	}
	else
	{
		expr();
		if (symbol == 16)
		{
			getsym();
			return 1;
		}
		else
		{
			error();
			return 0;
		}
	}
}
*/
/*************************************************************
＜写语句＞ ::=  printf‘(’[<字符串>,][＜expression ＞]‘）’
　　　　　 //当出现字符串时，就加印字符串, 之后打印表达式的值；
**************************************************************/
static int writestatement()
{

	if(symbol != 15)
	{
		error(10, 5);
	}
	else
		getsym();
	if (symbol == 20)
	{
		while (mystring[token_p] != '"')
		{
			pushdir((int)mystring[token_p]);
			wrt();
			getchar1();
		}
		getsym();
		getsym();
		if (symbol != 26)
		{
			error(21, 5);
		}
		else
			getsym();
		if(!expr())
			return 0;
		wrt();
	}
	else if(symbol == 16)
	{
		return 1;
	}
	else
	{
		if(!expr())
			return 0;
		wrt();
	}
	if (symbol != 16)
	{
		error(12, 5);
	}
	else
		getsym();
	return 1;
}

static int returnstatement()
{
	if(symbol == 21)
	{
		getsym();
		gen(1, 0, 0);
		return 1;
	}
	if (symbol != 15)
	{
		error(10, 5);
	}
	else
		getsym();
	if(!expr())
		return 0;
	if (symbol != 16)
	{
		error(12, 5);
	}
	else
	{
		gen(0, 0, 0);		//load a 0 on the top of the stack to reserve return, because OPR 0 0 will pop the top of the stack
		gen(1, 0, 0);		//OPR 0 0
		getsym();
	}
	return 1;
}


int gen(int op,int lev,int x)		
{
	if(numOfPcode<MAX_SIZE_OF_PCODE)
	{
		pcode[numOfPcode].op = op;
		pcode[numOfPcode].lev = lev;
		pcode[numOfPcode].x = x;
		numOfPcode = numOfPcode + 1;
	}
	else
	{
		error(22, 5);
		return 0;
	}
	return 1;
}

//generate a LIT Pcode 
//@pushdir
static int pushdir(int x)
{
	gen(0, 0, x);
	return 1;
}

//generate a LOD Pcode
//@pushbyaddr
static int pushbyaddr(int lev, int x)
{
	gen(2, lev, x);
	return 1;
}

//generate an add Pcode
//@add
static int add()
{
	gen(1, 0, 2);
	return 1;
} 

//generate a subtract Pcode
//@subt
static int subt()
{
	gen(1, 0, 3);
	return 1;
}

//generate a mutiply Pcode
//@mul
static int mul()
{
	gen(1, 0, 4);
	return 1;
}

//generate a division Pcode
//@div
static int div()
{
	gen(1, 0, 5);
	return 1;
}

//generate an OPR Pcode to reverse the item on the top of the stack
//@reverse
static int reverse()
{
	gen(1, 0, 1);
	return 1;
}

//generate an STO Pcode to strore a var
//@sto
static int sto(int lev, int x)
{
	gen(3, lev, x);
	return 1;
}

static int jmp(int x)
{
	gen(6, 0, x);
	return 1;
}

static int jmc(int x)
{
	gen(7, 0, x);
	return 1;
}

static int wrt()
{
	gen(9, 0, 0);
	return 1;
}
//pop useless item from character table
//@backout
static int backout()
{
	int i;
	for(i = numOfCtbl - 1; i >= 0; i--)
	{
		if(ctbl[i].kind == 0 || ctbl[i].kind == 3 || ctbl[i].kind == 4)
			break;
		numOfCtbl = numOfCtbl - 1;
	}
	numOfVarInLev[lev] = 0;
	return 1;
}

//return the number of identifier in character table
//@lookup
static int lookup(char *name)
{
	int i;
	int j = lev;
	for(; j >= 0 ; j--)
	{
		for (i = numOfCtbl - 1; i >= 0; i--)
		{
			if(ctbl[i].lev < j)
				break;
			if(strcmp(ctbl[i].name, name) == 0 && ctbl[i].lev == j)
				return i;
		}
	}
	return -1;
}

//@insert by name, type, kind, and count
static int enter(char const*name, int type, int kind, int count)
{
	int i;
	if(numOfCtbl >= MAX_SIZE_OF_CHARACTERTABLE)
	{
		error(9, 0);
		return 0;
	}
	for(i = numOfCtbl - 1; i >= 0; i--)
	{
		if(ctbl[i].lev < lev)
				break;
		if(ctbl[i].lev == lev && !strcmp(name, ctbl[i].name))
		{
			error(8, 0);
			return 0;
		}
	}
	strcpy(ctbl[numOfCtbl].name, name);
	ctbl[numOfCtbl].lev = lev;
	ctbl[numOfCtbl].type = type;
	ctbl[numOfCtbl].kind = kind;
	if(kind == 1)						//const
	{
		ctbl[numOfCtbl].num = count;
		ctbl[numOfCtbl].addr = numOfPcode;
	}
	if(kind == 0 || kind == 2)						//var and parameter
	{
		numOfVarInLev[lev] = numOfVarInLev[lev] + 1;
		ctbl[numOfCtbl].addr = numOfVarInLev[lev];
	}
	if(kind == 3)
	{
		ctbl[numOfCtbl].addr = numOfPcode;
		ctbl[numOfCtbl].num = count;
	}
	numOfCtbl = numOfCtbl + 1;
	return 1;
}

static void error(int msg_id, int cx)
{
	printf("In line %d:%d\terror:%s\n", errorline, errorchar, error_msg[msg_id]);
	/*while (symbol != 16 ||symbol != 18|| symbol != 21 || symbol != 26)
	{
		getsym();
	}*/
	if (cx == 0)
	{
		while (symbol != 18 && symbol != 21)
		{
			getsym();
		}
		getsym();
	}
	else if(cx == 1)
	{
		while (symbol != 16)
		{
			getsym();
		}
	}
	else if(cx == 2)
	{
		while (symbol != 18)
		{
			getsym();
		}
	}
	else if (cx == 3)
	{
		while (symbol != 21)
		{
			getsym();
		}
	}
	else if (cx == 4)
	{
		while (symbol != 26 )
		{
			getsym();
		}
		getsym();
	}

}