function xmlLoad(url)
{
	var xml = new XMLHttpRequest()

	//xml.onreadystatechange = stateChange
	xml.open("GET", url, false)
	xml.send(null)

	// if not "OK"
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

	var path = window.location.search.substring(1)

	var full = 
		"http://svn.berlios.de/viewcvs/*checkout*/cbear/trunk/cbear.berlios.de/" + 
		path + 
		"/index.xml"

	document.getElementsByTagName("body")[0].innerHTML = full

	var xml = xmlLoad(full)

	var xslt = new XSLTProcessor()
	xslt.importStylesheet(xmlLoad("http.xsl").responseXML)	

	var html = xslt.transformToFragment(xml.responseXML, document);

	document.getElementsByTagName("body")[0].appendChild(html);
}

