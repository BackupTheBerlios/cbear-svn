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
<xsl:param name="P:style">
body
{
	font-family: sans-serif;
}
a 
{ 
	color: blue;
	text-decoration: none; 
}
a:hover 
{ 
	text-decoration: underline; 
}
ul
{
	list-style: disc;
}
.p-menu
{
	list-style: none;
	background-color: navy;
	color: white;
}
.p-menu-disable
{
	color: grey;
}
div.p-menu
{
	padding: 0px 10px 0px 10px;
}
</xsl:param>

<xsl:variable name="P:index">
	<xsl:call-template name="P:index"/>	
</xsl:variable>

<!-- P:index -->

<xsl:template name="P:index">
	<xsl:param name="language" select="$P:language"/>
	<xsl:variable name="extension">
		<xsl:if test="$language!=''">
			<xsl:value-of select="concat('.', $language)"/>
		</xsl:if>
	</xsl:variable>	
	<xsl:value-of select="concat('index', $extension)"/>
</xsl:template>

<!-- P:global.content.table -->

<xsl:template match="/S:wc-entries" mode="P:global.content.table">
	<xsl:param name="path"/>
	<xsl:for-each select="S:entry[@kind='dir' and @name!='']">
		<xsl:sort select="@name"/>
		<div class="p-menu">
			<xsl:variable
				name="file" select="concat('../', @name, '/', $P:index, '.xml')"/>
			<xsl:choose>
				<xsl:when test="document($file, .)/P:section">
					<a 
						href="{concat($path, @name, '/', $P:index, '.', $P:extension)}"
						class="p-menu">
						<xsl:value-of select="document($file, .)/P:section/@name"/>
					</a>
				</xsl:when>
				<xsl:otherwise>
					<span class="p-menu-disable">
						<xsl:value-of select="@name"/>
					</span>
				</xsl:otherwise>
			</xsl:choose>
<!--
			<xsl:apply-templates
				select="document(concat('../', @name, '/', $P:svn), .)/*"
				mode="P:global.content.table">
				<xsl:with-param name="path" select="concat($path, @name, '/')"/>
			</xsl:apply-templates>
-->
		</div>
	</xsl:for-each>
</xsl:template>

<!-- -->

<xsl:template match="/P:section">
	<html>
		<head>
			<title>
				<xsl:value-of select="@name"/>
			</title>
			<style type="text/css"><xsl:value-of select="$P:style"/></style>
		</head>
		<body>
			<!-- P:title -->
			<h1><xsl:value-of select="@name"/></h1>
			<table>
				<tr>
					<td>
						<!-- P:language -->
						<xsl:for-each select="document('languages.xml')/P:languages">
							<xsl:for-each select="P:language">
								<div class="p-menu">
									<xsl:variable name="index">
										<xsl:call-template name="P:index">
											<xsl:with-param name="language" select="@id"/>
										</xsl:call-template>
									</xsl:variable>
									<xsl:choose>
										<xsl:when test="string(@id)=string($P:language)">
											<span class="p-menu-disable">
												<xsl:value-of select="@name"/>
											</span>
										</xsl:when>
										<xsl:otherwise>
											<a 
												href="{concat($index, '.', $P:extension)}"
												class="p-menu">
												<xsl:value-of select="@name"/>
											</a>				
										</xsl:otherwise>
									</xsl:choose>
								</div>
							</xsl:for-each>
						</xsl:for-each>
					</td>
				</tr>
				<!-- P:local.content.table -->
				<!-- P:full.content.table -->
				<tr>
					<td>
						<xsl:apply-templates 
							select="document($P:svn, .)/*" mode="P:global.content.table"/>
					</td>
				</tr>
			</table>
			<!-- P:revision -->
			<xsl:for-each select="document($P:svn, .)/S:wc-entries/S:entry[@name='']">
				<div class="p-revision">
					<xsl:value-of select="concat('Revision: ', @revision)"/>
				</div>
			</xsl:for-each>
			<!-- -->
		</body>
	</html>
</xsl:template>

</xsl:stylesheet>
