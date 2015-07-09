#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <pmc.h>
/*#include "pctop.h"*/
#include "sorter.h"

FILE *month_blt;

/* struct shit for username / upload bytes / monthly bytes */
struct Record {
	char User[25];
	unsigned long long Uploadbytes;
	unsigned long long Monthlybytes;
};

typedef struct
{
	char userp[25];
	unsigned long long bytep;
} myStruct;
myStruct DATA;

struct Record pmc[MAXUSERS];
struct int_list *sorted;
unsigned long long tmptop[MAXUSERS];

int i, dog, c;

/* ========================================================================= */
/* =====[ monthly ]========================================================= */
/* ========================================================================= */
int Do_Monthly()
{
	FILE *old_data;

	char OLD_User[MAXUSERS][25];
	unsigned long long OLD_Uploadbytes[MAXUSERS];
	char Monthly_User[MAXUSERS][25];
	unsigned long long Monthly_Uploadbytes[MAXUSERS];
// not used?
// unsigned long long SOMEBYTES=0;
	char tempDBA[80];
	int im = 1, match = 0;
	long dba = 0, max_dba = 0;

	printf("at do monhtly\n");

	old_data = fopen("_month.DBA", "rb");
	if (!old_data)
	{
		printf("error at _month.DBA !\n");
		exit(1);
	}

	while (!feof(old_data))
	{
		dba++;

		fread(&DATA, sizeof(myStruct), 1, old_data);

		strcpy(OLD_User[dba], DATA.userp);
		OLD_Uploadbytes[dba] = 0;
		OLD_Uploadbytes[dba] = DATA.bytep;

/*	printf("userp: %s\n -- bytep: %llu ...\n",DATA.userp,DATA.bytep);*/

/* printf("read %lu num, user: %s, bytes: %llu\n",dba,OLD_User[dba],OLD_Uploadbytes[dba]); */
		if (feof(old_data))
			break;
	}

	max_dba = dba - 1; /* how many users in dba? */
	printf("we have %lu users in max_dba = _month.dba\n", max_dba);
	fclose(old_data);
	printf("Done old data extraction\n");

	dba = 0;

	while (dba < max_dba)
	{
		dba++;

		for (im = 1; im < c; im++)
		{
/*    printf("Comparing: %s to %s\n",pmc[im].User,OLD_User[dba]);    */
			if (strstr(pmc[im].User, OLD_User[dba]))
			{
				pmc[im].Monthlybytes = 0;
				pmc[im].Monthlybytes = (float)(pmc[im].Uploadbytes - OLD_Uploadbytes[dba]);
				match = 1;
				printf("found pmc[].User match: %s montly_uploadbytes: %llu\n", pmc[im].User, pmc[im].Monthlybytes);
			}
			if (match)
			{
				match = 0;
				break;
			}
		}
	}

	month_blt = fopen("_monthly.txt", "wt");
	if (!month_blt)
	{
		printf("error at _monthly.txt!\n");
		exit(1);
	}
	printf("opened _monthly.txt\n");
	fputs("\n umm yeah, monthly\n\n", month_blt);

	/* created monthlybytes sorted list */

	for (i = 0; i < c; i++)
		tmptop[i] = pmc[i].Monthlybytes;

	Writer(2);
	fputs("\n\n\tand then uploadbytes\n\n", month_blt);

	/* created uploadbytes sorted list */

	for (i = 0; i < c; i++)
		tmptop[i] = pmc[i].Uploadbytes;

	Writer(1);

	fclose(month_blt);
	return 0;
}

int Writer(int num)
{
	char buf[1024];
	char tempstr[80];

	sorted = sort_top(tmptop);
	dog = 0;

	while (sorted)
	{
		dog++;

		if (num == 1)
			sprintf(tempstr, "%llu", pmc[sorted->num].Uploadbytes);
		if (num == 2)
			sprintf(tempstr, "%llu", pmc[sorted->num].Monthlybytes);

		strcpy(tempstr, f_format(tempstr));
		sprintf(buf, " %3d  %-24s %20s\n", dog, pmc[sorted->num].User,
		        tempstr);

		fputs(buf, month_blt);
		sorted = sorted->next;
	}

	return 0;
}

void make_some_tops()
{
	FILE *tempf;
	char line[80];
	i = 0;
	printf("at make_some_tops()\n");

	tempf = fopen("data/MYBBS.DAT", "rt");
	if (!tempf)
	{
		printf("error opening tempf!\n");
		exit(1);
	}
	fgets(line, 80, tempf); /* board_id */
	fgets(line, 80, tempf); /* date     */

	while (!feof(tempf))
	{
		i++;
		fgets(line, 80, tempf);
		line[strlen(line) - 1] = '\0'; /* remove the linefeed */
		strcpy(pmc[i].User, line);
/*	printf("read user: %s\n",line); */

		fgets(line, 80, tempf);
		line[strlen(line) - 1] = '\0'; /* remove the linefeed */
		sscanf(line, "%llu", &pmc[i].Uploadbytes);
/*	printf("read bytes: %s\n",line); */
		if (feof(tempf))
			break;
	}
	c = i;
	fclose(tempf);
}

int main()
{
	bzero(&pmc, sizeof(struct Record) * MAXUSERS);

	make_some_tops();

	Do_Monthly();

	return 0;
}
