<?xml version="1.0"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:odl="http://cbear.berlios.de/windows/com"
	exclude-result-prefixes="xi odl">

<xsl:import href="color.xsl"/>

<!-- XHTML 1.1. -->
<xsl:output 
	method="xml"
	indent="no"
	doctype-public="-//W3C//DTD XHTML 1.1//EN"
	doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"/>
	
<!-- * -->

<xsl:template match="*" mode="odl:html.a">
	<a href="{concat('#', @id)}">
		<xsl:apply-templates select="." mode="odl:html.title"/>
		<xsl:value-of select="@id"/>
	</a>
</xsl:template>

<xsl:template match="*" mode="odl:html.content.table">
	<li>
		<a href="{concat('#', @id)}">
			<xsl:apply-templates select="." mode="odl:html.title"/>
			<xsl:apply-templates select="." mode="odl:html.id"/>
		</a>
	</li>
</xsl:template>

<xsl:template match="*" mode="odl:html.id">
	<xsl:value-of select="concat(local-name(), ' ', @id)"/>
</xsl:template>

<xsl:template match="*" mode="odl:html.name">
	<span style="{$odl:color.keyword}">
		<xsl:value-of select="local-name()"/>
	</span>
	<xsl:value-of select="' '"/>
	<span style="{$odl:color.id}"><xsl:value-of select="@id"/></span>
</xsl:template>

<xsl:template match="*" mode="odl:html.title">
	<xsl:for-each select="odl:attribute[@id='helpstring']">
		<xsl:attribute name="title">
			<xsl:value-of select="substring(@value, 2, string-length(@value) - 2)"/>
		</xsl:attribute>
	</xsl:for-each>
</xsl:template>

<xsl:template match="*" mode="odl:html.intro"/>

<xsl:template match="*" mode="odl:html.header">
	<xsl:for-each select="odl:comment">
		<div class="comment"><xsl:copy-of select="*|text()"/></div>
	</xsl:for-each>
</xsl:template>

<xsl:template match="*" mode="odl:html.details">
	<pre>
		<xsl:apply-templates select="." mode="odl:color.attribute.list.line"/>
	</pre>
</xsl:template>

<xsl:template match="*" mode="odl:html.content">
	<div id="{concat(../@id, '.', @id)}" class="h3">
		<h3><xsl:apply-templates select="." mode="odl:html.name"/></h3>
		<xsl:apply-templates select="." mode="odl:html.details"/>
		<xsl:apply-templates select="." mode="odl:html.header"/>
	</div>
</xsl:template>

<xsl:template match="*" mode="odl:html">
	<div id="{@id}" class="h2">
		<h2><xsl:apply-templates select="." mode="odl:html.name"/></h2>
		<xsl:apply-templates select="." mode="odl:html.details"/>
		<xsl:apply-templates select="." mode="odl:html.header"/>
		<xsl:apply-templates select="*" mode="odl:html.content"/>
	</div>
</xsl:template>

<!-- comment -->

<xsl:template match="odl:comment" mode="odl:html.content.table"/>

<xsl:template match="odl:comment" mode="odl:html.content"/>

<xsl:template match="odl:comment" mode="odl:html"/>

<!-- attribute -->

<xsl:template match="odl:attribute" mode="odl:html.content.table"/>

<xsl:template match="odl:attribute" mode="odl:html.content"/>

<xsl:template match="odl:attribute" mode="odl:html"/>

<xsl:template match="odl:attribute" mode="odl:html.parameter.base">
	<span style="{$odl:color.keyword}"><xsl:value-of select="@id"/></span>
</xsl:template>

<xsl:template match="odl:attribute" mode="odl:html.parameter">
	<xsl:apply-templates select="." mode="odl:html.parameter.base"/>
	<xsl:text>, </xsl:text>
</xsl:template>

<xsl:template 
	match="odl:attribute[position()=last()]" mode="odl:html.parameter">
	<xsl:apply-templates select="." mode="odl:html.parameter.base"/>
</xsl:template>

<!-- importlib -->

<xsl:template match="odl:importlib" mode="odl:html.content.table"/>

<xsl:template match="odl:importlib" mode="odl:html"/>

<!-- type.ref -->

<xsl:template match="odl:type.ref" mode="odl:html.a">
	<xsl:variable name="id" select="@id"/>
	<xsl:choose>
		<xsl:when test="/odl:library/odl:interface[@id=$id]">
			<xsl:apply-templates 
				select="/odl:library/odl:interface[@id=$id]" mode="odl:html.a"/>
		</xsl:when>
		<xsl:otherwise>
			<span style="{$odl:color.id}"><xsl:value-of select="@id"/></span>
		</xsl:otherwise>
	</xsl:choose>
	<xsl:if test="odl:type.ref">
		<xsl:text>(</xsl:text>
		<xsl:apply-templates select="odl:type.ref" mode="odl:html.a"/>
		<xsl:text>)</xsl:text>
	</xsl:if>
</xsl:template>

<xsl:template match="odl:type.ref[@id='*']" mode="odl:html.a">
	<xsl:apply-templates select="odl:type.ref" mode="odl:html.a"/>
</xsl:template>

<xsl:template match="odl:type.ref" mode="odl:html.content"/>

<xsl:template match="odl:coclass/odl:type.ref" mode="odl:html.name">
	<span style="{$odl:color.keyword}">interface</span>
	<xsl:value-of select="' '"/>
	<xsl:apply-templates select="." mode="odl:html.a"/>
</xsl:template>

<xsl:template match="odl:coclass/odl:type.ref" mode="odl:html.content">
	<div id="{concat(../@id, '.', @id)}" class="h3">
		<h3><xsl:apply-templates select="." mode="odl:html.name"/></h3>
		<xsl:apply-templates select="." mode="odl:html.details"/>
		<xsl:apply-templates select="." mode="odl:html.header"/>
	</div>
</xsl:template>

<!-- item -->

<xsl:template match="odl:item" mode="odl:html.name">
	<span style="{$odl:color.id}"><xsl:value-of select="@id"/></span>
	<xsl:text> = </xsl:text>
	<span style="{$odl:color.const}">
		<xsl:value-of select="odl:const/@value"/>
	</span>
</xsl:template>

<!-- typedef -->

<xsl:template match="odl:typedef" mode="odl:html.id">
	<xsl:apply-templates select="*" mode="odl:html.id"/>
</xsl:template>

<xsl:template match="odl:typedef" mode="odl:html.title">
	<xsl:apply-templates select="*" mode="odl:html.title"/>
</xsl:template>

<xsl:template match="odl:typedef" mode="odl:html">
	<xsl:apply-templates select="*" mode="odl:html"/>
</xsl:template>

<!-- parameter -->

<xsl:template match="odl:parameter" mode="odl:html.name.base">
	<xsl:text>[</xsl:text>
	<xsl:apply-templates select="odl:attribute" mode="odl:html.parameter"/>
	<xsl:text>]</xsl:text>
	<xsl:apply-templates select="odl:type.ref" mode="odl:html.a"/>
</xsl:template>

<xsl:template match="odl:parameter" mode="odl:html.name">
	<xsl:param name="number"/>
	<xsl:apply-templates select="." mode="odl:html.name.base"/>
	<xsl:if test="position() &lt; $number">
		<xsl:text>, </xsl:text>
	</xsl:if>
</xsl:template>

<!-- method -->

<xsl:template match="odl:method" mode="odl:html.name.header">
	<xsl:for-each select="odl:parameter[odl:attribute/@id='retval']">
		<xsl:apply-templates select="odl:type.ref" mode="odl:html.a"/>
		<xsl:value-of select="' '"/>
	</xsl:for-each>
	<span style="{$odl:color.id}"><xsl:value-of select="@id"/></span>
</xsl:template>

<xsl:template match="odl:method" mode="odl:html.details">
	<pre>
		<xsl:apply-templates select="." mode="odl:color.attribute.list.line"/>
		<xsl:text>&#10;</xsl:text>
		<xsl:apply-templates select="." mode="odl:color.header"/>
	</pre>
</xsl:template>

<xsl:template match="odl:method" mode="odl:html.name">
	<xsl:apply-templates select="." mode="odl:html.name.header"/>
	<xsl:variable 
		name="number" 
		select="
			count(odl:parameter) - count(odl:parameter/odl:attribute[@id='retval'])"/>
	<xsl:text>(</xsl:text>
	<xsl:apply-templates 
		select="odl:parameter[position()&lt;=$number]" mode="odl:html.name">
		<xsl:with-param name="number" select="$number"/>
	</xsl:apply-templates>
	<xsl:text>);</xsl:text>
</xsl:template>

<xsl:template match="odl:method" mode="odl:html.name.property">
	<xsl:variable name="id" select="@id"/>
	<xsl:text>[</xsl:text>
	<xsl:for-each select="../odl:method[@id=$id]">
		<span style="{$odl:color.keyword}">
			<xsl:choose>
				<xsl:when test="odl:attribute/@id='propput'">propput</xsl:when>
				<xsl:otherwise>propget</xsl:otherwise>
			</xsl:choose>
		</span>
		<xsl:if test="position()!=last()">
			<xsl:text>, </xsl:text>
		</xsl:if>
	</xsl:for-each>
	<xsl:text>] </xsl:text>
	<xsl:apply-templates select="." mode="odl:html.name.header"/>
	
	<xsl:variable name="number" select="count(odl:parameter) - 1"/>
	<xsl:if test="$number &gt;= 1">
		<xsl:text>(</xsl:text>
		<xsl:apply-templates 
			select="odl:parameter[position()&lt;=$number]" mode="odl:html.name">
			<xsl:with-param name="number" select="$number"/>
		</xsl:apply-templates>		
		<xsl:text>)</xsl:text>
	</xsl:if>
	<xsl:text>;</xsl:text>
</xsl:template>

<xsl:template match="odl:method" mode="odl:html.content.property">
	<div id="{concat(../@id, '.', @id)}" class="h3">
		<h3><xsl:apply-templates select="." mode="odl:html.name.property"/></h3>
		<xsl:variable name="id" select="@id"/>
		<xsl:for-each select="../odl:method[@id=$id]">
			<xsl:apply-templates select="." mode="odl:html.details"/>
		</xsl:for-each>
		<xsl:apply-templates select="." mode="odl:html.header"/>
	</div>
</xsl:template>

<xsl:template 
	match="odl:method[preceding-sibling::odl:method/@id=@id]" 
	mode="odl:html.content.property"/>

<xsl:template 
	match="odl:method[odl:attribute/@id='propput']" mode="odl:html.content">
	<xsl:apply-templates select="." mode="odl:html.content.property"/>
</xsl:template>

<xsl:template 
	match="odl:method[odl:attribute/@id='propget']" mode="odl:html.content">
	<xsl:apply-templates select="." mode="odl:html.content.property"/>
</xsl:template>

<!-- interface -->

<xsl:template match="odl:interface" mode="odl:html.name">
	<span style="{$odl:color.keyword}">interface</span>
	<xsl:value-of select="' '"/>
	<span style="{$odl:color.id}"><xsl:value-of select="@id"/></span>
	<xsl:text>: </xsl:text>
	<xsl:apply-templates select="odl:type.ref" mode="odl:html.a"/>
</xsl:template>

<!-- library -->

<xsl:template match="odl:library" mode="odl:html">
	<html>
		<head>
			<title>
				<xsl:apply-templates select="." mode="odl:html.id"/>
			</title>
			<style type="text/css">
body { font-family: monospace; }
div 
{ 
	padding: 3px 20px 3px 3px;
	margin: 3px 3px 3px 3px; 
}
.comment { font-family: sans-serif; font-style: italic; }
.h2 { border-top: solid 1px silver; }
a { text-decoration: none; color: blue; }
a:hover { text-decoration: underline; }
.error { color: red; }
table { border-collapse: collapse; }
th, td { padding: 3px 3px 3px 3px; border: solid 1px black; }
pre { margin-left: 20px; padding-left: 5px; border-left: solid 1px black; }
			</style>
		</head>
		<body>
			<h1><xsl:apply-templates select="." mode="odl:html.name"/></h1>
			<div class="h2">
				<h2>Table Of Contents</h2>
				<ul>
					<li><a href="#Introduction">Introduction</a></li>
					<xsl:apply-templates select="*" mode="odl:html.content.table"/>
				</ul>
			</div>
			<div id="Introduction" class="h2">
				<h2>Introduction</h2>
				<xsl:apply-templates select="." mode="odl:html.details"/>
				<xsl:apply-templates select="." mode="odl:html.header"/>
			</div>
			<xsl:apply-templates select="*" mode="odl:html"/>
		</body>
	</html>
</xsl:template>
	
<!-- Entry Point -->
	
<xsl:template match="*">
	<xsl:apply-templates select="." mode="odl:html"/>
</xsl:template>

</xsl:stylesheet>
