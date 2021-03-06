#include "lexical_analysis.h"
static int getsym()
{
	clearToken();
	if (char_pointed == -1)
	{
		return -1;
	}
	while (isSpace())
	{
		getchar1();
	}
	if(isletter())
	{
		while(isletter() || isnum())
		{
			addToToken();
			getchar1();
		}
		if (isreserver() >= 0)
		{
			symbol = isreserver();
		}
		else
		{
			symbol = 11;
		}
		return 1;
	}
	if(isnum())
	{
		while (isnum())
		{
			addToToken();
			getchar1();
		}
		symbol = 12;
		return 1;
	}
	else if(isLpar())
	{
		symbol = 15;
		getchar1();
		return 1;
	}
	else if(isRpar())
	{
		symbol = 16;
		getchar1();
		return 1;
	}
	else if(islLpar())
	{
		symbol = 17;
		getchar1();
		return 1;
	}
	else if(islRpar())
	{
		symbol = 18;
		getchar1();
		return 1;
	}
	else if(isapos())
	{
		symbol = 19;
		getchar1();
		return 1;
	}
	else if(isquata())
	{
		symbol = 20;
		getchar1();
		return 1;
	}
	else if(issemi())
	{
		symbol = 21;
		getchar1();
		return 1;
	}
	else if(isplus())
	{
		symbol = 22;
		getchar1();
		return 1;
	}
	else if(isminus())
	{
		symbol = 23;
		getchar1();
		return 1;
	}
	else if(ismul())
	{
		symbol = 24;
		getchar1();
		return 1;
	}
	else if(isdivi())
	{
		symbol = 25;
		getchar1();
		return 1;
	}
	else if(iscomma())
	{
		symbol = 26;
		getchar1();
		return 1;
	}
	else if(isassign())
	{
		symbol = 27;
		getchar1();
		return 1;
	}
	else if(iscolon())
	{
		symbol = 28;
		getchar1();
		return 1;
	}
	else if(ismoe())
	{
		symbol = 29;
		getchar1();
		return 1;
	}
	else if(isloe())
	{
		symbol = 30;
		getchar1();
		return 1;
	}
	else if(isequ())
	{
		symbol = 31;
		getchar1();
		return 1;
	}
	else if(isunequ())
	{
		symbol = 32;
		getchar1();
		return 1;
	}
	else
	{
		printf("%d\t%s\n",1,error_msg[0]);
		getchar1();
		while (symbol != 18 && symbol != 21)
		{
			getsym();
		}
		getsym();
	}
	return 0;
}

static void getchar1()
{
	token_p += 1;
	char_pointed = mystring[token_p];
	errorchar++;
}
static void retract()
{
	token_p -= 1;
}
static void clearToken()
{
	memset(token, '\0', MAX_SIZE_OF_TOKEN);
}
static bool isSpace()
{
	
	if (char_pointed == '\t' || char_pointed =='\n' || char_pointed == ' ')
	{
		if(char_pointed == '\n')
		{
			errorline++;
			errorchar = 1;
		}
		return 1;
	}
	else
	{
		return 0;
	}
}
static bool isnum()
{
	if(char_pointed >= '0' && char_pointed<='9')
		return 1;
	else
	{
		return 0;
	}
}
static bool isletter()
{
	if((char_pointed >= 'a' && char_pointed <= 'z') || (char_pointed >= 'A'&& char_pointed<='Z')|| char_pointed == '_')
		return 1;
	else
	{
		return 0;
	}
}
static bool ismore()
{
	if (char_pointed == '>')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
static bool isless()
{
	if (char_pointed == '<')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
static bool isLpar()
{
	if (char_pointed == '(')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
static bool isRpar()
{
	if (char_pointed == ')')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
static bool islLpar()
{
	if (char_pointed == '{')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
static bool islRpar()
{
	if (char_pointed == '}')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
static bool isapos()
{
	if (char_pointed == '\'')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
static bool isquata()
{
	if (char_pointed == '"')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
static bool issemi()
{
	if (char_pointed == ';')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
static bool isplus()
{
	if (char_pointed == '+')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
static bool isminus()
{
	if (char_pointed == '-')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
static bool ismul()
{
	if (char_pointed == '*')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
static bool isdivi()
{
	if (char_pointed == '/')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
static bool iscomma()
{
	if (char_pointed == ',')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
static bool isassign()
{
	if (char_pointed == '=')
	{
		getchar1();
		if (char_pointed != '=')
		{
			return 1;
		}
		retract();
		return 0;
	}
	else
	{
		return 0;
	}
}
static bool iscolon()
{
	if (char_pointed == ':')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
static bool ismoe()
{
	if (ismore())
	{
		getchar1();
		if (char_pointed == '=')
			return 1;
		else
		{
			retract();
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
static bool isloe()
{
	if (isless())
	{
		getchar1();
		if(char_pointed == '=')
			return 1;
		else
		{
			retract();
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
static bool isequ()
{
	if (char_pointed == '=')
	{
		getchar1();
		if(char_pointed == '=')
			return 1;
		else
		{
			retract();
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
static bool isunequ()
{
	if (char_pointed == '!')
	{
		getchar1();
		if(char_pointed == '=')
			return 1;
		else
		{
			retract();
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

static int isreserver()
{
	for (int i = 0; i <= 10; i++)
	{
		if (strcmp(token, reserver_ls[i]) == 0)
		{
			return i;
		}
	}
	return -1;
}

static void addToToken()
{
	int len = strlen(token);
	token[len] = char_pointed;
}