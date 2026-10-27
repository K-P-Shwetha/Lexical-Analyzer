
#include"token.h"

extern char *key[];

char *operators[] =
{
    "++", "--","==", "!=", ">=", "<=","&&", "||","+=", "-=", "*=", "/=", "%=","<<", ">>","+", "-", "*", "/", "%","=", "<", ">", "!","&", "|", "^", "~",NULL
};
char *special[] =
{
    "(",")","{","}","[","]",";",",",":","?",".",NULL
};
void write_key(char *word,struct files *file)
{
	printf("Keyword : %s\n",word);
}

void write_non_key(char *word,struct files *file)
{
	printf("Identifier : %s\n",word);
}

void write_num(int ch, struct files *file)
{
    printf("Constant : ");

    while ((ch >= '0' && ch <= '9') && ch !='e' && ch!='f' && ch!='.' && ch!='o' && ch!='x'  )
    {
        printf("%c",ch);
        ch = fgetc(file->f_in);
    }
	ungetc(ch,file->f_in);
    printf("\n");

}

void write_string(int byte, struct files *file)
{
	printf("Constant : %c",byte);
	int ch;
	while((ch=fgetc(file->f_in)) != '"')
	{
		printf("%c",ch);	
	}
	printf("%c\n",ch);
}

void write_char(int byte,struct files *file)
{
	printf("Constant : ");
	int ch;
	while((ch=fgetc(file->f_in)) != '\'')
	{
		printf("%c",ch);
	}
	printf("%c\n",ch);
}

void write_spec_char(int ch, struct files *file)
{
	char arr[3];int i=0,op_flag=0;
	arr[0]=ch;
	if( ch == '"')
		write_string(ch,file);
	else if(ch == '\'')
	{
		write_char(ch,file);
	}
	else
	{
	/*	arr[1]=fgetc(file->f_in);
		arr[2]=0;
		while(operators[1]!=NULL)
		{
			if(!strcmp(arr,operators[i]))
			{
				printf("Operator : %s\n",arr);
				break;
			}
			else if( arr[0]==operators[i])
			{
				printf("Operator : %c\n",arr[0]);
				op_flag =1;
				break;
			}
		}
		if(op_flag == 1)
			ungetc(arr[1],file->f_in);*/
	printf("Special : %c\n",ch);
	}
}
