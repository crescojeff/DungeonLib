#include <stdio.h>
#include <string.h>

#include "defines.h"

#define FILES TRUE

#include "funcs.h"
#include "globals.h"

void inc(f)
FILE *f;
{
   fprintf(f,"#include \"xdef.h\"\n");
   fprintf(f,"#include \"xlang.h\"\n");
   fprintf(f,"#include \"xfuncs.h\"\n");
   fprintf(f,"#include \"xglobals.h\"\n");
   prterr=fprintf(f,"\n");
   if (prterr<0)
      diskfull();
}

void open_files()
{
   xdef= fopenx("xdef.h", "w");
   fprintf(xdef,"#ifndef GOT_DEF\n#define GOT_DEF 1\n\n");
   fprintf(xdef,"#ifdef INIT\nchar *strp[100];\n");
   fprintf(xdef,"#else\nextern char *strp[];\n#endif\n");
   xdict= fopenx("a.dic", "w");
   fprintf(xdict,"char *dict[]=\n{\n");
   fclose(xdict);
   xmsg= fopenx("i.c", "w");
   xodet= fopenx("h.c", "w");     inc(xodet);
   xolng= fopenx("j.c", "w");     
   xosht= fopenx("m.c", "w");
   xosynn= fopenx("n.c", "w");   inc(xosynn);
   xosynt= fopenx("o.c", "w");
   xrmd= fopenx("p.c", "w");       inc(xrmd);
   xrmp= fopenx("r.c", "w");       inc(xrmp);
   xrml= fopenx("q.c", "w");       
   xrms= fopenx("s.c", "w");
   xvchk= fopenx("t.c", "w");     inc(xvchk);
   xvsynn= fopenx("v.c", "w");   inc(xvsynn);
   xvsynt= fopenx("w.c", "w");
   fprintf(xvsynn,"int vsynn[]=\n{\n");
   fprintf(xvsynt,"char *vsynt[]=\n{\n");
   fclose(xvsynn); fclose(xvsynt);
   xoqual= fopenx("k.c", "w");
   xoqualo= fopenx("l.c", "w");
   xvprep= fopenx("u.c", "w");
   fprintf(xmsg,"char *msg[]=\n{\n");
   fprintf(xodet,"int odet[][23]=\n{\n");
   fprintf(xolng,"char *olng[]=\n{\n");
   fprintf(xosht,"char *osht[]=\n{\n");
   fprintf(xosynn,"int osynn[]=\n{\n");
   fprintf(xosynt,"char *osynt[]=\n{\n");
   fprintf(xrmd,"int rmd[][4]=\n{\n");
   fprintf(xrml,"char *rml[]=\n{\n");
   fprintf(xrms,"char *rms[]=\n{\n");
   fclose(xrml); fclose(xrms);
   fprintf(xrmp,"int rmp[][3]=\n{\n");
   fprintf(xvchk,"int vchk[][2]=\n{\n");
   fprintf(xoqual,"char *oqual[]=\n{\n");
   fprintf(xoqualo,"char *oqualo[]=\n{\n");
   fprintf(xvprep,"char *vprep[]=\n{\n");
   fclose(xoqual); fclose(xoqualo); fclose(xvprep);
   xlogic= fopenx("f.c", "w"); inc(xlogic);
   fprintf(xlogic,"BOOLEAN high()\n{\n");
   fclose(xlogic);
   xlogic= fopenx("e1.x", "w");
   fprintf(xlogic, "void sinit()\n{\n");
   fprintf(xlogic, "   int i;\n\n   for (i=0; i<99; i++)\n");
   fprintf(xlogic, "      strp[i]=NULL;\n");
   fclose(xlogic); 
   xlogic= fopenx("e2.x", "w");
   fprintf(xlogic, "void first()\n{\n");
   fclose(xlogic);
   xlogic= fopenx("e3.x", "w");
   fprintf(xlogic, "void last()\n{\n");
   fclose(xlogic);
   xlogic= fopenx("e.c", "w"); 
   fprintf(xlogic, "#define INIT 1\n\n");
   inc(xlogic);
   fprintf(xlogic, "#include \"e1.x\"\n\n");
   fprintf(xlogic, "#include \"e2.x\"\n\n");
   fprintf(xlogic, "#include \"e3.x\"\n\n");
   fprintf(xlogic,"BOOLEAN init()\n{\n");
   fclose(xlogic);
   xlogic= fopenx("g.c", "w"); inc(xlogic);
   prterr=fprintf(xlogic,
             "BOOLEAN low(vt,xvn,nt,xnn)\nchar *vt, *nt;\nint xvn, xnn;\n{\n");
   if (prterr<0)
      diskfull();   
}

void close_files()
{
   fclose(xlogic);
   xlogic= fopenx("e1.x", "a");
   fprintf(xlogic, "}\n");
   fclose(xlogic);
   xlogic= fopenx("e2.x", "a");
   fprintf(xlogic, "}\n");
   fclose(xlogic);
   xlogic= fopenx("e3.x", "a");
   fprintf(xlogic, "}\n");
   fclose(xlogic);
   xlogic= fopenx("g.c", "a");
   fprintf(xlogic,"   return TRUE;\n}\n");
   fclose(xlogic);
   xlogic= fopenx("f.c", "a");
   fprintf(xlogic,"   return TRUE;\n}\n");
   fclose(xlogic);
   xlogic= fopenx("e.c", "a");
   fprintf(xlogic,"}\n");
   fclose(xlogic);
   fprintf(xmsg,"   \"\"\n};\n");
   fclose(xmsg);
   fprintf(xodet,"   -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1\n};\n");
   fclose(xodet);
   fprintf(xolng,"   \"\"\n};\n");
   fclose(xolng);
   fprintf(xosht,"   \"\"\n};\n");
   fclose(xosht);
   fprintf(xosynn,"   -1\n};\n");
   fclose(xosynn);
   fprintf(xosynt,"   \"\"\n};\n");
   fclose(xosynt);
   fprintf(xrmd,"   -1,-1,-1,-1\n};\n");
   fclose(xrmd);
   xrml= fopenx("q.c", "a");       
   xrms= fopenx("s.c", "a");
   fprintf(xrml,"   \"\"\n};\n");
   fclose(xrml);
   fprintf(xrmp,"   -1,-1,-1\n};\n");
   fclose(xrmp);
   fprintf(xrms,"   \"\"\n};\n");
   fclose(xrms);
   fprintf(xvchk,"   -1, -1\n};\n");
   fclose(xvchk);
   xvsynn= fopenx("v.c", "a"); 
   xvsynt= fopenx("w.c", "a");
   fprintf(xvsynn,"   -1\n};\n");
   fclose(xvsynn);
   fprintf(xvsynt,"   \"\"\n};\n");
   fclose(xvsynt);
   xoqual= fopenx("k.c", "a");
   xoqualo= fopenx("l.c", "a");
   xvprep= fopenx("u.c", "a");
   fprintf(xoqual,"   \"\"\n};\n");
   fclose(xoqual);
   fprintf(xoqualo,"   \"\"\n};\n");
   fclose(xoqualo);
   fprintf(xvprep,"   \"\"\n};\n");
   fclose(xvprep);
   xdict= fopenx("a.dic","a");
   fprintf(xdict, "   \"\"\n};\n");
   fclose(xdict);
   prterr= fprintf(xdef, "\n#endif\n");
   fclose(xdef);
   if (prterr<0) 
      diskfull();
}
