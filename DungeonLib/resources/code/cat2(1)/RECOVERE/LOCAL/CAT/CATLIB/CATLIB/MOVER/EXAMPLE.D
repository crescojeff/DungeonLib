@REM ******************************************************************
@REM * First of all, I'll define some rooms - some are dark           *
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
@ROOMSHT ROOM 4.
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
@REM * Now, I'll create a bunch of players!                           *
@REM ******************************************************************

@OBJ TOM @OBJSHT Tom
@OBJPLR @OBJSTR 10 @OBJROOM ROOM_1 @OBJINRM IN_TOM @OBJNGT
@ENDOBJ
@ROOM IN_TOM @ENDROOM


@OBJ DICK @OBJSHT Dick
@OBJPLR @OBJSTR 10 @OBJROOM ROOM_1 @OBJINRM IN_DICK @OBJNGT
@ENDOBJ
@ROOM IN_DICK @ENDROOM


@OBJ HARRY @OBJSHT Harry
@OBJPLR @OBJSTR 10 @OBJROOM ROOM_1 @OBJINRM IN_HARRY @OBJNGT
@ENDOBJ
@ROOM IN_HARRY @ENDROOM


@OBJ TONY @OBJSHT Tony
@OBJPLR @OBJSTR 10 @OBJROOM ROOM_1 @OBJINRM IN_TONY @OBJNGT
@ENDOBJ
@ROOM IN_TONY @ENDROOM


@OBJ SIMON @OBJSHT Simon
@OBJPLR @OBJSTR 10 @OBJROOM ROOM_1 @OBJINRM IN_SIMON @OBJNGT
@ENDOBJ
@ROOM IN_SIMON @ENDROOM


@OBJ SARA @OBJSHT Sara
@OBJPLR @OBJSTR 10 @OBJROOM ROOM_1 @OBJINRM IN_SARA @OBJNGT
@ENDOBJ
@ROOM IN_SARA @ENDROOM


@OBJ MARK @OBJSHT Mark
@OBJPLR @OBJSTR 10 @OBJROOM ROOM_1 @OBJINRM IN_MARK @OBJNGT
@ENDOBJ
@ROOM IN_MARK @ENDROOM


@OBJ LISA @OBJSHT Lisa
@OBJPLR @OBJSTR 10 @OBJROOM ROOM_1 @OBJINRM IN_LISA @OBJNGT
@ENDOBJ
@ROOM IN_LISA @ENDROOM


@OBJ ANDREW @OBJSHT Andrew
@OBJPLR @OBJSTR 10 @OBJROOM ROOM_1 @OBJINRM IN_ANDREW @OBJNGT
@ENDOBJ
@ROOM IN_ANDREW @ENDROOM


@OBJ ANT @OBJSHT Ant
@OBJPLR @OBJSTR 10 @OBJROOM ROOM_1 @OBJINRM IN_ANT @OBJNGT
@ENDOBJ
@ROOM IN_ANT @ENDROOM


@REM *************************************************************************
@REM I've included a lamp for testing purposes
@REM *************************************************************************

@OBJ LAMP @OBJSHT a lamp @OBJLGT @OBJROOM IN_TONY @ENDOBJ

@REM *************************************************************************
@REM Set initial player, and define active mover object bank.
@REM *************************************************************************

@INIT
@BECOME(TONY)
@SETCOUNT(404,TOM) @REM First object to include in mover.
@SETCOUNT(405,ANT) @REM Last object to include in mover.

@REM *************************************************************************


