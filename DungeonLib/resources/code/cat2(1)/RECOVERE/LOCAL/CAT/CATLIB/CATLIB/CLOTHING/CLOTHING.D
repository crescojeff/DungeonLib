@rem **************************************************************************
@rem * CAT clothing handler - written by Tony Stiles June 1991                *
@rem * Based on an idea from Martyn Dryden of the South West Software Library *
@rem **************************************************************************

@rem This file contains a clothing handler suitable for CAT version 2 and
     upwards. Thanks go to Martyn Dryden for the idea.
     
     The code in this file simulates 'stacking of clothing'....
     
     For example if you are wearing a pair of trousers, then you should not
     also be able to wear a pair of jeans, but you may be able to wear a skirt
     - whereas you would certainly be able to wear a jumper. 

     Likewise, if you are wearing a shirt and a jumper, then you should not
     be able to remove the shirt without first removing the jumper!

@rem *********************************************************************

@rem In order to use this code, you must define all of your clothing items
     in one consecutive bank i.e. one object after the other.

     You must also define two banks of messages - with one message for each
     clothing item, whether the message text is blank or not. The first bank
     of messages specifies all the objects that will stop this object from 
     being worn. The second bank defines the objects that will stop this 
     object from being removed. The two banks will not necessarily be the 
     same - for example it may be possible to remove a bra whilst wearing a 
     jumper, but impossible to wear the bra whilst wearing the jumper.

     Presuming the banks of data have been defined, these need to be
     introduced to CAT in initialisation logic. 

     Counter 400 should be set to the first object number to be included in
                 the clothing handler.

     Counter 401 should be set to the last object number to be included in
                 the clothing handler.

     Counter 402 should be set the the first msg in the 'wear' msg bank.

     Counter 403 should be set to the first msg in the 'remove' msg bank.

@rem *********************************************************************

@rem A full example can be found in 'EXAMPLE.D'

     This file should be included in your GENLIST before ZZSTD.D and ZZRQD.D

@rem *********************************************************************

@rem Temporary strings, and messages specific to clothing handler.

@STR WEAR_TMP_A @ENDSTR
@STR WEAR_TMP_B @ENDSTR

@MSG WEAR_OVER @MSGTXT You can't wear that on top of @ENDMSG

@MSG REMOVE_UNDER @MSGTXT You can't remove that while you are wearing @ENDMSG

@REM *********************************************************************

@REM This is the processing needed to stop the player from wearing a 
     given item of clothing if he is already wearing one of the objects
     that will block wearing this item. 

@LOW 

@REM Is the verb wear?
@IF @VERBNOIS(WEAR) @DO
   @REM Is the object in the object bank?
   @REM If yes, make sure we aren't wearing any exclude items.
   @IF @THISOBJ GE @COUNT(400) AND @THISOBJ LE @COUNT(401) @DO
      @SETCOUNT(498,@COUNT(400))
      @REM Pull correct msg from WEAR message bank.
      @MSGTOSTR(@COUNT(402)+@THISOBJ-@COUNT(400),@STRNO(WEAR_TMP_A))
      @STRUPP(WEAR_TMP_A)
      @REM We're going to check each of the objects in the clothing bank.
      @WHILE @COUNT(498) LE @COUNT(401) @DO
         @REM Only bother with items that are actually worn.
         @IF @ISWORN(@COUNT(498)) @DO
            @REM Pull object short text to temp string.
            @OSTOSTR(@COUNT(498),@STRNO(WEAR_TMP_B))
            @REM Convert string to upper case
            @STRUPP(WEAR_TMP_B)
            @REM If this item is in exclude list, print error and exit.
            @IF @STRFSTR(WEAR_TMP_A,@STRNO(WEAR_TMP_B)) GE 0 @DO
               @PMSG(WEAR_OVER)
               @ENDCHAR('.')
               @POBJS(@COUNT(498)) @REM This is the conflicting object.
               @CONT
            @ENDIF
         @ENDIF
         @ADDCOUNT(498,1)
      @WEND
   @ENDIF
@ENDIF

@REM *********************************************************************

@REM This is the processing needed to stop the player from removing a 
     given item of clothing if he is already wearing one of the objects
     that will block the removal of this item. 

@LOW 

@REM Is the verb remove?
@IF @VERBNOIS(REMOVE) @DO
   @REM Is the object in the object bank?
   @REM If yes, make sure we aren't wearing any exclude items.
   @IF @THISOBJ GE @COUNT(400) AND @THISOBJ LE @COUNT(401) @DO
      @SETCOUNT(498,@COUNT(400))
      @REM Pull correct msg from REMOVE message bank.
      @MSGTOSTR(@COUNT(403)+@THISOBJ-@COUNT(400),@STRNO(WEAR_TMP_A))
      @STRUPP(WEAR_TMP_A)
      @REM We're going to check each of the objects in the clothing bank.
      @WHILE @COUNT(498) LE @COUNT(401) @DO
         @REM Only bother with items that are actually worn.
         @IF @ISWORN(@COUNT(498)) @DO
            @REM Pull object short text to temp string.
            @OSTOSTR(@COUNT(498),@STRNO(WEAR_TMP_B))
            @REM Convert string to upper case
            @STRUPP(WEAR_TMP_B)
            @REM If this item is in exclude list, print error and exit.
            @IF @STRFSTR(WEAR_TMP_A,@STRNO(WEAR_TMP_B)) GE 0 @DO
               @PMSG(REMOVE_UNDER)
               @ENDCHAR('.')
               @POBJS(@COUNT(498)) @REM This is the conflicting object.
               @CONT
            @ENDIF
         @ENDIF
         @ADDCOUNT(498,1)
      @WEND
   @ENDIF
@ENDIF

