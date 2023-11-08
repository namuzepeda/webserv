<?php

$uploadDir = $_SERVER["UPLOAD_STORE"]; // Carpeta de destino
if (!file_exists($uploadDir)) {
    mkdir($uploadDir, 0777, true); // Crea la carpeta si no existe
}

foreach ($_FILES as $file) {
    $uploadFile = $uploadDir . basename($file['name']); // Nombre de archivo de destino

    // Verifica si se subió el archivo correctamente
    if (move_uploaded_file($file['tmp_name'], $uploadFile)) {
        echo "El archivo {$file['name']} se ha subido con éxito a la carpeta de destino.";
        die(json_encode(array("ok" => true)));
    } else {
        die(json_encode(array("ok" => false)));
        echo "Error al subir el archivo {$file['name']}.";
    }
}

die(json_encode(array("ok" => true)));

?>