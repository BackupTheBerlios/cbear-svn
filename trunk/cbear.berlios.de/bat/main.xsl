<?xml version="1.0"?>
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
	xmlns:B="http://cbear.berlios.de/bat">

<xsl:output method="text" encoding="ascii"/>

<xsl:param name="B:log" select="/B:bat/@log"/>
<xsl:param name="B:title" select="/B:bat/@title"/>

<!-- * -->
<xsl:template name="B:tag">
	<xsl:param name="name"/>
	<xsl:param name="attributes"/>
	<xsl:param name="text"/>

	<xsl:call-template name="T:log.line">
		<xsl:with-param 
			name="text" select="concat('^&lt;', $name, ' ', $attributes, '^&gt;')"/>
	</xsl:call-template>
	<xsl:apply-templates select="$text"/>
	<xsl:call-template name="T:log.line">
		<xsl:with-param 
			name="text" select="concat('^&lt;/', $name, '^&gt;')"/>
	</xsl:call-template>
</xsl:template>

<xsl:template match="*">
	<xsl:call-template name="B:tag">
		<xsl:with-param name="name" select="local-name()"/>
		<xsl:with-param name="attributes">
			<xsl:for-each select="@*">
				<xsl:value-of select="concat(' ', local-name(), '=^&#34;', ., '^&#34;')"/>
			</xsl:for-each>
		</xsl:with-param>
		<xsl:with-param name="text">
			<xsl:apply-templates select="*"/>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- B:line -->
<xsl:template name="B:line">
	<xsl:param name="text"/>
	<xsl:value-of select="concat($text, '&#10;')"/>
</xsl:template>

<xsl:template match="B:line">
	<xsl:call-template name="B:line">
		<xsl:with-param name="text" select="@text"/>
	</xsl:call-template>
</xsl:template>

<!-- B:message -->
<xsl:template name="B:message">
	<xsl:param name="text"/>
	<xsl:call-template name="B:line">
		<xsl:with-param name="text" select="concat('echo.', $text)"/>
	</xsl:call-template>
</xsl:template>

<xsl:template match="B:message">
	<xsl:call-template name="B:message">
		<xsl:with-param name="text" select="@text"/>
	</xsl:call-template>
</xsl:template>

<!-- B:log.line -->
<xsl:template name="B:log.line">
	<xsl:param name="text"/>
	<xsl:param name="to" select="'&gt;&gt;'"/>
	<xsl:call-template name="B:message">
		<xsl:with-param name="text" select="concat($text, $to, $B:log)"/>
	</xsl:call-template>
</xsl:template>

<xsl:template match="B:log.line">
	<xsl:call-template name="B:log.line">
		<xsl:with-param name="text" select="@text"/>
	</xsl:call-template>
</xsl:template>

<!-- B:title -->
<xsl:template name="B:title">
	<xsl:param name="text"/>
	<xsl:call-template name="B:line">
		<xsl:with-param name="text" select="concat('title ', $B:title, $text)"/>
	</xsl:call-template>
</xsl:template>

<!-- B:cdata -->
<xsl:template name="B:cdata">
	<xsl:param name="text"/>
	<xsl:call-template name="B:log.line">
		<xsl:with-param name="text" select="'^&lt;![CDATA['"/>
	</xsl:call-template>
	<xsl:value-of select="$text"/>
	<xsl:call-template name="B:log.line">
		<xsl:with-param name="text" select="']]^&gt;'"/>
	</xsl:call-template>
</xsl:template>

<xsl:template match="B:cdata">
	<xsl:call-template name="B:cdata">
		<xsl:with-param name="text">
			<xsl:apply-templates select="*"/>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- B:label.name -->
<xsl:template match="B:label.name">
	<xsl:value-of select="concat('n', count(preceding::*))"/>
</xsl:template>

<!-- B:label -->
<xsl:template name="B:label">
	<xsl:param name="name"/>
	<xsl:call-template name="B:line">
		<xsl:with-param name="text" select="concat(':', $name)"/>
	</xsl:call-template>	
</xsl:template>

<!-- B:goto -->
<xsl:template name="B:goto">
	<xsl:param name="label"/>
	<xsl:call-template name="B:line">
		<xsl:with-param name="text" select="concat('goto ', $label)"/>
	</xsl:call-template>
</xsl:template>

<!-- B:if.not.goto -->
<xsl:template name="B:if.not.goto">
	<xsl:param name="test"/>
	<xsl:param name="label"/>
	<xsl:call-template name="B:line">
		<xsl:with-param name="text" select="concat('if not ', $test, ' goto ', $label)"/>
	</xsl:call-template>
</xsl:template>

<!-- B:if -->
<xsl:template name="B:if">
	<xsl:param name="test"/>
	<xsl:param name="text"/>
	<xsl:param name="end"/>

	<xsl:call-template name="B:if.not.goto">
		<xsl:with-param name="test" select="$test"/>
		<xsl:with-param name="label" select="$end"/>
	</xsl:call-template>
	<xsl:value-of select="$text"/>
	<xsl:call-template name="B:label">	
		<xsl:with-param name="name" select="$end"/>
	</xsl:call-template>
</xsl:template>

<xsl:template match="B:if">
	<xsl:call-template name="B:if">
		<xsl:with-param name="test" select="@test"/>
		<xsl:with-param name="text">
			<xsl:apply-templates select="*"/>
		</xsl:with-param>
		<xsl:with-param name="end">
			<xsl:call-template name="B:label.name"/>
		</xsl:with-param>
	</xsl:call-template>
</xsl:template>

<!-- B:when -->
<xsl:template name="B:when">
	<xsl:param name="test"/>
	<xsl:param name="text"/>
	<xsl:param name="end"/>
	<xsl:param name="choose.end"/>

	<xsl:call-template name="B:if">
		<xsl:with-param name="test" select="$test"/>
		<xsl:with-param name="text">
			<xsl:value-of select="$text"/>
			<xsl:call-template name="B:goto">
				<xsl:with-param name="label" select="$choose.end"/>
			</xsl:call-template>
		</xsl:with-param>
		<xsl:with-param name="end" select="$end"/>		
	</xsl:call-template>
</xsl:template>

<!-- B:choose -->
<xsl:template name="B:choose">
	<xsl:param name="when.list"/>
	<xsl:param name="otherwise"/>
	<xsl:param name="end"/>

	<xsl:value-of select="when.list"/>
	<xsl:value-of select="otherwise"/>
	<xsl:call-template name="B:label">
		<xsl:with-param name="name" select="$end"/>
	</xsl:call-template>
</xsl:template>

<xsl:template match="B:choose">
	<xsl:variable name="choose.end">
		<xsl:call-template name="B:label.name"/>
	</xsl:variable>
	<xsl:call-template name="B:choose">
		<xsl:with-param name="when.list">
			<xsl:for-each select="when">
				<xsl:call-template name="B:when">
					<xsl:with-param name="test" select="@test"/>
					<xsl:with-param name="text">
						<xsl:apply-templates select="*"/>
					</xsl:with-param>
					<xsl:with-param name="end">
						<xsl:call-template name="B:label.name"/>
					</xsl:with-param>
					<xsl:with-param name="choose.end" select="$choose.end"/>
				</xsl:call-template>
			</xsl:for-each>
		</xsl:with-param>
		<xsl:with-param name="otherwise">
			<xsl:apply-templates select="*"/>
		</xsl:with-param>
		<xsl:with-param name="end" select="$choose.end"/>
	</xsl:call-template>
</xsl:template>

<!-- B:command -->
<xsl:template match="B:command">

	<xsl:call-template name="B:title">
		<xsl:with-param 
			name="text" 
			select="concat(' ', count(preceding::B:command))"/>
	</xsl:call-template>

	<xsl:call-template name="B:message">
		<xsl:with-param name="text" select="@name"/>
	</xsl:call-template>

	<xsl:variable 
		name="attributes" select="'xmlns=^&#34;http://cbear.berlios.de/bat^&#34;'"/>

	<xsl:call-template name="B:tag">
		<xsl:with-param name="name" select="'command'"/>
		<xsl:with-param name="attributes" select="$attributes"/>
		<xsl:with-param name="text">

			<xsl:call-template name="B:tag">
				<xsl:with-param name="name" select="'output'"/>				
				<xsl:with-param name="attributes" select="$attributes"/>
				<xsl:with-param name="text">
					<xsl:call-template name="B:cdata">
						<xsl:with-param name="text">	
							<xsl:call-template name="B:line">
								<xsl:with-param name="text" select="
									concat(@text, '&gt;&gt;', $B:log, ' 2&gt;&amp;1')"/>
							</xsl:call-template>
						</xsl:with-param>
					</xsl:call-template>
				</xsl:with-param>
			</xsl:call-template>

			<xsl:call-template name="B:tag">
				<xsl:with-param name="name" select="'errorlevel'"/>
				<xsl:with-param 
					name="attributes" 
					select="concat($attributes, ' value=^&#34;%errorlevel%^&#34;',)"/>
			</xsl:call-template>

			<xsl:variable name="choose.end">
				<xsl:call-template name="B:label.name"/>
			</xsl:variable>
			<xsl:call-template name="B:choose">
				<xsl:with-param name="when.list">
					<xsl:call-template name="B:when">
						<xsl:with-param name="test" select="'%errorlevel% == 0'"/>
						<xsl:with-param name="text">
							<xsl:call-template name="B:message">
								<xsl:with-param name="text" select="'ok'"/>
							</xsl:call-template>
						</xsl:with-param>
						<xsl:with-param name="end" select="concat($choose.end, 'ok')"/>
						<xsl:with-param name="choose.end" select="$choose.end"/>
					</xsl:call-template>
				</xsl:with-param>
				<xsl:with-param name="otherwise">
					<xsl:call-template name="B:message">
						<xsl:with-param name="text" select="'failed'"/>
					</xsl:call-template>
				</xsl:with-param>
				<xsl:with-param name="choose.end" select="$choose.end"/>
			</xsl:call-template>

		</xsl:with-param>
	</xsl:call-template>

</xsl:template>

<!-- B:bat -->
<xsl:template match="B:bat">
	<xsl:call-template name="B:line">
		<xsl:with-param name="text" select="'@echo off'"/>
	</xsl:call-template>
	<xsl:call-template name="B:title"/>
	<xsl:apply-templates select="*"/>
</xsl:template>

</xsl:stylesheet>
