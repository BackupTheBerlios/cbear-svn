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
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:api="http://cbear.berlios.de/api"
	xmlns:exsl="http://exslt.org/common"
	xmlns="http://cbear.berlios.de/windows/com"
	xmlns:odl="http://cbear.berlios.de/windows/com"
	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	extension-element-prefixes="exsl"
	exclude-result-prefixes="xi api odl">

<xsl:output method="xml" indent="yes"/>

<xsl:param name="api:com.odl.xsd"/>
<xsl:param name="api:com.odl.xsl"/>
<xsl:param name="api:com.odl.prefix"/>

<!-- -->

<xsl:template match="@*" mode="api:body"/>

<xsl:template match="*" mode="api:body">
	<xsl:copy-of select="."/>
</xsl:template>

<xsl:template match="api:*" mode="api:body">
	<xsl:element 
		namespace="http://cbear.berlios.de/windows/com"
		name="{local-name()}">
		<xsl:apply-templates select="@id" mode="api:body"/>
		<xsl:apply-templates select="@uuid" mode="api:body"/>
		<xsl:apply-templates select="api:comment" mode="api:body.comment"/>
		<xsl:apply-templates select="*" mode="api:body"/>
	</xsl:element>
</xsl:template>

<!-- comment -->

<xsl:template match="api:comment" mode="api:body"/>

<xsl:template match="api:comment" mode="api:body.comment">
	<comment><xsl:copy-of select="*|text()"/></comment>
</xsl:template>

<!-- @id -->

<xsl:template match="@id" mode="api:com.odl.id">
	<xsl:value-of select="translate(., './', '__')"/>
</xsl:template>

<xsl:template match="@id" mode="api:body">	
	<xsl:attribute name="id">
		<xsl:apply-templates select="." mode="api:com.odl.id"/>
	</xsl:attribute>
</xsl:template>

<xsl:template match="@id[../api:pragma/odl:alias]" mode="api:body"/>

<xsl:template match="@id[../api:pragma/odl:alias/@id]" mode="api:body">
	<xsl:attribute name="id">
		<xsl:value-of select="../api:pragma/odl:alias/@id"/>
	</xsl:attribute>
</xsl:template>

<!-- @brief -->

<xsl:template match="@brief" mode="api:body">
	<attribute id="helpstring" value="{concat('&#x22;', ., '&#x22;')}"/>
</xsl:template>

<!-- @uuid -->

<xsl:template match="@uuid" mode="api:body">
	<attribute id="uuid" value="{.}"/>
</xsl:template>

<!-- @version -->

<xsl:template match="@version" mode="api:body">
	<attribute id="version" value="{.}"/>
</xsl:template>

<!-- pragma -->

<xsl:template match="api:pragma" mode="api:body"/>

<xsl:template match="api:pragma" mode="api:body.pragma">
	<xsl:copy-of select="odl:attribute"/>
</xsl:template>

<!-- const -->

<xsl:template match="api:const" mode="api:body">
	<const value="{@value}"/>
</xsl:template>

<!-- type.ref -->

<xsl:template match="*" mode="api:body.type.ref">
	<xsl:param name="content"/>
	<xsl:param name="library"/>
	<type.ref>
		<xsl:if test="$library">
			<xsl:attribute name="library">
				<xsl:value-of select="$library"/>
			</xsl:attribute>
		</xsl:if>
		<xsl:apply-templates select="@id" mode="api:body"/>
		<xsl:copy-of select="$content"/>
	</type.ref>
</xsl:template>

<xsl:template match="api:type" mode="api:body.type.ref">
	<xsl:param name="content"/>
	<xsl:param name="library"/>
	<type.ref>
		<xsl:apply-templates select="@id" mode="api:body"/>	
		<xsl:copy-of select="$content"/>
	</type.ref>
</xsl:template>

<xsl:template match="api:interface" mode="api:body.type.ref">
	<xsl:param name="library"/>
	<type.ref id="*">
		<type.ref>
			<xsl:if test="$library">
				<xsl:attribute name="library">
					<xsl:value-of select="$library"/>
				</xsl:attribute>
			</xsl:if>
			<xsl:apply-templates select="@id" mode="api:body"/>
		</type.ref>
	</type.ref>
</xsl:template>

<xsl:template match="/api:library" mode="api:body.type.ref.library">
	<xsl:value-of select="@id"/>	
</xsl:template>

<xsl:template 
	match="/api:library[api:pragma/odl:alias/@id]" 
	mode="api:body.type.ref.library">
	<xsl:value-of select="api:pragma/odl:alias/@id"/>	
</xsl:template>

<xsl:template match="/api:library" mode="api:body.type.ref">
	<xsl:param name="id"/>
	<xsl:param name="content"/>
	<xsl:param name="library"/>
	<xsl:apply-templates select="*[@id=$id]" mode="api:body.type.ref">
		<xsl:with-param name="content" select="$content"/>
		<xsl:with-param name="library" select="$library"/>
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="api:type.ref" mode="api:body.type.ref">
	<xsl:apply-templates select="/api:library" mode="api:body.type.ref">
		<xsl:with-param name="id" select="@id"/>
		<xsl:with-param name="content">
			<xsl:apply-templates select="*" mode="api:body"/>
		</xsl:with-param>
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="api:type.ref[@library]" mode="api:body.type.ref">
	<xsl:variable name="library" select="@library"/>
	<xsl:apply-templates 
		select="document(/api:library/api:using[@id=$library]/@href)/api:library"
		mode="api:body.type.ref">
		<xsl:with-param name="id" select="@id"/>
		<xsl:with-param name="content">
			<xsl:apply-templates select="*" mode="api:body"/>
		</xsl:with-param>
		<xsl:with-param name="library">
			<xsl:apply-templates 
				select="document(/api:library/api:using[@id=$library]/@href)/api:library" 
				mode="api:body.type.ref.library"/>
		</xsl:with-param>
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="api:type.ref" mode="api:body">
	<xsl:apply-templates select="." mode="api:body.type.ref"/>
</xsl:template>

<!-- method -->

<xsl:template match="api:in|api:out" mode="api:body">
	<attribute id="{local-name()}"/>
</xsl:template>

<xsl:template name="api:method.header">
	<xsl:apply-templates select="@brief" mode="api:body"/>
	<xsl:apply-templates select="api:pragma" mode="api:body.pragma"/>
	<xsl:apply-templates select="api:comment" mode="api:body.comment"/>
	<type.ref id="HRESULT"/>
</xsl:template>

<xsl:template match="api:type.ref" mode="api:body.result">
	<parameter id="_result">
		<attribute id="retval"/>
		<attribute id="out"/>
		<type.ref id="*">
			<xsl:apply-templates select="." mode="api:body.type.ref"/>
		</type.ref>
	</parameter>
</xsl:template>

<xsl:template match="api:parameter/api:type.ref[../api:out]" mode="api:body">
	<type.ref id="*">
		<xsl:apply-templates select="." mode="api:body.type.ref"/>
	</type.ref>
</xsl:template>

<xsl:template match="api:parameter" mode="api:body">
	<parameter id="{concat('_', count(preceding-sibling::api:parameter))}">
		<xsl:apply-templates select="*" mode="api:body"/>
	</parameter>
</xsl:template>

<xsl:template match="api:method" mode="api:body">
	<method>
		<xsl:apply-templates select="@id" mode="api:body"/>
		<xsl:call-template name="api:method.header"/>
		<xsl:apply-templates select="api:parameter" mode="api:body"/>
		<xsl:apply-templates select="api:type.ref" mode="api:body.result"/>
	</method>
</xsl:template>

<!-- property -->

<xsl:template match="api:property" mode="api:body.property.item"/>

<xsl:template match="api:property[api:parameter]" mode="api:body.property.item">
	<xsl:if test="not(api:pragma/odl:attribute[@id='id'])">
		<attribute id="id" value="0"/>
	</xsl:if>
</xsl:template>

<xsl:template match="api:get" mode="api:body">
	<xsl:for-each select="..">
		<method>
			<xsl:apply-templates select="@id" mode="api:body"/>
			<attribute id="propget"/>
			<xsl:apply-templates select="." mode="api:body.property.item"/>
			<xsl:call-template name="api:method.header"/>
			<xsl:apply-templates select="api:parameter" mode="api:body"/>
			<xsl:apply-templates select="api:type.ref" mode="api:body.result"/>
		</method>
	</xsl:for-each>
</xsl:template>

<xsl:template match="api:set" mode="api:body">
	<xsl:for-each select="..">
		<method>
			<xsl:apply-templates select="@id" mode="api:body"/>
			<attribute id="propput"/>
			<xsl:apply-templates select="." mode="api:body.property.item"/>
			<xsl:call-template name="api:method.header"/>
			<xsl:apply-templates select="api:parameter" mode="api:body"/>
			<parameter id="_value">
				<attribute id="in"/>
				<xsl:apply-templates select="api:type.ref" mode="api:body.type.ref"/>
			</parameter>
		</method>
	</xsl:for-each>
</xsl:template>

<xsl:template match="api:property" mode="api:body">
	<xsl:apply-templates select="api:get|api:set" mode="api:body"/>
</xsl:template>

<!-- interface -->

<xsl:template match="api:interface/api:type.ref" mode="api:body">
	<xsl:variable name="type.ref">
		<xsl:apply-templates select="." mode="api:body.type.ref"/>
	</xsl:variable>
	<method id="{exsl:node-set($type.ref)/odl:type.ref/odl:type.ref/@id}">
		<attribute id="propget"/>
		<xsl:call-template name="api:method.header"/>
		<xsl:apply-templates select="." mode="api:body.result"/>
	</method>
</xsl:template>

<xsl:template 
	match="api:interface/api:type.ref[count(preceding-sibling::api:type.ref)=0]"
	mode="api:body">
	<xsl:variable name="type">
		<xsl:apply-templates select="." mode="api:body.type.ref"/>
	</xsl:variable>
	<xsl:copy-of select="exsl:node-set($type)/odl:type.ref/odl:type.ref"/>
</xsl:template>

<xsl:template match="api:interface" mode="api:body.dual"/>

<xsl:template match="api:interface[api:type.ref]" mode="api:body.dual">
	<xsl:variable name="id" select="api:type.ref/@id"/>
	<xsl:apply-templates 
		select="/api:library/api:interface[@id=$id]" mode="api:body.dual"/>
</xsl:template>

<xsl:template match="api:interface[api:type.ref/@library]" mode="api:body.dual">
	<xsl:variable name="library" select="api:type.ref/@library"/>
	<xsl:variable name="id" select="api:type.ref/@id"/>
	<xsl:apply-templates
		select="document(/api:library/api:using[@id=$library]/@href)/api:library/
			api:interface[@id=$id]"
		mode="api:body.dual"/>
</xsl:template>

<xsl:template 
	match="api:interface[api:pragma/odl:alias/@id='IDispatch']" 
	mode="api:body.dual">
	<attribute id="dual"/>
</xsl:template>

<xsl:template match="api:interface" mode="api:body">
	<interface>
		<xsl:apply-templates select="@id" mode="api:body"/>
		<xsl:apply-templates select="@uuid" mode="api:body"/>
		<xsl:apply-templates select="@brief" mode="api:body"/>
		<xsl:apply-templates select="." mode="api:body.dual"/>
		<attribute id="oleautomation"/>
		<xsl:apply-templates select="api:pragma" mode="api:body.pragma"/>
		<xsl:apply-templates select="api:comment" mode="api:body.comment"/>
		<xsl:if test="not(api:type.ref)">
			<type.ref library="stdole" id="IUnknown"/>
		</xsl:if>
		<xsl:apply-templates select="*" mode="api:body"/>
	</interface>
</xsl:template>

<!-- typedef -->

<xsl:template match="*" mode="api:body.typedef"/>

<xsl:template match="api:struct" mode="api:body.typedef">
	<struct>
		<xsl:apply-templates select="@id" mode="api:body"/>
		<xsl:apply-templates select="@uuid" mode="api:body"/>
		<xsl:apply-templates select="@brief" mode="api:body"/>
		<xsl:apply-templates select="api:comment" mode="api:body.comment"/>
		<xsl:apply-templates select="*" mode="api:body"/>
	</struct>
</xsl:template>

<xsl:template match="api:enum" mode="api:body.typedef">
	<enum>
		<xsl:apply-templates select="@id" mode="api:body"/>
		<xsl:apply-templates select="@uuid" mode="api:body"/>
		<xsl:apply-templates select="@brief" mode="api:body"/>
		<xsl:apply-templates select="api:comment" mode="api:body.comment"/>
		<xsl:apply-templates select="*" mode="api:body"/>
	</enum>
</xsl:template>

<xsl:template match="api:struct|api:enum" mode="api:body">
	<typedef>
		<xsl:apply-templates select="@id" mode="api:body"/>
		<xsl:apply-templates select="." mode="api:body.typedef"/>
	</typedef>
</xsl:template>

<!--
<xsl:template match="api:struct" mode="api:body">
	<xsl:apply-templates select="." mode="api:body.typedef"/>
</xsl:template>
-->

<!-- object -->

<xsl:template match="api:library/api:object" mode="api:body">
	<coclass>
		<xsl:apply-templates select="@id" mode="api:body"/>
		<xsl:apply-templates select="@uuid" mode="api:body"/>
		<xsl:apply-templates select="@brief" mode="api:body"/>
		<attribute id="appobject"/>
		<xsl:apply-templates select="api:pragma" mode="api:body.pragma"/>
		<xsl:apply-templates select="api:comment" mode="api:body.comment"/>
		<xsl:variable name="type.ref">
			<xsl:apply-templates select="api:type.ref" mode="api:body.type.ref"/>
		</xsl:variable>
		<type.ref id="{exsl:node-set($type.ref)/odl:type.ref/odl:type.ref/@id}">
			<attribute id="default"/>
		</type.ref>
	</coclass>
</xsl:template>

<!-- using -->

<xsl:template match="api:library" mode="api:body.filename">
	<xsl:value-of select="concat(@id, '.tlb')"/>
</xsl:template>

<xsl:template 
	match="api:library[api:pragma/odl:alias/@filename]" mode="api:body.filename">
	<xsl:value-of select="api:pragma/odl:alias/@filename"/>
</xsl:template>

<xsl:template match="api:using" mode="api:body">
	<xsl:variable name="file">
		<xsl:apply-templates 
			select="document(@href)/api:library" mode="api:body.filename"/>
	</xsl:variable>
	<importlib href="{$file}"/>
</xsl:template>

<!-- library -->

<xsl:template match="api:library" mode="api:body">
	<xsl:processing-instruction name="xml-stylesheet">
		<xsl:text>type="text/xsl" href="</xsl:text>
		<xsl:value-of select="$api:com.odl.xsl"/>
		<xsl:text>"</xsl:text>
	</xsl:processing-instruction>
	<library
		xsi:schemaLocation="{concat(
			'http://cbear.berlios.de/windows/com ', $api:com.odl.xsd)}">
		<xsl:apply-templates select="@id" mode="api:body"/>
		<xsl:apply-templates select="@uuid" mode="api:body"/>
		<xsl:apply-templates select="@version" mode="api:body"/>
		<xsl:apply-templates select="@brief" mode="api:body"/>
		<xsl:apply-templates select="api:comment" mode="api:body.comment"/>
		<xsl:apply-templates select="api:using" mode="api:body"/>
		<xsl:apply-templates select="api:enum" mode="api:body"/>
		<xsl:apply-templates select="api:struct" mode="api:body"/>
		<xsl:apply-templates select="api:interface" mode="api:body"/>
		<xsl:apply-templates select="api:object" mode="api:body"/>
	</library>	
</xsl:template>

<xsl:template match="/api:library">
	<xsl:apply-templates select="." mode="api:body"/>
</xsl:template>

</xsl:stylesheet>
