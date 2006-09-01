<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:H="http://cbear.berlios.de/hex"
	exclude-result-prefixes="H">

	<xsl:variable name="H:dec" select="'0123456789'"/>

	<xsl:variable name="H:lower" select="'abcdef'"/>

	<xsl:variable name="H:hex" select="concat($H:dec, $H:lower)"/>

	<xsl:template name="H:hex1">
		<!-- 0 <= $number < 16 -->
		<xsl:param name="number"/>
		<xsl:choose>
			<xsl:when test="string-length($number) = 1">
				<xsl:value-of select="$number"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of 
					select="translate(substring($number, 2, 1), $H:dec, $H:lower)"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template name="H:hex">
		<!-- 0 <= $number -->
		<xsl:param name="number"/>
		<xsl:if test="$number &gt; 16">
			<xsl:call-template name="H:hex">
				<xsl:with-param name="number" select="floor($number div 16)"/>
			</xsl:call-template>
		</xsl:if>
		<xsl:call-template name="H:hex1">
			<xsl:with-param name="number" select="$number mod 16"/>
		</xsl:call-template>
	</xsl:template>

	<xsl:template name="H:number">
		<!-- $hex in {'0'..'9', 'a'..'f'} -->
		<xsl:param name="hex"/>
		<xsl:choose>
			<xsl:when test="contains($H:dec, $hex)">
				<xsl:value-of select="$hex"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="concat('1', translate($hex, $H:lower, $H:dec))"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template name="H:o2">
		<xsl:param name="a"/>
		<xsl:param name="b"/>
		<xsl:param name="o"/>
		<xsl:variable name="an">
			<xsl:call-template name="H:number">
				<xsl:with-param name="hex" select="$a"/>
			</xsl:call-template>
		</xsl:variable>
		<xsl:value-of select="translate(
			$b, $H:hex, substring($o, $an * 16 + 1, 16))"/>
	</xsl:template>

	<xsl:template name="H:logical">
		<xsl:param name="a"/>
		<xsl:param name="b"/>
		<xsl:param name="o"/>
		<xsl:variable name="a.size" select="string-length($a)"/>
		<xsl:if test="$a.size != string-length($b)">
			<xsl:message terminate="yes">
				<xsl:value-of select="'string-length($a) != string-length($b)'"/>
			</xsl:message>
		</xsl:if>
		<xsl:if test="$a.size &gt; 0">
			<xsl:call-template name="H:o2">
				<xsl:with-param name="a" select="substring($a, 1, 1)"/>
				<xsl:with-param name="b" select="substring($b, 1, 1)"/>
				<xsl:with-param name="o" select="$o"/>
			</xsl:call-template>
			<xsl:call-template name="H:logical">
				<xsl:with-param name="a" select="substring($a, 2, $a.size - 1)"/>
				<xsl:with-param name="b" select="substring($b, 2, $a.size - 1)"/>
				<xsl:with-param name="o" select="$o"/>
			</xsl:call-template>
		</xsl:if>
	</xsl:template>

	<!-- not -->

	<xsl:variable name="H:not" select="'fedcba9876543210'"/>

	<xsl:template name="H:not">
		<xsl:param name="a"/>
		<xsl:value-of select="translate(
			translate($a, $H:upper, $H:lower), $H:hex, $H:not)"/>
	</xsl:template>

	<!-- div -->

	<xsl:variable 
		name="H:div" 
		select="
			'X000000000000000X100000000000000X210000000000000X311000000000000X421100000000000X521110000000000X632111000000000X732111100000000X842211110000000X943211111000000Xa53221111100000Xb53221111110000Xc64322111111000Xd64322111111100Xe74322211111110Xf75332211111111'
			"/>

	<xsl:template name="H:div">
		<xsl:param name="a"/>
		<xsl:param name="b"/>
		<xsl:call-template name="H:o2">
			<xsl:with-param name="a" select="$a"/>
			<xsl:with-param name="b" select="$b"/>
			<xsl:with-param name="o" select="$H:div"/>
		</xsl:call-template>
	</xsl:template>

	<!-- mod -->

	<xsl:variable
		name="H:mod"
		select="
			'X000000000000000X011111111111111X002222222222222X010333333333333X001044444444444X012105555555555X000210666666666X011321077777777X002032108888888X010143210999999X0012043210aaaaaX01231543210bbbbX000020543210cccX0111316543210ddX00224206543210eX010303176543210'
			"/>

	<xsl:template name="H:mod">
		<xsl:param name="a"/>
		<xsl:param name="b"/>
		<xsl:call-template name="H:o2">
			<xsl:with-param name="a" select="$a"/>
			<xsl:with-param name="b" select="$b"/>
			<xsl:with-param name="o" select="$H:mod"/>
		</xsl:call-template>
	</xsl:template>

	<!-- and -->

	<xsl:variable
		name="H:and"
		select="
			'00000000000000000101010101010101002200220022002201230123012301230000444400004444010145450101454500224466002244660123456701234567000000008888888801010101898989890022002288aa88aa0123012389ab89ab000044448888cccc010145458989cdcd0022446688aaccee0123456789abcdef'
			"/>

	<xsl:template name="H:and">
		<xsl:param name="a"/>
		<xsl:param name="b"/>
		<xsl:call-template name="H:logical">
			<xsl:with-param name="a" select="$a"/>
			<xsl:with-param name="b" select="$b"/>
			<xsl:with-param name="o" select="$H:and"/>
		</xsl:call-template>
	</xsl:template>

	<!-- or -->

	<xsl:variable
		name="H:or"
		select="
			'0123456789abcdef1133557799bbddff23236767ababefef33337777bbbbffff45674567cdefcdef55775577ddffddff67676767efefefef77777777ffffffff89abcdef89abcdef99bbddff99bbddffababefefababefefbbbbffffbbbbffffcdefcdefcdefcdefddffddffddffddffefefefefefefefefffffffffffffffff'
			"/>

	<xsl:template name="H:or">
		<xsl:param name="a"/>
		<xsl:param name="b"/>
		<xsl:call-template name="H:logical">
			<xsl:with-param name="a" select="$a"/>
			<xsl:with-param name="b" select="$b"/>
			<xsl:with-param name="o" select="$H:or"/>
		</xsl:call-template>
	</xsl:template>

	<!-- xor -->
	
	<xsl:variable
		name="H:xor"
		select="
			'0123456789abcdef1032547698badcfe23016745ab89efcd32107654ba98fedc45670123cdef89ab54761032dcfe98ba67452301efcdab8976543210fedcba9889abcdef0123456798badcfe10325476ab89efcd23016745ba98fedc32107654cdef89ab45670123dcfe98ba54761032efcdab8967452301fedcba9876543210'
			"/>

	<xsl:template name="H:xor">
		<xsl:param name="a"/>
		<xsl:param name="b"/>
		<xsl:call-template name="H:logical">
			<xsl:with-param name="a" select="$a"/>
			<xsl:with-param name="b" select="$b"/>
			<xsl:with-param name="o" select="$H:xor"/>
		</xsl:call-template>
	</xsl:template>

	<!-- left shift -->

	<xsl:variable 
		name="H:leftshift.low"
		select="'0123456789abcdef02468ace02468ace048c048c048c048c0808080808080808'"/>

	<xsl:variable
		name="H:leftshift.high"
		select="'0000000000000000000000001111111100001111222233330011223344556677'"/>

	<xsl:template name="H:leftshift4">
		<xsl:param name="a"/>
		<!-- 0 <= b	< 4 -->
		<xsl:param name="b"/>

		<xsl:variable name="shift" select="$b * 16 + 1"/>

		<xsl:variable 
			name="high"
			select="translate(
				$a, $H:hex, substring($H:leftshift.high, $shift))"/>
		<xsl:call-template name="H:or">
			<xsl:with-param 
				name="a" 
				select="concat(substring($high, 2), substring($high, 1, 1))"/>
			<xsl:with-param
				name="b" 
				select="translate(
					$a, $H:hex, substring($H:leftshift.low, $shift))"/>
		</xsl:call-template>
	</xsl:template>

	<xsl:template name="H:leftshift">
		<xsl:param name="a"/>
		<xsl:param name="b"/>

		<xsl:choose>
			<xsl:when test="$b &lt; 4">
			 	<xsl:call-template name="H:leftshift4">
					<xsl:with-param name="a" select="$a"/>
					<xsl:with-param name="b" select="$b"/>
				</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>				
				<xsl:variable 
					name="bh" 
					select="floor($b div 4) mod string-length($a)"/>
			 	<xsl:call-template name="H:leftshift4">
					<xsl:with-param 
						name="a" 
						select="concat(substring($a, $bh + 1), substring($a, 1, $bh))"/>
					<xsl:with-param name="b" select="$b mod 4"/>
				</xsl:call-template>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<!-- plus -->

	<!-- 256 + 16 -->
	<xsl:variable 
		name="H:plus"
		select="
			'0123456789abcdef123456789abcdef023456789abcdef013456789abcdef012456789abcdef012356789abcdef012346789abcdef012345789abcdef012345689abcdef012345679abcdef012345678abcdef0123456789bcdef0123456789acdef0123456789abdef0123456789abcef0123456789abcdf0123456789abcde0123456789abcdef'
			"/>

	<!-- 256 + 16 -->
	<xsl:variable
		name="H:plus.high"
		select="
			'00000000000000000000000000000001000000000000001100000000000001110000000000001111000000000001111100000000001111110000000001111111000000001111111100000001111111110000001111111111000001111111111100001111111111110001111111111111001111111111111101111111111111111111111111111111'
			"/>

	<xsl:template name="H:plus.detail">
		<xsl:param name="a"/>
		<xsl:param name="b"/>

		<xsl:choose>
			<xsl:when test="string-length($a) &gt; 0">

				<xsl:variable name="r">
					<xsl:call-template name="H:plus.detail">
						<xsl:with-param name="a" select="substring($a, 2)"/>
						<xsl:with-param name="b" select="substring($b, 2)"/>
					</xsl:call-template>
				</xsl:variable>

				<xsl:variable name="shift" select="substring($r, 1, 1) * 16 + 1"/>
				<xsl:variable name="a1" select="substring($a, 1, 1)"/>
				<xsl:variable name="b1" select="substring($b, 1, 1)"/>

				<xsl:call-template name="H:o2">
					<xsl:with-param name="a" select="$a1"/>
					<xsl:with-param name="b" select="$b1"/>
					<xsl:with-param name="o" select="substring($H:plus.high, $shift)"/>
				</xsl:call-template>
				<xsl:call-template name="H:o2">
					<xsl:with-param name="a" select="$a1"/>
					<xsl:with-param name="b" select="$b1"/>
					<xsl:with-param name="o" select="substring($H:plus, $shift)"/>
				</xsl:call-template>
				<xsl:value-of select="substring($r, 2)"/>

			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="'0'"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template name="H:plus">
		<xsl:param name="a"/>
		<xsl:param name="b"/>

		<xsl:variable name="r">
			<xsl:call-template name="H:plus.detail">
				<xsl:with-param name="a" select="$a"/>
				<xsl:with-param name="b" select="$b"/>
			</xsl:call-template>
		</xsl:variable>

		<xsl:value-of select="substring($r, 2)"/>

	</xsl:template>

	<!-- ascii -->

	<xsl:template name="H:ascii.hex">
		<xsl:param name="text"/>
		<xsl:variable name="size" select="string-length($text)"/>
		<xsl:choose>
			<xsl:when test="$size = 0"/>
			<xsl:when test="$size = 1">
				<xsl:variable 
					name="hex" 
					select="
						document('ascii.xml')/H:set/H:character[@id=$text]/@hex"/>
				<xsl:if test="string-length($hex) != 2">
					<xsl:message terminate="yes">unknown character</xsl:message>
				</xsl:if>
				<xsl:value-of select="$hex"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:variable name="middle" select="floor($size div 2)"/>
				<xsl:call-template name="H:ascii.hex">
					<xsl:with-param name="text" select="substring($text, 1, $middle)"/>
				</xsl:call-template>
				<xsl:call-template name="H:ascii.hex">
					<xsl:with-param 
						name="text" 
						select="substring($text, $middle + 1, $size - $middle)"/>
				</xsl:call-template>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

</xsl:stylesheet>
