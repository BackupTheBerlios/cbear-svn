rem Boost 1.33.1
cd c:\boost_1_33_1\tools\build\jam_src\
call build.bat
call "C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\SetEnv.Cmd"
cd c:\boost_1_33_1\
C:\boost_1_33_1\tools\build\jam_src\bin.ntx86\bjam.exe "-sTOOLS=mingw vc-8_0" "-sMINGW_ROOT_DIRECTORY=c:\mingw" "-sPYTHON_ROOT=c:\python24" "-sPYTHON_VERSION=2.4" install
