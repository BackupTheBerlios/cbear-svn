<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:U="http://cbear.berlios.de/uuid"
	exclude-result-prefixes="U">

	<!-- hex -->

	<xsl:variable name="U:hex" select="'0123456789abcdef'"/>

	<xsl:variable name="U:hex.not" select="'fedcba9876543210'"/>

	<xsl:variable 
		name="U:hex.div" 
		select="
			'X000000000000000X100000000000000X210000000000000X311000000000000X421100000000000X521110000000000X632111000000000X732111100000000X842211110000000X943211111000000Xa53221111100000Xb53221111110000Xc64322111111000Xd64322111111100Xe74322211111110Xf75332211111111'
			"/>

	<xsl:variable
		name="U:hex.mod"
		select="
			'X000000000000000X011111111111111X002222222222222X010333333333333X001044444444444X012105555555555X000210666666666X011321077777777X002032108888888X010143210999999X0012043210aaaaaX01231543210bbbbX000020543210cccX0111316543210ddX00224206543210eX010303176543210'
			"/>

	<xsl:variable
		name="U:hex.and"
		select="
			'00000000000000000101010101010101002200220022002201230123012301230000444400004444010145450101454500224466002244660123456701234567000000008888888801010101898989890022002288aa88aa0123012389ab89ab000044448888cccc010145458989cdcd0022446688aaccee0123456789abcdef'
			"/>

	<xsl:variable
		name="U:hex.or"
		select="
			'0123456789abcdef1133557799bbddff23236767ababefef33337777bbbbffff45674567cdefcdef55775577ddffddff67676767efefefef77777777ffffffff89abcdef89abcdef99bbddff99bbddffababefefababefefbbbbffffbbbbffffcdefcdefcdefcdefddffddffddffddffefefefefefefefefffffffffffffffff'
			"/>
	
	<xsl:variable
		name="U:hex.xor"
		select="
			'0123456789abcdef1032547698badcfe23016745ab89efcd32107654ba98fedc45670123cdef89ab54761032dcfe98ba67452301efcdab8976543210fedcba9889abcdef0123456798badcfe10325476ab89efcd23016745ba98fedc32107654cdef89ab45670123dcfe98ba54761032efcdab8967452301fedcba9876543210'
			"/>

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
				<xsl:value-of select="concat(
					'1', 
					translate(translate($hex, 'ABCDEF', 'abcdef'), 'abcdef', '012345'))"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template name="U:hex.not">
		<xsl:param name="a"/>
		<xsl:value-of select="translate(
			translate($a, 'ABCDEF', 'abcdef'), $U:hex, $U:hex.not)"/>
	</xsl:template>

	<xsl:template name="U:hex.o2">
		<xsl:param name="a"/>
		<xsl:param name="b"/>
		<xsl:param name="o"/>
		<xsl:variable name="an">
			<xsl:call-template name="U:hex.number">
				<xsl:with-param name="hex" select="$a"/>
			</xsl:call-template>
		</xsl:variable>
		<xsl:value-of select="translate(
			translate($b, 'ABCDEF', 'abcdef'), $U:hex, substring($o, $an * 16 + 1, 16))"/>
	</xsl:template>

	<xsl:template name="U:hex.div">
		<xsl:param name="a"/>
		<xsl:param name="b"/>
		<xsl:call-template name="U:hex.o2">
			<xsl:with-param name="a" select="$a"/>
			<xsl:with-param name="b" select="$b"/>
			<xsl:with-param name="o" select="$U:hex.div"/>
		</xsl:call-template>
	</xsl:template>

	<xsl:template name="U:hex.mod">
		<xsl:param name="a"/>
		<xsl:param name="b"/>
		<xsl:call-template name="U:hex.o2">
			<xsl:with-param name="a" select="$a"/>
			<xsl:with-param name="b" select="$b"/>
			<xsl:with-param name="o" select="$U:hex.mod"/>
		</xsl:call-template>
	</xsl:template>

	<xsl:template name="U:hex.and">
		<xsl:param name="a"/>
		<xsl:param name="b"/>
		<xsl:call-template name="U:hex.o2">
			<xsl:with-param name="a" select="$a"/>
			<xsl:with-param name="b" select="$b"/>
			<xsl:with-param name="o" select="$U:hex.and"/>
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

	<!-- clock-seq-and-reserved -->

	<xsl:template name="U:clock-seq-and-reserved.reserved">
		<xsl:param name="clock-seq-and-reserver"/>
		<xsl:call-template name="U:hex.div">
			<xsl:with-param name="a">
				<xsl:call-template name="U:hex.and">
					<xsl:with-param 
						name="a" select="substring($clock-seq-and-reserved, 1, 1)"/>
					<xsl:with-param name="b" select="'c'"/>
				</xsl:call-template>
			</xsl:with-param>
			<xsl:with-param name="b" select="4"/>
		</xsl:call-template>
	</xsl:template>

	<xsl:template name="U:clock-seq-and-reserved.clock-seq-high">
		<xsl:param name="clock-seq-and-reserved"/>
		<xsl:call-template name="U:hex.and">
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
