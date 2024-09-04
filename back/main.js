import { onEvent, startServer } from "soquetic";
import { readFileSync } from 'fs';
import SerialPort from 'serialport';
import Readline from '@serialport/parser-readline';

const horario = JSON.parse(readFileSync('horario.json'));
const ingles = JSON.parse(readFileSync('ingles.json'));

let date = new Date().getDay() - 1;
const diasSemana = ['Lunes', 'Martes', 'Miercoles', 'Jueves', 'Viernes'];
let dia = 'diasSemana[date]'
const aulas = ['inicio', 'L202', 'L204', 'L206', 'L208', 'L4', 'L3', 'L2', 'L1', 'L213', 'L215', 'L217', 'L218', 'L216', 'L207', 'L205', 'L203', 'L201', 'L5', 'L200'];
let curso
let bloque
let respuesta
let aulaObjetivo

onEvent("bloque", (data) => {
  bloque = Number(data.bloque)
});

onEvent("curso", (data) => {
  curso = data.curso
});

function responderHorario(dia, curso, bloque) {
  for (const row of horario) {
    if (row.dia === dia && row.curso === curso && row.bloque === bloque) {
      if (row.aula === 'E') {
        return 'Tenés Ed. Física';
      } else if (row.aula === 0) {
        return 'No tenés ninguna materia en este bloque';
      } else {
        aulaObjetivo = row.aula
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
  respuesta = responderHorario(dia, curso, bloque)
  return respuesta
});

onEvent("preguntarIngles", () => {
  respuesta = contestarIngles(dia, bloque)
  return respuesta
});

onEvent("mapa", ()=> {
  camino = responderCamino(aulas, aulaObjetivo);
  return camino
})


/* conexión con hard:

const SerialPort = require('serialport');
const ReadlineParser = require('@serialport/parser-readline');

// Configura el puerto serie
const port = new SerialPort({
    path: 'COM4',
    baudRate: 9600
});

// Configura el parser para leer líneas
const parser = port.pipe(new ReadlineParser({ delimiter: '\n' }));

// Evento cuando se abre la conexión
port.on('open', function() {
    console.log('Conexión serial abierta');
});

// Evento cuando se recibe un dato del Arduino
parser.on('data', function(data) {
    data = data.trim(); // Elimina espacios en blanco alrededor
    if (data === 'llegué') {
        console.log('Notificación recibida del Arduino: Llegué');
    } else if (data === 'obstáculo adelante') {
        console.log('Notificación recibida del Arduino: Obstáculo adelante');
        // Aquí puedes agregar el código para manejar la parada por obstáculo
    } else if (data === 'obstáculo atrás') {
        console.log('Notificación recibida del Arduino: Obstáculo atrás');
        // Aquí puedes agregar el código para manejar la parada por obstáculo trasero
    } else {
        console.log('Recibido del Arduino:', data);
    }
});

// Función para enviar instrucciones al Arduino
function enviarInstrucciones(direccion, distancia) {
    port.write(`${direccion}\n`);
    port.write(`${distancia}\n`);
}

*/

startServer()