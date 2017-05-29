<?php
  function spawnBrick($r,$g,$b,$num){
    return '<div class="brick" id="brick'.$num.'"><div class="body" style="background-color: rgb('.$r.','.$g.','.$b.');"><div class="left" style="background-color: rgb('.$r.','.$g.','.$b.');"></div><div class="right" style="background-color: rgb('.$r.','.$g.','.$b.');"></div></div></div>';
  }

  function getRecipe(){
    echo'<div class="container" id="recipe">
      <h2>Rezept</h2>
        <div class="container" id="block-container">
        </div>
      </div>';
    while (@ ob_end_flush());
            $num = 1;
            $handle = fopen("in.txt", "r");
            if ($handle) {
                while (($line = fgets($handle)) !== false) {
                   $a = explode(';', $line );
                  $code = spawnBrick($a[0],$a[1],$a[2],$num);
                  $log =  $code . '<script>$("#brick'.$num.'").appendTo("#block-container")</script>';
                  echo $log;
                @ flush();
                $num++;
                }

                fclose($handle);
            }
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
  <div class="container" id="content">
      <h1>Robo Webinterface</h1>
      
      <div class="container" id="actions">
        <h2>Aktionen</h2>
        <div class="btn-group" role="group" aria-label="...">
          <a href="?act=getRecipe" class="btn btn-info" role="button">GetRecipe</a>
          <a href="?act=readRecipe" class="btn btn-info" role="button">ReadRecipe</a>
          <a href="?act=moveTest" class="btn btn-info" role="button">MoveTest</a>
          <a href="?act=getStone" class="btn btn-info" role="button">GetStone</a>

        </div>
      </div>
      <script src="js/jquery-3.2.1.min.js"></script>

      <div class="container" id="console">
        <?php
          if(isset($_GET['act'])){
            
            if($_GET['act'] == 'getRecipe'){
              getRecipe();
            }else if ($_GET['act'] == 'moveTest'){
              echo "<h2>Konsole</h2>";
              while (@ ob_end_flush());
              echo '<pre>';
              echo "Script running moveTest...\n";
              @ flush();

              $proc = popen('echo Cisco0| sudo php php/start_moveTest.php', 'r');
              while (!feof($proc))
              {
                  echo fread($proc, 4096);
                  @ flush();
              }
              echo "Done!";
              echo '</pre>';
            }else if ($_GET['act'] == 'getStone'){
              echo "<h2>Konsole</h2>";
              while (@ ob_end_flush());
              echo '<pre>';
              echo "Script running getStone...\n";
              @ flush();

              $proc = popen('echo Cisco0| sudo php php/start_getStone.php', 'r');
              while (!feof($proc))
              {
                  echo fread($proc, 4096);
                  @ flush();
              }
              echo "Done!";
              echo '</pre>';
            }else if ($_GET['act'] == 'readRecipe'){

               echo'<div class="container" id="recipe">
      <h2>Live Rezept</h2>
        <div class="container" id="block-container">
        </div>
      </div>';

              echo "<h2>Konsole</h2>";
              while (@ ob_end_flush());
              echo '<pre>';
              echo "Script running readRecipe...\n";
              @ flush();
              $proc = popen('echo Cisco0| sudo php php/start_readRecipe.php', 'r');

              $num = 1;
              while (!feof($proc))
              { 
                  $log = fread($proc, 4096);
                  if(!empty($log)){
                    $exp = explode(';', $log);
                    $out =  '';
                    $out .= spawnBrick($exp[0],$exp[1],$exp[2],$num);
                    $out .= '<script>$("#brick'.($num).'").appendTo("#block-container")</script>';
                    echo $out;
                    echo $log;
                    @ flush();
                    $num++;
                  }
                  
              }
              echo "Done!";
              echo '</pre>';
            }
        }

        ?>
      </div>
  </div>

    <script src="js/bootstrap.min.js"></script>

  </body>
</html>