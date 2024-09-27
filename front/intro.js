
document.getElementById('theme-stylesheet').setAttribute('href', `intro${localStorage.getItem('theme')}.css`);
// Escuchar el clic en el botón "Comenzar"
document.getElementById("boton").addEventListener("click", function() {
    window.location.href = "cursos.html"
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
