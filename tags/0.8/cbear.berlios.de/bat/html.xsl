<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:B="http://cbear.berlios.de/bat"
	xmlns="http://www.w3.org/1999/xhtml">

<!-- XHTML 1.1. -->
<xsl:output 
	method="xml"
	encoding="utf-8"
	doctype-public="-//W3C//DTD XHTML 1.1//EN"
	doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"/>

<xsl:template match="*" mode="B:id">
	<xsl:value-of select="concat('n', count(preceding::*|ancestor::*))"/>
</xsl:template>

<xsl:template match="B:command">
	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="B:id"/>
	</xsl:variable>
	<xsl:variable name="class">
		<xsl:if test="B:errorlevel/@value!=0">
			<xsl:text>error</xsl:text>
		</xsl:if>
	</xsl:variable>
	<div id="{$id}" class="{$class}">
		<h2><xsl:value-of select="@name"/></h2>
		<div>
			<h4>Command</h4>
			<pre><xsl:value-of select="@text"/></pre>
		</div>
		<div>
			<h4>Output</h4>
			<pre><xsl:value-of select="B:output"/></pre>
		</div>
		<div>
			<h4>Errorlevel</h4>
			<pre><xsl:value-of select="B:errorlevel/@value"/></pre>
		</div>
	</div>
</xsl:template>

<xsl:template match="B:bat">
	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="B:id"/>
	</xsl:variable>
	<div id="{$id}">
		<h2><xsl:value-of select="@name"/></h2>
		<xsl:apply-templates select="*"/>
	</div>
</xsl:template>

<xsl:template match="B:command" mode="B:content.table">
	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="B:id"/>
	</xsl:variable>
	<xsl:variable name="class">
		<xsl:if test="B:errorlevel/@value!=0">
			<xsl:text>error</xsl:text>
		</xsl:if>
	</xsl:variable>
	<li>
		<a href="{concat('#', $id)}" class="{$class}"><xsl:value-of select="@name"/></a>
	</li>
</xsl:template>

<xsl:template match="B:bat" mode="B:content.table">
	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="B:id"/>
	</xsl:variable>
	<li>
		<a href="{concat('#', $id)}"><xsl:value-of select="@name"/></a>
		<xsl:if test="*">
			<ul>
				<xsl:apply-templates select="*" mode="B:content.table"/>
			</ul>
		</xsl:if>
	</li>
</xsl:template>

<xsl:template match="/B:bat">
	<html>
		<head>
			<style type="text/css">
div
{
	border-style: solid;
	border-width: 1px; 
	border-color: gray;	

	margin: 5px 5px 5px 5px;
}
.error
{
	color: red;
}
a { color: blue; }
			</style>
			<title><xsl:value-of select="@name"/></title>
		</head>
		<body>
			<ul>
				<xsl:apply-templates select="*" mode="B:content.table"/>
			</ul>
			<xsl:apply-templates select="*"/>
		</body>
	</html>
</xsl:template>

</xsl:stylesheet>
