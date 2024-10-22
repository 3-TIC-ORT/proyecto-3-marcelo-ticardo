
const aulas = ['inicio', 'L202', 'L204', 'L206', 'L208', 'L4', 'L3', 'L2', 'L1', 'L213', 'L215', 'L217'];
const aulas_inv = ['inicio', 'L200', 'L201', 'L203', 'L205', 'L207', 'L216', 'L218']


let objetivo
let direccion
fetchData("mapa", (data) => {
    console.log(data)
    objetivo = data[0]
    direccion = data[1]
    document.getElementById("inicio_u").setAttribute("visibility", "visible")
    if (direccion === 'ADELANTE'){
        for (let i=1; i <= aulas.indexOf(objetivo); i++){
            document.getElementById(aulas[i]).setAttribute("visibility", "visible")
        }
    }
    else if (direccion === 'ATRAS'){
        for (let i=1; i <= aulas_inv.indexOf(objetivo); i++){
            document.getElementById(aulas_inv[i]).setAttribute("visibility", "visible")
        }
    }
    });

    let i = 0


receive("linea", (data) =>{
    console.log(data)
    if (data === "anterior"){
        if (direccion === "ADELANTE"){
            direccion = "ATRAS"
        }
        else{
            direccion = "ADELANTE"
        }
    }
    console.log(direccion)
    if (data === "siguiente"){
        if(direccion === "ADELANTE"){
            document.getElementById(`${aulas[i]}_u`).setAttribute("visibility", "hidden")
            i++
            document.getElementById(`${aulas[i]}_u`).setAttribute("visibility", "visible")
        }
        if (direccion === "ATRAS"){
            document.getElementById(`${aulas_inv[i]}_u`).setAttribute("visibility", "hidden")
            i++
            document.getElementById(`${aulas_inv[i]}_u`).setAttribute("visibility", "visible")
        }
    if (data === "anterior"){
        if (direccion === "ADELANTE"){
            document.getElementById(`${aulas_inv[i]}_u`).setAttribute("visibility", "hidden")
            i--
            document.getElementById(`${aulas_inv[i]}_u`).setAttribute("visibility", "visible")
        }
        if (direccion === "ATRAS"){
            console.log("hola??")
            document.getElementById(`${aulas[i]}_u`).setAttribute("visibility", "hidden")
            i--
            document.getElementById(`${aulas[i]}_u`).setAttribute("visibility", "visible")
        }
    }
    }
})