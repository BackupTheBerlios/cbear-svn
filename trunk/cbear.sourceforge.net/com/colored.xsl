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
	exclude-result-prefixes="xi">

<!-- XHTML 1.1. -->
<xsl:output 
	method="xml"
	indent="no"
	doctype-public="-//W3C//DTD XHTML 1.1//EN"
	doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"/>

<xsl:variable name="odl:indent">
	border-width: 1px; 
	border-left-style: dotted; 
	padding-left: 20px;
</xsl:variable>

<xsl:variable name="odl:id">
	color: blue;
</xsl:variable>

<xsl:variable name="odl:keyword">
	color: black;
</xsl:variable>

<xsl:variable name="odl:attribute">
	color: navy;
</xsl:variable>

<xsl:variable name="odl:const">
	color: green;
</xsl:variable>

<xsl:template name="odl:br">
	<br/>
<xsl:text>
</xsl:text>
</xsl:template>

<xsl:template match="*" mode="odl:id">
	<xsl:if test="..!=/">
		<xsl:apply-templates select=".." mode="odl:id"/>
		<xsl:text>.</xsl:text>
	</xsl:if>
	<xsl:value-of select="@id"/>
</xsl:template>

<xsl:template name="odl:id">
	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="odl:id"/>
	</xsl:variable>
	<span style="{$odl:id}" id="{$id}"><xsl:value-of select="@id"/></span>
</xsl:template>

<xsl:template match="text()" mode="odl:body"/>

<xsl:template match="*" mode="odl:body">
	<xsl:call-template name="odl:definition"/>
	<span style="{$odl:keyword}"><xsl:value-of select="local-name()"/></span>
	<xsl:text> </xsl:text>
	<xsl:call-template name="odl:id"/>
	<xsl:call-template name="odl:br"/>
	<xsl:text>{</xsl:text>
	<div style="{$odl:indent}"><xsl:apply-templates mode="odl:body"/></div>
	<xsl:text>};</xsl:text>
	<xsl:call-template name="odl:br"/>
</xsl:template>

<xsl:template match="odl:attribute" mode="odl:body"/>

<xsl:template match="odl:attribute" mode="odl:body.attribute">
	<span style="{$odl:attribute}"><xsl:value-of select="@id"/></span>
	<xsl:if test="@value">
		<xsl:text>(</xsl:text>
		<span style="{$odl:const}"><xsl:value-of select="@value"/></span>	
		<xsl:text>)</xsl:text>
	</xsl:if>
	<xsl:if test="position()!=last()">, </xsl:if>
</xsl:template>

<xsl:template name="odl:definition">
	<xsl:if test="odl:attribute">
		<xsl:text>[</xsl:text>
		<xsl:apply-templates select="odl:attribute" mode="odl:body.attribute"/>
		<xsl:text>]</xsl:text>
		<xsl:call-template name="odl:br"/>
	</xsl:if>	
</xsl:template>

<xsl:template match="odl:const" mode="odl:body">
	<span style="{$odl:const}"><xsl:value-of select="@value"/></span>
</xsl:template>

<xsl:template match="odl:type.ref" mode="odl:body">
	<span style="{$odl:id}"><xsl:value-of select="@id"/></span>
	<xsl:if test="odl:type.ref">
		<xsl:text>(</xsl:text>
		<xsl:apply-templates select="*" mode="odl:body.type"/>
		<xsl:text>)</xsl:text>
	</xsl:if>
</xsl:template>

<xsl:template match="odl:type.ref[@id='*']" mode="odl:body">
	<xsl:apply-templates select="odl:type.ref" mode="odl:body"/>
	<xsl:text>*</xsl:text>
</xsl:template>

<xsl:template match="*" mode="odl:body.type">
	<xsl:apply-templates select="." mode="odl:body"/>
	<xsl:if test="position()!=last()">
		<xsl:text>, </xsl:text>
	</xsl:if>
</xsl:template>

<xsl:template match="odl:parameter" mode="odl:body">
	<xsl:if test="odl:attribute">
		<xsl:text>[</xsl:text>
		<xsl:apply-templates select="odl:attribute" mode="odl:body.attribute"/>
		<xsl:text>]</xsl:text>
	</xsl:if>
	<xsl:text> </xsl:text>
	<xsl:apply-templates select="odl:type.ref" mode="odl:body"/>
	<xsl:text> </xsl:text>
	<span style="{$odl:id}"><xsl:value-of select="@id"/></span>
	<xsl:if test="position()!=last()">
		<xsl:text>,</xsl:text>
		<xsl:call-template name="odl:br"/>
	</xsl:if>
</xsl:template>

<xsl:template match="odl:method" mode="odl:body.parameters"/>

<xsl:template match="odl:method[odl:parameter]" mode="odl:body.parameters">
	<div style="{$odl:indent}">
		<xsl:apply-templates select="odl:parameter" mode="odl:body"/>
	</div>
</xsl:template>

<xsl:template match="odl:method" mode="odl:body">	
	<xsl:call-template name="odl:definition"/>
	<span style="{$odl:id}">
		<xsl:apply-templates select="odl:type.ref" mode="odl:body"/>
	</span>
	<xsl:text> </xsl:text>
	<xsl:call-template name="odl:id"/>
	<xsl:text>(</xsl:text>
	<xsl:apply-templates select="." mode="odl:body.parameters"/>
	<xsl:text>);</xsl:text>
	<xsl:call-template name="odl:br"/>
</xsl:template>

<xsl:template match="odl:interface" mode="odl:body">
	<xsl:call-template name="odl:definition"/>
	
	<span style="{$odl:keyword}">interface</span>
	<xsl:text> </xsl:text>
	<xsl:call-template name="odl:id"/>
	<xsl:if test="odl:type.ref">
		<xsl:text>: </xsl:text>
		<xsl:apply-templates select="odl:type.ref" mode="odl:body"/>
	</xsl:if>
	<xsl:call-template name="odl:br"/>
	<xsl:text>{</xsl:text>
	<div style="{$odl:indent}">
		<xsl:apply-templates select="odl:method" mode="odl:body"/>
	</div>
	<xsl:text>};</xsl:text>
	<xsl:call-template name="odl:br"/>
</xsl:template>

<xsl:template match="odl:item" mode="odl:body">
	<xsl:call-template name="odl:definition"/>
	<xsl:call-template name="odl:id"/>
	<xsl:text> = </xsl:text>
	<xsl:apply-templates select="*" mode="odl:body"/>
	<xsl:text>,</xsl:text>
	<xsl:call-template name="odl:br"/>
</xsl:template>

<xsl:template match="odl:object" mode="odl:body">
	<xsl:call-template name="odl:definition"/>
	<xsl:apply-templates select="odl:type.ref" mode="odl:body"/>
	<xsl:text> </xsl:text>
	<xsl:call-template name="odl:id"/>
	<xsl:text>;</xsl:text>
	<xsl:call-template name="odl:br"/>	
</xsl:template>

<xsl:template match="*" mode="odl:body.typedef">
	<xsl:call-template name="odl:definition"/>
	<span style="{$odl:keyword}"><xsl:value-of select="local-name()"/></span>
	<xsl:text> </xsl:text>
	<xsl:call-template name="odl:id"/>
	<xsl:call-template name="odl:br"/>
	<xsl:text>{</xsl:text>
	<div style="{$odl:indent}"><xsl:apply-templates mode="odl:body"/></div>
	<xsl:text>}</xsl:text>
</xsl:template>

<xsl:template match="odl:typedef" mode="odl:body">
	<span style="{$odl:keyword}">typedef</span>
	<xsl:call-template name="odl:br"/>
	<xsl:apply-templates select="*" mode="odl:body.typedef"/>
	<xsl:text> </xsl:text>
	<xsl:call-template name="odl:id"/>
	<xsl:text>;</xsl:text>
	<xsl:call-template name="odl:br"/>
</xsl:template>

<xsl:template match="odl:coclass/odl:type.ref" mode="odl:body">
	<span style="{$odl:keyword}">interface</span>
	<xsl:text> </xsl:text>
	<xsl:call-template name="odl:id"/>
	<xsl:text>;</xsl:text>
	<xsl:call-template name="odl:br"/>
</xsl:template>

<xsl:template match="odl:importlib" mode="odl:body">
	<span style="{$odl:keyword}">importlib</span>
	<xsl:text>(</xsl:text>
	<span style="{$odl:const}">
		<xsl:value-of select="concat('&#x22;', @href, '&#x22;')"/>
	</span>
	<xsl:text>);</xsl:text>
	<xsl:call-template name="odl:br"/>
</xsl:template>

<xsl:template match="odl:comment" mode="odl:body"/>

<xsl:template match="/odl:library">
	<html>
		<body style="font-family: monospace;">
			<xsl:apply-templates select="." mode="odl:body"/>
		</body>
	</html>
</xsl:template>

</xsl:stylesheet>
