cd c:\cbear\cbear.berlios.de\api\examples
mkdir c:\cbear\global
c:\nxslt-2.1\nxslt2 api.xml c:\cbear\cbear.berlios.de\api\build.xsl -o c:/cbear/global/_build.bat.xml
c:\nxslt-2.1\nxslt2 c:/cbear/global/_build.bat.xml c:\cbear\cbear.berlios.de\bat\main.xsl -o c:/cbear/global/_build.bat
call c:/cbear/global/_build.bat