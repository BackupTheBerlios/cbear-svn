set nxslt=c:/nxslt-1.6.4/bin/nxslt
set cbear=c:/cbear/
%nxslt% index.xml %cbear%cbear.berlios.de/cms/list.xsl  -o _list.bat.xml xmlns:C=http://cbear.berlios.de/cms C:nxslt=%nxslt% C:cbear=%cbear%
%nxslt% _list.bat.xml %cbear%cbear.berlios.de/bat/main.xsl -o _list.bat
call _list.bat
