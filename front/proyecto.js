localStorage.setItem('theme', '');

function thememode() {
    let menu = document.getElementById("themeMode-check-container");
    let body = document.getElementById("body");
    let boton = document.getElementById("logo-gif");   // Contenedor del GIF claro
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
        boton.src = "Logo-1-[remix]-oscuro.gif"
        // Cambiar los íconos
        solIcon.src = "sol-oscuro.svg";
        lunaIcon.src = "luna-oscuro.svg";

        localStorage.setItem('theme', '-oscuro');
    }
}



document.getElementById("logo-gif").addEventListener("click", function() {
        window.location.href = "intro.html";
});
