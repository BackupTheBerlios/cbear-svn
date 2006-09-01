<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:U="http://cbear.berlios.de/uuid"
	exclude-result-prefixes="U">

	<xsl:import href="main.xsl"/>

	<xsl:template match="/">
		<html>
			<body>
				<xsl:variable name="uuid">
					<xsl:call-template name="U:uuid">
						<xsl:with-param name="time-low" select="'c45a5909'"/>
						<xsl:with-param name="time-mid" select="'4166'"/>
						<xsl:with-param name="time-high-and-version" select="'4d51'"/>
						<xsl:with-param name="clock-seq-and-reserved" select="'9a'"/>
						<xsl:with-param name="clock-seq-low" select="'90'"/>
						<xsl:with-param name="node" select="'834af3938f50'"/>
					</xsl:call-template>
				</xsl:variable>

				<h1>UUID</h1>
				<ul>
					<li>UUID = <xsl:value-of select="$uuid"/></li>
					<li>
						time-low = 
						<xsl:call-template name="U:uuid.time-low">
							<xsl:with-param name="uuid" select="$uuid"/>
						</xsl:call-template>
					</li>
					<li>
						time-mid = 
						<xsl:call-template name="U:uuid.time-mid">
							<xsl:with-param name="uuid" select="$uuid"/>
						</xsl:call-template>
					</li>
					<li>
						<xsl:variable name="time-high-and-version">
							<xsl:call-template name="U:uuid.time-high-and-version">
								<xsl:with-param name="uuid" select="$uuid"/>
							</xsl:call-template>				
						</xsl:variable>
						time-high-and-version = <xsl:value-of select="$time-high-and-version"/>
						<ul>
							<li>
								time-high = 
								<xsl:call-template name="U:time-high-and-version.time-high">
									<xsl:with-param 
										name="time-high-and-version" 
										select="$time-high-and-version"/>
								</xsl:call-template>
							</li>
							<li>
								version = 
								<xsl:call-template name="U:time-high-and-version.version">
									<xsl:with-param 
										name="time-high-and-version" 
										select="$time-high-and-version"/>
								</xsl:call-template>
							</li>
						</ul>
					</li>
					<li>
						<xsl:variable name="clock-seq-and-reserved">
							<xsl:call-template name="U:uuid.clock-seq-and-reserved">
								<xsl:with-param name="uuid" select="$uuid"/>
							</xsl:call-template>
						</xsl:variable>
						clock-seq-and-reserved = 
						<xsl:value-of select="$clock-seq-and-reserved"/>
						<ul>
							<li>
								reserved =
								<xsl:call-template name="U:clock-seq-and-reserved.reserved">
									<xsl:with-param 
										name="clock-seq-and-reserved" 
										select="$clock-seq-and-reserved"/>
								</xsl:call-template>					
							</li>
							<li>
								clock-seq-high =
								<xsl:call-template name="U:clock-seq-and-reserved.clock-seq-high">
									<xsl:with-param 
										name="clock-seq-and-reserved" 
										select="$clock-seq-and-reserved"/>
								</xsl:call-template>					
							</li>
						</ul>
					</li>
					<li>
						clock-seq-low = 
						<xsl:call-template name="U:uuid.clock-seq-low">
							<xsl:with-param name="uuid" select="$uuid"/>
						</xsl:call-template>
					</li>
					<li>
						node = 
						<xsl:call-template name="U:uuid.node">
							<xsl:with-param name="uuid" select="$uuid"/>
						</xsl:call-template>
					</li>
				</ul>
				<h1>Others</h1>
				<ul>
					<li>
						timestamp =
						<xsl:call-template name="U:uuid.timestamp">
							<xsl:with-param name="uuid" select="$uuid"/>
						</xsl:call-template>
					</li>
					<li>
						clock-seq =
						<xsl:call-template name="U:uuid.clock-seq">
							<xsl:with-param name="uuid" select="$uuid"/>
						</xsl:call-template>
					</li>
				</ul>
			</body>
		</html>
	</xsl:template>

</xsl:stylesheet>
