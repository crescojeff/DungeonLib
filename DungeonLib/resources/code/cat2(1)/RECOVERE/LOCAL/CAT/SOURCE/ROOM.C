#include <stdio.h>
#include <string.h>

#include "defines.h"

#define ROOM TRUE

#include "funcs.h"
#include "globals.h"

static char sht[1000]="";
static char lng[2000]="";
static char pnt[80]="";
static char id[80]="";
static BOOLEAN got_sht= FALSE;
static BOOLEAN got_lng= FALSE;
static BOOLEAN got_drk= FALSE;
static BOOLEAN got_pth= FALSE;
static BOOLEAN got_pnt= FALSE;
static BOOLEAN got_id= FALSE;

void roomsht(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (!got_sht)
      {
         if (strlen(sht)!=0)
            strcat(sht, " ");
         strcat(sht, token);
      }
   }
   else
   {
      if (got_sht)
         warning(0, "R_", id, "Excess short description ignored.");
      else
      {
         encrypt(sht,TRUE);
         if (strlen(sht)>254)
            warning(0,"R_",id,"Short text is over 254 characters - portable?");
         got_sht= TRUE;
      }
   }
}

void roomlng(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (!got_lng)
      {
         if (strlen(lng)!=0)
            strcat(lng," ");
         strcat(lng, token);
      }
   }
   else
   {
      if (got_lng)
         warning(0, "R_", id, "Excess long description ignored.");
      else
      {
         encrypt(lng,TRUE);
         if (strlen(lng)>254)
            warning(0,"R_",id,"Long text is over 254 characters - portable?");
         got_lng= TRUE;
      }
   }
}

void roomdrk()
{
   got_drk= TRUE;
}

void roompnt(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (got_pnt)
      {
         sprintf(error, "Excess points (%s) ignored.", token);
         warning(0,"R_",id,error);
      }
      else
      {
         strcpy(pnt, token);
         got_pnt= TRUE;
      }
   }
}

void roompth(token)
char *token;
{
   char *p;
   char verb[80];
   char to_room[80];
   char line[80];
   char use[80];
   
   if (strcmp(token,"@END"))
   {
      p=strpbrk(token,",");
      if (!p)
      {
         sprintf(error,"Invalid path (%s) ignored.", token);
         warning(0,"R_",id, error);
      }
      else
      {
         *p= '\0';
         strcpy(verb, token);
         strcpy(to_room, p+1);
         if (!got_id)
            sprintf(line, "   %d, ", room_no+1);
         else
            sprintf(line, "   R_%s, ", id);
         sprintf(use, "V_%s", verb);
         m_use(use);
         strcat(line, use);
         strcat(line, ", ");
         strcpy(use, "");
         if (strcmp(to_room,"CARRIED"))
            strcat(use, "R_");
         strcat(use, to_room);
         if (strcmp(to_room,"CARRIED"))
            m_use(use);
         strcat(line, use);
         strcat(line, ",\n");
         if (update)
         {
            prterr=fprintf(xrmp,line);
            if (prterr<0)
               diskfull();
         }
         got_pth= TRUE;
      }
   }
}

void room(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (got_id)
      {
         sprintf(error, "Excess id (%s) ignored.", token);
         warning(0,"R_",id, error);   
      }
      else
      {
         strcpy(id, token);
         got_id= TRUE;
      }
   }
}


void endroom(token)
char *token;
{
   char line[80];
   char def[80];
   
   if (strcmp(token,"@END")==0)
   {
      if (!got_id)
      {
         sprintf(id, "%05d", room_no+1);
         sprintf(error, "Identifier (%s) generated.", id);
         warning(0,"R_",id, error);
      }
     
      if (!got_sht)
      {
         strcpy(sht, " ");
         warning(0,"R_",id, "Blank short text added.");
      }

      if (!got_lng)
      {
         strcpy(lng, sht);
         warning(1,"R_",id, "Long text derived from short text.");
      }
      
      if (!got_pth)
         warning(1,"R_",id, "Room has no obvious exits!");
         
      sprintf(def, "R_%s", id);
      m_def(def);

      if (update)
      {
         sprintf(line, "#define R_%s %d\n", id, room_no+1);
         prterr=fprintf(xdef,line);
      
         xrml= fopenx("q.c", "a");       
         xrms= fopenx("s.c", "a");

         prterr=fprintf(xrms,"   \"");
         prterr=fprintf(xrms,sht);
         prterr=fprintf(xrms,"\",\n");
      
         prterr=fprintf(xrml,"   \"");
         prterr=fprintf(xrml,lng);
         prterr=fprintf(xrml,"\",\n");
      
         if (update) {fclose(xrml); fclose(xrms);}
      
         if (got_drk)
            prterr=fprintf(xrmd,"   DARK,  NOT_VISITED, ");
         else
            prterr=fprintf(xrmd,"   LIGHT, NOT_VISITED, ");
         
         if (got_pnt)
            prterr=fprintf(xrmd, "%8s, ", pnt);
         else
            prterr=fprintf(xrmd, "NO_SCORE, ");
         
         prterr=fprintf(xrmd,"-1,\n");
         
         if (prterr<0)
            diskfull();
      }
         
      ++room_no;
      got_id= FALSE;
      got_sht= FALSE;
      got_lng= FALSE;
      got_pth= FALSE;
      got_drk= FALSE;
      got_pnt= FALSE;
      lng[0]='\0';
      sht[0]='\0';
      pnt[0]='\0';
      id[0]='\0';
   }
}
