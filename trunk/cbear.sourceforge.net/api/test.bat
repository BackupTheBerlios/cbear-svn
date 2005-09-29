@rem The MIT License
@rem
@rem Copyright (c) 2005 C Bear (http://cbear.sourceforge.net)
@rem 
@rem Permission is hereby granted, free of charge, to any person obtaining a 
@rem copy of this software and associated documentation files (the "Software"),
@rem to deal in the Software without restriction, including without limitation 
@rem the rights to use, copy, modify, merge, publish, distribute, sublicense, 
@rem and/or sell copies of the Software, and to permit persons to whom the 
@rem Software is furnished to do so, subject to the following conditions:
@rem 
@rem The above copyright notice and this permission notice shall be included in 
@rem all copies or substantial portions of the Software.
@rem 
@rem THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
@rem IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
@rem FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
@rem AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
@rem LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
@rem FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
@rem DEALINGS IN THE SOFTWARE.

..\xsd\bin\Debug\xsd.exe base.xml
..\xsd\bin\Debug\xsd.exe example.xml

rem c:\nxslt-1.6\bin\nxslt example.xml com.xsl -o example.odl.xml api:com.xsl.xsd="../com/odl.xsd" xmlns:api="http://cbear.sourceforge.net/api"
rem ODL file.
c:\python24\scripts\4xslt --ignore --noxinclude --outfile=example.odl.xml --define=api:com.odl.xsd="../com/odl.xsd" --define=api:com.odl.xsl="../com/html.xsl" example.xml com.odl.xsl
c:\python24\scripts\4xslt --ignore --noxinclude --outfile=example.odl example.odl.xml ../com/odl.xsl
..\xsd\bin\Debug\xsd.exe example.odl.xml

rem CPP file.
rem c:\python24\scripts\4xslt --ignore --noxinclude --outfile=example.com.cpp.xml --define=api:com.cpp.xsd="../cpp/main.xsd" --define=api:com.cpp.xsl="../cpp/html.xsl" --define=api:com.cpp.name="_example.com" example.xml com.cpp.xsl
rem c:\python24\scripts\4xslt --ignore --noxinclude --define=cpp:cpp.root="../../" example.com.cpp.xml ../cpp/cpp.xsl
rem ..\xsd\bin\Debug\xsd.exe example.com.cpp.xml

rem CPP file.
c:\python24\scripts\4xslt --ignore --noxinclude --outfile=example.odl.cpp.xml --define=odl:cpp.xsd="../cpp/main.xsd" --define=odl:cpp.xsl="../cpp/html.xsl" --define=odl:cpp.name="_example.com" example.odl.xml ../com/cpp.xsl
c:\python24\scripts\4xslt --ignore --noxinclude example.odl.cpp.xml ../cpp/cpp.xsl
..\xsd\bin\Debug\xsd.exe example.odl.cpp.xml