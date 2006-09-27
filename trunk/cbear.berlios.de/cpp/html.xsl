<?xml version="1.0"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:cpp="http://cbear.berlios.de/cpp"
	xmlns:txt="http://cbear.berlios.de/text"
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

<xsl:template match="cpp:id.ref[@type='.']" mode="cpp:html.id.ref">
	<xsl:apply-templates select="." mode="cpp:html.id.ref.type">
		<xsl:with-param name="separator" select="'.'"/>
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
	<!--
	<xsl:apply-templates select="." mode="cpp:html.id.ref.type"/>
	-->
	<xsl:apply-templates 
		select="cpp:id.ref[1]" mode="cpp:html.id.ref"/>
	<xsl:text> &amp; </xsl:text>
	<xsl:apply-templates 
		select="cpp:id.ref[2]" mode="cpp:html.id.ref"/>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='|']" mode="cpp:html.id.ref">
	<xsl:apply-templates 
		select="cpp:id.ref[1]" mode="cpp:html.id.ref"/>
	<xsl:text>|</xsl:text>
	<xsl:apply-templates 
		select="cpp:id.ref[2]" mode="cpp:html.id.ref"/>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='&lt;&lt;']" mode="cpp:html.id.ref">
	<xsl:apply-templates 
		select="cpp:id.ref[1]" mode="cpp:html.id.ref"/>
	<xsl:text> &lt;&lt; </xsl:text>
	<xsl:apply-templates 
		select="cpp:id.ref[2]" mode="cpp:html.id.ref"/>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='&gt;&gt;']" mode="cpp:html.id.ref">
	<xsl:apply-templates 
		select="cpp:id.ref[1]" mode="cpp:html.id.ref"/>
	<xsl:text> &gt;&gt; </xsl:text>
	<xsl:apply-templates 
		select="cpp:id.ref[2]" mode="cpp:html.id.ref"/>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='==']" mode="cpp:html.id.ref">
	<xsl:apply-templates 
		select="cpp:id.ref[1]" mode="cpp:html.id.ref"/>
	<xsl:text>==</xsl:text>
	<xsl:apply-templates 
		select="cpp:id.ref[2]" mode="cpp:html.id.ref"/>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='!=']" mode="cpp:html.id.ref">
	<xsl:apply-templates 
		select="cpp:id.ref[1]" mode="cpp:html.id.ref"/>
	<xsl:text>!=</xsl:text>
	<xsl:apply-templates 
		select="cpp:id.ref[2]" mode="cpp:html.id.ref"/>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='&amp;&amp;']" mode="cpp:html.id.ref">
	<xsl:for-each select="cpp:id.ref">
		<xsl:apply-templates select="." mode="cpp:html.id.ref"/>
		<xsl:if test="position()!=last()">
			<xsl:text>&amp;&amp;</xsl:text>
		</xsl:if>
	</xsl:for-each>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='||']" mode="cpp:html.id.ref">
	<xsl:for-each select="cpp:id.ref">
		<xsl:apply-templates select="." mode="cpp:html.id.ref"/>
		<xsl:if test="position()!=last()">
			<xsl:value-of select="'||'"/>
		</xsl:if>
	</xsl:for-each>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='=']" mode="cpp:html.id.ref">
	<xsl:apply-templates 
		select="cpp:id.ref[1]" mode="cpp:html.id.ref"/>
	<xsl:text>=</xsl:text>
	<xsl:apply-templates 
		select="cpp:id.ref[2]" mode="cpp:html.id.ref"/>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='*']" mode="cpp:html.id.ref">
	<xsl:text>*</xsl:text>
	<xsl:apply-templates 
		select="cpp:id.ref" mode="cpp:html.id.ref"/>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='static']" mode="cpp:html.id.ref">
	<span style="{$cpp:html.keyword}">static</span>
	<xsl:value-of select="' '"/>
	<xsl:apply-templates select="." mode="cpp:html.id.ref.type"/>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='const']" mode="cpp:html.id.ref">
	<span style="{$cpp:html.keyword}">const</span>
	<xsl:value-of select="' '"/>
	<xsl:apply-templates select="." mode="cpp:html.id.ref.type"/>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='typename']" mode="cpp:html.id.ref">
	<span style="{$cpp:html.keyword}">typename</span>
	<xsl:value-of select="' '"/>
	<xsl:apply-templates select="." mode="cpp:html.id.ref.type"/>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='declare']" mode="cpp:html.id.ref">
	<xsl:apply-templates select="cpp:id.ref[1]" mode="cpp:html.id.ref"/>
	<xsl:value-of select="' '"/>
	<span style="{$cpp:html.id}"><xsl:value-of select="@id"/></span>
	<xsl:if test="cpp:id.ref[2]">
		<xsl:text> = </xsl:text>
		<xsl:apply-templates select="cpp:id.ref[2]" mode="cpp:html.id.ref"/>
	</xsl:if>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='return']" mode="cpp:html.id.ref">
	<span style="{$cpp:html.keyword}">return</span>
	<xsl:value-of select="' '"/>
	<xsl:apply-templates select="cpp:id.ref" mode="cpp:html.id.ref"/>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='this']" mode="cpp:html.id.ref">
	<span style="{$cpp:html.keyword}">this</span>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='value']" mode="cpp:html.id.ref">
	<span style="{$cpp:html.const}"><xsl:value-of select="@id"/></span>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='{}']" mode="cpp:html.id.ref">
	<xsl:text> { </xsl:text>
	<xsl:for-each select="cpp:id.ref">
		<xsl:apply-templates select="." mode="cpp:html.id.ref"/>
		<xsl:text>, </xsl:text>
	</xsl:for-each>
	<xsl:text> } </xsl:text>
</xsl:template>

<xsl:template match="cpp:id.ref[@type='~']" mode="cpp:html.id.ref">
	<xsl:text>~</xsl:text>
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
	<xsl:value-of select="' '"/>
</xsl:template>

<xsl:template match="cpp:body/cpp:id.ref" mode="cpp:html">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">	
			<xsl:apply-templates select="." mode="cpp:html.id.ref"/>
			<xsl:text>;</xsl:text>
		</xsl:with-param>
	</xsl:call-template>
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
			<xsl:value-of select="' '"/>
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
			<xsl:value-of select="' '"/>
			<xsl:apply-templates select="cpp:id.ref" mode="cpp:html"/>
			<xsl:value-of select="' '"/>
			<span style="{$cpp:html.id}"><xsl:value-of select="@id"/></span>
			<xsl:text>;</xsl:text>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- const -->

<xsl:template match="cpp:const" mode="cpp:html">
	<xsl:value-of select="' '"/>
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
	<xsl:value-of select="' '"/>	
</xsl:template>

<!-- static -->

<xsl:template match="cpp:static" mode="cpp:html">
	<span style="{$cpp:html.keyword}">static</span>
	<xsl:value-of select="' '"/>	
</xsl:template>

<!-- virtual -->

<xsl:template match="cpp:virtual" mode="cpp:html">
	<span style="{$cpp:html.keyword}">virtual</span>
	<xsl:value-of select="' '"/>
</xsl:template>

<!-- stdcall -->

<xsl:template match="cpp:stdcall" mode="cpp:html">
	<span style="{$cpp:html.keyword}">__stdcall</span>
	<xsl:value-of select="' '"/>
</xsl:template>

<!-- cdecl -->

<xsl:template match="cpp:cdecl" mode="cpp:html">
	<span style="{$cpp:html.keyword}">__cdecl</span>
	<xsl:value-of select="' '"/>
</xsl:template>

<!-- parameter -->

<xsl:template name="cpp:html.parameter">
	<xsl:apply-templates select="cpp:id.ref" mode="cpp:html"/>
	<xsl:if test="@id">
		<xsl:value-of select="' '"/>
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

<!-- ctor -->

<xsl:template match="cpp:ctor" mode="cpp:html.ctor">
	<xsl:apply-templates select="cpp:*" mode="cpp:html"/>
	<!--
	<xsl:apply-templates select="cpp:id.ref" mode="cpp:html"/>
	<xsl:text>(</xsl:text>
	<xsl:apply-templates select="cpp:*" mode="cpp:html"/>
	<xsl:text>)</xsl:text>
	-->
</xsl:template>

<xsl:template match="cpp:method/cpp:ctor" mode="cpp:html">
	<xsl:apply-templates select="." mode="cpp:html.ctor"/>
	<xsl:text>, </xsl:text>
</xsl:template>

<xsl:template match="cpp:method/cpp:ctor[position()=last()]" mode="cpp:html">
	<xsl:apply-templates select="." mode="cpp:html.ctor"/>
</xsl:template>

<!-- catch -->

<xsl:template match="cpp:catch" mode="txt:main.indent"/>

<xsl:template match="cpp:catch" mode="cpp:html">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<span style="{$cpp:html.keyword}">catch</span>
			<xsl:text>(</xsl:text>
			<xsl:apply-templates select="cpp:parameter" mode="cpp:html"/>
			<xsl:text>)</xsl:text>
		</xsl:with-param>
	</xsl:call-template>
	<xsl:apply-templates select="cpp:body" mode="cpp:html"/>
</xsl:template>

<!-- try -->

<xsl:template match="cpp:try" mode="txt:main.indent"/>

<xsl:template match="cpp:try" mode="cpp:html">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<span style="{$cpp:html.keyword}">try</span>
		</xsl:with-param>
	</xsl:call-template>
	<xsl:apply-templates select="*" mode="cpp:html"/>
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
			<xsl:apply-templates select="cpp:stdcall|cpp:cdecl" mode="cpp:html"/>
			<xsl:apply-templates select="." mode="cpp:html.method.id"/>
			<xsl:text>(</xsl:text>
			<xsl:apply-templates select="cpp:parameter" mode="cpp:html"/>
			<xsl:text>)</xsl:text>
			<xsl:apply-templates select="cpp:const" mode="cpp:html"/>
			<xsl:apply-templates select="cpp:abstract" mode="cpp:html"/>
			<xsl:if test="cpp:ctor">
				<xsl:text>: </xsl:text>
				<xsl:apply-templates select="cpp:ctor" mode="cpp:html"/>
			</xsl:if>
			<xsl:if test="not(cpp:body)">
				<xsl:text>;</xsl:text>
			</xsl:if>
		</xsl:with-param>
	</xsl:call-template>
	<xsl:apply-templates select="cpp:body" mode="cpp:html"/>
</xsl:template>

<!-- object -->

<xsl:template match="cpp:object" mode="cpp:html">
	<xsl:call-template name="txt:main.line">
		<xsl:with-param name="text">
			<xsl:apply-templates select="cpp:id.ref[1]" mode="cpp:html.id.ref"/>
			<xsl:value-of select="' '"/>
			<span style="{$cpp:html.id}"><xsl:value-of select="@id"/></span>
			<xsl:if test="cpp:id.ref[2]">
				<xsl:text> = </xsl:text>
				<xsl:apply-templates select="cpp:id.ref[2]" mode="cpp:html.id.ref"/>
			</xsl:if>
			<xsl:text>;</xsl:text>
		</xsl:with-param>
	</xsl:call-template>
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
			<xsl:value-of select="' '"/>
			<xsl:apply-templates select="cpp:id.ref" mode="cpp:html.id.ref"/>
			<xsl:if test="not(cpp:access)">;</xsl:if>
			<xsl:if test="cpp:access/cpp:id.ref">:</xsl:if>
		</xsl:with-param>
	</xsl:call-template>
	<xsl:if test="cpp:access">
		<xsl:for-each select="cpp:access/cpp:id.ref">
			<xsl:call-template name="txt:main.line">
				<xsl:with-param name="text">
					<span style="{$cpp:html.keyword}">
						<xsl:value-of select="../@access"/>
					</span>
					<xsl:value-of select="' '"/>
					<xsl:apply-templates select="." mode="cpp:html.id.ref"/>
					<xsl:if test="position()!=last()">,</xsl:if>
				</xsl:with-param>
			</xsl:call-template>
		</xsl:for-each>
		<xsl:call-template name="cpp:html.block">
			<xsl:with-param name="end" select="'};'"/>
		</xsl:call-template>
	</xsl:if>
</xsl:template>

<!-- id -->

<xsl:template name="cpp:html.id">
	<span style="{$cpp:html.keyword}">class</span>
	<xsl:value-of select="' '"/>
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
			<xsl:value-of select="' '"/>
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
			translate(
				translate(../@id, './', '__'), 
				$txt:main.lowercase, 
				$txt:main.uppercase),
			'_HPP_INCLUDED')"/>
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
