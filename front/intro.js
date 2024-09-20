// Variable global para almacenar el estado del modo
let isDarkMode = false;

function thememode() {
    let menu = document.getElementById("themeMode-check-container");
    let body = document.getElementById("body");
    let text = document.getElementById("text");
    let text1 = document.getElementById("text1");
    let boton = document.getElementById("boton");
    let franja = document.getElementById("franjita");
    
    if (menu.classList.contains("themeMode-check-container-on")) {
        // Desactivar modo oscuro (modo claro activado)
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

        // Estado del modo claro
        isDarkMode = false;

    } else {
        // Activar modo oscuro
        menu.classList.add("themeMode-check-container-on");
        menu.classList.remove("circle-color-light");
        menu.classList.add("circle-color-dark");

        // Cambiar el color de fondo del cuerpo a negro
        body.style.backgroundColor = '#2C3148';

        // Cambiar el color de texto a negro
        text.style.color = "black";
        text1.style.color = "black";
        boton.style.backgroundColor = "#1F2232";
        boton.style.color = "white";
        boton.style.borderColor = "white";
        franja.style.backgroundColor = "#1F2232";
        franja.style.borderColor = "white";

        // Cambiar el color de fondo del botón a negro
        menu.style.backgroundColor ='#2C3148';

        // Cambiar el color del borde del botón a blanco
        menu.style.borderColor = "white";

        // Estado del modo oscuro
        isDarkMode = true;
    }
}

// Escuchar el clic en el botón "Comenzar"
document.getElementById("boton").addEventListener("click", function() {
    if (isDarkMode) {
        // Si está en modo oscuro, redirigir al wireframe oscuro
        window.location.href = "curso-oscuro.html";
    } else {
        // Si está en modo claro, redirigir al wireframe claro
        window.location.href = "cursos.html";
    }

    // Llamar a la función de animación
    agrandarBoton("boton-con-franja-SI");
    console.log("Botón Comenzar clickeado");
});

function agrandarBoton(id) {
    var botonConFranja = document.getElementById(id);
    var boton = botonConFranja.querySelector(".boton");
    var franja = botonConFranja.querySelector(".franja");

    // Agrandar el botón
    boton.classList.add("grande");

    // Hacer desaparecer la franja
    franja.classList.add("oculta");

    console.log("Botón agrandado y franja oculta"); // Para depuración
}
