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

onEvent("bloque", (data) => {
  bloque = Number(data.bloque)
});

onEvent("curso", (data) => {
  curso = data.curso
});

onEvent("preguntarHorario", () => {
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
});

onEvent("preguntarIngles", () => {
  cursosIngles = ""
  for (const row of ingles) { 
    if (row.dia === dia && row.bloque === bloque) {
      cursosIngles = cursosIngles + `${row.nivel},${row.aula};`;
    }
  }
  return cursosIngles
});

startServer()