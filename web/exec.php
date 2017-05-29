<?php
	$out = exec('./readRecipe');
	echo $out;
	$out = shell_exec('./readRecipe');
	echo $out;
	$out = system('./readRecipe');
	echo $out;
?>