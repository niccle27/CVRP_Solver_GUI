<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8">
    <meta nom="author" content="Clément NICOLAS">
    <link rel="stylesheet" href="Assets/Bootstrap/bootstrap.min.css">
    <link rel="stylesheet" href="Assets/FontAwesome/css/all.min.css" type="text/css"/>
    <link rel="stylesheet" href="Assets/Bootstrap-table/bootstrap-table.min.css" type="text/css"/>
    <title>OpenVRP</title>
    <style>
     .edit {color:#ffc42e !important;}
     .edit:hover {color:#a88220 !important;}
     .delete {color:#ff2e2e !important;}
     .delete:hover {color:#a82020 !important;}
    </style>
  </head>
  <body>
    <script type="text/javascript" src="Assets/JQuery/jquery-3.4.1.min.js"></script>
    <script type="text/javascript" src="cycle.js"></script>
    <script type="text/javascript" src="utils.js"></script>

    <?php include($_SERVER['DOCUMENT_ROOT'].'/nav.php') ?>
    <div id="mainContent" class="row">

      <div class="col-sm-8">
        <form>
          <table id="table_clients" class="table table-dark table-hover">
            <thead>
              <tr>
                <th></th>
                <th>Nom</th>
                <th>Quantité</th>
                <th>Latitude</th>
                <th>Longitude</th>
                <th>Editer</th>
                <th>Supprimer</th>
              </tr>
            </thead>
            <tbody>
            </tbody>
        </form>
        </table>
      </div>

      <div class="col-sm-4">
        <?php include($_SERVER['DOCUMENT_ROOT'].'/sidebar.php') ?>
      </div>
      <script type="text/javascript" src="Assets/Popper/popper.min.js"></script>
      <script type="text/javascript" src="Assets/Bootstrap/bootstrap.min.js"></script>
      <!-- Modal -->
      <?php include($_SERVER['DOCUMENT_ROOT'].'/customerForm.php') ?>
      <script type="text/javascript" src="./default_values.js"></script>
      <script type="text/javascript" src="./GUI.js"></script>
      <!--<script type="text/javascript" src="./api.js"></script>-->
  </body>
</html>
