set INCLUDE=C:\Program Files\Microsoft SDKs\Windows\v6.0\Include\;%2\include;%INCLUDE%
set LIB=C:\Program Files\Microsoft SDKs\Windows\v6.0\Lib\;%LIB%
set PATH=%2\bin;%PATH%
rem Boost 1.34.1
cd %1\boost_1_34_1\tools\jam\
call build_dist.bat
cd %1\boost_1_34_1\
%1\boost_1_34_1\tools\jam\src\bin.ntx86\bjam.exe --toolset=msvc --toolset=borland --toolset=dmc install

