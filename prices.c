#include<stdio.h>
#include<ctype.h>

struct profile
{
	char name[31];
	char pass[31];
}p;

void main()
{
	FILE *ptr = fopen("prices.dat", "rb+");
	
	fread(&p, sizeof(p), 1, ptr);
	
	while(!feof(ptr))
	{
		printf("\n%s\t%s", p.name, p.pass);
		fread(&p, sizeof(p), 1, ptr);
	}
	
}