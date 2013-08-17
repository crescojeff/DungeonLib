#include <stdio.h>
#include <string.h>

#include "defines.h"

#define TOKEN TRUE

#include "funcs.h"
#include "globals.h"

static BOOLEAN force_do= FALSE;

void p_token(token)
char *token;
{
   char cap_token[80];
   
   static int omode=0;
   int mode, do_mode;
   
   /* Does the token specify an operating mode? */

   mode=0;
   strcpy(cap_token, token);
   upper(cap_token);
   
   if ((strcmp(cap_token,"@END")==0) || (strcmp(cap_token,"\0")==0))
      mode=M_END;
   else if (strcmp(cap_token,"@REM")==0)
      mode=M_REM;
   else if (strcmp(cap_token,"@VERB")==0)
      mode=M_VERB;
   else if (strcmp(cap_token,"@VERBCHK")==0)
      mode=M_VERBCHK;
   else if (strcmp(cap_token,"@VERBPREP")==0)
      mode=M_VERBPREP;
   else if (strcmp(cap_token,"@VERBLGT")==0)
      mode=M_VERBLGT;
   else if (strcmp(cap_token,"@VERBSYN")==0)
      mode=M_VERBSYN;
   else if (strcmp(cap_token,"@ENDVERB")==0)
      mode=M_ENDVERB;
   else if (strcmp(cap_token,"@MSG")==0)
      mode=M_MSG;
   else if (strcmp(cap_token,"@MSGTXT")==0)
      mode=M_MSGTXT;
   else if (strcmp(cap_token,"@ENDMSG")==0)
      mode=M_ENDMSG;
   else if (strcmp(cap_token,"@ROOM")==0)
      mode=M_ROOM;
   else if (strcmp(cap_token,"@ROOMSHT")==0)
      mode=M_ROOMSHT;
   else if (strcmp(cap_token,"@ROOMLNG")==0)
      mode=M_ROOMLNG;
   else if (strcmp(cap_token,"@ROOMDRK")==0)
      mode=M_ROOMDRK;
   else if (strcmp(cap_token,"@ROOMPTH")==0)
      mode=M_ROOMPTH;
   else if (strcmp(cap_token,"@ROOMPNT")==0)
      mode=M_ROOMPNT;
   else if (strcmp(cap_token,"@ENDROOM")==0)
      mode=M_ENDROOM;
   else if (strcmp(cap_token,"@OBJ")==0)
      mode=M_OBJ;
   else if (strcmp(cap_token,"@OBJSHT")==0)
      mode=M_OBJSHT;
   else if (strcmp(cap_token,"@OBJLNG")==0)
      mode=M_OBJLNG;
   else if (strcmp(cap_token,"@OBJSYN")==0)
      mode=M_OBJSYN;
   else if (strcmp(cap_token,"@OBJWGT")==0)
      mode=M_OBJWGT;
   else if (strcmp(cap_token,"@OBJVAL")==0)
      mode=M_OBJVAL;
   else if (strcmp(cap_token,"@OBJSTR")==0)
      mode=M_OBJSTR;
   else if (strcmp(cap_token,"@OBJROOM")==0)
      mode=M_OBJROOM;
   else if (strcmp(cap_token,"@OBJINRM")==0)
      mode=M_OBJINRM;
   else if (strcmp(cap_token,"@OBJDOOR")==0)
      mode=M_OBJDOOR;
   else if (strcmp(cap_token,"@OBJPORTAL")==0)
      mode=M_OBJPORTAL;
   else if (strcmp(cap_token,"@OBJPLR")==0)
      mode=M_OBJPLR;
   else if (strcmp(cap_token,"@OBJCMD")==0)
      mode=M_OBJCMD;
   else if (strcmp(cap_token,"@OBJACT")==0)
      mode=M_OBJACT;
   else if (strcmp(cap_token,"@OBJWEAR")==0)
      mode=M_OBJWEAR;
   else if (strcmp(cap_token,"@OBJWORN")==0)
      mode=M_OBJWORN;
   else if (strcmp(cap_token,"@OBJHIDE")==0)
      mode=M_OBJHIDE;
   else if (strcmp(cap_token,"@OBJEAT")==0)
      mode=M_OBJEAT;
   else if (strcmp(cap_token,"@OBJDRINK")==0)
      mode=M_OBJDRINK;
   else if (strcmp(cap_token,"@OBJLCK")==0)
      mode=M_OBJLCK;
   else if (strcmp(cap_token,"@OBJLGT")==0)
      mode=M_OBJLGT;
   else if (strcmp(cap_token,"@OBJLIT")==0)
      mode=M_OBJLIT;
   else if (strcmp(cap_token,"@OBJNGT")==0)
      mode=M_OBJNGT;
   else if (strcmp(cap_token,"@OBJREAD")==0)
      mode=M_OBJREAD;
   else if (strcmp(cap_token,"@OBJPNT")==0)
      mode=M_OBJPNT;
   else if (strcmp(cap_token,"@OBJKEY")==0)
      mode=M_OBJKEY;
   else if (strcmp(cap_token,"@ENDOBJ")==0)
      mode=M_ENDOBJ;
   else if (strcmp(cap_token,"@STR")==0)
      mode=M_STR;
   else if (strcmp(cap_token,"@STRSIZE")==0)
      mode=M_STRSIZE;
   else if (strcmp(cap_token,"@STRTXT")==0)
      mode=M_STRTXT;
   else if (strcmp(cap_token,"@ENDSTR")==0)
      mode=M_ENDSTR;
   else if (strcmp(cap_token,"@IF")==0)
      mode=M_IF;
   else if (strcmp(cap_token,"@LC")==0)
      mode=M_LC;
   else if (strcmp(cap_token,"@WHILE")==0)
      mode=M_WHILE;
   else if (strcmp(cap_token,"@ELSE")==0)
   {
      force_do= TRUE;
      mode=M_ELSE;
   }
   else if (strcmp(cap_token,"@ENDIF")==0)
   {
      force_do = TRUE;
      mode=M_ENDIF;
   }
   else if (strcmp(cap_token,"@WEND")==0)
   {
      force_do= TRUE;
      mode=M_WEND;
   }
   else if (strcmp(cap_token,"@DO")==0)
      mode=M_DO;
   else if (strcmp(cap_token,"@HIGH")==0)
   {
      force_do= TRUE;
      mode=M_HIGH;
   }
   else if (strcmp(cap_token,"@LOW")==0)
   {
      force_do= TRUE;
      mode=M_LOW;
   }
   else if (strcmp(cap_token,"@INIT")==0)
   {
      force_do= TRUE;
      mode=M_INIT;
   }
   else if (strcmp(cap_token,"@FIRST")==0)
   {
      force_do= TRUE;
      mode=M_FIRST;
   }
   else if (strcmp(cap_token,"@LAST")==0)
   {
      force_do= TRUE;
      mode=M_LAST;
   }
   else if (strcmp(cap_token,"@ENCRYPT")==0)
   {
      mode=M_ENCRYPT;
      if (update)
         fprintf(xdef,"#define DECRYPT TRUE\n\n");
   }
   
   /* Ensure that all modes are closed properly */
   
   if ( (mode != 0) && (omode!=0) )
   {
      token= "@END";
      strcpy(cap_token,token);
   }
   
   do_mode=omode;
   
   if (mode!=0)
      omode= mode;
      
   switch (do_mode)
   {
      case M_REM:
         /* Gobble all remark tokens - unless we find a command! */
         if (((cap_token[0]=='@') || (cap_token[0]=='_')) 
                                              && (strlen(cap_token)>1))
            ldo(cap_token);
         break;
      case M_VERB:
         verb(cap_token);
         break;
      case M_VERBCHK:
         verbchk(cap_token);
         break;
      case M_VERBPREP:
         verbprep();
         break;
      case M_VERBLGT:
         verblgt();
         break;
      case M_VERBSYN:
         verbsyn(cap_token);
         break;
      case M_ENDVERB:
         endverb(cap_token);
         break;
      case M_MSG:
         msg(cap_token);
         break;
      case M_MSGTXT:
         msgtxt(token);
         break;
      case M_ENDMSG:
         endmsg(cap_token);
         break;
      case M_ROOM:
         room(cap_token);
         break;
      case M_ROOMSHT:
         roomsht(token);
         break;
      case M_ROOMLNG:
         roomlng(token);
         break;
      case M_ROOMDRK:
         roomdrk();
         break;
      case M_ROOMPTH:
         roompth(cap_token);
         break;
      case M_ROOMPNT:
         roompnt(cap_token);
         break;
      case M_ENDROOM:
         endroom(cap_token);
         break;
      case M_OBJ:
         obj(cap_token);
         break;
      case M_OBJSHT:
         objsht(token);
         break;
      case M_OBJLNG:
         objlng(token);
         break;
      case M_OBJSYN:
         objsyn(cap_token);
         break;
      case M_OBJWGT:
         objwgt(cap_token);
         break;
      case M_OBJVAL:
         objval(cap_token);
         break;
      case M_OBJSTR:
         objstr(cap_token);
         break;
      case M_OBJROOM:
         objroom(cap_token);
         break;
      case M_OBJDOOR:
         objdoor(cap_token);
         break;
      case M_OBJPORTAL:
         objportal(cap_token);
         break;
      case M_OBJINRM:
         objinrm(cap_token);
         break;
      case M_OBJPLR:
         objplr();
         break;
      case M_OBJCMD:
         objcmd();
         break;
      case M_OBJACT:
         objact();
         break;
      case M_OBJWEAR:
         objwear();
         break;
      case M_OBJWORN:
         objworn();
         break;
      case M_OBJHIDE:
         objhide();
         break;
      case M_OBJEAT:
         objeat(cap_token);
         break;
      case M_OBJDRINK:
         objdrink(cap_token);
         break;
      case M_OBJLCK:
         objlck(cap_token);
         break;
      case M_OBJLGT:
         objlgt();
         break;
      case M_OBJLIT:
         objlit();
         break;
      case M_OBJNGT:
         objngt();
         break;
      case M_OBJREAD:
         objread(cap_token);
         break;
      case M_OBJPNT:
         objpnt(cap_token);
         break;
      case M_OBJKEY:
         objkey(cap_token);
         break;
      case M_ENDOBJ:
         endobj(cap_token);
         break;
      case M_STR:
         str(cap_token);
         break;
      case M_STRSIZE:
         strsize(cap_token);
         break;
      case M_STRTXT:
         strtxt(token);
         break;
      case M_ENDSTR:
         endstr(cap_token);
         break;
      case M_IF:
         lif(cap_token);
         break;
      case M_LC:
         lc();
         break;
      case M_WHILE:
         lwhile(cap_token);
         break;
      case M_ELSE:
         lelse();
         break;
      case M_ENDIF:
         lendif();
         break;
      case M_WEND:
         lwend();
         break;
      case M_DO:
         ldo(cap_token);
         break;
      case M_HIGH:
         lhigh();
         break;
      case M_LOW:
         llow();
         break;
      case M_INIT:
         linit();
         break;
      case M_FIRST:
         lfirst();
         break;
      case M_LAST:
         llast();
         break;
      case M_ENCRYPT:
         do_encrypt= TRUE;
         break;
   }
}

char *get_token(file,eof)
char *file;
BOOLEAN *eof;
{
   static FILE *fp=NULL;
   static char *p=NULL;
   static char *got_rec;
   static char string[161];
   char *r;
   
   *eof= FALSE;
   
   if (force_do==TRUE)
   {
      force_do= FALSE;
      return("@DO");
   }
   
   if (fp==NULL)
   {
      fp=fopen(file,"r");
      if (fp==NULL)
      {
      	 sprintf(error, "Source file \"%s\" not found.", file);
      	 warning(0,"","FILES",error);
         *eof= TRUE;
         return(NULL);
      }
      else
      {
         strcpy(fname, file);
         cline= 0;
      }
   }
   
   if (got_rec==NULL)
   {
      got_rec= fgets(string, 160, fp);
      if (got_rec==NULL)
      {
         *eof= TRUE;
         fclose(fp);
         fp=NULL;
         return(NULL);
      }
      else
      {
         ++cline;
         string[strlen(string)-1]= '\0';
         if (list)
            printf("%s\n", string);
         p= string;
      }
   }
   
   p=strtok(p, " \t");
   r=p;
   if (p)
      p+= strlen(p)+1;
   else
      got_rec= NULL;
   return(r);
}
