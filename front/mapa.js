document.getElementById('theme-stylesheet').setAttribute('href', `mapa${localStorage.getItem('theme')}.css`);

        document.getElementById("contenedor-imagen").addEventListener("click", function() {
            window.location.href = "respuesta.html"
        });

document.getElementById("boton-volver").addEventListener("click", function() {
    // Llama a la función para agrandar el botón
    agrandarBoton("boton-con-franja3");

    // Redirige inmediatamente
    window.location.href = "proyecto.html";
});

function agrandarBoton(id) {
    var botonConFranja = document.getElementById(id);
    
    if (botonConFranja) {
        console.log(`Elemento con ID ${id} encontrado`);

        // Selecciona el botón de volver
        var boton1 = botonConFranja.querySelector(".boton-volver");
        // Selecciona la franja1
        var franja1 = botonConFranja.querySelector(".franja1");
        if (boton1) {
            console.log("Botón encontrado. Agrandando...");
            boton1.classList.add("grande-volver");
        } else {
            console.log("No se encontró el botón 'volver'");
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