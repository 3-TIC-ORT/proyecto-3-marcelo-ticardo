import { onEvent, startServer } from "soquetic";
import { readFileSync } from 'fs';

const horario = JSON.parse(readFileSync('horario.json'));
const ingles = JSON.parse(readFileSync('ingles.json'));

let date = new Date().getDay() - 1;
const diasSemana = ['Lunes', 'Martes', 'Miercoles', 'Jueves', 'Viernes'];
let dia = diasSemana[date]
let curso
let bloque
let cursosIngles
let objetivo

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
})

startServer()