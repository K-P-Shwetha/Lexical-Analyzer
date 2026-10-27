#include"main.h"
#include"token.h"
char *key[] =
{
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

int number_flag;
int main(int argc, char *argv[])
{
	struct files file;
	if(argc < 2)
	{
		printf("Not enough files are sent\n");
		return ;
	}
	int ret=check_arg(argv,&file);
	if(ret == FALSE)
	{
		printf("File passed error\n");
		return -1;
	}
	else
		printf("Files passed\n");
	ret = token(&file);
}

int check_arg( char *argv[] , struct files *file )
{
	if(strstr(argv[1],".c") != NULL)
		file->input=argv[1];
	else
		return FALSE;
	printf("Arg checked\n");
	return TRUE;
}

int token(struct files *file)
{
	int ret=open_files(file);
	if(ret == FALSE)
	{
		printf("File open failed\n");
		return 0;
	}
	int ch=fgetc(file->f_in);
	while(ch != EOF)
	{
		switch(ch)
		{
			case '0' ... '9' :write_num(ch,file);
			     		  break;
			case 'a' ... 'z' :
			case 'A' ... 'Z' :
			case '_' :
					  is_identifier(ch,file);
					  break;
			default: write_spec_char(ch,file);
   				 break;
		}
	ch=fgetc(file->f_in);
	}
}

void is_identifier(int ch,struct files *file)
{
	char byte[50];int i=0;
	int ch1;int found=0;
	byte[i++]=ch;
	ch1=fgetc(file->f_in);
	while((ch1>='a' && ch1<='z') || (ch1>='A' && ch1<='Z') || (ch1>='0' && ch1<='9') || ch1=='_')
	{
		byte[i++]=ch1;
		ch1=fgetc(file->f_in);
	}
	ungetc(ch1,file->f_in);
	byte[i]=0;
	i=0;
	while(i!=32)
	{
		if(!strcmp(byte,key[i]))
		{
			write_key(byte,file);
			found=1;
			break;
		}	
		i++;
	}
	if(found == 0)
	{
		write_non_key(byte,file);
	}
}

int open_files(struct files *file)
{
	file->f_in=fopen(file->input,"r");
	if(file->f_in == NULL)
		return FALSE;
	printf("File opened\n");
}
