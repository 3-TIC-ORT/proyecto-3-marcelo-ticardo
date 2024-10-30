document.getElementById('theme-stylesheet').setAttribute('href', `mapa${localStorage.getItem('theme')}.css`);





function agrandarBoton(id) {
    var botonConFranja = document.getElementById(id);
    
    if (botonConFranja) {
        // Selecciona el botón de volver
        var boton1 = botonConFranja.querySelector(".boton-volver");
        // Selecciona la franja1
        var franja1 = botonConFranja.querySelector(".franja1");
        if (boton1) {
            boton1.classList.add("grande-volver");
        } else {
            console.log("No se encontró el botón 'volver'");
        }
        if (franja1) {
            franja1.classList.add("oculta");
        } else {
            console.log("No se encontró la franja");
        }
    } else {
        console.log(`No se encontró el elemento con ID ${id}`);
    }
}

// CODIGO DE FUNCIONALIDAD DEL MAPA

const aulas = ['inicio', 'L202', 'L204', 'L206', 'L208', 'L4', 'L3', 'L2', 'L1', 'L213', 'L215', 'L217'];
const aulas_inv = ['inicio', 'L200', 'L201', 'L203', 'L205', 'L207', 'L216', 'L218'];
let objetivo, direccion, normoinv;
let i = 0;  // Control del índice actual

// Obtener el mapa inicial y mostrar las líneas
fetchData("mapa", (data) => {
    objetivo = data[0];
    document.getElementById("yendoalaula").textContent =`Estamos yendo al aula ${objetivo}`
    direccion = data[1];
    document.getElementById(`inicio_u`).setAttribute("visibility", "visible");
    // Mostrar las líneas hasta el objetivo
    if (direccion === 'ADELANTE') {
        normoinv = "norm"
        for (let j = 1; j <= aulas.indexOf(objetivo); j++) {
            document.getElementById(aulas[j]).setAttribute("visibility", "visible");
        }
    } else if (direccion === 'ATRAS') {
        normoinv = "inv"
        for (let j = 1; j <= aulas_inv.indexOf(objetivo); j++) {
            document.getElementById(aulas_inv[j]).setAttribute("visibility", "visible");
        }
    }
});

// Recibir actualizaciones del backend en tiempo real
receive("linea", (data) => {
    if (normoinv === "norm"){
        if (data === "siguiente") {
            // Ocultar ubicación actual y mostrar la siguiente
            document.getElementById(`${aulas[i]}_u`).setAttribute("visibility", "hidden");
            i++;
            document.getElementById(`${aulas[i]}_u`).setAttribute("visibility", "visible");
        } else if (data === "anterior") {
            // Ocultar ubicación actual y mostrar la anterior
            document.getElementById(`${aulas[i]}_u`).setAttribute("visibility", "hidden");
            i--;
            document.getElementById(`${aulas[i]}_u`).setAttribute("visibility", "visible");
        }
    }
    else if (normoinv === "inv"){
        if (data === "siguiente") {
            // Ocultar ubicación actual y mostrar la siguiente
            document.getElementById(`${aulas_inv[i]}_u`).setAttribute("visibility", "hidden");
            i++;
            document.getElementById(`${aulas_inv[i]}_u`).setAttribute("visibility", "visible");
        } else if (data === "anterior") {
            // Ocultar ubicación actual y mostrar la anterior
            document.getElementById(`${aulas_inv[i]}_u`).setAttribute("visibility", "hidden");
            i--;
            document.getElementById(`${aulas_inv[i]}_u`).setAttribute("visibility", "visible");
        }
    }
});

// Al llegar al inicio, volver a la página de inicio
receive("llegada", () => {
    document.getElementById('llegaste').setAttribute("visibility", "visible");
    document.getElementById('llegastee').setAttribute("visibility", "visible");
});


receive("llegadaInicio", () => {
    window.location.href = "proyecto.html"
});