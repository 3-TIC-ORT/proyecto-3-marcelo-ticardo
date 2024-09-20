// Código hecho con ChatGPT a modo de base para tener en cuenta cuando se haga el código verdadero
import SerialPort from 'serialport';
import ReadlineParser from '@serialport/parser-readline';
// Configura el puerto serie
const port = new SerialPort({
    path: 'COM4',
    baudRate: 9600
});
// Configura el parser para leer líneas
const parser = port.pipe(new ReadlineParser({ delimiter: '\n' }));
// Evento cuando se abre la conexión
port.on('open', function() {
    console.log('Conexión serial abierta');w
});
// Evento cuando se recibe un dato del Arduino
parser.on('data', function(data) {
    data = data.trim();
    if (data === 'llegué') {
        console.log('Notificación recibida del Arduino: Llegué');
    } else if (data === 'obstáculo adelante') {
        console.log('Notificación recibida del Arduino: Obstáculo adelante');
    } else if (data === 'obstáculo atrás') {
        console.log('Notificación recibida del Arduino: Obstáculo atrás');
    } else {
        console.log('Recibido del Arduino:', data);
    }
});
// Función para enviar instrucciones al Arduino
function enviarInstrucciones(direccion, distancia) {
    port.write(`${direccion}\n`);
    port.write(`${distancia}\n`);
}
