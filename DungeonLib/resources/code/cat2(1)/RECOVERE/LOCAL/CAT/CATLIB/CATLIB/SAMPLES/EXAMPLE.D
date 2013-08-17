@obj		Screaming_Cindy
@objsht		Screaming Cindy
@objplr
@objroom	Bedroom
@objinrm	In_cindy
@objstr		50
@endobj

@obj		aa_leaflet
@objsht		a crumpled leaflet
@objlng		Just an ordinary crumpled leaflet.
@objread	read_aa_leaflet
@objroom	In_cindy
@endobj

@msg		Read_aa_leaflet
@msgtxt		The leaflet is far too crumpled to read.
@endmsg

@obj		ab_leaflet
@objsht		a beautifully uncrumpled leaflet
@objlng		...beautifully uncrumpled!
@objread	read_ab_leaflet
@endobj

@msg		Read_ab_leaflet
@msgtxt		The leaflet says 'Thankyou for uncrumpling me'.
@endmsg

@room In_cindy @endroom

@room 		Bedroom
@roomsht	Bedroom.
@roomlng	You are in a bedroom. Suprisingly, there are no exits.
		You feel like screaming.
@endroom

@verb uncrumple @verbsyn straighten @verbchk carried @endverb

@verb scream @endverb

@init @become(screaming_cindy)
      _samplay("\\samples\\hithere.snd",-1)
      @waitkey
      @setcount(1,1)
      @while @count(1) lt 4 @do
         _samplay("\\samples\\hithere.snd",@count(1))
         @addcount(1,1)
         @waitkey
      @wend
@low

@if @verbnois(uncrumple) and @nounnois(aa_leaflet) @do
   @swap(aa_leaflet,ab_leaflet)
   @pmsg(okay)
   @cont
@endif

@if @verbnois(scream) @do
   @setcount(1,@random(5))
   @if @count(1) eq 1 @do
      _samplay("\\samples\\scream1.snd",-1)
   @endif
   @if @count(1) eq 2 @do
      _samplay("\\samples\\scream2.snd",-1)
   @endif
   @if @count(1) eq 3 @do
      _samplay("\\samples\\scream3.snd",-1)
   @endif
   @if @count(1) eq 4 @do
      _samplay("\\samples\\scream4.snd",-1)
   @endif
   @if @count(1) eq 5 @do
      _samplay("\\samples\\scream5.snd",-1)
   @endif
   @pmsg(okay)
   @cont
@endif

