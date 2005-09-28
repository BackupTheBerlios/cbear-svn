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
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:odl="http://cbear.sourceforge.net/com"
	xmlns:txt="http://cbear.sourceforge.net/text"
	exclude-result-prefixes="odl txt xi">

<xsl:import href="../text/main.xsl"/>

<!-- XHTML 1.1. -->
<xsl:output 
	method="xml"
	doctype-public="-//W3C//DTD XHTML 1.1//EN"
	doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"/>

<!-- Style -->

<xsl:param name="odl:color.keyword">
	color: green;
</xsl:param>

<xsl:param name="odl:color.id">
	color: blue;
</xsl:param>

<xsl:param name="odl:color.const">
	color: magenta;
</xsl:param>

<!-- * -->

<xsl:template match="*" mode="odl:color">
	<xsl:message terminate="no">
		<xsl:value-of select="concat(
			'Unknown tag &#x22;', name(), '&#x22; was skipped.')"/>
	</xsl:message>
</xsl:template>

<!-- odl:* -->

<xsl:template match="odl:*" mode="odl:color">
	<xsl:apply-templates select="." mode="odl:color.block"/>	
</xsl:template>

<xsl:template match="odl:*" mode="odl:color.block">
	<xsl:apply-templates select="." mode="odl:color.attribute.list"/>
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<xsl:apply-templates select="." mode="odl:color.header"/>
		</xsl:with-param>
	</xsl:call-template>
	<xsl:call-template name="txt:main.block">
		<xsl:with-param name="begin">
			<xsl:apply-templates select="." mode="odl:color.begin"/>
		</xsl:with-param>
		<xsl:with-param name="end">
			<xsl:apply-templates select="." mode="odl:color.end"/>
		</xsl:with-param>
		<xsl:with-param name="content">
			<xsl:apply-templates select="*" mode="odl:color"/>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<xsl:template match="odl:*" mode="odl:color.header">
	<span class="{$odl:color.keyword}">
		<xsl:value-of select="local-name()"/>
	</span>
	<xsl:text> </xsl:text>
	<span class="{$odl:color.id}"><xsl:value-of select="@id"/></span>
</xsl:template>

<xsl:template match="odl:*" mode="odl:color.begin">
	<xsl:text>{</xsl:text>
</xsl:template>

<xsl:template match="odl:*" mode="odl:color.end">
	<xsl:text>};</xsl:text>
</xsl:template>

<!-- comment -->

<xsl:template match="odl:comment" mode="odl:color"/>

<!-- attribute -->

<xsl:template match="odl:attribute" mode="odl:color.attribute.body">
	<span class="{$odl:color.keyword}"><xsl:value-of select="@id"/></span>
</xsl:template>

<xsl:template match="odl:attribute[@value]" mode="odl:color.attribute.body">
	<span class="{$odl:color.keyword}"><xsl:value-of select="@id"/></span>
	<xsl:text>(</xsl:text>
	<span class="{$odl:color.const}"><xsl:value-of select="@value"/></span>
	<xsl:text>)</xsl:text>
</xsl:template>

<xsl:template match="odl:attribute" mode="odl:color.attribute">
	<xsl:apply-templates select="." mode="odl:color.attribute.body"/>
	<xsl:text>, </xsl:text>
</xsl:template>

<xsl:template 
	match="odl:attribute[position()=last()]" mode="odl:color.attribute">
	<xsl:apply-templates select="." mode="odl:color.attribute.body"/>
</xsl:template>

<xsl:template match="odl:*" mode="odl:color.attribute.list.line"/>

<xsl:template match="odl:*[odl:attribute]" mode="odl:color.attribute.list.line">
	<xsl:text>[</xsl:text>
	<xsl:apply-templates select="odl:attribute" mode="odl:color.attribute"/>	
	<xsl:text>]</xsl:text>
</xsl:template>

<xsl:template match="odl:*" mode="odl:color.attribute.list">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<xsl:apply-templates select="." mode="odl:color.attribute.list.line"/>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<xsl:template match="odl:attribute" mode="odl:color"/>

<!-- importlib -->

<xsl:template match="odl:importlib" mode="odl:color">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<span class="keyword">importlib</span>
			<xsl:text>(</xsl:text>
			<span class="const">
				<xsl:value-of select="concat('&#x22;', @href,'&#x22;')"/>
			</span>
			<xsl:text>);</xsl:text>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- item -->

<xsl:template match="odl:item" mode="odl:color">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<span class="{$odl:color.id}"><xsl:value-of select="@id"/></span>
			<xsl:text> = </xsl:text>
			<span class="{$odl:color.const}">
				<xsl:value-of select="odl:const/@value"/>
			</span>
			<xsl:text>,</xsl:text>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- typedef -->

<xsl:template match="odl:typedef" mode="txt:main.indent"/>

<xsl:template match="odl:typedef" mode="odl:color">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<span class="keyword">typedef</span>
		</xsl:with-param>
	</xsl:call-template>
	<xsl:apply-templates select="*" mode="odl:color"/>
</xsl:template>

<xsl:template match="odl:typedef/odl:*" mode="odl:color.end">
	<xsl:text>} </xsl:text>
	<span class="{$odl:color.id}"><xsl:value-of select="../@id"/></span>
	<xsl:text>;</xsl:text>
</xsl:template>

<!-- type.ref -->

<xsl:template match="odl:type.ref" mode="odl:color.type.ref.header">
	<span class="id"><xsl:value-of select="@id"/></span>
</xsl:template>

<xsl:template match="odl:type.ref" mode="odl:color.type.ref">
	<xsl:apply-templates select="." mode="odl:color.type.ref.header"/>
</xsl:template>

<xsl:template match="odl:type.ref[odl:type.ref]" mode="odl:color.type.ref">
	<xsl:apply-templates select="." mode="odl:color.type.ref.header"/>
	<xsl:text>(</xsl:text>
		<xsl:apply-templates select="odl:type.ref" mode="odl:color.type.ref"/>
	<xsl:text>)</xsl:text>
</xsl:template>

<xsl:template match="odl:type.ref[@id='*']" mode="odl:color.type.ref">
	<xsl:apply-templates select="odl:type.ref" mode="odl:color.type.ref"/>
	<xsl:text>*</xsl:text>
</xsl:template>

<xsl:template match="odl:type.ref" mode="odl:color">
	<xsl:apply-templates select="." mode="odl:color.type.ref"/>
</xsl:template>

<xsl:template match="odl:method/odl:type.ref" mode="odl:color"/>

<xsl:template match="odl:interface/odl:type.ref" mode="odl:color"/>

<xsl:template match="odl:coclass/odl:type.ref" mode="odl:color">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<xsl:apply-templates select="." mode="odl:color.attribute.list.line"/>
			<span class="{$odl:color.id}">interface</span>
			<xsl:text> </xsl:text>
			<xsl:apply-templates select="." mode="odl:color.type.ref"/>
			<xsl:text>;</xsl:text>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- parameter -->

<xsl:template match="odl:parameter" mode="odl:color.parameter.body">
	<xsl:apply-templates select="." mode="odl:color.attribute.list.line"/>
	<xsl:apply-templates select="odl:type.ref" mode="odl:color"/>
	<xsl:text> </xsl:text>
	<span class="{$odl:color.id}"><xsl:value-of select="@id"/></span>
</xsl:template>

<xsl:template match="odl:parameter" mode="odl:color">
	<xsl:apply-templates select="." mode="odl:color.parameter.body"/>
	<xsl:text>,</xsl:text>
</xsl:template>

<xsl:template 
	match="odl:parameter[position()=last()]" mode="odl:color">
	<xsl:apply-templates select="." mode="odl:color.parameter.body"/>
</xsl:template>

<!-- method -->

<xsl:template match="odl:method" mode="odl:color">
	<xsl:apply-templates select="." mode="odl:color.attribute.list"/>
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<xsl:apply-templates select="odl:type.ref" mode="odl:color.type.ref"/>
			<xsl:text> </xsl:text>
			<span class="{$odl:color.id}"><xsl:value-of select="@id"/></span>
			<xsl:text>(</xsl:text>
			<xsl:apply-templates select="odl:parameter" mode="odl:color"/>
			<xsl:text>);</xsl:text>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- interface -->

<xsl:template match="odl:interface" mode="odl:color.header">
	<span class="{$odl:color.keyword}">interface</span>
	<xsl:text> </xsl:text>
	<span class="{$odl:color.id}"><xsl:value-of select="@id"/></span>
	<xsl:text>: </xsl:text>
	<span class="{$odl:color.id}">
		<xsl:apply-templates select="odl:type.ref" mode="odl:color.type.ref"/>
	</span>
</xsl:template>

<!-- Entry Points -->

<xsl:template match="odl:*">
	<xsl:apply-templates select="." mode="odl:color"/>
</xsl:template>

<xsl:template match="/odl:*">
	<html>
		<body>
			<pre><xsl:apply-templates select="." mode="odl:color"/></pre>
		</body>
	</html>
</xsl:template>

</xsl:stylesheet>
