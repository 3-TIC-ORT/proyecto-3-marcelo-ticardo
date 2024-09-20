fetchData("preguntarIngles", (data) => {
  const niveles = [];
  const aulas = [];
  data.forEach(grupo => {
    if (grupo) {
      niveles.push(grupo.nivel.trim());
      aulas.push(grupo.aula.trim());
    }
  });

  const contenedor = document.getElementById('botones');

  niveles.forEach((nivel, index) => {
    const boton = document.createElement('button');
    boton.innerText = nivel;
    boton.className = "boton-nivel";

    boton.addEventListener('click', () => {
      const parametro = aulas[index];
      postData("objetivo", aula[index]);
      window.location.href = 'respuestaingles.html'
    });

    contenedor.appendChild(boton);
  });
});
