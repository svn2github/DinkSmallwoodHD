cd ..\android
call build.bat
@ECHO ON
set D_FILE_NAME=%APP_NAME%-unprotected.apk
del ..\%D_FILE_NAME%
copy bin\%APP_NAME%-debug.apk ..\%D_FILE_NAME%
cd ..
set d_fname=%D_FILE_NAME%
call script\FTPToSite.bat
cd script
pause