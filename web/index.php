<?php 

  function spawnBrick($r,$g,$b){
    echo ' <div class="brick">
	        <div class ="brick_bottom" style="background-color:rgb('.$r.','.$g.','.$b.');"></div>
	        <div class ="brick_side" style="background-color:rgb('.$r.','.$g.','.$b.');"></div>
	        <div class ="brick_head" style="background-color:rgb('.$r.','.$g.','.$b.');"></div>
	    </div>';
  }

?>
<html>
<head>
	<link rel="stylesheet" href="main.css">
</head>
<body>
	<div id="recipie-container">
	    <h1>Momentanes Rezept</h1>

      <?php
        $file = fopen("in.txt", "r");
        if ($file) {
          $brick_count  = fgets($file);
          echo  "<div class='numb'>$brick_count - Bricks gefunden!</div></br>";
          while (($line = fgets($file)) !== false) {
              $s = explode(";", $line);
              spawnBrick($s[0],$s[1],$s[2]);
            }
          fclose($file);
        }
      ?>
	</div>
	 
	<div id="control">
		<h1> Steuerung </h1>
	    <button type="button" style="left:20%;" >STEINE EINLESEN!</button>
	    <button type="button"  style="right:20%;">STEINE EINSAMMELN!</button> 
	</div>
</body>
</html>


