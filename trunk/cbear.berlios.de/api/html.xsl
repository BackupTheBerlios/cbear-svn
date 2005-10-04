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
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:api="http://cbear.berlios.de/api"
	exclude-result-prefixes="xi">

<!-- XHTML 1.1. -->
<xsl:output 
	method="xml"
	doctype-public="-//W3C//DTD XHTML 1.1//EN"
	doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"/>

<xsl:template name="api:name">
	<span class="node">
		<xsl:value-of select="concat(local-name(), ' ')"/>
	</span>
</xsl:template>

<xsl:template match="@*" mode="api:body"/>

<xsl:template match="@id" mode="api:body">
	<span class="id"><xsl:value-of select="concat(., ' ')"/></span>
</xsl:template>

<xsl:template match="@value" mode="api:body">
	<span class="constant"><xsl:value-of select="concat(., ' ')"/></span>
</xsl:template>

<xsl:template match="@uuid" mode="api:body">
	<span class="constant"><xsl:value-of select="concat('{', ., '} ')"/></span>
</xsl:template>

<xsl:template match="api:public" mode="api:body">
	<li class="comment-public">
		<xsl:copy-of select="."/>
	</li>
</xsl:template>

<xsl:template match="api:private" mode="api:body">
	<li class="comment-private">
		<xsl:copy-of select="."/>
	</li>
</xsl:template>

<xsl:template match="api:comment" mode="api:body">
	<xsl:apply-templates select="*" mode="api:body"/>
</xsl:template>

<xsl:template match="text()" mode="api:body">
	<xsl:if test="normalize-space()!=''">
		<li class="text">
			<xsl:value-of select="."/>
		</li>
	</xsl:if>
</xsl:template>

<xsl:template match="api:using" mode="api:body">
	<li>
		<div class="header">
			<xsl:call-template name="api:name"/>
			<xsl:apply-templates select="@id" mode="api:body"/>
			<xsl:text> = </xsl:text>
			<a href="{@href}">
				<xsl:value-of select="document(@href)/api:library/@id"/>
			</a>
		</div>
	</li>
</xsl:template>

<xsl:template match="api:type.ref" mode="api:body">
	<li>
		<div class="header">
			<xsl:call-template name="api:name"/>
			<xsl:choose>
				<xsl:when test="@library">
					<xsl:variable name="library" select="@library"/>
					<a href="{concat(
						/api:library/api:using[@id=$library]/@href, '#', @id)}">
						<xsl:value-of select="concat(@library, ':', @id)"/>
					</a>
				</xsl:when>
				<xsl:otherwise>
					<a href="{concat('#', @id)}"><xsl:value-of select="@id"/></a>
				</xsl:otherwise>
			</xsl:choose>
		</div>
		<xsl:if test="*|text()">
			<ul>
				<xsl:apply-templates select="*|text()" mode="api:body"/>
			</ul>
		</xsl:if>
	</li>
</xsl:template>

<xsl:template name="api:id">
	<xsl:param name="dot" select="false()"/>
	<xsl:if test=". != /">		
		<xsl:for-each select="..">
			<xsl:call-template name="api:id">
				<xsl:with-param name="dot" select="true()"/>
			</xsl:call-template>
		</xsl:for-each>
		<xsl:value-of select="@id"/>
		<xsl:if test="boolean($dot)">
			<xsl:text>.</xsl:text>
		</xsl:if>
	</xsl:if>
</xsl:template>

<xsl:template match="*" mode="api:body">
	<xsl:variable name="id">
		<xsl:if test="not(ancestor-or-self::*[not(@id)])">
			<xsl:call-template name="api:id"/>
		</xsl:if>
	</xsl:variable>
	<li id="{$id}">
		<xsl:if test="$id != ''">
			<xsl:attribute name="id"><xsl:value-of select="$id"/></xsl:attribute>
		</xsl:if>
		<div class="header">
			<xsl:call-template name="api:name"/>
			<xsl:apply-templates select="@*" mode="api:body"/>
		</div>
		<xsl:if test="*|text()">
			<ul>
				<xsl:apply-templates select="*|text()" mode="api:body"/>
			</ul>
		</xsl:if>
	</li>
</xsl:template>

<xsl:template match="/api:library">
	<html>
		<head>
			<style type="text/css">
body { font-family: monospace; }
ul 
{ 
	list-style-type: disc; 
	border-left-style: dotted;
	border-width: 1px;
	
	margin-left: 0px;
	padding-left: 20px;

	margin-top: 5px;
	margin-bottom: 5px;
}
.constant { color: green; }
.node { color: black; }
.id { color: blue; }
.comment-public { color: red; font-style: italic; }
.comment-private { color: magenta; font-style: italic; }
			</style>
		</head>
		<body>
			<ul>
				<xsl:apply-templates select="." mode="api:body"/>
			</ul>
		</body>
	</html>
</xsl:template>

</xsl:stylesheet>
