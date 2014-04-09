#include <stdlib.h>
#include "parse analysis/parse.cpp"
int main()
{
	char filepath[100] = "D:\\Assignment\\compiling\\b.c0";
	char ch;
	long lSize = 0;
	int ctl = 1;
	while(ctl)
	{
		lSize = 0;
		ch = 0;
		printf("Please input the directory of the file to compile\n");
		//scanf("%s",filepath);
		FILE *fp = fopen(filepath,"r");
		while(ch != EOF)
		{
			ch=fgetc(fp);
			mystring[lSize] = ch;
			lSize++;
		}
		//scanf("%d", &ctl);
		mystring[lSize] = '\0';
		errorline = 1;
		char_pointed = mystring[0];
		token_p = 0;
		getsym();
		progress();
		for(int i = 0; i < numOfPcode; i++)
			printf("%d\t%s\t%d\t%d\n", i, operation[pcode[i].op], pcode[i].lev, pcode[i].x);
		printf("enter 0 to exit, else to continue.\n");
		scanf("%d", &ctl);
	}
}


