<!DOCTYPE html>
<html>
    <head>
        <title>First Pagee</title>
        <style>
            @import url(https://fonts.googleapis.com/css?family=Open+Sans);
            html{
                background-color: #e74c3c;
                display: flex;
                align-items: center;
                justify-content: center;
                height: 100vh;
            }
            body{
                color: #fefefe;
                display: flex;
                align-items: center;
                justify-content: center;
            }
            .first-middle{
                display: block;
                vertical-align: middle;
            }
        </style>
    </head>

    <body>
        <div class="first-middle">
            <?php
                if($_GET["status"]) { ?>
                <label>File uploaded correctly !</label>
                <?php 
                }
            ?>
            <form id="sendFile" enctype="multipart/form-data">
                <input type="file" name="file" />
                <input type="file" name="file2" />
                <input type="text" name="text"/>
                <button type="submit">Send</button>
            </form>
        </div>

        <script>
            const formulario = document.getElementById('sendFile'); // Reemplaza 'miFormulario' con el ID de tu formulario

                // Escucha el evento submit del formulario
                formulario.addEventListener('submit', function(event) {
                event.preventDefault(); // Previene la recarga de la página

                // Crea un objeto FormData a partir del formulario
                const formData = new FormData(formulario);

                // URL a la que quieres enviar los datos del formulario
                const url = '/platform/ajax/upload.php'; // Reemplaza con la URL de destino

                // Opciones para la solicitud fetch
                const opciones = {
                    method: 'POST', // Puedes usar 'GET' u otro método según tus necesidades
                    body: formData,
                };

                // Realiza la solicitud fetch
                fetch(url, opciones)
                    .then(response => response.text())
                    .then(data => {
                    // Maneja la respuesta del servidor aquí, si es necesario
                    console.log(data);
                    })
                    .catch(error => {
                    // Maneja los errores de la solicitud aquí
                    console.error('Error: ' + error);
                    });
                });
        </script>
    </body>
</html>

