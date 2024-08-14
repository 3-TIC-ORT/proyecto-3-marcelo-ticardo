const fs = require('fs');
const csv = require('csv-parser');

let date = new Date().getDay() - 1;
const diasSemana = ['Lunes', 'Martes', 'Miércoles', 'Jueves', 'Viernes'];
let dia = diasSemana[date];

let curso = 'B'
let bloque = '1'

fs.createReadStream('horario.csv')
  .pipe(csv())
  .on('data', (row) => {
    if (row.dia === dia && row.curso === curso && row.bloque === bloque && row.aula === 'E'){
      console.log('Tenés Ed. Física')
    }
    else if (row.dia === dia && row.curso === curso && row.bloque === bloque && row.aula === '0'){
      console.log('No tenés ninguna materia en este bloque')
    }
    else if (row.dia === dia && row.curso === curso && row.bloque === bloque && row.aula === 'I'){
      
      fs.createReadStream('ingles.csv')
      .pipe(csv())
      .on('data', (row) => {
        if (row.dia === dia && row.bloque === bloque){
          console.log(`El nivel ${row.nivel} tiene en el aula ${row.aula}`)
        }
      }
      )
    }
    else if (row.dia === dia && row.curso === curso && row.bloque === bloque) {
      console.log(`Tenés ${row.materia} en el Aula ${row.aula}`);
    }
  })