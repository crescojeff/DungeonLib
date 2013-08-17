@REM ******************************************************************
@REM Start off the game with an atmospheric sample                    *
@REM ******************************************************************

@INIT 
   _SAMPLAY("\\SAMPLES\\DRAGNET.SND",-1)
   @PMSG(INTRO_MSG)
   _SAMPLAY("\\SAMPLES\\DRAGNET.SND",-1)

@MSG	INTRO_MSG
@MSGTXT Welcome to the CATLIB 1.0 demonstration adventure. This program
	demonstrates the use of the GEMLIB, SAMPLES, MOVER, and CLOTHING
	CAT library functions. LF LF LF \SAMPLES\DRAGNET now playing....
	LF LF LF 
@ENDMSG

@REM ******************************************************************
@REM * Define some rooms - some are dark                              *
@REm ******************************************************************

@ROOM ROOM_1
@ROOMSHT Room 1.
@ROOMPTH EAST,ROOM_2 SOUTH,ROOM_4
@ENDROOM

@ROOM ROOM_2
@ROOMSHT Room 2.
@ROOMDRK
@ROOMPTH EAST,ROOM_3 SOUTH,ROOM_5 WEST,ROOM_1
@ENDROOM

@ROOM ROOM_3
@ROOMSHT Room 3.
@ROOMPTH SOUTH,ROOM_6 WEST,ROOM_2
@ENDROOM

@ROOM ROOM_4 
@ROOMSHT Room 4.
@ROOMPTH NORTH,ROOM_1 EAST,ROOM_5 SOUTH,ROOM_7
@ENDROOM

@ROOM ROOM_5 
@ROOMDRK
@ROOMSHT Room 5.
@ROOMPTH NORTH,ROOM_2 EAST,ROOM_6 SOUTH,ROOM_8 WEST,ROOM_4
@ENDROOM

@ROOM ROOM_6
@ROOMSHT Room 6.
@ROOMPTH NORTH,ROOM_3 SOUTH,ROOM_9 WEST,ROOM_5
@ENDROOM

@ROOM ROOM_7
@ROOMSHT Room 7.
@ROOMPTH NORTH,ROOM_4 EAST,ROOM_8
@ENDROOM

@ROOM ROOM_8 
@ROOMDRK
@ROOMSHT Room 8.
@ROOMPTH NORTH,ROOM_5 EAST,ROOM_9 WEST,ROOM_7
@ENDROOM

@ROOM ROOM_9
@ROOMSHT Room 9.
@ROOMPTH NORTH,ROOM_6 WEST,ROOM_8
@ENDROOM

@REM ******************************************************************
@REM * Now, create a bunch of players!                                *
@REM ******************************************************************

@OBJ TOM @OBJSHT Tom
@OBJPLR @OBJSTR 10 @OBJROOM ROOM_1 @OBJINRM IN_TOM @OBJNGT
@ENDOBJ
@ROOM IN_TOM @ENDROOM

@OBJ DICK @OBJSHT Dick
@OBJPLR @OBJSTR 10 @OBJROOM ROOM_2 @OBJINRM IN_DICK @OBJNGT
@ENDOBJ
@ROOM IN_DICK @ENDROOM

@OBJ HARRY @OBJSHT Harry
@OBJPLR @OBJSTR 10 @OBJROOM ROOM_3 @OBJINRM IN_HARRY @OBJNGT
@ENDOBJ
@ROOM IN_HARRY @ENDROOM

@OBJ TONY @OBJSHT Tony
@OBJPLR @OBJSTR 10 @OBJROOM ROOM_4 @OBJINRM IN_TONY @OBJNGT
@ENDOBJ
@ROOM IN_TONY @ENDROOM

@OBJ SIMON @OBJSHT Simon
@OBJPLR @OBJSTR 10 @OBJROOM ROOM_5 @OBJINRM IN_SIMON @OBJNGT
@ENDOBJ
@ROOM IN_SIMON @ENDROOM

@OBJ SARA @OBJSHT Sara
@OBJPLR @OBJSTR 10 @OBJROOM ROOM_6 @OBJINRM IN_SARA @OBJNGT
@ENDOBJ
@ROOM IN_SARA @ENDROOM

@OBJ MARK @OBJSHT Mark
@OBJPLR @OBJSTR 10 @OBJROOM ROOM_7 @OBJINRM IN_MARK @OBJNGT
@ENDOBJ
@ROOM IN_MARK @ENDROOM

@OBJ LISA @OBJSHT Lisa
@OBJPLR @OBJSTR 10 @OBJROOM ROOM_8 @OBJINRM IN_LISA @OBJNGT
@ENDOBJ
@ROOM IN_LISA @ENDROOM

@OBJ ANDREW @OBJSHT Andrew
@OBJPLR @OBJSTR 10 @OBJROOM ROOM_9 @OBJINRM IN_ANDREW @OBJNGT
@ENDOBJ
@ROOM IN_ANDREW @ENDROOM

@OBJ ANT @OBJSHT Ant
@OBJPLR @OBJSTR 10 @OBJROOM ROOM_1 @OBJINRM IN_ANT @OBJNGT
@ENDOBJ
@ROOM IN_ANT @ENDROOM

@REM *************************************************************************
@REM Set initial player.
@REM *************************************************************************

@INIT
   @BECOME(TONY)

@REM *************************************************************************
@REM Define active object mover bank.                 
@REM *************************************************************************

@INIT 
   @SETCOUNT(404,TOM) @REM First object to include in mover.
   @SETCOUNT(405,ANT) @REM Last object to include in mover.

@REM **************************************************************************
@REM * Okay, now we need to define each of the objects that are to be handled *
@REM * by the clothing handler. It is important that all of these objects     *
@REM * follow directly after the other, i.e. without any other objects in     *
@REM * between.                                                               *
@REM **************************************************************************

@OBJ		JEANS
@OBJSHT		a pair of jeans
@OBJWEAR
@OBJROOM	ROOM_1
@OBJINRM 	IN_JEANS
@OBJSTR		0
@ENDOBJ

@ROOM IN_JEANS @ENDROOM

@rem *********************************************************************

@OBJ		TROUSERS
@OBJSHT		a pair of trousers
@OBJWEAR
@OBJROOM	ROOM_2
@ENDOBJ

@REM *********************************************************************

@OBJ		SKIRT
@OBJSHT		a skirt
@OBJWEAR
@OBJROOM	ROOM_3
@ENDOBJ

@rem *********************************************************************

@OBJ		KNICKERS
@OBJSHT 	a pair of knickers
@OBJWEAR	
@OBJROOM 	ROOM_4
@ENDOBJ

@REM *********************************************************************

@OBJ		PANTS
@OBJSHT		a pair of pants
@OBJWEAR
@OBJROOM	ROOM_5
@ENDOBJ

@REM *********************************************************************

@OBJ		JACKET
@OBJSHT		a jacket
@OBJWEAR
@OBJROOM	ROOM_6
@ENDOBJ

@REM *********************************************************************

@OBJ		JUMPER
@OBJSHT		a jumper
@OBJWEAR
@OBJROOM	ROOM_7
@ENDOBJ

@REM *********************************************************************

@OBJ		T_SHIRT
@OBJSHT		a t shirt
@OBJWEAR
@OBJROOM	ROOM_8
@ENDOBJ

@REM *********************************************************************

@OBJ		BRA
@OBJSHT		a bra
@OBJWEAR
@OBJROOM	ROOM_9
@ENDOBJ

@REM *********************************************************************

@OBJ		LEFT_SHOE
@OBJSHT		a left shoe
@OBJWEAR
@OBJROOM	ROOM_1
@ENDOBJ

@REM *********************************************************************

@OBJ		RIGHT_SHOE
@OBJSHT		a right shoe
@OBJWEAR
@OBJROOM	ROOM_2
@ENDOBJ

@REM *********************************************************************

@OBJ		LEFT_SOCK
@OBJSHT		a left sock
@OBJWEAR
@OBJROOM	ROOM_3
@ENDOBJ

@REM *********************************************************************

@OBJ		RIGHT_SOCK
@OBJSHT		a right sock
@OBJWEAR
@OBJROOM	ROOM_4
@ENDOBJ

@REM *********************************************************************

@OBJ		STOCKINGS
@OBJSHT		a pair of stockings
@OBJWEAR
@OBJROOM	ROOM_5
@ENDOBJ

@REM **************************************************************************
@REM * This is the WEAR exclude message bank. The naming of the messages is   *
@REM * irrellevant as they are only accessed indirectly - BUT it is important *
@REM * that you define one message for each object (above) even if this means *
@REM * defining an empty message.                                             *
@REM *                                                                        *
@REM * For each object, the relating message describes each of the objects    *
@REM * that will stop this object from being worn - for example the player    *
@REM * would not be able to WEAR the jeans if he was wearing the trousers;    *
@REM * a left shoe or a right shoe. The object short text for each excluding  *
@REM * object is given in the message - this must be identical to the actual  *
@REM * short text for the respective object. The |'s are used to separate     *
@REM * the objects. The msgs must be defined in the same order as the objs.   *
@REM **************************************************************************

@MSG	W_JEANS
@MSGTXT a pair of trousers|a left shoe|a right shoe|
@ENDMSG

@MSG	W_TROUSERS
@MSGTXT a pair of jeans|a left shoe|a right shoe|
@ENDMSG

@MSG	W_SKIRT
@ENDMSG

@MSG    W_KNICKERS
@MSGTXT a pair of jeans|a pair of trousers|a pair of pants|
	a pair of stockings|
@ENDMSG

@MSG	W_PANTS
@MSGTXT	a pair of jeans|a pair of trousers|a pair of knickers|
	a pair of stockings|
@ENDMSG

@MSG	W_JACKET
@ENDMSG

@MSG	W_JUMPER
@MSGTXT a jacket|
@ENDMSG

@MSG	W_T_SHIRT
@MSGTXT a jacket|a jumper|
@ENDMSG

@MSG	W_BRA
@MSGTXT a jacket|a t shirt|a jumper|
@ENDMSG

@MSG	W_LEFT_SHOE
@ENDMSG

@MSG	W_RIGHT_SHOE
@ENDMSG

@MSG	W_LEFT_SOCK
@MSGTXT a left shoe|
@ENDMSG

@MSG	W_RIGHT_SOCK
@MSGTXT a right shoe|
@ENDMSG

@MSG	W_STOCKINGS
@MSGTXT a pair of trousers|a pair of jeans|a left shoe| a right shoe|
	a left sock|a right sock|
@ENDMSG

@REM **************************************************************************
@REM * This is the REMOVE exclude message bank. The naming of the messages is *
@REM * irrellevant as they are only accessed indirectly - BUT it is important *
@REM * that you define one message for each object (above) even if this means *
@REM * defining an empty message.                                             *
@REM *                                                                        *
@REM * For each object, the relating message describes each of the objects    *
@REM * that will stop this object from being removed - for example the player *
@REM * would not be able to REMOVE the jeans if he was wearing either a left  *
@REM * shoe or a right shoe. The object short text for each excluding         *
@REM * object is given in the message - this must be identical to the actual  *
@REM * short text for the respective object. The |'s are used to separate     *
@REM * the objects. The msgs must be defined in the same order as the objs.   *
@REM **************************************************************************


@MSG	R_JEANS
@MSGTXT a left shoe|a right shoe|
@ENDMSG

@MSG	R_TROUSERS
@MSGTXT a left shoe|a right shoe|
@ENDMSG

@MSG	R_SKIRT
@ENDMSG

@MSG	R_KNICKERS
@MSGTXT	a pair of jeans|a pair of trousers|a pair of stockings|
@ENDMSG

@MSG	R_PANTS
@MSGTXT	a pair of jeans|a pair of trousers|a pair of stockings|
@ENDMSG

@MSG	R_JACKET
@ENDMSG

@MSG	R_JUMPER
@MSGTXT a jacket|
@ENDMSG

@MSG	R_T_SHIRT
@MSGTXT a jacket|a jumper|
@ENDMSG

@MSG	R_BRA
@ENDMSG

@MSG	R_LEFT_SHOE
@ENDMSG

@MSG	R_RIGHT_SHOE
@ENDMSG

@MSG	R_LEFT_SOCK
@MSGTXT a left shoe|
@ENDMSG

@MSG	R_RIGHT_SOCK
@MSGTXT a right shoe|
@ENDMSG

@MSG	R_STOCKINGS
@MSGTXT a pair of trousers|a pair of jeans|a left shoe| a right shoe|
	a left sock|a right sock|
@ENDMSG

@REM ***********************************************************************
@REM * Now we need to actually tell the clothing handler about our objects *
@REM ***********************************************************************

@INIT @SETCOUNT(400,@OBJNO(JEANS))         @REM First obj in bank
      @SETCOUNT(401,@OBJNO(STOCKINGS))     @REM Last obj in bank
      @SETCOUNT(402,@MSGNO(W_JEANS))       @REM First msg in wear exclude bank
      @SETCOUNT(403,@MSGNO(R_JEANS))       @REM First msg in remove exclude bank

@REM *************************************************************************

@OBJ LAMP @OBJSHT a lamp @OBJLGT @OBJROOM IN_TONY @ENDOBJ

@OBJ BACON @OBJSHT a rasher of bacon @OBJEAT 10 @OBJROOM IN_JEANS 
@OBJLNG Boy oh boy, this sure does look tasty. @OBJWGT 0 @ENDOBJ

@OBJ MONSTER @OBJSHT a bacon monster @OBJACT @OBJSTR 5000 
@OBJROOM ROOM_5 @OBJINRM IN_MONSTER @OBJNGT @ENDOBJ

@ROOM IN_MONSTER @ENDROOM

@REM *************************************************************************

@MSG 	GOT_KEY
@MSGTXT The bacon monster thanks you, and hands you a small metal key.
@ENDMSG

@HIGH 

   @IF @ISHERE(MONSTER) AND (NOT @OBJROOMIS(NOWHERE,BACON)) @DO
      _samplay("\\SAMPLES\\FEEDME.SND",-1)
   @ENDIF

   @IF @ISIN(BACON,MONSTER) @DO
      @TOROOM(NOWHERE,BACON)
      @TOROOM(@OBJINRM(@PLAYER),KEY)
      @PMSG(GOT_KEY)
      @CONT
   @ENDIF

@REM *************************************************************************

@OBJ KEY @OBJSHT a small metal key @ENDOBJ 

@OBJ TRAP_DOOR @OBJSHT a trap door @OBJLCK LOCKED @OBJDOOR ROOM_5,END_ROOM
     @OBJKEY KEY @OBJNGT @ENDOBJ

@ROOM END_ROOM @ROOMSHT End room. @ROOMLNG You are in the final room. Well done,
      you have completed this pointless little adventure. @ENDROOM

@HIGH 
   @IF @ROOMIS(END_ROOM) @DO @ENDGAME @ENDIF

@REM *************************************************************************

@VERB SCREAM @VERBSYN YELL @ENDVERB

@LOW

@IF @VERBNOIS(SCREAM) @DO
   @REM Convert object number of player into range 0-5
   @REM i.e. give each player their own voice!!!!!!!!!
   @SETCOUNT(1,@OBJNO(@PLAYER)%6)
   @IF @COUNT(1) eq 0 @do _samplay("\\samples\\scream1.snd",-1) @ENDIF
   @IF @COUNT(1) eq 1 @do _samplay("\\samples\\scream2.snd",-1) @ENDIF
   @IF @COUNT(1) eq 2 @do _samplay("\\samples\\scream3.snd",-1) @ENDIF
   @IF @COUNT(1) eq 3 @do _samplay("\\samples\\scream4.snd",-1) @ENDIF
   @IF @COUNT(1) eq 4 @do _samplay("\\samples\\scream5.snd",-1) @ENDIF
   @IF @COUNT(1) eq 5 @do _samplay("\\samples\\scream6.snd",-1) @ENDIF
   @CONT
@ENDIF
