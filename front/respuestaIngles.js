document.getElementById('theme-stylesheet').setAttribute('href', `respuestaingles${localStorage.getItem('theme')}.css`);


fetchData("aulaIngles", (data) => {
    aula = data
    document.getElementById('resultado').textContent = `Tenés Inglés en el Aula ${aula}`;
    if (aula.includes("L2")){
        document.getElementById("otropiso").style.display = "none";
        document.getElementById("boton-volver").style.display = "none";
    }
    else{
        document.getElementById("guia").style.display = "none";
        document.getElementById("boton-SI").style.display = "none";
        document.getElementById("boton-NO").style.display = "none";
    }
    }
);

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

document.getElementById("boton-SI").addEventListener("click", function() {
    window.location.href = "mapa.html";
});

document.getElementById("boton-NO").addEventListener("click", function() {
    window.location.href = "proyecto.html";
});

document.getElementById("boton-volver").addEventListener("click", function() {
    agrandarBoton("boton-volver");
    window.location.href = "proyecto.html";
});