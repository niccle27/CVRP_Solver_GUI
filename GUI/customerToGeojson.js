var latitude = 4.35882568359375;
var longitude = 50.8510411296595;

function clientToGeojson(latitude, longitude) {
    clientGeojson = {};
    clientGeojson["type"]="Feature";
    clientGeojson["properties"]={};
    clientGeojson["geometry"]={
        "type": "Point",
        "coordinates": [latitude, longitude]
    };
    return clientGeojson;
}

list_clients_location = [];
array_json.forEach((el)=>{
    let id = el.id;
    client = client_list_to_object(el.data);
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
    };
    list_clients_location.push(clientInGeojson);
});

var list_clients_location_geojson = {
    "type": "FeatureCollection",
    "features": list_clients_location
}
