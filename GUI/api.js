var resultCompute = null;
drawingCircuits = [];
list_clients_location_geojson={};

function get_coordinate_list_per_vehicle(vehicle_id){
    var listCoord = [];
    listCoord.push(getLongLatFromClientId(0));
    for(var customer_id=0; customer_id<vehicle_customer_list[vehicle_id].length;customer_id++){
        listCoord.push(getLongLatFromClientId(vehicle_customer_list[vehicle_id][customer_id]));
        /* console.log(getLongLatFromClientId(vehicle_customer_list[vehicle_id][customer_id])); */
    };
    listCoord.push(getLongLatFromClientId(0));
    return listCoord
}

function request_vehicle_cycle(listCoord){
    console.log("function request_vehicle_cycle")
    var body={};
    body["coordinates"] = listCoord;
    let request = new XMLHttpRequest();
    request.open('POST', "https://api.openrouteservice.org/v2/directions/driving-car/geojson", false);  // false makes the request synchronous
    request.setRequestHeader('Accept', 'application/json, application/geo+json, application/gpx+xml, img/png; charset=utf-8');
    request.setRequestHeader('Content-Type', 'application/json');
    request.setRequestHeader('Authorization', '5b3ce3597851110001cf6248703754048738463ba206b43ed13658a3');
    console.log(JSON.stringify(body));
    request.send(JSON.stringify(body));
    if (request.status === 200) {
        console.log(request.responseText);
        return request.responseText
    }
    else{
        console.log("request status =" + request.status)
        return null;
    }
}

function client_to_geojson(client) {
    var clientInGeojson = {
        "type": "Feature",
        "properties": {},
        "geometry": {
            "type": "Point",
            "coordinates": [
                client.latitude,
                client.longitude
            ]
        }
    }
    return clientInGeojson;
}


function get_circuit_path(msg) {
    vehicle_customer_list=JSON.parse(msg)["vehicles"];
    console.log("vehicle_customer_list");
    console.log(vehicle_customer_list);
    drawingCircuits=[];
    /* vehicle_customer_list=msg; */
    for(var vehicle_id=0; vehicle_id<vehicle_customer_list.length;vehicle_id++){
        listCoord=get_coordinate_list_per_vehicle(vehicle_id);
        response=request_vehicle_cycle(listCoord)
        drawingCircuits.push(response);
    };
    list_clients_location = [];
    array_json.forEach((el)=>{
        let id = el.id;
        client = client_list_to_object(el.data);
        clientInGeojson=client_to_geojson(client)
        list_clients_location.push(clientInGeojson);
        console.log("add");
        console.log(list_clients_location)
    });
    list_clients_location_geojson = {
        "type": "FeatureCollection",
        "features": list_clients_location
    };
    /* console.log(JSON.stringify(list_clients_location_geojson)); */
    /* console.log(drawingCircuits); */
    window.localStorage.setItem('list_clients_location_geojson', JSON.stringify(list_clients_location_geojson));
    window.localStorage.setItem('list_circuit_geojson', JSON.stringify(drawingCircuits));
}

$(document).ready(function(){
    $("#compute_btn").click(function(){
        console.log("click")
        $.ajax({
            method: "POST",
            url: "VRP_compute.php",
            data: { json: "data"}
        })
            .done(get_circuit_path);
    });
});

function getLongLatFromClientId(id){
    var client = array_json.find(el => el.id == id);
    liste = client.data;
    return[liste[2], liste[3]];
}
