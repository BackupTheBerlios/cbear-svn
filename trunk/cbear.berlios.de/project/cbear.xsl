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

<xsl:template match="prj:section" mode="prj:html.top">
	<div class="background">
		<img 
			border="0" 
			src="http://svn.berlios.de/viewcvs/*checkout*/cbear/trunk/cbear.berlios.de/mainlogo.png"/>
	</div>
</xsl:template>

<xsl:template match="prj:section" mode="prj:html.bottom">
	<div class="background">
		<table style="margin: 0 auto 0 auto;">
			<tr>
				<td>
<!-- SiteSearch Google -->
<form method="get" action="http://www.google.com/custom" target="_top">
<table border="0" bgcolor="#cccccc">
<tr><td nowrap="nowrap" valign="top" align="left" height="32">
<a href="http://www.google.com/">
<img src="http://www.google.com/logos/Logo_25gry.gif"
border="0" alt="Google"></img></a>
</td>
<td nowrap="nowrap">
<input type="hidden" name="domains" value="cbear.berlios.de"></input>
<input type="text" name="q" size="31" maxlength="255" value=""></input>
<input type="submit" name="sa" value="Search"></input>
</td></tr>
<tr>
<td> </td>
<td nowrap="nowrap">
<table>
<tr>
<td>
<input type="radio" name="sitesearch" value="" checked="checked"></input>
<font size="-1" color="#000000">Web</font>
</td>
<td>
<input type="radio" name="sitesearch" value="cbear.berlios.de"></input>
<font size="-1" color="#000000">cbear.berlios.de</font>
</td>
</tr>
</table>
<input type="hidden" name="client" value="pub-3298900216650066"></input>
<input type="hidden" name="forid" value="1"></input>
<input type="hidden" name="channel" value="7219731056"></input>
<input type="hidden" name="ie" value="UTF-8"></input>
<input type="hidden" name="oe" value="UTF-8"></input>
<input type="hidden" name="cof" value="GALT:#008000;GL:1;DIV:#336699;VLC:663399;AH:center;BGC:FFFFFF;LBGC:336699;ALC:0000FF;LC:0000FF;T:000000;GFNT:0000FF;GIMP:0000FF;FORID:1;"></input>
<input type="hidden" name="hl" value="en"></input>

</td></tr></table>
</form>
<!-- SiteSearch Google -->
				</td>
			</tr>
		</table>
		<table style="margin: 0 auto 0 auto;">
			<tr>
				<td>
<script type="text/javascript">
google_ad_client = "pub-3298900216650066";
google_ad_width = 728;
google_ad_height = 90;
google_ad_format = "728x90_as";
google_ad_type = "text_image";
google_ad_channel ="5882639306";
google_color_border = "003366";
google_color_bg = "003366";
google_color_link = "FF6600";
google_color_url = "99CCFF";
google_color_text = "FFFFFF";
</script>
<script type="text/javascript"
  src="http://pagead2.googlesyndication.com/pagead/show_ads.js">
</script>
				</td>
			</tr>
		</table>
	</div>
</xsl:template>

</xsl:stylesheet>
