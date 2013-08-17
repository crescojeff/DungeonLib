/*	Martyn Dryden's GEM AES functions for CAT 11-08-91	*/
/*      ....slightly amended by Tony Stiles                     */
/*
	WARNING
	The use of this file may make your adventure incompatible
	with C compilers throughout the known universe.

	Designed only for use with the Atari ST
*/

#ifndef PC		/* Default to ST generation */
#ifndef ST
#define ST 1
#endif
#endif

#include "xdef.h"	/* Include CAT header files */
#include "xlang.h"
#include "xfuncs.h"
#include "xglobals.h"

#ifdef ST
#include <osbind.h>
#endif

/* graf_mouse() constants */
#define ARROW 0
#define HIDE_M 256
#define SHOW_M 257

#ifdef ST
static char *buffer; 
static char bufp[32256]="";
static char default_path[64]="", fspec[80]="";
char *screen;
int dummy;
#endif

/* Initialise the AES (and other things) */
void init_aes()
{
#ifdef ST	
   appl_init();

   default_path[0]=Dgetdrv()+'A';
   default_path[1]=':';
   Dgetpath(&default_path[2],0);

   /* Create buffer for screen save */
   buffer= &bufp[0];
   
   /* Make sure it's on a page boundary */
   if ( (long) buffer & 0xFF )
      buffer=buffer+(0x100 - (long)buffer & 0xFF );

   /* Set up pointer to normal screen */
   screen = (char *)Logbase();
#endif	
}

/* Allow CAT to find out whether GEM is available */
gem_avail()
{
#ifndef ST
   return(FALSE);
#else	
   return(TRUE);
#endif	
}

/* Hide the mouse */
void mseoff()
{
#ifdef ST	
   graf_mouse(ARROW,&dummy);
   graf_mouse(HIDE_M,&dummy);
#endif	
}

/* Show the mouse */
void mseon()
{
#ifdef ST	
   graf_mouse(SHOW_M,&dummy);
   graf_mouse(ARROW,&dummy);
#endif	
}

/* End AES */
void end_aes()
{
#ifdef ST
   appl_exit();   
#endif
}

/* Display a GEM File Selector and get a filename   */
/* Returns 1 if successful, 0 if cancelled          */
/* Chosen filespec is in global string fspec       */
file_select()
{
#ifdef ST   
   int fs_button, i;
   char fs_path[64], fs_fname[16];

   Fattrib("START123.SAV",1,2); /* Hide our system file */
   strcpy( fs_path, default_path );
   strcat( fs_path, "\\*.SAV" );
   strcpy( fs_fname, "");

   /* Copy current screen to buffer */
   memcpy(buffer,screen,32000);

   /* Display buffer instead of normal screen */
   Setscreen( buffer, buffer, -1 );

   /* Do the File Selector */
   mseon();
   fsel_input(fs_path, fs_fname, &fs_button);
   mseoff();

   /* Display normal screen again */
   Setscreen( screen, screen, -1 );

   if (fs_button)
   {
      /* Start building the output filespec */
      strcpy( fspec, fs_path );
      trunname( fspec );

      /* Remember the user's chosen path for next time */
      strcpy( default_path, fspec );
      default_path[ strlen(default_path) - 1 ] = '\0';

      /* Chop user's extn off & put ours on */
      for( i=1 ; i<strlen(fs_fname) ; i++ )
         if( fs_fname[i] == '.' ) fs_fname[i] = '\0';
            strcat( fs_fname, ".SAV" );

      /* Add filename to chosen path - all done! */
      strcat( fspec, fs_fname );
         return( 1 );
   }
   else 
      return( 0 );
#endif   
}

/* Chop off everything after the last backslash   */
trunname(string)
char *string;
{
#ifdef ST   
   int i;

   for( i=strlen(string) ; i >=0 ; --i )
      if( string[i] == '\\' ) break;
         string[i+1]=0;
#endif   
}

/* Game save routine that calls file_select() */
void xsave()
{
#ifdef ST   
   FILE *f= NULL;
   int i=0, j=0, k=0;
   int ok, button, test=1;

   while (odet[i][0] != -1) ++i;
   while (rmd[j][0] != -1) ++j;
   test= i*j+1782;

   if( file_select() )
   {
      ok = Fsfirst( fspec, 0x003F );
      if( ok == 0 )
      {
         mseon();
         button = form_alert( 1, "[1][  |  File exists!  |  OK to replace?  |  ][ Cancel |  OK  ]" );
         mseoff();
         if (button==2) ok = 1;
            if (ok==0)
            {
               PMSG(M_CANCELLED);
               return;
            }
      }
      
      if (script) prn_out(fspec);
      f=fopen(fspec, "wb");

      if (f==NULL)
      {
         PMSG(M_DISK_ERROR);
         PMSG(M_DISK_FULL);
         return;
      }
      PMSG(M_SAVING);
      ftext( fspec );

      fwrite(&test,sizeof(int),1,f);
      fwrite(&odet[0][0],sizeof(int),i*23,f);
      fwrite(&rmd[0][0],sizeof(int),j*4,f);
      fwrite(&cnt[0],sizeof(int),500,f);
      fwrite(&score,sizeof(int),1,f);
      fwrite(&cplr,sizeof(int),1,f);
      fwrite(&player,sizeof(int),1,f);
    
      for (k=0; k<2; k++)
      {
         encrypt(strp[k]);
         fwrite(strp[k],200,1,f);
         decrypt(strp[k]);
      }
      for (k=2; k<6; k++)
      {
         encrypt(strp[k]);
         fwrite(strp[k],100,1,f);
         decrypt(strp[k]);
      }
      for (k=6; k<10; k++)
      {
         encrypt(strp[k]);
         fwrite(strp[k],50,1,f);
         decrypt(strp[k]);
      }
   	
      if (fwrite(&turns,sizeof(int),1,f)==0)
      {
         fclose(f);
         unlink(fspec);
         PMSG(M_DISK_ERROR);
         PMSG(M_DISK_FULL);
         return;
      }
      else
      {
         fclose(f);
         PMSG(M_OPERATION_COMPLETE);
      }
   }
   else
      PMSG(M_CANCELLED);
#endif   
}

void xload()
{
#ifdef ST   
   FILE *f= NULL;
   int i=0, j=0, k;
   int test;

   while (odet[i][0] != -1) ++i;
   while (rmd[j][0] != -1) ++j;

   if ( file_select() )
   {
      if (script) prn_out(fspec);
      f = fopen(fspec, "rb");
      if (f==NULL)
      {
         form_alert( 1, "[1][  |  File not found  |  ][ Sheesh! ]" );
   	 PMSG(M_FAILED);
         return;
      }
      PMSG(M_LOADING);
      ftext( fspec );
      fread(&test,sizeof(int),1,f);
      if (test!=(int) i*j+1782)
      {
         form_alert( 1, "[1][  |  File read error  |  ][ Sheesh! ]" );
   	 PMSG(M_FAILED);
   	 fclose(f);
   	 return;
      }
      fread(&odet[0][0],sizeof(int),i*23,f);
      fread(&rmd[0][0],sizeof(int),j*4,f);
      fread(&cnt[0],sizeof(int),500,f);
      fread(&score,sizeof(int),1,f);
      fread(&cplr,sizeof(int),1,f);
      fread(&player,sizeof(int),1,f);

      for (k=0; k<2; k++)
      {
         fread(strp[k],200,1,f);
         decrypt(strp[k]);
      }
      for (k=2; k<6; k++)
      {
         fread(strp[k],100,1,f);
         decrypt(strp[k]);
      }
      for (k=6; k<10; k++)
      {
         fread(strp[k],50,1,f);
         decrypt(strp[k]);
      }
      fread(&turns,sizeof(int),1,f);

      if (ferror(f))
      {
         form_alert( 1, "[1][  |  File read error  |  ][ Sheesh! ]" );
   	 PMSG(M_DISK_ERROR);
      }
      else
         PMSG(M_OPERATION_COMPLETE);

      fclose(f);
   } else 
   	PMSG(M_CANCELLED);
#endif
}
