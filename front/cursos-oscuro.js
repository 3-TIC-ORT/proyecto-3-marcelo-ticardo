document.getElementById("boton-cursoA").addEventListener("click", function() {
    agrandarBoton("boton-con-franja1");
    postData("curso", {curso: "A"}), window.location.href = "bloques-oscuro.html"});

document.getElementById("boton-cursoB").addEventListener("click", function() {
    agrandarBoton("boton-con-franja2");
    postData("curso", {curso: "B"}), window.location.href = "bloques-oscuro.html"});

document.getElementById("boton-cursoC").addEventListener("click", function() {
    agrandarBoton("boton-con-franja3");
    postData("curso", {curso: "C"}), window.location.href = "bloques-oscuro.html"});

document.getElementById("boton-cursoD").addEventListener("click", function() {
    agrandarBoton("boton-con-franja4");
    postData("curso", {curso: "D"}), window.location.href = "bloques-oscuro.html"});

document.getElementById("boton-cursoE").addEventListener("click", function() {
    agrandarBoton("boton-con-franja5");
    postData("curso", {curso: "E"}), window.location.href = "bloques-oscuro.html"});

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