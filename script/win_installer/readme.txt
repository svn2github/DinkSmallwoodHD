Dink Smallwood HD for Windows 7, 8, 10.

Requires OpenGL, if you have any problems running this, try installing the latest video drivers for your video card/chip.

To change screen size, drag the window borders around.  (Hold shift while dragging to toggle aspect-ratio lock)
To toggle a psuedo full screen mode, click Full Screen Toggle in the options.  (Or hit Alt-Enter)

NOTE: Quick saves might give a "Can't load old version" error if the data format has changed.  However, normal Dink saves (using save machines, etc) will always work.

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

(big thanks to Redink1 for most of these bug reports!)

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