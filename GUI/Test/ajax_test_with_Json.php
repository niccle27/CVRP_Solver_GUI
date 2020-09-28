<html>
  <head>
    <script type="text/javascript" src="Assets/JQuery/jquery-3.4.1.min.js"></script>
  </head>
  <body>

  </body>
  <div id="myId">

  </div>
  <script>
   function getMatrix(listCoordinates) {
     let request = new XMLHttpRequest();
     request.open('POST', "https://api.openrouteservice.org/v2/matrix/driving-car", false);
     request.setRequestHeader('Accept', 'application/json, application/geo+json, application/gpx+xml, img/png; charset=utf-8');
     request.setRequestHeader('Content-Type', 'application/json');
     request.setRequestHeader('Authorization', '5b3ce3597851110001cf6248703754048738463ba206b43ed13658a3');
     var bodyObject = {};
     bodyObject["locations"]=listCoordinates;
     /* const body = JSON.stringify(bodyObject); */
     /* console.log(body) */
     request.send(JSON.stringify(bodyObject));
     if (request.status === 200) {
       responseObject = JSON.parse(request.responseText);
       /* console.log(responseObject) */

       return responseObject;
     }
     else{
       return null;
     }
   }
   responseObject = getMatrix([[9.70093,48.477473],[9.207916,49.153868],[37.573242,55.801281],[115.663757,38.106467]])
   demands = [32,6,25,9];
   inputCProg = {}
   if ("durations" in responseObject){
     inputCProg["distances"] = responseObject["durations"];
   }
   inputCProg["demands"] = demands;
   console.log(inputCProg)
   mJson = '{"distances":[[0, 12, 11, 7, 10, 10, 9, 8, 6, 12],[12, 0, 8, 5, 9, 12, 14, 16, 17, 22],[11, 8, 0, 9, 15, 17, 8, 18, 14, 22],[7, 5, 9, 0, 7, 9, 11, 12, 12, 17],[10, 9, 15, 7, 0, 3, 17, 7, 15, 18],[10, 12, 17, 9, 3, 0, 18, 6, 15, 15],[9, 14, 8, 11, 17, 18, 0, 16, 8, 16],[8, 16, 18, 12, 7, 6, 16, 0, 11, 11],[6, 17, 14, 12, 15, 15, 8, 11, 0, 10],[12, 22, 22, 17, 18, 15, 6, 11, 10, 0]],"demands": [10, 15, 18, 17, 3, 5, 9, 4, 6]}';
   mObj = JSON.parse(mJson);
   distances = mObj["distances"];
   demands = mObj["demands"];
   /* console.log(distances); */
   /* console.log(demands); */
   var fusionDict = {};
   fusionDict["demands"] = mObj["demands"];
   fusionDict["distances"] = mObj["distances"];
   var jsonString = JSON.stringify(inputCProg);
   console.log(jsonString)
   var jsonFromCProg = null;
   $.ajax({
     method: "POST",
     url: "test_CW_Exec.php",
     data: {json: jsonString}
   })
    .done(function( msg ) {
      $("#myId").html(msg)
      jsonFromCProg = JSON.parse(msg);
      console.log(jsonFromCProg)
    });
  </script>
</html>
