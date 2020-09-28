<style>
 .btn{margin-bottom:5px;border-radius: 8px;}
</style>
<div class="container">
  <div class="row">
    <div class="col-sm-4">
      <div class="btn-group-vertical" >
        <button type="button" class="btn btn-primary" data-toggle="modal" data-target="#modal_client_action" data-action="Ajouter_client">
          Ajouter un point de passage
        </button>
        <button id="compute_btn" type="button" class="btn btn-primary">
          Calcul trajet
        </button>
        <button id="clear_map_btn" type="button" class="btn btn-primary">
          Effacer les annotations
        </button>
        <button id="clear_list_btn" type="button" class="btn btn-primary">
          Vider la liste
        </button>
      </div>
    </div>
    <div class="col-sm-8">
      <form class="card p-3 bg-light m-5" >
        <div class="form-row">
          <div class="form-group col-md-6">
            <label for="depot_latitude">Latitude du dépot</label>
            <input id="depot_latitude" type="number" min="-90"
                   max="90" step="0.000001" class="form-control">
          </div>
          <div class="form-group col-md-6">
            <label for="depot_longitude">Longitude du dépot</label>
            <input id="depot_longitude" type="number" min="-180"
                   max="180" step="0.000001" class="form-control">
          </div>
        </div>
      </form>
    </div>
  </div>
</div>

<!-- <form class="form-inline">
     <div class="form-group">
     <label for="inputPassword6">Password</label>
     <input type="password" id="inputPassword6" class="form-control mx-sm-3" aria-describedby="passwordHelpInline">
     <small id="passwordHelpInline" class="text-muted">
     Must be 8-20 characters long.
     </small>
     </div>
     </form> -->
<form class="card p-3 bg-light m-5" >
    <div class="form-group">
      <label for="n_vehicles">Nombre de véhicules </label>
      <input type="number" class="" id="n_vehicles" min="1" value="3">
    </div>
    <div class="form-group">
      <label for="vehicule_max_capacity" class="form-check-label">Capacité maximum par véhicule</label>
      <input type="number" class="" id="vehicule_max_capacity" min="1" value="30">
    </div>
    <div class="form-group">
      <label for="sel_heuristic">Algorithme heuristique</label>
      <select id="sel_heuristic" class="form-check-label"">
        <option selected>CW</option>
      </select>
    </div>
    <div class="form-check">
      <input type="checkbox" class="form-check-input" id="use_meta_cb">
      <label class="form-check-label" for="use_meta_cb">Activer meta</label>
    </div>
    <div class="form-group">
      <label for="sel_meta">Algorithme metaheuristique</label>
      <select id="sel_meta" class="form-check-label"">
        <option selected>SA</option>
      </select>
    </div>
</form>
<form class="card p-3 bg-light m-5" >
  <div class="form-group">
    <label for="temp_init_input">Temperature initiale </label>
    <input type="number" class="" id="temp_init_input" min="1" value="5000">
  </div>
  <div class="form-group">
    <label for="temp_final_input">Temperature finale </label>
    <input type="number" class="" id="temp_final_input" min="0.0001" step="0.0001" value="0.001">
  </div>
  <div class="form-group">
    <label for="alpha">Alpha </label>
    <input type="number" class="" id="alpha" min="0.0001" max="0.9999" step="0.0001" value="0.999">
  </div>
  <div class="form-group">
    <label for="beta">Beta </label>
    <input type="number" class="" id="beta" min="1" step="0.0001" value="1.01">
  </div>
  <div class="form-group">
    <label for="n_iter_at_temp_init">Nombre d'interations par seuil initial </label>
    <input type="number" class="" id="n_iter_at_temp_init" min="1"  value="5">
  </div>
  <div class="form-group">
    <label for="n_iter_without_impr">Nombre d'interations sans améliorations </label>
    <input type="number" class="" id="n_iter_without_impr" min ="1" value="10000000">
  </div>
</form>
