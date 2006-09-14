<?xml version="1.0"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:cs="http://cbear.berlios.de/cs"
	xmlns:txt="http://cbear.berlios.de/text"
	exclude-result-prefixes="cs txt xi">

<xsl:import href="../text/main.xsl"/>

<!-- XHTML 1.1. -->
<xsl:output 
	method="xml"
	doctype-public="-//W3C//DTD XHTML 1.1//EN"
	doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"/>

<!-- Styles -->

<xsl:variable name="cs:html">
	border-style: solid;
	border-width: 1px;
	margin: 5px 5px 5px 5px;
</xsl:variable>

<xsl:variable name="cs:html.preprocessor">
	color: navy;
</xsl:variable>

<xsl:variable name="cs:html.keyword">
	color: green;
</xsl:variable>

<xsl:variable name="cs:html.id">
	color: blue;
</xsl:variable>

<xsl:variable name="cs:html.const">
	color: magenta;
</xsl:variable>

<!-- block -->

<xsl:template match="*" mode="cs:html.block">
	<xsl:param name="begin" select="'{'"/>
	<xsl:param name="end" select="'}'"/>
	<xsl:call-template name="txt:main.block">
		<xsl:with-param name="begin" select="$begin"/>
		<xsl:with-param name="end" select="$end"/>
		<xsl:with-param name="content">
			<xsl:apply-templates select="*" mode="cs:html"/>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- * -->

<xsl:template match="*" mode="cs:html">
	<xsl:message terminate="no">
		<xsl:value-of select="concat(
			'Unknown tag &#x22;', name(), '&#x22; was skipped.')"/>
	</xsl:message>
</xsl:template>

<xsl:template match="*" mode="cs:html.access"/>

<xsl:template match="*[@access]" mode="cs:html.access">
	<span style="{$cs:html.keyword}"><xsl:value-of select="@access"/></span>
	<xsl:value-of select="' '"/>
</xsl:template>

<!-- attribute -->

<xsl:template match="cs:attribute" mode="cs:html"/>

<xsl:template match="cs:attribute" mode="cs:html.attribute">
	<xsl:variable name="text">
		<xsl:value-of select="'['"/>
		<xsl:if test="@id">
			<span style="{$cs:html.id}"><xsl:value-of select="@id"/></span>
			<xsl:value-of select="': '"/>
		</xsl:if>
		<xsl:apply-templates select="*" mode="cs:html"/>
		<xsl:value-of select="']'"/>
	</xsl:variable>
	<xsl:for-each select="..">
		<xsl:call-template name="txt:main.line">
			<xsl:with-param name="text" select="$text"/>
		</xsl:call-template>
	</xsl:for-each>
</xsl:template>

<!-- id.ref -->

<xsl:template match="cs:id.ref[@id]" mode="cs:html.id.ref">
	<span style="{$cs:html.id}"><xsl:value-of select="@id"/></span>
</xsl:template>

<xsl:template match="cs:id.ref[@value]" mode="cs:html.id.ref">
	<span style="{$cs:html.const}"><xsl:value-of select="@value"/></span>
</xsl:template>

<xsl:template match="cs:id.ref" mode="cs:html.dot">
	<xsl:apply-templates select="." mode="cs:html.id.ref"/>
	<xsl:value-of select="'.'"/>
</xsl:template>

<xsl:template match="cs:id.ref[last()]" mode="cs:html.dot">
	<xsl:apply-templates select="." mode="cs:html.id.ref"/>
</xsl:template>

<xsl:template match="cs:id.ref[@type='.']" mode="cs:html.id.ref">
	<xsl:apply-templates select="*" mode="cs:html.dot"/>
</xsl:template>

<xsl:template match="cs:id.ref[@type='()']" mode="cs:html.id.ref">
	<xsl:apply-templates select="*[1]" mode="cs:html.id.ref"/>
	<xsl:value-of select="'('"/>
	<xsl:apply-templates select="*[position()>1]" mode="cs:html.id.ref"/>
	<xsl:value-of select="')'"/>
</xsl:template>

<xsl:template match="cs:id.ref" mode="cs:html.or">
	<xsl:apply-templates select="." mode="cs:html.id.ref"/>
	<xsl:value-of select="'|'"/>
</xsl:template>

<xsl:template match="cs:id.ref[last()]" mode="cs:html.or">
	<xsl:apply-templates select="." mode="cs:html"/>
</xsl:template>

<xsl:template match="cs:id.ref[@type='|']" mode="cs:html.id.ref">
	<xsl:apply-templates select="*" mode="cs:html.or"/>
</xsl:template>

<xsl:template match="cs:id.ref[@type='[]']" mode="cs:html.id.ref">
	<xsl:apply-templates select="*" mode="cs:html.or"/>
	<xsl:value-of select="'[]'"/>
</xsl:template>

<xsl:template match="cs:id.ref" mode="cs:html">
	<xsl:apply-templates select="." mode="cs:html.id.ref"/>
</xsl:template>

<xsl:template match="cs:interface/cs:id.ref" mode="cs:html"/>

<xsl:template match="cs:class/cs:id.ref" mode="cs:html"/>

<xsl:template match="cs:property/cs:id.ref" mode="cs:html"/>

<xsl:template match="cs:id.ref" mode="cs:html.parent.separator">
	<xsl:value-of select="','"/>
</xsl:template>

<xsl:template match="cs:id.ref[1]" mode="cs:html.parent.separator">
	<xsl:value-of select="':'"/>
</xsl:template>

<xsl:template match="cs:id.ref" mode="cs:html.parent">
	<xsl:apply-templates select="." mode="cs:html.parent.separator"/>
	<xsl:value-of select="' '"/>
	<xsl:apply-templates select="." mode="cs:html.id.ref"/>
</xsl:template>

<!-- get -->

<xsl:template match="cs:get" mode="cs:html">
	<xsl:apply-templates select="cs:attribute" mode="cs:html.attribute"/>
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<span style="{$cs:html.keyword}">get</span>
			<xsl:value-of select="';'"/>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- set -->

<xsl:template match="cs:set" mode="cs:html">
	<xsl:apply-templates select="cs:attribute" mode="cs:html.attribute"/>
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<span style="{$cs:html.keyword}">set</span>
			<xsl:value-of select="';'"/>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- parameter -->

<xsl:template match="cs:parameter" mode="cs:html.parameter">
	<xsl:apply-templates select="*" mode="cs:html"/>
	<xsl:value-of select="' '"/>
	<span style="{$cs:html.id}"><xsl:value-of select="@id"/></span>
</xsl:template>

<xsl:template match="cs:parameter" mode="cs:html.separator">
	<xsl:value-of select="', '"/>
	<xsl:apply-templates select="." mode="cs:html.parameter"/>
</xsl:template>

<xsl:template match="cs:parameter[1]" mode="cs:html.separator">
	<xsl:apply-templates select="." mode="cs:html.parameter"/>
</xsl:template>

<xsl:template match="cs:parameter" mode="cs:html">
	<xsl:apply-templates select="." mode="cs:html.separator"/>
</xsl:template>

<xsl:template match="cs:property/cs:parameter" mode="cs:html"/>

<!-- property -->

<xsl:template match="cs:property" mode="cs:html">
	<xsl:apply-templates select="cs:attribute" mode="cs:html.attribute"/>
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<xsl:apply-templates select="." mode="cs:html.access"/>
			<xsl:apply-templates select="cs:id.ref" mode="cs:html.id.ref"/>
			<xsl:value-of select="' '"/>
			<span style="{$cs:html.id}"><xsl:value-of select="@id"/></span>
			<xsl:if test="cs:parameter">
				<xsl:value-of select="'['"/>
				<xsl:apply-templates select="cs:parameter" mode="cs:html.separator"/>
				<xsl:value-of select="']'"/>
			</xsl:if>
		</xsl:with-param>
	</xsl:call-template>
	<xsl:apply-templates select="." mode="cs:html.block"/>
</xsl:template>

<!-- method -->

<xsl:template match="cs:method" mode="cs:html">
	<xsl:apply-templates select="cs:attribute" mode="cs:html.attribute"/>
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<xsl:apply-templates select="." mode="cs:html.access"/>
			<xsl:apply-templates select="cs:id.ref" mode="cs:html"/>
			<xsl:value-of select="' '"/>
			<span style="{$cs:html.id}"><xsl:value-of select="@id"/></span>
			<xsl:value-of select="'('"/>
			<xsl:apply-templates select="cs:parameter" mode="cs:html"/>
			<xsl:value-of select="')'"/>
			<xsl:value-of select="';'"/>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- item -->

<xsl:template match="cs:item" mode="cs:html">
	<xsl:apply-templates select="cs:attribute" mode="cs:html.attribute"/>
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<span style="{$cs:html.id}"><xsl:value-of select="@id"/></span>
			<xsl:value-of select="' = '"/>
			<span style="{$cs:html.const}"><xsl:value-of select="@value"/></span>
			<xsl:value-of select="','"/>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- enum -->

<xsl:template match="cs:enum" mode="cs:html">
	<xsl:apply-templates select="cs:attribute" mode="cs:html.attribute"/>
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<xsl:apply-templates select="." mode="cs:html.access"/>
			<span style="{$cs:html.keyword}">enum</span>
			<xsl:value-of select="' '"/>
			<span style="{$cs:html.id}"><xsl:value-of select="@id"/></span>
		</xsl:with-param>
	</xsl:call-template>
	<xsl:apply-templates select="." mode="cs:html.block"/>
</xsl:template>

<!-- interface -->

<xsl:template match="cs:interface" mode="cs:html">
	<xsl:apply-templates select="cs:attribute" mode="cs:html.attribute"/>
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<xsl:apply-templates select="." mode="cs:html.access"/>
			<span style="{$cs:html.keyword}">interface</span>
			<xsl:value-of select="' '"/>
			<span style="{$cs:html.id}"><xsl:value-of select="@id"/></span>
			<xsl:apply-templates select="cs:id.ref" mode="cs:html.parent"/>
		</xsl:with-param>
	</xsl:call-template>
	<xsl:apply-templates select="." mode="cs:html.block"/>
</xsl:template>

<!-- class -->

<xsl:template match="cs:class" mode="cs:html">
	<xsl:apply-templates select="cs:attribute" mode="cs:html.attribute"/>
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<xsl:apply-templates select="." mode="cs:html.access"/>
			<span style="{$cs:html.keyword}">class</span>
			<xsl:value-of select="' '"/>
			<span style="{$cs:html.id}"><xsl:value-of select="@id"/></span>
			<xsl:apply-templates select="cs:id.ref" mode="cs:html.parent"/>
		</xsl:with-param>
	</xsl:call-template>
	<xsl:apply-templates select="." mode="cs:html.block"/>
</xsl:template>

<!-- using -->

<xsl:template match="cs:using" mode="cs:html">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<span style="{$cs:html.keyword}">using</span>
			<xsl:value-of select="' '"/>
			<span style="{$cs:html.id}"><xsl:value-of select="@id"/></span>
			<xsl:value-of select="';'"/>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- namespace -->

<xsl:template match="cs:namespace" mode="cs:html">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<span style="{$cs:html.keyword}">namespace</span>
			<xsl:value-of select="' '"/>
			<span style="{$cs:html.id}"><xsl:value-of select="@id"/></span>
		</xsl:with-param>
	</xsl:call-template>
	<xsl:apply-templates select="." mode="cs:html.block"/>
</xsl:template>

<!-- unit -->

<xsl:template match="cs:unit" mode="txt:main.indent"/>

<xsl:template match="cs:unit" mode="cs:html.unit">
	<xsl:apply-templates select="cs:attribute" mode="cs:html.attribute"/>
	<xsl:apply-templates select="*" mode="cs:html"/>
</xsl:template>

<xsl:template match="cs:unit" mode="cs:html">
	<xsl:apply-templates select="." mode="cs:html.unit"/>	
</xsl:template>

<xsl:template match="/cs:unit" mode="cs:html">
	<html>
		<body><pre><xsl:apply-templates select="." mode="cs:html.unit"/></pre></body>
	</html>
</xsl:template>

<!-- Entry Point -->

<xsl:template match="cs:*">
	<xsl:apply-templates select="." mode="cs:html"/>
</xsl:template>

</xsl:stylesheet>
