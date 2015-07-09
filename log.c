#include <stdio.h>

typedef struct
{
	char userp[25];
	unsigned long long bytep;
} myStruct;
myStruct DATA;

void read_datas()
{
	FILE *DATT;
	int i = 0;

	DATT = fopen("_month.DBA", "rb");
	if (!DATT)
	{
		printf("error at _month.DBA file!\n");
		exit(1);
	}

	printf("\n\tHere you go sir, contents of _month.DBA:\n\n");

	while (!feof(DATT))
	{
		i++;
		fread(&DATA, sizeof(myStruct), 1, DATT);
		if (feof(DATT))
			break;
		printf("record: %3i, user: %20s  bytes: %15llu\n",
		       i, DATA.userp, DATA.bytep);
	}

	fclose(DATT);
}

int main()
{
	read_datas();
	return 0;
}