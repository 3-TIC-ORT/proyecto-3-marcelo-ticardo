function obtenerParametro(param) {
    const urlParams = new URLSearchParams(window.location.search);
    return urlParams.get(param);
}
let aula
document.addEventListener('DOMContentLoaded', () => {
    aula = obtenerParametro('aula');
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

document.getElementById("boton-SI").addEventListener("click", function() {
    window.location.href = "mapa.html";
});

document.getElementById("boton-NO").addEventListener("click", function() {
    window.location.href = "proyecto.html";
});

document.getElementById("boton-volver").addEventListener("click", function() {
    window.location.href = "proyecto.html";
});