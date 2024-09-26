

let isDarkMode = false;

function thememode() {
    let menu = document.getElementById("themeMode-check-container");
    let body = document.getElementById("body");
    let boton = document.getElementById("boton-inicio");


    if (menu.classList.contains("themeMode-check-container-on")) {
        // Desactivar modo oscuro (modo claro activado)
        menu.classList.remove("themeMode-check-container-on");
        menu.classList.remove("circle-color-dark");
        menu.classList.add("circle-color-light");

        // Cambiar el color de fondo del cuerpo a blanco
        body.style.backgroundColor = "white";
        menu.style.backgroundColor = "white";
        boton.style.backgroundColor = "white"

        // Cambiar el color del borde del botón a negro
        menu.style.borderColor = "black";

        // Estado del modo claro
        isDarkMode = false;
    } else {
        // Activar modo oscuro
        menu.classList.add("themeMode-check-container-on");
        menu.classList.remove("circle-color-light");
        menu.classList.add("circle-color-dark");

        // Cambiar el color de fondo del cuerpo a negro
        body.style.backgroundColor = '#2C3148';
        menu.style.backgroundColor ='#2C3148';
        boton.style.backgroundColor = "white"

        // Cambiar el color del borde del botón a blanco
        menu.style.borderColor = "white";

        // Estado del modo oscuro
        isDarkMode = true;
    }
}

document.getElementById("boton-inicio").addEventListener("click", function() {
    if (isDarkMode) {
        // Si está en modo oscuro, redirigir al wireframe oscuro
        window.location.href = "intro-oscuro.html";
    } else {
        // Si está en modo claro, redirigir al wireframe claro
        window.location.href = "intro.html";
    }
});