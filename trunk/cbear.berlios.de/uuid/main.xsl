<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:U="http://cbear.berlios.de/uuid"
	exclude-result-prefixes="U">

	<!-- hex -->

	<xsl:template name="U:hex">
		<!-- 0 <= $number < 16 -->
		<xsl:param name="number"/>
		<xsl:choose>
			<xsl:when test="string-length($number) = 1">
				<xsl:value-of select="$number"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of 
					select="translate(substring($number, 2, 1), '012345', 'abcdef')"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template name="U:hex.number">
		<!-- $hex in {'0'..'9', 'A'..'F', 'a'..'f'} -->
		<xsl:param name="hex"/>
		<xsl:choose>
			<xsl:when test="contains('0123456789', $hex)">
				<xsl:value-of select="$hex"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="
					concat('1', translate($hex, 'ABCDEFabcdef', '012345012345'))"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template name="U:hex.div">
		<xsl:param name="a"/>
		<xsl:param name="b"/>

		<xsl:variable name="an">
			<xsl:call-template name="U:hex.number">
				<xsl:with-param name="hex" select="$a"/>
			</xsl:call-template>
		</xsl:variable>
		<xsl:variable name="bn">
			<xsl:call-template name="U:hex.number">
				<xsl:with-param name="hex" select="$b"/>
			</xsl:call-template>
		</xsl:variable>

		<xsl:call-template name="U:hex">
			<xsl:with-param 
				name="number" 
				select="floor($an div $bn)"/>
		</xsl:call-template>

	</xsl:template>

	<xsl:template name="U:hex.and">
		<xsl:param name="a"/>
		<xsl:param name="b"/>

		<xsl:variable name="an">
			<xsl:call-template name="U:hex.number">
				<xsl:with-param name="hex" select="$a"/>
			</xsl:call-template>
		</xsl:variable>
		<xsl:variable name="bn">
			<xsl:call-template name="U:hex.number">
				<xsl:with-param name="hex" select="$b"/>
			</xsl:call-template>
		</xsl:variable>

		<xsl:call-template name="U:hex">
			<xsl:with-param 
				name="number" 
				select="
					($an       - $an mod 8) * ($bn       - $bn mod 8) div 8 +
					($an mod 8 - $an mod 4) * ($bn mod 8 - $bn mod 4) div 4 +
					($an mod 4 - $an mod 2) * ($bn mod 4 - $bn mod 2) div 2 +
					($an mod 2            ) * ($bn mod 2            )"/>
		</xsl:call-template>

	</xsl:template>

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

	<!-- reserved -->

</xsl:stylesheet>
