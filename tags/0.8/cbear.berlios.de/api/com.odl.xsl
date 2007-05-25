<?xml version="1.0"?>
<xsl:stylesheet 
	version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:api="http://cbear.berlios.de/api"
	xmlns:exsl="http://exslt.org/common"
	xmlns="http://cbear.berlios.de/windows/com"
	xmlns:odl="http://cbear.berlios.de/windows/com"
	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	xmlns:U="http://cbear.berlios.de/uuid"
	extension-element-prefixes="exsl"
	exclude-result-prefixes="xi api odl">

<xsl:import href="../uuid/main.xsl"/>

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
		<xsl:apply-templates select="@id" mode="api:body.local"/>
<!--
		<xsl:apply-templates select="." mode="api:body.uuid"/>
-->
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
	<xsl:value-of select="translate(., '.', '_')"/>
</xsl:template>

<xsl:template match="@id" mode="api:body">
	<xsl:param name="prefix"/>
	<xsl:attribute name="id">
		<xsl:value-of select="translate($prefix, './', '__')"/>
		<xsl:apply-templates select="." mode="api:com.odl.id"/>
	</xsl:attribute>
</xsl:template>

<xsl:template match="@id[../api:pragma/odl:alias]" mode="api:body"/>

<xsl:template match="@id[../api:pragma/odl:alias/@id]" mode="api:body">
	<xsl:param name="prefix"/>
	<xsl:attribute name="id">
		<xsl:value-of select="$prefix"/>
		<xsl:value-of select="../api:pragma/odl:alias/@id"/>
	</xsl:attribute>
</xsl:template>

<xsl:template match="@id" mode="api:body.local">
	<xsl:apply-templates select="." mode="api:body">
		<xsl:with-param name="prefix">
			<xsl:call-template name="api:prefix"/>
		</xsl:with-param>
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="*" mode="api:body.id.full">
	<xsl:apply-templates select="/api:library" mode="api:body.id.full"/>
	<xsl:value-of select="concat('.', @id)"/>
</xsl:template>

<xsl:template match="api:library" mode="api:body.id.full">
	<xsl:value-of select="@id"/>
</xsl:template>

<!-- @brief -->

<xsl:template match="@brief" mode="api:body">
	<attribute id="helpstring">
		<value><xsl:value-of select="concat('&#x22;', ., '&#x22;')"/></value>
	</attribute>
</xsl:template>

<!-- @uuid -->

<xsl:template match="*" mode="api:body.uuid.explicit">
	<xsl:param name="uuid" select="@uuid"/>
	<attribute id="uuid">
		<value><xsl:value-of select="$uuid"/></value>
	</attribute>
</xsl:template>

<xsl:template match="*" mode="api:body.uuid">
	<xsl:variable name="uuid">
		<xsl:call-template name="U:create">
			<xsl:with-param name="namespace" select="U:cbear.id"/>
			<xsl:with-param name="name">
				<xsl:apply-templates select="." mode="api:body.id.full"/>
			</xsl:with-param>
		</xsl:call-template>
	</xsl:variable>
	<xsl:apply-templates select="." mode="api:body.uuid.explicit">
		<xsl:with-param name="uuid" select="translate($uuid, 'abcdef', 'ABCDEF')"/>
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="*[@uuid]" mode="api:body.uuid">
	<xsl:apply-templates select="." mode="api:body.uuid.explicit"/>
</xsl:template>

<!-- @version -->

<xsl:template match="@version" mode="api:body">
	<attribute id="version">
		<value><xsl:value-of select="."/></value>
	</attribute>
</xsl:template>

<!-- pragma -->

<xsl:template match="api:pragma" mode="api:body"/>

<xsl:template match="api:pragma" mode="api:body.pragma">
	<xsl:copy-of select="odl:attribute|odl:cdecl"/>
</xsl:template>

<!-- const -->

<xsl:template match="api:const" mode="api:body">
	<const value="{@value}"/>
</xsl:template>

<!-- custom -->

<!--
<xsl:template name="api:body.custom">
	<xsl:param name="id"/>
	<attribute id="custom">
		<value>0F21F359-AB84-41E8-9A78-36D110E6D2F9</value>
		<value><xsl:value-of select="concat('&#34;', $id, '&#34;')"/></value>
	</attribute>
</xsl:template>
-->

<xsl:template match="api:*" mode="api:body.custom">
	<attribute id="custom">
		<value>0F21F359-AB84-41E8-9A78-36D110E6D2F9</value>
		<value>
			<xsl:value-of select="'&#34;'"/>
			<xsl:apply-templates select="." mode="api:body.id.full"/>
			<xsl:value-of select="'&#34;'"/>
		</value>
	</attribute>
<!--
	<xsl:call-template name="api:body.custom">
		<xsl:with-param name="id" select="concat(/api:library/@id, '.',	@id)"/>
	</xsl:call-template>
-->
</xsl:template>

<!-- prefix -->

<xsl:template match="/api:library" mode="api:body.library.prefix">
	<xsl:apply-templates select="/api:library" mode="api:body.type.ref.library"/>
	<xsl:text>_</xsl:text>
</xsl:template>

<xsl:template 
	match="/api:library[api:pragma/odl:alias/@strong.prefix]" 
	mode="api:body.library.prefix">
	<xsl:value-of select="api:pragma/odl:alias/@strong.prefix"/>
</xsl:template>

<xsl:template name="api:prefix">
	<xsl:if test="$api:com.odl.prefix">
		<xsl:apply-templates select="/api:library" mode="api:body.library.prefix"/>
	</xsl:if>
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
		<xsl:apply-templates select="@id" mode="api:body.local"/>
		<xsl:copy-of select="$content"/>
	</type.ref>
</xsl:template>

<xsl:template match="api:type" mode="api:body.type.ref">
	<xsl:param name="content"/>
	<type.ref>
		<xsl:apply-templates select="@id" mode="api:body.local"/>	
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
			<xsl:apply-templates select="@id" mode="api:body.local"/>
		</type.ref>
	</type.ref>
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

<xsl:template match="/api:library" mode="api:body.type.ref.library">
	<xsl:value-of select="translate(@id, '.', '_')"/>
</xsl:template>

<xsl:template 
	match="/api:library[api:pragma/odl:alias/@id]" 
	mode="api:body.type.ref.library">
	<xsl:value-of select="api:pragma/odl:alias/@id"/>	
</xsl:template>

<xsl:template match="api:type.ref" mode="api:body.type.ref">
	<xsl:apply-templates select="/api:library" mode="api:body.type.ref">
		<xsl:with-param name="id" select="@id"/>
		<xsl:with-param name="content">
			<xsl:apply-templates select="*" mode="api:body"/>
		</xsl:with-param>
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="api:library" mode="api:body.external">
	<xsl:param name="id"/>
	<xsl:param name="content"/>
	<xsl:apply-templates select="." mode="api:body.type.ref">
		<xsl:with-param name="id" select="$id"/>
		<xsl:with-param name="content" select="$content"/>
		<xsl:with-param name="library">
			<xsl:apply-templates select="." mode="api:body.type.ref.library"/>
		</xsl:with-param>
	</xsl:apply-templates>
</xsl:template>

<xsl:template match="api:type.ref[@library]" mode="api:body.type.ref">
	<xsl:variable name="library" select="@library"/>
	<xsl:apply-templates 
		select="document(/api:library/api:using[@id=$library]/@href)/api:library"
		mode="api:body.external">
		<xsl:with-param name="id" select="@id"/>
		<xsl:with-param name="content">
			<xsl:apply-templates select="*" mode="api:body"/>
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
		<attribute id="id">
			<value>0</value>
		</attribute>
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
		<xsl:apply-templates select="@id" mode="api:body.local"/>
<!--
		<xsl:apply-templates select="@uuid" mode="api:body"/>
-->
		<xsl:apply-templates select="." mode="api:body.uuid"/>
		<xsl:apply-templates select="@brief" mode="api:body"/>
		<xsl:apply-templates select="." mode="api:body.dual"/>
		<xsl:apply-templates select="." mode="api:body.custom"/>
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
		<xsl:apply-templates select="@id" mode="api:body.local"/>
<!--
		<xsl:apply-templates select="@uuid" mode="api:body"/>
-->
		<xsl:apply-templates select="." mode="api:body.uuid"/>
		<xsl:apply-templates select="@brief" mode="api:body"/>
		<xsl:apply-templates select="api:comment" mode="api:body.comment"/>
		<xsl:apply-templates select="*" mode="api:body"/>
	</struct>
</xsl:template>

<xsl:template match="api:enum" mode="api:body.typedef">
	<enum>
		<xsl:apply-templates select="@id" mode="api:body.local"/>
<!--
		<xsl:apply-templates select="@uuid" mode="api:body"/>
-->
		<xsl:apply-templates select="." mode="api:body.uuid"/>
		<xsl:apply-templates select="@brief" mode="api:body"/>
		<xsl:apply-templates select="api:comment" mode="api:body.comment"/>
		<xsl:apply-templates select="*" mode="api:body"/>
	</enum>
</xsl:template>

<xsl:template match="api:struct|api:enum" mode="api:body">
	<typedef>
		<xsl:apply-templates select="@id" mode="api:body.local"/>
		<xsl:apply-templates select="." mode="api:body.typedef"/>
	</typedef>
</xsl:template>

<!-- object -->

<xsl:template match="api:struct/api:object" mode="api:body">
	<object>
		<xsl:apply-templates select="@id" mode="api:body"/>
		<xsl:apply-templates select="@brief" mode="api:body"/>
		<xsl:apply-templates select="api:comment" mode="api:body.comment"/>
		<xsl:apply-templates select="*" mode="api:body"/>
	</object>
</xsl:template>

<xsl:template match="api:library/api:object" mode="api:body">
	<coclass>
		<xsl:apply-templates select="@id" mode="api:body.local"/>
<!--
		<xsl:apply-templates select="@uuid" mode="api:body"/>
-->
		<xsl:apply-templates select="." mode="api:body.uuid"/>
		<xsl:apply-templates select="@brief" mode="api:body"/>
		<xsl:apply-templates select="." mode="api:body.custom"/>
		<attribute id="appobject"/>
		<xsl:apply-templates select="api:pragma" mode="api:body.pragma"/>
		<xsl:apply-templates select="api:comment" mode="api:body.comment"/>
		<xsl:for-each select="api:type.ref">
			<xsl:variable name="type.ref">
				<xsl:apply-templates select="." mode="api:body.type.ref"/>
			</xsl:variable>
			<type.ref id="{exsl:node-set($type.ref)/odl:type.ref/odl:type.ref/@id}"/>
		</xsl:for-each>
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

<xsl:template match="api:library" mode="api:body.strong.filename">
	<xsl:value-of select="concat(@id, '.strong.tlb')"/>
</xsl:template>

<xsl:template 
	match="api:library[api:pragma/odl:alias/@strong.filename]" 
	mode="api:body.strong.filename">
	<xsl:value-of select="api:pragma/odl:alias/@strong.filename"/>
</xsl:template>

<xsl:template match="api:using" mode="api:body">
	<xsl:variable name="file">
		<xsl:choose>
			<xsl:when test="$api:com.odl.prefix">
				<xsl:apply-templates 
					select="document(@href)/api:library" mode="api:body.strong.filename"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:apply-templates 
					select="document(@href)/api:library" mode="api:body.filename"/>
			</xsl:otherwise>
		</xsl:choose>
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
<!--
		<xsl:apply-templates select="@uuid" mode="api:body"/>
-->
		<xsl:apply-templates select="." mode="api:body.uuid"/>
		<xsl:apply-templates select="@version" mode="api:body"/>
		<xsl:apply-templates select="@brief" mode="api:body"/>
<!--
		<xsl:call-template name="api:body.custom">
			<xsl:with-param name="id" select="@id"/>
		</xsl:call-template>
-->
		<xsl:apply-templates select="." mode="api:body.custom"/>
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
