set nxslt=c:/nxslt-1.6.4/bin/nxslt
set cbear=c:/cbear/
%nxslt% index.xml %cbear%cbear.berlios.de/cms/cbear.list.xsl  -o _list.bat.xml xmlns:C=http://cbear.berlios.de/cms C:nxslt=%nxslt% C:cbear=%cbear% C:html=%cbear%cbear.berlios.de/cms/cbear.xsl
%nxslt% _list.bat.xml %cbear%cbear.berlios.de/bat/main.xsl -o _list.bat
call _list.bat
