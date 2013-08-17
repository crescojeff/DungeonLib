@room		room1
@roomsht	The first room.
@roomlng	This is the first room in the game.
@roompth	north,room2 east,room2 west,room2 south,room2
@endroom

@room		room2
@roomsht	The second room.
@roomlng	This is the second room in the game.
@roompth	north,room3 east,room3 west,room3 south,room3
@endroom

@room		room3
@roomsht	The maze.
@roomlng	You are in a maze of twisty little passages, all alike.
@roompth	north,room3 east,room3 west,room3 south,room3
@endroom


@obj 		joe
@objplr
@objsht 	Joe
@objlng 	Joe Punter is just an average guy.
@objroom 	room1
@objinrm 	In_Joe
@objwgt		125
@objstr 	100
@endobj

@room		in_joe
@roomsht	Carried by Joe.
@roomlng	You are being carried by Joe.
@roompth	down,carried
@endroom

@obj 		zoe
@objplr
@objsht 	Zoe
@objlng 	Zoe Punter is just an average guy.
@objroom 	room2
@objinrm 	In_Zoe
@objwgt		125
@objstr 	100
@endobj

@room		in_zoe
@roomsht	Carried by Zoe.
@roomlng	You are being carried by Zoe.
@roompth	down,carried
@endroom

@obj 	 	credit_card
@objsyn		card
@objsht  	a credit card
@objlng  	The credit card has the usual attributes:  a number that 
			exceeds the number of atoms in the universe, a hologram
			of Frank Zappa, a magnetic stripe, and an indecipherable
			signature - yours. Moreover, it appears to be valid.
@objroom 	room2
@endobj

@init
	@become(joe)


