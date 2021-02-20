#include <windows.h>
#include <stdio.h>
#include <string.h>

void get_spaced_string(char *str)
{
	char ch = 0;
	for(int pos = 0; pos < 16; pos++) 
	{
		ch = getchar();

		if (ch == EOF || ch == '\n') 
		{
			str[pos] = '\0';
			break;
		} 
		else 
		{
			str[pos] = ch;
		}
	}
}

int cmd_add();
int cmd_list();
int cmd_exit();

char *builtin_list[] = 
{
	"add",
	"list",
	"exit"
};

int (*builtin_func[]) () = 
{
	&cmd_add,
	&cmd_list,
	&cmd_exit
};

int builtin_count()
{
	return sizeof(builtin_list) / sizeof(char *);
}

int cmd_list()
{
	FILE *file;
	char cmd[2];
	char *about;

	file = fopen("cmd.db", "r");
	if(file == NULL)
	{
		printf("Can't open file.");
		return -1;
	}

	char ch;
	char str[64];
	int n = 0;
	for(; n < 64; n++)
	{
		ch = fgetc(file);
		if(ch == EOF)
			break;
		if(ch == '\n')
			about = str+3;
		str[n] = ch;
		if(ch == ' ')
		{
			cmd[0] = str[n-2];
			cmd[1] = str[n-1];
		}
		printf("%c", ch);
	}
}

int cmd_add()
{
	FILE *file;

	file = fopen("cmd.db", "a");
	if(file == NULL)
	{
		printf("Can't open file.");
		return -1;
	}

	char cmd[16];
	char about[64];
	for(int i = 0; i < 16; i++)
		cmd[i] = '\0';
	printf("db/add>\n\tcmd: ");
	char ch = 0;
	//Читатет перевод строки, который остается не прочитанным после ввода
	//последней команды
	ch = getchar();
	get_spaced_string(cmd);
	printf("\tabout: ");
	get_spaced_string(about);

	printf("%s 0x%x%x\n", cmd, cmd[1], cmd[0]);
	printf("C#:\n\tconst int CMD_%c%c = 0x%x%x;\n",\
		toupper(cmd[0]), toupper(cmd[1]),\
		cmd[1], cmd[0]);
	printf("Define:\n\t#define CMD_%c%c 0x%x%x;\n",\
		toupper(cmd[0]), toupper(cmd[1]),\
		cmd[1], cmd[0]);
	fprintf(file, "%s %s\n", cmd, about);

	fclose(file);
}

int cmd_remove()
{
	
}

int cmd_exit()
{
	printf("exit");
	return 0;
}

int main() {
	char cmd[16];
	
	while(1)
	{
		printf("db>");
		scanf("%s", cmd);

		for(int i = 0; i < builtin_count(); i++)
		{
			if(!strcmp(cmd, builtin_list[i]))
				(*builtin_func[i])();
		}
	}
	return 0;
}