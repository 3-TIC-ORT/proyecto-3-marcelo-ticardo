import { onEvent, startServer } from "soquetic";
import { readFileSync } from 'fs';
import SerialPort from 'serialport';
import Readline from '@serialport/parser-readline';

const horario = JSON.parse(readFileSync('horario.json'));
const ingles = JSON.parse(readFileSync('ingles.json'));

let date = new Date().getDay() - 1;
const diasSemana = ['Lunes', 'Martes', 'Miercoles', 'Jueves', 'Viernes'];
let dia = diasSemana[date]
let curso
let bloque
let respuesta

onEvent("bloque", (data) => {
  bloque = Number(data.bloque)
});

onEvent("curso", (data) => {
  curso = data.curso
});

function contestarHorario(dia, curso, bloque) {
  for (const row of horario) {
    if (row.dia === dia && row.curso === curso && row.bloque === bloque) {
      if (row.aula === 'E') {
        return 'Tenés Ed. Física';
      } else if (row.aula === 0) {
        return 'No tenés ninguna materia en este bloque';
      } else {
        return `Tenés ${row.materia} en el Aula ${row.aula}`;
      }
    }
  }
}

let todos
function contestarIngles(dia, bloque){
  todos = ""
  for (const row of ingles) { 
    if (row.dia === dia && row.bloque === bloque) {
      todos = todos + `${row.nivel},${row.aula};`;
    }
  }
  return todos
}

onEvent("preguntarHorario", () => {
  respuesta = contestarHorario(dia, curso, bloque)
  return respuesta})

onEvent("preguntarIngles", () => {
  respuesta = contestarIngles(dia, bloque)
  return respuesta
})

/* TEST:
onEvent("mapa", ()=> {
  // Lista de aulas en orden.
  const aulas = ['L205', 'L203', 'L201', 'L5', 'L200', 'L202', 'L204', 'L206', 'L208', 'L4', 'L3', 'L2', 'L1', 'L213', 'L215', 'L217', 'L218', 'L216', 'L207'];

  // Función para calcular la distancia mínima entre dos aulas y la dirección.
  function calcularCaminoMasCorto(aulaInicio, aulaDestino) {
      const indexInicio = aulas.indexOf(aulaInicio);
      const indexDestino = aulas.indexOf(aulaDestino);
      
      if (indexInicio === -1 || indexDestino === -1) {
          return `Una o ambas aulas no existen en la lista.`;
      }

      const distanciaAdelante = (indexDestino >= indexInicio) 
          ? indexDestino - indexInicio 
          : aulas.length - indexInicio + indexDestino;

      const distanciaAtras = (indexInicio >= indexDestino)
          ? indexInicio - indexDestino
          : indexInicio + aulas.length - indexDestino;

      if (distanciaAdelante <= distanciaAtras) {
          return { distancia: distanciaAdelante, direccion: 'adelante' };
      } else {
          return { distancia: distanciaAtras, direccion: 'atras' };
      }
  }

  const port = new SerialPort('COM4', { baudRate: 9600 });
  const parser = port.pipe(new Readline({ delimiter: '\r\n' }));

  // Ejemplo de uso
  const aulaInicio = 'L205';
  const aulaDestino = 'L202';
  const resultado = calcularCaminoMasCorto(aulaInicio, aulaDestino);

  // Envía la información a   l Arduino
  port.write(`Distancia: ${resultado.distancia}, Direccion: ${resultado.direccion}\n`, (err) => {
      if (err) {
          return console.log('Error en la escritura:', err.message);
      }
      console.log('Mensaje enviado al Arduino:', `Distancia: ${resultado.distancia}, Direccion: ${resultado.direccion}`);
  });

  // Lee los datos que envía el Arduino (opcional)
  parser.on('data', (data) => {
      console.log('Recibido del Arduino:', data);
  }); 
}); 

*/

startServer()