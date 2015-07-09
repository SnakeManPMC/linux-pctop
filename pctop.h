/* how many users we can list on the array */
#define ASIZE    1000

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

glob_t gl;

FILE *userfile;
FILE *bulletin;
FILE *month_blt;

char raw_username[25];
char board_id[ASIZE][10];
char tempstr[80];
char parameter[10];
char GroupName[ASIZE][30];
char GroupUser[ASIZE][25];
int b_id, x, maxuser, MemNumber[ASIZE];
int NumOfGroups = 0, i, dog, c;
unsigned long long raw_ul_bytes;
unsigned long long All_Bytes;

char Output_dir[80];
char Html_dir[80];
char line[80];
char buf[1024];