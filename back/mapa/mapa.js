import { onEvent, startServer } from "soquetic";
import { readFileSync } from 'fs';
import { SerialPort } from 'serialport';
import { ReadlineParser } from '@serialport/parser-readline';

const aulas = ['inicio', 'L202', 'L204', 'L206', 'L208', 'L4', 'L3', 'L2', 'L1', 'L213', 'L215', 'L217', 'L218', 'L216', 'L207', 'L205', 'L203', 'L201', 'L5', 'L200'];

const port = new SerialPort({
    path: 'COM3',
    baudRate: 9600
  });

const parser = port.pipe(new ReadlineParser({ delimiter: '\n' }));

let objetivo = 'L213'

onEvent("mapa", () => {
    let veces = 0;
    parser.on('data', (data) => {
        if (data.trim() === "Apretado") {
            veces++;
            console.log(`El botón se apretó ${veces} veces.`);
        }
        });
});

startServer()