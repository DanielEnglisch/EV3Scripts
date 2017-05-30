<?php
	while (@ ob_end_flush());

    	$proc = popen('executables/getStone 2>&1', 'r');
        while (!feof($proc))
        {
        	echo fread($proc, 4096);
            @ flush();
        }
?>