function xmlLoad(url)
{
	var xml = new XMLHttpRequest()

	//xml.onreadystatechange = stateChange
	xml.open("GET", url, false)
	xml.send(null)

	// if "OK"
	if (xml.status!=200 && xml.status!=0)
	{
		alert("Problem retrieving XML data: " + xml.status + " " + xml.statusText)
		return null
	}
	return xml
}

function main()
{
	var xsltProcessor = null

	var xml = xmlLoad("http://svn.berlios.de/viewcvs/*checkout*/cbear/trunk/cbear.berlios.de/index.xml")
	var xsl = xmlLoad("http.xsl")

	document.write("b")
	document.write(xml.responseText);
}

main()
