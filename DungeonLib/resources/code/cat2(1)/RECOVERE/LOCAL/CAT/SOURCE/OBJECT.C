#include <stdio.h>
#include <string.h>

#include "defines.h"

#define OBJECT TRUE

#include "funcs.h"
#include "globals.h"

static char id[80]="";
static char sht[1000]="";
static char lng[2000]="";
static char wgt[80]="";
static char val[80]="";
static char pnt[80]="";
static char str[80]="";
static char eat[80]="";
static char drink[80]="";
static char rom[80]="";
static char inrm[80]="";
static char door1[80]="";
static char door2[80]="";
static char portal[80]="";
static char lck[80]="";
static char read[80]="";
static char key[80]="";
static BOOLEAN got_id= FALSE;
static BOOLEAN got_sht= FALSE;
static BOOLEAN got_lng= FALSE;
static BOOLEAN got_wgt= FALSE;
static BOOLEAN got_val= FALSE;
static BOOLEAN got_pnt= FALSE;
static BOOLEAN got_str= FALSE;
static BOOLEAN got_room= FALSE;
static BOOLEAN got_inrm= FALSE;
static BOOLEAN got_door= FALSE;
static BOOLEAN got_portal= FALSE;
static BOOLEAN got_lck= FALSE;
static BOOLEAN got_read= FALSE;
static BOOLEAN got_key= FALSE;
static BOOLEAN got_plr= FALSE;
static BOOLEAN got_cmd= FALSE;
static BOOLEAN got_act= FALSE;
static BOOLEAN got_wear= FALSE;
static BOOLEAN got_worn= FALSE;
static BOOLEAN got_eat= FALSE;
static BOOLEAN got_drink= FALSE;
static BOOLEAN got_lgt= FALSE;
static BOOLEAN got_lit= FALSE;
static BOOLEAN got_ngt= FALSE;
static BOOLEAN got_hide= FALSE;

void objsht(token)
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
         warning(0,"O_",id,"Excess short text ignored.");
      else
      {
         encrypt(sht,TRUE);
         if (strlen(sht)>254)
            warning(0,"O_",id,"Short text is over 254 characters - portable?");
         got_sht= TRUE;
      }
   }
}

void objlng(token)
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
         warning(0,"O_",id,"Excess long text ignored.");
      else
      {
         encrypt(lng,TRUE);
         if (strlen(lng)>254)
            warning(0,"O_",id,"Long text is over 254 characters - portable?");
         got_lng= TRUE;
      }
   }
}

void objlck(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (got_lck)
      {
         sprintf(error, "Excess lock (%s) ignored.", token);
         warning(0,"O_",id,error);
      }
      else
      {
         if (strstr("OPEN CLOSED LOCKED ", token)!=NULL)
         {
            strcpy(lck, token);
            got_lck= TRUE;
         }
         else
         {
            sprintf(error, "Unrecognised lock (%s) ignored.", token);
            warning(0,"O_",id,error);
         }
      }
   }
}

void objsyn(token)
char *token;
{
   char syn[80];
   char *p;
   
   if (strcmp(token,"@END"))
   {
      encrypt(token,FALSE);
      sprintf(syn, "   \"%s\",\n", token);
      if (update) prterr=fprintf(xosynt,syn);
      
      if (got_id)
      {
         sprintf(syn, "   O_%s,\n", id);
         if (update) prterr=fprintf(xosynn,syn);
      }
      else
      {
         sprintf(syn, "   %d,\n", obj_no+1);
         if (update) prterr=fprintf(xosynn,syn);
      }
      
      if (prterr<0)
         diskfull();
         
      /* Look for qualifiers */
      
      strcpy(syn, token);
      p= strchr(syn, (int) '_');
      if (p)
      {
         *p= '\0';
         xoqual= fopenx("k.c", "a");
         xoqualo= fopenx("l.c", "a");
         if (update) prterr=fprintf(xoqual, "   \"%s\",\n", syn);
         if (update) prterr=fprintf(xoqualo, "   \"%s\",\n", p+1);
         if (update) {fclose(xoqual); fclose(xoqualo);}
         if (update) prterr=fprintf(xosynt, "   \"%s\",\n", p+1);
         if (update)
         {
            if (got_id) 
               prterr=fprintf(xosynn, "   O_%s,\n", id);
            else
               prterr=fprintf(xosynn, "   %d,\n", obj_no+1);
            if (prterr<0)
               diskfull();
         }
      }
   }
}

void obj(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (got_id)
      {
         sprintf(error, "Excess id (%s) ignored.", token);
         warning(0,"O_",id,error);
      }
      else
      {
         strcpy(id, token);
         got_id= TRUE;
         objsyn(token);
      }
   }   
}

void objwgt(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if ( (got_wgt) || (got_ngt) )
      {
      	 sprintf(error, "Excess weight (%s) ignored.", token);
         warning(0,"O_",id,error);
      }
      else
      {
         strcpy(wgt, token);
         got_wgt= TRUE;
      }
   }
}

void objval(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (got_val)
      {
         sprintf(error, "Excess value (%s) ignored.", token);
         warning(0,"O_",id,error);
      }
      else
      {
         strcpy(val, token);
         got_val= TRUE;
      }
   }
}

void objpnt(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (got_pnt)
      {
         sprintf(error, "Excess points (%s) ignored.", token);
         warning(0,"O_",id,error);
      }
      else
      {
         strcpy(pnt, token);
         got_pnt= TRUE;
      }
   }
}

void objstr(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (got_str)
      {
         sprintf(error, "Excess strength (%s) ignored.", token);
         warning(0,"O_",id,error);
      }
      else
      {
         strcpy(str, token);
         got_str= TRUE;
      }
   }
}

void objroom(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (got_room)
      {
         sprintf(error, "Excess room (%s) ignored.", token);
         warning(0,"O_",id,error);
      }
      else
      {
         strcpy(rom, "R_");
         strcat(rom, token);
         m_use(rom);
         got_room= TRUE;
      }
   }
}

void objinrm(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (got_inrm)
      {
         sprintf(error, "Excess in-room (%s) ignored.", token);
         warning(0,"O_",id,error);
      }
      else
      {
         strcpy(inrm, "R_");
         strcat(inrm, token);
         m_use(inrm);
         got_inrm= TRUE;
      }
   }
}

void objportal(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (got_portal)
      {
         sprintf(error, "Excess portal (%s) ignored.", token);
         warning(0,"O_",id,error);
      }
      else
      {
         strcpy(portal, "R_");
         strcat(portal, token);
         m_use(portal);
         got_portal= TRUE;
      }
   }
}

void objread(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (got_read)
      {
         sprintf(error, "Excess read (%s) ignored.", token);
         warning(0,"O_",id,error);
      }
      else
      {
         strcpy(read, "M_");
         strcat(read, token);
         m_use(read);
         got_read= TRUE;
      }
   }
}

void objkey(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (got_key)
      {
         sprintf(error, "Excess key (%s) ignored.", token);
         warning(0,"O_",id, error);
      }
      else
      {
         strcpy(key, "O_");
         strcat(key, token);
         m_use(key);
         got_key= TRUE;
      }
   }
}

void objplr()
{
   got_plr= TRUE;
}

void objcmd()
{
   got_cmd= TRUE;
}

void objact()
{
   got_act= TRUE;
}

void objngt()
{
   got_ngt= TRUE;
}

void objwear()
{
   got_wear= TRUE;
}

void objworn()
{
   got_worn= TRUE;
}

void objhide()
{
   got_hide= TRUE;
}

void objeat(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (got_eat)
      {
         sprintf(error, "Excess eat (%s) ignored.", token);
         warning(0,"O_",id,error);
      }
      else
      {
         strcpy(eat, token);
         got_eat= TRUE;
      }
   }
}

void objdrink(token)
char *token;
{
   if (strcmp(token,"@END"))
   {
      if (got_drink)
      {
         sprintf(error, "Excess drink (%s) ignored.", token);
         warning(0,"O_",id,error);
      }
      else
      {
         strcpy(drink, token);
         got_drink= TRUE;
      }
   }
}

void objlgt()
{
   got_lgt= TRUE;
}

void objlit()
{
   got_lit= TRUE;
}

void objdoor(token)
char *token;
{
   char *p;
   
   if (strcmp(token,"@END"))
   {
      if (got_door)
      {
         sprintf(error, "Excess door (%s) ignored.", token);
         warning(0,"O_",id,error);
      }
      else
      {
         p=strpbrk(token,",");
         if (!p)
         {
            sprintf(error,"Invalid door (%s) ignored.", token);
            warning(0,"O_",id,error);
         }
         else
         {
            *p= '\0';
            strcpy(door1, "R_");
            strcat(door1, token);
            strcpy(door2, "R_");
            strcat(door2, p+1);
            m_use(door1);
            m_use(door2);
            got_door= TRUE;
         }
      }
   }
}

void endobj(token)
char *token;
{
   char def[80];
   
   if (strcmp(token,"@END")==0)
   {
      if (!got_id)
      {
         sprintf(id, "%05d", obj_no+1);
         sprintf(error, "Identifier (%s) generated.", id);
         warning(0,"O_",id,error);
      }
     
      if (update)
      {
         prterr=fprintf(xdef, "#define O_%s %d\n", id, obj_no+1);
         if (prterr<0)
            diskfull();
      }
      sprintf(def, "O_%s", id);
      m_def(def);

      if (got_plr)
      {
         got_cmd= TRUE;
         got_act= TRUE;
      }
      
      if (got_cmd)
         got_act= TRUE;
      
      if (got_act)
      {
         if (!got_str)
            warning(0,"O_",id,"Active object has zero strength.");
         if (!got_inrm)   
            warning(0,"O_",id,"Active object does not have in-room.");
      }
            
      if ((!got_act) && (got_inrm))
      {
         if (!got_str)
            warning(0,"O_",id,"Object with in-room has zero strength.");
      }
      
      if ((got_lck) && (strcmp(lck,"LOCKED")==0))
      {
         if (!got_key)
            warning(1,"O_",id,"Locked object has no key.");
      }
      
      if ((got_key) && (!got_lck))
         warning(1,"O_",id,"Object has key, but no object lock.");
         
      if (!got_sht)
      {
         strcpy(sht, " ");
         warning(1,"O_",id,"Blank short text added.");
      }

      if (!got_lng)
      {
         strcpy(lng, " ");
         warning(1,"O_",id,"Blank long text added.");
      }

      if (got_ngt)
         strcpy(wgt, "NON_MOVABLE");
      else if (!got_wgt)
         strcpy(wgt, "1");
         
      if (!got_val)
         strcpy(val, "0");
         
      if (!got_pnt)
         strcpy(pnt, "0");
         
      if (!got_str)
         strcpy(str, "0");
         
      if (!got_room)
      {
         strcpy(rom, "R_NOWHERE");
         warning(1,"O_",id,"Object assumed to be nowhere.");
      }
      
      if (!got_inrm)
         strcpy(inrm, "R_NOWHERE");
         
      if (!got_door)
      {
         strcpy(door1, "R_NOWHERE");
         strcpy(door2, "R_NOWHERE");
      }
      
      if (!got_portal)
         strcpy(portal, "R_NOWHERE");
         
      if (!got_lck)
         strcpy(lck, "NO_LOCK");
         
      if (!got_read)
         strcpy(read, "NON_READABLE");

      if (!got_key)
         strcpy(key, "NO_KEY");

      if (update)
      {
         prterr=fprintf(xosht, "   \"%s\",\n", sht);
         prterr=fprintf(xolng, "   \"%s\",\n", lng);
      
         prterr=fprintf(xodet, "   %s, %s, %s, %s,\n", wgt, val, rom, inrm);

         if (got_plr)
            prterr=fprintf(xodet, "   PLAYER, ");
         else
            prterr=fprintf(xodet, "   NON_PLAYER, ");
         
         if (got_worn)
            prterr=fprintf(xodet, "WORN, ");
         else if (got_wear)
            prterr=fprintf(xodet, "WEARABLE, ");
         else
            prterr=fprintf(xodet, "NON_WEARABLE, ");

         if (got_eat)
            prterr=fprintf(xodet, "%10s,\n",eat);
         else
            prterr=fprintf(xodet, "NON_EDIBLE,\n");
         
         prterr=fprintf(xodet, "   %s, %s, ", str, lck);
      
         if (got_lit)
            prterr=fprintf(xodet, "LIT, ");
         else if (got_lgt)
            prterr=fprintf(xodet, "LIGHT_SOURCE, ");
         else
            prterr=fprintf(xodet, "NON_LIGHT_SOURCE, ");
         
         prterr=fprintf(xodet, "%s,\n", read);
      
         prterr=fprintf(xodet, "   %s, %s, 0,\n", pnt, key);
         prterr=fprintf(xodet, "   %s, %s, %s, ", door1, door2, portal);

         if (got_hide)
            prterr=fprintf(xodet, "HIDDEN, ");
         else
            prterr=fprintf(xodet, "NOT_HIDDEN, ");

         if (got_drink)
            prterr=fprintf(xodet, "%13s,\n",drink);
         else
            prterr=fprintf(xodet, "NON_DRINKABLE,\n");
         
         if (got_cmd)
            prterr=fprintf(xodet, "COMMANDABLE, ");
         else
            prterr=fprintf(xodet, "NO_COMMANDS, ");
         
         if (got_act)
            prterr=fprintf(xodet, "ACTIVE,    ");
         else
            prterr=fprintf(xodet, "NON_ACTIVE, ");
         
         prterr=fprintf(xodet, "-1,-1,");
         
         prterr=fprintf(xodet, "\n\n");
      
         if (prterr<0)
            diskfull();
      }

      ++obj_no;
      id[0]='\0';
      sht[0]='\0';
      lng[0]='\0';
      wgt[0]='\0';
      val[0]='\0';
      pnt[0]='\0';
      str[0]='\0';
      rom[0]='\0';
      inrm[0]='\0';
      door1[0]='\0';
      door2[0]='\0';
      portal[0]='\0';
      lck[0]='\0';
      read[0]='\0';
      eat[0]='\0';
      drink[0]='\0';
      got_id= FALSE;
      got_sht= FALSE;
      got_lng= FALSE;
      got_wgt= FALSE;
      got_val= FALSE;
      got_pnt= FALSE;
      got_str= FALSE;
      got_room= FALSE;
      got_inrm= FALSE;
      got_door= FALSE;
      got_portal= FALSE;
      got_lck= FALSE;
      got_read= FALSE;
      got_key= FALSE;
      got_plr= FALSE;
      got_cmd= FALSE;
      got_act= FALSE;
      got_wear= FALSE;
      got_worn= FALSE;
      got_hide= FALSE;
      got_eat= FALSE;
      got_drink= FALSE;
      got_lgt= FALSE;
      got_lit= FALSE;
      got_ngt= FALSE;
   }
}
