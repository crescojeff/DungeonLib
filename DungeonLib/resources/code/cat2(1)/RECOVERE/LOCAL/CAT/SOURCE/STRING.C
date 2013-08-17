#include <stdio.h>
#include <string.h>

#include "defines.h"

#define STRING TRUE

#include "funcs.h"
#include "globals.h"

static char txt[2000]="";
static char id[80]="";
static char size[80]="";
static BOOLEAN got_txt= FALSE;
static BOOLEAN got_id= FALSE;
static BOOLEAN got_size= FALSE;

void strtxt(token)
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
         warning(0,"S_",id, "Excess string text ignored.");
      else
      {
         got_txt= TRUE;
         encrypt(txt,FALSE);
      }
   }
}

void str(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (got_id)
      {
         sprintf(error, "Excess id (%s) ignored.", token);
         warning(0,"S_",id, error);
      }
      else
      {
         strcpy(id, token);
         got_id= TRUE;
      }
   }
}

void strsize(token)
char *token;
{
   int i;
   
   if (strcmp(token,"@END"))
   {
      if (!all_digits(token))
      {
         sprintf(error, "Invalid string size (%s) ignored.", token);
         warning(0,"S_",id, error);
      }
      else
      {
         i= atoi(token);
         if ( (i<1) || (i>254))
         {
            sprintf(error, "Invalid string size (%s) ignored.", token);
            warning(0,"S_",id, error);
         }
         else
         {
            strcpy(size, token);
            got_size= TRUE;
         }
      }
   }
}

void endstr(token)
char *token;
{
   char def[80];
   int i;
   FILE *fp;
   
   if (strcmp(token,"@END")==0)
   {
      if (strlen(id)==0)
      {
         sprintf(id, "%05d", str_no+1);
         sprintf(error, "Identifier (%s) generated.", id);
         warning(0,"S_",id,error);
      }
      
      if (strlen(txt)==0)
         warning(1,"S_",id,"Blank text added.");
         
      if (!got_size)
      {
         strcpy(size, "254");
         sprintf(error, "String defaulted to size of 254.");
         warning(1,"S_",id,error);
      }
         
      i= atoi(size);
      if (strlen(txt)>i)
      {
         txt[i]='\0';
         sprintf(error, "String truncated to %d characters.", i);
         warning(0,"S_",id,error);
      }
      
      sprintf(def, "S_%s", id);
      m_def(def);

      if (update)
      {
         fp= fopenx("e1.x", "a");
         fprintf(fp, "   strp[%d]= u_s%d;\n", str_no+1, str_no+1);
         fprintf(fp, "   strcpy(strp[%d],\"%s\");\n", str_no+1, txt);
         fprintf(fp, "   decrypt(strp[%d]);\n", str_no+1);
         fclose(fp);
            
         fprintf(xdef, "#define S_%s %d\n", id, str_no+1);
         fprintf(xdef, "#ifdef INIT\n");
         fprintf(xdef, "char u_s%d[%s+1];\n", str_no+1, size);
         fprintf(xdef, "#else\n");
         fprintf(xdef, "extern char u_s%d[];\n", str_no+1);
         prterr= fprintf(xdef, "#endif\n");
      
         if (prterr<0)
            diskfull();
      }

      ++str_no;
      got_txt= FALSE;
      got_id= FALSE;
      got_size= FALSE;
      id[0]= '\0';
      txt[0]='\0';
      size[0]='\0';
   }
}

