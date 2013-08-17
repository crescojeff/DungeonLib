#ifdef MAIN
FILE *genout= NULL;
FILE *xdef= NULL;
FILE *xlogic= NULL;
FILE *xdict= NULL;
FILE *xodet= NULL;
FILE *xmsg= NULL;
FILE *xolng= NULL;
FILE *xosht= NULL;
FILE *xosynn= NULL;
FILE *xosynt= NULL;
FILE *xrmd= NULL;
FILE *xrml= NULL;
FILE *xrmp= NULL;
FILE *xrms= NULL;
FILE *xvchk= NULL;
FILE *xvsynn= NULL;
FILE *xvsynt= NULL;
FILE *xoqual= NULL;
FILE *xoqualo= NULL;
FILE *xvprep= NULL;
BOOLEAN do_encrypt= FALSE;
BOOLEAN islow= TRUE;
BOOLEAN ishigh= FALSE;
BOOLEAN isinit= FALSE;
BOOLEAN isfirst= FALSE;
BOOLEAN islast= FALSE;
BOOLEAN gotip= FALSE;
BOOLEAN update= TRUE;
int cline=0;
char fname[80]="";
char error[80]="";
char source[80]=".";
int msg_no= -1;
int verb_no= -1;
int room_no= -1;
int obj_no= -1;
int str_no= -1;
int isev= 0;
BOOLEAN list= FALSE;
BOOLEAN defin= FALSE;
BOOLEAN flt= FALSE;
int prterr;
#else
extern FILE *genout;
extern FILE *xdef;
extern FILE *xlogic;
extern FILE *xdict;
extern FILE *xodet;
extern FILE *xmsg;
extern FILE *xolng;
extern FILE *xosht;
extern FILE *xosynn;
extern FILE *xosynt;
extern FILE *xrmd;
extern FILE *xrml;
extern FILE *xrmp;
extern FILE *xrms;
extern FILE *xvchk;
extern FILE *xvsynn;
extern FILE *xvsynt;
extern FILE *xoqual;
extern FILE *xoqualo;
extern FILE *xvprep;
extern BOOLEAN do_encrypt;
extern int cline;
extern char fname[];
extern char error[];
extern int msg_no;
extern int verb_no;
extern int room_no;
extern int obj_no;
extern int str_no;
extern int isev;
extern BOOLEAN list;
extern BOOLEAN defin;
extern BOOLEAN flt;
extern BOOLEAN islow;
extern BOOLEAN ishigh;
extern BOOLEAN isinit;
extern BOOLEAN isfirst;
extern BOOLEAN islast;
extern BOOLEAN gotip;
extern BOOLEAN update;
extern int prterr;
#endif


