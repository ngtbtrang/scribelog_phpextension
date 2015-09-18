<?php 
	$time_start = microtime(true);
	for ($x = 0; $x <= 0; $x++) {
		$res = scribelog('Hello to Scribe from EXT!', 'EXT');
		if ($res != 0){
			echo "ERROR";
		}		
	} 
	$time_end = microtime(true);
	$time = $time_end - $time_start;
	echo "DONE after $time seconds\n";
	
?>
