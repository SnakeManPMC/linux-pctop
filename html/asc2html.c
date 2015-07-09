#include <stdio.h>
#include <string.h>

FILE *pctop;
FILE *html_out;

char line[80];
char pos[80];
char user[80];
char bytes[80];
char changes[80];
char ReleaseDate[80];
char feedtopic[80];
char *p;
char html_buffer[1024];
int i;

void Html_Header(char *topic)
{
	sprintf(html_buffer,
	        "<html>\n"
	        "<head>\n"
	        "<title>PC-TOP</title>\n"
	        "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\">\n"
	        "<style type=\"text/css\">\n"
	        "<!--\n"
	        ".pctop {  font-family: Verdana, Arial, Helvetica, sans-serif; font-size: 9pt; font-style: normal; font-weight: normal}\n"
	        "-->\n"
	        "</style>\n"
	        "</head>\n\n"
	        "<body bgcolor=\"#FFFFFF\" text=\"#000000\" link=\"#666666\" vlink=\"#666666\" alink=\"#666666\">\n"
	        "<div align=\"center\">\n");

	fputs(html_buffer, html_out);

	sprintf(html_buffer,
	        " <p><img src=\"../../yla.jpg\" width=\"486\" height=\"139\"> <br>\n"
	        "    <font face=\"Arial, Helvetica, sans-serif\">%s</font></p>\n"
	        "  <table border=\"0\" cellpadding=\"5\" bgcolor=\"#D7D7D7\" cellspacing=\"0\" width=\"48%\">\n", topic);

	fputs(html_buffer, html_out);
}

void html_loop(char *hpos, char *huser, char *hbytes, char *hchanges)
{
	/* pos,user,bytes adding */
	sprintf(html_buffer,
	        "    <tr>\n"
	        "      <td class=\"pctop\">%s</td>\n"
	        "      <td class=\"pctop\">%s</td>\n"
	        "      <td class=\"pctop\">\n"
	        "        <div align=\"right\">%s</div>\n"
	        "      </td>\n"
	        "      <td class=\"pctop\">\n"
	        "        <div align=\"right\">%s</div>\n"
	        "      </td>\n"
	        "    </tr>\n", hpos, huser, hbytes, hchanges);

	fputs(html_buffer, html_out);
}

void Html_Footer()
{
	/* footer */
	sprintf(html_buffer,
	        "  </table>\n"
	        "  <p><img src=\"../../ala.jpg\" width=\"486\" height=\"29\"><font face=\"Arial, Helvetica, sans-serif\" size=\"2\"><br>\n"
	        "    </font><font face=\"Arial, Helvetica, sans-serif\" size=\"1\">pc-top (c) snake\n"
	        "    man, pmc 1993-2015<br>\n"
	        "    pc-top webpages (c) pk 2000-2015</font></p>\n"
	        "  <p>&nbsp;</p>\n"
	        "  <hr>\n");

	fputs(html_buffer, html_out);

	fclose(html_out);
}

void Doit(int num)
{
	char temp[80];

	sprintf(temp, "top/PCTOP%i.ASC", num);

	pctop = fopen(temp, "rt");
	if (!pctop)
	{
		printf("error at %s\n", temp);
		exit(1);
	}

	for (i = 1; i < 8; i++) fgets(line, 80, pctop);

	for (i = 1; i < num + 1; i++) {
		fgets(line, 80, pctop);

		p = strtok(line, " ");
		p = strtok(NULL, " ");
		strcpy(pos, p);

		p = strtok(NULL, " ");
		strcpy(user, p);

		p = strtok(NULL, " ");

		strcpy(bytes, p);

		/* loop more tokens UNTIL we find "," from the string */
		while (strstr(bytes, ",") == 0)
		{
			strcat(user, " ");
			strcat(user, bytes);
			p = strtok(NULL, " ");

			strcpy(bytes, p);
		}

		p = strtok(NULL, " ");

		strcpy(changes, p);
		if (strcmp(p, "(") == 0)
		{
			p = strtok(NULL, " ");
			strcat(changes, p);
		}

		html_loop(pos, user, bytes, changes);
	}
	fclose(pctop);
}

int GROUPDOIT(int num)
{
	char temp[80];

	sprintf(temp, "top/TOPG%i.ASC", num);

	pctop = fopen(temp, "rt");
	if (!pctop)
	{
		printf("error at %s\n", temp);
		exit(1);
	}

	for (i = 1; i < 8; i++) fgets(line, 80, pctop);

	for (i = 1; i < num + 1; i++) {
		fgets(line, 80, pctop);

		p = strtok(line, " ");
		p = strtok(NULL, " ");
		strcpy(pos, p);

		p = strtok(NULL, " ");
		strcpy(user, p);
		if (strstr(p, "0"))
		{
			printf("ok P == zero! skipping...\n");
			while (i < num + 1)
			{
				strcpy(user, "-");
				strcpy(bytes, "0");
				strcpy(changes, "( --)");
				html_loop(pos, user, bytes, changes);
				i++;
			}
			fclose(pctop);
			return 0;
		}

		p = strtok(NULL, " ");

		strcpy(bytes, p);

		/* loop more tokens UNTIL we find "," from the string */
		while (strstr(bytes, ",") == 0)
		{
			strcat(user, " ");
			strcat(user, bytes);
			p = strtok(NULL, " ");

			strcpy(bytes, p);
		}

		p = strtok(NULL, " ");

		strcpy(changes, p);
		if (strcmp(p, "(") == 0)
		{
			p = strtok(NULL, " ");
			strcat(changes, p);
		}

		html_loop(pos, user, bytes, changes);
	}

	fclose(pctop);
	return 0;
}

int GROUP_MONTH_DOIT(int num)
{
	char temp[80];

	sprintf(temp, "top/TOPGM%i.ASC", num);

	pctop = fopen(temp, "rt");
	if (!pctop)
	{
		printf("error at %s\n", temp);
		exit(1);
	}

	for (i = 1; i < 8; i++) fgets(line, 80, pctop);

	for (i = 1; i < num + 1; i++) {
		fgets(line, 80, pctop);

		p = strtok(line, " ");
		p = strtok(NULL, " ");
		strcpy(pos, p);

		p = strtok(NULL, " ");
		strcpy(user, p);
		if (strstr(p, "0"))
		{
			printf("ok P == zero! skipping...\n");
			while (i < num + 1)
			{
				strcpy(user, "-");
				strcpy(bytes, "0");
				strcpy(changes, "( --)");
				html_loop(pos, user, bytes, changes);
				i++;
			}
			fclose(pctop);
			return 0;
		}

		p = strtok(NULL, " ");

		strcpy(bytes, p);

		/* loop more tokens UNTIL we find "," from the string */
		while (strstr(bytes, ",") == 0)
		{
			strcat(user, " ");
			strcat(user, bytes);
			p = strtok(NULL, " ");

			strcpy(bytes, p);
		}

		p = strtok(NULL, " ");

		strcpy(changes, p);
		if (strcmp(p, "(") == 0)
		{
			p = strtok(NULL, " ");
			strcat(changes, p);
		}

		html_loop(pos, user, bytes, changes);
	}
	fclose(pctop);
	return 0;
}

int GROUP_HIGHSCORE_DOIT(int num)
{
	char temp[80];

	sprintf(temp, "top/TOPGH%i.ASC", num);

	pctop = fopen(temp, "rt");
	if (!pctop)
	{
		printf("error at %s\n", temp);
		exit(1);
	}

	for (i = 1; i < 8; i++) fgets(line, 80, pctop);

	for (i = 1; i < num + 1; i++) {
		fgets(line, 80, pctop);

		p = strtok(line, " ");
		p = strtok(NULL, " ");
		strcpy(pos, p);

		p = strtok(NULL, " ");
		strcpy(user, p);
		if (strstr(p, "0"))
		{
			printf("ok P == zero! skipping...\n");
			while (i < num + 1)
			{
				strcpy(user, "-");
				strcpy(bytes, "0");
				strcpy(changes, "( --)");
				html_loop(pos, user, bytes, changes);
				i++;
			}
			fclose(pctop);
			return 0;
		}

		p = strtok(NULL, " ");

		strcpy(bytes, p);

		/* loop more tokens UNTIL we find "," from the string */
		while (strstr(bytes, ",") == 0)
		{
			strcat(user, " ");
			strcat(user, bytes);
			p = strtok(NULL, " ");

			strcpy(bytes, p);
		}

		p = strtok(NULL, " ");

		strcpy(changes, p);
		if (strcmp(p, "(") == 0)
		{
			p = strtok(NULL, " ");
			strcat(changes, p);
		}

		html_loop(pos, user, bytes, changes);
	}
	fclose(pctop);
	return 0;
}

void HIGHSCOREdoit(int num)
{
	char temp[80];

	sprintf(temp, "top/PCTOPH%i.ASC", num);

	pctop = fopen(temp, "rt");
	if (!pctop)
	{
		printf("error at %s\n", temp);
		exit(1);
	}

	for (i = 1; i < 8; i++) fgets(line, 80, pctop);

	for (i = 1; i < num + 1; i++) {
		fgets(line, 80, pctop);

		p = strtok(line, " ");
		p = strtok(NULL, " ");
		strcpy(pos, p);

		p = strtok(NULL, " ");
		strcpy(user, p);

		p = strtok(NULL, " ");

		strcpy(bytes, p);

		/* loop more tokens UNTIL we find "," from the string */
		while (strstr(bytes, ",") == 0)
		{
			strcat(user, " ");
			strcat(user, bytes);
			p = strtok(NULL, " ");

			strcpy(bytes, p);
		}

		p = strtok(NULL, " ");

		strcpy(changes, p);
		if (strcmp(p, "(") == 0)
		{
			p = strtok(NULL, " ");
			strcat(changes, p);
		}

		html_loop(pos, user, bytes, changes);
	}
	fclose(pctop);
}

int MONTHLYdoit(int num)
{
	char temp[80];

	sprintf(temp, "top/PCTOPM%i.ASC", num);

	pctop = fopen(temp, "rt");
	if (!pctop)
	{
		printf("error at %s\n", temp);
		exit(1);
	}

	for (i = 1; i < 8; i++) fgets(line, 80, pctop);

	for (i = 1; i < num + 1; i++) {
		fgets(line, 80, pctop);

		p = strtok(line, " ");
		p = strtok(NULL, " ");
		strcpy(pos, p);

		p = strtok(NULL, " ");
		strcpy(user, p);
		if (strstr(p, "0"))
		{
			printf("ok P == zero! skipping...\n");
			while (i < num + 1)
			{
				strcpy(user, "-");
				strcpy(bytes, "0");
				strcpy(changes, "( --)");
				html_loop(pos, user, bytes, changes);
				i++;
			}
			fclose(pctop);
			return 0;
		}

		p = strtok(NULL, " ");

		strcpy(bytes, p);

		/* loop more tokens UNTIL we find "," from the string */
		while (strstr(bytes, ",") == 0)
		{
			strcat(user, " ");
			strcat(user, bytes);
			p = strtok(NULL, " ");

			strcpy(bytes, p);
		}

		p = strtok(NULL, " ");

		strcpy(changes, p);
		if (strcmp(p, "(") == 0)
		{
			p = strtok(NULL, " ");
			strcat(changes, p);
		}

		html_loop(pos, user, bytes, changes);
	}
	fclose(pctop);
	return 0;
}

int Gimme_Date()
{
	FILE *release;

	release = fopen("asc2html.rel", "rt");
	if (!release)
	{
		printf("error at asc2html.rel, cannot open!\n");
		exit(1);
	}

	fgets(ReleaseDate, 80, release);

	fclose(release);
	return 0;
}

int TopGroup_Generator()
{
	char temp[80];

	strcpy(temp, "top/TOPGROUP.ASC");

	pctop = fopen(temp, "rt");
	if (!pctop)
	{
		printf("error at %s\n", temp);
		exit(1);
	}

	fputs("<center>\n", html_out);

	while (!feof(pctop))
	{
		fgets(line, 80, pctop);
		if ((strstr(line, "PC-TOP")) || (strstr(line, "|--")))
		{
			printf("we found garbage\n");
		}
		else
		{
			strcat(line, "<br>\n");
			fputs(line, html_out);
		}
	}

	fputs("</center>\n", html_out);

	fclose(pctop);
	return 0;
}

int Release_Text_Generator()
{
	char temp[80];

	strcpy(temp, "top/text.txt");

	pctop = fopen(temp, "rt");
	if (!pctop)
	{
		printf("error at %s\n", temp);
		exit(1);
	}

	fputs("<center><tr><td>\n", html_out);
	fgets(line, 80, pctop);

	while (!feof(pctop))
	{
		strcat(line, "<br>\n");
		fputs(line, html_out);
		fgets(line, 80, pctop);
	}

	fputs("</tr></td></center>\n", html_out);

	fclose(pctop);
	return 0;
}

int main()
{
	printf("\n\tPC-TOP asc 2 html converter.\n\n");

	Gimme_Date(); /* read release date like; May, 2000. from asc2html.rel */

	/*  pc-top release text */
	html_out = fopen("pctop_release.html", "wt");
	if (!html_out)
	{
		printf("error at pctop_release.html\n");
		exit(1);
	}

	sprintf(feedtopic, "%s Release toughts", ReleaseDate);
	Html_Header(feedtopic);
	Release_Text_Generator();
	Html_Footer();
	printf("pctop_release.html created!\n");

	/*  top-10 uploaders  */
	html_out = fopen("pctop10.html", "wt");
	if (!html_out)
	{
		printf("error at pctop10.html\n");
		exit(1);
	}

	sprintf(feedtopic, "%s Top-10 Uploaders", ReleaseDate);
	Html_Header(feedtopic);
	Doit(10);
	Html_Footer();
	printf("pctop10.html created!\n");

	/*  top-50 uploaders  */
	html_out = fopen("pctop50.html", "wt");
	if (!html_out)
	{
		printf("error at pctop50.html\n");
		exit(1);
	}

	sprintf(feedtopic, "%s Top-50 Uploaders", ReleaseDate);
	Html_Header(feedtopic);
	Doit(50);
	Html_Footer();
	printf("pctop50.html created!\n");

	/*  monthly  */
	html_out = fopen("pctop_monthly.html", "wt");
	if (!html_out)
	{
		printf("error at pctop_monthly.html\n");
		exit(1);
	}

	sprintf(feedtopic, "Top-10 Monthly Uploaders in %s", ReleaseDate);
	Html_Header(feedtopic);
	MONTHLYdoit(10);
	Html_Footer();
	printf("pctop_monthly.html created!\n");

	/*  highscores  */
	html_out = fopen("pctop_hscore.html", "wt");
	if (!html_out)
	{
		printf("error at pctop_hscore.html\n");
		exit(1);
	}

	sprintf(feedtopic, "%s Top-10 Highscores", ReleaseDate);
	Html_Header(feedtopic);
	HIGHSCOREdoit(10);
	Html_Footer();
	printf("pctop_hscore.html created!\n");

	/*  top-10 groups  */
	html_out = fopen("pctop_group10.html", "wt");
	if (!html_out)
	{
		printf("error at pctop_group10.html\n");
		exit(1);
	}

	sprintf(feedtopic, "%s Top-10 Groups", ReleaseDate);
	Html_Header(feedtopic);
	GROUPDOIT(10);
	Html_Footer();
	printf("pctop_group10.html created!\n");

	/*  top-10 groups monthly  */
	html_out = fopen("pctop_groupm10.html", "wt");
	if (!html_out)
	{
		printf("error at pctop_groupm10.html\n");
		exit(1);
	}

	sprintf(feedtopic, "Group Top-10 Monthly %s", ReleaseDate);
	Html_Header(feedtopic);
	GROUP_MONTH_DOIT(10);
	Html_Footer();
	printf("pctop_groupm10.html created!\n");

	/*  top-10 groups highscores */
	html_out = fopen("pctop_grouphs10.html", "wt");
	if (!html_out)
	{
		printf("error at pctop_grouphs10.html\n");
		exit(1);
	}

	sprintf(feedtopic, "%s Group Top-10 Highscores", ReleaseDate);
	Html_Header(feedtopic);
	GROUP_HIGHSCORE_DOIT(10);
	Html_Footer();
	printf("pctop_grouphs10.html created!\n");

	/*  topgroups */
	html_out = fopen("pctop_topgrops.html", "wt");
	if (!html_out)
	{
		printf("error at pctop_topgroups.html\n");
		exit(1);
	}

	sprintf(feedtopic, "%s Group Memberlist", ReleaseDate);
	Html_Header(feedtopic);
	TopGroup_Generator();
	Html_Footer();
	printf("pctop_topgroups.html created!\n");

	/*  pc-top release text */
	html_out = fopen("pctop_release.html", "wt");
	if (!html_out)
	{
		printf("error at pctop_release.html\n");
		exit(1);
	}

	sprintf(feedtopic, "%s Release toughts", ReleaseDate);
	Html_Header(feedtopic);
	Release_Text_Generator();
	Html_Footer();
	printf("pctop_release.html created!\n");

	return 0;
}
