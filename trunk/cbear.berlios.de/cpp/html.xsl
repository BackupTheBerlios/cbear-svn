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
	xmlns:cpp="http://cbear.sourceforge.net/cpp"
	xmlns:txt="http://cbear.sourceforge.net/text"
	exclude-result-prefixes="cpp txt xi">

<xsl:import href="../text/main.xsl"/>

<!-- XHTML 1.1. -->
<xsl:output 
	method="xml"
	doctype-public="-//W3C//DTD XHTML 1.1//EN"
	doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"/>

<!-- Styles -->

<xsl:variable name="cpp:html.header">
	border-style: solid;
	border-width: 1px;
	margin: 5px 5px 5px 5px;
</xsl:variable>

<xsl:variable name="cpp:html.code" select="$cpp:html.header"/>

<xsl:variable name="cpp:html.preprocessor">
	color: navy;
</xsl:variable>

<xsl:variable name="cpp:html.keyword">
	color: green;
</xsl:variable>

<xsl:variable name="cpp:html.id">
	color: blue;
</xsl:variable>

<xsl:variable name="cpp:html.const">
	color: magenta;
</xsl:variable>

<!-- Preprocessor Line -->

<xsl:template name="cpp:html.preprocessor">
	<xsl:param name="text"/>
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<span style="{$cpp:html.preprocessor}">
				<xsl:copy-of select="$text"/>
			</span>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- * -->

<xsl:template match="*" mode="cpp:html">
	<xsl:message terminate="no">
		<xsl:value-of select="concat(
			'Unknown tag &#x22;', name(), '&#x22; was skipped.')"/>
	</xsl:message>
</xsl:template>

<!-- block -->

<xsl:template name="cpp:html.block">
	<xsl:param name="begin" select="'{'"/>
	<xsl:param name="end" select="'}'"/>
	<xsl:call-template name="txt:main.block">
		<xsl:with-param name="begin" select="$begin"/>
		<xsl:with-param name="end" select="$end"/>
		<xsl:with-param name="content">
			<xsl:apply-templates select="*" mode="cpp:html"/>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- id.ref -->

<xsl:template match="cpp:id.ref" mode="cpp:html.id.ref.separator">
	<xsl:param name="separator"/>
	<xsl:apply-templates select="." mode="cpp:html.id.ref"/>
	<xsl:value-of select="$separator"/>
</xsl:template>

<xsl:template 
	match="cpp:id.ref[position()=last()]" mode="cpp:html.id.ref.separator">
	<xsl:apply-templates select="." mode="cpp:html.id.ref"/>
</xsl:template>

<xsl:template match="cpp:id.ref" mode="cpp:html.id.ref.type">
	<xsl:param name="begin"/>
	<xsl:param name="end"/>
	<xsl:param name="separator"/>

	<span style="{$cpp:html.id}"><xsl:value-of select="@id"/></span>
	<xsl:value-of select="$begin"/>
	<xsl:apply-templates select="cpp:id.ref" mode="cpp:html.id.ref.separator">
		<xsl:with-param name="separator" select="$separator"/>
	</xsl:apply-templates>
	<xsl:value-of select="$end"/>
</xsl:template>

<xsl:template match="cpp:id.ref" mode="cpp:html.id.ref">
	<xsl:apply-templates select="." mode="cpp:html.id.ref.type"/>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='::']" mode="cpp:html.id.ref">
	<xsl:apply-templates select="." mode="cpp:html.id.ref.type">
		<xsl:with-param name="separator" select="'::'"/>
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='&lt;&gt;']" mode="cpp:html.id.ref">
	<xsl:apply-templates select="." mode="cpp:html.id.ref.type">
		<xsl:with-param name="begin" select="'&lt; '"/>
		<xsl:with-param name="end" select="' &gt;'"/>
		<xsl:with-param name="separator" select="', '"/>
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='.']" mode="cpp:html.id.ref">
	<xsl:apply-templates select="." mode="cpp:html.id.ref.type">
		<xsl:with-param name="separator" select="'.'"/>
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='->']" mode="cpp:html.id.ref">
	<xsl:apply-templates select="." mode="cpp:html.id.ref.type">
		<xsl:with-param name="separator" select="'->'"/>
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='()']" mode="cpp:html.id.ref">
	<xsl:apply-templates select="." mode="cpp:html.id.ref.type">
		<xsl:with-param name="begin" select="'('"/>
		<xsl:with-param name="end" select="')'"/>
		<xsl:with-param name="separator" select="', '"/>
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='[]']" mode="cpp:html.id.ref">
	<xsl:apply-templates select="." mode="cpp:html.id.ref.type">
		<xsl:with-param name="begin" select="'['"/>
		<xsl:with-param name="end" select="']'"/>
		<xsl:with-param name="separator" select="', '"/>
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='&amp;']" mode="cpp:html.id.ref">
	<xsl:apply-templates select="." mode="cpp:html.id.ref.type"/>
	<xsl:text> &amp;</xsl:text>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='const']" mode="cpp:html.id.ref">
	<span style="{$cpp:html.keyword}">const</span>
	<xsl:text> </xsl:text>
	<xsl:apply-templates select="." mode="cpp:html.id.ref.type"/>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='typename']" mode="cpp:html.id.ref">
	<span style="{$cpp:html.keyword}">typename</span>
	<xsl:text> </xsl:text>
	<xsl:apply-templates select="." mode="cpp:html.id.ref.type"/>
</xsl:template>

<xsl:template match="cpp:id.ref" mode="cpp:html">
	<xsl:apply-templates select="." mode="cpp:html.id.ref"/>	
</xsl:template>

<xsl:template 
	match="cpp:type.parameters/cpp:id.ref[position()!=last()]" mode="cpp:html">
	<xsl:apply-templates select="." mode="cpp:html.id.ref"/>
	<xsl:text>, </xsl:text>
</xsl:template>

<xsl:template match="cpp:class/cpp:id.ref" mode="cpp:html"/>

<xsl:template match="cpp:access/cpp:id.ref" mode="cpp:html"/>

<xsl:template match="cpp:method/cpp:id.ref" mode="cpp:html">
	<xsl:apply-templates select="." mode="cpp:html.id.ref"/>
	<xsl:text> </xsl:text>
</xsl:template>

<!-- item -->

<xsl:template match="cpp:item" mode="cpp:html">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<span style="{$cpp:html.id}"><xsl:value-of select="@id"/></span>
			<xsl:text> = </xsl:text>
			<span style="{$cpp:html.const}"><xsl:value-of select="@value"/></span>
			<xsl:text>,</xsl:text>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- enum -->

<xsl:template match="cpp:enum" mode="cpp:html">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<span style="{$cpp:html.keyword}">enum</span>
			<xsl:text> </xsl:text>
			<span style="{$cpp:html.id}"><xsl:value-of select="@id"/></span>
		</xsl:with-param>
	</xsl:call-template>
	<xsl:call-template name="cpp:html.block">
		<xsl:with-param name="end" select="'};'"/>
	</xsl:call-template>
</xsl:template>

<!-- typedef -->

<xsl:template match="cpp:typedef" mode="cpp:html">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<span style="{$cpp:html.keyword}">typedef</span>
			<xsl:text> </xsl:text>
			<xsl:apply-templates select="cpp:id.ref" mode="cpp:html"/>
			<xsl:text> </xsl:text>
			<span style="{$cpp:html.id}"><xsl:value-of select="@id"/></span>
			<xsl:text>;</xsl:text>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- const -->

<xsl:template match="cpp:const" mode="cpp:html">
	<xsl:text> </xsl:text>
	<span style="{$cpp:html.keyword}">const</span>
</xsl:template>

<!-- abstract -->

<xsl:template match="cpp:abstract" mode="cpp:html">
	<xsl:text> = </xsl:text>
	<span style="{$cpp:html.const}">0</span>
</xsl:template>

<!-- explicit -->

<xsl:template match="cpp:explicit" mode="cpp:html">
	<span style="{$cpp:html.keyword}">explicit</span>
	<xsl:text> </xsl:text>	
</xsl:template>

<!-- static -->

<xsl:template match="cpp:static" mode="cpp:html">
	<span style="{$cpp:html.keyword}">static</span>
	<xsl:text> </xsl:text>	
</xsl:template>

<!-- virtual -->

<xsl:template match="cpp:virtual" mode="cpp:html">
	<span style="{$cpp:html.keyword}">virtual</span>
	<xsl:text> </xsl:text>
</xsl:template>

<!-- parameter -->

<xsl:template name="cpp:html.parameter">
	<xsl:apply-templates select="cpp:id.ref" mode="cpp:html"/>
	<xsl:if test="@id">
		<xsl:text> </xsl:text>
		<span style="{$cpp:html.id}"><xsl:value-of select="@id"/></span>
	</xsl:if>
</xsl:template>

<xsl:template match="cpp:parameter" mode="cpp:html">
	<xsl:call-template name="cpp:html.parameter"/>
	<xsl:text>, </xsl:text>
</xsl:template>

<xsl:template match="cpp:parameter[position()=last()]" mode="cpp:html">
	<xsl:call-template name="cpp:html.parameter"/>
</xsl:template>

<!-- exp -->

<xsl:template match="cpp:call/cpp:exp" mode="cpp:html">
	<xsl:apply-templates select="*" mode="cpp:html"/>
	<xsl:text>, </xsl:text>
</xsl:template>

<xsl:template match="cpp:call/cpp:exp[position()=last()]" mode="cpp:html">
	<xsl:apply-templates select="*" mode="cpp:html"/>
</xsl:template>

<!-- call -->

<xsl:template match="cpp:call" mode="cpp:html.call">
	<xsl:apply-templates select="cpp:id.ref" mode="cpp:html"/>
	<xsl:text>(</xsl:text>
	<xsl:apply-templates select="cpp:*" mode="cpp:html"/>
	<xsl:text>)</xsl:text>
</xsl:template>

<xsl:template match="cpp:call" mode="cpp:html">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">	
			<xsl:apply-templates select="." mode="cpp:html.call"/>
			<xsl:text>;</xsl:text>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<xsl:template match="cpp:method/cpp:call" mode="cpp:html">
	<xsl:apply-templates select="." mode="cpp:html.call"/>
	<xsl:text>, </xsl:text>
</xsl:template>

<xsl:template match="cpp:method/cpp:call[position()=last()]" mode="cpp:html">
	<xsl:apply-templates select="." mode="cpp:html.call"/>
</xsl:template>

<!-- body -->

<xsl:template match="cpp:body" mode="cpp:html">
	<xsl:call-template name="cpp:html.block"/>
</xsl:template>

<!-- method -->

<xsl:template match="cpp:method" mode="txt:main.indent"/>

<xsl:template match="cpp:method" mode="cpp:html.method.id">
	<span style="{$cpp:html.id}"><xsl:value-of select="@id"/></span>
</xsl:template>

<xsl:template match="cpp:method[@id='[]']" mode="cpp:html.method.id">
	<span style="{$cpp:html.keyword}">operator</span>
	<xsl:text>[]</xsl:text>
</xsl:template>

<xsl:template match="cpp:method" mode="cpp:html">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<xsl:apply-templates select="cpp:explicit" mode="cpp:html"/>
			<xsl:apply-templates select="cpp:static" mode="cpp:html"/>
			<xsl:apply-templates select="cpp:virtual" mode="cpp:html"/>
			<xsl:apply-templates select="cpp:id.ref" mode="cpp:html"/>
			<xsl:apply-templates select="." mode="cpp:html.method.id"/>
			<xsl:text>(</xsl:text>
			<xsl:apply-templates select="cpp:parameter" mode="cpp:html"/>
			<xsl:text>)</xsl:text>
			<xsl:apply-templates select="cpp:const" mode="cpp:html"/>
			<xsl:apply-templates select="cpp:abstract" mode="cpp:html"/>
			<xsl:if test="cpp:call">
				<xsl:text>: </xsl:text>
				<xsl:apply-templates select="cpp:call" mode="cpp:html"/>
			</xsl:if>
			<xsl:if test="not(cpp:body)">
				<xsl:text>;</xsl:text>
			</xsl:if>
		</xsl:with-param>
	</xsl:call-template>
	<xsl:apply-templates select="cpp:body" mode="cpp:html"/>
</xsl:template>

<!-- access -->

<xsl:template match="cpp:access" mode="txt:main.indent"/>

<xsl:template match="cpp:access" mode="cpp:html">
	<xsl:variable name="access" select="@access"/>
	<xsl:for-each select="..">
		<xsl:call-template name="txt:main.line">
			<xsl:with-param name="text">
				<span style="{$cpp:html.keyword}">
					<xsl:value-of select="$access"/>
				</span>
				<xsl:text>:</xsl:text>
			</xsl:with-param>
		</xsl:call-template>
	</xsl:for-each>
	<xsl:apply-templates select="*" mode="cpp:html"/>
</xsl:template>

<xsl:template 
	match="cpp:access[count(cpp:id.ref) = count(*)]" mode="cpp:html"/>

<!-- class -->

<xsl:template match="cpp:class" mode="cpp:html">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<span style="{$cpp:html.keyword}">class</span>
			<xsl:text> </xsl:text>
			<xsl:apply-templates select="cpp:id.ref" mode="cpp:html.id.ref"/>
			<xsl:if test="cpp:access/cpp:id.ref">:</xsl:if>
		</xsl:with-param>
	</xsl:call-template>
	<xsl:for-each select="cpp:access/cpp:id.ref">
		<xsl:call-template name="txt:main.line">
			<xsl:with-param name="text">
				<span style="{$cpp:html.keyword}">
					<xsl:value-of select="../@access"/>
				</span>
				<xsl:text> </xsl:text>
				<xsl:apply-templates select="." mode="cpp:html.id.ref"/>
				<xsl:if test="position()!=last()">,</xsl:if>
			</xsl:with-param>
		</xsl:call-template>
	</xsl:for-each>
	<xsl:call-template name="cpp:html.block">
		<xsl:with-param name="end" select="'};'"/>
	</xsl:call-template>
</xsl:template>

<!-- id -->

<xsl:template name="cpp:html.id">
	<span style="{$cpp:html.keyword}">class</span>
	<xsl:text> </xsl:text>
	<span style="{$cpp:html.id}"><xsl:value-of select="@id"/></span>
	<xsl:if test="position()!=last()">, </xsl:if>
</xsl:template>

<xsl:template match="cpp:id" mode="cpp:html"/>

<!-- template -->

<xsl:template match="cpp:template" mode="txt:main.indent"/>

<xsl:template match="cpp:template" mode="cpp:html">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<span style="{$cpp:html.keyword}">template</span>
			<xsl:text>&lt;</xsl:text>
			<xsl:for-each select="cpp:id">
				<xsl:call-template name="cpp:html.id"/>
			</xsl:for-each>
			<xsl:text>&gt;</xsl:text>
		</xsl:with-param>
	</xsl:call-template>
	<xsl:apply-templates select="*" mode="cpp:html"/>
</xsl:template>

<!-- namespace -->

<xsl:template match="cpp:namespace" mode="cpp:html">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<span style="{$cpp:html.keyword}">namespace</span>
			<xsl:text> </xsl:text>
			<span style="{$cpp:html.id}"><xsl:value-of select="@id"/></span>
		</xsl:with-param>
	</xsl:call-template>
	<xsl:call-template name="cpp:html.block"/>
</xsl:template>

<!-- include -->

<xsl:template match="cpp:include" mode="cpp:html">
	<xsl:call-template name="cpp:html.preprocessor">
		<xsl:with-param 
			name="text" select="concat('#include &lt;', @href, '&gt;')"/>
	</xsl:call-template>
</xsl:template>

<!-- header -->

<xsl:template match="cpp:header" mode="txt:main.indent"/>

<xsl:template match="cpp:header" mode="cpp:html">
	<div style="{$cpp:html.header}">
		<xsl:variable name="define" select="concat(
			translate(../@id, './', '__'), '_hpp_included')"/>
		<xsl:call-template name="cpp:html.preprocessor">
			<xsl:with-param name="text" select="concat('#ifndef ', $define)"/>
		</xsl:call-template>
		<xsl:call-template name="cpp:html.preprocessor">
			<xsl:with-param name="text" select="concat('#define ', $define)"/>
		</xsl:call-template>
		<xsl:apply-templates select="*" mode="cpp:html"/>
		<xsl:call-template name="cpp:html.preprocessor">
			<xsl:with-param name="text" select="'#endif'"/>
		</xsl:call-template>
	</div>
</xsl:template>

<!-- code -->

<xsl:template match="cpp:code" mode="txt:main.indent"/>

<xsl:template match="cpp:code" mode="cpp:html">
	<div style="{$cpp:html.code}">
		<xsl:call-template name="cpp:html.preprocessor">
			<xsl:with-param 
				name="text" select="concat('#include &lt;', ../@id, '.hpp&gt;')"/>
		</xsl:call-template>
		<xsl:apply-templates select="*" mode="cpp:html"/>
	</div>
</xsl:template>

<!-- unit -->

<xsl:template match="cpp:unit" mode="txt:main.indent"/>

<xsl:template name="cpp:html.unit">
	<xsl:apply-templates select="*" mode="cpp:html"/>
</xsl:template>

<xsl:template match="cpp:unit" mode="cpp:html">
	<xsl:call-template name="cpp:html.unit"/>
</xsl:template>

<xsl:template match="/cpp:unit" mode="cpp:html">
	<html><body><pre><xsl:call-template name="cpp:html.unit"/></pre></body></html>
</xsl:template>

<!-- Entry Point -->

<xsl:template match="cpp:*">
	<xsl:apply-templates select="." mode="cpp:html"/>
</xsl:template>

</xsl:stylesheet>