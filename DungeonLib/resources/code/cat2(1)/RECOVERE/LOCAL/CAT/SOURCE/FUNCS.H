#ifndef MAIN
extern void upper();
extern void lower();
extern void encrypt();
extern void warning();
extern FILE *fopenx();
extern void diskfull();
#endif

#ifndef LCHECK 
extern BOOLEAN lcheck();
#endif

#ifndef FILES 
extern void inc();
extern void open_files();
extern void close_files();
#endif

#ifndef TOKEN
extern void p_token();
extern char *get_token();
#endif

#ifndef OBJECT
extern void obj();
extern void objsht();
extern void objsyn();
extern void objlng();
extern void objwgt();
extern void objngt();
extern void objval();
extern void objpnt();
extern void objstr();
extern void objroom();
extern void objinrm();
extern void objdoor();
extern void objportal();
extern void objlck();
extern void objread();
extern void objkey();
extern void objplr();
extern void objcmd();
extern void objact();
extern void objwear();
extern void objworn();
extern void objhide();
extern void objeat();
extern void objdrink();
extern void objlgt();
extern void objlit();
extern void endobj();
#endif

#ifndef MSG
extern void msg();
extern void msgtxt();
extern void endmsg();
#endif

#ifndef ROOM
extern void room();
extern void roomsht();
extern void roomlng();
extern void roompth();
extern void roomdrk();
extern void roompnt();
extern void endroom();
#endif

#ifndef VERB
extern void verb();
extern void verbsyn();
extern void verbchk();
extern void verbprep();
extern void verblgt();
extern void endverb();
#endif

#ifndef LOGIC
extern void lc();
extern void lif();
extern void lelse();
extern void lendif();
extern void lwhile();
extern void lwend();
extern void lhigh();
extern void llow();
extern void linit();
extern void lfirst();
extern void llast();
extern void m_use();
extern void m_def();
extern void puse();
extern void pdef();
extern void freelink();
extern BOOLEAN isused();
extern BOOLEAN isdef();
#endif
