<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:U="http://cbear.berlios.de/uuid"
	exclude-result-prefixes="U">

	<xsl:import href="main.xsl"/>

	<xsl:template name="U:hex.test">
		<xsl:param name="hex"/>
		<xsl:variable name="number">
			<xsl:call-template name="U:hex.number">
				<xsl:with-param name="hex" select="$hex"/>
			</xsl:call-template>
		</xsl:variable>
		<xsl:variable name="hex.new">
			<xsl:call-template name="U:hex">
				<xsl:with-param name="number" select="$number"/>
			</xsl:call-template>
		</xsl:variable>
		<li>
			<xsl:value-of select="concat(
				'hex.number(', 
				$hex, 
				')=', 
				$number, 
				', hex(', 
				$number, 
				')=', 
				$hex.new)"/>
		</li>
	</xsl:template>

	<xsl:template name="U:hex.div.test">
		<xsl:param name="ab"/>
		<li>
			<xsl:value-of select="concat(
				'hex.div(', substring($ab, 1, 1), ',', substring($ab, 2, 1), ')=')"/>
			<xsl:call-template name="U:hex.div">
				<xsl:with-param name="a" select="substring($ab, 1, 1)"/>
				<xsl:with-param name="b" select="substring($ab, 2, 1)"/>
			</xsl:call-template>
		</li>
	</xsl:template>

	<xsl:template name="U:hex.and.test">
		<xsl:param name="ab"/>
		<li>
			<xsl:value-of select="concat(
				'hex.and(', substring($ab, 1, 1), ',', substring($ab, 2, 1), ')=')"/>
			<xsl:call-template name="U:hex.and">
				<xsl:with-param name="a" select="substring($ab, 1, 1)"/>
				<xsl:with-param name="b" select="substring($ab, 2, 1)"/>
			</xsl:call-template>
		</li>
	</xsl:template>

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
				<h1>Hex</h1>
				<ul>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="0"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="1"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="2"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="3"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="4"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="5"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="6"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="7"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="8"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="9"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="'A'"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="'B'"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="'C'"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="'D'"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="'E'"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="'F'"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="'a'"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="'b'"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="'c'"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="'d'"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="'e'"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.test">
						<xsl:with-param name="hex" select="'f'"/>
					</xsl:call-template>
				</ul>
				<h1>Hex Div</h1>
				<ul>
					<xsl:call-template name="U:hex.div.test">
						<xsl:with-param name="ab" select="'a3'"/>
					</xsl:call-template>
				</ul>
				<h1>Hex And</h1>
				<ul>
					<xsl:call-template name="U:hex.and.test">
						<xsl:with-param name="ab" select="'00'"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.and.test">
						<xsl:with-param name="ab" select="'01'"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.and.test">
						<xsl:with-param name="ab" select="'11'"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.and.test">
						<xsl:with-param name="ab" select="'21'"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.and.test">
						<xsl:with-param name="ab" select="'3e'"/>
					</xsl:call-template>
					<xsl:call-template name="U:hex.and.test">
						<xsl:with-param name="ab" select="'f5'"/>
					</xsl:call-template>
				</ul>
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
						clock-seq-and-reserved = 
						<xsl:call-template name="U:uuid.clock-seq-and-reserved">
							<xsl:with-param name="uuid" select="$uuid"/>
						</xsl:call-template>
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
				</ul>
			</body>
		</html>
	</xsl:template>

</xsl:stylesheet>
