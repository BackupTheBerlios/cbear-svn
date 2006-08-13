var xmlhttp = null
var xsltProcessor = null

var url = "http://svn.berlios.de/viewcvs/*checkout*/cbear/trunk/cbear.berlios.de/index.xml" 

// Mozilla family.
if (window.XMLHttpRequest)
{
		xmlhttp=new XMLHttpRequest()
		xsltProcessor = new XSLTProcessor();
}
else
{
	alert("Your browser does not support XMLHttpRequest.")
	return;
}

xmlhttp.onreadystatechange = stateChange
xmlhttp.open("GET", url, false)
xmlhttp.send(null)

// if "OK"
if (xmlhttp.status!=200 && xmlhttp.status!=0)
{
	alert("Problem retrieving XML data:" + xmlhttp.status + " " + xmlhttp.statusText)
	return;
}

document.write("a")
document.write(xmlhttp.responseText);


