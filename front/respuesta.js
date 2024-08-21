let respuesta
fetchData("preguntarHorario", (data) => {
    if (data === "Tenés Ingles en el Aula I"){
        window.location.href = "ingles.html"
    } else
        document.getElementById("aula").innerHTML = data
        respuesta = data
    });


document.getElementById("boton-SI").addEventListener("click", function() {
    if (respuesta.includes("L2") || respuesta.endsWith("L1") || respuesta.endsWith("L3") || respuesta.endsWith("L4") || respuesta.endsWith("L5")){
            window.location.href = "mapa.html"
    } else{
    alert("No te puedo llevar, el aula queda en otro piso")
    window.location.href = "proyecto.html"
    }

});

document.getElementById("boton-NO").addEventListener("click", function() {
    window.location.href = "proyecto.html";
});