<nav class="navbar sticky-top navbar-expand-lg navbar-dark bg-dark">
  <a class="navbar-brand" href="#">LOGO</a>
  <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
    <span class="navbar-toggler-icon"></span>
  </button>

  <div class="collapse navbar-collapse" id="navbarSupportedContent">
    <ul class="navbar-nav mr-auto">
      <li class="nav-item active">
        <a href="index.php"><button class="btn btn-info" style="margin-right:10px;">Gérer les noeuds</button></a>
        <!-- <a class="nav-link" href="#">Gérer les noeuds <span class="sr-only">(current)</span></a> -->
      </li>
      <li class="nav-item">
        <a href="leaflet_from_local_storage.php"><button id="btn_go_to_map" class="btn btn-info" style="margin-right:10px;">Afficher la carte</button></a>
        <!-- <a class="nav-link" href="#">Afficher la carte</a> -->
      </li>
      <li class="nav-item">
        <button id="import_btn" class="btn btn-info" style="margin-right:10px;">Importer</button><input hidden type="file" id="input_import">
      </li>
      <li class="nav-item">
        <button id="export_btn" class="btn btn-info" style="margin-right:10px;">Exporter</button>
      </li>
      <li id="best_solution" class="nav-item align-self-center" style="color:#fff;font-size: 23px;">

      </li>
    </ul>
    <ul class="nav justify-content-end">
      <li class="nav-item">
        <a href="#"></a><button class="btn btn-info" style="margin-right:10px;">A propos</button></a>
  <!-- <a class="nav-link" href="#">A propos</a> -->
      </li>
    </ul>
  </div>
</nav>

<script type="text/javascript">
 solution_cost = load_data_local_storage("best_solution");
 console.log("solution_cost")
 console.log(solution_cost)
 if(solution_cost){
   console.log("show")
   $("#best_solution").text(`Meilleure solution : ${solution_cost.toFixed(2)} m`).show();
 }else{
   $("#best_solution").hide();
 }
</script>
