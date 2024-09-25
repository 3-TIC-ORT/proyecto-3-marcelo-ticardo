import { onEvent, startServer, sendEvent } from "soquetic";
import { readFileSync } from 'fs';
import { SerialPort } from 'serialport';
import { ReadlineParser } from '@serialport/parser-readline';

const horario = JSON.parse(readFileSync('horario.json'));
const ingles = JSON.parse(readFileSync('ingles.json'));

let date = new Date().getDay() - 1;
const diasSemana = ['Lunes', 'Martes', 'Miercoles', 'Jueves', 'Viernes'];
const aulas = ['inicio', 'L202', 'L204', 'L206', 'L208', 'L4', 'L3', 'L2', 'L1', 'L213', 'L215', 'L217', 'L218', 'L216', 'L207', 'L205', 'L203', 'L201', 'L200'];
let dia = diasSemana[date]
let curso
let bloque
let cursosIngles
let objetivo
let direccion
let distancia

/*
const port = new SerialPort({
  path: 'COM3',
  baudRate: 9600
});
const parser = port.pipe(new ReadlineParser({ delimiter: '\n' }));
*/

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
  if (objetivo === 'L5'){
    objetivo = 'L200'
  }
  if (aulas.indexOf(objetivo) <= 11){
    direccion = 'ADELANTE'
  } else{
    direccion = 'ATRAS'
  }
  if (direccion = 'ADELANTE'){
    distancia = aulas.indexOf(objetivo)
  } else{
    distancia = [aulas[0], ...aulas.slice(-7).reverse()].indexOf(objetivo)
  }
  return [objetivo, direccion]
});


function arduino(){
  port.write(direccion)
  port.write(distancia)
  let veces = 0;
  parser.on('data', (data) => {
      if (data.trim() === "LINEA") {
          veces++;
          console.log(`Va por la linea ${veces} de ${distancia}`);
          sendEvent("siguiente", null);
          if (veces === distancia){
            console.log('LLegaste a tu destino. Volviendo al inicio.')
            port.write('VOLVER')
          }
      }
      });
      parser.on('data', function(data) {
          data = data.trim();
          if (data === 'OBSTACULO') {
              console.log('Se paró porque hay un obstaculo');
          }
      });
  }

startServer()