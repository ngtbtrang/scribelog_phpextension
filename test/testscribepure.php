<?php
	$time_start = microtime(true);	
	$GLOBALS['THRIFT_ROOT'] = '/usr/lib/php';
	$GLOBALS['SCRIBE_ROOT'] = '/home/trangntb/testphpextension/gen-php';	
	
	error_reporting(E_ALL);

	require_once ('/usr/lib/php/Thrift/ClassLoader/ThriftClassLoader.php');

	use Thrift\ClassLoader\ThriftClassLoader;

	$loader = new ThriftClassLoader();
	$loader->registerNamespace('Thrift', '/usr/lib/php/');
	$loader->register();	
	
	include_once $GLOBALS['SCRIBE_ROOT'].'/facebook/fb303/FacebookService.php';
	include_once $GLOBALS['THRIFT_ROOT'].'/Thrift/Type/TType.php';
	include_once $GLOBALS['SCRIBE_ROOT'].'/scribe/thrift/Types.php';
	include_once $GLOBALS['SCRIBE_ROOT'].'/scribe/thrift/scribe.php';
	include_once $GLOBALS['THRIFT_ROOT'].'/Thrift/Protocol/TProtocol.php';
	include_once $GLOBALS['THRIFT_ROOT'].'/Thrift/Protocol/TBinaryProtocol.php';
	include_once $GLOBALS['THRIFT_ROOT'].'/Thrift/Transport/TTransport.php';
	include_once $GLOBALS['THRIFT_ROOT'].'/Thrift/Transport/TFramedTransport.php';
	include_once $GLOBALS['THRIFT_ROOT'].'/Thrift/Transport/TSocket.php';	

	
	use Thrift\Protocol\TBinaryProtocol;
	use Thrift\Transport\TSocket;
	use Thrift\Transport\TFramedTransport;
	use Thrift\Exception\TException;
	use scribe\thrift\scribeClient;
	use scribe\thrift\LogEntry;
	use scribe\thrift\ResultCode;	
	
	
	
	try {
		$sock = new TSocket('localhost', 1463);
		$trans = new TFramedTransport($sock);
		$prot = new TBinaryProtocol($trans);
		
		// Create the client
		print "creating scribe client\n";
		$scribe_client = new scribeClient($prot);
		
		// Open the transport (we rely on PHP to close it at script termination)
		print "opening transport\n";
		$trans->open();
		
		$entry = new LogEntry;
		$entry->category = "PHP";
		$entry->message = "Hello to Scribe from PHP!";
		$messages []= $entry;
		
		for ($x = 0; $x <= 0; $x++) {
			$result = $scribe_client->Log($messages);
			
			if ($result != ResultCode::OK) {
				print "Warning: Log returned $result \n";
			}			
		} 
		
		$time_end = microtime(true);
		$time = $time_end - $time_start;
		echo "DONE after $time seconds\n";
		
		
		} catch (Exception $x) {
		print "Unable to create global scribe client, received exception: $x \n";
	}
	
	
?>





