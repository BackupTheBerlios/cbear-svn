..\xsd\bin\Debug\xsd.exe base.xml
..\xsd\bin\Debug\xsd.exe example.xml

rem c:\nxslt-1.6.3\bin\nxslt example.xml com.xsl -o example.odl.xml api:com.xsl.xsd="../com/odl.xsd" xmlns:api="http://cbear.berlios.de/api"
rem ODL file.
c:\python24\scripts\4xslt --ignore --noxinclude --outfile=example.odl.xml --define=api:com.odl.xsd="../com/odl.xsd" --define=api:com.odl.xsl="../com/html.xsl" example.xml com.odl.xsl
c:\python24\scripts\4xslt --ignore --noxinclude --outfile=example.odl example.odl.xml ../com/odl.xsl
..\xsd\bin\Debug\xsd.exe example.odl.xml

call "C:\Program Files\Microsoft Visual C++ Toolkit 2003\vcvars32.bat" 
"C:\Program Files\Microsoft Platform SDK\Bin\midl.exe" example.odl

rem CPP file.
rem c:\python24\scripts\4xslt --ignore --noxinclude --outfile=example.com.cpp.xml --define=api:com.cpp.xsd="../cpp/main.xsd" --define=api:com.cpp.xsl="../cpp/html.xsl" --define=api:com.cpp.name="_example.com" example.xml com.cpp.xsl
rem c:\python24\scripts\4xslt --ignore --noxinclude --define=cpp:cpp.root="../../" example.com.cpp.xml ../cpp/cpp.xsl
rem ..\xsd\bin\Debug\xsd.exe example.com.cpp.xml

rem CPP file.
c:\python24\scripts\4xslt --ignore --noxinclude --outfile=example.odl.cpp.xml --define=odl:cpp.xsd="../cpp/main.xsd" --define=odl:cpp.xsl="../cpp/html.xsl" --define=odl:cpp.name="_example.com" example.odl.xml ../com/cpp.xsl
c:\python24\scripts\4xslt --ignore --noxinclude example.odl.cpp.xml ../cpp/cpp.xsl
..\xsd\bin\Debug\xsd.exe example.odl.cpp.xml