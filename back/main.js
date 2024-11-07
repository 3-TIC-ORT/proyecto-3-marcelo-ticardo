import { onEvent, startServer, sendEvent } from 'soquetic'
import { readFileSync } from 'fs'
import { SerialPort } from 'serialport'

const horario = JSON.parse(readFileSync('horario.json'))
const ingles = JSON.parse(readFileSync('ingles.json'))

const date = new Date().getDay() - 1
const diasSemana = ['Lunes', 'Martes', 'Miercoles', 'Jueves', 'Viernes']
const dia = diasSemana[date]

const aulas = ['inicio', 'L202', 'L204', 'L206', 'L208', 'L4', 'L3', 'L2', 'L1', 'L213', 'L215', 'L217']
const aulasInv = ['inicio', 'L200', 'L201', 'L203', 'L205', 'L207', 'L214', 'L216']

let curso, bloque, cursosIngles, objetivo, direccion, distancia, veces, motion, running, puerto

const ports = await SerialPort.list()
if (ports.length > 0) {
  puerto = ports[0].path
} else {
  console.error('No serial ports found')
}
const port = new SerialPort({
  path: puerto,
  baudRate: 9600
})
port.on('open', () => {
  console.log(`Port ${puerto} is open`)
})
port.on('error', err => {
  console.error('Error: ', err.message)
})

onEvent('bloque', data => {
  bloque = data
})

onEvent('curso', data => {
  curso = data
})

onEvent('objetivo', data => {
  objetivo = data
})

onEvent('preguntarHorario', () => {
  for (const row of horario) {
    if (row.dia === dia && row.curso === curso && row.bloque === bloque) {
      return {
        materia: row.materia,
        aula: row.aula
      }
    }
  }
})

onEvent('preguntarIngles', () => {
  cursosIngles = []
  for (const row of ingles) {
    if (row.dia === dia && row.bloque === bloque) {
      cursosIngles.push({ nivel: row.nivel, aula: row.aula })
    }
  }
  return cursosIngles
})
onEvent('aulaIngles', () => {
  return objetivo
})

onEvent('mapa', () => {
  if (objetivo === 'L5') {
    objetivo = 'L200'
  }
  if (aulas.includes(objetivo)) {
    direccion = 'ADELANTE'
    distancia = aulas.indexOf(objetivo)
  } else if (aulasInv.includes(objetivo)) {
    direccion = 'ATRAS'
    distancia = aulasInv.indexOf(objetivo)
  }
  veces = 0
  motion = 'yendo'
  running = true

  arduino()
  return [objetivo, direccion]
})

async function arduino () {
  if (!running) return
  port.write(`${direccion}\n`)

  const onDataHandler = data => {
    if (!running) return
    const message = data.toString().trim()
    if (message === 'LINEA') {
      console.log(`Va por la linea ${veces} de ${distancia}`)
      if (motion === 'yendo') {
        veces++
        sendEvent('linea', 'siguiente')
        if (veces === distancia) {
          motion = 'volviendo'
          direccion = direccion === 'ADELANTE' ? 'ATRAS' : 'ADELANTE'
          sendEvent('llegada', null)
          port.write(`${direccion}\n`)
        }
      } else if (motion === 'volviendo') {
        veces--
        sendEvent('linea', 'anterior')
        if (veces === 0) {
          port.write('LLEGASTE\n')
          sendEvent('llegadaInicio', null)
          port.removeListener('data', onDataHandler)
          running = false
          return
        }
      }
    }
  }

  port.on('data', onDataHandler)
}

startServer()
