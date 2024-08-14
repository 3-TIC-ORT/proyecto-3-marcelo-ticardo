let contenido = document.getElementById("boton-inicio");


let button0 = document.createElement("button");
button0.textContent = `Comenzar`;
contenido.appendChild(button0);

document.getElementById("boton-inicio").addEventListener("click", function() {
    window.location.href = "segundo wireframe.html";
});
