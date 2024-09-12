document.getElementById("boton-bloque1").addEventListener("click", function() {
    agrandarBoton("boton-con-franja1");
    postData("bloque", {bloque: "1"}), window.location.href = "respuesta.html"});

document.getElementById("boton-bloque2").addEventListener("click", function() {
    agrandarBoton("boton-con-franja2");
    postData("bloque", {bloque: "2"}), window.location.href = "respuesta.html"});

document.getElementById("boton-bloque3").addEventListener("click", function() {
    agrandarBoton("boton-con-franja3");
    postData("bloque", {bloque: "3"}), window.location.href = "respuesta.html"});

document.getElementById("boton-bloque4").addEventListener("click", function() {
    agrandarBoton("boton-con-franja4");
    postData("bloque", {bloque: "4"}), window.location.href = "respuesta.html"});

document.getElementById("boton-bloque5").addEventListener("click", function() {
    agrandarBoton("boton-con-franja5");
    postData("bloque", {bloque: "5"}), window.location.href = "respuesta.html"});

document.getElementById("boton-bloque6").addEventListener("click", function() {
    agrandarBoton("boton-con-franja6");
    postData("bloque", {bloque: "6"}), window.location.href = "respuesta.html"});

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