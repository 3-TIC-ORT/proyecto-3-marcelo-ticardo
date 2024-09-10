function thememode() {
    let menu = document.getElementById("themeMode-check-container");
    let body = document.getElementById("body");
    let text = document.getElementById("text");
    let text1 = document.getElementById("text1");
    
    if (menu.classList.contains("themeMode-check-container-on")) {
        // Desactivar modo oscuro
        menu.classList.remove("themeMode-check-container-on");
        menu.classList.remove("circle-color-dark");
        menu.classList.add("circle-color-light");

        // Cambiar el color de fondo del cuerpo a blanco
        body.style.backgroundColor = "white";

        // Cambiar el color de texto a negro
        text.style.color = "black";
        text1.style.color = "black";

        // Cambiar el color de fondo del botón a blanco
        menu.style.backgroundColor = "white";

        // Cambiar el color del borde del botón a negro
        menu.style.borderColor = "black";
    } else {
        // Activar modo oscuro
        menu.classList.add("themeMode-check-container-on");
        menu.classList.remove("circle-color-light");
        menu.classList.add("circle-color-dark");

        // Cambiar el color de fondo del cuerpo a negro
        body.style.backgroundColor = '#2C3148';

        // Cambiar el color de texto a cualquier color
        text.style.color = "black";
        text1.style.color = "black";

        // Cambiar el color de fondo del botón a negro
        menu.style.backgroundColor ='#2C3148';

        // Cambiar el color del borde del botón a blanco
        menu.style.borderColor = "white";
    }
}

document.getElementById("boton").addEventListener("click", function() {
    window.location.href = "bloques.html"});