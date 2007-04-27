call config.bat

cd "%ROOT%\cbear.berlios.de\api\examples
mkdir "%ROOT%\global"
"%NXSLT2%\nxslt2" api.xml "%ROOT%\cbear.berlios.de\api\build.xsl" -o "%ROOT%\global\_build.bat.xml"
"%NXSLT2%\nxslt2" "%ROOT%\global\_build.bat.xml" "%ROOT%\cbear.berlios.de\bat\main.xsl" -o %ROOT%\global\_build.bat"
call "%ROOT%\global\_build.bat"