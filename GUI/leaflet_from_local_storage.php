<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8">
    <meta name="author" content="Clément NICOLAS">
    <link rel="stylesheet" href="Assets/Bootstrap/bootstrap.min.css">
    <link rel="stylesheet" href="Assets/leaflet/leaflet.css" type="text/css">
    <style>
        #map{
            height: 100%;
            width: 100%;
            position: fixed;
        }
    </style>
    <title>OpenVRP</title>
  </head>
  <body>
    <script type="text/javascript" src="Assets/v6.1.1-dist/ol.js"></script>
    <script type="text/javascript" src="cycle.js"></script>
    <script type="text/javascript" src="utils.js"></script>
    <script type="text/javascript" src="Assets/JQuery/jquery-3.4.1.min.js"></script>

    <?php include($_SERVER['DOCUMENT_ROOT'].'/nav.php') ?>
    <div class="row">
      <div class="col-sm-12">
        <div id="map"></div>
      </div>
    </div>
    <script type="text/javascript" src="./randomColor.js"></script>
    <script type="text/javascript" src="Assets/Popper/popper.min.js"></script>
    <script type="text/javascript" src="Assets/Bootstrap/bootstrap.min.js"></script>
    <script type="text/javascript" src="Assets/leaflet/leaflet.js"></script>
    <script type="text/javascript" src="./../Assets/leaflet/Plugin/Polyline.encoded.js"></script>
    <script>
     var greenIcon = L.icon({
       iconUrl: 'depot_img.png',
       iconSize:     [60, 86], // size of the icon
       iconAnchor:   [29, 86], // point of the icon which will correspond to marker's location
       popupAnchor:  [0, -80] // point from which the popup should open relative to the iconAnchor
     });

     function getRandomColor() {
       var letters = '0123456789ABCDEF';
       var color = '#';
       for (var i = 0; i < 6; i++) {
         color += letters[Math.floor(Math.random() * 16)];
       }
       return color;
     }

     list_client_geojson = load_data_local_storage("list_client_geojson");
     /* console.log(list_client_geojson); */
     list_vehicle_cycles = load_data_local_storage("list_vehicle_cycles");
     depot = load_data_local_storage("depot");
     var center_coord = depot!=null?[depot.latitude, depot.longitude]:[51.505, -0.09];
     var map = L.map('map', {
       center: center_coord,
       zoom: 13
     });
     /* draw depot */
     L.marker([depot.latitude, depot.longitude], {icon: greenIcon}).addTo(map).bindPopup("<b>Dépot</b>");;
     /* var map = L.map('map'); */

     L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
       attribution: '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors'
     }).addTo(map);

     function onEachFeature(feature, layer) {
       // does this feature have a property named popupContent?
       if (feature.properties && feature.properties.popupContent) {
         layer.bindPopup(feature.properties.popupContent);
       }
     }

     if (list_vehicle_cycles){
       var cycles = L.featureGroup();

       cycles.addTo(map);

       list_vehicle_cycles.forEach(function (item, index) {
         var polyline_layer = L.Polyline.fromEncoded(item.polyline,
                                                     {weight: 3,
                                                      color: randomColor(),
                                                      onEachFeature:onEachFeature}).toGeoJSON();
         /* display time or distance */
         polyline_layer["properties"]= {"popupContent": `<strong>Véhicule ${index+1}:</strong><br/> - Temps: ${item.duration} seconds<br/> - Distance:${item.distance} m `}
         L.geoJSON(polyline_layer,{weight: 5,
                                   color: randomColor(),
                                   onEachFeature:onEachFeature}).addTo(cycles);
         /* polyline_layer.addTo(cycles); */
         console.log(polyline_layer);
       })
       map.fitBounds(cycles.getBounds())
     }


     /* a = JSON.parse(list_circuit_geojson[0]); */
     /* b = JSON.parse(list_circuit_geojson[1]); */
     /* c = JSON.parse(list_circuit_geojson[2]); */
     /* v = [a, b, c]; */
     /* console.log(a); */
     /* console.log(b); */
     /* list_trajets_layer = L.geoJSON(list_circuit_geojson).addTo(map); */
     if(list_client_geojson){
       list_clients_layer = L.geoJSON(list_client_geojson,{onEachFeature:onEachFeature}).addTo(map);
       console.log(list_clients_layer);
     }



    </script>
  </body>
</html>
