Dink Smallwood HD for Windows 7, 8, 10.

Requires OpenGL, if you have any problems running this, try installing the latest video drivers for your video card/chip.

To change screen size, drag the window borders around.  (Hold shift while dragging to toggle aspect-ratio lock)
To toggle a psuedo full screen mode, click Full Screen Toggle in the options.  (Or hit Alt-Enter)

NOTE: Quick saves might give a "Can't load old version" error if the data format has changed.  However, normal Dink saves (using save machines, etc) will always work.

Controls:

F1 - Quick save
F10 - Quick load
Control - Attack
Arrow keys - Movement
Space - Talk
Enter - Inventory
Shift - Magic
Escape - Bring up menu
Drag on window borders - scale the play area (when windowed)

NOTE: If you have a controller (like an xbox 360 pad) plugged in when you start the game, you can use that instead of keyboard, but you still need to use the
mouse to navigate the initial menus to start the game

Supported command line options:

-game <dmod directory> (Example:  dink.exe -game c:\dmods\island ) (this also sets -dmodpath automatically to the dmods parent directory)
-dmodpath <dir containing DMOD dirs> (Example:  dink.exe -game c:\dmods )


------------- BETA VERSION -----------------

This is a beta version which means it probably has bugs and isn't ready for general consumption.  However, it means you've been recruited to help us make it better!

To report a bug, find or post a thread about Dink HD on dinknetwork.com and and please include the following information if you can:

- Dink files are installed to C:\Users\<user name>\AppData\Local\DinkSmallwoodHD by default.

- Description of the bug and how to recreate it
- If the bug takes work to get to, it would be great if you could "Quick save" in the game and add a URL to download the quicksave.dat file.

quicksave.dat should be located in C:\Users\<user name>\AppData\Local\DinkSmallwoodHD for the main game and C:\Users\<user name>\AppData\Local\DinkSmallwoodHD\dmods\<dmod dir> for DMODs.

- The DMOD name (and URL to download it if possible)
- Windows version you're playing on
- Screen mode/resolution
- If the game crashes, please include the log.txt file as it may contain information about the crash.

-Seth (seth@rtsoft.com)
www.rtsoft.com

------ Change log for 1.7.0 ----------

* Upgraded source projects to Visual Studio 2017 (free community edition works fine)
* (bugfix) No longer forces reload of all graphics when saving the state
* (bugfix) No longer forces reload of all graphics and audio when losing focus/going into the background
* (bugfix) Fixed issue where screen scrolling could bug out if window was resized on windows
* Latest state data to "Continue" persists even if the game crashes now
* Added support for 64 bit builds (still fully compatible with existing save states/games)
* Added support for aspect ratio correction (can be disabled by enabling "Fullscreen stretch" in the options)
* Added IPV6 support
* (DinkC) Goto statements no longer require a ; at the end to work
* (iOS) Now compatible with iOS 11
* (Windows) Installer no longer requires admin privileges, now installs to local user's appdata dir (C:\UserName\AppData\Local\DinkSmallwoodHD)
* (Windows) .exe and installer are now signed with RTsoft's distribution certificate
* (Windows) Now checks for new versions on startup
* (Windows) Now writes the stack trace to log.txt if the game crashes (helps debug problems)

------ Change log for 1.7.1 ----------

(big thanks to Redink1 for most of these bug reports and the fancy shadows patch!)

* (Windows) Fixed app icon
* (Windows) Mouse-controlled screens in DMODs control better and hide the original mouse cursor
* (Windows) Now remembers screen size and fullscreen mode (don't forget, you can drag the window corners around to customize the screen size as well)
* (Windows) Input URL input area gets focus by default when installing a DMOD by URL
* (bugfix) Can no longer tap F8 during a game load to load a save state too early which can freeze the game
* (bugfix) Fixed issue where 32 bit tilebitmaps would go wonky when reloading the surface
* Default color under status bar is now black, fixes issue when transparent colors are used in the stats area, random garbage would show through
* (windows) Version # is now shown in title bar
* (bugfix) Fixed some issues with how default offsets are calculated, it fixed some problems where sprites would be in the wrong place in certain DMODs
* (bugfix, windows) "Smoothing" no longer incorrectly turns on if you lose/regain focus
* (windows) Added "Windowed Borderless fullscreen mode" toggle, defaults to off.  It will try to do 640X480 at your native monitor resolution by default now on
	a clean install. If you've dragged the dink window to a weird size it won't be able to go fullscreen which is kind of weird, but it does give a clear error message. It should probably
	enumerate graphic modes and choose one if the current one is invalid, or let the user choose, meh
* Added redink1's "soft shadow improvement" patch
* (proton) Fixed issue with blitting alpha things to the background, fixed the soft shadows for things rendered into the background

------ Change log for 1.7.2 ----------

* Changed "FPS lock:" to "Lock to 30 FPS:" in options, makes it more clear it's actually bad to use and not vsync
* (Windows) Handles alt-tab and clicking on a different monitor while in native fullscreen modes better
* Added "Ghost walk toggle" to in-game cheat menu.  Allows you to walk through solid objects and screenlocks
* (DinkC) Added support for Dan's load_tile() command
* (Windows) Added support for -game <dmod directory> parm to load a DMOD from anywhere on your HD. It also sets 
	the active DMOD dir to the DMODs parent directory for that session.  Automatic state autosave, save/continue and quicksave/quickload work as expected by saving data to its directory
* (bugfix) Save states now properly load even if the DMOD directory has been cut and pasted to a new place
* (bugfix) Full state saves now properly setup backgrounds with correct vision modifications instead of assuming it was 0
- Due to minor changes in the save state stuff, I've versioned it so the game will refuse to load old versions (as always, this doesn't affect the normal save files, just the full state saves HD does)
* (DinkC) fill_screen works better and colors 0 and 255 are no longer sometimes reversed
* (bugfix) M can now be used to turn off the map, previously it only worked to turn it on
* (bugfix) Status no longer incorrectly draws over full screen bitmaps (like the map in Mystery Island) and is properly reconstructed in full save states

------ Change log for 1.7.3 ----------

* (DinkC) DinkC version is now reported as 110 instead of 109
* (Bugfix) Fixed issue with set_frame_frame, the DMOD Mayhem now works
* (Bugfix) Fixed another incorrect color issue with fill_screen (This fixed Initiation's title screen)
* (Bugfix) Fixed horrible issue where the last line in a script might not get run.  This fixed the intro screen to Lost Forest Romp
* (Bugfix) Rewrote some nasty code that I could no longer understand, THE LAST QUEST (part 2)'s cool room slide/warp effect now works right
* Added "Debug DinkC Toggle" to cheat menu, it shows collision boxes and causes the log (log.txt or choose view log from debug menu)
* If fullscreen is at a weird size it will now just force it to 1024X768.  If that fails, well, it won't be good
- Note:  Save state format has been changed again, so old save states won't load

------ Change log for 1.7.4 ----------

* (Bugfix) Fixed a script crash.  This bug was also in the legacy dink
* (Windows) "Tap to continue" is no longer shown when waiting for a keypress, but will still be shown on touch-devices
* Fixed bug where any DMOD directory starting with "dink" was ignored from the internal DMOD listing screen.  Oops, that was a pretty bad one, sorry dinkcrft.