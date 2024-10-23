localStorage.setItem('theme', '');

function thememode() {
    let menu = document.getElementById("themeMode-check-container");
    let body = document.getElementById("body");
    let boton = document.getElementById("contenedor");   // Contenedor del GIF claro
    let boton1 = document.getElementById("contenedor1"); // Contenedor del GIF oscuro
    let solIcon = document.getElementById("sol-icon");
    let lunaIcon = document.getElementById("luna-icon");

    if (menu.classList.contains("themeMode-check-container-on")) {
        // Modo claro activado
        menu.classList.remove("themeMode-check-container-on");
        menu.classList.remove("circle-color-dark");
        menu.classList.add("circle-color-light");

        // Cambiar el fondo a blanco para el modo claro
        body.style.backgroundColor = "white";
        menu.style.backgroundColor = "white";

        // Ajustar z-index: contenedor claro arriba
        boton.style.zIndex = "1";    // Contenedor claro tiene prioridad
        boton1.style.zIndex = "-1";  // Contenedor oscuro detrás

        // Cambiar los íconos
        solIcon.src = "sol-claro.svg";
        lunaIcon.src = "luna-claro.svg";

        localStorage.setItem('theme', '');
    } else {
        // Modo oscuro activado
        menu.classList.add("themeMode-check-container-on");
        menu.classList.remove("circle-color-light");
        menu.classList.add("circle-color-dark");

        // Cambiar el fondo a oscuro
        body.style.backgroundColor = '#2C3148';
        menu.style.backgroundColor = '#2C3148';

        // Ajustar z-index: contenedor oscuro arriba
        boton.style.zIndex = "1";   // Contenedor claro detrás
        boton1.style.zIndex = "2";   // Contenedor oscuro tiene prioridad

        // Cambiar los íconos
        solIcon.src = "sol-oscuro.svg";
        lunaIcon.src = "luna-oscuro.svg";

        localStorage.setItem('theme', '-oscuro');
    }
}


document.getElementById("boton-inicio").addEventListener("click", function() {
        window.location.href = "intro.html";
});
document.getElementById("contenedor1").addEventListener("click", function() {
    window.location.href = "intro.html";
});