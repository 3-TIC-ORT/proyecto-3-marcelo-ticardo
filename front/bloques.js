document.getElementById('theme-stylesheet').setAttribute('href', `bloques${localStorage.getItem('theme')}.css`);

document.getElementById("boton-bloque1").addEventListener("click", function() {
    agrandarBoton("boton-con-franja1");
    postData("bloque", 1), fetchData("preguntarHorario", (data) => {if (data.aula === "I") {window.location.href = "ingles.html";} else if (data.aula === 0) {window.location.href = "nada.html"} else {window.location.href = "respuesta.html"}});});

document.getElementById("boton-bloque2").addEventListener("click", function() {
    agrandarBoton("boton-con-franja2");
    postData("bloque", 2), fetchData("preguntarHorario", (data) => {if (data.aula === "I") {window.location.href = "ingles.html";} else if (data.aula === 0) {window.location.href = "nada.html"} else {window.location.href = "respuesta.html"}});});

document.getElementById("boton-bloque3").addEventListener("click", function() {
    agrandarBoton("boton-con-franja3");
    postData("bloque", 3), fetchData("preguntarHorario", (data) => {if (data.aula === "I") {window.location.href = "ingles.html";} else if (data.aula === 0) {window.location.href = "nada.html"} else {window.location.href = "respuesta.html"}});});

document.getElementById("boton-bloque4").addEventListener("click", function() {
    agrandarBoton("boton-con-franja4");
    postData("bloque", 4), fetchData("preguntarHorario", (data) => {if (data.aula === "I") {window.location.href = "ingles.html";} else if (data.aula === 0) {window.location.href = "nada.html"} else {window.location.href = "respuesta.html"}});});

document.getElementById("boton-bloque5").addEventListener("click", function() {
    agrandarBoton("boton-con-franja5");
    postData("bloque", 5), fetchData("preguntarHorario", (data) => {if (data.aula === "I") {window.location.href = "ingles.html";} else if (data.aula === 0) {window.location.href = "nada.html"} else {window.location.href = "respuesta.html"}});});

document.getElementById("boton-bloque6").addEventListener("click", function() {
    agrandarBoton("boton-con-franja6");
    postData("bloque", 6), fetchData("preguntarHorario", (data) => {if (data.aula === "I") {window.location.href = "ingles.html";} else if (data.aula === 0) {window.location.href = "nada.html"} else {window.location.href = "respuesta.html"}});});

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