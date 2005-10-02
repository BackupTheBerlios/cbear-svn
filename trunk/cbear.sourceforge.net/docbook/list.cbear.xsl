<?xml version="1.0"?>
<!--
The MIT License

Copyright (c) 2005 C Bear (http://cbear.sourceforge.net)

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
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:exsl="http://exslt.org/common"
	xmlns:cbear.docbook="http://cbear.sourceforge.net/docbook"
	xmlns:cbear.exslt.common="http://cbear.sourceforge.net/exslt/common"
	exclude-result-prefixes="xi cbear.docbook cbear.exslt.common">

<xsl:import href="list.xsl"/>

<xsl:output 
	method="xml" 
	version="1.0"
	indent="yes"
	standalone="yes"
	doctype-public="" 
	doctype-system=""/>

<!-- Footer -->
<xsl:template name="cbear.docbook:footer">
	<div class="footer">
		<a href="http://sourceforge.net/donate/index.php?group_id=147280">
			<img 
				src="http://images.sourceforge.net/images/project-support.jpg" 
				width="88" 
				height="32" 
				alt="Support This Project"/> 
		</a>
		<xsl:text> </xsl:text>
		<a href="http://sourceforge.net">
			<img 
				src="http://sourceforge.net/sflogo.php?group_id=147280&amp;type=1" 
				width="88" 
				height="31" 
				alt="SourceForge.net Logo" />
		</a>
		<xsl:text> </xsl:text>
		<a href="http://developer.berlios.de" title="BerliOS Developer">
			<img 
				src="http://developer.berlios.de/bslogo.php?group_id=4712" 
				width="124px" 
				height="32px" 
				border="0" 
				alt="BerliOS Developer Logo"/>
		</a>
		<xsl:text> </xsl:text>
		<a href="http://cbear.sourceforge.net">
			<img
    	 	src="http://cbear.sourceforge.net/logo.png"
      	alt="Sea Bear" 
				height="31" 
				width="88" />
		</a>
		<xsl:text> </xsl:text>
		<a href="http://validator.w3.org/check?uri=referer">
			<img
    	 	src="http://www.w3.org/Icons/valid-xhtml11"
      	alt="Valid XHTML 1.1" 
				height="31" 
				width="88" />
		</a>
		<xsl:text> </xsl:text>
		<a href="http://jigsaw.w3.org/css-validator/check/referer">
		  <img 
				style="border:0;width:88px;height:31px"
				src="http://jigsaw.w3.org/css-validator/images/vcss" 
				alt="Valid CSS!" />
		</a>
	</div>
</xsl:template>

</xsl:stylesheet>
