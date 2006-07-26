<?xml version="1.0" encoding="utf-8"?>
<!--
The MIT License

Copyright (c) 2005 C Bear (http://cbear.berlios.de)

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-->
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:O="http://cbear.berlios.de/windows/com"
	xmlns:D="http://cbear.berlios.de/windows/com/device" 
	xmlns:C="http://cbear.berlios.de/c">

	<xsl:output method="xml"/>

	<xsl:param name="D:cbear"/>

	<xsl:variable 
		name="D:c.id" 
		select="translate(/O:library/@id, '.', '_')"/>

	<!-- interface -->

	<xsl:template match="O:interface" mode="D:interface">
		<xsl:param name="body"/>
		<C:function id="{translate(
			concat(/O:library/@id, '_device_', @id), '.', '_')}">
			<C:id.ref id="int"/>
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
	
	<!-- h -->
	
	<xsl:template match="*" mode="D:h"/>

	<xsl:template match="O:interface" mode="D:h">
		<xsl:apply-templates select="." mode="D:interface"/>
	</xsl:template>

	<!-- c -->
	
	<xsl:template match="*" mode="D:c"/>

	<xsl:template match="O:interface" mode="D:c">
		<xsl:apply-templates select="." mode="D:interface">
			<xsl:with-param name="body">
				<C:body>
					<C:switch>
						<C:id.ref type="*_">
							<C:id.ref id="_in"/>
						</C:id.ref>
						<C:body>
							<C:case>
								<C:id.ref type="const" value="0"/>
							</C:case>
							<C:break/>
						</C:body>
					</C:switch>
				</C:body>
			</xsl:with-param>
		</xsl:apply-templates>
	</xsl:template>
	
	<!-- library -->
		
	<xsl:template match="/O:library">
		<xsl:processing-instruction name="xml-stylesheet">
			<xsl:value-of select="concat(
				'href=&#34;file:///', 
				$D:cbear, 
				'cbear.berlios.de/c/html.xsl&#34; type=&#34;text/xsl&#34;')"/>
		</xsl:processing-instruction>
		<C:unit id="{concat(/O:library/@id, '.device')}">
			<C:h>
				<xsl:apply-templates select="*" mode="D:h"/>
			</C:h>
			<C:c>
				<xsl:apply-templates select="*" mode="D:c"/>
			</C:c>
		</C:unit>
	</xsl:template>

</xsl:stylesheet>
