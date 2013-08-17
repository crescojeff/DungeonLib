#include "defines.h"

#define LCHECK TRUE

struct lt_struct
{
   char *name;
   BOOLEAN islow;
   BOOLEAN istest;
   BOOLEAN iscmd;
};

static struct lt_struct lt[]=
{
   "@INIT",		FALSE,	FALSE,	FALSE,
   "@LOW",		FALSE,	FALSE,	FALSE,
   "@HIGH",		FALSE,	FALSE,	FALSE,
   "@IF",		FALSE,	FALSE,	FALSE,		
   "@ELSE",		FALSE,	FALSE,	FALSE,
   "@ENDIF",		FALSE,	FALSE,	FALSE,
   "@WHILE",		FALSE,	FALSE,	FALSE,
   "@WEND",		FALSE,	FALSE,	FALSE,
   "@DO",		FALSE,	FALSE,	FALSE,
   "@LC",		FALSE,	TRUE,	TRUE,
   "@CARRIED_WEIGHT",	FALSE,	TRUE,	TRUE,
   "@COUNT",		FALSE,	TRUE,	TRUE,
   "@CPLAYER",		FALSE,	TRUE,	TRUE,
   "@FIRSTOB",		FALSE,	TRUE,	TRUE,
   "@LASTOB",		FALSE,	TRUE,	TRUE,
   "@MSGNO",		FALSE,	TRUE,	TRUE,
   "@OBJINRM",		FALSE,	TRUE,	TRUE,
   "@OBJKEY",		FALSE,	TRUE,	TRUE,
   "@OBJLCK",		FALSE,	TRUE,	TRUE,
   "@OBJNO",		FALSE,	TRUE,	TRUE,
   "@OBJRM",		FALSE,	TRUE,	TRUE,
   "@PLAYER",		FALSE,	TRUE,	TRUE,
   "@POINTS",		FALSE,	TRUE,	TRUE,
   "@RANDOM",		FALSE,	TRUE,	TRUE,
   "@ROOMNO",		FALSE,	TRUE,	TRUE,
   "@SCORE",		FALSE,	TRUE,	TRUE,
   "@SIZE",		FALSE,	TRUE,	TRUE,
   "@STRENGTH",		FALSE,	TRUE,	TRUE,
   "@THISROOM",		FALSE,	TRUE,	TRUE,
   "@TURNS",		FALSE,	TRUE,	TRUE,
   "@LOCKTYPE",		FALSE,	TRUE,	TRUE,
   "@VALUE",		FALSE,	TRUE,	TRUE,
   "@VERBPATH",		FALSE,	TRUE,	TRUE,
   "@WEIGHT",		FALSE,	TRUE,	TRUE,
   "@THISCOBJ",		TRUE,	TRUE,	TRUE,
   "@THISCVERB",	TRUE,	TRUE,	TRUE,
   "@THISOBJ",		TRUE,	TRUE,	TRUE,
   "@THISVERB",		TRUE,	TRUE,	TRUE,
   "@CHECK",		FALSE,	TRUE,	FALSE,
   "@CONFIRM",		FALSE,	TRUE,	FALSE,
   "@CPLAYERIS",	FALSE,	TRUE,	FALSE,
   "@ISACTIVE",		FALSE,	TRUE,	FALSE,
   "@ISAVAIL",		FALSE,	TRUE,	FALSE,
   "@ISBOX",		FALSE,	TRUE,	FALSE,
   "@ISCARRIED",	FALSE,	TRUE,	FALSE,
   "@ISCARRIEDANY",	FALSE,	TRUE,	FALSE,
   "@ISCARRIEDBY",	FALSE,	TRUE,	FALSE,
   "@ISCLOSED",		FALSE,	TRUE,	FALSE,
   "@ISCOMMANDABLE",	FALSE,	TRUE,	FALSE,
   "@ISDARK",		FALSE,	TRUE,	FALSE,
   "@ISDRINKABLE",	FALSE,	TRUE,	FALSE,
   "@ISEDIBLE",		FALSE,	TRUE,	FALSE,
   "@ISEXIT",		FALSE,	TRUE,	FALSE,
   "@ISHERE",		FALSE,	TRUE,	FALSE,
   "@ISHIDDEN",		FALSE,	TRUE,	FALSE,
   "@ISIN",		FALSE,	TRUE,	FALSE,
   "@ISLIGHT",		FALSE,	TRUE,	FALSE,
   "@ISLIT",		FALSE,	TRUE,	FALSE,
   "@ISLOCKED",		FALSE,	TRUE,	FALSE,
   "@ISMOVABLE",	FALSE,	TRUE,	FALSE,
   "@ISOPEN",		FALSE,	TRUE,	FALSE,
   "@ISPATH",		FALSE,	TRUE,	FALSE,
   "@ISPLAYER",		FALSE,	TRUE,	FALSE,
   "@ISREADABLE",	FALSE,	TRUE,	FALSE,
   "@ISWEARABLE",	FALSE,	TRUE,	FALSE,
   "@ISWITH",		FALSE,	TRUE,	FALSE,
   "@ISWORN",		FALSE,	TRUE,	FALSE,
   "@ISWORNANY",	FALSE,	TRUE,	FALSE,
   "@ISWORNBY",		FALSE,	TRUE,	FALSE,
   "@OBJHASL",		FALSE,	TRUE,	FALSE,
   "@OBJROOMIS",	FALSE,	TRUE,	FALSE,
   "@PLAYERIS",		FALSE,	TRUE,	FALSE,
   "@ROOMIS",		FALSE,	TRUE,	FALSE,
   "@CNOUNIS",		TRUE,	TRUE,	FALSE,
   "@CNOUNNOIS",	TRUE,	TRUE,	FALSE,
   "@CVERBIS",		TRUE,	TRUE,	FALSE,
   "@CVERBNOIS",	TRUE,	TRUE,	FALSE,
   "@ISCOMPOUND",	TRUE,	TRUE,	FALSE,
   "@NOUNIS",		TRUE,	TRUE,	FALSE,
   "@NOUNNOIS",		TRUE,	TRUE,	FALSE,
   "@VERBIS",		TRUE,	TRUE,	FALSE,
   "@VERBNOIS",		TRUE,	TRUE,	FALSE,
   "EQ",		FALSE,	TRUE,	FALSE,
   "==",		FALSE,	TRUE,	FALSE,
   "NE",		FALSE,	TRUE,	FALSE,
   "!=",		FALSE,	TRUE,	FALSE,
   "LT",		FALSE,	TRUE,	FALSE,
   "<",			FALSE,	TRUE,	FALSE,
   "LE",		FALSE,	TRUE,	FALSE,
   "<=",		FALSE,	TRUE,	FALSE,
   "GT",		FALSE,	TRUE,	FALSE,
   ">",			FALSE,	TRUE,	FALSE,
   "GE",		FALSE,	TRUE,	FALSE,
   ">=",		FALSE,	TRUE,	FALSE,
   "OR",		FALSE,	TRUE,	FALSE,
   "||",		FALSE,	TRUE,	FALSE,
   "AND",		FALSE,	TRUE,	FALSE,
   "&&",		FALSE,	TRUE,	FALSE,
   "NOT",		FALSE,	TRUE,	FALSE,
   "!",			FALSE,	TRUE,	FALSE,
   "@ADDCOMMAND",	FALSE,	FALSE,	TRUE,
   "@TOROOM",		FALSE,	FALSE,	TRUE,
   "@SETPOINTS",	FALSE,	FALSE,	TRUE,
   "@ADDPOINTS",	FALSE,	FALSE,	TRUE,
   "@SUBPOINTS",	FALSE,	FALSE,	TRUE,
   "@SETCOUNT",		FALSE,	FALSE,	TRUE,
   "@ADDCOUNT",		FALSE,	FALSE,	TRUE,
   "@SUBCOUNT",		FALSE,	FALSE,	TRUE,
   "@ADDSCORE",		FALSE,	FALSE,	TRUE,
   "@SETSCORE",		FALSE,	FALSE,	TRUE,
   "@SUBSCORE",		FALSE,	FALSE,	TRUE,
   "@ADDPLAYER",	FALSE,	FALSE,	TRUE,
   "@ADDSTRENGTH",	FALSE,	FALSE,	TRUE,
   "@ADDVALUE",		FALSE,	FALSE,	TRUE,
   "@ADDWEIGHT",	FALSE,	FALSE,	TRUE,
   "@BECOME",		FALSE,	FALSE,	TRUE,
   "@BRIEF",		FALSE,	FALSE,	TRUE,
   "@CLOSE",		FALSE,	FALSE,	TRUE,
   "@CONTROL",		FALSE,	FALSE,	TRUE,
   "@DRINK",		FALSE,	FALSE,	TRUE,
   "@DROP",		FALSE,	FALSE,	TRUE,
   "@EAT",		FALSE,	FALSE,	TRUE,
   "@ENDCHAR",		FALSE,	FALSE,	TRUE,
   "@ENDGAME",		FALSE,	FALSE,	TRUE,
   "@ENTER",		FALSE,	FALSE,	TRUE,
   "@GET",		FALSE,	FALSE,	TRUE,
   "@GOTO",		FALSE,	FALSE,	TRUE,
   "@HIDE",		FALSE,	FALSE,	TRUE,
   "@INVENTORY",	FALSE,	FALSE,	TRUE,
   "@KILL",		FALSE,	FALSE,	TRUE,
   "@LF",		FALSE,	FALSE,	TRUE,
   "@LIGHT",		FALSE,	FALSE,	TRUE,
   "@LOAD",		FALSE,	FALSE,	TRUE,
   "@LOCK",		FALSE,	FALSE,	TRUE,
   "@LOOK",		FALSE,	FALSE,	TRUE,
   "@MAKEDARK",		FALSE,	FALSE,	TRUE,
   "@MAKELIGHT",	FALSE,	FALSE,	TRUE,
   "@NEWLINE",		FALSE,	FALSE,	TRUE,
   "@OPEN",		FALSE,	FALSE,	TRUE,
   "@PAUSE",		FALSE,	FALSE,	TRUE,
   "@PCONTENTS",	FALSE,	FALSE,	TRUE,
   "@PEXITS",		FALSE,	FALSE,	TRUE,
   "@PMSG",		FALSE,	FALSE,	TRUE,
   "@POBJL",		FALSE,	FALSE,	TRUE,
   "@POBJS",		FALSE,	FALSE,	TRUE,
   "@PROOML",		FALSE,	FALSE,	TRUE,
   "@PROOMS",		FALSE,	FALSE,	TRUE,
   "@PNUM",		FALSE,	FALSE,	TRUE,
   "@PVAL",		FALSE,	FALSE,	TRUE,
   "@READ",		FALSE,	FALSE,	TRUE,
   "@REMOVE",		FALSE,	FALSE,	TRUE,
   "@REMOVECOMMAND",	FALSE,	FALSE,	TRUE,
   "@REMOVEPLAYER",	FALSE,	FALSE,	TRUE,
   "@REVIVE",		FALSE,	FALSE,	TRUE,
   "@SAVE",		FALSE,	FALSE,	TRUE,
   "@SCRIPT",		FALSE,	FALSE,	TRUE,
   "@SETSTRENGTH",	FALSE,	FALSE,	TRUE,
   "@SETVALUE",		FALSE,	FALSE,	TRUE,
   "@SETWEIGHT",	FALSE,	FALSE,	TRUE,
   "@SUBSTRENGTH",	FALSE,	FALSE,	TRUE,
   "@SUBVALUE",		FALSE,	FALSE,	TRUE,
   "@SUBWEIGHT",	FALSE,	FALSE,	TRUE,
   "@SWAP",		FALSE,	FALSE,	TRUE,
   "@UNHIDE",		FALSE,	FALSE,	TRUE,
   "@UNLIGHT",		FALSE,	FALSE,	TRUE,
   "@UNLOCK",		FALSE,	FALSE,	TRUE,
   "@UNSCRIPT",		FALSE,	FALSE,	TRUE,
   "@VERBOSE",		FALSE,	FALSE,	TRUE,
   "@VOCAB",		FALSE,	FALSE,	TRUE,
   "@WAITKEY",		FALSE,	FALSE,	TRUE,
   "@WEAR",		FALSE,	FALSE,	TRUE,
   "@WHOAMI",		FALSE,	FALSE,	TRUE,
   "@CONT",		TRUE,	FALSE,	TRUE,
   "@FVERB",		TRUE,	FALSE,	TRUE,
   "@STOP",		TRUE,	FALSE,	TRUE,
   "+",			FALSE,	TRUE,	TRUE,
   "-",			FALSE,	TRUE,	TRUE,
   "/",			FALSE,	TRUE,	TRUE,
   "*",		 	FALSE,	TRUE,	TRUE,
   "%",			FALSE,	TRUE,	TRUE,
   "NO_KEY",		FALSE,	TRUE,	FALSE,
   "NO_LOCK",		FALSE,	TRUE,	FALSE,
   "LOCKED",		FALSE,	TRUE,	FALSE,
   "CLOSED",		FALSE,	TRUE,	FALSE,
   "OPEN",		FALSE,	TRUE,	FALSE,
   "@NEED_LIGHT",	FALSE,	TRUE,	TRUE,
   "@NO_LIGHT",		FALSE,	TRUE,	TRUE,
   "@STRNO",		FALSE,	TRUE,	TRUE,
   "@ROOMSEEN",		FALSE,	TRUE,	FALSE,
   "@PSTR",		FALSE,	FALSE,	TRUE,
   "@GETSTR",		FALSE,	FALSE,	TRUE,
   "@STRCAT",		FALSE,	FALSE,	TRUE,
   "@STRCLR",		FALSE,	FALSE,	TRUE,
   "@STRUPP",		FALSE,	FALSE,	TRUE,
   "@STRLOW",		FALSE,	FALSE,	TRUE,
   "@MSGTOSTR",		FALSE,	FALSE,	TRUE,
   "@OSTOSTR",		FALSE,	FALSE,	TRUE,
   "@OLTOSTR",		FALSE,	FALSE,	TRUE,
   "@RSTOSTR",		FALSE,	FALSE,	TRUE,
   "@RLTOSTR",		FALSE,	FALSE,	TRUE,
   "@STRCPY",		FALSE,	FALSE,	TRUE,
   "@STRADDC",		FALSE,	FALSE,	TRUE,
   "@STRPCPY",		FALSE,	FALSE,	TRUE,
   "@NUMTOSTR",		FALSE,	FALSE,	TRUE,
   "@STRCAP",		FALSE,	FALSE,	TRUE,
   "@STRLEN",		FALSE,	TRUE,	TRUE,
   "@STRFCHR",		FALSE,	TRUE,	TRUE,
   "@STRFSTR",		FALSE,	TRUE,	TRUE,
   "@STRASC",		FALSE,	TRUE,	TRUE,
   "@STRCMP",		FALSE,	TRUE,	TRUE,
   "@STRNUM",		FALSE,	TRUE,	TRUE,
   "@RAMSAVE",		FALSE,	FALSE,	TRUE,
   "@RAMLOAD",		FALSE,	FALSE,	TRUE,
   "",			FALSE,	TRUE,	FALSE
};

BOOLEAN lcheck(token,islow,istest,iscmd)
char *token;
BOOLEAN *islow, *istest, *iscmd;
{
   register i=0;

   if (all_digits(token))
   {
      *islow=  FALSE;
      *iscmd=  TRUE;
      *istest= TRUE;
      return TRUE;
   }

   while (lt[i].name[0]!='\0')
   {
      if (strcmp(token,lt[i].name)==0)
      {
         *islow= lt[i].islow;
         *istest= lt[i].istest;
         *iscmd= lt[i].iscmd;
         return TRUE;
      }
      ++i;
   }

   *islow=  FALSE;
   *istest= FALSE;
   *iscmd=  FALSE;
   return FALSE;

}

