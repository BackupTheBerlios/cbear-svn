<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:R="http://cbear.berlios.de/remote"
	xmlns:C="http://cbear.berlios.de/c">

	<xsl:output method="xml"/>

	<xsl:param name="R:cbear"/>

	<xsl:variable name="R:command.begin" select="2"/>

	<!-- coclass -->

	<xsl:template match="R:coclass" mode="C:id">
		<xsl:value-of select="concat(
			translate(/R:library/@id, '.', '_'), '_remote_', @id)"/>
	</xsl:template>

	<xsl:template match="R:coclass">
		<xsl:param name="body"/>
		<xsl:variable name="id">
			<xsl:apply-templates select="." mode="C:id"/>
		</xsl:variable>
		<C:function id="{$id}">
			<C:id.ref id="void"/>
			<C:parameter id="_command">
				<C:id.ref id="char"/>
			</C:parameter>
			<C:parameter id="_in">
				<C:id.ref type="_*">
					<C:id.ref id="char"/>
				</C:id.ref>
			</C:parameter>
			<C:parameter id="_out">
				<C:id.ref type="_*">
					<C:id.ref id="char"/>
				</C:id.ref>
			</C:parameter>
			<xsl:copy-of select="$body"/>
		</C:function>
	</xsl:template>

	<!-- uuid -->

	<xsl:template name="R:uuid">
		<xsl:param name="text" select="@uuid"/>
		<xsl:if test="string($text)!=''">
			<xsl:choose>
				<xsl:when test="substring($text, 1, 1)='-'">
					<xsl:call-template name="R:uuid">
						<xsl:with-param 
							name="text" 
							select="substring($text, 2)"/>
					</xsl:call-template>
				</xsl:when>
				<xsl:otherwise>
					<C:id.ref 
						type="const" value="{concat('0x', substring($text, 1, 2))}"/>
					<xsl:call-template name="R:uuid">
						<xsl:with-param 
							name="text" 
							select="substring($text, 3)"/>
					</xsl:call-template>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:if>
	</xsl:template>

	<!-- method -->

	<xsl:template name="R:method.count">
		<xsl:value-of select="
			$R:command.begin + 
			count(preceding::R:method[
				ancestor::R:coclass/@id = current()/ancestor::R:coclass/@id])"/>
	</xsl:template>

	<!-- library -->

	<xsl:template match="/R:library">
		<xsl:processing-instruction name="xml-stylesheet">
			<xsl:value-of select="concat(
				'href=&#34;file:///', 
				$R:cbear, 
				'cbear.berlios.de/c/html.xsl&#34; type=&#34;text/xsl&#34;')"/>
		</xsl:processing-instruction>
		<C:unit id="{concat(@id, '.remote')}">
			<C:h>
				<xsl:apply-templates select="R:*"/>
			</C:h>
			<C:c>
				<C:include href="cbear.berlios.de/remote/uuid.h"/>
				<C:include href="cbear.berlios.de/remote/command1_out.h"/>
				<xsl:for-each select="R:coclass">
					<xsl:variable name="id">
						<xsl:apply-templates select="." mode="C:id"/>
					</xsl:variable>
					<xsl:variable name="command1-out" select="concat($id, '_command1_out')"/>
					<xsl:variable name="interface.count" select="count(.//R:interface)"/>
					<C:exp>
						<C:id.ref type=" ">
							<C:id.ref id="cbear_berlios_de_remote_command1_out"/>
							<C:id.ref type="=">
								<C:id.ref type="[]">
									<C:id.ref id="{$command1-out}"/>
									<C:id.ref type="const" value="{$interface.count}"/>
								</C:id.ref>
								<C:id.ref type="{'{}'}">
									<xsl:for-each select=".//R:interface">
										<C:id.ref type="{'{}'}">
											<C:id.ref type="{'{}'}">
												<xsl:call-template name="R:uuid"/>
											</C:id.ref>
											<xsl:variable name="method.count">
												<xsl:call-template name="R:method.count"/>
											</xsl:variable>
											<C:id.ref type="const" value="{$method.count}"/>
										</C:id.ref>
									</xsl:for-each>
								</C:id.ref>
							</C:id.ref>
						</C:id.ref>
					</C:exp>
					<xsl:apply-templates select=".">
						<xsl:with-param name="body">
							<C:body>
								<C:switch>
									<C:id.ref id="_command"/>
									<C:body>
										<!-- 0 -->
										<C:case>
											<C:id.ref type="const" value="0"/>
										</C:case>
										<C:exp>
											<C:id.ref type="=">
												<C:id.ref type="[]">
													<C:id.ref id="_out"/>
													<C:id.ref type="const" value="0"/>
												</C:id.ref>
												<C:id.ref type="const" value="{$interface.count}"/>
											</C:id.ref>
										</C:exp>
										<C:break/>
										<!-- 1 -->
										<C:case>
											<C:id.ref type="const" value="1"/>
										</C:case>
										<C:exp>
											<C:id.ref type="=">
												<C:id.ref type="*_">
													<C:id.ref type="()_">
														<C:id.ref type="_*">
															<C:id.ref id="cbear_berlios_de_remote_command1_out"/>
														</C:id.ref>
														<C:id.ref id="_out"/>
													</C:id.ref>
												</C:id.ref>
												<C:id.ref type="[]">
													<C:id.ref id="{$command1-out}"/>
													<C:id.ref type="[]">
														<C:id.ref id="_in"/>
														<C:id.ref type="const" value="0"/>
													</C:id.ref>
												</C:id.ref>
											</C:id.ref>
										</C:exp>
										<C:break/>
										<!-- method -->
										<xsl:for-each select=".//R:method">
											<C:case>
												<xsl:variable name="method.count">
													<xsl:call-template name="R:method.count"/>
												</xsl:variable>
												<C:id.ref type="const" value="{$method.count}"/>
											</C:case>
											<C:break/>
										</xsl:for-each>
									</C:body>
								</C:switch>
							</C:body>
						</xsl:with-param>
					</xsl:apply-templates>
				</xsl:for-each>
			</C:c>
		</C:unit>
	</xsl:template>

</xsl:stylesheet>
