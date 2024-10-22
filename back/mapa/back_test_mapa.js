import { onEvent, startServer, sendEvent } from "soquetic";
import { readFileSync } from 'fs';
import { SerialPort } from 'serialport';
import { ReadlineParser } from '@serialport/parser-readline';

const aulas = ['inicio', 'L202', 'L204', 'L206', 'L208', 'L4', 'L3', 'L2', 'L1', 'L213', 'L215', 'L217', 'L218', 'L216', 'L207', 'L205', 'L203', 'L201', 'L200'];
const aulas_inv = ['inicio', 'L200', 'L201', 'L203', 'L205', 'L207', 'L216', 'L218']

const port = new SerialPort({
    path: 'COM13',
    baudRate: 9600
  });

let objetivo = "L1"
let direccion
let distancia

onEvent("mapa", ()=>{
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
      distancia = aulas_inv.indexOf(objetivo);
    }
    arduino();
    return [objetivo, direccion]
  });
  
  // Hay que probar esto
  async function arduino(){
    port.write(`${direccion}\n`);
    let veces = 0;
    let motion = "yendo"
    port.on('data', (data) => {
        if (data.toString().trim() === "LINEA") {
          if (motion === "yendo"){
            veces++;
            console.log(`Va por la linea ${veces} de ${distancia}`);
            sendEvent("linea", "siguiente");
            if (veces === distancia){
              console.log('LLegaste a tu destino. Volviendo al inicio.');
              port.write('VOLVER\n'); 
              motion = "volviendo";
              if (direccion === 'ADELANTE'){ // invertir la dirección
                direccion = 'ATRAS';
              }
              else if (direccion === "ATRAS"){
                direccion = 'ADELANTE';
              }
              port.write(`${direccion}\n`);
          } else if (motion==="volviendo"){
            veces--
            console.log(`Va por la linea ${veces} de ${distancia}`);
            sendEvent("linea", "anterior")
            if (veces === 0){
              console.log('Llegaste al inicio de vuelta.');
              port.write('LLEGASTE\n'); 
            }}
          }
        }
        });
  }
  
  
  startServer();