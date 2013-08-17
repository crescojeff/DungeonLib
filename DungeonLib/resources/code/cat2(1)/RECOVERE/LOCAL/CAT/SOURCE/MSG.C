#include <stdio.h>
#include <string.h>

#include "defines.h"

#define MSG TRUE

#include "funcs.h"
#include "globals.h"

static char txt[2000]="";
static char id[80]="";
static BOOLEAN got_txt= FALSE;
static BOOLEAN got_id= FALSE;

void msgtxt(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (!got_txt)
      {
         if (strlen(txt)!=0)
            strcat(txt," ");
         strcat(txt, token);
      }
   }
   else
   {
      if (got_txt)
         warning(0,"M_",id, "Excess text ignored.");
      else
      {
         encrypt(txt,TRUE);
         got_txt= TRUE;
      }
   }
}

void msg(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (got_id)
      {
         sprintf(error, "Excess id (%s) ignored.", token);
         warning(0,"M_",id, error);
      }
      else
      {
         strcpy(id, token);
         got_id= TRUE;
      }
   }
}

void endmsg(token)
char *token;
{
   char line[80];
   char def[80];
   
   if (strcmp(token,"@END")==0)
   {
      if (strlen(id)==0)
      {
         sprintf(id, "%05d", msg_no+1);
         sprintf(error, "Identifier (%s) generated.", id);
         warning(0,"M_",id,error);
      }
      
      if (strlen(txt)==0)
         warning(0,"M_",id,"Blank text added.");
         
      if (update)
      {
         sprintf(line, "#define M_%s %d\n", id, msg_no+1);
         prterr=fprintf(xdef, line);
      }
      sprintf(def, "M_%s", id);
      m_def(def);
      
      if (strlen(txt)>254)
         warning(0,"M_",id,"Text is over 254 characters - portable?");
         
      if (update)
      {
         prterr=fprintf(xmsg,"   \"");
         if (strlen(txt))
            prterr=fprintf(xmsg,txt);
         else
            prterr=fprintf(xmsg," ");
         prterr=fprintf(xmsg,"\",\n");
         if (prterr<0)
            diskfull();
      }

      ++msg_no;
      got_txt= FALSE;
      got_id= FALSE;
      id[0]= '\0';
      txt[0]='\0';
   }
}
