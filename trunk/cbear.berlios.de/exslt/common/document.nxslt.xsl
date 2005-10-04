<?xml version="1.0"?>
<!--
The MIT License

Copyright (c) 2005 C Bear (http://cbear.berlios.de)

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:exsl="http://exslt.org/common"
	xmlns:common="http://cbear.berlios.de/exslt/common"
	exclude-result-prefixes="exsl common">

<!-- http://www.exslt.org/exsl/elements/document 
<exsl:document
   href = { uri-reference }
   method = { "xml" | "html" | "text" | qname-but-not-ncname }
   version = { nmtoken }
   encoding = { string }
   omit-xml-declaration = { "yes" | "no" }
   standalone = { "yes" | "no" }
   doctype-public = { string }
   doctype-system = { string }
   cdata-section-elements = { qnames }
   indent = { "yes" | "no" }
   media-type = { string }>
   - Content: template -
</exsl:document>
-->
<xsl:template match="*" mode="common:document.nxslt">
	<exsl:document
	  href = "{@href}"
  	method = "{@method}"
	  version = "{@version}"
  	encoding = "{@encoding}"
	  omit-xml-declaration = "{@omit-xml-declaration}"
  	standalone = "{@standalone}"
	  doctype-public = "{@doctype-public}"
  	doctype-system = "{@doctype-system}"
	  cdata-section-elements = "{@cdata-section-elements}"
  	indent = "{@indent}"
		media-type = "{@media-type}">
		<xsl:copy-of select="*|text()"/>
	</exsl:document>
</xsl:template>

</xsl:stylesheet>
