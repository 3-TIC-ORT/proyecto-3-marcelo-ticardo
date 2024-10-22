import { onEvent, startServer, sendEvent } from "soquetic";
import { readFileSync } from 'fs';
import { SerialPort } from 'serialport';
import { ReadlineParser } from '@serialport/parser-readline';

const horario = JSON.parse(readFileSync('horario.json'));
const ingles = JSON.parse(readFileSync('ingles.json'));

let date = new Date().getDay() - 1;
const diasSemana = ['Lunes', 'Martes', 'Miercoles', 'Jueves', 'Viernes'];
const aulas = ['inicio', 'L202', 'L204', 'L206', 'L208', 'L4', 'L3', 'L2', 'L1', 'L213', 'L215', 'L217', 'L218', 'L216', 'L207', 'L205', 'L203', 'L201', 'L200'];
const aluas_inv = ['inicio', 'L200', 'L201', 'L203', 'L205', 'L207', 'L216', 'L218']
let dia = diasSemana[date]
let curso
let bloque
let cursosIngles
let objetivo
let direccion
let distancia

const port = new SerialPort({
  path: 'COM12',
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

onEvent("mapa", ()=>{
  objetivo = "L5" // SACARLO
  if (objetivo === 'L5'){
    objetivo = 'L200';
  }
  if (aulas.indexOf(objetivo) <= 11){
    direccion = 'ADELANTE';
  } else{
    direccion = 'ATRAS';
  }
  if (direccion === 'ADELANTE'){
    distancia = aulas.indexOf(objetivo);
  } else{
    distancia = aluas_inv.indexOf(objetivo);
  }
  arduino();
  return [distancia, direccion]
});

// Hay que probar esto
async function arduino(){
  port.write(direccion)
  let veces = 0;
  port.on('data', (data) => {
      if (data.toString().trim() === "LINEA") {
          veces++;
          console.log(`Va por la linea ${veces} de ${distancia}`);
          sendEvent("siguiente", null);
          if (veces === distancia){
            console.log('LLegaste a tu destino. Volviendo al inicio.');
            port.write('VOLVER'); 
            veces = 0;
            if (direccion === 'ADELANTE'){ // invertir la dirección
              direccion = 'ATRAS';
            }
            else{
              direccion = 'ADELANTE';
            }
            port.write(direccion);
          }
      }
      });
}


startServer();