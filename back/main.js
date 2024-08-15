const fs = require('fs');

const horario = JSON.parse(fs.readFileSync('horario.json'));
const ingles = JSON.parse(fs.readFileSync('ingles.json'));

let date = new Date().getDay() - 1;
const diasSemana = ['Lunes', 'Martes', 'Miércoles', 'Jueves', 'Viernes'];
let dia = diasSemana[date];

let curso = 'B';
let bloque = 3;

horario.forEach((row) => {
  if (row.dia === dia && row.curso === curso && row.bloque === bloque) {
    if (row.aula === 'E') {
      console.log('Tenés Ed. Física');
    } else if (row.aula === '0') {
      console.log('No tenés ninguna materia en este bloque');
    } else if (row.aula === 'I') {
      ingles.forEach((inglesRow) => {
        if (inglesRow.dia === dia && inglesRow.bloque === bloque) {
          console.log(`El nivel ${inglesRow.nivel} tiene en el aula ${inglesRow.aula}`);
        }
      });
    } else {
      console.log(`Tenés ${row.materia} en el Aula ${row.aula}`);
    }
  }
});