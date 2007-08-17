rem Boost 1.34.1
cd c:\boost_1_34_1\tools\jam\
call build_dist.bat
cd c:\boost_1_34_1\
C:\boost_1_34_1\tools\jam\src\bin.ntx86\bjam.exe --toolset=msvc --toolset=borland install

