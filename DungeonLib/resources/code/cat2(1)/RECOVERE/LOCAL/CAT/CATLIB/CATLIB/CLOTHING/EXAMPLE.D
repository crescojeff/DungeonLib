@REM CAT clothing handler example usage.


@REM First, we need to define a player and a start room.

@ROOM 		TEST_ROOM
@ROOMSHT 	The closet.
@ENDROOM

@OBJ 		MR_CLOTHES
@OBJSHT 	Mr clothes
@OBJROOM 	TEST_ROOM
@OBJPLR
@OBJSTR		20
@OBJINRM	IN_CLOTHES
@ENDOBJ

@ROOM IN_CLOTHES @ENDROOM

@INIT @BECOME(MR_CLOTHES)


@REM **************************************************************************
@REM * Okay, now we need to define each of the objects that are to be handled *
@REM * by the clothing handler. It is important that all of these objects     *
@REM * follow directly after the other, i.e. without any other objects in     *
@REM * between.                                                               *
@REM **************************************************************************

@OBJ		JEANS
@OBJSHT		a pair of jeans
@OBJWEAR
@OBJROOM	TEST_ROOM
@ENDOBJ

@rem *********************************************************************

@OBJ		TROUSERS
@OBJSHT		a pair of trousers
@OBJWEAR
@OBJROOM	TEST_ROOM
@ENDOBJ

@REM *********************************************************************

@OBJ		SKIRT
@OBJSHT		a skirt
@OBJWEAR
@OBJROOM	TEST_ROOM
@ENDOBJ

@rem *********************************************************************

@OBJ		KNICKERS
@OBJSHT 	a pair of knickers
@OBJWEAR	
@OBJROOM 	TEST_ROOM
@ENDOBJ

@REM *********************************************************************

@OBJ		PANTS
@OBJSHT		a pair of pants
@OBJWEAR
@OBJROOM	TEST_ROOM
@ENDOBJ

@REM *********************************************************************

@OBJ		JACKET
@OBJSHT		a jacket
@OBJWEAR
@OBJROOM	TEST_ROOM
@ENDOBJ

@REM *********************************************************************

@OBJ		JUMPER
@OBJSHT		a jumper
@OBJWEAR
@OBJROOM	TEST_ROOM
@ENDOBJ

@REM *********************************************************************

@OBJ		T_SHIRT
@OBJSHT		a t shirt
@OBJWEAR
@OBJROOM	TEST_ROOM
@ENDOBJ

@REM *********************************************************************

@OBJ		BRA
@OBJSHT		a bra
@OBJWEAR
@OBJROOM	TEST_ROOM
@ENDOBJ

@REM *********************************************************************

@OBJ		LEFT_SHOE
@OBJSHT		a left shoe
@OBJWEAR
@OBJROOM	TEST_ROOM
@ENDOBJ

@REM *********************************************************************

@OBJ		RIGHT_SHOE
@OBJSHT		a right shoe
@OBJWEAR
@OBJROOM	TEST_ROOM
@ENDOBJ

@REM *********************************************************************

@OBJ		LEFT_SOCK
@OBJSHT		a left sock
@OBJWEAR
@OBJROOM	TEST_ROOM
@ENDOBJ

@REM *********************************************************************

@OBJ		RIGHT_SOCK
@OBJSHT		a right sock
@OBJWEAR
@OBJROOM	TEST_ROOM
@ENDOBJ

@REM *********************************************************************

@OBJ		STOCKINGS
@OBJSHT		a pair of stockings
@OBJWEAR
@OBJROOM	TEST_ROOM
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

@REM ***********************************************************************

