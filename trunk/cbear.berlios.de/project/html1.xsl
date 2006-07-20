<?xml version="1.0" encoding="utf-8"?>
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
	xmlns:P="http://cbear.berlios.de/project"
	xmlns:S="svn:"
	exclude-result-prefixes="P S">

<xsl:param name="P:extension" select="'xml'"/>
<xsl:param name="P:svn" select="'_svn/entries'"/>
<xsl:param name="P:language" select="/P:section/@xml:lang"/>

<!-- P:global.content.table -->

<xsl:template match="/S:wc-entries" mode="P:global.content.table">
	<xsl:param name="path"/>
	<xsl:if test="S:entry[@kind='dir' and @name!='']">
		<ul>
			<xsl:for-each select="S:entry[@kind='dir' and @name!='']">
				<li>
					<xsl:variable
						name="file" select="concat('../', @name, '/index.xml')"/>
					<xsl:choose>
						<xsl:when test="document($file, .)/P:section">
							<a href="{concat($path, @name, '/index.', $P:extension)}">
								<xsl:value-of select="document($file, .)/P:section/@name"/>
							</a>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="@name"/>
						</xsl:otherwise>
					</xsl:choose>
					<xsl:apply-templates 
						select="document(concat('../', @name, '/', $P:svn), .)/*"
						mode="P:global.content.table">
						<xsl:with-param name="path" select="concat($path, @name, '/')"/>
					</xsl:apply-templates>
				</li>
			</xsl:for-each>
		</ul>
	</xsl:if>
</xsl:template>

<!-- -->

<xsl:template match="/P:section">
	<html>
		<head>
			<title>
				<xsl:value-of select="@name"/>
			</title>
		</head>
		<body>
			<!-- P:title -->
			<h1><xsl:value-of select="@name"/></h1>
			<!-- P:language -->
			<xsl:for-each select="document('lang.xml')/languages/language">
			</xsl:for-each>
			<!-- P:local.content.table -->
			<!-- P:full.content.table -->
			<xsl:apply-templates 
				select="document($P:svn, .)/*" mode="P:global.content.table"/>
			<!-- P:revision -->
			<xsl:for-each select="document($P:svn, .)/S:wc-entries/S:entry[@name='']">
				<div>
					<xsl:value-of select="concat('Revision: ', @revision)"/>
				</div>
			</xsl:for-each>
			<!-- -->
		</body>
	</html>
</xsl:template>

</xsl:stylesheet>
