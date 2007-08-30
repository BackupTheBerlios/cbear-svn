call one.build.bat %2
c:\nxslt-2.3-bin\nxslt2 -o %2/_build.bat %2/_svn.info.xml %1/cbear.berlios.de/cms/svn/build.xsl
%2/_build.bat