<?xml version="1.0"?>
<xsl:stylesheet
	version="1.0" 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:rc="http://cbear.berlios.de/windows/resource"
	xmlns:C="http://cbear.berlios.de/cms"
	xmlns:svn="svn:">
	
<xsl:import href="../../text/main.xsl"/>

<xsl:import href="../../cms/html.xsl"/>

<xsl:output method="text" encoding="urf-8"/>

<!--
<xsl:param name="rc:root"/>
<xsl:param name="rc:setup"/>
-->

<xsl:template match="C:section">

	<xsl:variable name="line" select="'&#10;'"/>	

	<xsl:variable name="company">
		<xsl:apply-templates select="." mode="C:company"/>
	</xsl:variable>

	<xsl:variable name="product">
		<xsl:value-of select='@name'/>
	</xsl:variable>

	<xsl:variable name="description">
		<xsl:value-of select="@title"/>
	</xsl:variable>

	<xsl:variable name="date">
		<xsl:apply-templates select="." mode="C:date"/>
	</xsl:variable>

	<xsl:variable name="version">
		<xsl:apply-templates select="." mode="C:version"/>
	</xsl:variable>

	<xsl:value-of select="concat(
		'[assembly: System.Reflection.AssemblyCompany(&#x22;', $company, '&#x22;)]', 
			$line,
		'[assembly: System.Reflection.AssemblyCopyright(&#x22;&#xA9; ', 
			substring($date, 1, 4), ' ',  $company, '&#x22;)]', $line,
		'[assembly: System.Reflection.AssemblyFileVersion(&#x22;', $version, 
			'&#x22;)]', $line,
		'[assembly: System.Reflection.AssemblyInformationalVersion(&#x22;', 
			$version, '&#x22;)]', $line,
		'[assembly: System.Reflection.AssemblyProduct(&#x22;', $product, '&#x22;)]', 
			$line,
		'[assembly: System.Reflection.AssemblyTitle(&#x22;', $description, '&#x22;)]',
			$line,
		'[assembly: System.Reflection.AssemblyVersion(&#x22;', $version, 
			'&#x22;)]', $line)"/>
</xsl:template>

</xsl:stylesheet>
