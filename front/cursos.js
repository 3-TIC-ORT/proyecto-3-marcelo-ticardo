document.getElementById('theme-stylesheet').setAttribute('href', `cursos${localStorage.getItem('theme')}.css`);

document.getElementById("boton-cursoA").addEventListener("click", function() {
    agrandarBoton("boton-con-franja1");
    postData("curso", "A"), window.location.href = "bloques.html"});
document.getElementById("boton-cursoB").addEventListener("click", function() {
    agrandarBoton("boton-con-franja2");
    postData("curso", "B"), window.location.href = "bloques.html"});
document.getElementById("boton-cursoC").addEventListener("click", function() {
    agrandarBoton("boton-con-franja3");
    postData("curso", "C"), window.location.href = "bloques.html"});
document.getElementById("boton-cursoD").addEventListener("click", function() {
    agrandarBoton("boton-con-franja4");
    postData("curso", "D"), window.location.href = "bloques.html"});
document.getElementById("boton-cursoE").addEventListener("click", function() {
    agrandarBoton("boton-con-franja5");
    postData("curso", "E"), window.location.href = "bloques.html"});
    
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