<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:U="http://cbear.berlios.de/uuid"
	xmlns:H="http://cbear.berlios.de/hex"
	exclude-result-prefixes="U H">

	<xsl:import href="../hex/main.xsl"/>

	<!-- uuid -->

	<xsl:template name="U:uuid">
		<!-- 0123, 12345678 -->
		<xsl:param name="time-low"/>
		<!-- 45, 9 0123 -->
		<xsl:param name="time-mid"/>
		<!-- 67, 4 5678 -->
		<xsl:param name="time-high-and-version"/>
		<!-- 8, 9 01 -->
		<xsl:param name="clock-seq-and-reserved"/>
		<!-- 9, 23 -->
		<xsl:param name="clock-seq-low"/>
		<!-- 012345, 4 567890123456 -->
		<xsl:param name="node"/>

		<xsl:value-of select="concat(
			$time-low, '-', 
			$time-mid, '-', 
			$time-high-and-version, '-',
			$clock-seq-and-reserved,
			$clock-seq-low, '-', 
			$node)"/>
	</xsl:template>

	<xsl:template name="U:uuid.time-low">
		<xsl:param name="uuid"/>
		<xsl:value-of select="substring($uuid, 1, 8)"/>
	</xsl:template>

	<xsl:template name="U:uuid.time-mid">
		<xsl:param name="uuid"/>
		<!-- offset = 8 + 1 = 9 -->
		<xsl:value-of select="substring($uuid, 10, 4)"/>
	</xsl:template>

	<xsl:template name="U:uuid.time-high-and-version">
		<xsl:param name="uuid"/>
		<!-- offset = 8 + 1 + 4 + 1 = 14 -->
		<xsl:value-of select="substring($uuid, 15, 4)"/>
	</xsl:template>

	<xsl:template name="U:uuid.clock-seq-and-reserved">
		<xsl:param name="uuid"/>
		<!-- offset = 8 + 1 + 4 + 1 + 4 + 1 = 19 -->
		<xsl:value-of select="substring($uuid, 20, 2)"/>
	</xsl:template>

	<xsl:template name="U:uuid.clock-seq-low">
		<xsl:param name="uuid"/>
		<!-- offset = 8 + 1 + 4 + 1 + 4 + 1 + 2 = 21 -->
		<xsl:value-of select="substring($uuid, 22, 2)"/>
	</xsl:template>

	<xsl:template name="U:uuid.node">
		<xsl:param name="uuid"/>
		<!-- offset = 8 + 1 + 4 + 1 + 4 + 1 + 2 + 2 + 1 = 24 -->
		<xsl:value-of select="substring($uuid, 25, 12)"/>
	</xsl:template>

	<!-- time-high-and-version -->

	<xsl:template name="U:time-high-and-version">
		<xsl:param name="time-high"/>
		<xsl:param name="version"/>
		<xsl:value-of select="concat($time-high, $version)"/>
	</xsl:template>

	<xsl:template name="U:time-high-and-version.time-high">
		<xsl:param name="time-high-and-version"/>
		<xsl:value-of select="substring($time-high-and-version, 2, 3)"/>
	</xsl:template>

	<xsl:template name="U:time-high-and-version.version">
		<xsl:param name="time-high-and-version"/>
		<xsl:value-of select="substring($time-high-and-version, 1, 1)"/>
	</xsl:template>

	<!-- timestamp -->

	<xsl:template name="U:uuid.timestamp">
		<xsl:param name="uuid"/>
		<xsl:call-template name="U:uuid.time-low">
			<xsl:with-param name="uuid" select="$uuid"/>
		</xsl:call-template>
		<xsl:call-template name="U:uuid.time-mid">
			<xsl:with-param name="uuid" select="$uuid"/>
		</xsl:call-template>
		<xsl:call-template name="U:time-high-and-version.time-high">
			<xsl:with-param name="time-high-and-version">
				<xsl:call-template name="U:uuid.time-high-and-version">
					<xsl:with-param name="uuid" select="$uuid"/>
				</xsl:call-template>
			</xsl:with-param>
		</xsl:call-template>
	</xsl:template>

	<!-- clock-seq-and-reserved -->

	<xsl:template name="U:clock-seq-and-reserved.reserved">
		<xsl:param name="clock-seq-and-reserved"/>
		<xsl:call-template name="H:div">
			<xsl:with-param name="a">

				<xsl:call-template name="H:and">
					<xsl:with-param 
						name="a" select="substring($clock-seq-and-reserved, 1, 1)"/>
					<xsl:with-param name="b" select="'c'"/>
				</xsl:call-template>

			</xsl:with-param>
			<xsl:with-param name="b" select="'4'"/>
		</xsl:call-template>
	</xsl:template>

	<xsl:template name="U:clock-seq-and-reserved.clock-seq-high">
		<xsl:param name="clock-seq-and-reserved"/>
		<xsl:call-template name="H:and">
			<xsl:with-param 
				name="a" select="substring($clock-seq-and-reserved, 1, 1)"/>
			<xsl:with-param name="b" select="'3'"/>
		</xsl:call-template>
		<xsl:value-of select="substring($clock-seq-and-reserved, 2, 1)"/>
	</xsl:template>

	<!-- clock-seq -->

	<xsl:template name="U:uuid.clock-seq">
		<xsl:param name="uuid"/>
		<xsl:call-template name="U:clock-seq-and-reserved.clock-seq-high">
			<xsl:with-param name="clock-seq-and-reserved">
				<xsl:call-template name="U:uuid.clock-seq-and-reserved">
					<xsl:with-param name="uuid" select="$uuid"/>
				</xsl:call-template>
			</xsl:with-param>
		</xsl:call-template>
		<xsl:call-template name="U:uuid.clock-seq-low">
			<xsl:with-param name="uuid" select="$uuid"/>
		</xsl:call-template>
	</xsl:template>

</xsl:stylesheet>
