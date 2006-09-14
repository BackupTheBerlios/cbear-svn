<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:H="http://cbear.berlios.de/hex"
	exclude-result-prefixes="H">

	<xsl:import href="main.xsl"/>

	<xsl:template name="H:hex.test">
		<xsl:param name="hex"/>
		<xsl:variable name="number">
			<xsl:call-template name="H:number">
				<xsl:with-param name="hex" select="$hex"/>
			</xsl:call-template>
		</xsl:variable>
		<xsl:variable name="hex.new">
			<xsl:call-template name="H:hex">
				<xsl:with-param name="number" select="$number"/>
			</xsl:call-template>
		</xsl:variable>
		<li>
			<xsl:value-of select="concat(
				'number(', 
				$hex, 
				')=', 
				$number, 
				', hex(', 
				$number, 
				')=', 
				$hex.new)"/>
		</li>
	</xsl:template>

	<xsl:template name="H:div.test">
		<xsl:param name="ab"/>
		<li>
			<xsl:value-of select="concat(
				'div(', substring($ab, 1, 1), ',', substring($ab, 2, 1), ')=')"/>
			<xsl:call-template name="H:div">
				<xsl:with-param name="a" select="substring($ab, 1, 1)"/>
				<xsl:with-param name="b" select="substring($ab, 2, 1)"/>
			</xsl:call-template>
		</li>
	</xsl:template>

	<xsl:template name="H:and.test">
		<xsl:param name="ab"/>
		<li>
			<xsl:value-of select="concat(
				'and(', substring($ab, 1, 1), ',', substring($ab, 2, 1), ')=')"/>
			<xsl:call-template name="H:and">
				<xsl:with-param name="a" select="substring($ab, 1, 1)"/>
				<xsl:with-param name="b" select="substring($ab, 2, 1)"/>
			</xsl:call-template>
		</li>
	</xsl:template>

	<xsl:template name="H:xor.test">
		<xsl:param name="a"/>
		<xsl:param name="b"/>
		<li>
			<xsl:value-of select="concat('xor(', $a, ',', $b, ')=')"/>
			<xsl:call-template name="H:xor">
				<xsl:with-param name="a" select="$a"/>
				<xsl:with-param name="b" select="$b"/>
			</xsl:call-template>
		</li>
	</xsl:template>

	<xsl:template name="H:leftshift.test">
		<xsl:param name="a"/>
		<xsl:param name="b"/>
		<li>
			<xsl:value-of select="concat('leftshift(', $a, ',', $b, ')=')"/>
			<xsl:call-template name="H:leftshift">
				<xsl:with-param name="a" select="$a"/>
				<xsl:with-param name="b" select="$b"/>
			</xsl:call-template>
		</li>
	</xsl:template>

	<xsl:template name="H:plus.test">
		<xsl:param name="a"/>
		<xsl:param name="b"/>
		<li>
			<xsl:value-of select="concat('plus(', $a, ',', $b, ')=')"/>
			<xsl:call-template name="H:plus">
				<xsl:with-param name="a" select="$a"/>
				<xsl:with-param name="b" select="$b"/>
			</xsl:call-template>
		</li>
	</xsl:template>

	<xsl:template match="/">
		<html>
			<body>
				<h1>Hex</h1>
				<ul>
					<xsl:call-template name="H:hex.test">
						<xsl:with-param name="hex" select="0"/>
					</xsl:call-template>
					<xsl:call-template name="H:hex.test">
						<xsl:with-param name="hex" select="1"/>
					</xsl:call-template>
					<xsl:call-template name="H:hex.test">
						<xsl:with-param name="hex" select="2"/>
					</xsl:call-template>
					<xsl:call-template name="H:hex.test">
						<xsl:with-param name="hex" select="3"/>
					</xsl:call-template>
					<xsl:call-template name="H:hex.test">
						<xsl:with-param name="hex" select="4"/>
					</xsl:call-template>
					<xsl:call-template name="H:hex.test">
						<xsl:with-param name="hex" select="5"/>
					</xsl:call-template>
					<xsl:call-template name="H:hex.test">
						<xsl:with-param name="hex" select="6"/>
					</xsl:call-template>
					<xsl:call-template name="H:hex.test">
						<xsl:with-param name="hex" select="7"/>
					</xsl:call-template>
					<xsl:call-template name="H:hex.test">
						<xsl:with-param name="hex" select="8"/>
					</xsl:call-template>
					<xsl:call-template name="H:hex.test">
						<xsl:with-param name="hex" select="9"/>
					</xsl:call-template>
					<xsl:call-template name="H:hex.test">
						<xsl:with-param name="hex" select="'a'"/>
					</xsl:call-template>
					<xsl:call-template name="H:hex.test">
						<xsl:with-param name="hex" select="'b'"/>
					</xsl:call-template>
					<xsl:call-template name="H:hex.test">
						<xsl:with-param name="hex" select="'c'"/>
					</xsl:call-template>
					<xsl:call-template name="H:hex.test">
						<xsl:with-param name="hex" select="'d'"/>
					</xsl:call-template>
					<xsl:call-template name="H:hex.test">
						<xsl:with-param name="hex" select="'e'"/>
					</xsl:call-template>
					<xsl:call-template name="H:hex.test">
						<xsl:with-param name="hex" select="'f'"/>
					</xsl:call-template>
				</ul>
				<h1>Div</h1>
				<ul>
					<xsl:call-template name="H:div.test">
						<xsl:with-param name="ab" select="'a3'"/>
					</xsl:call-template>
				</ul>
				<h1>And</h1>
				<ul>
					<xsl:call-template name="H:and.test">
						<xsl:with-param name="ab" select="'00'"/>
					</xsl:call-template>
					<xsl:call-template name="H:and.test">
						<xsl:with-param name="ab" select="'01'"/>
					</xsl:call-template>
					<xsl:call-template name="H:and.test">
						<xsl:with-param name="ab" select="'11'"/>
					</xsl:call-template>
					<xsl:call-template name="H:and.test">
						<xsl:with-param name="ab" select="'21'"/>
					</xsl:call-template>
					<xsl:call-template name="H:and.test">
						<xsl:with-param name="ab" select="'3e'"/>
					</xsl:call-template>
					<xsl:call-template name="H:and.test">
						<xsl:with-param name="ab" select="'f5'"/>
					</xsl:call-template>
					<xsl:call-template name="H:and.test">
						<xsl:with-param name="ab" select="'93'"/>
					</xsl:call-template>
					<xsl:call-template name="H:and.test">
						<xsl:with-param name="ab" select="'ea'"/>
					</xsl:call-template>
				</ul>
				<h1>Xor</h1>
				<ul>
					<xsl:call-template name="H:xor.test">
						<xsl:with-param name="a" select="'00'"/>
						<xsl:with-param name="b" select="'12'"/>
					</xsl:call-template>
					<xsl:call-template name="H:xor.test">
						<xsl:with-param name="a" select="'01'"/>
						<xsl:with-param name="b" select="'23'"/>
					</xsl:call-template>
					<xsl:call-template name="H:xor.test">
						<xsl:with-param name="a" select="'11'"/>
						<xsl:with-param name="b" select="'45'"/>
					</xsl:call-template>
					<xsl:call-template name="H:xor.test">
						<xsl:with-param name="a" select="'21'"/>
						<xsl:with-param name="b" select="'67'"/>
					</xsl:call-template>
					<xsl:call-template name="H:xor.test">
						<xsl:with-param name="a" select="'3e'"/>
						<xsl:with-param name="b" select="'89'"/>
					</xsl:call-template>
					<xsl:call-template name="H:xor.test">
						<xsl:with-param name="a" select="'f5'"/>
						<xsl:with-param name="b" select="'ab'"/>
					</xsl:call-template>
					<xsl:call-template name="H:xor.test">
						<xsl:with-param name="a" select="'93'"/>
						<xsl:with-param name="b" select="'cd'"/>
					</xsl:call-template>
				</ul>
				<h1>Left Shift</h1>
				<ul>
					<xsl:call-template name="H:leftshift.test">
						<xsl:with-param name="a" select="'00'"/>
						<xsl:with-param name="b" select="0"/>
					</xsl:call-template>
					<xsl:call-template name="H:leftshift.test">
						<xsl:with-param name="a" select="'01'"/>
						<xsl:with-param name="b" select="1"/>
					</xsl:call-template>
					<xsl:call-template name="H:leftshift.test">
						<xsl:with-param name="a" select="'11'"/>
						<xsl:with-param name="b" select="2"/>
					</xsl:call-template>
					<xsl:call-template name="H:leftshift.test">
						<xsl:with-param name="a" select="'21'"/>
						<xsl:with-param name="b" select="3"/>
					</xsl:call-template>
					<xsl:call-template name="H:leftshift.test">
						<xsl:with-param name="a" select="'3e'"/>
						<xsl:with-param name="b" select="0"/>
					</xsl:call-template>
					<xsl:call-template name="H:leftshift.test">
						<xsl:with-param name="a" select="'f5'"/>
						<xsl:with-param name="b" select="1"/>
					</xsl:call-template>
					<xsl:call-template name="H:leftshift.test">
						<xsl:with-param name="a" select="'93'"/>
						<xsl:with-param name="b" select="2"/>
					</xsl:call-template>
					<xsl:call-template name="H:leftshift.test">
						<xsl:with-param name="a" select="'1a'"/>
						<xsl:with-param name="b" select="8"/>
					</xsl:call-template>
					<xsl:call-template name="H:leftshift.test">
						<xsl:with-param name="a" select="'1a'"/>
						<xsl:with-param name="b" select="9"/>
					</xsl:call-template>
				</ul>
				<h1>Plus</h1>
				<ul>
					<xsl:call-template name="H:plus.test">
						<xsl:with-param name="a" select="'00'"/>
						<xsl:with-param name="b" select="'12'"/>
					</xsl:call-template>
					<xsl:call-template name="H:plus.test">
						<xsl:with-param name="a" select="'01'"/>
						<xsl:with-param name="b" select="'23'"/>
					</xsl:call-template>
					<xsl:call-template name="H:plus.test">
						<xsl:with-param name="a" select="'11'"/>
						<xsl:with-param name="b" select="'45'"/>
					</xsl:call-template>
					<xsl:call-template name="H:plus.test">
						<xsl:with-param name="a" select="'21'"/>
						<xsl:with-param name="b" select="'67'"/>
					</xsl:call-template>
					<xsl:call-template name="H:plus.test">
						<xsl:with-param name="a" select="'3e'"/>
						<xsl:with-param name="b" select="'89'"/>
					</xsl:call-template>
					<xsl:call-template name="H:plus.test">
						<xsl:with-param name="a" select="'f5'"/>
						<xsl:with-param name="b" select="'ab'"/>
					</xsl:call-template>
					<xsl:call-template name="H:plus.test">
						<xsl:with-param name="a" select="'93'"/>
						<xsl:with-param name="b" select="'cd'"/>
					</xsl:call-template>
				</ul>
				<h1>ASCII</h1>
				<xsl:variable 
					name="ascii" 
					select="'The quick brown fox jumps over the lazy dog'"/>
				<xsl:variable name="hex">
					<xsl:call-template name="H:ascii.hex">
						<xsl:with-param name="text" select="$ascii"/>
					</xsl:call-template>
				</xsl:variable>
				<xsl:value-of select="concat($ascii, ' = ', $hex)"/>
				<br/>
				<xsl:value-of select="string-length($hex)"/>
			</body>
		</html>
	</xsl:template>

</xsl:stylesheet>
