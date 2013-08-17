

*****************************************************************
                      >>>   ShareWare   <<<
*****************************************************************


     This is a SHARWARE product. If you continue to use Smart 
Play, this means you must like it (or like to use it). All I ask 
is if you like to use Smart Play you send me $5.00 (Check or money 
order). Registered users get discounts on other software products 
written by me, such as Digi-Mix a full featured paint and bit 
block editor and Outer Limits a fast paced action game (includes 
GFA Basic 2.0 source code). They also get upgrades at a very low 
cost.  



                         Smart Play Documentation
                         ========================
          Many computer owners are now discovering digitized sound 
     samples. You probably own one or two games that use some type 
     of digitized sound in it. Some animation packages now have 
     the ability to incorporate sound samples in there sequence 
     files. This makes for some great affects. The applications 
     are limitless.
     
          Now you can enjoy listening to sound samples without 
     buying an expensive interface cartridge. There are now lots 
     of sound sample files available on BBS's across the United 
     States.
     
          Smart Play has basically two different functions, edit 
     and play sound sample files. With Smart Play you can edit and 
     save any sound file you load in to memory. There are two 
     ways to play sound samples with Smart Play. The first is to 
     simply load the sound sample, select the play speed and 
     select the play selection. The second is to load a sound 
     sample file into memory and append the last byte in the 
     sample to show the speed of the sample (I will talk more on 
     this later). By using the latter method you can play sounds one 
     after another using yet another feature called "Autoplay".

          The source code contains a special section on how to 
     load and play ST-Reply sound files.
     
     FILES
     =====
     
          You should have the following files:
               READ_ME.TXT
               BASECODE.EXE
               SMART_PL.PRG
     
          For Smart Play to run successfully you must have both 
     SMART_PL.PRG and BASECODE.EXE in the same folder/directory.
     
     REQUIREMENTS
     ============
     
          Smart Play will run on the Atari 520ST, 520FM, 1040ST, 
     Mega 2 and Mega 4. You may use a color or monochrome 
     monitor in any resolution. 
     
     FUNCTIONS
     =========
     
     LOAD SPL.
     =========
               
           To load a sound sample simply select "LOAD 
     SPL.". A file select dialog box will appear and you simply 
     pick your file and select "OK". Once the file is loaded into 
     memory you can edit or play the file. If the sound file has 
     allready been appended the speed will be set automatically.
     
     PLAY SPL.
     =========
     
          No mysteries here just select "PLAY SPL." and you will 
          the sound sample that is currently in memory.
     
     SAVE SPL.
     =========
     
          There are three way you can save a sound sample. The 
     first is after loading a sample you save it WITHOUT editing. 
     The second is after loading a sample you edit the sample, 
     then save the edited sample (Using the Editor). The third is 
     after selecting append (see "APND.") you re-save the sample.
     
     APND.
     =====
     
          In order to have sound samples load and play in the correct 
     speed or "Khz" you must append the current sample in memory. 
     This is done by first loading a sample into memory. You may 
     at this time do some editing if you wish. Next select the 
     proper speed setting (your really setting the proper 
     frequency, but speed is easier to relate to). Now select the 
     "APND." function and re-save the sample. 
     
          By selecting to append the sample you are changing the 
     first byte in the sample file. Later when you choose the 
     "AUTOPLAY" function the program will look at that first byte 
     to see what speed the sample should be played at. THIS DOES 
     NOT AFFECT THE QUALITY OF THE SAMPLE! 
     
          Even though a sample has been appended by Smart Play it 
     does not affect the samples play quality. Other sample 
     players/editors can use appended sample from Smart Play with 
     no ill affects at all.
     
     AUTOPLAY
     ========
     
          To automatically play sample files select "AUTOPLAY". 
     This option works much in the same way slide show programs 
     for picture files do. You simply pick the drive and 
     path/folder name and chose if Smart Play should look for that 
     appended byte for speed adjustment. Once this is done Smart 
     Play WILL LOAD ANY FILE WITH THE EXTENSION ".SPL". This 
     extension is commonly accepted as meaning "SAMPLE".
     
          To exit from "AUTOPLAY" just hold down the right mouse 
     button until the mouse cursor turns back into a pointer.
      
     Speed of Sample
     ===============
     
          In the mid right hand corner of the screen you will see 
     a box with an arrow on each side of it. This box is used to 
     select the speed the sample will play at. 
     
          To use this function simply click on one of the arrows. 
     Clicking on the left arrow will make your sample play slower, 
     clicking on the right arrow will make the sample play faster. 
     If you do not know the speed a sample should be played at, 
     just increase or decrease the speed until it sounds right 
     when played. 
     
          IMPORTANT! If you intend to appended a file for 
     "AUTOPLAY" make sure you have first chosen the correct speed 
     for that sample. The best way to avoid appending with wrong 
     speed is to play the sample just before you append it for 
     "AUTOPLAY". If you do append a sample with wrong speed simply 
     re-append it with the correct speed.
     
     EDITOR
     ======
     
          Using the editor is very simple. First load a sample 
     into memory. Now note the two small boxes with arrows facing 
     in opposite directions. Clicking one of these arrows will 
     allow you to edit your sample.
     
          The box above is used to gauge your sample. This box 
     represents your entire sample no matter how small or large it 
     may be. By clicking on the arrows directly below you can cut 
     out section from your sample and save them.  

          After you have begun editing you can select "PLAY SPL." 
     to hear what the edited sample sounds like. When you have 
     finished editing your sample you can save it by simply 
     selecting "SAVE SPL.". 
     
          To select the speed of the editor note the two small 
     boxes with "S" and "F", just below the editor. If you select 
     "S" the editor will run at a slow rate. If you select "F" the 
     editor will run at a fast rate. 
     
     
                             TA-DAAAAA
          Well that just about says it all. If you program in GFA 
     Basic you might be interested in the source code. You can 
     really spruce up a program by adding a sample or two to it. 
    
          I hope you enjoy using Smart Play.
     
     



                                        >Richard R Betson
                                        >543 E. 4th AVE.
                                        >Escondido, CA  92025

                                        >GEnie Mail "TALON.TECH"
                                        >SDACE BBS 619-284-3821


