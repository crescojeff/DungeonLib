#include <osbind.h>
#include <stdio.h>

main()
{
   unlink("cat2lod1.tos");
   Pexec(0,"arc602.ttp"," XZ CAT", "");
   unlink("cat.arc");
   Pexec(0,"arc602.ttp"," XZ CATTXT", "");
   unlink("cattxt.arc");
   Pexec(0,"arc602.ttp"," XZ CATTUTR5", "");
   unlink("cattutr5.arc");
   Pexec(0,"arc602.ttp"," XZ CATEXPRT", "");
   unlink("catexprt.arc");
   Pexec(0,"arc602.ttp"," XZ CATTUTR1", "");
   unlink("cattutr1.arc");
   Pexec(0,"arc602.ttp"," XZ CATTUTR2", "");
   unlink("cattutr2.arc");
   Pexec(0,"arc602.ttp"," XZ CATTUTR3", "");
   unlink("cattutr3.arc");
   Pexec(0,"arc602.ttp"," XZ CATTUTR4", "");
   unlink("cattutr4.arc");
   unlink("cat2lod2.tos");
   unlink("catread.me");
}
