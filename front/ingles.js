document.getElementById('theme-stylesheet').setAttribute('href', `bloques${localStorage.getItem('theme')}.css`);

fetchData("preguntarIngles", (data) => {
  const niveles = [];
  const aulas = [];

  // Rellenar los arrays niveles y aulas
  data.forEach(grupo => {
      if (grupo) {
          niveles.push(grupo.nivel.trim());
          aulas.push(grupo.aula.trim());
      }
  });

  // Obtener el contenedor donde se añadirán los divs
  const contenedorBotones = document.getElementById('contenedor-botones');

  // Recorrer los niveles y crear los divs dinámicamente
  niveles.forEach((nivel, index) => {
      // Crear un nuevo div
      const divElement = document.createElement('div');
      divElement.id = `div-${index}`;
      divElement.className = 'boton-con-franja'; // Añadir una clase para el contenedor
      divElement.innerHTML = `
          <div id="boton-nivel-${index}" class="boton">${nivel}</div>
          <div class="franja"></div>
      `;

      // Añadir un listener para manejar el clic en cada div
      divElement.addEventListener('click', () => {
          agrandarBoton(divElement.id); // Llamar a la función de agrandar
          postData("objetivo", aulas[index]); // Enviar el aula correspondiente
          window.location.href = 'respuestaIngles.html'; // Redirigir a la siguiente página
      });

      // Añadir el div al contenedor de botones
      contenedorBotones.appendChild(divElement);
  });
});

// Función para agrandar el botón y ocultar la franja
function agrandarBoton(id) {
  var botonConFranja = document.getElementById(id);
  var boton = botonConFranja.querySelector(".boton");
  var franja = botonConFranja.querySelector(".franja");

  // Agrandar el botón
  boton.classList.add("grande");

  // Hacer desaparecer la franja
  franja.classList.add("oculta");

  console.log("Botón agrandado y franja oculta"); // Para depuración
}
