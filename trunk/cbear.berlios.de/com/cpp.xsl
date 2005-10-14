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
	xmlns="http://cbear.berlios.de/cpp"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:xi="http://www.w3.org/2001/XInclude"
	xmlns:odl="http://cbear.berlios.de/com"
	xmlns:exsl="http://exslt.org/common"
	xmlns:cpp="http://cbear.berlios.de/cpp"
	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	xmlns:txt="http://cbear.berlios.de/text"
	extension-element-prefixes="exsl"
	exclude-result-prefixes="xi odl cpp txt">

<xsl:import href="../text/main.xsl"/>

<xsl:output method="xml"/>

<xsl:param name="odl:cpp.xsd"/>
<xsl:param name="odl:cpp.xsl"/>
<xsl:param name="odl:cpp.path"/>

<!-- * -->

<xsl:template match="*" mode="odl:cpp">
	<xsl:message terminate="no">
		<xsl:value-of select="concat(
			'Unknown tag: &#x22;', name(), '&#x22; was skipped.')"/>
	</xsl:message>
</xsl:template>

<!-- attribute -->

<xsl:template match="odl:attribute" mode="odl:cpp"/>

<!-- importlib -->

<xsl:template match="odl:importlib" mode="odl:cpp"/>

<!-- item -->

<xsl:template match="odl:item" mode="odl:cpp">
	<item id="{@id}" value="{odl:const/@value}"/>
</xsl:template>

<!-- enum -->

<xsl:template match="odl:enum" mode="odl:cpp">
	<xsl:variable name="name">
		<id.ref id="{@id}"/>
	</xsl:variable>
	<xsl:variable name="internal">
		<id.ref type="::"><id.ref/><id.ref id="{@id}"/></id.ref>
	</xsl:variable>
	<xsl:variable name="base">
		<id.ref type="::">
			<id.ref/>
			<id.ref id="cbear_berlios_de"/>
			<id.ref id="policy"/>
			<id.ref id="wrap" type="&lt;&gt;">
				<xsl:copy-of select="$name"/>
				<xsl:copy-of select="$internal"/>
			</id.ref>
		</id.ref>
	</xsl:variable>
	<class>
		<id.ref id="{@id}"/>
		<access access="public">
			<xsl:copy-of select="$base"/>
			<enum id="type">
				<xsl:apply-templates select="odl:item" mode="odl:cpp"/>
			</enum>
			<method id="{@id}"><body/></method>
			<method id="{@id}">
				<parameter id="X">
					<xsl:copy-of select="$internal"/>
				</parameter>
				<ctor>
					<id.ref>
						<xsl:copy-of select="$base"/>
						<id.ref type="()">
							<id.ref id="X"/>
						</id.ref>
					</id.ref>
				</ctor>
				<body>
				</body>
			</method>
			<method id="{@id}">
				<parameter id="X"><id.ref id="type"/></parameter>
				<ctor>
					<id.ref>
						<xsl:copy-of select="$base"/>
						<id.ref type="()">
							<id.ref>
								<xsl:copy-of select="$internal"/>
								<id.ref type="()">
									<id.ref id="X"/>
								</id.ref>
							</id.ref>
						</id.ref>
					</id.ref>
				</ctor>
				<body>
				</body>
			</method>
		</access>
	</class>
</xsl:template>

<!-- typedef -->

<xsl:template match="odl:typedef" mode="odl:cpp">
	<xsl:apply-templates select="*" mode="odl:cpp"/>
</xsl:template>

<!-- type.ref -->

<xsl:template match="odl:type.ref" mode="odl:cpp">
	<id.ref id="{concat(
		translate(@id, $txt:main.uppercase, $txt:main.lowercase), '_t')}">
		<xsl:if test="odl:type.ref">
			<xsl:attribute name="type">&lt;&gt;</xsl:attribute>
			<xsl:apply-templates select="odl:type.ref" mode="odl:cpp"/>
		</xsl:if>
	</id.ref>
</xsl:template>

<xsl:template 
	match="odl:type.ref[/odl:library/odl:*/@id=@id]" mode="odl:cpp">
	<id.ref type="::">
		<id.ref id="{/odl:library/@id}"/>
		<id.ref id="{@id}"/>
	</id.ref>
</xsl:template>

<xsl:template match="odl:type.ref[@id='*']" mode="odl:cpp">
	<xsl:apply-templates select="odl:type.ref" mode="odl:cpp"/>
</xsl:template>

<!-- parameter -->

<xsl:template match="odl:parameter" mode="odl:cpp">
	<parameter id="{@id}">
		<xsl:apply-templates select="odl:type.ref" mode="odl:cpp"/>
	</parameter>
</xsl:template>

<xsl:template match="odl:parameter[odl:attribute/@id='out']" mode="odl:cpp">
	<parameter id="{@id}">
		<id.ref type="&amp;">
			<xsl:apply-templates select="odl:type.ref" mode="odl:cpp"/>
		</id.ref>
	</parameter>
</xsl:template>

<xsl:template match="odl:parameter[odl:attribute/@id='retval']" mode="odl:cpp"/>

<xsl:template match="odl:parameter" mode="odl:cpp.method.result"/>

<xsl:template 
	match="odl:parameter[odl:attribute/@id='retval']" 
	mode="odl:cpp.method.result">
	<id.ref id="_result" type="declare">
		<xsl:apply-templates select="odl:type.ref" mode="odl:cpp"/>
	</id.ref>
</xsl:template>

<xsl:template match="odl:parameter" mode="odl:cpp.method.return"/>

<xsl:template 
	match="odl:parameter[odl:attribute/@id='retval']" 
	mode="odl:cpp.method.return">
	<id.ref type="return"><id.ref id="_result"/></id.ref>
</xsl:template>

<xsl:template 
	match="odl:parameter[odl:attribute/@id='in']" 
	mode="odl:cpp.parameter.io">
	<xsl:text>in</xsl:text>
</xsl:template>

<xsl:template 
	match="odl:parameter[odl:attribute/@id='out']" 
	mode="odl:cpp.parameter.io">
	<xsl:text>out</xsl:text>
</xsl:template>

<xsl:template 
	match="odl:parameter[odl:attribute/@id='in' and odl:attribute/@id='out']"
	mode="odl:cpp.parameter.io">
	<xsl:text>in_out</xsl:text>
</xsl:template>

<xsl:template match="odl:parameter" mode="odl:cpp.method.call">
	<xsl:variable name="io">
		<xsl:apply-templates select="." mode="odl:cpp.parameter.io"/>
	</xsl:variable>
	<id.ref id="{$io}" type="()">
		<id.ref id="{@id}"/>
	</id.ref>
</xsl:template>

<xsl:template match="odl:parameter" mode="odl:cpp.implementation.io">
	<xsl:text>in_type</xsl:text>
</xsl:template>

<xsl:template 
	match="odl:parameter[odl:attribute/@id='out']" 
	mode="odl:cpp.implementation.io">
	<xsl:text>out_type</xsl:text>
</xsl:template>

<xsl:template 
	match="odl:parameter[odl:attribute/@id='out' and odl:attribute/@id='in']" 
	mode="odl:cpp.implementation.io">
	<xsl:text>in_out_type</xsl:text>
</xsl:template>

<xsl:template match="odl:parameter" mode="odl:cpp.implementation">
	<parameter id="{@id}">
		<xsl:variable name="io">
			<xsl:apply-templates select="." mode="odl:cpp.implementation.io"/>
		</xsl:variable>
		<id.ref type="::">
			<id.ref id="{$io}" type="&lt;&gt;">
				<xsl:apply-templates select="odl:type.ref" mode="odl:cpp"/>
			</id.ref>
			<id.ref id="type"/>
		</id.ref>
	</parameter>
</xsl:template>

<!-- method -->

<xsl:template match="odl:method" mode="odl:cpp.method.id.ref">
	<id.ref id="void"/>
</xsl:template>

<xsl:template 
	match="odl:method[odl:parameter/odl:attribute/@id='retval']" 
	mode="odl:cpp.method.id.ref">
	<xsl:apply-templates select="
		odl:parameter[odl:attribute/@id='retval']/odl:type.ref" mode="odl:cpp"/>
</xsl:template>

<xsl:template match="odl:method" mode="odl:cpp.method.id">
	<xsl:value-of select="@id"/>
</xsl:template>

<xsl:template 
	match="odl:method[odl:attribute/@id='propget']" mode="odl:cpp.method.id">
	<xsl:value-of select="concat('get_', @id)"/>
</xsl:template>

<xsl:template 
	match="odl:method[odl:attribute/@id='propput']" mode="odl:cpp.method.id">
	<xsl:value-of select="concat('put_', @id)"/>
</xsl:template>

<xsl:template match="odl:method" mode="odl:cpp.method.id.short">
	<xsl:value-of select="@id"/>
</xsl:template>

<xsl:template 
	match="odl:method[odl:attribute/@id='propput']" 
	mode="odl:cpp.method.id.short">
	<xsl:value-of select="concat('put_', @id)"/>
</xsl:template>

<xsl:template match="odl:method" mode="odl:cpp">
	<xsl:variable name="id.short">
		<xsl:apply-templates select="." mode="odl:cpp.method.id.short"/>
	</xsl:variable>
	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="odl:cpp.method.id"/>
	</xsl:variable>
	<method id="{$id.short}">
		<xsl:apply-templates select="." mode="odl:cpp.method.id.ref"/>
		<xsl:apply-templates select="odl:parameter" mode="odl:cpp"/>
		<const/>
		<body>
			<xsl:apply-templates select="odl:parameter" mode="odl:cpp.method.result"/>
			<id.ref type="::">
				<id.ref id="exception"/>
				<id.ref id="throw_unless" type="()">
					<id.ref type=".">
						<id.ref type="-&gt;">
							<id.ref type="this"/>
							<id.ref id="internal_reference" type="()"/>
						</id.ref>
						<id.ref id="{$id}" type="()">
							<xsl:apply-templates 
								select="odl:parameter" mode="odl:cpp.method.call"/>
						</id.ref>
					</id.ref>
				</id.ref>
			</id.ref>
			<xsl:apply-templates select="odl:parameter" mode="odl:cpp.method.return"/>
		</body>
	</method>	
</xsl:template>

<xsl:template match="odl:method" mode="odl:cpp.implementation">
	<xsl:variable name="id.short">
		<xsl:apply-templates select="." mode="odl:cpp.method.id.short"/>
	</xsl:variable>
	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="odl:cpp.method.id"/>
	</xsl:variable>
	<xsl:variable name="id.long" select="concat(../@id, '_', $id.short)"/>
	<method id="{$id.long}">
		<virtual/>
		<xsl:apply-templates select="." mode="odl:cpp.method.id.ref"/>
		<xsl:apply-templates select="odl:parameter" mode="odl:cpp"/>
		<abstract/>
	</method>
	<method id="{$id}">
		<id.ref type="::">
			<id.ref id="hresult"/>
			<id.ref id="internal_type"/>
		</id.ref>
		<stdcall/>
		<xsl:apply-templates select="odl:parameter" mode="odl:cpp.implementation"/>
		<body>
			<try>
				<body>
					<id.ref type="-&gt;">
						<id.ref type="this"/>
						<id.ref id="{$id.long}" type="()"/>
					</id.ref>
					<id.ref type="return">
						<id.ref type="::">
							<id.ref id="hresult"/>
							<id.ref id="s_ok"/>
						</id.ref>
					</id.ref>
				</body>
				<catch>
					<parameter><id.ref id="..."/></parameter>
					<body>
						<id.ref type="return">
							<id.ref type="::">
								<id.ref id="exception"/>
								<id.ref id="catch_" type="()"/>
							</id.ref>
						</id.ref>
					</body>
				</catch>
			</try>
		</body>
	</method>
</xsl:template>

<!-- interface -->

<xsl:template match="odl:interface" mode="odl:cpp">
	<typedef id="{@id}">
		<id.ref type="::">
			<id.ref/>
			<id.ref id="cbear_berlios_de"/>
			<id.ref id="com"/>
			<id.ref id="object" type="&lt;&gt;">				
				<id.ref type="::">
					<id.ref/>
					<id.ref id="{@id}"/>
				</id.ref>
			</id.ref>
		</id.ref>
	</typedef>
</xsl:template>

<xsl:template match="odl:interface" mode="odl:cpp.object">
	<template>
		<id id="Base"/>
		<class>
			<id.ref id="object_content" type="&lt;&gt;">				
				<id.ref type="::">
					<id.ref/>
					<id.ref id="{@id}"/>
				</id.ref>
				<id.ref id="Base"/>
			</id.ref>
			<access access="public">
				<id.ref id="object_content" type="&lt;&gt;">
					<id.ref type="::">
						<id.ref/>
						<id.ref id="{odl:type.ref/@id}"/>
					</id.ref>
					<id.ref id="Base"/>
				</id.ref>
				<xsl:apply-templates select="odl:method" mode="odl:cpp"/>
			</access>
		</class>
	</template>
	<template>
		<id id="Base"/>
		<class>
			<id.ref id="implementation" type="&lt;&gt;">
				<id.ref type="::">
					<id.ref/>
					<id.ref id="{@id}"/>
				</id.ref>
				<id.ref id="Base"/>
			</id.ref>
			<access access="public">
				<id.ref id="implementation_base" type="&lt;&gt;">
					<id.ref type="::">
						<id.ref/>
						<id.ref id="{@id}"/>
					</id.ref>
					<id.ref id="Base"/>
					<id.ref type="::">
						<id.ref/>
						<id.ref id="{odl:type.ref/@id}"/>
					</id.ref>
				</id.ref>
				<xsl:apply-templates select="odl:method" mode="odl:cpp.implementation"/>
			</access>
		</class>
	</template>
</xsl:template>

<!-- libray -->

<xsl:template match="odl:library" mode="odl:cpp">
	<xsl:processing-instruction name="xml-stylesheet">
		<xsl:text>type="text/xsl" href="</xsl:text>
		<xsl:value-of select="$odl:cpp.xsl"/>
		<xsl:text>"</xsl:text>
	</xsl:processing-instruction>
	<xsl:variable name="path" select="concat($odl:cpp.path, @id)"/>
	<unit
		xsi:schemaLocation="{concat(
			'http://cbear.berlios.de/cpp ', $odl:cpp.xsd)}"
		id="{$path}">
		<header>
			<include href="{concat($path, '.h')}"/>
			<include href="cbear.berlios.de/com/in.hpp"/>
			<include href="cbear.berlios.de/com/in_out.hpp"/>
			<include href="cbear.berlios.de/com/out.hpp"/>
			<include href="cbear.berlios.de/com/variant_bool.hpp"/>
			<include href="cbear.berlios.de/com/int.hpp"/>
			<include href="cbear.berlios.de/com/byte.hpp"/>
			<include href="cbear.berlios.de/com/ushort.hpp"/>
			<include href="cbear.berlios.de/com/ulong.hpp"/>
			<include href="cbear.berlios.de/com/double.hpp"/>
			<include href="cbear.berlios.de/com/bstr.hpp"/>
			<include href="cbear.berlios.de/com/date.hpp"/>
			<include href="cbear.berlios.de/com/safearray.hpp"/>
			<include href="cbear.berlios.de/com/object.hpp"/>
			<include href="cbear.berlios.de/com/exception.hpp"/>
			<include href="cbear.berlios.de/com/implementation.hpp"/>
			<namespace id="{translate(@id, '.\/', '___')}">
				<xsl:apply-templates select="*" mode="odl:cpp"/>
			</namespace>
			<namespace id="cbear_berlios_de">
				<namespace id="com">
					<xsl:apply-templates select="odl:interface" mode="odl:cpp.object"/>
				</namespace>
			</namespace>
		</header>
	</unit>
</xsl:template>

<!-- Entry Point -->

<xsl:template match="odl:*">
	<xsl:apply-templates select="." mode="odl:cpp"/>
</xsl:template>

</xsl:stylesheet>
