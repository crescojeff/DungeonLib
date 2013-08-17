#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifdef PC
#include <alloc.h>
#endif

#include "defines.h"

#define MTEST 1
#define MCMD  2

struct u_struct
{
   char token[41];
   struct u_struct *next;
};

static struct u_struct *f_use= NULL, *l_use= NULL;
static struct u_struct *f_def= NULL, *l_def= NULL;

static int ifl=0, whilel=0;
static BOOLEAN inif= FALSE, inwhile= FALSE;

#define LOGIC TRUE

#include "funcs.h"
#include "globals.h"

static int ind=3;

void freelink()
{
   struct u_struct *wp;
   
   while (f_def!=NULL)
   {
      wp= f_def->next;
      free(f_def);
      f_def= wp;
   }
   
   while (f_use!=NULL)
   {
      wp= f_use->next;
      free(f_use);
      f_use= wp;
   }
}  

BOOLEAN isused(token)
char *token;
{
   struct u_struct *t_use;
   
   t_use= f_use;
   while (t_use != NULL)
   {
      if (strcmp(t_use->token,token)==0)
         return TRUE;
      t_use= t_use->next;
   }
   return FALSE;
}

BOOLEAN isdef(token)
char *token;
{
   struct u_struct *t_def;
   
   t_def= f_def;
   while (t_def != NULL)
   {
      if (strcmp(t_def->token,token)==0)
         return TRUE;
      t_def= t_def->next;
   }
   return FALSE;
}

void m_use(token)
char *token;
{
   struct u_struct *t_use;
   
   if ( (strncmp(token,"O_",2)==0) ||
        (strncmp(token,"V_",2)==0) ||
        (strncmp(token,"R_",2)==0) ||
        (strncmp(token,"S_",2)==0) ||
        (strncmp(token,"M_",2)==0) )
      if (!isused(token))
      {
        if ((t_use=(struct u_struct *)malloc(sizeof(struct u_struct)))==NULL)
        {
            printf("Memory allocation error - aborting\n");
            fexit();
         }
         strncpy(t_use->token, token, 40);
         t_use->next= NULL;
         if (f_use==NULL)
         {
            f_use= t_use;
            l_use= t_use;
         }
         else
         {
            l_use->next= t_use;
            l_use= l_use->next;
         }
      }
}

void m_def(token)
char *token;
{
   struct u_struct *t_def;
   
   if ( (strncmp(token,"O_",2)==0) ||
        (strncmp(token,"V_",2)==0) ||
        (strncmp(token,"R_",2)==0) ||
        (strncmp(token,"S_",2)==0) ||
        (strncmp(token,"M_",2)==0) )
      if (!isdef(token))
      {
        if ((t_def=(struct u_struct *)malloc(sizeof(struct u_struct)))==NULL)
        {
            printf("Memory allocation error - aborting\n");
            fexit();
         }
         strncpy(t_def->token, token, 40);
         t_def->next= NULL;
         if (f_def==NULL)
         {
            f_def= t_def;
            l_def= t_def;
         }
         else
         {
            l_def->next= t_def;
            l_def= l_def->next;
         }
      }
      else
      {
         sprintf(error, "Redefinition of (%s).", token);
         warning(0,"",token, error);
      }
}

void pdef()
{
   struct u_struct *t_def;
   
   t_def= f_def;
   
   genout= fopen("GENOUT.TXT","a");
   if (defin)
   {
      printf("\n\nThe following are defined\n");
      printf("=========================\n\n");
      prterr=fprintf(genout,"\n\nThe following are defined\n");
      prterr=fprintf(genout,"=========================\n\n");
      while (t_def != NULL)
      {
         printf("%-40s", t_def->token);
         prterr=fprintf(genout,"%-40s", t_def->token);
         if (!isused(t_def->token))
         {
            printf("NOT USED");
            prterr=fprintf(genout,"NOT USED");
         }
         printf("\n");
         prterr=fprintf(genout,"\n");
         t_def= t_def->next;
      }
   }
   else
   {
      printf("\n\nThe following are defined, but not directly used\n");
      printf("================================================\n\n");
      prterr=fprintf(genout,"\n\nThe following are defined, but not directly used\n");
      prterr=fprintf(genout,"================================================\n\n");
      while (t_def != NULL)
      {
         if (!isused(t_def->token))
         {
            printf(t_def->token);
            printf("\n");
            prterr=fprintf(genout,t_def->token);
            prterr=fprintf(genout,"\n");
         }
         t_def= t_def->next;
      }
   }
   if (prterr<0)
      diskfull();
   fclose(genout);
}

void puse()
{
   struct u_struct *t_use;
   
   genout= fopen("GENOUT.TXT", "a");
   t_use= f_use;
   printf("\n\nThe following are used, but not defined\n");
   printf("=======================================\n\n");
   prterr=fprintf(genout,"\n\nThe following are used, but not defined\n");
   prterr=fprintf(genout,"=======================================\n\n");
   while (t_use != NULL)
   {
      if (!isdef(t_use->token))
      {
         printf("%-40s", t_use->token);
         printf("\n");
         prterr=fprintf(genout,"%-40s", t_use->token);
         prterr=fprintf(genout,"\n");
      }
      t_use= t_use->next;
   }
   fclose(genout);
   if (prterr<0)
      diskfull();
}

BOOLEAN all_digits(token)
char *token;
{
   while (*token)
   {
      if ( (!isdigit(*token)) && (*token!='-') && (*token!='+') )
         return(FALSE);
      ++token;
   }
   return(TRUE);
}

char *parse(token,mode,open,close)
char *token;
int mode;
int *open, *close;
{
   int i;
   static char wrk[100]="";
   char wrk2[100]="";
   char use[100]="";
   char pfx[3]="";
   char *p;
   char s;
   BOOLEAN blow, btest, bcmd;

   for (i=0; i<100; i++)
      wrk[i]= '\0';
 
   do
   {
      p= strpbrk(token, "(,)*+-%/");
      s= '\0';
      if (p)
      {
         s= *p;
         if (s=='(') ++*open;
         if (s==')') ++*close;
         *p= '\0';
      }

      if (strlen(token))
      {
         if ( (strcmp(token,"@BECOME")==0) && (isinit) )
            gotip= TRUE;
      
         if (token[0]=='_')
         {
            lower(token);
            sprintf(error, "Using external C function (%s).", token+1);
            warning(0,"","LOGIC",error);
         }
         
         else if ( (flt) && ((strlen(pfx)==0)||(token[0]=='@')) )
         {
            if (lcheck(token,&blow,&btest,&bcmd)==FALSE)
            {
               sprintf(error,"Don't recognise (%s) as a logic token.",token);
               warning(0,"","LOGIC",error);
            }
            else
            {
               if ((!islow) && (blow==TRUE))
               {
                  sprintf(error,
                    "Low pty logic token (%s) not in low pty logic.", token);
                  warning(0,"","LOGIC",error);
               }
               if ((mode==MTEST) && (btest!=TRUE))
               {
                  sprintf(error,
                    "Token (%s) is not valid in logic test.", token);
                  warning(0,"","LOGIC",error);
               }
               if ((mode==MCMD) && (bcmd!=TRUE))
               {
                  sprintf(error,
                    "Logic test token (%s) appears in do logic.", token);
                  warning(0,"","LOGIC",error);
               }
            }
         }
            
         if ( (token[0]=='@') || (token[0]=='_') )
         {
            if (token[0]=='_')
            {
               strcpy(wrk2,token+1);
               upper(wrk2);
            }
            else
               strcpy(wrk2,token+1);
            strcat(wrk2," ");
            if ( (strstr(wrk2,"ROOM")!=NULL) ||
                 (strstr(wrk2,"GOTO")!=NULL) ||
                 (strstr(wrk2,"MAKE")!=NULL) ||
                 (strstr(wrk2,"RSTOSTR")!=NULL) ||
                 (strstr(wrk2,"RLTOSTR")!=NULL) ||
                 (strstr(wrk2,"FIRSTOB")!=NULL) ||
                 (strstr(wrk2,"LASTOB")!=NULL) )
               strcpy(pfx, "R_");
            else if (strstr(wrk2,"VERB")!=NULL)
               strcpy(pfx, "V_");
            else if (strstr(wrk2,"CHECK")!=NULL)
               strcpy(pfx, "VC_");
            else if (strstr(wrk2,"MSG")!=NULL)
               strcpy(pfx, "M_");
            else if ( (strstr(wrk2,"STR")!=NULL) &&
                                        (strstr(wrk2,"STRENGTH")==NULL) &&
                                        (strstr(wrk2,"TOSTR")==NULL))
               strcpy(pfx, "S_");
            else
               strcpy(pfx, "O_");
            strcat(wrk, token+1);
            if ( (strcmp(token+1,"LIGHT")==0) ||
                 (strcmp(token+1,"OPEN")==0) ||
                 (strcmp(token+1,"RANDOM")==0) ||
                 (strcmp(token+1,"PLAYER")==0) )
               strcat(wrk, "_");
         }
         else
         {
            strcpy(use, "");
            if ( (token[0]!='\'') && (token[0]!='\"') && (!all_digits(token)) )
            {
               strcat(wrk, pfx);
               strcat(use, pfx);
               pfx[0]='\0';
            }
            strcat(wrk, token);
            strcat(use, token);
            m_use(use);
         }
      }

      if (p)
      {
         wrk[strlen(wrk)]=s;
         token+= strlen(token)+1;
         if ((s==',')||(s=='+')||(s=='-')||(s=='/')||(s=='*')||(s=='%'))
            strcpy(pfx, "O_");
      }
      else
         token= NULL;

   } while (token);
   return(&wrk[0]);
}

void indent()
{
   int i;
   char wname[80];
   char *w, *p;

   strcpy(wname, fname);
   w= wname;
   while (strchr(w,'\\')!=NULL)
      w= strchr(w,'\\')+1;
   p= (strchr(w,(int) '.'));
   if (p)
      *p='\0';
      
   if (update)
   {
      fprintf(xlogic, "/* %-8s %-5d */ ", w, cline);
      for (i=0; i<ind; i++)
         prterr=fprintf(xlogic, " ");
      if (prterr<0)
         diskfull();
   }
}

void lif(token)
char *token;
{
   static char wrk[200]="";
   static int open=0, close=0;

   if (strcmp(token,"@END"))
   {
      if (strlen(wrk)!=0)
         strcat(wrk, " ");
      token= parse(token,MTEST,&open,&close);
      strcat(wrk, token);
   }
   else
   {
      inif= TRUE;
      ifl= 0;
      indent();
      if (update)
      {
         prterr=fprintf(xlogic, "if (%s)\n", wrk);
         indent();
         prterr=fprintf(xlogic, "{\n");
         if (prterr<0)
            diskfull();
      }
      ind+= 3;
      wrk[0]='\0';
      if (open>close)
      {
         sprintf(error, "%d closing brace(s) missing.", open-close);
         warning(0,"","LOGIC",error);
      }
      if (open<close)
      {
         sprintf(error, "%d opening brace(s) missing.", close-open);
         warning(0,"","LOGIC",error);
      }
      open=0;
      close=0;
   }
}

void lwhile(token)
char *token;
{
   static char wk[200]="";
   static int open=0, close=0;
   
   if (strcmp(token,"@END"))
   {
      if (strlen(wk)!=0)
         strcat(wk, " ");
      token= parse(token,MTEST,&open,&close);
      strcat(wk, token);
   }
   else
   {
      inwhile= TRUE;
      whilel= 0;
      indent();
      if (update)
      {
         prterr=fprintf(xlogic, "while (%s)\n", wk);
         indent();
         prterr=fprintf(xlogic, "{\n");
         if (prterr<0)
            diskfull();
      }
      ind+= 3;
      wk[0]='\0';
      if (open>close)
      {
         sprintf(error, "%d closing brace(s) missing.", open-close);
         warning(0,"","LOGIC",error);
      }
      if (open<close)
      {
         sprintf(error, "%d opening brace(s) missing.", close-open);
         warning(0,"","LOGIC",error);
      }
      open=0;
      close=0;
   }
}

void lelse()
{
   ind-= 3;
   ifl= 0;
   indent();
   if (update)
   {
      prterr=fprintf(xlogic, "}\n");
      indent();
      prterr=fprintf(xlogic, "else\n");
      indent();
      prterr=fprintf(xlogic, "{\n");
      if (prterr<0)
         diskfull();
   }
   ind+= 3;
}

void lendif()
{
   ind-= 3;
   indent();
   if (ifl==0)
      warning(0,"","LOGIC","Empty @IF logic.");
   if (update)
   {
      prterr=fprintf(xlogic, "}\n");
      if (prterr<0)
         diskfull();
   }
}

void lwend()
{
   ind-= 3;
   indent();
   if (whilel==0)
      warning(0,"","LOGIC","Empty @WHILE logic.");
   if (update)
   {
      prterr=fprintf(xlogic, "}\n");
      if (prterr<0)
         diskfull();
   }
}

void ldo(token)
char *token;
{
   static int open=0, close=0;
   
   if ( (strcmp(token,"@END")!=0) && (strcmp(token,"@ENDDO")!=0) ) 
   {
      indent();
      token= parse(token,MCMD,&open,&close);
      if (update)
      {
         prterr=fprintf(xlogic,"%s;\n", token);
         if (prterr<0)
            diskfull();
      }
      if (inif)
         ++ifl;
      if (inwhile) 
         ++whilel;
      if (open>close)
      {
         sprintf(error, "%d closing brace(s) missing.", open-close);
         warning(0,"","LOGIC", error);
      }
      if (open<close)
      {
         sprintf(error, "%d opening brace(s) missing.", close-open);
         warning(0,"","LOGIC", error);
      }
      open=0;
      close=0;
   }
}

void lhigh()
{
   if (!ishigh)
   {
      if (update)
      {
         fclose(xlogic);
         xlogic= fopenx("f.c","a");
      }
      ishigh= TRUE;
      islow= FALSE;
      isinit= FALSE;
      isfirst= FALSE;
      islast= FALSE;
   }
   if (ind>3)
      warning(0,"","LOGIC", "Mismatched @IF/@WHILE found.");
   if (ind<3)
      warning(0,"","LOGIC", "Mismatched @ENDIF/@WEND found.");
   ind=3;
}

void llow()
{
   if (!islow)
   {
      if (update)
      {
         fclose(xlogic);
         xlogic= fopenx("g.c","a");
      }
      islow= TRUE;
      ishigh= FALSE;
      isinit= FALSE;
      isfirst= FALSE;
      islast= FALSE;
   }
   if (ind>3)
      warning(0,"","LOGIC", "Mismatched @IF/@WHILE found.");
   if (ind<3)
      warning(0,"","LOGIC", "Mismatched @ENDIF/@WEND found.");
   ind=3;
}

void linit()
{
   if (!isinit)
   {
      if (update)
      {
         fclose(xlogic);
         xlogic= fopenx("e.c","a");
      }
      isinit= TRUE;
      islow= FALSE;
      ishigh= FALSE;
      isfirst= FALSE;
      islast= FALSE;
   }
   if (ind>3)
      warning(0,"","LOGIC", "Mismatched @IF/@WHILE found.");
   if (ind<3)
      warning(0,"","LOGIC", "Mismatched @ENDIF/@WEND found.");
   ind=3;
}

void lfirst()
{
   if (!isfirst)
   {
      if (update)
      {
         fclose(xlogic);
         xlogic= fopenx("e2.x","a");
      }
      isinit= FALSE;
      islow= FALSE;
      ishigh= FALSE;
      isfirst= TRUE;
      islast= FALSE;
   }
   if (ind>3)
      warning(0,"","LOGIC", "Mismatched @IF/@WHILE found.");
   if (ind<3)
      warning(0,"","LOGIC", "Mismatched @ENDIF/@WEND found.");
   ind=3;
}

void llast()
{
   if (!islast)
   {
      if (update)
      {
         fclose(xlogic);
         xlogic= fopenx("e3.x","a");
      }
      isinit= FALSE;
      islow= FALSE;
      ishigh= FALSE;
      isfirst= FALSE;
      islast= TRUE;
   }
   if (ind>3)
      warning(0,"","LOGIC", "Mismatched @IF/@WHILE found.");
   if (ind<3)
      warning(0,"","LOGIC", "Mismatched @ENDIF/@WEND found.");
   ind=3;
}

void lc()
{
   if (ind>3)
      warning(0,"","LOGIC", "Mismatched @IF/@WHILE found.");
   if (ind<3)
      warning(0,"","LOGIC", "Mismatched @ENDIF/@WEND found.");
   ind=3;
}


