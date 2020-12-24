#include <stdio.h>

//A = 65
//a = 97
//a - A = 32

int main() {
	char let[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
		'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

	FILE *ftable;
	FILE *fdefines;
	ftable = fopen("table.txt", "w");
	fdefines = fopen("defines.h", "w");
	if(ftable == NULL)
		return 1;

	fprintf(ftable, "ch |    x16 |   x10 |\n");
	fprintf(ftable, "---------------------\n");
	for(int x = 0; x < 26; x++)
	{
		for(int y = 0; y < 26; y++)
		{
			printf("%c%c | 0x%x | %d |\n", 
				let[x], let[y], let[x] + (let[y]<<8), let[x] + (let[y]<<8));
			fprintf(ftable, "%c%c | 0x%x | %d |\n", 
				let[x], let[y], let[x] + (let[y]<<8), let[x] + (let[y]<<8));
			fprintf(fdefines, "#define CMD_%c%c 0x%x\n", 
				let[x] - 32, let[y] - 32, let[x] + (let[y]<<8));
		}
	}
	fclose(ftable);
	fclose(fdefines);

	return 0;
}