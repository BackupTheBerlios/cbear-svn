<?xml version="1.0"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:C="http://cbear.berlios.de/c" 
	xmlns:T="http://cbear.berlios.de/text"
	xmlns="http://www.w3.org/1999/xhtml">

	<xsl:import href="../text/main.xsl"/>

	<!-- XHTML 1.1. -->
	<xsl:output 
		method="xml"
		indent="no"
		doctype-public="-//W3C//DTD XHTML 1.1//EN"
		doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"/>

	<xsl:variable name="C:style.div" select="'border: solid 1px;'"/>
	<xsl:variable name="C:style.pp" select="'color: grey;'"/>
	<xsl:variable name="C:style.error" select="'color: red;'"/>
	<xsl:variable name="C:style.id" select="'color: blue;'"/>
	<xsl:variable name="C:style.key" select="'color: green;'"/>
	<xsl:variable name="C:style.const" select="'color: brown;'"/>

	<!-- Indent -->

	<xsl:template match="C:*" mode="T:main.indent"/>

	<xsl:template match="C:body" mode="T:main.indent">
		<xsl:apply-imports/>
	</xsl:template>

	<!-- * -->
	<xsl:template match="*">
		<span style="{$C:style.error}">
			<xsl:value-of select="local-name()"/>
		</span>
	</xsl:template>

	<!-- include -->

	<xsl:template name="C:include">
		<xsl:param name="href" select="@href"/>
		<xsl:call-template name="C:pp">
			<xsl:with-param 
				name="text" select="concat('include &lt;', $href, '&gt;')"/>
		</xsl:call-template>
	</xsl:template>

	<xsl:template match="C:include" mode="C:include">
		<xsl:call-template name="C:include"/>
	</xsl:template>

	<xsl:template match="C:include"/>

	<!-- id.ref -->	

	<xsl:template match="C:id.ref[@type='_*']">
		<xsl:apply-templates select="*"/>
		<xsl:text>*</xsl:text>
		<xsl:if test="@memory">
			<span style="{$C:style.key}">
				<xsl:value-of select="@memory"/>
			</span>
			<xsl:value-of select="' '"/>
		</xsl:if>
	</xsl:template>

	<xsl:template match="C:id.ref[@type='*_']">
		<xsl:text>*</xsl:text>
		<xsl:apply-templates select="*"/>		
	</xsl:template>	

	<xsl:template match="C:id.ref[@id]">
		<span style="{$C:style.id}">
			<xsl:value-of select="@id"/>
		</span>
		<xsl:if test="@memory">
			<xsl:value-of select="' '"/>
			<span style="{$C:style.key}">
				<xsl:value-of select="@memory"/>
			</span>
		</xsl:if>
	</xsl:template>

	<xsl:template match="C:id.ref[@type='()']">
		<xsl:text>(</xsl:text>
		<xsl:apply-templates select="C:id.ref[1]"/>
		<xsl:text>)</xsl:text>
	</xsl:template>

	<xsl:template match="C:id.ref[@type='()_']">
		<xsl:text>(</xsl:text>
		<xsl:apply-templates select="C:id.ref[1]"/>
		<xsl:text>)</xsl:text>
		<xsl:apply-templates select="C:id.ref[2]"/>
	</xsl:template>

	<xsl:template match="C:id.ref[@type='_()']">
		<xsl:apply-templates select="C:id.ref[1]"/>
		<xsl:text>(</xsl:text>
		<xsl:for-each select="C:id.ref[position() &gt; 1]">
			<xsl:apply-templates select="."/>
			<xsl:if test="position()!=last()">, </xsl:if>
		</xsl:for-each>
		<xsl:text>)</xsl:text>
	</xsl:template>

	<xsl:template match="C:id.ref[@type='const']">
		<span style="{$C:style.const}">
			<xsl:value-of select="@value"/>
		</span>
	</xsl:template>

	<xsl:template match="C:id.ref[@type='=']">
		<xsl:apply-templates select="C:id.ref[1]"/>
		<xsl:text> = </xsl:text>
		<xsl:apply-templates select="C:id.ref[2]"/>
	</xsl:template>

	<xsl:template match="C:id.ref[@type='[]']">
		<xsl:apply-templates select="C:id.ref[1]"/>
		<xsl:text>[</xsl:text>
		<xsl:apply-templates select="C:id.ref[2]"/>
		<xsl:text>]</xsl:text>
	</xsl:template>

	<xsl:template match="C:id.ref[@type='-&gt;']">
		<xsl:apply-templates select="C:id.ref[1]"/>
		<xsl:text>-&gt;</xsl:text>
		<xsl:apply-templates select="C:id.ref[2]"/>
	</xsl:template>

	<xsl:template match="C:id.ref[@type='.']">
		<xsl:apply-templates select="C:id.ref[1]"/>
		<xsl:text>.</xsl:text>
		<xsl:apply-templates select="C:id.ref[2]"/>
	</xsl:template>

	<xsl:template match="C:id.ref[@type=' ']">
		<xsl:apply-templates select="C:id.ref[1]"/>
		<xsl:value-of select="' '"/>
		<xsl:apply-templates select="C:id.ref[2]"/>
	</xsl:template>

	<xsl:template match="C:id.ref[@type='{}']">
		<xsl:text>{ </xsl:text>
		<xsl:for-each select="C:id.ref">
			<xsl:apply-templates select="."/>		
			<xsl:if test="position()!=last()">
				<xsl:text>, </xsl:text>
			</xsl:if>
		</xsl:for-each>
		<xsl:text> }</xsl:text>
	</xsl:template>

	<xsl:template match="C:id.ref[@type='struct']">
		<span style="{$C:style.key}">struct</span>
		<xsl:text> </xsl:text>
		<span style="{$C:style.id}"><xsl:value-of select="@id"/></span>
	</xsl:template>

	<xsl:template match="C:id.ref[@type='+']">
		<xsl:apply-templates select="C:id.ref[1]"/>
		<xsl:text>+</xsl:text>
		<xsl:apply-templates select="C:id.ref[2]"/>		
	</xsl:template>

	<!-- struct -->
	<xsl:template match="C:struct">
		<xsl:call-template name="T:main.line">
			<xsl:with-param name="text">
				<span style="{$C:style.key}">struct</span>
				<xsl:text> </xsl:text>
				<span style="{$C:style.id}"><xsl:value-of select="@id"/></span>
				<xsl:text>;</xsl:text>
			</xsl:with-param>
		</xsl:call-template>		
	</xsl:template>

	<xsl:template match="C:struct[C:body]">
		<xsl:call-template name="T:main.line">
			<xsl:with-param name="text">
				<span style="{$C:style.key}">struct</span>
				<xsl:text> </xsl:text>
				<span style="{$C:style.id}"><xsl:value-of select="@id"/></span>
			</xsl:with-param>
		</xsl:call-template>
		<xsl:apply-templates select="C:body">
			<xsl:with-param name="end" select="'};'"/>
		</xsl:apply-templates>
	</xsl:template>

	<!-- typedef -->
	<xsl:template match="C:typedef">
		<xsl:call-template name="T:main.line">
			<xsl:with-param name="text">
				<span style="{$C:style.key}">typedef</span>
				<xsl:text> </xsl:text>
				<xsl:apply-templates select="C:id.ref[1]"/>
				<xsl:text> </xsl:text>
				<xsl:apply-templates select="C:id.ref[2]"/>
				<xsl:text>;</xsl:text>
			</xsl:with-param>
		</xsl:call-template>		
	</xsl:template>

	<!-- exp -->
	<xsl:template match="C:exp">
		<xsl:call-template name="T:main.line">
			<xsl:with-param name="text">
				<xsl:apply-templates select="*"/>
				<xsl:text>;</xsl:text>
			</xsl:with-param>
		</xsl:call-template>
	</xsl:template>

	<!-- break -->
	<xsl:template match="C:break">
		<xsl:call-template name="T:main.line">
			<xsl:with-param name="text">
				<span style="{$C:style.key}">break</span>
				<xsl:text>;</xsl:text>	
			</xsl:with-param>
		</xsl:call-template>
	</xsl:template>

	<!-- case -->
	<xsl:template match="C:case">
		<xsl:variable name="text">
			<span style="{$C:style.key}">case</span>
			<xsl:text> </xsl:text>
			<xsl:apply-templates select="*"/>
			<xsl:text>:</xsl:text>
		</xsl:variable>
		<xsl:for-each select="..">
			<xsl:call-template name="T:main.line">
				<xsl:with-param name="text" select="$text"/>
			</xsl:call-template>		
		</xsl:for-each>
	</xsl:template>

	<!-- switch -->
	<xsl:template match="C:switch">
		<xsl:call-template name="T:main.line">
			<xsl:with-param name="text">
				<span style="{$C:style.key}">switch</span>
				<xsl:text>(</xsl:text>
				<xsl:apply-templates select="C:id.ref"/>
				<xsl:text>)</xsl:text>
			</xsl:with-param>
		</xsl:call-template>
		<xsl:apply-templates select="C:body"/>
	</xsl:template>

	<!-- body -->
	<xsl:template match="C:body">
		<xsl:param name="end" select="'}'"/>
		<xsl:call-template name="T:main.line">
			<xsl:with-param name="text" select="'{'"/>
		</xsl:call-template>
		<xsl:apply-templates select="*"/>
		<xsl:call-template name="T:main.line">
			<xsl:with-param name="text" select="$end"/>
		</xsl:call-template>
	</xsl:template>

	<!-- function -->
	<xsl:template match="C:function">
		<xsl:call-template name="T:main.line">
			<xsl:with-param name="text">
				<xsl:apply-templates select="C:id.ref"/>
				<xsl:text> </xsl:text>
				<span style="{$C:style.id}">
					<xsl:value-of select="@id"/>
				</span>
				<span>(</span>
				<xsl:for-each select="C:parameter">
					<xsl:if test="position()!=1">, </xsl:if>			
					<xsl:apply-templates select="C:id.ref"/>
					<xsl:text> </xsl:text>
					<span style="{$C:style.id}">
						<xsl:value-of select="@id"/>
					</span>			
				</xsl:for-each>
				<span>)</span>
				<xsl:if test="not(C:body)">;</xsl:if>
			</xsl:with-param>
		</xsl:call-template>
		<xsl:apply-templates select="C:body"/>		
	</xsl:template>
	
	<!-- pp -->

	<xsl:template name="C:pp">
		<xsl:param name="text"/>
		<xsl:call-template name="T:main.line">
			<xsl:with-param name="text">	
				<span style="{$C:style.pp}">
					<xsl:text>#</xsl:text>
					<xsl:copy-of select="$text"/>
				</span>
			</xsl:with-param>
		</xsl:call-template>
	</xsl:template>

	<!-- h -->
	<xsl:template match="C:h">
		<div style="{$C:style.div}">
			<pre>				
				<xsl:variable 
					name="define" 
					select="concat(
						translate(
							../@id, 
							'.abcdefghijklmnopqrstuvwxyz', 
							'_ABCDEFGHIJKLMNOPQRSTUVWXYZ'),
						'_H_INCLUDED')"/>
				<xsl:call-template name="C:pp">
					<xsl:with-param name="text" select="concat('ifndef ', $define)"/>
				</xsl:call-template>
				<xsl:call-template name="C:pp">
					<xsl:with-param name="text" select="concat('define ', $define)"/>
				</xsl:call-template>
				<xsl:apply-templates select="C:include" mode="C:include"/>
				<xsl:call-template name="C:pp">
					<xsl:with-param name="text" select="'ifdef __cplusplus'"/>
				</xsl:call-template>
				<xsl:call-template name="T:main.line">
					<xsl:with-param name="text">
						<span style="{$C:style.key}">extern</span>
						<xsl:text> </xsl:text>
						<span style="{$C:style.const}">"C"</span>
					</xsl:with-param>
				</xsl:call-template>
				<xsl:call-template name="T:main.line">
					<xsl:with-param name="text" select="'{'"/>
				</xsl:call-template>
				<xsl:call-template name="C:pp">
					<xsl:with-param name="text" select="'endif'"/>
				</xsl:call-template>
				<xsl:apply-templates select="*"/>
				<xsl:call-template name="C:pp">
					<xsl:with-param name="text" select="'ifdef __cplusplus'"/>
				</xsl:call-template>
				<xsl:call-template name="T:main.line">
					<xsl:with-param name="text" select="'}'"/>
				</xsl:call-template>
				<xsl:call-template name="C:pp">
					<xsl:with-param name="text" select="'endif'"/>
				</xsl:call-template>
				<xsl:call-template name="C:pp">
					<xsl:with-param name="text" select="'endif'"/>
				</xsl:call-template>
			</pre>
		</div>
	</xsl:template>

	<!-- c -->
	<xsl:template match="C:c">
		<div style="{$C:style.div}">
			<pre>
				<xsl:call-template name="C:include">
					<xsl:with-param name="href" select="concat(../@id, '.h')"/>
				</xsl:call-template>
				<xsl:apply-templates select="C:include" mode="C:include"/>
				<xsl:apply-templates select="*"/>
			</pre>
		</div>
	</xsl:template>	
	
	<!-- unit -->
	<xsl:template match="C:unit">
		<html>
			<body>
				<xsl:apply-templates select="C:*"/>
			</body>
		</html>
	</xsl:template>

</xsl:stylesheet>