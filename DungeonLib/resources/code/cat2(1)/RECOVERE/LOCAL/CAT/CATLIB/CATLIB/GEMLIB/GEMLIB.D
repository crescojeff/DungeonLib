@rem **************************************************************************
@rem * CAT GEM AES functions, by Martyn Dryden of                             *
@rem *                                  The South West Software Library       *
@rem **************************************************************************

@Rem This file contains interfaces to C routines which will allow use of the
     GEM file selector when loading/saving games, and also to turn the mouse
     pointer off/on at appropriate times.

     Details on interfacing external C functions into CAT definitions can be
     found in the CATEXPRT folder on the CAT distribution disk.

     NOTE: These functions are only suitable for the Atari ST, and also the
           save/load functions may need some changes along with future 
           releases of CAT. Your compiler must provide an AES library.
           Users of Sozobon C -> an AES library has been included.

@rem **************************************************************************

@REM Messages related to loading/saving

@msg		cancelled
@msgtxt		Operation cancelled.
@endmsg

@msg		failed
@msgtxt		Operation failed.
@endmsg

@msg		saving
@msgtxt		Saving game as
@endmsg

@msg		loading
@msgtxt		Loading game from
@endmsg

@rem **************************************************************************

@REM When the program loads, we initialise AES etc, and turn the mouse off.
     
@first
   _init_aes()                   @REM ext function defined in csource\x.c
   _mseoff()                     @REM ext function defined in csource\x.c

@rem **************************************************************************

@low

@if @verbnois(save) @do

   @rem If the GEM load/save functions are available
   @rem then we use the GEM File Selector save routine
   @rem else we fall through to the default save routine

   @if _gem_avail() @do          @REM ext function defined in csource\x.c
      _xsave()                   @REM ext function defined in csource\x.c
      @stop
   @endif

@endif

@if @verbnois(load) @do

   @rem If the GEM load/save functions are available
   @rem then we use the GEM File Selector load routine
   @rem else we fall through to the default load routine

   @if _gem_avail() @do          @REM ext function defined in csource\x.c
      _xload()                   @REM ext function defined in csource\x.c
      @stop
   @endif

@endif

@rem **************************************************************************

@REM Just before leaving the program, turn the mouse back on and kill AES.
 
@last 
   _mseon()                      @REM ext function defined in csource\x.c
   _end_aes()                    @REM ext function defined in csource\x.c

