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
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:prj="http://cbear.berlios.de/project"
	xmlns:cbear.html="http://cbear.berlios.de/html"
	exclude-result-prefixes="prj">

<xsl:import href="list.xsl"/>

<xsl:template match="prj:section" mode="prj:html.body">
	<table style="margin: 0 auto 0 auto;">
		<tr>
			<td style="vertical-align: top; width: 100%;">
				<div style="text-align: center; border: none;">
					<!--
					<img border="0" src="http://cbear.berlios.de/mainlogo.png"/>
					-->
					<img border="0" src="mainlogo.png"/>
				</div>
				<xsl:apply-imports/>
			</td>
			<xsl:copy-of select="document('cbear.xml')"/>			
		</tr>
	</table>
</xsl:template>

</xsl:stylesheet>
