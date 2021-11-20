<?php
    $filename = "people.txt";
    $file = fopen( $filename, "r" );
         
    if( $file == false ) {
        echo ( "Error in opening file" );
        exit();
    }
         
    $filesize = filesize( $filename );
    $filetext = fread( $file, $filesize );
    fclose( $file );
    ?>
<html>
   <head>
      <title>CPS Project</title>
      <meta http-equiv="refresh" content="2">
   </head>
   
   <body style="background-color:powderblue;">
   <h1 style="text-align:center;">Total people in the room:</h1>
   <p style="text-align:center;font-size: 24px;color:green">
        <?php
            echo($filetext);
        ?>
    </p>
   </body>
</html>