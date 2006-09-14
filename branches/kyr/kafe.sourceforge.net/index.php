<?php 
	$query = $_SERVER["QUERY_STRING"];
	header("Location: http://cbear.berlios.de/$query");
	exit;
?>