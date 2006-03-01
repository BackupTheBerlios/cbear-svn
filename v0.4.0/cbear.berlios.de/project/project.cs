/*
The MIT License

Copyright (c) 2005 C Bear (http://cbear.sourceforger.net)

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
*/

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
