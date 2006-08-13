var xmlhttp

function go()
{
	xmlhttp=null

	var url = "http://svn.berlios.de/viewcvs/*checkout*/cbear/trunk/cbear.berlios.de/index.xml" 

	// Mozilla family.
	if (window.XMLHttpRequest)
	{
 		xmlhttp=new XMLHttpRequest()
	}
	else
	{
		alert("Your browser does not support XMLHttpRequest.")
		return;
	}

	xmlhttp.onreadystatechange = stateChange
	xmlhttp.open("GET", url, true)
	xmlhttp.send(null)
}

function stateChange()
{
	// if xmlhttp shows "loaded"
	if (xmlhttp.readyState!=4)
  {
		return;
	}

 	// if "OK"
  if (xmlhttp.status!=200 && xmlhttp.status!=0)
  {
		alert("Problem retrieving XML data:" + xmlhttp.status + " " + xmlhttp.statusText)
		return;
	}

	document.write("a")
	document.write(xmlhttp.responseText);
}

