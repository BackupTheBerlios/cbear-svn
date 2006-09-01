<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:H="http://cbear.berlios.de/hex"
	exclude-result-prefixes="H">

	<xsl:import href="sha1.xsl"/>

	<xsl:template name="H:message.debug">
		<xsl:param name="message"/>
		<xsl:param name="i" select="0"/>

		<xsl:if test="string-length($message) &gt; 0">
			<xsl:value-of select="concat(
				'msg[', $i, ']=', substring($message, 1, 8), '&#10;')"/>
			<xsl:call-template name="H:message.debug">
				<xsl:with-param name="message" select="substring($message, 9)"/>
				<xsl:with-param name="i" select="$i + 1"/>
			</xsl:call-template>
		</xsl:if>
	</xsl:template>

	<xsl:template name="H:w.debug">
		<xsl:param name="w"/>
		
		<xsl:if test="string-length($w) &gt; 0">

			<xsl:value-of select="concat(
				'W[', 
				80 - string-length($w) div 8, 
				']=', 
				substring($w, 1, 8), 
				'&#10;')"/>

			<xsl:call-template name="H:w.debug">
				<xsl:with-param name="w" select="substring($w, 9)"/>
			</xsl:call-template>

		</xsl:if>
	</xsl:template>

	<xsl:template name="H:hash.debug">
		<xsl:param name="hash"/>

		<xsl:value-of select="concat(
			'A=', 
			substring($hash, 1, 8),
			' B=', 
			substring($hash, 9, 8),
			' C=', 
			substring($hash, 17, 8),
			' D=', 
			substring($hash, 25, 8),
			' E=', 
			substring($hash, 33, 8),
			'&#10;')"/>
	</xsl:template>

	<xsl:template name="H:next.debug">
		<xsl:param name="w"/>
		<xsl:param name="hash"/>

		<xsl:if test="string-length($w) &gt; 0">

			<xsl:variable name="new">
				<xsl:call-template name="H:sha1.next">
					<xsl:with-param name="w" select="$w"/>
					<xsl:with-param name="hash" select="$hash"/>
				</xsl:call-template>
			</xsl:variable>

			<xsl:value-of select="concat('i=', 80 - string-length($w) div 8, ' ')"/>
			<xsl:call-template name="H:hash.debug">
				<xsl:with-param name="hash" select="$new"/>
			</xsl:call-template>
	
			<!-- -->
			<xsl:call-template name="H:next.debug">
				<xsl:with-param name="w" select="substring($w, 9)"/>
				<xsl:with-param name="hash" select="$new"/>
			</xsl:call-template>

		</xsl:if>
	</xsl:template>

	<xsl:template name="H:chunk.list.debug">
		<xsl:param name="message"/>
		<xsl:param name="i" select="0"/>
		<xsl:param name="hash" select="'67452301efcdab8998badcfe10325476c3d2e1f0'"/>

		<xsl:if test="string-length($message) &gt; 0">

			<xsl:value-of select="concat('Starting block at word ', $i, '&#10;')"/>

			<xsl:variable name="w">
				<xsl:call-template name="H:sha1.extension">
					<xsl:with-param name="data" select="$message"/>
				</xsl:call-template>
			</xsl:variable>

			<xsl:call-template name="H:w.debug">
				<xsl:with-param name="w" select="$w"/>
			</xsl:call-template>

			<xsl:call-template name="H:hash.debug">
				<xsl:with-param name="hash" select="$hash"/>
			</xsl:call-template>

			<xsl:call-template name="H:next.debug">
				<xsl:with-param name="w" select="$w"/>
				<xsl:with-param name="hash" select="$hash"/>
			</xsl:call-template>

			<!-- next chunk -->
			<xsl:call-template name="H:chunk.list.debug">
				<xsl:with-param name="message" select="substring($message, 128 + 1)"/>
				<xsl:with-param name="i" select="$i + 16"/>
			</xsl:call-template>

		</xsl:if>

	</xsl:template>

	<xsl:template match="/">
		<html>
			<body>
				<pre>
					<xsl:variable 
						name="ascii" 
						select="'The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy cog.'"/>
					<xsl:variable name="hex">
						<xsl:call-template name="H:ascii.hex">
							<xsl:with-param name="text" select="$ascii"/>
						</xsl:call-template>
					</xsl:variable>
<!--
					<xsl:variable name="hex.size" select="string-length($hex) div 2"/>
					<xsl:variable name="message">
						<xsl:call-template name="H:sha1.message">
							<xsl:with-param name="source" select="$hex"/>
						</xsl:call-template>
					</xsl:variable>
					<xsl:value-of select="concat(
						'length=', $hex.size, '&#10;')"/>
					<xsl:value-of select="concat(
						'length%4=', 
						$hex.size mod 4, 
						', padding=', 
						substring($message, floor($hex.size div 4) * 8 + 1, 8), 
						'&#10;')"/>
					<xsl:call-template name="H:message.debug">
						<xsl:with-param name="message" select="$message"/>
					</xsl:call-template>
					<xsl:call-template name="H:chunk.list.debug">
						<xsl:with-param name="message" select="$message"/>
					</xsl:call-template>
-->
					<xsl:call-template name="H:sha1">
						<xsl:with-param name="hex" select="$hex"/>
					</xsl:call-template>
				</pre>
			</body>
		</html>
	</xsl:template>

</xsl:stylesheet>
