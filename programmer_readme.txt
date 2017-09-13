Dink Smallwood HD

-- How to compile and run:

* First, be able to compile and run the proton example RTSimpleApp.  More info at www.protonsdk.com on installing and setting up proton
* Move the RTDink directory checkout to a sub directory of your proton dir. (it works exactly like a proton example - you can still svn update/commit like normal, svn allows you to move around dirs like that)
* Sign up at fmod.com and download FMod Studio for Windows.  Unzip to <proton dir>\shared\win\fmodstudio, so you should have a proton\shared\win\fmodstudio\api dir, etc.
* Install Visual Studio 2017 (Community version works fine and is free) and open RTDink\windows_vs2017\iPhoneRTDink.sln
* By default, Proton SDK's main.cpp is setup to compile for iPhone most likely.  Assuming you'd rather not have an iPhone build, search the project for "//WORK: Change device emulation here" and right under that,
	change it from string desiredVideoMode = "iPhone Landscape"; or whatever it was to "string desiredVideoMode = "Windows"; instead.  (this is where you can emulate many devices and sizes)
* Set the profile to "Release GL" and "Win32".  (or "Debug GL" is ok too)  Compile.  If it worked, you should have a dink.exe created in DinkHD/bin.
* Install DinkHD from rtsoft.com. (media is not svn, so this is a way to get it..)  Overwrite its dink.exe with your new one.  It should run!




Use the "Debug GL" or "Release GL" solution configuations.

--- Have a bugfix or patch?! Please send it over to Seth!  Please note that any submission (code, media, translations, ect) must be 100% compatible with the license as listed in dinkhd_license.txt

See script/installer/readme.txt for what's new info.
