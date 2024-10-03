document.getElementById('theme-stylesheet').setAttribute('href', `respuesta${localStorage.getItem('theme')}.css`);

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
    document.getElementById("franja1").style.display = "none";
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
// Listener del botón volver
document.getElementById("boton-volver").addEventListener("click", function() {
    // Llama a la función para agrandar el botón
    agrandarBoton("boton-con-franja3");

    // Redirige inmediatamente
    window.location.href = "proyecto.html";
});

// Función para agrandar el botón y ocultar la franja
function agrandarBoton(id) {
    var botonConFranja = document.getElementById(id);
    
    if (botonConFranja) {
        console.log(`Elemento con ID ${id} encontrado`);

        // Selecciona el botón de volver
        var boton1 = botonConFranja.querySelector(".boton-volver");
        // Selecciona la franja1
        var franja1 = botonConFranja.querySelector(".franja1");
        var boton = botonConFranja.querySelector(".boton")
        var franja = botonConFranja.querySelector(".franja")
        

        // Verifica si los elementos existen
        if (boton1) {
            console.log("Botón encontrado. Agrandando...");
            boton1.classList.add("grande-volver");
        } else {
            console.log("No se encontró el botón 'volver'");
        }
        if (boton) {
            console.log("Botón encontrado. Agrandando...");
            boton.classList.add("grande");
        } else {
            console.log("No se encontró el botón 'volver'");
        }
        if (franja) {
            console.log("Franja encontrada. Ocultando...");
            franja.classList.add("oculta");
        } else {
            console.log("No se encontró la franja");
        }
        if (franja1) {
            console.log("Franja encontrada. Ocultando...");
            franja1.classList.add("oculta");
        } else {
            console.log("No se encontró la franja");
        }

    } else {
        console.log(`No se encontró el elemento con ID ${id}`);
    }
}

document.getElementById("contenedor-imagen").addEventListener("click", function() {
    window.location.href = "bloques.html";
});
