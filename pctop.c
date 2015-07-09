/*

        PC-TOP (c) Snake Man 1993-2015.
   linux version with html support is wicked.

 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include <pmc.h>
#include "pctop.h"
#include "sorter.h"

struct Record pmc[MAXUSERS];
struct int_list *sorted;
unsigned long long tmptop[MAXUSERS];

/* ========================================================================= */
/* =====[ read the configuration file ]===================================== */
/* ========================================================================= */
int Read_Config_File()
{
	FILE *cfg_file;
	FILE *pcgroup_file;
	char Groupsfile[80];
	int gu = 0;
	int gn = 0;

	cfg_file = fopen("pctop.cfg", "rt");
	if (!cfg_file)
	{
		printf("error at pctop.cfg file! alarm\n");
		exit(1);
	}

	fscanf(cfg_file, "%s", Output_dir); /* output dir      */
	fscanf(cfg_file, "%s", Html_dir);   /* html output dir */
	fscanf(cfg_file, "%s", Groupsfile); /* pcgroup.cfg dir */
	/* more to come */

	pcgroup_file = fopen(Groupsfile, "rt");
	if (!pcgroup_file)
	{
		printf("error at %s file! alarm\n", Groupsfile);
		exit(1);
	}

	/* this fucks up badly man... damn... */
	while (!feof(pcgroup_file))
	{
		gn++;
		MemNumber[gn] = 0;

		fscanf(pcgroup_file, "%s", GroupName[gn]); /* read group name */

		if (strstr(GroupName[gn], "null"))
		{
			gn--;
			break;
		}

		fscanf(pcgroup_file, "%i", &MemNumber[gn]); /* read group name */
		gu = 1;

		while (gu <= MemNumber[gn])
		{
			fgets(GroupUser[gu], 80, pcgroup_file);
			GroupUser[gu][strlen(GroupUser[gu]) - 1] = '\0';
			gu++;
		}
	}
	NumOfGroups = gn;

	fclose(cfg_file);
	fclose(pcgroup_file);
	return 0;
}

/* ========================================================================= */
/* =====[ reads the userfiles ]============================================= */
/* ========================================================================= */
int Data_Extraction()
{
	b_id = 1; /* board id */

	for (x = 0; x < gl.gl_pathc; x++)
	{
		userfile = fopen(gl.gl_pathv[x], "rt");
		if (!userfile)
		{
			printf("error at %s file!", gl.gl_pathv[x]);
			exit(1);
		}
		printf("info gather on: %i which is: %s\n", b_id, gl.gl_pathv[x]);

		if (b_id == 1)
			Read_My_First_Data_File();  /* our first datafile read */
		else
			Info_Gather();

		fclose(userfile);
		b_id++;
	}
	b_id--;
	return 0;
}

/* ========================================================================= */
/* =====[ first datafile read ]============================================= */
/* ========================================================================= */
int Read_My_First_Data_File()
{
	int i = 0;
	printf("at reamyfirstdatafile, with board_id: %i\n", b_id);

	fgets(board_id[b_id], 80, userfile); /* board_id */
	fgets(line, 80, userfile);           /* date */

	while (!feof(userfile))
	{
		if (feof(userfile))
			break;
		i++;
		fgets(line, 80, userfile);
		line[strlen(line) - 1] = '\0';
		strcpy(pmc[i].User, line);

		fgets(line, 80, userfile);
		line[strlen(line) - 1] = '\0';
		sscanf(line, "%llu", &pmc[i].Uploadbytes);
	}

	maxuser = i - 1;
	return 0;
}

/* ========================================================================= */
/* =====[ reading user infos ]============================================== */
/* ========================================================================= */
int Info_Gather()
{
	printf("at info gather (second board), with board_id: %i\n", b_id);

	fgets(board_id[b_id], 80, userfile); /* board_id */
	fgets(line, 80, userfile);           /* date */

	while (!feof(userfile))
	{
		if (feof(userfile))
			break;

		fgets(raw_username, 80, userfile);
		raw_username[strlen(raw_username) - 1] = '\0';

		fgets(line, 80, userfile);
		raw_ul_bytes = 0;
		sscanf(line, "%llu", &raw_ul_bytes); /* users upload bytes */

		if (raw_ul_bytes > 0)
			Compare_Users();
	}

	return 0;
}

/* ========================================================================= */
/* =====[ username check, exist already? ]================================== */
/* ========================================================================= */
int Compare_Users()
{
	int cc = 1;
	int found = 0;

	while (cc <= maxuser)
	{
		if (strstr(pmc[cc].User, raw_username))
		{
			pmc[cc].Uploadbytes += raw_ul_bytes;
			found = 1;
			break;
		}
		cc++;
	}

	if (found == 0)
	{
		maxuser++;
		strcpy(pmc[maxuser].User, raw_username);
		pmc[maxuser].Uploadbytes = raw_ul_bytes;
	}

	return 0;
}

/* ========================================================================= */
/* =====[ All Bytes Counter ]=============================================== */
/* ========================================================================= */
int All_Bytes_Stats()
{
	int al = 1;

	while (al <= maxuser)
	{
		All_Bytes += pmc[al].Uploadbytes; /* total bytes count */
		al++;
	}

	return 0;
}

/* ========================================================================= */
/* =====[ Writing Alltime Top ]============================================= */
/* ========================================================================= */
int Do_Alltime_Top(int usernum)
{
	char huoh[80];
	char htmlhuoh[80];
	char Topic[80];

	if (usernum == 10)
	{
		strcpy(huoh, "_top10_users.txt");
		strcpy(htmlhuoh, "_top10_users.html");
	}

	if (usernum == 50)
	{
		strcpy(huoh, "_top50_users.txt");
		strcpy(htmlhuoh, "_top50_users.html");
	}

	if (usernum == 1000)
	{
		strcpy(huoh, "_top1000_users.txt");
		strcpy(htmlhuoh, "_top1000_users.html");
	}

	bulletin = fopen(huoh, "wt");
	if (!bulletin)
	{
		printf("error at %s!\n", huoh);
		exit(1);
	}

	if (usernum == 10)
	{
		strcpy(Topic, "\n\n\t PC-TOP 10 Alltime Users\n\n");
		fputs(Topic, bulletin);
		/* created monthlybytes sorted list */

		for (i = 0; i < maxuser; i++)
			tmptop[i] = pmc[i].Uploadbytes;

		sorted = sort_top(tmptop);
		dog = 0;

		while (sorted)
		{
			dog++;

			sprintf(tempstr, "%llu", pmc[sorted->num].Uploadbytes);
			strcpy(tempstr, f_format(tempstr));
			sprintf(buf, " %3d  %-24s %20s\n", dog, pmc[sorted->num].User,
			        tempstr);
			sorted = sorted->next;
			if (dog > 10)
				break;
			fputs(buf, bulletin);
		}
	}
	if (usernum == 50)
	{
		strcpy(Topic, "\n\n\t PC-TOP 50 Alltime Users\n\n");
		fputs(Topic, bulletin);
		/* created monthlybytes sorted list */

		for (i = 0; i < maxuser; i++)
			tmptop[i] = pmc[i].Uploadbytes;

		sorted = sort_top(tmptop);
		dog = 0;

		while (sorted)
		{
			dog++;

			sprintf(tempstr, "%llu", pmc[sorted->num].Uploadbytes);
			strcpy(tempstr, f_format(tempstr));
			sprintf(buf, " %3d  %-24s %20s\n", dog, pmc[sorted->num].User,
			        tempstr);
			sorted = sorted->next;
			if (dog > 50)
				break;
			fputs(buf, bulletin);
		}
	}

	if (usernum == 1000)
	{
		strcpy(Topic, "\n\n\t PC-TOP 1000 Alltime Users\n\n");
		fputs(Topic, bulletin);
		/* created monthlybytes sorted list */

		for (i = 0; i < maxuser; i++)
			tmptop[i] = pmc[i].Uploadbytes;

		sorted = sort_top(tmptop);
		dog = 0;

		while (sorted)
		{
			dog++;

			sprintf(tempstr, "%llu", pmc[sorted->num].Uploadbytes);
			strcpy(tempstr, f_format(tempstr));
			sprintf(buf, " %3d  %-24s %20s\n", dog, pmc[sorted->num].User,
			        tempstr);
			sorted = sorted->next;
			fputs(buf, bulletin);
		}
	}

	fclose(bulletin);
	return 0;
}

/* ========================================================================= */
/* =====[ stats ]=========================================================== */
/* ========================================================================= */
int Do_Stats()
{
	FILE *stats;
	char statbuf[200];

	stats = fopen("_top-stat.txt", "wt");
	if (!stats)
	{
		printf("error at _top-stat.txt\n");
		exit(1);
	}

	sprintf(tempstr, "%llu", All_Bytes);
	strcpy(tempstr, f_format(tempstr));

	sprintf(statbuf, "\n\n\t%i boards, %i total users, %s total bytes\n", b_id, maxuser, tempstr);
	fputs(statbuf, stats);

	sprintf(tempstr, "%llu", All_Bytes / (1024 * 1024 * 1024));
	strcpy(tempstr, f_format(tempstr));
	sprintf(statbuf, "\tgigs %s\n\n", tempstr);
	fputs(statbuf, stats);

	fclose(stats);
	return 0;
}

/* ========================================================================= */
/* =====[ check for update parameter ]====================================== */
/* ========================================================================= */
int Check_Param(char *argc[])
{
	FILE *DataBase;
	char parameter[10];
	int ii = 0;

	strcpy(parameter, argc[1]);
	if (!strcasecmp(parameter, "/w"))
	{
		printf("at Check_Param(), parameter was - %s which means *UPDATE*\n", parameter);
		/* ... insert here the UPDATE function please */

		DataBase = fopen("_month.DBA", "wb");
		if (!DataBase)
		{
			printf("Something wrong with _month.DBA!\n");
			exit(1);
		}

		while (ii < maxuser)
		{
			ii++;

			bzero(DATA.userp, sizeof(DATA.userp));
			strcpy(DATA.userp, pmc[ii].User);
			DATA.bytep = pmc[ii].Uploadbytes;
			printf("dat %i, userp: %s --- bytep: %llu ---\n", ii, DATA.userp, DATA.bytep);

			fwrite(&DATA, sizeof(myStruct), 1, DataBase);
		}

		fclose(DataBase);
	} /* if param ok */

	return 0;
}

/* ========================================================================= */
/* =====[ monthly ]========================================================= */
/* ========================================================================= */
int Do_Monthly()
{
	FILE *old_data;

	char OLD_User[MAXUSERS][25];
	unsigned long long OLD_Uploadbytes[MAXUSERS];
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

		if (feof(old_data))
			break;
	}

	max_dba = dba; /* how many users in dba? */
	printf("we have %lu users in max_dba = _month.dba\n", max_dba);
	fclose(old_data);
	printf("Done old data extraction\n");

	dba = 0;

	while (dba < max_dba)
	{
		dba++;

		for (im = 1; im < maxuser; im++) {
/*    printf("Comparing: %s to %s\n",pmc[im].User,OLD_User[dba]); */
			if (strstr(pmc[im].User, OLD_User[dba]))
			{
				pmc[im].Monthlybytes = 0;
				pmc[im].Monthlybytes = (float)(pmc[im].Uploadbytes - OLD_Uploadbytes[dba]);
				match = 1; /* printf("found pmc[].User match: %s montly_uploadbytes: %llu\n",pmc[im].User,pmc[im].Monthlybytes);*/
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
	printf("openedet _monthly.txt\n");
	fputs("\n umm yeah, monthly\n\n", month_blt);

	/* created monthlybytes sorted list */

	for (i = 0; i < maxuser; i++)
		tmptop[i] = pmc[i].Monthlybytes;

	sorted = sort_top(tmptop);
	dog = 0;

	while (sorted)
	{
		dog++;

		sprintf(tempstr, "%llu", pmc[sorted->num].Monthlybytes);
		strcpy(tempstr, f_format(tempstr));
		sprintf(buf, " %3d  %-24s %20s\n", dog, pmc[sorted->num].User,
		        tempstr);
		sorted = sorted->next;
		fputs(buf, month_blt);
	}

	fclose(month_blt);
	return 0;
}

/* ========================================================================= */
/* =====[ the big motha ]=================================================== */
/* ========================================================================= */
int main(int argv, char *argc[])

{
	bzero(&pmc, sizeof(struct Record) * MAXUSERS);

	Read_Config_File();

	glob("data/*.DAT", 0, 0, &gl);

	Data_Extraction(); /* read files etc */
	globfree(&gl);

	printf("Data extraction complete.\n");

	All_Bytes_Stats(); /* all bytes counter */

	printf("All_Bytes_Stats complete.\n");

	Do_Alltime_Top(10);   /* alltime top-10 */
	Do_Alltime_Top(50);   /* alltime top-50 */
	Do_Alltime_Top(1000); /* alltime top-1000 */
	Do_Stats();           /* write stats    */
	Do_Monthly();         /* monthly top    */

	if (argv == 2)
		Check_Param(argc);    /* check if we make UPDATE */

	return 0;
}
