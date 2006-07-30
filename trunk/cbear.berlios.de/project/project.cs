namespace cbear.berlios.de.project
{
	using SX = System.Xml;
	using SXT = System.Xml.Xsl;
	using SXP = System.Xml.XPath;
	using SI = System.IO;
	using ST = System.Text;
	
	class project
	{
		public string text;
		public string rtf;
	
		public void Load(string fileName)
		{
			this.text = new SI.StreamReader(fileName).ReadToEnd();
			SXP.XPathDocument document = new SXP.XPathDocument(new SX.XmlTextReader(
				new SI.StringReader(this.text)));
			SXT.XslTransform transform = new SXT.XslTransform();
			transform.Load(new SX.XmlTextReader("docbook/rtf.xsl"));
			ST.StringBuilder builder = new ST.StringBuilder();
			SI.StringWriter writer = new SI.StringWriter(builder);
			transform.Transform(document, null, writer);
			this.rtf = builder.ToString();
		}
	}
}
