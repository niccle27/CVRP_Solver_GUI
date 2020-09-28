

<html>
  <head>
    <script type="text/javascript" src="Assets/JQuery/jquery-3.4.1.min.js"></script>
  </head>
  <body>

  </body>
  <div id="myId">

  </div>
  <script>
   $.ajax({
     method: "POST",
     url: "test.php",
     data: { name: "John", location: "Boston" ,children:[1,2,3,4]}
   })
    .done(function( msg ) {
      $("#myId").html(msg)
    });
  </script>
</html>
