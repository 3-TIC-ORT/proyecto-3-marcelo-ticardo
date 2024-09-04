fetchData("preguntarHorario", (data) => {
    if (data === "Tenés Ingles en el Aula I"){
        window.location.href = "ingles.html"
    } else
        document.getElementById("aula").innerHTML = data
        if (data.includes("L2") || data.endsWith("L1") || data.endsWith("L3") || data.endsWith("L4") || data.endsWith("L5")){
            document.getElementById("otropiso").style.display = "none";
            document.getElementById("boton-volver").style.display = "none";
        }
        else{
            document.getElementById("guia").style.display = "none";
            document.getElementById("boton-SI").style.display = "none";
            document.getElementById("boton-NO").style.display = "none";
        }
    });


document.getElementById("boton-SI").addEventListener("click", function() {
    window.location.href = "mapa.html";
});

document.getElementById("boton-NO").addEventListener("click", function() {
    window.location.href = "proyecto.html";
});

document.getElementById("boton-volver").addEventListener("click", function() {
    window.location.href = "proyecto.html";
});