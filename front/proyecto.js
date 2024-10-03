localStorage.setItem('theme', '');

function thememode() {
    let menu = document.getElementById("themeMode-check-container");
    let body = document.getElementById("body");
    let boton = document.getElementById("boton-inicio");
    let solIcon = document.getElementById("sol-icon");
    let lunaIcon = document.getElementById("luna-icon");


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

        solIcon.src = "sol-claro.svg";
        lunaIcon.src = "luna-claro.svg";
        // Estado del modo claro
        localStorage.setItem('theme', '');
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
        
        solIcon.src = "sol-oscuro.svg";
        lunaIcon.src = "luna-oscuro.svg";
        // Estado del modo oscuro
        localStorage.setItem('theme', '-oscuro');
    }
}

document.getElementById("boton-inicio").addEventListener("click", function() {
        window.location.href = "intro.html";
});