<?xml version="1.0"?>
<xsl:stylesheet
	version="1.0" 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:rc="http://cbear.berlios.de/windows/resource"
	xmlns:svn="svn:">
	
<xsl:import href="../../text/main.xsl"/>

<xsl:output method="text" encoding="urf-8"/>

<xsl:param name="rc:root"/>
<xsl:param name="rc:setup"/>

<xsl:template match="section">

	<xsl:variable name="line" select="'&#10;'"/>	

	<xsl:variable name="company">
		<xsl:value-of select="document($rc:setup)/setup/company"/>
	</xsl:variable>

	<xsl:variable name="product">
		<xsl:value-of select="document($rc:setup)/setup/name"/>
	</xsl:variable>

	<xsl:variable name="date">
		<xsl:value-of select="document(concat($rc:root, '/.svn/entries'))/
			svn:wc-entries/svn:entry[@name='']/@committed-date"/>
	</xsl:variable>

	<xsl:variable name="version">
		<xsl:value-of select="document($rc:setup)/setup/version/number"/>
		<xsl:value-of select="'.'"/>
		<xsl:value-of select="document(concat($rc:root, '/.svn/entries'))/
			svn:wc-entries/svn:entry[@name='']/@committed-rev"/>
	</xsl:variable>

	<xsl:value-of select="concat(
		'[assembly: System.Reflection.AssemblyCompany(&#x22;', $company, '&#x22;)]', 
			$line,
		'[assembly: System.Reflection.AssemblyCopyright(&#x22;&#xA9; ', 
			substring($date, 1, 4), ' ',  $company, '&#x22;)]', $line,
		'[assembly: System.Reflection.AssemblyDescription(&#x22;', @name, 
			'&#x22;)]', $line,
		'[assembly: System.Reflection.AssemblyFileVersion(&#x22;', $version, 
			'&#x22;)]', $line,
		'[assembly: System.Reflection.AssemblyInformationalVersion(&#x22;', 
			$version, '&#x22;)]', $line,
		'[assembly: System.Reflection.AssemblyProduct(&#x22;', $product, '&#x22;)]', 
			$line,
		'[assembly: System.Reflection.AssemblyTitle(&#x22;', @name, '&#x22;)]', 
			$line,
		'[assembly: System.Reflection.AssemblyVersion(&#x22;', $version, 
			'&#x22;)]', $line)"/>
</xsl:template>

</xsl:stylesheet>
