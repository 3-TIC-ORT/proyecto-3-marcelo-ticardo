let container_SI = document.getElementById("boton-SI");

let button_SI = document.createElement("button");
button_SI.textContent = `Si`;
container_SI.appendChild(button_SI);

document.getElementById("boton-SI").addEventListener("click", function() {
    window.location.href = "cuarto wireframe.html";
});


let container_NO = document.getElementById("boton-NO");

let button_NO = document.createElement("button");
button_NO.textContent = `No`;
container_NO.appendChild(button_NO);

document.getElementById("boton-NO").addEventListener("click", function() {
    window.location.href = "proyecto.html";
});