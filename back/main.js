import { onEvent, startServer } from "soquetic";
import { readFileSync } from 'fs';

const horario = JSON.parse(readFileSync('horario.json'));
const ingles = JSON.parse(readFileSync('ingles.json'));

let date = new Date().getDay() - 1;
const diasSemana = ['Lunes', 'Martes', 'Miércoles', 'Jueves', 'Viernes'];
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

startServer()