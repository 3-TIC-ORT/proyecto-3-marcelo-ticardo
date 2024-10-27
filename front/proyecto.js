// Cargar el tema almacenado
if (localStorage.getItem('theme') === '-oscuro') {
    // Si el tema almacenado es oscuro, ajusta los estilos y el GIF desde el inicio
    document.getElementById('body').style.backgroundColor = '#2C3148';
    document.getElementById('themeMode-check-container').classList.add('themeMode-check-container-on');
    document.getElementById('themeMode-check-container').style.backgroundColor = '#2C3148';
    document.getElementById('logo-gif').src = "Logo-1-[remix]-oscuro.gif";
    document.getElementById("sol-icon").src = "sol-oscuro.svg";
    document.getElementById("luna-icon").src = "luna-oscuro.svg";
} else {
    // Modo claro por defecto
    document.getElementById('logo-gif').src = "Logo-1-[remix].gif";
}

function thememode() {
    let menu = document.getElementById("themeMode-check-container");
    let body = document.getElementById("body");
    let boton = document.getElementById("logo-gif");   // Contenedor del GIF
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

        // Cambiar el GIF a la versión clara
        boton.src = "Logo-1-[remix].gif";  // Cambiar a GIF claro

        // Cambiar los íconos
        solIcon.src = "sol-claro.svg";
        lunaIcon.src = "luna-claro.svg";

        // Almacenar el estado en localStorage
        localStorage.setItem('theme', '');
    } else {
        // Modo oscuro activado
        menu.classList.add("themeMode-check-container-on");
        menu.classList.remove("circle-color-light");
        menu.classList.add("circle-color-dark");

        // Cambiar el fondo a oscuro
        body.style.backgroundColor = '#2C3148';
        menu.style.backgroundColor = '#2C3148';

        // Cambiar el GIF a la versión oscura
        boton.src = "Logo-1-[remix]-oscuro.gif";  // Cambiar a GIF oscuro

        // Cambiar los íconos
        solIcon.src = "sol-oscuro.svg";
        lunaIcon.src = "luna-oscuro.svg";

        // Almacenar el estado en localStorage
        localStorage.setItem('theme', '-oscuro');
    }
}

// Evento para redirigir a la otra página al hacer clic en el GIF
document.getElementById("logo-gif").addEventListener("click", function() {
    window.location.href = "intro.html";
});
