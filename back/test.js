import { SerialPort } from 'serialport';
import { ReadlineParser } from '@serialport/parser-readline';
import { createInterface } from 'readline';

// Configura el puerto serial
const port = new SerialPort({
  path: 'COM10',
  baudRate: 9600,  // Cambia a la velocidad que necesites
  autoOpen: false,
});

// Parser para leer líneas completas (hasta salto de línea)
const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }));

// Abrir puerto
port.open((err) => {
  if (err) {
    return console.log('Error al abrir el puerto: ', err.message);
  }
  console.log('Puerto serial abierto en COM10');
});

// Cuando llega un dato
parser.on('data', (data) => {
  console.log('Recibido:', data);
});

// Para leer de la consola y enviar mensajes al puerto serial
const rl = createInterface({
  input: process.stdin,
  output: process.stdout,
});

console.log('Escribe un mensaje y presiona Enter para enviarlo:');

rl.on('line', (input) => {
  if (port.isOpen) {
    port.write(input + '\r\n', (err) => {
      if (err) {
        console.log('Error al enviar:', err.message);
      } else {
        console.log('Enviado:', input);
      }
    });
  } else {
    console.log('El puerto no está abierto aún');
  }
});
