<?php 
if(isset ($_GET['x']))
{
    $filename = "people.txt";
    $file = fopen( $filename, "w" );
    fwrite( $file, $_GET['x'] );
    fclose( $file );
}
?>