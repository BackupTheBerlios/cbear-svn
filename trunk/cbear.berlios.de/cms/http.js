var xml = null
var xsl = null
var xsltProcessor = null

var xmlUrl = "http://svn.berlios.de/viewcvs/*checkout*/cbear/trunk/cbear.berlios.de/index.xml" 
var xslUrl = "http.xsl"

// Mozilla family.
if (window.XMLHttpRequest)
{
		xml = new XMLHttpRequest()
		xsl = new XMLHttpRequest()
		xsltProcessor = new XSLTProcessor();
}
else
{
	alert("Your browser does not support XMLHttpRequest.")
	return;
}

xml.onreadystatechange = stateChange
xml.open("GET", xmlUrl, false)
xml.send(null)

// if "OK"
if (xml.status!=200 && xml.status!=0)
{
	alert("Problem retrieving XML data: " + xml.status + " " + xml.statusText)
	return;
}

xsl.onreadystatechange = stateChange
xsl.open("GET", xslUrl, false)
xsl.send(null)

// if "OK"
if (xsl.status!=200 && xsl.status!=0)
{
	alert("Problem retrieving XSL data: " + xsl.status + " " + xsl.statusText)
	return;
}

document.write("b")
document.write(xml.responseText);


