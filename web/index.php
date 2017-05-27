<?php
  function spawnBrick($r,$g,$b){
    echo '
      <div class="brick">
        <div class="body" style="background-color: rgb('.$r.','.$g.','.$b.');">
          <div class="left" style="background-color: rgb('.$r.','.$g.','.$b.');"></div>
          <div class="right" style="background-color: rgb('.$r.','.$g.','.$b.');"></div>
        </div>
      </div>';
  }
?>
<!DOCTYPE html>
<html lang="de">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Geared Towards Progress - Controller</title>
    <link href="css/bootstrap.min.css" rel="stylesheet">
    <link href="css/brick.css" rel="stylesheet">

  </head>
  <body>
  <div class="container">
      <h1>Momentanes Rezept</h1>

      <div class="container" id="brick-container">
        <?php
        $file = fopen("in.txt", "r");
        if ($file) {
          while (($line = fgets($file)) !== false) {
              $s = explode(";", $line);
              spawnBrick($s[0],$s[1],$s[2]);
            }
          fclose($file);
        }
      ?>

      </div>
      

  </div>

    <script src="js/jquery-3.2.1.min.js"></script>
    <script src="js/bootstrap.min.js"></script>

  
  </body>
</html>