/**************************************************************************/
/* C sample player code for Master sound player - Tony Stiles August 1991 */
/* Suitable to Mastersound format samples, (and some others?)             */
/**************************************************************************/
/* This code should be fully portable between C compilers on the ST. It   */
/* has been tested on Sozobon C and MWC. It doesn't use any assembler or  */
/* anything horrendous like that - so porting should be a doddle!         */
/*									  */
/* As it stands, the code can handle samples up to 65535 characters - I'm */
/* sure it could be amended to handle larger samples - the main reason I  */
/* didn't do this was malloc etal gets so non-standard for large amounts. */
/**************************************************************************/
/* 									  */
/* When your program starts, call: 	saminit()			  */
/* 									  */
/* 					This will load the sample player  */
/*					and initialise pointers etc.      */
/* 									  */
/* To play a sample, call:              samplay("sample",speed)           */
/*									  */
/*					Where "sample" specifies the path */
/*					and name of your sample file, and */
/*					speed determines at what speed    */
/*					the sample will be played:	  */
/*					 0=  5Khz   1= 7.5Khz  2= 10Khz   */
/*					 3= 15Khz   4=  20Khz  5= ?????   */
/*					-1= first byte of image file used */
/* 									  */
/* At the end of your program, call:	samkill()			  */
/* 									  */
/**************************************************************************/
/* 									  */
/* Note: The Mastersound player module is particularly neat because it    */
/*       plays the samples under interrupt - leaving your application to  */
/*       carry on as usual. Additionally, only 2 of the 3 sound channels  */
/*       are used. This does result in a bit of distortion, BUT it means  */
/*       that the channel used for the bell and keyclick is spare - which */
/*       means you can type/beep away without spoiling the sample.        */
/* 									  */
/**************************************************************************/
/* 									  */
/* NOTE: This code plays the sample image as if it has no header. Yes, I  */
/*       know sample images normally have headers - but believe me, these */
/*       are so comparatively small that they won't be noticed.           */
/*									  */
/*       Also, HOW does the speed get into the first byte of the sample?? */
/*       Well, I used SMART_PL.PRG to do this - I've supplied a copy in   */
/*       SAMPLES folder. This allows you to edit sample speeds/lengths.   */
/*									  */
/**************************************************************************/
/* This code only works on the ST... It will compile other machines,      */
/* but won't actually do anything. 					  */
/**************************************************************************/

#ifdef ST

#include <stdio.h>
#include <osbind.h>

char *malloc();

#ifndef SEEK_SET
#define SEEK_SET 0
#endif
 
#ifndef SEEK_END
#define SEEK_END 2
#endif

/***************************************************************************
 ***************************************************************************/
 
static char *samtop= NULL;  /* Top of currently loaded sample */
static char *playsam=NULL;  /* Start of sample player code */
static long *play=   NULL;  /* Address of sample play code */
static long *halt=   NULL;  /* Address of sample halt code */
static long *wait=   NULL;  /* Address of sample wait code */
static int *speed  = NULL;  /* location to store sample playback speed */
static long *len   = NULL;  /* location to store length of sample */
static long *start = NULL;  /* location to store sample start */

static char sname[80]="NOSAMPLE.XXX"; /* name of last sample played */
static long size=0;                   /* size of last sample played */

/***************************************************************************
 ***************************************************************************/
 
/* Execute an external function - take note all you guys who insist on
				  using an assembler module to do this bit! */

doext(memloc)
void (*memloc) ();
{
   /* The address of the routine is passed. We just need to call it */
   (*memloc)();
}

/***************************************************************************
 ***************************************************************************/
 
/* Initialise sample player. Load sampler code, and initialise indexing 
   pointers */
   
saminit()
{
   FILE *fp;
   long size;
   
   /* Open the code file */
   if ((fp=fopen("MASTER.BIN","rb"))==NULL)
   {
      printf("Sample player file MASTER.BIN not found.\n");
      return;
   }

   /* Determine length of code file */
   fseek(fp,0L,SEEK_END);
   size= ftell(fp);
   
   /* Allocate enough memory to contain the code */
   
   playsam= (char *) malloc((int)size);
   if (playsam==NULL)
   {
      printf("Uhoh - can't allocate storage for sample player.\n");
      fclose(fp);
      return;
   }
   
   /* Read the sample code into the allocated memory, and close the file */
   
   fseek(fp,0L,SEEK_SET);
   fread(playsam,(int)size,1,fp);
   fclose(fp);
   
   /* Initialise indexes into the code */
   
   play=   (long *) (playsam+28);
   wait=   (long *) (playsam+28+8);
   halt=   (long *) (playsam+28+12);
   speed=  (int *) (playsam+28+24);
   start=  (long *) (playsam+28+28);
   len=    (long *) (playsam+28+32);  
}

/***************************************************************************
 ***************************************************************************/

/* Play a selected sample. If the file name is the same as the previously 
   loaded sample, then it will not be reloaded! */
   
samplay(name,_speed)
char *name;           /* Name of file containing sample image */
int _speed;           /* Speed at which to play sample */
{
   char *sam=NULL;                       /* memory location of sample */
   int num,                              /* Number of 32767 byte chunks */
       rem,                              /* Number of remaining bytes */
       i;
   FILE *fp;

   /* Make sure sample player has been loaded! */

   if (playsam==NULL)
   {
      printf("Sample player has not been loaded.\n");
      return;
   }
      
   /* If we haven't already got this sample in memory, load it in! */

   if (strcmp(name,sname))
   {
      /* Try to open the file */      

      if ((fp=fopen(name,"rb"))==NULL)
      {
         printf("Sample image \"%s\" not found.\n", name);
         return;
      }

      /* If we have previously played a sample, make sure it has ended, 
         then kill it, and free memory up. */

      if (samtop!=NULL)
      {
         doext(wait);   
         doext(halt);   
         free(samtop);
         samtop=NULL;
      }

      /* Determine the size of the sample */

      fseek(fp,0L,SEEK_END);
      size= ftell(fp);
   
      /* I'm limiting max size to 65535 simply because large malloc variations
         become so non-standard that it becomes ridiculous. */

      if (size>65535L) 
      {
         printf("Uhoh - that sample is too big for me to handle!\n");
         return;
      }

      /* Allocate space for sample. Return normally if not enough memory */
         
      sam= (char *) malloc((unsigned)size);
      if (sam==NULL)
      {
         fclose(fp);
         return;
      }
      
      samtop= sam;

      /* Load in the sample in chunks of 32767 characters.
         Theory says that we should be able to load in chunks of 65535,
         but I couldn't get this to work reliably. */
         
      fseek(fp,0L,SEEK_SET);
      num= size/32767;
      rem= size%32767;
      for (i=0; i<num; ++i)
      {
         fread(sam,32767,1,fp);
         sam+=32767;
      }
      if (rem)
         fread(sam,rem,1,fp);
      fclose(fp);
      
      strcpy(sname,name);
   }

   /* Tell sample player the speed at which to play - if -1 is used,
      then the first byte of the sample image is used to determine 
      the speed at which the sample should be played */
      
   if (_speed== -1)
      *speed= *samtop;
   else
      *speed= _speed;
      
   /* Tell sample player the address of the sample, and its length */
   
   *start= (long)((long *)(samtop+1));
   *len= size-1;

   /* play the sample! */
   
   doext(play);
}

/***************************************************************************
 ***************************************************************************/
 
/* Kill the currently loaded sample, and the sample player - free memory */

samkill()
{
   /* Only do this if sample player has been loaded! */
   
   if (playsam!=NULL)
   {
      doext(wait);
      doext(halt);
      free(playsam);
      playsam= NULL;
      if (samtop!=NULL)
         free(samtop);
      samtop= NULL;
      strcpy(sname,"NOSAMPLE.XXX");
      size=0;
   }
}
   
/***************************************************************************
 ***************************************************************************/

/* If not compiled on ST, do nothing! */

#else
void saminit() {}
void samplay(x,y) char *x; int y; {}
void samkill() {}
#endif

