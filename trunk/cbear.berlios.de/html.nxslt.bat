@rem The MIT License
@rem
@rem Copyright (c) 2005 C Bear (http://cbear.berlios.de)
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
c:\nxslt-1.6.3\bin\nxslt index.xml docbook/list.cbear.xsl -xi -mo url=cbear.berlios.de
c:\nxslt-1.6.3\bin\nxslt index.xml.xml project/list.xsl -xi -mo
