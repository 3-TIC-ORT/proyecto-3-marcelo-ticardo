document.getElementById('theme-stylesheet').setAttribute('href', `respuestaingles${localStorage.getItem('theme')}.css`);


fetchData("aulaIngles", (data) => {
    aula = data;
    document.getElementById('resultado').textContent = `Tenés Inglés en el Aula ${aula}`;

    // Si es en el piso correcto (contiene L2)
    if (aula.includes("L2")) {
        // Ocultar el mensaje de otro piso y el botón de volver
        document.getElementById("otropiso").style.display = "none";
        document.getElementById("boton-volver").style.display = "none";
        document.getElementById("franja1").style.display = "none";
        
        // Mostrar la pregunta "¿Querés guía?" y los botones de Si/No
        document.getElementById("guia").style.display = "flex";
        document.getElementById("contenedor-bloques").style.display = "flex";
    } else {
        // Mostrar el mensaje de que no es en este piso y el botón de volver
        document.getElementById("otropiso").style.display = "flex";  // Mostrar el mensaje de "otro piso"
        document.getElementById("boton-volver").style.display = "flex";  // Mostrar el botón de "volver"
        document.getElementById("franja1").style.display = "flex";  // Mostrar la franja del botón "volver"
        
        // Ocultar los botones de guía
        document.getElementById("guia").style.display = "none";
        document.getElementById("contenedor-bloques").style.display = "none";
    }
});


// Listener del botón "Sí"
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