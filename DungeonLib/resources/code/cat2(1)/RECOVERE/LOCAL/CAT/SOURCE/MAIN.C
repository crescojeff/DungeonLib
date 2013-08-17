#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "defines.h"

#define MAIN TRUE

#include "funcs.h"
#include "globals.h"

#ifdef PC
#include <dir.h>
#include <alloc.h>
#endif

#include <stdio.h>
#include <errno.h>

#ifdef PC
#include <dos.h>
#include <conio.h>
#endif
#ifdef ST
#include <osbind.h>
#endif

struct dict_list
{
   char dname[41];
   struct dict_list *next;
};

struct name_list
{
   char fname[80];
   struct name_list *next;
};

static struct dict_list  *f_dict= NULL, *l_dict= NULL, *t_dict= NULL;

static char dest[100]="csource";
static char gensrc[100]="\\cat\\gensrc";

static BOOLEAN compress=FALSE;

/* This routine returns a keypress from the keyboard and exits */

void fexit()
{
#ifdef PC
   char c;

   printf("Press a key to exit.\n");
   c= bdos(7,0,0);
   if (c==0)
   {
      c= bdos(7,0,0);
   }
#endif
#ifdef ST
   int c;
   printf("Press a key to exit.\n");
   c=(Crawcin());
#endif
   exit(1);
}

void diskfull()
{
   printf("Sorry, the disk is full.\n");
   fexit();
}

FILE * fopenx(name,modes)
char *name, *modes;
{
   FILE *w;
   char wrk[80];
   
   if (update)
   {
      strcpy(wrk,dest);
      strcat(wrk,"\\");
      strcat(wrk,name);
      w= fopen(wrk,modes);
      if (w)
         return(w);
      printf("Error when trying to open \"%s\".\n", wrk);
      fexit();
   }
   else
      return(NULL);
}

void do_compress(s)
char *s;
{
   int idx=0;
   
   t_dict= f_dict;
   while (t_dict)
   {
      ++idx;
      if (strcmp(t_dict->dname,s)==0)
      {
      	 sprintf(s,"~%x~", idx);
         return;
      }
      t_dict= t_dict->next;
   }
  
   t_dict= (struct dict_list *) malloc(sizeof(struct dict_list));
   sprintf(t_dict->dname,s);
   t_dict->next= NULL;
   if (f_dict==NULL)
      f_dict= t_dict;
   else
      l_dict->next= t_dict;
   l_dict= t_dict;
   sprintf(s,"~%x~", idx+1);
}

void crypt(s)
char *s;
{
   static char *code1="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
   static char *code2="qazwsxedcrfvtgbyhnujmikolpMNBVCXZQWERTYUIOPGHJKLFDSA";
   
   int i=0;
   char *p;
   
   while (s[i])
   {
      p= strchr(code1,s[i]);
      if (p)
         s[i]= code2[p-code1];
      ++i;
   }
}

void encrypt(s,cmp)
char *s;
BOOLEAN cmp;
{
   static char buf[2000]="";
   char tw[100];
   int j=0;
   int i=0;
   
   /* Now we'll add extra chars to manage " and \ properly. */
   
   while (s[i])         /* Watch out for " and \ */
   {
      if ( (s[i]=='\"') || (s[i]=='\\') )
         buf[j++]= '\\';
      if (s[i]=='%')
         buf[j++]= '%';
      if (s[i]=='~')	/* special - for compression! */
         s[i]='^';
      buf[j++]= s[i];
      ++i;
   }
   buf[j]='\0';
   strcpy(s,buf);
   
   if (do_encrypt)
      crypt(s);

   /* Now we'll compress the words into the dictionary */
   
   if ((cmp) && (compress))
   {
      i=0;
      buf[0]='\0';
      while (s[i])
      {
         while ((s[i]) && (!isalpha(s[i])))
         {
            buf[strlen(buf)+1]='\0';
            buf[strlen(buf)]=s[i++];
         }
         if (s[i])
         {
            j=0;
            tw[j]='\0';
            while (isalpha(s[i])) 
               tw[j++]=s[i++];
            tw[j]='\0';
            if ((strlen(tw)<=40) && (strlen(tw)>4))
            {
               do_compress(tw);
               if (do_encrypt)
                  crypt(tw);
            }
            strcat(buf,tw);
         }
      }
      strcpy(s,buf);
   }
}

void upper(s)
char *s;
{
   while (*s)
   {
      if (islower(*s))
         *s=toupper(*s);
      ++s;
   }
}

void lower(s)
char *s;
{
   while (*s)
   {
      if (isupper(*s))
         *s=tolower(*s);
      ++s;
   }
}

void warning(sev,pfx,obj,s)
int sev;
char *pfx;
char *obj;
char *s;
{
   int i;
   char wname[80];
   char *w;

   strcpy(wname, fname);
   w= wname;
   while (strchr(w,'\\')!=NULL)
      w= strchr(w,'\\')+1;
      
   if (sev<=isev)
   {
      for (i=0; i<79; i++) printf("=");
      printf("\n");  
      printf("***** <<<<< FILE:%s @LINE:%05d ITEM:%s%s >>>>>\n", w, cline, pfx, obj);
      printf("***** %s\n",s);
      genout= fopen("GENOUT.TXT","a");
      for (i=0; i<79; i++) prterr=fprintf(genout,"=");
      prterr=fprintf(genout,"\n");  
      prterr=fprintf(genout,"***** <<<<< FILE:%s @LINE:%05d ITEM:%s%s >>>>>\n", w, cline, pfx, obj);
      prterr=fprintf(genout,"***** %s\n",s);
      fclose(genout);
      if (prterr<0)
         diskfull();
   }  
}

void cpyf(file)
char *file;
{
   char f[80];
   char buf[1024];
   FILE *fp1, *fp2;
   int cnt;
   
   strcpy(f, gensrc);
   strcat(f, "\\");
   strcat(f,file);
   
   if ((fp1=fopen(f,"r"))==NULL)
   {
      printf("Cannot find \"%s\" to autocopy.\n", f);
      return;
   }
   
   fp2= fopenx(file,"w");
   
   printf("Autocopying \"%s\" to \"%s\".\n", f, dest);
   
   while ((cnt=fread(&buf[0],1,1024,fp1))!=0)
   {
      fwrite(&buf[0],1,cnt,fp2);
   }
   
   fclose(fp1);
   fclose(fp2);
}

main(argc,argv)
int argc;
char *argv[];
{
   int i, rs;
   BOOLEAN eof;
   BOOLEAN autoc= FALSE;
   char *token;
   BOOLEAN enc= FALSE;
   FILE *wrk;
   char wf[80];
   struct name_list  *f_name= NULL, *l_name= NULL, *t_name= NULL;

   printf("*********************************\n");
   printf("*    The C Adventure Toolkit    *\n");
   printf("*          Version 2.00         *\n");
   printf("*           August '91          *\n");
   printf("*                               *\n");
   printf("*        (c) Tony Stiles        *\n");
   printf("*********************************\n\n");

   m_use("M_MORE");
   m_use("M_BAD_LOAD");
   m_use("M_PLAY_AGAIN");
   m_use("M_TOO_DARK");
   m_use("M_DEAF_EARS");
   m_use("M_SCORED");
   m_use("M_IN");
   m_use("M_TURNS");
   m_use("M_PRESS_A_KEY");
   m_use("M_IT_CONTAINS");
   m_use("M_NOTHING");
   m_use("M_BE_MORE_SPECIFIC");
   m_use("M_DARKNESS");
   m_use("M_DISK_ERROR");
   m_use("M_DISK_FULL");
   m_use("M_EMPTY_HANDS");
   m_use("M_FILE_NOT_FOUND");
   m_use("M_GET_FILE_NAME");
   m_use("M_IT_IS_ALIGHT");
   m_use("M_IT_IS_OPEN");
   m_use("M_IT_IS_CLOSED");
   m_use("M_IT_IS_DARK");
   m_use("M_IT_IS_LOCKED");
   m_use("M_OBJECT_WORN");
   m_use("M_NO");
   m_use("M_NOTHING_UNUSUAL");
   m_use("M_NOUN_NOT_FOUND");
   m_use("M_NO_COMMAND");
   m_use("M_NO_OBVIOUS_EXITS");
   m_use("M_NO_PATH");
   m_use("M_OBJECT_CARRIED");
   m_use("M_OBJECT_NOT_GOT");
   m_use("M_OBJECT_NOT_HERE");
   m_use("M_OBJECT_NOT_WORN");
   m_use("M_OBVIOUS_EXITS");
   m_use("M_OPERATION_COMPLETE");
   m_use("M_WHAT_NOW");
   m_use("M_YES");
   m_use("M_YOU_ARE");
   m_use("M_YOU_ARE_CARRYING");
   m_use("M_YOU_ARE_WEARING");
   m_use("M_YOU_CAN_SEE");
   m_use("O_ALL");
   m_use("O_THEM");
   m_use("O_ME");
   m_use("V_DOWN");
   m_use("V_EAST");
   m_use("V_NORTH");
   m_use("V_NORTHEAST");
   m_use("V_NORTHWEST");
   m_use("V_SOUTH");
   m_use("V_SOUTHEAST");
   m_use("V_SOUTHWEST");
   m_use("V_UP");
   m_use("V_WEST");
   m_use("V_LEAVE");
   m_use("V_ENTER");
   m_use("V_FROM");
   m_use("M_YES_CHARS");
   m_use("M_NO_CHARS");
   m_use("M_WHICH_ONE");
   m_use("R_NOWHERE");
   m_use("O_EXCEPT");
   m_use("M_NO_RAM_LOAD");
   m_use("M_NO_RAM_SAVE");
   m_use("M_AND");
         
   for (i=1; i<argc; i++)
   {
      upper(argv[i]);
      if (strcmp(argv[i],"-C")==0)
         compress= TRUE;
      else if (strcmp(argv[i],"-R")==0)
         update= FALSE;
      else if (strcmp(argv[i],"-L")==0)
         list= TRUE;
      else if (strcmp(argv[i],"-V")==0)
         isev= 1;
      else if (strcmp(argv[i],"-I")==0)
         defin= TRUE;  
      else if (strcmp(argv[i],"-E")==0)
         enc= TRUE;
      else if (strncmp(argv[i],"-A",2)==0)
      {
         autoc= TRUE;
         if (strlen(argv[i])>2)
            strcpy(gensrc,argv[i]+2);
      }
      else if (strncmp(argv[i],"-S",2)==0)
         strcpy(source,&argv[i][2]);
      else if (strncmp(argv[i],"-D",2)==0)
         strcpy(dest,&argv[i][2]);
      else if (strcmp(argv[i],"-F")==0)
         flt= TRUE;
      else
      {
         printf("\nValid switches are:\n-I tem list\n-L ist source\n-E ncrypt\n");
         printf("-V erbose\n-S ource pathname\n-F ull logic tests\n");
         printf("-R eport only - no update\n-D estination pathname\n");
         printf("-A uto copy of GENSRC from \\CAT\\GENSRC\n");
         printf("                (or optional pathname)\n");
         printf("-C ompression   (slower but smaller games!)\n\n");
         fexit();
      }  
   }  

   upper(source);
   
   if ((strlen(source)>1) && (source[1]==':'))
   {
      printf("Source path cannot include a drive spec.\n");
      fexit();
   }
  
   if (chdir(source))
   {
      printf("Cannot find source pathname \"%s\".\n", source);
      fexit();
   }

   if ((wrk=fopen("genlist","r"))==NULL)
   {
      printf("Cannot find \"GENLIST\" in \"%s\".\n", source);
      fexit();
   }
   
   if ((genout=fopen("GENOUT.TXT","w"))==NULL)
   {
      printf("Cannot open disk file. Is disk write protected?\n");
      fexit();
   }
   
   prterr=fprintf(genout,"*********************************\n");
   prterr=fprintf(genout,"*    The C Adventure Toolkit    *\n");
   prterr=fprintf(genout,"*          Version 2.00         *\n");
   prterr=fprintf(genout,"*           August '91          *\n");
   prterr=fprintf(genout,"*                               *\n");
   prterr=fprintf(genout,"*        (c) Tony Stiles        *\n");
   prterr=fprintf(genout,"*********************************\n\n");
   if (prterr<0)
      diskfull();
   
   while (fgets(wf,80,wrk))
   {
      if (strlen(wf))
      {
      	 upper(wf);
      	 if (wf[strlen(wf)-1]=='\n')
      	    wf[strlen(wf)-1]='\0';
      	 if (strlen(wf))
      	 {
            if (strcmp(wf,"-C")==0)
               compress= TRUE;
            else if (strcmp(wf,"-R")==0)
               update= FALSE;
            else if (strcmp(wf,"-L")==0)
               list= TRUE;
            else if (strcmp(wf,"-V")==0)
               isev= 1;
            else if (strcmp(wf,"-I")==0)
               defin= TRUE;  
            else if (strcmp(wf,"-E")==0)
               enc= TRUE;
            else if (strncmp(wf,"-A",2)==0)
            {
               autoc= TRUE;
               if (strlen(wf)>2)
                  strcpy(gensrc,wf+2);
            }
            else if (strncmp(wf,"-D",2)==0)
               strcpy(dest,wf+2);
            else if (strcmp(wf,"-F")==0)
               flt= TRUE;
            else
            {
               t_name= (struct name_list *) malloc(sizeof(struct name_list));
               strcpy(t_name->fname,wf);
               t_name->next= NULL;
               if (f_name==NULL)
                  f_name= t_name;
               else
                  l_name->next= t_name;
               l_name= t_name;
            }  
         }
      }
   }
   fclose(wrk);
   
   if (dest[strlen(dest)-1]=='\\')
      dest[strlen(dest)-1]='\0';
   
   if (gensrc[strlen(gensrc)-1]=='\\')
      gensrc[strlen(gensrc)-1]='\0';

   upper(dest);
   upper(gensrc);

   if (update==FALSE)
   {
      printf("******** REPORT ONLY RUN ********\n\n");
      fprintf(genout,"******** REPORT ONLY RUN ********\n\n");
   }
   printf("Source folder is \"%s\".\n", source);
   fprintf(genout,"Source folder is \"%s\".\n", source);
   if (update)
   {
      printf("Destination folder is \"%s\".\n", dest);
      fprintf(genout,"Destination folder is \"%s\".\n", dest);
   }
   if ((autoc) && (update))
   {
      printf("Autocopying is enabled from \"%s\".\n", gensrc);
      fprintf(genout,"Autocopying is enabled from \"%s\".\n", gensrc);
   }
   if ((enc) && (update))
   {
      printf("Encryption is enabled.\n");
      fprintf(genout,"Encryption is enabled.\n");
   }
   if ((compress) && (update))
   {
      printf("Compression is enabled.\n");
      fprintf(genout,"Compression is enabled.\n");
   }
   if ((!compress) && (update))
   {
      printf("Compression is disabled.\n");
      fprintf(genout,"Compression is disabled.\n");
   }
   if (defin)
   {
      printf("Item list is enabled.\n");
      fprintf(genout,"Item list is enabled.\n");
   }
   if (isev)
   {
      printf("Verbose mode is enabled.\n");
      fprintf(genout,"Verbose mode is enabled.\n");
   }
   if (list)
   {
      printf("Source listing is enabled.\n");
      fprintf(genout,"Source listing is enabled.\n");
   }
   if (flt)
   {
      printf("Full logic checking is enabled.\n");
      fprintf(genout,"Full logic checking is enabled.\n");
   }

   printf("\n");
   fprintf(genout,"\n");
      
   fclose(genout);
   
   if (update)
      open_files();
   
   if (enc)
      p_token("@ENCRYPT");

   /* Define standard strings */
   
   p_token("@STR");
   p_token("S1");
   p_token("@STRSIZE");
   p_token("200");
   p_token("@ENDSTR");
   
   p_token("@STR");
   p_token("S2");
   p_token("@STRSIZE");
   p_token("200");
   p_token("@ENDSTR");
   
   p_token("@STR");
   p_token("S3");
   p_token("@STRSIZE");
   p_token("100");
   p_token("@ENDSTR");
   
   p_token("@STR");
   p_token("S4");
   p_token("@STRSIZE");
   p_token("100");
   p_token("@ENDSTR");
   
   p_token("@STR");
   p_token("S5");
   p_token("@STRSIZE");
   p_token("100");
   p_token("@ENDSTR");
   
   p_token("@STR");
   p_token("S6");
   p_token("@STRSIZE");
   p_token("100");
   p_token("@ENDSTR");
   
   p_token("@STR");
   p_token("S7");
   p_token("@STRSIZE");
   p_token("50");
   p_token("@ENDSTR");
   
   p_token("@STR");
   p_token("S8");
   p_token("@STRSIZE");
   p_token("50");
   p_token("@ENDSTR");
   
   p_token("@STR");
   p_token("S9");
   p_token("@STRSIZE");
   p_token("50");
   p_token("@ENDSTR");
   
   p_token("@STR");
   p_token("S10");
   p_token("@STRSIZE");
   p_token("50");
   p_token("@ENDSTR");
   
   /* Define NOWHERE as a room! */
   
   p_token("@ROOM");
   p_token("NOWHERE");
   p_token("@ROOMSHT");
   p_token("Nowhere!");
   p_token("@ENDROOM");
             
   while (f_name!=NULL)
   {
      do
      {
         token= get_token(f_name->fname, &eof);
         if (token)
            p_token(token);
      } while (!eof);
      t_name= f_name->next;
      free(f_name);
      f_name=t_name;
   }
   
   if (!gotip)
   {
      sprintf(error,"WARNING!! No current player defined in INIT logic- @BECOME.",token);
      warning(0,"","LOGIC", error);
   }
   
   p_token("@END");

   if (update)
   {
      t_dict= f_dict;
      xdict= fopenx("a.dic","a");
      while (t_dict)
      {
         fprintf(xdict, "   \"%s\",\n", t_dict->dname);
         l_dict= t_dict;
         t_dict= t_dict->next;
         free(l_dict);
      }
      fclose(xdict);
   }
      
   pdef();
   puse();
   freelink();
   
   rs= 0;
   rs+= 23*sizeof(int)*(obj_no+1);
   rs+= 4* sizeof(int)*(room_no+1);
   rs+= 500*sizeof(int);
   rs+= 4*sizeof(int);
   rs+= 1000;

   if (update)
      fprintf(xdef,"#define RSIZE %d\n", rs);
   
   if (update)
      close_files();
   
   if ((autoc)&&(update))
   {
      cpyf("portab.i");
      cpyf("a.c");
      cpyf("b.c");
      cpyf("c.c");
      cpyf("d.c");
      cpyf("z.c");
      cpyf("xlang.h");
      cpyf("xfuncs.h");
      cpyf("xglobals.h");
   }
   
   fexit();
}
