<?xml version="1.0"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:C="http://cbear.berlios.de/c" 
	xmlns="http://www.w3.org/1999/xhtml">

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

	<!-- * -->
	<xsl:template match="*">
		<span style="{$C:style.error}">
			<xsl:value-of select="local-name()"/>
		</span>
	</xsl:template>

	<!-- id.ref -->	
	<xsl:template match="C:id.ref[@type='_*']">
		<xsl:apply-templates select="*"/>
		<xsl:text>*</xsl:text>
	</xsl:template>

	<xsl:template match="C:id.ref[@type='*_']">
		<xsl:text>*</xsl:text>
		<xsl:apply-templates select="*"/>		
	</xsl:template>	

	<xsl:template match="C:id.ref[@id]">
		<span style="{$C:style.id}">
			<xsl:value-of select="@id"/>
		</span>		
	</xsl:template>

	<xsl:template match="C:id.ref[@type='()']">
		<xsl:text>(</xsl:text>
		<xsl:apply-templates select="*"/>
		<xsl:text>)</xsl:text>
	</xsl:template>

	<xsl:template match="C:id.ref[@type='const']">
		<span style="{$C:style.const}">
			<xsl:value-of select="@value"/>
		</span>
	</xsl:template>

	<xsl:template match="C:id.ref[@type='=']">
		<xsl:apply-templates select="*[1]"/>
		<xsl:text> = </xsl:text>
		<xsl:apply-templates select="*[2]"/>
	</xsl:template>

	<!-- exp -->
	<xsl:template match="C:exp">
		<xsl:apply-templates select="*"/>
		<xsl:text>;&#10;</xsl:text>
	</xsl:template>

	<!-- break -->
	<xsl:template match="C:break">
		<span style="{$C:style.key}">break</span>
		<xsl:text>;&#10;</xsl:text>
	</xsl:template>

	<!-- case -->
	<xsl:template match="C:case">
		<span style="{$C:style.key}">case</span>
		<xsl:text> </xsl:text>
		<xsl:apply-templates select="*"/>
		<xsl:text>:&#10;</xsl:text>
	</xsl:template>

	<!-- switch -->
	<xsl:template match="C:switch">
		<span style="{$C:style.key}">switch</span>
		<xsl:text>(</xsl:text>
		<xsl:apply-templates select="C:id.ref"/>
		<xsl:text>)&#10;</xsl:text>
		<xsl:apply-templates select="C:body"/>
	</xsl:template>

	<!-- body -->
	<xsl:template match="C:body">
		<xsl:text>{&#10;</xsl:text>
		<xsl:apply-templates select="*"/>
		<xsl:text>}&#10;</xsl:text>
	</xsl:template>

	<!-- function -->
	<xsl:template match="C:function">
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
		<xsl:text>&#10;</xsl:text>
		<xsl:apply-templates select="C:body"/>		
	</xsl:template>
	
	<!-- h -->
	<xsl:template match="C:h">
		<div style="{$C:style.div}">
			<pre>
				<span style="{$C:style.pp}">
					<xsl:variable 
						name="define" 
						select="concat(
							translate(
								../@id, 
								'.abcdefghijklmnopqrstuvwxyz', 
								'_ABCDEFGHIJKLMNOPQRSTUVWXYZ'),
							'_H_INCLUDED&#10;')"/>
					<xsl:value-of select="concat('#ifndef ', $define)"/>
					<xsl:value-of select="concat('#define ', $define)"/>
				</span>
				<xsl:apply-templates select="*"/>
				<span style="{$C:style.pp}">
					<xsl:value-of select="'#endif&#10;'"/>
				</span>
			</pre>
		</div>
	</xsl:template>

	<!-- c -->
	<xsl:template match="C:c">
		<div style="{$C:style.div}">
			<pre>
				<span style="{$C:style.pp}">
					<xsl:value-of select="concat('#include &lt;', ../@id, '.h&gt;&#10;')"/>
				</span>
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