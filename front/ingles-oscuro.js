fetchData("preguntarIngles", (data) => {
const niveles = [];
const aulas = [];
const grupos = data.split(';');

grupos.forEach(grupo => {
    if (grupo.trim() !== "") {
        const [nivel, aula] = grupo.split(',');
        niveles.push(nivel.trim());
        aulas.push(aula.trim());
    }
});


const contenedor = document.getElementById('botones');

niveles.forEach((nivel, aula) => {
  const boton = document.createElement('button');
  boton.innerText = nivel;
  boton.className = "boton-nivel";

  boton.addEventListener('click', () => {
    const parametro = aulas[aula];
    window.location.href = `respuestaingles.html?aula=${encodeURIComponent(parametro)}`;
  });

  contenedor.appendChild(boton);
});
    });