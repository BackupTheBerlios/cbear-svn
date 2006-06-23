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
	xmlns:odl="http://cbear.berlios.de/windows/com"
	xmlns:exsl="http://exslt.org/common"
	xmlns:cpp="http://cbear.berlios.de/cpp"
	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	xmlns:txt="http://cbear.berlios.de/text"
	extension-element-prefixes="exsl"
	exclude-result-prefixes="xi odl cpp txt">

<xsl:import href="../../text/main.xsl"/>

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
		<id.ref type="::"><id.ref/><xsl:copy-of select="$name"/></id.ref>
	</xsl:variable>
	<xsl:variable name="base">
		<id.ref type="::">
			<id.ref/>
			<id.ref id="cbear_berlios_de"/>
			<id.ref id="windows"/>
			<id.ref id="com"/>
			<id.ref id="enum_t" type="&lt;&gt;">
				<xsl:copy-of select="$name"/>
				<xsl:copy-of select="$internal"/>
			</id.ref>
		</id.ref>
	</xsl:variable>
	<class>
		<xsl:copy-of select="$name"/>
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
				<explicit/>
				<parameter id="X"><id.ref id="int"/></parameter>
				<ctor>
					<id.ref>
						<xsl:copy-of select="$base"/>
						<id.ref type="()">
							<id.ref type="::">
								<id.ref/>
								<id.ref type="()" id="{@id}">
									<id.ref id="X"/>
								</id.ref>
							</id.ref>
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

<!-- struct -->

<xsl:template match="odl:object" mode="odl:cpp">
	<object id="{@id}">
		<xsl:apply-templates select="odl:type.ref" mode="odl:cpp"/>
	</object>
</xsl:template>

<xsl:template match="odl:object" mode="odl:cpp.ctor">
	<ctor><id.ref id="{@id}" type="()"/></ctor>
</xsl:template>

<xsl:template match="odl:struct" mode="odl:cpp">
	<xsl:variable name="name">
		<id.ref id="{@id}"/>
	</xsl:variable>
	<xsl:variable name="internal">
		<id.ref type="::">
			<id.ref/>
			<xsl:copy-of select="$name"/>
		</id.ref>
	</xsl:variable>
	<xsl:variable name="base">
		<id.ref type="::">
			<id.ref/>
			<id.ref id="cbear_berlios_de"/>
			<id.ref id="windows"/>
			<id.ref id="com"/>
			<id.ref id="struct_t" type="&lt;&gt;">
				<xsl:copy-of select="$name"/>
				<xsl:copy-of select="$internal"/>
			</id.ref>
		</id.ref>
	</xsl:variable>	
	<class>
		<xsl:copy-of select="$name"/>
		<access access="public">
			<xsl:copy-of select="$base"/>
			<typedef id="library_info">
				<id.ref id="info"/>
			</typedef>
			<xsl:apply-templates select="odl:object" mode="odl:cpp"/>
			<method id="{@id}">
				<xsl:apply-templates select="odl:object" mode="odl:cpp.ctor"/>
				<body/>
			</method>
			<method id="{@id}">
				<parameter id="X">
					<id.ref type="&amp;">
						<id.ref type="const">
							<id.ref id="move_type"/>
						</id.ref>
					</id.ref>
				</parameter>
				<!--
				<xsl:apply-templates select="odl:object" mode="odl:cpp.ctor"/>
				-->
				<body>
					<id.ref type="-&gt;">
						<id.ref type="this"/>
						<id.ref type="()" id="move_assign">
							<id.ref type="*">
								<id.ref id="X"/>
							</id.ref>
						</id.ref>
					</id.ref>
				</body>
			</method>
			<method id="swap">
				<id.ref id="void"/>
				<parameter id="X">
					<id.ref type="&amp;">
						<xsl:copy-of select="$name"/>
					</id.ref>
				</parameter>
				<body>
					<xsl:for-each select="odl:object">
						<id.ref type="::">
							<id.ref/>
							<id.ref id="cbear_berlios_de"/>
							<id.ref id="base"/>
							<id.ref type="()" id="swap">
								<id.ref type="-&gt;">
									<id.ref id="this"/>
									<id.ref id="{@id}"/>
								</id.ref>
								<id.ref type=".">
									<id.ref id="X"/>
									<id.ref id="{@id}"/>
								</id.ref>
							</id.ref>
						</id.ref>
					</xsl:for-each>
				</body>
			</method>
			<method id="move_assign">
				<id.ref id="void"/>
				<parameter id="X">
					<id.ref type="&amp;">
						<xsl:copy-of select="$name"/>
					</id.ref>
				</parameter>
				<body>
					<xsl:for-each select="odl:object">
						<id.ref type="::">
							<id.ref/>
							<id.ref id="cbear_berlios_de"/>
							<id.ref id="move"/>
							<id.ref type="()" id="assign">
								<id.ref type="-&gt;">
									<id.ref id="this"/>
									<id.ref id="{@id}"/>
								</id.ref>
								<id.ref type=".">
									<id.ref id="X"/>
									<id.ref id="{@id}"/>
								</id.ref>
							</id.ref>
						</id.ref>
					</xsl:for-each>
				</body>
			</method>
			<method id="operator==">
				<id.ref id="bool"/>
				<parameter id="X">
					<id.ref type="&amp;">
						<id.ref type="const">
							<xsl:copy-of select="$name"/>
						</id.ref>
					</id.ref>
				</parameter>
				<const/>				
				<body>
					<id.ref type="return">
						<id.ref type="&amp;&amp;">
							<xsl:for-each select="odl:object">
								<id.ref type="==">
									<id.ref type="-&gt;">
										<id.ref id="this"/>
										<id.ref id="{@id}"/>
									</id.ref>
									<id.ref type=".">
										<id.ref id="X"/>
										<id.ref id="{@id}"/>
									</id.ref>									
								</id.ref>
							</xsl:for-each>
						</id.ref>
					</id.ref>
				</body>
			</method>
			<method id="operator!=">
				<id.ref id="bool"/>
				<parameter id="X">
					<id.ref type="&amp;">
						<id.ref type="const">
							<xsl:copy-of select="$name"/>
						</id.ref>
					</id.ref>
				</parameter>
				<const/>				
				<body>
					<id.ref type="return">
						<id.ref type="||">
							<xsl:for-each select="odl:object">
								<id.ref type="!=">
									<id.ref type="-&gt;">
										<id.ref id="this"/>
										<id.ref id="{@id}"/>
									</id.ref>
									<id.ref type=".">
										<id.ref id="X"/>
										<id.ref id="{@id}"/>
									</id.ref>									
								</id.ref>
							</xsl:for-each>
						</id.ref>
					</id.ref>
				</body>
			</method>
			<!-- Serialization
			<template>
				<id id="ArchiveType"/>
				<method id="serialize">
					<id.ref id="void"/>
					<parameter id="Archive">
						<id.ref type="&amp;">
							<id.ref id="ArchiveType"/>
						</id.ref>
					</parameter>
					<parameter id="Version">
						<id.ref type="const">
							<id.ref id="unsigned int"/>
						</id.ref>
					</parameter>
					<body>
						<xsl:for-each select="odl:object">
							<id.ref type="&amp;">
								<id.ref id="Archive"/>
								<id.ref type="::">
									<id.ref/>
									<id.ref id="boost"/>
									<id.ref id="serialization"/>
									<id.ref id="make_nvp" type="()">
										<id.ref 
											type="value" id="{concat('&#x22;', @id, '&#x22;')}"/>
										<id.ref type="-&gt;">
											<id.ref id="this"/>
											<id.ref id="{@id}"/>
										</id.ref>
									</id.ref>
								</id.ref>
							</id.ref>
						</xsl:for-each>
					</body>
				</method>
			</template>
			-->
			<template>
				<id id="StreamType"/>
				<method id="binary_read">
					<id.ref id="void"/>
					<parameter id="Stream">
						<id.ref type="&amp;">
							<id.ref id="StreamType"/>
						</id.ref>
					</parameter>
					<body>
						<xsl:for-each select="odl:object">
							<id.ref type="::">
								<id.ref/>
								<id.ref id="cbear_berlios_de"/>
								<id.ref id="stream"/>	
								<id.ref id="binary"/>
								<id.ref id="read" type="()">
									<id.ref id="Stream"/>
									<id.ref type="-&gt;">
										<id.ref id="this"/>
										<id.ref id="{@id}"/>
									</id.ref>
								</id.ref>
							</id.ref>
						</xsl:for-each>
					</body>
				</method>
			</template>
			<template>
				<id id="StreamType"/>
				<method id="binary_write">
					<id.ref id="void"/>
					<parameter id="Stream">
						<id.ref type="&amp;">
							<id.ref id="StreamType"/>
						</id.ref>
					</parameter>
					<const/>
					<body>
						<xsl:for-each select="odl:object">
							<id.ref type="::">
								<id.ref/>
								<id.ref id="cbear_berlios_de"/>
								<id.ref id="stream"/>	
								<id.ref id="binary"/>
								<id.ref id="write" type="()">
									<id.ref id="Stream"/>
									<id.ref type="-&gt;">
										<id.ref id="this"/>
										<id.ref id="{@id}"/>
									</id.ref>
								</id.ref>
							</id.ref>
						</xsl:for-each>
					</body>
				</method>
			</template>
		</access>
	</class>
</xsl:template>

<!-- typedef -->

<xsl:template match="odl:typedef" mode="odl:cpp">
	<xsl:apply-templates select="*" mode="odl:cpp"/>
</xsl:template>

<!-- const -->

<xsl:template match="odl:const" mode="odl:cpp">
	<id.ref type="value" id="{@value}"/>
</xsl:template>

<!-- type.ref -->

<xsl:template match="odl:type.ref" mode="odl:cpp">
	<id.ref type="::">
		<id.ref/>
		<id.ref id="cbear_berlios_de"/>
		<id.ref id="windows"/>
		<id.ref id="com"/>		
		<id.ref id="{concat(
		translate(@id, $txt:main.uppercase, $txt:main.lowercase), '_t')}">
			<xsl:if test="*">
				<xsl:attribute name="type">&lt;&gt;</xsl:attribute>
				<xsl:apply-templates select="odl:type.ref|odl:const" mode="odl:cpp"/>
			</xsl:if>
		</id.ref>
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
		<id.ref type="&amp;">
			<id.ref type="const">
				<xsl:apply-templates select="odl:type.ref" mode="odl:cpp"/>
			</id.ref>
		</id.ref>
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
		<id.ref type="::">
			<id.ref type="&lt;&gt;" id="traits">
				<xsl:apply-templates select="odl:type.ref" mode="odl:cpp"/>
			</id.ref>
			<id.ref id="move_type"/>
		</id.ref>
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
	<id.ref id="in"/>
</xsl:template>

<xsl:template 
	match="odl:parameter[odl:attribute/@id='out']" 
	mode="odl:cpp.parameter.io">
	<id.ref id="out"/>
</xsl:template>

<xsl:template 
	match="odl:parameter[odl:attribute/@id='in' and odl:attribute/@id='out']"
	mode="odl:cpp.parameter.io">
	<id.ref id="in_out"/>
</xsl:template>

<xsl:template match="odl:parameter" mode="odl:cpp.method.call">
	<id.ref>
		<id.ref type="::">
			<id.ref id="com"/>
			<id.ref id="internal" type="&lt;&gt;">
				<xsl:apply-templates select="." mode="odl:cpp.parameter.io"/>
			</id.ref>
		</id.ref>
		<id.ref type="()">
			<id.ref id="{@id}"/>
		</id.ref>
	</id.ref>
</xsl:template>

<xsl:template match="odl:parameter" mode="odl:cpp.implementation">
	<parameter id="{@id}">
		<id.ref type="::">
			<id.ref id="internal_result" type="&lt;&gt;">
				<xsl:apply-templates select="." mode="odl:cpp.parameter.io"/>
				<xsl:apply-templates select="odl:type.ref" mode="odl:cpp"/>
			</id.ref>
			<id.ref id="type"/>
		</id.ref>
	</parameter>
</xsl:template>

<xsl:template 
	match="odl:parameter" mode="odl:cpp.implementation.call.parameter">
	<id.ref>
		<id.ref id="wrap" type="&lt;&gt;">
			<xsl:apply-templates select="." mode="odl:cpp.parameter.io"/>
			<xsl:apply-templates select="odl:type.ref" mode="odl:cpp"/>
		</id.ref>
		<id.ref type="()">
			<id.ref id="{@id}"/>
		</id.ref>
	</id.ref>
</xsl:template>

<xsl:template match="odl:parameter" mode="odl:cpp.implementation.call">
	<xsl:apply-templates select="." mode="odl:cpp.implementation.call.parameter"/>
</xsl:template>

<xsl:template 
	match="odl:parameter[odl:attribute/@id='retval']" 
	mode="odl:cpp.implementation.call"/>

<!-- method -->

<xsl:template match="odl:method" mode="odl:cpp.method.id.ref">
	<id.ref id="void"/>
</xsl:template>

<xsl:template 
	match="odl:method[odl:parameter/odl:attribute/@id='retval']" 
	mode="odl:cpp.method.id.ref">
	<id.ref type="::">
		<id.ref id="traits" type="&lt;&gt;">
			<xsl:apply-templates 
				select="odl:parameter[odl:attribute/@id='retval']/odl:type.ref"
				mode="odl:cpp"/>
		</id.ref>
		<id.ref id="move_type"/>
	</id.ref>
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

<xsl:template match="odl:method" mode="odl:cpp.method.id.long">
	<xsl:value-of select="concat(../@id, '_')"/>
	<xsl:apply-templates select="." mode="odl:cpp.method.id.short"/>
</xsl:template>

<xsl:template match="odl:method" mode="odl:cpp.implementation.call">
	
	<xsl:param name="P"/>

	<xsl:variable name="id.long">
		<xsl:apply-templates select="." mode="odl:cpp.method.id.long"/>
	</xsl:variable>

	<id.ref type="-&gt;">
		<id.ref id="{$P}"/>
		<id.ref id="{$id.long}" type="()">
			<xsl:apply-templates 
				select="odl:parameter" mode="odl:cpp.implementation.call"/>
		</id.ref>
	</id.ref>
<!--
	<id.ref type="-&gt;">
		<id.ref type="this"/>
		<id.ref type="-&gt;">
			<id.ref id="base" type="()"/>
			<id.ref id="{$id.long}" type="()">
				<xsl:apply-templates 
					select="odl:parameter" mode="odl:cpp.implementation.call"/>
			</id.ref>
		</id.ref>
	</id.ref>
-->
</xsl:template>

<xsl:template match="odl:method" mode="odl:cpp.implementation.assign">
	<xsl:param name="P"/>
	<xsl:apply-templates select="." mode="odl:cpp.implementation.call">
		<xsl:with-param name="P" select="$P"/>
	</xsl:apply-templates>
</xsl:template>

<xsl:template 
	match="odl:method[odl:parameter/odl:attribute/@id='retval']" 
	mode="odl:cpp.implementation.assign">
	<xsl:param name="P"/>
	<id.ref type="=">
		<xsl:apply-templates 
			select="odl:parameter[odl:attribute/@id='retval']" 
			mode="odl:cpp.implementation.call.parameter"/>
		<xsl:apply-templates select="." mode="odl:cpp.implementation.call">
			<xsl:with-param name="P" select="$P"/>
		</xsl:apply-templates>
	</id.ref>
</xsl:template>

<xsl:template match="odl:method" mode="odl:cpp.implementation">
	<xsl:variable name="id.short">
		<xsl:apply-templates select="." mode="odl:cpp.method.id.short"/>
	</xsl:variable>
	<xsl:variable name="id">
		<xsl:apply-templates select="." mode="odl:cpp.method.id"/>
	</xsl:variable>
	<xsl:variable name="id.long">
		<xsl:apply-templates select="." mode="odl:cpp.method.id.long"/>
	</xsl:variable>
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
				  <xsl:apply-templates select="." mode="odl:cpp.implementation.assign">
						<xsl:with-param name="P" select="'this->base()'"/>
					</xsl:apply-templates>
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
							<id.ref type=".">
								<id.ref type="::">
									<id.ref id="create_exception"/>
									<id.ref id="catch_" type="()"/>
								</id.ref>
								<id.ref id="internal" type="()"/>
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
			<id.ref id="windows"/>
			<id.ref id="com"/>
			<id.ref id="pointer" type="&lt;&gt;">				
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
			<id.ref id="pointer_content" type="&lt;&gt;">
				<id.ref id="Base"/>
				<id.ref type="::">
					<id.ref/>
					<id.ref id="{@id}"/>
				</id.ref>
			</id.ref>
			<access access="public">
				<id.ref id="pointer_content" type="&lt;&gt;">
					<id.ref id="Base"/>
					<id.ref type="::">
						<id.ref/>
						<id.ref id="{odl:type.ref/@id}"/>
					</id.ref>
				</id.ref>
				<xsl:apply-templates select="odl:method" mode="odl:cpp"/>
			</access>
		</class>
	</template>
	<namespace id="dynamic">
		<template>
			<id id="Base"/>
			<class>
				<id.ref id="implementation" type="&lt;&gt;">
					<id.ref id="Base"/>
					<id.ref type="::">
						<id.ref/>
						<id.ref id="{@id}"/>
					</id.ref>
				</id.ref>
				<access access="public">
					<id.ref id="implementation_base" type="&lt;&gt;">
						<id.ref id="Base"/>
						<id.ref type="::">
							<id.ref/>
							<id.ref id="{@id}"/>
						</id.ref>
						<id.ref type="::">
							<id.ref/>
							<id.ref id="{odl:type.ref/@id}"/>
						</id.ref>
					</id.ref>
					<xsl:apply-templates 
						select="odl:method" mode="odl:cpp.implementation"/>
				</access>
			</class>
		</template>
	</namespace>
	<namespace id="static_">
		<template>
			<id id="T"/>
			<id id="B"/>
			<class>
				<id.ref id="interface_content" type="&lt;&gt;">
					<id.ref id="T"/>
					<id.ref id="B"/>
					<id.ref type="::">
						<id.ref/>
						<id.ref id="{@id}"/>
					</id.ref>
				</id.ref>
				<access access="public">
					<id.ref id="interface_" type="&lt;&gt;">
						<id.ref id="T"/>
						<id.ref id="B"/>
						<id.ref type="::">
							<id.ref/>
							<id.ref id="{odl:type.ref/@id}"/>
						</id.ref>						
					</id.ref>
					<xsl:for-each select="odl:method">
						<xsl:variable name="id">
							<xsl:apply-templates select="." mode="odl:cpp.method.id"/>
						</xsl:variable>

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
										<id.ref type="declare" id="P">
											<id.ref type="const">
												<id.ref id="pointer_t"/>
											</id.ref>
											<id.ref type="-&gt;">
												<id.ref type="this"/>
												<id.ref id="base" type="()"/>
											</id.ref>
										</id.ref>
				  					<xsl:apply-templates select="." mode="odl:cpp.implementation.assign">
											<xsl:with-param name="P" select="'P'"/>
										</xsl:apply-templates>
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
												<id.ref type=".">
													<id.ref type="::">
														<id.ref id="create_exception"/>
														<id.ref id="catch_" type="()"/>
													</id.ref>
													<id.ref id="internal" type="()"/>
												</id.ref>
											</id.ref>
										</body>
									</catch>
								</try>
							</body>
						</method>
					</xsl:for-each>
				</access>
			</class>
		</template>
	</namespace>
	<template>
		<class>
			<id.ref id="library_info" type="&lt;&gt;">
				<id.ref type="::">
					<id.ref/>
					<id.ref id="{@id}"/>
				</id.ref>
			</id.ref>
			<access access="public">
				<typedef id="type">
					<id.ref type="::">
						<id.ref/>
						<id.ref id="{/odl:library/@id}"/>
						<id.ref id="info"/>
					</id.ref>
				</typedef>
			</access>
		</class>
	</template>
</xsl:template>

<!-- coclass -->

<xsl:template match="odl:coclass" mode="odl:cpp">
	<xsl:variable name="windows">
		<id.ref/>
		<id.ref id="cbear_berlios_de"/>
		<id.ref id="windows"/>
	</xsl:variable>
	<xsl:variable name="com">
		<xsl:copy-of select="$windows"/>
		<id.ref id="com"/>
	</xsl:variable>
	<xsl:variable name="coclass-info">
		<id.ref type="::">
			<xsl:copy-of select="$com"/>
			<id.ref id="coclass_info" type="&lt;&gt;">
				<id.ref id="Char"/>
			</id.ref>
		</id.ref>
	</xsl:variable>
	<xsl:variable name="uuid-wrap-ref">
		<id.ref type="::">
			<xsl:copy-of select="$com"/>
			<id.ref id="uuid"/>
			<id.ref id="wrap_ref"/>
		</id.ref>
	</xsl:variable>
	<xsl:variable name="select">
		<id.ref type="::">
			<xsl:copy-of select="$windows"/>
			<id.ref id="select" type="&lt;&gt;">
				<id.ref id="Char"/>
			</id.ref>
		</id.ref>
	</xsl:variable>
	<template>
		<id id="Char"/>
		<method id="{concat(@id, '_info')}">
			<xsl:copy-of select="$coclass-info"/>
			<body>
				<id.ref type="return">
					<xsl:copy-of select="$coclass-info"/>
					<id.ref type="()">
						<id.ref>
							<xsl:copy-of select="$uuid-wrap-ref"/>
							<id.ref type="()">
								<id.ref type="::">
									<id.ref/>
									<id.ref id="{concat('LIBID_', ../@id)}"/>
								</id.ref>
							</id.ref>
						</id.ref>
						<id.ref>
							<xsl:copy-of select="$uuid-wrap-ref"/>
							<id.ref type="()">
								<id.ref type="::">
									<id.ref/>
									<id.ref id="{concat('CLSID_', @id)}"/>
								</id.ref>
							</id.ref>
						</id.ref>
						<id.ref type="()" id="CBEAR_BERLIOS_DE_SELECT_STRING">
							<id.ref id="Char"/>
							<id.ref type="value" id="{concat('&#x22;', ../@id, '&#x22;')}"/>
						</id.ref>
						<id.ref type="()" id="CBEAR_BERLIOS_DE_SELECT_STRING">
							<id.ref id="Char"/>
							<id.ref type="value" id="{concat('&#x22;', @id, '&#x22;')}"/>
						</id.ref>
						<id.ref type="()" id="CBEAR_BERLIOS_DE_SELECT_STRING">
							<id.ref id="Char"/>
							<id.ref type="value" id="{concat('&#x22;', ../odl:attribute[@id='version']/@value, '&#x22;')}"/>
						</id.ref>
					</id.ref>
				</id.ref>
			</body>
		</method>
	</template>
</xsl:template>

<!-- uuid -->

<xsl:template match="odl:typedef/odl:struct" mode="odl:cpp.uuid">
	<template>
		<class>
			<id.ref type="::">
				<id.ref id="uuid"/>
				<id.ref type="&lt;&gt;" id="of_type">
					<id.ref type="::">
						<id.ref/>
						<id.ref id="{@id}"/>
					</id.ref>
				</id.ref>
			</id.ref>
			<access access="public">
				<method id="create">
					<static/>
					<id.ref type="&amp;">
						<id.ref type="const">
							<id.ref id="uuid"/>
						</id.ref>
					</id.ref>
					<body>
						<id.ref type="declare" id="Result">
							<id.ref type="static">
								<id.ref type="const">
									<id.ref type="::">
										<id.ref id="uuid"/>
										<id.ref id="internal_type"/>
									</id.ref>
								</id.ref>
							</id.ref>
							<id.ref type="{'{}'}">				
								<xsl:variable 
									name="uuid" select="odl:attribute[@id='uuid']/@value"/>
								<id.ref id="{concat('0x', substring($uuid, 1, 8))}"/>
								<id.ref id="{concat('0x', substring($uuid, 10, 4))}"/>
								<id.ref id="{concat('0x', substring($uuid, 15, 4))}"/>
								<id.ref type="{'{}'}">
									<id.ref id="{concat('0x', substring($uuid, 20, 2))}"/>
									<id.ref id="{concat('0x', substring($uuid, 22, 2))}"/>

									<id.ref id="{concat('0x', substring($uuid, 25, 2))}"/>
									<id.ref id="{concat('0x', substring($uuid, 27, 2))}"/>
									<id.ref id="{concat('0x', substring($uuid, 29, 2))}"/>
									<id.ref id="{concat('0x', substring($uuid, 31, 2))}"/>
									<id.ref id="{concat('0x', substring($uuid, 33, 2))}"/>
									<id.ref id="{concat('0x', substring($uuid, 35, 2))}"/>
								</id.ref>
							</id.ref>
						</id.ref>
						<id.ref type="return">
							<id.ref type="::">
								<id.ref id="uuid"/>
								<id.ref id="wrap_ref" type="()">
									<id.ref id="Result"/>
								</id.ref>
							</id.ref>
						</id.ref>
					</body>
				</method>
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
			<include href="cbear.berlios.de/windows/base.hpp"/>
			<include href="{concat($path, '.h')}"/>
			<include href="cbear.berlios.de/windows/com/int.hpp"/>
			<include href="cbear.berlios.de/windows/com/uint.hpp"/>
			<include href="cbear.berlios.de/windows/com/char.hpp"/>
			<include href="cbear.berlios.de/windows/com/byte.hpp"/>
			<include href="cbear.berlios.de/windows/com/short.hpp"/>
			<include href="cbear.berlios.de/windows/com/ushort.hpp"/>
			<include href="cbear.berlios.de/windows/com/long.hpp"/>
			<include href="cbear.berlios.de/windows/com/ulong.hpp"/>
			<include href="cbear.berlios.de/windows/com/longlong.hpp"/>
			<include href="cbear.berlios.de/windows/com/ulonglong.hpp"/>
			<include href="cbear.berlios.de/windows/com/float.hpp"/>
			<include href="cbear.berlios.de/windows/com/double.hpp"/>
			<include href="cbear.berlios.de/windows/com/enum.hpp"/>
			<include href="cbear.berlios.de/windows/com/array.hpp"/>
			<include href="cbear.berlios.de/windows/com/struct.hpp"/>			
			<include href="cbear.berlios.de/windows/com/variant_bool.hpp"/>
			<include href="cbear.berlios.de/windows/com/bstr.hpp"/>
			<include href="cbear.berlios.de/windows/com/date.hpp"/>
			<include href="cbear.berlios.de/windows/com/safearray.hpp"/>
			<include href="cbear.berlios.de/windows/com/pointer.hpp"/>
			<include href="cbear.berlios.de/windows/com/exception.hpp"/>
			<include href="cbear.berlios.de/windows/com/coclass.hpp"/>
			<include href="cbear.berlios.de/windows/com/idispatch.hpp"/>
			<include href="cbear.berlios.de/windows/com/static/interface_content.hpp"/>
			<include href="cbear.berlios.de/windows/com/static/interface.hpp"/>
			<include href="cbear.berlios.de/windows/com/static/idispatch.hpp"/>
			<include href="cbear.berlios.de/windows/com/dynamic/implementation.hpp"/>
			<include href="cbear.berlios.de/base/swap.hpp"/>
			<namespace id="{translate(@id, '.\/', '___')}">
				<class>
					<id.ref id="info"/>
				</class>
				<xsl:apply-templates select="*" mode="odl:cpp"/>
				<class>
					<id.ref id="info"/>
					<access access="public">
						<xsl:variable name="parent">
							<id.ref type="::">
								<id.ref/>
								<id.ref id="cbear_berlios_de"/>
								<id.ref id="windows"/>
								<id.ref id="com"/>
								<id.ref type="&lt;&gt;" id="scoped_typelib">
									<id.ref id="info"/>
								</id.ref>
							</id.ref>
						</xsl:variable>
						<xsl:copy-of select="$parent"/>
						<xsl:for-each select="odl:typedef/odl:struct">
							<id.ref type="::">
								<id.ref id="{@id}"/>
								<id.ref id="scoped_info"/>
							</id.ref>
						</xsl:for-each>
						<xsl:for-each select="odl:interface">
							<id.ref type="::">
								<id.ref/>
								<id.ref id="cbear_berlios_de"/>
								<id.ref id="windows"/>
								<id.ref id="com"/>
								<id.ref type="&lt;&gt;" id="scoped_type_info">
									<id.ref type="::">
										<id.ref/>
										<id.ref id="{@id}"/>
									</id.ref>
								</id.ref>
							</id.ref>
						</xsl:for-each>
						<method>
							<id.ref id="info"/>
							<parameter id="Hmodule">
								<id.ref type="::">
									<id.ref/>
									<id.ref id="cbear_berlios_de"/>
									<id.ref id="windows"/>
									<id.ref id="hmodule"/>
								</id.ref>
							</parameter>
							<ctor>
								<id.ref>
									<xsl:copy-of select="$parent"/>
									<id.ref type="()">
										<id.ref 
											type="value" 
											id="{concat(
												'L&#x22;', @id, '&#x22;')}"/>
										<id.ref id="Hmodule"/>										
									</id.ref>
								</id.ref>
							</ctor>
							<body/>
						</method>
					</access>
				</class>
			</namespace>
			<namespace id="cbear_berlios_de">
				<namespace id="windows">
					<namespace id="com">						
						<xsl:apply-templates select="odl:typedef/odl:struct" mode="odl:cpp.uuid"/>
						<xsl:apply-templates select="odl:interface" mode="odl:cpp.object"/>
					</namespace>
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
