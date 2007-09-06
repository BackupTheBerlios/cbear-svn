@call %cbear%cbear.berlios.de/cms/svn/one.build.bat
@%nxslt2% -o %target%_build.bat %target%_svn.info.xml %cbear%/cbear.berlios.de/cms/svn/build.xsl xmlns:C=http://cbear.berlios.de/cms C:target=%target%
@call %target%/_build.bat