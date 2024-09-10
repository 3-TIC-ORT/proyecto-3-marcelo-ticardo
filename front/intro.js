// Selecciona el botón por su ID
const arrowButton = document.getElementById('arrowButton');

// Añade un evento click para redirigir a otro wireframe (otra página)
arrowButton.addEventListener('click', function() {
    // Cambia "otro_wireframe.html" al nombre de tu archivo o enlace
    window.location.href = 'cursos.html';
});

function thememode() {
    let menu = document.getElementById("themeMode-check-container")
    if (menu.classList.contains("themeMode-check-container-on")) {
            menu.classList.remove("themeMode-check-container-on")
    } else {
            menu.classList.add("themeMode-check-container-on")
    }
}
