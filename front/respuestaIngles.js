function obtenerParametro(param) {
    const urlParams = new URLSearchParams(window.location.search);
    return urlParams.get(param);
}
let aula
document.addEventListener('DOMContentLoaded', () => {
    aula = obtenerParametro('aula');
    document.getElementById('resultado').textContent = `Tenés Inglés en el Aula ${aula}`;
});

document.getElementById("boton-SI").addEventListener("click", function() {
    if (aula.includes("L2")){
            window.location.href = "mapa.html"
    } else{
    alert("No te puedo llevar, el aula queda en otro piso")
    window.location.href = "proyecto.html"
    }

});

document.getElementById("boton-NO").addEventListener("click", function() {
    window.location.href = "proyecto.html";
});