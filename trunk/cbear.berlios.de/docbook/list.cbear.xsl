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
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:exsl="http://exslt.org/common"
	xmlns:cbear.docbook="http://cbear.berlios.de/docbook"
	xmlns:cbear.exslt.common="http://cbear.berlios.de/exslt/common"
	extension-element-prefixes="exsl"
	exclude-result-prefixes="xi cbear.docbook cbear.exslt.common">

<xsl:import href="list.xsl"/>

<xsl:output 
	method="xml" 
	version="1.0"
	indent="yes"
	standalone="yes"
	doctype-public="" 
	doctype-system=""/>

<xsl:template name="cbear.docbook:style">
.main-table { width: 100%; }
.main, .ad { vertical-align: top; }
.ad { text-align: center; }
div.header
{ 
	border-style: solid; 
}
span.header
{
	font-size: 50px;
	font-weight: bold;
}
</xsl:template>

<xsl:template name="cbear.docbook:body">
	<xsl:param name="content"/>
	<table class="main-table">
		<tbody>
			<tr>
				<td rowspan="3" class="main">
					<xsl:copy-of select="$content"/>
				</td>
				<td style="vertical-align: top; width: 200px;">
					<table>
						<tbody>
							<tr>
								<xsl:copy-of select="document('../google/search.xml')"/>
							</tr>
							<tr>
								<xsl:copy-of select="document('../google/content.xml')"/>
							</tr>
						</tbody>
					</table>
				</td>
			</tr>
		</tbody>
	</table>
</xsl:template>

<xsl:template name="cbear.docbook:header">
	<xsl:param name="root"/>
	<div class="header">
		<img src="{concat($root, 'mainlogo.png')}" height="92px" width="148px"/>
		<span class="header">C BEAR</span>
	</div>
</xsl:template>
	
<!-- Footer -->
<xsl:template name="cbear.docbook:footer">
	<xsl:variable name="td" select="'vertical-align: top;'"/>
	<div class="footer">
		<table>
			<tr>
				<td style="{$td}">
					<form action="https://www.paypal.com/cgi-bin/webscr" method="post">
						<input type="hidden" name="cmd" value="_s-xclick"/>
						<input 
							type="image" 
							src="https://www.paypal.com/en_US/i/btn/x-click-but04.gif" 
							border="0" 
							name="submit" 
							alt="Make payments with PayPal - it's fast, free and secure!"/>
						<input 
							type="hidden" 
							name="encrypted" 
							value="-----BEGIN PKCS7-----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-----END PKCS7-----"/>
					</form>
				</td>
				<td style="{$td}">
					<a href="http://developer.berlios.de" title="BerliOS Developer">
						<img 
							src="http://developer.berlios.de/bslogo.php?group_id=4712" 
							width="124px" 
							height="32px" 
							border="0" 
							alt="BerliOS Developer Logo"/>
					</a>
				</td>
				<td style="{$td}">
					<a href="http://sourceforge.net">
						<img 
							src="http://sourceforge.net/sflogo.php?group_id=147280&amp;type=1" 
							width="88" 
							height="31" 
							alt="SourceForge.net Logo" />
					</a>
				</td>
				<td style="{$td}">
					<a href="http://cbear.berlios.de">
						<img
							src="http://cbear.berlios.de/logo.png"
							alt="C Bear" 
							height="31" 
							width="88" />
					</a>
				</td>
				<td style="{$td}">
					<a href="http://validator.w3.org/check?uri=referer">
					<img
						src="http://www.w3.org/Icons/valid-xhtml11"
						alt="Valid XHTML 1.1" 
						height="31" 
						width="88" />
					</a>
				</td>
				<td style="{$td}">
					<a href="http://jigsaw.w3.org/css-validator/check/referer">
						<img 
							style="border:0;width:88px;height:31px"
							src="http://jigsaw.w3.org/css-validator/images/vcss" 
							alt="Valid CSS!" />
					</a>
				</td>
			</tr>
		</table>
	</div>
</xsl:template>

</xsl:stylesheet>
