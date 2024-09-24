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
    postData("objetivo", aulas[index]);
    window.location.href = 'respuestaingles.html'
  });

  contenedor.appendChild(boton);
});
});
const contenedor = document.getElementById('botones2');

niveles.forEach((nivel, index) => {
  const boton = document.createElement('button');
  boton.innerText = nivel;
  boton.className = "boton-nivel";

  boton.addEventListener('click', () => {
    const parametro = aulas[index];
    postData("objetivo", aulas[index]);
    window.location.href = 'respuestaingles.html'
  });
  contenedor.appendChild(boton);
});

const contenedor = document.getElementById('botones3');

niveles.forEach((nivel, index) => {
  const boton = document.createElement('button');
  boton.innerText = nivel;
  boton.className = "boton-nivel";

  boton.addEventListener('click', () => {
    const parametro = aulas[index];
    postData("objetivo", aulas[index]);
    window.location.href = 'respuestaingles.html'
  });

  contenedor.appendChild(boton);
});

const contenedor = document.getElementById('botones4');

niveles.forEach((nivel, index) => {
  const boton = document.createElement('button');
  boton.innerText = nivel;
  boton.className = "boton-nivel";

  boton.addEventListener('click', () => {
    const parametro = aulas[index];
    postData("objetivo", aulas[index]);
    window.location.href = 'respuestaingles.html'
  });

  contenedor.appendChild(boton);
});

const contenedor = document.getElementById('botones5');

niveles.forEach((nivel, index) => {
  const boton = document.createElement('button');
  boton.innerText = nivel;
  boton.className = "boton-nivel";

  boton.addEventListener('click', () => {
    const parametro = aulas[index];
    postData("objetivo", aulas[index]);
    window.location.href = 'respuestaingles.html'
  });

  contenedor.appendChild(boton);
});

const contenedor = document.getElementById('botones6');

niveles.forEach((nivel, index) => {
  const boton = document.createElement('button');
  boton.innerText = nivel;
  boton.className = "boton-nivel";

  boton.addEventListener('click', () => {
    const parametro = aulas[index];
    postData("objetivo", aulas[index]);
    window.location.href = 'respuestaingles.html'
  });

  contenedor.appendChild(boton);
});

const contenedor = document.getElementById('botones7');

niveles.forEach((nivel, index) => {
  const boton = document.createElement('button');
  boton.innerText = nivel;
  boton.className = "boton-nivel";

  boton.addEventListener('click', () => {
    const parametro = aulas[index];
    postData("objetivo", aulas[index]);
    window.location.href = 'respuestaingles.html'
  });

  contenedor.appendChild(boton);
});

const contenedor = document.getElementById('botones8');

niveles.forEach((nivel, index) => {
  const boton = document.createElement('button');
  boton.innerText = nivel;
  boton.className = "boton-nivel";

  boton.addEventListener('click', () => {
    const parametro = aulas[index];
    postData("objetivo", aulas[index]);
    window.location.href = 'respuestaingles.html'
  });

  contenedor.appendChild(boton);
});