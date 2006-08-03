<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:C="http://cbear.berlios.de/cms"
	xmlns:S="svn:"
	xmlns:H="http://www.w3.org/1999/xhtml"
	exclude-result-prefixes="C S H">

<xsl:import href="html.xsl"/>

<xsl:template match="/C:section">
	<html>
		<head>
			<title>
				<xsl:value-of select="@name"/>
			</title>
			<style type="text/css">
				<xsl:value-of select="normalize-space($C:style)"/>
			</style>
		</head>
		<body>
			<table class="main">
				<!-- Header -->
				<tr>
					<td colspan="3" class="menu">
						<xsl:apply-templates select="." mode="C:header"/>
					</td>
				</tr>
				<!-- Path -->
				<xsl:variable name="path">
					<xsl:apply-templates select="." mode="C:path"/>
				</xsl:variable>
				<xsl:if test="string($path)!=''">
					<tr>
						<td colspan="3" class="menu">
							<div class="menu">
								<xsl:copy-of select="$path"/>
							</div>
						</td>
					</tr>
				</xsl:if>
				<!-- -->
				<tr class="tr">
					<td class="menu">
						<!-- Properties -->
						<xsl:apply-templates select="." mode="C:properties"/>
						<!-- Menu -->
						<xsl:apply-templates select="." mode="C:menu"/>
						<!-- Language -->
						<xsl:variable name="languages">
							<div class="menu">
								<xsl:apply-templates select="." mode="C:language"/>
							</div>
						</xsl:variable>
						<xsl:if test="string($languages)!=''">
							<xsl:copy-of select="$languages"/>
						</xsl:if>
						<!-- Files -->
						<xsl:apply-templates select="." mode="C:files"/>
					</td>
					<td class="content">
						<!-- Content -->
						<xsl:apply-templates select="." mode="C:content"/>
					</td>
					<td class="menu">
						<div class="menu" style="text-align: center;">
							<xsl:copy-of select="document('cbear.xml')/H:html/H:search/*"/>
						</div>
						<div class="menu" style="text-align: center;">
							<xsl:copy-of select="document('cbear.xml')/H:html/H:ad/*"/>
						</div>
					</td>
				</tr>
			</table>
		</body>
	</html>
</xsl:template>

</xsl:stylesheet>
