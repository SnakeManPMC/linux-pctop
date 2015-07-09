/*

    PC-TOP gftpd remote datafile collector (c) PMC 2000 - 2015.

 */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <glob.h>

glob_t gl;

FILE *userfile;
FILE *datafile;

char U_File[20];
char line[80];
char *p;
char Site_Name[80];
int maxuser = 0, i = 0, x = 0;
unsigned long long bytes_up = 0;
unsigned long long bytes_up_m = 0;

/* reads the userfiles in the dir */
int File_Select()
{
	char *utemp[10];
	int ui = 0;
	i = 0;

	/* loop to read the files */
	printf(" reading userfiles...");

	for (x = 0; x < gl.gl_pathc; x++)
	{
		char temp_gl[80];

		strcpy(temp_gl, gl.gl_pathv[x]);
		ui = splitpath(utemp, temp_gl);
		sprintf(U_File, "%s\n", utemp[ui]);

		userfile = fopen(gl.gl_pathv[x], "rt");
		if (!userfile)
			exit(1);

		Info_Gather();
		fclose(userfile);
	}

	maxuser = i;
	/* loop end here......... */

	printf("Done!\n read total of %i user-records\nThanks for using PC-TOP gftpd remote.\n", i);

	return 0;
}

/* reading the individual user information */
int Info_Gather()
{
	char temptag[80];
	unsigned long long tmp;

	if (strstr(gl.gl_pathv[x], "!!ERR!!"))
		return 0;
	if (strstr(gl.gl_pathv[x], "master"))
		return 0;
	if (strstr(gl.gl_pathv[x], "default"))
		return 0;
	if (strstr(gl.gl_pathv[x], "default.user"))
		return 0;

	fgets(line, 80, userfile);
	if (!strstr(line, "# General informati"))
		return 0;                          /* if not gftpd userfile */

	i++;
/*    strcpy(username[i],U_File); /* username */
	fputs(U_File, datafile);

	while (!feof(userfile))
	{
		if (strstr(line, "# Time-related information"))
		{
			fgets(line, 80, userfile); /* login_times */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%i",&login_times[i]); */

			fgets(line, 80, userfile); /* last_on 83838383 */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%lu",&last_on[i]); */

			fgets(line, 80, userfile); /* account_created 83838383 */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%i",&acc_created[i]); */

			fgets(line, 80, userfile); /* added_by ? */
/*	p=strtok(line," ");
        p=strtok(NULL," ");  */

			fgets(line, 80, userfile); /* comment ? */
/*	p=strtok(line," ");
        p=strtok(NULL," ");  */

			fgets(line, 80, userfile); /* time_limit */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%i",&time_limit[i]); */

			fgets(line, 80, userfile); /* time_on_today */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%i",&time_on_today[i]); */

			fgets(line, 80, userfile); /* last_nuked */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%i",&last_nuked[i]); */

			fgets(line, 80, userfile); /* skip user_color */
			fgets(line, 80, userfile); /* skip quiet */

			fgets(line, 80, userfile); /* speed_fuckups */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%i",&speed_fuckups[i]); */

			fgets(line, 80, userfile); /* week_bad */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%i",&week_bad[i]); */

			fgets(line, 80, userfile); /* all_bad */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%i",&all_bad[i]); */
		}

//    if (strstr(line,"tagline"))
//	{
//	p=strtok(line," ");
//	p=strtok(NULL," ");
//	strcpy(temptag,"");
//	while (p) /* do tokens until we dont have anything */
//	    {
//	    strcat(temptag,p);     /* append the next   */
//	    strcat(temptag," ");   /* some space...     */
//	    p=strtok(NULL," ");    /* tokenize another  */
//	    }

//	    if (strlen(temptag) > 30) temptag[31]='\0';

//	    strncpy(tagline[i],temptag,strlen(temptag)-2);/* removing \0 */
//	}

		if (strstr(line, "# Normal Xfer"))
		{
			fgets(line, 80, userfile); /* files_up */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%llu",&files_up[i]); */

			fgets(line, 80, userfile); /* bytes_up */
			p = strtok(line, " ");
			p = strtok(NULL, " ");
			sscanf(p, "%llu", &tmp);
			bytes_up = (tmp * 1024);
			sprintf(line, "%llu\n", bytes_up);
			fputs(line, datafile);

			fgets(line, 80, userfile); /* seconds_up */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%llu",&seconds_up[i]); */

			fgets(line, 80, userfile); /* files_down */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%llu",&files_down[i]); */

			fgets(line, 80, userfile); /* bytes_down */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%llu",&tmp);
        bytes_down[i]=(tmp*1024); */

			fgets(line, 80, userfile); /* seconds_down */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%llu",&seconds_down[i]); */

			fgets(line, 80, userfile); /* files_up_wk */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%llu",&files_up_wk[i]); */

			fgets(line, 80, userfile); /* bytes_up_wk */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%llu",&tmp);
        bytes_up_wk[i]=(tmp*1024); */

			fgets(line, 80, userfile); /* seconds_up_wk */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%llu",&seconds_up_wk[i]); */

			fgets(line, 80, userfile); /* files_down_wk */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%llu",&files_down_wk[i]); */

			fgets(line, 80, userfile); /* bytes_down_wk */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%llu",&tmp);
        bytes_down_wk[i]=(tmp*1024); */

			fgets(line, 80, userfile); /* seconds_down_wk */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%llu",&seconds_down_wk[i]); */

			fgets(line, 80, userfile); /* files_up_m */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%llu",&files_up_m[i]); */

			fgets(line, 80, userfile); /* bytes_up_m */
			p = strtok(line, " ");
			p = strtok(NULL, " ");
			sscanf(p, "%llu", &tmp);
			bytes_up_m = (tmp * 1024);
			sprintf(line, "%llu\n", bytes_up_m);
/* fputs(line,datafile); */

			fgets(line, 80, userfile); /* seconds_up_m */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%llu",&seconds_up_m[i]); */

			fgets(line, 80, userfile); /* files_down_m */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%llu",&files_down_m[i]); */

			fgets(line, 80, userfile); /* bytes_down_m */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%llu",&tmp);
        bytes_down_m[i]=(tmp*1024); */

			fgets(line, 80, userfile); /* seconds_down_m */
/*	p=strtok(line," ");
        p=strtok(NULL," ");
   sscanf(p,"%llu",&seconds_down_m[i]); */
		}

/* group top data collection */
		if (strstr(line, "# Groups for"))
		{
			fgets(line, 80, userfile); /* group sysop */
			fgets(line, 80, userfile); /* group's member? */
			p = strtok(line, " ");
			p = strtok(NULL, " ");
/*	strcpy(group[grp],p); */
		}

		fgets(line, 80, userfile);
	}

	return 0;
}

/* to stript the path from userfiles (names actually) */
int splitpath(char **args, char *p)
{
	int c = 0;

	while (*p == '/')
		p++;

	args[c++] = p;
	while (*p)
	{
		if (*p == '/')
		{
			*(p++) = 0;
			args[c++] = p;
			while(*p == '/')
				p++;
		}
		else
			p++;
	}
	args[c] = 0;

	return c - 1;
}

void Readingconf()
{
	FILE *fish;
	printf("readingconf!\n");

	fish = fopen("gftpd.sysconfig", "rt");
	if (!fish)
	{
		printf("error at /etc/gftpd.sysconfig !\n");
		exit(1);
	}

	fgets(line, 80, fish);

	while (strstr(line, "sitename") == 0)
	{
/*              p=strtok(line," ");
                p=strtok(NULL," "); */
		fgets(line, 80, fish);
	}

	p = strtok(line, " ");
	p = strtok(NULL, " ");
	strcpy(Site_Name, "");
	while (p) /* do tokens until we dont have anything */
	{
		strcat(Site_Name, p);   /* append the next   */
		strcat(Site_Name, " "); /* some space...     */
		p = strtok(NULL, " ");  /* tokenize another  */
	}

	fclose(fish);
}

void Name_Date()
{
	char buf[100];

	struct tm *tm;

	time_t t;
	t = time(0);
	tm = localtime(&t);

	printf("%-2.2d/%-2.2d/%-2.2d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year);

	Site_Name[strlen(Site_Name) - 1] = '\0';
	sprintf(buf, "%s%02d/%02d/%02d\n", Site_Name, tm->tm_mday, tm->tm_mon + 1, tm->tm_year);

	fputs(buf, datafile);
}

int main()
{
	Readingconf();

	glob("/.ftp-data/users/*", 0, 0, &gl); /* what files to select from the dir? */

	datafile = fopen("gftpdremote.dat", "wt");
	if (!datafile)
	{
		printf("error at remote.dat!\n");
		exit(1);
	}

	Name_Date();
	File_Select();

	fclose(datafile);
	return 0;
}
