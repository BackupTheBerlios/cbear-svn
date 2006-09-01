<?xml version="1.0" encoding="utf-8"?>
<!-- XHTML 1.1. -->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:H="http://cbear.berlios.de/hex"
	exclude-result-prefixes="H">

	<xsl:import href="main.xsl"/>

	<!-- sha1 -->

	<xsl:template name="H:fill">
		<xsl:param name="number"/>
		<xsl:param name="text"/>
		<xsl:if test="$number &gt; 0">
			<xsl:value-of select="$text"/>
			<xsl:call-template name="H:fill">
				<xsl:with-param name="number" select="$number - 1"/>
				<xsl:with-param name="text" select="$text"/>
			</xsl:call-template>
		</xsl:if>
	</xsl:template>

	<xsl:template name="H:sha1.extension">
		<xsl:param name="data"/>
		<!-- [16, 80) words = [128, 640) hexs -->
		<xsl:param name="i" select="128"/>
		<xsl:choose>
			<xsl:when test="$i &lt; 640">
				<xsl:call-template name="H:sha1.extension">
					<xsl:with-param name="data">
						<xsl:value-of select="$data"/>
						<xsl:call-template name="H:leftshift">
							<xsl:with-param name="a">
								<xsl:call-template name="H:xor">
									<xsl:with-param name="a">
										<xsl:call-template name="H:xor">
											<!-- i - 3 words = i - 24 hexs -->
											<xsl:with-param 
												name="a" select="substring($data, $i - 23, 8)"/>
											<!-- i - 8 words = i - 64 hexs -->
											<xsl:with-param 
												name="b" select="substring($data, $i - 63, 8)"/>
										</xsl:call-template>
									</xsl:with-param>
									<xsl:with-param name="b">
										<xsl:call-template name="H:xor">
											<!-- i - 14 words = i - 112 hexs -->
											<xsl:with-param 
												name="a" select="substring($data, $i - 111, 8)"/>
											<!-- i - 16 words = i - 128 hexs -->
											<xsl:with-param 
												name="b" select="substring($data, $i - 127, 8)"/>
										</xsl:call-template>
									</xsl:with-param>
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="b" select="1"/>
						</xsl:call-template>
					</xsl:with-param>
					<xsl:with-param name="i" select="$i + 8"/>
				</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="$data"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template name="H:sha1.next">
		<xsl:param name="w"/>
		<xsl:param name="hash"/>

		<xsl:variable name="a" select="substring($hash,  1, 8)"/>
		<xsl:variable name="b" select="substring($hash,  9, 8)"/>
		<xsl:variable name="c" select="substring($hash, 17, 8)"/>
		<xsl:variable name="d" select="substring($hash, 25, 8)"/>
		<xsl:variable name="e" select="substring($hash, 33, 8)"/>

		<xsl:variable name="size" select="string-length($w)"/>

		<xsl:variable name="fk">
			<xsl:choose>

				<!-- i < 20 words => size > (640 - 20 * 8) = 480 -->
				<xsl:when test="$size &gt; 480">
					<xsl:call-template name="H:xor">
						<xsl:with-param name="a" select="$d"/>
						<xsl:with-param name="b">
							<xsl:call-template name="H:and">
								<xsl:with-param name="a" select="$b"/>
								<xsl:with-param name="b">
									<xsl:call-template name="H:xor">
										<xsl:with-param name="a" select="$c"/>
										<xsl:with-param name="b" select="$d"/>
									</xsl:call-template>
								</xsl:with-param>
							</xsl:call-template>
						</xsl:with-param>
					</xsl:call-template>
					<xsl:value-of select="'5a827999'"/>
				</xsl:when>

				<!-- i < 40 words => size > (640 - 40 * 8) = 320 -->
				<xsl:when test="$size &gt; 320">
					<xsl:call-template name="H:xor">
						<xsl:with-param name="a">
							<xsl:call-template name="H:xor">
								<xsl:with-param name="a" select="$b"/>
								<xsl:with-param name="b" select="$c"/>
							</xsl:call-template>
						</xsl:with-param>
						<xsl:with-param name="b" select="$d"/>
					</xsl:call-template>
					<xsl:value-of select="'6ed9eba1'"/>
				</xsl:when>

				<!-- i < 60 words => size > (640 - 60 * 8) = 160 -->
				<xsl:when test="$size &gt; 160">
					<xsl:call-template name="H:or">
						<xsl:with-param name="a">
							<xsl:call-template name="H:and">
								<xsl:with-param name="a" select="$b"/>
								<xsl:with-param name="b" select="$c"/>
							</xsl:call-template>
						</xsl:with-param>
						<xsl:with-param name="b">
							<xsl:call-template name="H:and">
								<xsl:with-param name="a" select="$d"/>
								<xsl:with-param name="b">
									<xsl:call-template name="H:or">
										<xsl:with-param name="a" select="$b"/>
										<xsl:with-param name="b" select="$c"/>
									</xsl:call-template>
								</xsl:with-param>
							</xsl:call-template>
						</xsl:with-param>
					</xsl:call-template>
					<xsl:value-of select="'8f1bbcdc'"/>
				</xsl:when>

				<!-- i < 80 words => size > 0 -->
				<xsl:otherwise>
					<xsl:call-template name="H:xor">
						<xsl:with-param name="a">
							<xsl:call-template name="H:xor">
								<xsl:with-param name="a" select="$b"/>
								<xsl:with-param name="b" select="$c"/>
							</xsl:call-template>
						</xsl:with-param>
						<xsl:with-param name="b" select="$d"/>
					</xsl:call-template>
					<xsl:value-of select="'ca62c1d6'"/>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>

		<!-- a -->
		<xsl:call-template name="H:plus">
			<xsl:with-param name="a">
				<xsl:call-template name="H:leftshift">
					<xsl:with-param name="a" select="$a"/>
				<xsl:with-param name="b" select="5"/>
				</xsl:call-template>
			</xsl:with-param>
			<xsl:with-param name="b">
				<xsl:call-template name="H:plus">
					<xsl:with-param name="a">
						<xsl:call-template name="H:plus">
							<xsl:with-param name="a" select="substring($fk, 1, 8)"/>
							<xsl:with-param name="b" select="substring($fk, 9)"/>
						</xsl:call-template>
					</xsl:with-param>
					<xsl:with-param name="b">
						<xsl:call-template name="H:plus">
							<xsl:with-param name="a" select="$e"/>
							<xsl:with-param name="b" select="substring($w, 1, 8)"/>
						</xsl:call-template>	
					</xsl:with-param>
				</xsl:call-template>
			</xsl:with-param>
		</xsl:call-template>
		<!-- b = a -->
		<xsl:value-of select="$a"/>
		<!-- c = b << 30 -->
		<xsl:call-template name="H:leftshift">
			<xsl:with-param name="a" select="$b"/>
			<xsl:with-param name="b" select="30"/>
		</xsl:call-template>
		<!-- d = c -->
		<xsl:value-of select="$c"/>
		<!-- e = d -->
		<xsl:value-of select="$d"/>
	
	</xsl:template>

	<xsl:template name="H:sha1.main">
		<xsl:param name="w"/>
		<xsl:param name="hash"/>
		<xsl:variable name="size" select="string-length($w)"/>
		<xsl:choose>
			<xsl:when test="$size &gt; 0">
				<xsl:call-template name="H:sha1.main">
					<xsl:with-param name="w" select="substring($w, 9)"/>
					<xsl:with-param name="hash">
						<xsl:variable name="a" select="substring($hash,  1, 8)"/>
						<xsl:variable name="b" select="substring($hash,  9, 8)"/>
						<xsl:variable name="c" select="substring($hash, 17, 8)"/>
						<xsl:variable name="d" select="substring($hash, 25, 8)"/>
						<xsl:variable name="e" select="substring($hash, 33, 8)"/>
						<xsl:variable name="fk">
							<xsl:choose>
								<!-- i < 20 words => size > (640 - 20 * 8) = 480 -->
								<xsl:when test="$size &gt; 480">
									<xsl:call-template name="H:xor">
										<xsl:with-param name="a" select="$d"/>
										<xsl:with-param name="b">
											<xsl:call-template name="H:and">
												<xsl:with-param name="a" select="$b"/>
												<xsl:with-param name="b">
													<xsl:call-template name="H:xor">
														<xsl:with-param name="a" select="$c"/>
														<xsl:with-param name="b" select="$d"/>
													</xsl:call-template>
												</xsl:with-param>
											</xsl:call-template>
										</xsl:with-param>
									</xsl:call-template>
									<xsl:value-of select="'5a827999'"/>
								</xsl:when>
								<!-- i < 40 words => size > (640 - 40 * 8) = 320 -->
								<xsl:when test="$size &gt; 320">
									<xsl:call-template name="H:xor">
										<xsl:with-param name="a">
											<xsl:call-template name="H:xor">
												<xsl:with-param name="a" select="$b"/>
												<xsl:with-param name="b" select="$c"/>
											</xsl:call-template>
										</xsl:with-param>
										<xsl:with-param name="b" select="$d"/>
									</xsl:call-template>
									<xsl:value-of select="'6ed9eba1'"/>
								</xsl:when>
								<!-- i < 60 words => size > (640 - 60 * 8) = 160 -->
								<xsl:when test="$size &gt; 160">
									<xsl:call-template name="H:or">
										<xsl:with-param name="a">
											<xsl:call-template name="H:and">
												<xsl:with-param name="a" select="$b"/>
												<xsl:with-param name="b" select="$c"/>
											</xsl:call-template>
										</xsl:with-param>
										<xsl:with-param name="b">
											<xsl:call-template name="H:and">
												<xsl:with-param name="a" select="$d"/>
												<xsl:with-param name="b">
													<xsl:call-template name="H:or">
														<xsl:with-param name="a" select="$b"/>
														<xsl:with-param name="b" select="$c"/>
													</xsl:call-template>
												</xsl:with-param>
											</xsl:call-template>
										</xsl:with-param>
									</xsl:call-template>
									<xsl:value-of select="'8f1bbcdc'"/>
								</xsl:when>
								<!-- i < 80 words => size > 0 -->
								<xsl:otherwise>
									<xsl:call-template name="H:xor">
										<xsl:with-param name="a">
											<xsl:call-template name="H:xor">
												<xsl:with-param name="a" select="$b"/>
												<xsl:with-param name="b" select="$c"/>
											</xsl:call-template>
										</xsl:with-param>
										<xsl:with-param name="b" select="$d"/>
									</xsl:call-template>
									<xsl:value-of select="'ca62c1d6'"/>
								</xsl:otherwise>
							</xsl:choose>
						</xsl:variable>

						<!-- a -->
						<xsl:call-template name="H:plus">
							<xsl:with-param name="a">
								<xsl:call-template name="H:leftshift">
									<xsl:with-param name="a" select="$a"/>
									<xsl:with-param name="b" select="5"/>
								</xsl:call-template>
							</xsl:with-param>
							<xsl:with-param name="b">
								<xsl:call-template name="H:plus">
									<xsl:with-param name="a">
										<xsl:call-template name="H:plus">
											<xsl:with-param name="a" select="substring($fk, 1, 8)"/>
											<xsl:with-param name="b" select="substring($fk, 9)"/>
										</xsl:call-template>
									</xsl:with-param>
									<xsl:with-param name="b">
										<xsl:call-template name="H:plus">
											<xsl:with-param name="a" select="$e"/>
											<xsl:with-param name="b" select="substring($w, 1, 8)"/>
										</xsl:call-template>	
									</xsl:with-param>
								</xsl:call-template>
							</xsl:with-param>
						</xsl:call-template>
						<!-- b = a -->
						<xsl:value-of select="$a"/>
						<!-- c = b << 30 -->
						<xsl:call-template name="H:leftshift">
							<xsl:with-param name="a" select="$b"/>
							<xsl:with-param name="b" select="30"/>
						</xsl:call-template>
						<!-- d = c -->
						<xsl:value-of select="$c"/>
						<!-- e = d -->
						<xsl:value-of select="$d"/>

					</xsl:with-param>
				</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="$hash"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template name="H:sha1.chunk">
		<xsl:param name="data"/>
		<!-- 160 bits = 40 hexs         1234567890123456789012345678901234567890 -->
		<xsl:param name="hash" select="'67452301efcdab8998badcfe10325476c3d2e1f0'"/>

		<xsl:choose>
			<xsl:when test="string-length($data) &gt; 0">
				<xsl:call-template name="H:sha1.chunk">
					<xsl:with-param name="data" select="substring($data, 129, 128)"/>
					<xsl:with-param name="hash">
						<xsl:variable name="abcde">
							<xsl:call-template name="H:sha1.main">
								<xsl:with-param name="w">
									<xsl:call-template name="H:sha1.extension">
										<xsl:with-param name="data" select="substring($data, 1, 128)"/>
									</xsl:call-template>
								</xsl:with-param>
								<xsl:with-param name="hash" select="$hash"/>
							</xsl:call-template>
						</xsl:variable>
						<xsl:call-template name="H:plus">
							<xsl:with-param name="a" select="substring($hash, 1, 8)"/>
							<xsl:with-param name="b" select="substring($abcde, 1, 8)"/>
						</xsl:call-template>
						<xsl:call-template name="H:plus">
							<xsl:with-param name="a" select="substring($hash, 9, 8)"/>
							<xsl:with-param name="b" select="substring($abcde, 9, 8)"/>
						</xsl:call-template>
						<xsl:call-template name="H:plus">
							<xsl:with-param name="a" select="substring($hash, 17, 8)"/>
							<xsl:with-param name="b" select="substring($abcde, 17, 8)"/>
						</xsl:call-template>
						<xsl:call-template name="H:plus">
							<xsl:with-param name="a" select="substring($hash, 25, 8)"/>
							<xsl:with-param name="b" select="substring($abcde, 25, 8)"/>
						</xsl:call-template>
						<xsl:call-template name="H:plus">
							<xsl:with-param name="a" select="substring($hash, 33, 8)"/>
							<xsl:with-param name="b" select="substring($abcde, 33, 8)"/>
						</xsl:call-template>
					</xsl:with-param>
				</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="$hash"/>
			</xsl:otherwise>
		</xsl:choose> 
	</xsl:template>

	<xsl:template name="H:sha1.message">
		<xsl:param name="source"/>

		<!-- source.size [hex] -->
		<xsl:variable name="source.size" select="string-length($source)"/>
		<!-- chunk: 512 bits = 128 hexs -->
		<!-- end of data: 64 + 4 bits = 17 hexs -->
		<!-- 17 + 128 - 1 hexs = 144 hexs -->
		<xsl:variable 
			name="size" select="floor(($source.size + 144) div 128) * 128"/>
		<xsl:variable name="end">
			<xsl:call-template name="H:hex">
				<xsl:with-param name="number" select="$source.size * 4"/>
			</xsl:call-template>
		</xsl:variable>
		<xsl:value-of select="concat($source, '8')"/>
		<xsl:call-template name="H:fill">
			<xsl:with-param 
				name="number" 
				select="$size - $source.size - 1 - string-length($end)"/>
			<xsl:with-param name="text" select="'0'"/>
		</xsl:call-template>
		<xsl:value-of select="$end"/>
	</xsl:template>

	<xsl:template name="H:sha1">
		<xsl:param name="hex"/>

		<xsl:variable name="size" select="string-length($hex)"/>
		<!-- chunk: 512 bits = 128 hexs -->
		<!-- end of data: 64 + 4 bits = 17 hexs -->
		<!-- 17 + 128 - 1 hexs = 144 hexs -->
		<xsl:variable 
			name="data.size" select="floor(($size + 144) div 128) * 128"/>

		<xsl:variable name="end">
			<xsl:call-template name="H:hex">
				<xsl:with-param name="number" select="$size * 4"/>
			</xsl:call-template>
		</xsl:variable>

		<xsl:call-template name="H:sha1.chunk">
			<xsl:with-param name="data">
				<xsl:value-of select="concat($hex, '8')"/>
				<xsl:call-template name="H:fill">
					<xsl:with-param 
						name="number" 
						select="$data.size - $size - 1 - string-length($end)"/>
					<xsl:with-param name="text" select="'0'"/>
				</xsl:call-template>
				<xsl:value-of select="$end"/>
			</xsl:with-param>
		</xsl:call-template>

	</xsl:template>

</xsl:stylesheet>
