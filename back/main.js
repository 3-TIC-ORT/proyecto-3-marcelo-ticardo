import { onEvent, startServer, sendEvent } from "soquetic";
import { readFileSync } from 'fs';
import { SerialPort } from 'serialport';
import { ReadlineParser } from '@serialport/parser-readline';

const horario = JSON.parse(readFileSync('horario.json'));
const ingles = JSON.parse(readFileSync('ingles.json'));

let date = new Date().getDay() - 1;
const diasSemana = ['Lunes', 'Martes', 'Miercoles', 'Jueves', 'Viernes'];
const aulas = ['inicio', 'L202', 'L204', 'L206', 'L208', 'L4', 'L3', 'L2', 'L1', 'L213', 'L215', 'L217'];
const aulas_inv = ['inicio', 'L200', 'L201', 'L203', 'L205', 'L207', 'L216', 'L218'];

let dia = diasSemana[date]
let curso
let bloque
let cursosIngles
let objetivo
let direccion;
let distancia;
let veces
let motion

const port = new SerialPort({
  path: 'COM4',
  baudRate: 9600
});


onEvent("bloque", (data) => {
  bloque = data
});

onEvent("curso", (data) => {
  curso = data
});

onEvent("objetivo", (data) => {
  objetivo = data
});

onEvent("preguntarHorario", () => {
  for (const row of horario) {
    if (row.dia === dia && row.curso === curso && row.bloque === bloque) {
        return {
          materia: row.materia,
          aula: row.aula
    }
    }
  }
});

onEvent("preguntarIngles", () => {
  cursosIngles = [];
  for (const row of ingles) { 
    if (row.dia === dia && row.bloque === bloque) {
      cursosIngles.push({ nivel: row.nivel, aula: row.aula });
    }
  }
  return cursosIngles;
});

onEvent("aulaIngles", () =>{
  return objetivo
});


// Evento que maneja el mapa y establece la dirección y distancia hacia el objetivo
onEvent("mapa", () => {
  if (objetivo === 'L5'){
    objetivo = 'L200';
  }
// Determinar la dirección dependiendo del aula
if (aulas.includes(objetivo)) {
    direccion = 'ADELANTE';
    distancia = aulas.indexOf(objetivo);
} else if (aulas_inv.includes(objetivo)) {
    direccion = 'ATRAS';
    distancia = aulas_inv.indexOf(objetivo);
}
veces = 0;
motion = "yendo";
arduino();
return [objetivo, direccion];
});

// Variable para controlar si la función arduino sigue activa
let running = true;

async function arduino() {
// Verificamos si el proceso ya fue finalizado
if (!running) return;

port.write(`${direccion}\n`);  // Enviar la dirección al Arduino

const handleData = (data) => {
    if (!running) return;  // Verificar si se debe detener la ejecución

    const message = data.toString().trim();

    if (message === "LINEA") {
        console.log(`Va por la linea ${veces} de ${distancia}`);

        if (motion === "yendo") {
            veces++;
            sendEvent("linea", "siguiente");  // Enviar al frontend que avance

            // Si llegó al objetivo, cambiar a "volviendo"
            if (veces === distancia) {
                motion = "volviendo";
                direccion = direccion === 'ADELANTE' ? 'ATRAS' : 'ADELANTE';
                port.write(`${direccion}\n`);
            }
        } else if (motion === "volviendo") {
            veces--;
            sendEvent("linea", "anterior");  // Enviar al frontend que retroceda

            // Si volvió al inicio, finalizar
            if (veces === 0) {
                port.write('LLEGASTE\n');  // Enviar señal de finalización al Arduino
                sendEvent("llegada", null);  // Notificar al frontend que llegó al inicio

                // Detener la función arduino y eliminar el listener
                running = false;
                port.off('data', handleData);  // Eliminar el listener de datos
                return;  // Finalizar ejecución de la función arduino()
            }
        }
    }
};

// Añadir el listener para manejar los datos del puerto
port.on('data', handleData);
}

startServer();
