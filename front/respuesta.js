fetchData("preguntarHorario", (data) => {
    postData("objetivo", data.aula)
if (data.aula === 'E'){
    document.getElementById("aula").innerHTML = 'Tenés Ed. Física / Natacion';
    document.getElementById("boton-volver").style.display = "";
} else if (data.aula.includes("L2") || data.aula.endsWith("L1") || data.aula.endsWith("L3") || data.aula.endsWith("L4") || data.aula.endsWith("L5")) {
    document.getElementById("aula").innerHTML = `Tenés ${data.materia} en ${data.aula}`;
    document.getElementById("guia").style.display = "";
    document.getElementById("contenedor-bloques").style.display = "";
    document.getElementById("boton-volver").style.display = "none";
    document.getElementById("otropiso").style.display = "none";    
} else {
    document.getElementById("aula").innerHTML = `Tenés ${data.materia} en ${data.aula}`;
    document.getElementById("guia").style.display = "none";
    document.getElementById("contenedor-bloques").style.display = "none";
    document.getElementById("boton-volver").style.display = "";
    document.getElementById("otropiso").style.display = "";    
}
});

document.getElementById("boton-SI").addEventListener("click", function() {
    agrandarBoton("boton-con-franja1");
    window.location.href = "mapa.html";
});

document.getElementById("boton-NO").addEventListener("click", function() {
    agrandarBoton("boton-con-franja2");
    window.location.href = "proyecto.html";
});

document.getElementById("boton-volver").addEventListener("click", function() {
    window.location.href = "proyecto.html";
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