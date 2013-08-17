#include <stdio.h>
#include <string.h>

#include "defines.h"

#define VERB TRUE

#include "funcs.h"
#include "globals.h"

static char id[80]="";
static char chk[80]="";
static char lgt[80]="";
static BOOLEAN got_id= FALSE;
static BOOLEAN got_chk= FALSE;
static BOOLEAN got_prep= FALSE;
static BOOLEAN got_lgt= FALSE;

void verbchk(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (got_chk)
      {
         sprintf(error, "Excess check (%s) ignored.", token);
         warning(0,"V_",id, error);
      }
      else
      {
         if ((strstr("NO_CHECK HERE CARRIED_NOT_WORN WORN ", token)!=NULL) ||
             (strstr("AVAIL AVAIL_NOT_WORN EXIST ", token)!=NULL)||
             (strstr("CARRIED NOT_CARRIED ",token)!=NULL))
         {
            strcpy(chk, token);
            got_chk= TRUE;
         }
         else
         {
            sprintf(error, "Unrecognised check (%s) ignored.", token);
            warning(0,"V_",id, error);
         }
      }
   }
}

void verbsyn(token)
char *token;
{
   char syn[80];
   char wrk[80];
   
   if (strcmp(token,"@END"))
   {
      strcpy(wrk,token);
      encrypt(wrk,FALSE);
      if (update)
      {
         sprintf(syn, "   \"%s\",\n", wrk);
         xvsynt= fopenx("w.c", "a"); 
         prterr=fprintf(xvsynt,syn);
         if (prterr<0)
            diskfull();
         fclose(xvsynt);
      
         if (got_prep)
         {
            xvprep= fopenx("u.c", "a");
            prterr=fprintf(xvprep, syn);
         fclose(xvprep);
         if (prterr<0)
            diskfull();
         }
            
         if (got_id)
         {
            sprintf(syn, "   V_%s,\n", id);
            xvsynt= fopenx("v.c", "a");
            prterr=fprintf(xvsynt,syn);
            if (prterr<0)
               diskfull();
            fclose(xvsynt);
         }
         else
         {
            sprintf(syn, "   %d,\n", verb_no+1);
            xvsynn= fopenx("v.c", "a");
            prterr=fprintf(xvsynn,syn);
            if (prterr<0)
               diskfull();
            fclose(xvsynn);
         }
      }
   }
}

void verb(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (got_id)
      {
         sprintf(error, "Excess id (%s) ignored.", token);
         warning(0,"V_",id, error);
      }
      else
      {
         strcpy(id, token);
         got_id= TRUE;
      }
   }
}

void verbprep()
{
   got_prep= TRUE;
}

void verblgt()
{
   got_lgt= TRUE;
}

void endverb(token)
char *token;
{
   char line[80];
   char def[80];
   
   if (strcmp(token,"@END")==0)
   {
      if (!got_id)
      {
         sprintf(id, "%05d", verb_no+1);
         sprintf(error, "Identifier (%s) generated.", id);
         warning(0,"V_",id,error); 
      }

      verbsyn(id);
      if (!got_chk)
         sprintf(chk, "NO_CHECK");
         
      if (got_lgt)
         sprintf(lgt, "NEED_LIGHT");
      else
         sprintf(lgt, "NO_LIGHT");
            
      if (update)
      {
         sprintf(line, "   VC_%s, %s,\n", chk, lgt);
         prterr=fprintf(xvchk,line);
      
         sprintf(line, "#define V_%s %d\n", id, verb_no+1);
         prterr=fprintf(xdef,line);
         
         if (prterr<0)
            diskfull();
      }
      
      sprintf(def, "V_%s", id);
      m_def(def);
      
      got_chk= FALSE;
      got_id= FALSE;
      got_prep= FALSE;
      got_lgt= FALSE;
      id[0]= '\0';
      chk[0]='\0';
      lgt[0]='\0';
      ++verb_no;
   }
}
