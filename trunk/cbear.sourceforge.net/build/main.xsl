<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:date="http://exslt.org/dates-and-times"
	xmlns:str="http://exslt.org/strings"
	xmlns:exsl="http://exslt.org/common"
	xmlns:cbear.exslt.common="http://cbear.sourceforge.net/exslt/common"
	xmlns="http://www.w3.org/1999/xhtml"
	extension-element-prefixes="date str exsl"
	exclude-result-prefixes="xi cbear.exslt.common">

<xsl:import href="../exslt/common/document.xsl"/>

<xsl:output method="text" encoding="iso-8859-1"/>

<xsl:template match="version">
	<xsl:variable name="sub">
		<xsl:if test="@stable=''">
			<xsl:variable name="date" select="date:date-time()"/>
			<xsl:value-of select="concat(
				'-',
				date:year($date),
				'-',
				str:align(date:month-in-year($date), '00', 'right'), 
				'-', 
				str:align(date:day-in-month($date), '00', 'right'), 
				'-',
				str:align(date:hour-in-day($date), '00', 'right'), 
				'-',
				str:align(date:minute-in-hour($date), '00', 'right'),
				'-',
				str:align(date:second-in-minute($date), '00', 'right'))"/>
		</xsl:if>
	</xsl:variable>
	<xsl:variable 
		name="name" 
		select="concat(
			'cbear-', 
			@value, 
			$sub,
			'.zip')"/>
	<xsl:variable name="document">
		<document
				href="_build.bat"
				method="text"
				encoding="iso-8859-1">
<xsl:text>cd ..
</xsl:text>
	<xsl:value-of select="concat(
		'&#x22;c:\Program Files\7-zip\7z&#x22; a -r -tzip -x!*.zip ',
		'cbear.sourceforge.net/',
		$name, 
		' cbear.sourceforge.net/*')"/>
		</document>
	</xsl:variable>
	<xsl:apply-templates 
		select="exsl:node-set($document)/*" mode="cbear.exslt.common:document"/>
	<xsl:variable name="nightbuild">
		<document href="_nightbuild.html">
			<html>
				<body>
					<a href="{$name}"><xsl:value-of select="$name"/></a>
				</body>
			</html>
		</document>
	</xsl:variable>
	<xsl:apply-templates 
		select="exsl:node-set($nightbuild)/*" mode="cbear.exslt.common:xhtml11"/>
</xsl:template>

</xsl:stylesheet>
