#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifdef PC
#include <dos.h>
#include <conio.h>
#endif
#ifdef ST
#include <osbind.h>
#endif

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

void getkey()
{
   int i;
#ifdef PC
   char c;

      fprintf(stderr,"<Press a key to continue, or q to quit>");
      fflush(stderr);
      c= bdos(7,0,0);
      if (c==0)
         c= bdos(7,0,0);
#endif
#ifdef ST
   int c;
  
      fprintf(stderr,"<Press a key to continue, or q to quit>");
      fflush(stdout);
      c=(Crawcin());
#endif
      for (i=0; i<39; i++)
         fprintf(stderr,"\b");
      for (i=0; i<39; i++)
         fprintf(stderr," ");
      for (i=0; i<39; i++)
         fprintf(stderr,"\b");
         
     if ((c=='q') || (c=='Q'))
        exit(1);
}

void pline(s)
char *s;
{
   static int l=0;
   
   if (l==24)
   {
      l=0;
      getkey();
   }
   ++l;
   if (strlen(s)>80)
      printf("%80.80s",s);
   else
      printf(s);
}

main(argc,argv)
int argc;
char *argv[];
{
   FILE *fp;
   int i;
   char *p;
   char buf1[100];
   char buf2[100];
   
   if (argc<2) 
   {
      fprintf(stderr,"You must enter a search key.\n");
      getkey();
      exit(1);
   }
   
   if ((fp=fopen("catman.txt","r"))==NULL)
   {
      if ((fp=fopen("\\catman.txt","r"))==NULL)
      {
         if ((fp=fopen("\\cat\\catman.txt","r"))==NULL)
         {
            if ((fp=fopen("\\catsrc\\catman.txt","r"))==NULL)
            {
               fprintf(stderr,"Cannot find Xref manual at any of\n\n");
               fprintf(stderr,".\\CATMAN.TXT\n");
               fprintf(stderr,"\\CATMAN.TXT\n");
               fprintf(stderr,"\\CAT\\CATMAN.TXT\n");
               fprintf(stderr,"\\CATSRC\\CATMAN.TXT\n");
               getkey();
               exit(1);
            }
         }
      } 
   }
   
   for (i=1; i<argc; i++)
      upper(argv[i]);
      
   while (fgets(buf1,100,fp))
   {
      if ((buf1[0]=='*') && (buf1[1]=' '))
      {
         strcpy(buf2,buf1);
         upper(buf2);
         p= strchr(buf2+1,'*');
         if (p)
           *(p+1)='\0';
         for (i=1; i<argc; i++)
            if (strstr(buf2,argv[i]))
            {
               fgets(buf2,100,fp);
               pline(buf2);
               pline(buf1);
               pline(buf2);
               while (fgets(buf1,100,fp))
               {
                  if (strncmp(buf1,
                        "****************************************",40)==0)
                     break;
                  pline(buf1);
               }
               break;
            }
      }
   }
   fclose(fp);
   getkey();
}
