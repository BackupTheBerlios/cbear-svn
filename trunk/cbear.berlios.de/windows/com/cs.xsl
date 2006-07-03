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
	xmlns="http://cbear.berlios.de/cs"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:odl="http://cbear.berlios.de/windows/com"
	xmlns:exsl="http://exslt.org/common"
	xmlns:cs="http://cbear.berlios.de/cs"
	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	xmlns:txt="http://cbear.berlios.de/text"
	extension-element-prefixes="exsl"
	exclude-result-prefixes="xi odl cs txt">

<xsl:import href="color.lib.xsl"/>

<xsl:output method="xml"/>

<xsl:param name="odl:cs.xsd"/>
<xsl:param name="odl:cs.xsl"/>
<xsl:param name="odl:cs.path"/>

<!-- * -->

<xsl:template match="*" mode="odl:cs">
	<xsl:message terminate="no">
		<xsl:value-of select="concat(
			'Unknown tag: &#x22;', name(), '&#x22; was skipped.')"/>
	</xsl:message>
</xsl:template>

<!-- attribute -->

<xsl:template name="odl:cs.reflection">
	<id.ref id="System"/>
	<id.ref id="Reflection"/>
</xsl:template>

<xsl:template match="odl:attribute" mode="odl:cs.attribute"/>

<xsl:template match="odl:attribute[@id='version']" mode="odl:cs.attribute">
	<id.ref type="()">
		<id.ref type=".">
			<xsl:call-template name="odl:cs.reflection"/>
			<id.ref id="AssemblyVersion"/>
		</id.ref>
		<id.ref value="{concat('&quot;', @value, '&quot;')}"/>
	</id.ref>
</xsl:template>

<xsl:template match="odl:attribute[@id='helpstring']" mode="odl:cs.attribute">
	<id.ref type="()">
		<id.ref type=".">
			<id.ref id="System"/>
			<id.ref id="ComponentModel"/>
			<id.ref id="Description"/>
		</id.ref>
		<id.ref value="{@value}"/>
	</id.ref>
</xsl:template>

<xsl:template 
	match="odl:library/odl:attribute[@id='helpstring']" mode="odl:cs.attribute">
	<id.ref type="()">
		<id.ref type=".">
			<xsl:call-template name="odl:cs.reflection"/>
			<id.ref id="AssemblyDescription"/>
		</id.ref>
		<id.ref value="{@value}"/>
	</id.ref>
</xsl:template>

<xsl:template name="odl:cs.interop-services">
	<id.ref id="System"/>
	<id.ref id="Runtime"/>
	<id.ref id="InteropServices"/>
</xsl:template>

<xsl:template match="odl:attribute[@id='uuid']" mode="odl:cs.attribute">
	<id.ref type="()">
		<id.ref type=".">
			<xsl:call-template name="odl:cs.interop-services"/>
			<id.ref id="Guid"/>
		</id.ref>
		<id.ref value="{concat('&quot;', @value, '&quot;')}"/>
	</id.ref>
</xsl:template>

<xsl:template match="odl:attribute[@id='id']" mode="odl:cs.attribute">
	<id.ref type="()">
		<id.ref type=".">
			<xsl:call-template name="odl:cs.interop-services"/>
			<id.ref id="DispId"/>
		</id.ref>
		<id.ref value="{@value}"/>
	</id.ref>
</xsl:template>

<xsl:template match="odl:attribute" mode="odl:cs">
	<attribute>
		<xsl:apply-templates select="." mode="odl:cs.attribute"/>
	</attribute>
</xsl:template>

<xsl:template match="odl:attribute[@id='dual']" mode="odl:cs"/>
<xsl:template match="odl:attribute[@id='appobject']" mode="odl:cs"/>
<xsl:template match="odl:attribute[@id='oleautomation']" mode="odl:cs"/>
<xsl:template match="odl:attribute[@id='propget']" mode="odl:cs"/>
<xsl:template match="odl:attribute[@id='propput']" mode="odl:cs"/>

<xsl:template match="odl:attribute" mode="odl:cs.assembly">
	<attribute id="assembly">
		<xsl:apply-templates select="." mode="odl:cs.attribute"/>
	</attribute>
</xsl:template>

<xsl:template match="odl:attribute" mode="odl:cs.type"/>

<xsl:template name="odl:cs.type-lib-type-flags">
	<xsl:call-template name="odl:cs.interop-services"/>
	<id.ref id="TypeLibTypeFlags"/>
</xsl:template>

<xsl:template match="odl:attribute[@id='dual']" mode="odl:cs.type">
	<id.ref type=".">
		<xsl:call-template name="odl:cs.type-lib-type-flags"/>
		<id.ref id="FDual"/>
	</id.ref>
</xsl:template>

<xsl:template match="odl:attribute[@id='oleautomation']" mode="odl:cs.type">
	<id.ref type=".">
		<xsl:call-template name="odl:cs.type-lib-type-flags"/>
		<id.ref id="FOleAutomation"/>
	</id.ref>
</xsl:template>

<xsl:template match="odl:attribute[@id='appobject']" mode="odl:cs.type">
	<id.ref type=".">
		<xsl:call-template name="odl:cs.type-lib-type-flags"/>
		<id.ref id="FAppObject"/>
	</id.ref>
</xsl:template>

<!-- type.ref -->

<xsl:template match="odl:type.ref" mode="odl:cs">
	<id.ref id="{@id}"/>	
</xsl:template>

<xsl:template match="odl:type.ref[@id='BSTR']" mode="odl:cs">
	<id.ref type=".">
		<id.ref id="System"/>
		<id.ref id="String"/>
	</id.ref>
</xsl:template>

<xsl:template match="odl:type.ref[@id='VARIANT_BOOL']" mode="odl:cs">
	<id.ref type=".">
		<id.ref id="System"/>
		<id.ref id="Boolean"/>
	</id.ref>
</xsl:template>

<xsl:template match="odl:type.ref[@id='INT']" mode="odl:cs">
	<id.ref type=".">
		<id.ref id="System"/>
		<id.ref id="IntPtr"/>
	</id.ref>
</xsl:template>

<xsl:template match="odl:type.ref[@id='DATE']" mode="odl:cs">
	<id.ref type=".">
		<id.ref id="System"/>
		<id.ref id="DateTime"/>
	</id.ref>
</xsl:template>

<xsl:template match="odl:type.ref[@id='LONG']" mode="odl:cs">
	<id.ref type=".">
		<id.ref id="System"/>
		<id.ref id="Int32"/>
	</id.ref>
</xsl:template>

<xsl:template match="odl:type.ref[@id='ULONG']" mode="odl:cs">
	<id.ref type=".">
		<id.ref id="System"/>
		<id.ref id="UInt32"/>
	</id.ref>
</xsl:template>

<xsl:template match="odl:type.ref[@id='USHORT']" mode="odl:cs">
	<id.ref type=".">
		<id.ref id="System"/>
		<id.ref id="UInt16"/>
	</id.ref>
</xsl:template>

<xsl:template match="odl:type.ref[@id='BYTE']" mode="odl:cs">
	<id.ref type=".">
		<id.ref id="System"/>
		<id.ref id="Byte"/>
	</id.ref>
</xsl:template>

<xsl:template match="odl:type.ref[@id='DOUBLE']" mode="odl:cs">
	<id.ref type=".">
		<id.ref id="System"/>
		<id.ref id="Double"/>
	</id.ref>
</xsl:template>

<xsl:template match="odl:type.ref[@id='SAFEARRAY']" mode="odl:cs">
	<id.ref type="[]">
		<xsl:apply-templates select="*" mode="odl:cs"/>
	</id.ref>
</xsl:template>

<xsl:template match="odl:type.ref[@id='*']" mode="odl:cs">
	<xsl:apply-templates select="*" mode="odl:cs"/>
</xsl:template>

<xsl:template match="odl:interface/odl:type.ref[@id='IUnknown']" mode="odl:cs"/>

<xsl:template match="odl:interface/odl:type.ref[@id='IDispatch']" mode="odl:cs"/>

<xsl:template match="odl:method/odl:type.ref" mode="odl:cs"/>

<!-- parameter -->

<xsl:template match="odl:parameter" mode="odl:cs">
	<parameter id="{@id}">
		<xsl:apply-templates select="*" mode="odl:cs"/>
	</parameter>
</xsl:template>

<xsl:template match="odl:parameter[odl:attribute/@id='retval']" mode="odl:cs"/>

<!-- method -->

<xsl:template match="odl:method" mode="odl:cs"/>

<xsl:template match="odl:method" mode="odl:cs.id.ref">
	<id.ref id="void"/>
</xsl:template>

<xsl:template 
	match="odl:method[odl:parameter/odl:attribute/@id='retval']" 
	mode="odl:cs.id.ref">
	<xsl:apply-templates 
		select="odl:parameter[odl:attribute/@id='retval']/odl:type.ref" 
		mode="odl:cs"/>
</xsl:template>

<xsl:template match="odl:method" mode="odl:cs.method">
	<method id="{@id}">
		<xsl:apply-templates select="*" mode="odl:cs"/>
		<xsl:apply-templates select="." mode="odl:cs.id.ref"/>
	</method>
</xsl:template>

<xsl:template match="odl:method" mode="odl:cs.id">
	<xsl:value-of select="@id"/>
</xsl:template>

<xsl:template match="odl:method[count(odl:parameter) &gt;= 2]" mode="odl:cs.id">
	<xsl:value-of select="'this'"/>
</xsl:template>

<xsl:template 
	match="odl:method[odl:attribute/@id='propget']" mode="odl:cs.property.method">
	<get/>
</xsl:template>

<xsl:template 
	match="odl:method[odl:attribute/@id='propput']" mode="odl:cs.property.method">
	<set/>
</xsl:template>

<xsl:template match="odl:method" mode="odl:cs.property">
	<xsl:variable name="id" select="@id"/>
	<xsl:if test="not(following-sibling::odl:method[@id=$id])">
		<xsl:variable name="csid">
			<xsl:apply-templates select="." mode="odl:cs.id"/>
		</xsl:variable>
		<property id="{$csid}">
			<xsl:apply-templates 
				select="odl:attribute" mode="odl:cs"/>
			<xsl:apply-templates 
				select="odl:parameter[position()!=last()]" mode="odl:cs"/>
			<xsl:apply-templates 
				select="odl:parameter[last()]/odl:type.ref" mode="odl:cs"/>
			<xsl:apply-templates 
				select="../odl:method[@id=$id]" mode="odl:cs.property.method"/>
		</property>
	</xsl:if>
</xsl:template>

<xsl:template 
	match="odl:method[odl:attribute/@id='propput']" mode="odl:cs.method">
	<xsl:apply-templates select="." mode="odl:cs.property"/>
</xsl:template>

<xsl:template 
	match="odl:method[odl:attribute/@id='propget']" mode="odl:cs.method">
	<xsl:apply-templates select="." mode="odl:cs.property"/>
</xsl:template>

<!-- interface -->

<xsl:template match="odl:interface" mode="odl:cs.interface.methods">
	<xsl:variable name="id" select="odl:type.ref/@id"/>
	<xsl:apply-templates 
		select="/odl:library/odl:interface[@id=$id]" 
		mode="odl:cs.interface.methods"/>
	<xsl:apply-templates select="odl:method" mode="odl:cs.method"/>
</xsl:template>

<xsl:template match="odl:interface[odl:type.ref]" mode="odl:cs.interface.type">
	<xsl:variable name="id" select="odl:type.ref/@id"/>
	<xsl:apply-templates 
		select="/odl:library/odl:interface[@id=$id]" mode="odl:cs.interface.type"/>
</xsl:template>

<xsl:template 
	match="odl:interface[odl:type.ref/@library]" mode="odl:cs.interface.type">
	<xsl:variable name="library" select="odl:type.ref/@library"/>
	<xsl:variable name="id" select="odl:type.ref/@id"/>
	<xsl:variable 
		name="href" select="/odl:library/odl:importlib[@id=$library]/@href"/>
	<xsl:apply-templates 
		select="document(
			substring($href, 1, string-length() - 4), '.odl.xml')/
			odl:library/odl:interface[@id=$id]" mode="odl:cs.interface.type"/>
</xsl:template>

<xsl:template 
	match="odl:interface[odl:type.ref/@id='IDispatch']" 
	mode="odl:cs.interface.type"/>

<xsl:template 
	match="odl:interface[odl:type.ref/@id='IUnknown']" 
	mode="odl:cs.interface.type">
	<attribute>
		<id.ref type="()">
			<id.ref type=".">
				<xsl:call-template name="odl:cs.interop-services"/>
				<id.ref id="InterfaceType"/>
			</id.ref>
			<id.ref type=".">
				<xsl:call-template name="odl:cs.interop-services"/>
				<id.ref id="ComInterfaceType"/>
				<id.ref id="InterfaceIsIUnknown"/>
			</id.ref>
		</id.ref>
	</attribute>
</xsl:template>

<xsl:template match="odl:interface" mode="odl:cs">
	<interface id="{@id}" access="public">
		<xsl:apply-templates select="." mode="odl:cs.interface.type"/>
		<attribute>
			<id.ref type="()">
				<id.ref type=".">
					<xsl:call-template name="odl:cs.interop-services"/>
					<id.ref id="TypeLibType"/>
				</id.ref>
				<id.ref type="|">
					<xsl:apply-templates select="odl:attribute" mode="odl:cs.type"/>
				</id.ref>
			</id.ref>
		</attribute>
		<xsl:apply-templates select="*" mode="odl:cs"/>
		<xsl:apply-templates select="." mode="odl:cs.interface.methods"/>
	</interface>
</xsl:template>

<!-- item -->

<xsl:template match="odl:item" mode="odl:cs">
	<item id="{@id}" value="{odl:const/@value}"/>
</xsl:template>

<!-- enum -->

<xsl:template match="odl:enum" mode="odl:cs">
	<enum id="{@id}" access="public">
		<xsl:apply-templates select="*" mode="odl:cs"/>
	</enum>	
</xsl:template>

<!-- typedef -->

<xsl:template match="odl:typedef" mode="odl:cs">
	<xsl:apply-templates select="*" mode="odl:cs"/>	
</xsl:template>

<!-- coclass -->

<xsl:template match="odl:coclass" mode="odl:cs">
	<class id="{@id}" access="public">
		<attribute>
			<id.ref type="()">
				<id.ref type=".">
					<xsl:call-template name="odl:cs.interop-services"/>
					<id.ref id="ClassInterface"/>
				</id.ref>
				<id.ref type=".">
					<xsl:call-template name="odl:cs.interop-services"/>
					<id.ref id="ClassInterfaceType"/>
					<id.ref id="None"/>
				</id.ref>
			</id.ref>
		</attribute>
		<attribute>
			<id.ref type="()">
				<id.ref type=".">
					<xsl:call-template name="odl:cs.interop-services"/>
					<id.ref id="TypeLibType"/>
				</id.ref>
				<id.ref type="|">
					<xsl:apply-templates select="odl:attribute" mode="odl:cs.type"/>
				</id.ref>
			</id.ref>
		</attribute>
		<id.ref id="Implementation"/>
		<xsl:apply-templates select="*" mode="odl:cs"/>
	</class>
</xsl:template>

<!-- importlib -->

<xsl:template match="odl:importlib[@href='stdole2.tlb']" mode="odl:cs"/>

<xsl:template match="odl:importlib" mode="odl:cs">
	<using id="{substring(@href, 1, string-length(@href)-4)}"/>
</xsl:template>

<!-- libray -->

<xsl:template match="odl:library" mode="odl:cs">
	<xsl:processing-instruction name="xml-stylesheet">
		<xsl:text>type="text/xsl" href="</xsl:text>
		<xsl:value-of select="$odl:cs.xsl"/>
		<xsl:text>"</xsl:text>
	</xsl:processing-instruction>
	<xsl:variable name="path" select="concat($odl:cs.path, @id)"/>
	<unit
		xsi:schemaLocation="{concat(
			'http://cbear.berlios.de/cs ', $odl:cs.xsd)}"
		id="{$path}">
		<xsl:apply-templates select="odl:attribute" mode="odl:cs.assembly"/>
		<namespace id="{@id}">
			<xsl:apply-templates select="odl:importlib" mode="odl:cs"/>
			<xsl:apply-templates select="odl:typedef" mode="odl:cs"/>
			<xsl:apply-templates select="odl:interface" mode="odl:cs"/>
			<xsl:apply-templates select="odl:coclass" mode="odl:cs"/>
		</namespace>
	</unit>
</xsl:template>

<!-- Entry Point -->

<xsl:template match="odl:*">
	<xsl:apply-templates select="." mode="odl:cs"/>
</xsl:template>

</xsl:stylesheet>
