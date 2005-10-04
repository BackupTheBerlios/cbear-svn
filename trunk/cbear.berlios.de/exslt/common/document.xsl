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
	xmlns:exsl="http://exslt.org/common"
	xmlns:common="http://cbear.berlios.de/exslt/common"
	extension-element-prefixes="exsl"
	exclude-result-prefixes="common">

<xsl:import href="document.nxslt.xsl"/>

<xsl:param name="nxslt" select="false()"/>

<xsl:template match="*" mode="common:document">
	<xsl:choose>
		<xsl:when test="boolean($nxslt)">
			<xsl:apply-templates select="." mode="common:document.nxslt"/>
		</xsl:when>
		<xsl:otherwise>
			<xsl:variable name="method">
				<xsl:choose>
					<xsl:when test="@method">
						<xsl:value-of select="@method"/>
					</xsl:when>
					<xsl:otherwise>
						<xsl:value-of select="'xml'"/>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:variable>
			<xsl:variable name="version">
				<xsl:choose>
					<xsl:when test="@version">
						<xsl:value-of select="@version"/>
					</xsl:when>
					<xsl:otherwise>
						<xsl:value-of select="'1.0'"/>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:variable>
			<xsl:variable name="omit-xml-declaration">
				<xsl:choose>
					<xsl:when test="@omit-xml-declaration">
						<xsl:value-of select="@omit-xml-declaration"/>
					</xsl:when>
					<xsl:otherwise>
						<xsl:value-of select="'no'"/>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:variable>
			<xsl:variable name="standalone">
				<xsl:choose>
					<xsl:when test="@standalone">
						<xsl:value-of select="@standalone"/>
					</xsl:when>
					<xsl:otherwise>
						<xsl:value-of select="'no'"/>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:variable>
			<xsl:variable name="indent">
				<xsl:choose>
					<xsl:when test="@indent">
						<xsl:value-of select="@indent"/>
					</xsl:when>
					<xsl:otherwise>
						<xsl:value-of select="'no'"/>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:variable>
			<xsl:variable name="doctype-public">
				<xsl:choose>
					<xsl:when test="@doctype-public">
						<xsl:value-of select="@doctype-public"/>
					</xsl:when>
					<xsl:otherwise>
						<xsl:text> </xsl:text>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:variable>
			<xsl:variable name="doctype-system">
				<xsl:choose>
					<xsl:when test="@doctype-system">
						<xsl:value-of select="@doctype-system"/>
					</xsl:when>
					<xsl:otherwise>
						<xsl:text> </xsl:text>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:variable>
			<exsl:document
			  href = "{@href}"
  			method = "{$method}"
			  version = "{$version}"
  			encoding = "{@encoding}"
			  omit-xml-declaration = "{$omit-xml-declaration}"
  			standalone = "{$standalone}"
			  doctype-public = "{$doctype-public}"
  			doctype-system = "{$doctype-system}"
			  cdata-section-elements = "{@cdata-section-elements}"
  			indent = "{$indent}"
				media-type = "{@media-type}">
				<xsl:copy-of select="*|text()"/>
			</exsl:document>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>

<xsl:template match="*" mode="common:xhtml11">
	<xsl:variable name="document">
		<document>
			<xsl:attribute name="method">xml</xsl:attribute>
			<xsl:attribute name="doctype-public"
				>-//W3C//DTD XHTML 1.1//EN</xsl:attribute>			
	  	<xsl:attribute name="doctype-system"
				>http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd</xsl:attribute>
			<xsl:copy-of select="@*|*|text()"/>
		</document>
	</xsl:variable>
	<xsl:apply-templates 
		select="exsl:node-set($document)/*" mode="common:document"/>
</xsl:template>

</xsl:stylesheet>
