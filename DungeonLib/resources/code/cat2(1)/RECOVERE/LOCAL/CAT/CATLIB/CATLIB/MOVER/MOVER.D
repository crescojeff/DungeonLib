@rem **************************************************************************
@rem * CAT active object mover - written by Tony Stiles July 1991             *
@rem *                                                                        *
@rem **************************************************************************

@rem This file contains an active object mover suitable for CAT version 2 and
     upwards. This code will randomly move a selected group of active objects
     around their environment. For each active object in the group, a random
     number between 1-6 is generated. These map to North, East, South, West,
     Up and Down. If there is a path leading from the objects room in the 
     selected direction - then the object will be moved. The user will be 
     advised of the movements if he is in a position to be able to see!

     All objects to be 'moved' should be defined in one consecutive bank,
     and the bank should be defined with counters 404 and 405, in
     initialisation logic.

@rem *********************************************************************

     Presuming the bank of objects has been defined, these need to be
     introduced to CAT in initialisation logic. 

     Counter 404 should be set to the first object number to be included in
                 the movement handler.

     Counter 405 should be set to the last object number to be included in
                 the movement handler.

@rem *********************************************************************

@rem A full example can be found in 'EXAMPLE.D'

     This file should be included in your GENLIST before ZZSTD.D and ZZRQD.D

@rem *********************************************************************

@HIGH
@REM Start at the beginning of the bank.
@SETCOUNT(498,@COUNT(404))
@REM Process each object in the bank.
@WHILE @COUNT(498) LE @COUNT(405) @DO
   @REM Ignore the object if it is the current player
   @IF (NOT @PLAYERIS(@COUNT(498))) AND (NOT @CPLAYERIS(@COUNT(498))) AND
      @ISACTIVE(@COUNT(498)) @DO
      @REM Save the object number of the current player
      @SETCOUNT(494,@PLAYER)
      @REM Obtain random number between 1-6, corresponding to one of 6 exits.
      @SETCOUNT(495,@RANDOM(6))
      @REM Change the character
      @CONTROL(@COUNT(498))

      @REM If north selected, make sure exit exists and move.

      @IF @COUNT(495) EQ 1 AND @VERBPATH(NORTH) NE -1 @DO
         @REM Only report movement if the player should be able to see!
         @IF @ISHERE(@COUNT(494)) AND (NOT @ISDARK) @DO
            @POBJS(@PLAYER)
            @PMSG(GOES_NORTH)
         @ENDIF
         @TOROOM(@VERBPATH(NORTH),@PLAYER)
         @IF @ISHERE(@COUNT(494)) AND (NOT @ISDARK) @DO
            @POBJS(@PLAYER)
            @PMSG(ENTERS_FROM_SOUTH)
         @ENDIF
      @ENDIF

      @REM If east selected, make sure exit exists and move.

      @IF @COUNT(495) EQ 2 AND @VERBPATH(EAST) NE -1 @DO
         @REM Only report movement if the player should be able to see!
         @IF @ISHERE(@COUNT(494)) AND (NOT @ISDARK) @DO
            @POBJS(@PLAYER)
            @PMSG(GOES_EAST)
         @ENDIF
         @TOROOM(@VERBPATH(EAST),@PLAYER)
         @IF @ISHERE(@COUNT(494)) AND (NOT @ISDARK) @DO
            @POBJS(@PLAYER)
            @PMSG(ENTERS_FROM_WEST)
         @ENDIF
      @ENDIF

      @REM If south selected, make sure exit exists and move.

      @IF @COUNT(495) EQ 3 AND @VERBPATH(SOUTH) NE -1 @DO
         @REM Only report movement if the player should be able to see!
         @IF @ISHERE(@COUNT(494)) AND (NOT @ISDARK) @DO
            @POBJS(@PLAYER)
            @PMSG(GOES_SOUTH)
         @ENDIF
         @TOROOM(@VERBPATH(SOUTH),@PLAYER)
         @IF @ISHERE(@COUNT(494)) AND (NOT @ISDARK) @DO
            @POBJS(@PLAYER)
            @PMSG(ENTERS_FROM_NORTH)
         @ENDIF
      @ENDIF

      @REM If west selected, make sure exit exists and move.

      @IF @COUNT(495) EQ 4 AND @VERBPATH(WEST) NE -1 @DO
         @REM Only report movement if the player should be able to see!
         @IF @ISHERE(@COUNT(494)) AND (NOT @ISDARK) @DO
            @POBJS(@PLAYER)
            @PMSG(GOES_WEST)
         @ENDIF
         @TOROOM(@VERBPATH(WEST),@PLAYER)
         @IF @ISHERE(@COUNT(494)) AND (NOT @ISDARK) @DO
            @POBJS(@PLAYER)
            @PMSG(ENTERS_FROM_EAST)
         @ENDIF
      @ENDIF

      @REM If up selected, make sure exit exists and move.

      @IF @COUNT(495) EQ 5 AND @VERBPATH(UP) NE -1 @DO
         @REM Only report movement if the player should be able to see!
         @IF @ISHERE(@COUNT(494)) AND (NOT @ISDARK) @DO
            @POBJS(@PLAYER)
            @PMSG(GOES_UP)
         @ENDIF
         @TOROOM(@VERBPATH(UP),@PLAYER)
         @IF @ISHERE(@COUNT(494)) AND (NOT @ISDARK) @DO
            @POBJS(@PLAYER)
            @PMSG(ENTERS_FROM_DOWN)
         @ENDIF
      @ENDIF

      @REM If down selected, make sure exit exists and move.

      @IF @COUNT(495) EQ 6 AND @VERBPATH(DOWN) NE -1 @DO
         @REM Only report movement if the player should be able to see!
         @IF @ISHERE(@COUNT(494)) AND (NOT @ISDARK) @DO
            @POBJS(@PLAYER)
            @PMSG(GOES_DOWN)
         @ENDIF
         @TOROOM(@VERBPATH(DOWN),@PLAYER)
         @IF @ISHERE(@COUNT(494)) AND (NOT @ISDARK) @DO
            @POBJS(@PLAYER)
            @PMSG(ENTERS_FROM_UP)
         @ENDIF
      @ENDIF

      @REM Restore the original player
      @CONTROL(@COUNT(494))

   @ENDIF

   @REM Move onto next object in the bank.
   @ADDCOUNT(498,1)

@WEND

@MSG 	GOES_NORTH 		@MSGTXT goes north. @ENDMSG
@MSG	ENTERS_FROM_NORTH 	@MSGTXT enters from the north. @ENDMSG
@MSG 	GOES_EAST 		@MSGTXT goes east. @ENDMSG
@MSG	ENTERS_FROM_EAST 	@MSGTXT enters from the east. @ENDMSG
@MSG 	GOES_SOUTH 		@MSGTXT goes south. @ENDMSG
@MSG	ENTERS_FROM_SOUTH 	@MSGTXT enters from the south. @ENDMSG
@MSG 	GOES_WEST 		@MSGTXT goes west. @ENDMSG
@MSG	ENTERS_FROM_WEST 	@MSGTXT enters from the west. @ENDMSG
@MSG 	GOES_UP 		@MSGTXT goes up. @ENDMSG
@MSG	ENTERS_FROM_UP 		@MSGTXT comes down. @ENDMSG
@MSG 	GOES_DOWN 		@MSGTXT goes down. @ENDMSG
@MSG	ENTERS_FROM_DOWN 	@MSGTXT comes up. @ENDMSG


