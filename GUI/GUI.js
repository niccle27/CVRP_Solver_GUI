class Coordinates {
  constructor(long, lat) {
    this.long = long;
    this.lat = lat;
  }
}

class Customer {
  constructor(name, quantity, latitude, longitude, city, street, num, post_code, country, isSelected) {
    this.name = name;
    this.quantity = quantity;
    this.latitude = latitude;
    this.longitude = longitude;
    this.city = city;
    this.street = street;
    this.num = num;
    this.post_code = post_code;
    this.country = country;
    this.isSelected = true;
  }

  tolist(){
    let data = [this.name,
                parseInt(this.quantity),
                parseFloat(this.latitude),
                parseFloat(this.longitude),
                this.city,
                this.street,
                parseInt(this.num),
                parseInt(this.post_code),
                this.country];
    return data;
  }

  get_coordinates(){
    return[this.longitude, this.latitude];
  }

  fromlist(data){
    this.name = data[0];
    this.quantity = data[1];
    this.latitude = data[2];
    this.longitude = data[3];
    this.city = data[4];
    this.street = data[5];
    this.num = data[6];
    this.post_code = data[7];
    this.country = data[8];
    // this.isSelected = data[9];
  }

  getadress(){
    return `${this.street} ${this.num} ${this.city} ${this.post_code} ${this.country}`;
  }

  to_geojson(client) {
    var geojson = {
      "type": "Feature",
      "properties": {
        "popupContent": `<strong>${this.name}</strong> <br/>
                                  Ville: ${this.city} <br/>
                                  Rue: ${this.street}, n° ${this.num} <br/>
                                  Code postal: ${this.post_code} <br/>
                                  Pays: ${this.country} <br/>
                                  Quantité: ${this.quantity}`
      },
      "geometry": {
        "type": "Point",
        "coordinates": [
          this.longitude,
          this.latitude
        ]
      }
    };
    return geojson;
  }

  set_isSelected(isSelected){
    this.isSelected = isSelected;
  }

  toggle_isSelected(){
    this.isSelected = !this.isSelected;
    return this.isSelected;
  }
}


class Model {
  constructor() {
      this.dict_id_customer=load_data_local_storage("list_customer");
      this.max_capacity_per_vehicle=load_data_local_storage("max_capacity_per_vehicle");
      this.n_vehicles = load_data_local_storage("n_vehicles");
      this.heuristic = load_data_local_storage("heuristic");
      this.use_meta = load_data_local_storage("use_meta");
      this.meta = load_data_local_storage("meta");
      this.meta_parameter = load_data_local_storage("meta_parameter");
      this.depot = load_data_local_storage("depot");
      
      if(this.heuristic == null){
          this.heuristic = "CW";
      }
      if(this.meta == null){
          this.meta = "SA";
      }
      if(this.use_meta == null){
          this.use_meta = true;
      }
      if(this.meta_parameter == null){
          this.meta_parameter = {temp_init: 5000,
                                 temp_final: 0.001,
                                 alpha: 0.999,
                                 beta: 1.01,
                                 n_iter_at_temp_init: 5,
                                 n_iter_without_impr: 10000000,
                                 low_cost_threshold: 0};
      }
      if(this.depot == null){
          this.depot = {
              "latitude": 50.851041,
              "longitude": 4.358825
          };
      }
      // console.log(test);
      if (this.dict_id_customer == null) {
          this.dict_id_customer=[];
          this.set_example();
      }
      if(this.max_capacity_per_vehicle == null){
          this.max_capacity_per_vehicle = 30;
      }
      if(this.n_vehicles == null){
          this.n_vehicles = 3;
      }
      this.save_model_to_local_storage();
  }

    set_example(){
        // this.max_capacity_per_vehicle = 30;
        this.dict_id_customer = [
            // {
            //     "id": 0,
            //     "isSelected": true,
            //     "data": [
            //         "Dépot",
            //         13,
            //         50.8510411296595,
            //         4.35882568359375,
            //         "Charleroi",
            //         "rue de Dampremy",
            //         40,
            //         6000,
            //         "Belgium"
            //     ]
            // },
            {
                "id": 1,
                "isSelected": true,
                "data": [
                    "Client 1",
                    13,
                    51.05348088381823,
                    3.856201171875,
                    "Charleroi",
                    "rue de Dampremy",
                    40,
                    6000,
                    "Belgium"
                ]
            },
            {
                "id": 2,
                "isSelected": true,
                "data": [
                    "Client 2",
                    13,
                    51.04139389812637,
                    3.41949462890625,
                    "Charleroi",
                    "rue de Dampremy",
                    40,
                    6000,
                    "Belgium"
                ]
            },
            {
                "id": 3,
                "isSelected": true,
                "data": [
                    "Client 3",
                    13,
                    50.84930707388861,
                    3.7188720703125,
                    "Charleroi",
                    "rue de Dampremy",
                    40,
                    6000,
                    "Belgium"
                ]
            },
            {
                "id": 4,
                "isSelected": true,
                "data": [
                    "Client 4",
                    13,
                    50.83369767098071,
                    5.1470947265625,
                    "Charleroi",
                    "rue de Dampremy",
                    40,
                    6000,
                    "Belgium"
                ]
            },
            {
                "id": 5,
                "isSelected": true,
                "data": [
                    "Client 5",
                    13,
                    51.14317120049778,
                    5.45745849609375,
                    "Charleroi",
                    "rue de Dampremy",
                    40,
                    6000,
                    "Belgium"
                ]
            },
            {
                "id": 6,
                "isSelected": true,
                "data": [
                    "Client 6",
                    13,
                    51.2928411273273,
                    4.8394775390625,
                    "Charleroi",
                    "rue de Dampremy",
                    40,
                    6000,
                    "Belgium"
                ]
            },
            {
                "id": 7,
                "isSelected": true,
                "data": [
                    "Client 7",
                    13,
                    50.306884231551166,
                    4.3121337890625,
                    "Charleroi",
                    "rue de Dampremy",
                    40,
                    6000,
                    "Belgium"
                ]
            },
            {
                "id": 8,
                "isSelected": true,
                "data": [
                    "Client 8",
                    13,
                    49.27138884351881,
                    4.0264892578125,
                    "Charleroi",
                    "rue de Dampremy",
                    40,
                    6000,
                    "Belgium"
                ]
            },
            {
                "id": 9,
                "isSelected": true,
                "data": [
                    "Client 9",
                    13,
                    49.742231602580716,
                    4.72412109375,
                    "Charleroi",
                    "rue de Dampremy",
                    40,
                    6000,
                    "Belgium"
                ]
            }
        ];
  }
    set_max_capacity_per_vehicle(val){
        this.max_capacity_per_vehicle = val;
        save_data_local_storage("max_capacity_per_vehicle", this.max_capacity_per_vehicle);
        // this.save_model_to_local_storage();
    }

    set_n_vehicles(val){
        this.n_vehicles = val;
        save_data_local_storage("n_vehicles", this.n_vehicles);
        // this.save_model_to_local_storage();
    }
    
    set_heuristic(val){
        this.heuristic = val;
        save_data_local_storage("heuristic", this.heuristic);
        // this.save_model_to_local_storage();
    }

    set_use_meta(val){
        this.use_meta = val;
        save_data_local_storage("use_meta", this.use_meta);
        // this.save_model_to_local_storage();
    }
    
    set_meta(val){
        this.meta = val;
        save_data_local_storage("meta", this.meta);
        // this.save_model_to_local_storage();
    }

    set_meta_parameter(val){
        this.depot = val;
        save_data_local_storage("depot", this.depot);
        // this.save_model_to_local_storage();
    }
    
    set_meta_parameter(val){
        this.meta_parameter = val;
        save_data_local_storage("meta_parameter", this.meta_parameter);
        // this.save_model_to_local_storage();
    }

    set_depot(val){
        this.depot = val;
        save_data_local_storage("depot", this.depot);
        // this.save_model_to_local_storage();
    }
    
    empty_model(){
        this.dict_id_customer = [];
        this.save_model_to_local_storage();
    }
    
    load_from_json(json_file){
        var model = JSON.parse(json_file);
        if( model.dict_id_customer != null){
            this.dict_id_customer = model.dict_id_customer;
        }
        if( model.max_capacity_per_vehicle != null){
            this.max_capacity_per_vehicle = model.max_capacity_per_vehicle;
        }
        if( model.n_vehicles != null){
            this.n_vehicles = model.n_vehicles;
        }
        if( model.heuristic != null){
            this.heuristic = model.heuristic;
        }
        if( model.use_meta != null){
            this.use_meta = model.use_meta;
        }
        if( model.meta != null){
            this.meta = model.meta;
        }
        if( model.meta_parameter != null){
            this.meta_parameter = model.meta_parameter;
        }
        if( model.depot != null){
            this.depot = model.depot;
        }
        this.save_model_to_local_storage();
    }

    get_list_selected_customer_id(){
        var filtere_list = this.dict_id_customer.filter(el => el.isSelected);
        var list_id = filtere_list.map(el => el.id);
        return list_id;
    }

    get_list_geojson_selected_customer(){
        return this.get_list_selected_customer_id().map(
            id => this.get_customer(id).to_geojson());
    }

    get_list_coordinates_selected_customer(){
        return this.get_list_selected_customer_id().map(
            id => this.get_customer(id).get_coordinates());
    }

    get_list_demands_selected_customer(){
        return this.get_list_selected_customer_id().filter(id => id != 0).map(
            id => this.get_customer(id).quantity);
    }

    delete_customer(id){
        this.dict_id_customer = this.dict_id_customer.filter(el => el.id != id);
        this.save_model_to_local_storage();
    }

    add_customer(customer)
    {
        var id = this.dict_id_customer.length > 0 ? this.dict_id_customer[this.dict_id_customer.length-1].id + 1 : 1;
        this.dict_id_customer[this.dict_id_customer.length] =
            {
                "id": id,
                "data": customer.tolist(),
                "isSelected": customer.isSelected};
        this.save_model_to_local_storage();
        return id;
    };

    update_customer(id, t_customer)
    {
        var customer = this.dict_id_customer.find(el => el.id == id);
        if (customer) {
            customer.data = t_customer.tolist();
            customer.isSelected = t_customer.isSelected;
        }
        save_data_local_storage("list_customer", this.dict_id_customer);
        // this.save_model_to_local_storage();
    };

    save_model_to_local_storage(){
        save_data_local_storage("list_customer", this.dict_id_customer);
        save_data_local_storage("max_capacity_per_vehicle", this.max_capacity_per_vehicle);
        save_data_local_storage("heuristic", this.heuristic);
        save_data_local_storage("meta", this.meta);
        save_data_local_storage("meta_parameter", this.meta_parameter);
        save_data_local_storage("depot", this.depot);
    }

    get_customer(id){
        /* Get data from array_json for specific id */
        var tmp = this.dict_id_customer.filter(function(e) {
            return e.id == id;
        })[0];
        // console.log(tmp);
        var customer = new Customer();
        customer.fromlist(tmp.data);
        customer.set_isSelected(tmp.isSelected);
        return customer;
    }

    toggle_customer_isSelected(id){
        var customer = this.get_customer(id);
        var isSelected = customer.toggle_isSelected();
        this.update_customer(id, customer);
        return isSelected;
    }
}

class Customer_form_manager {
  constructor(api_manager) {
    var customer_form_manager = this;
    this.name = document.getElementById("client_nom");
    this.quantity = document.getElementById("client_quantite");
    this.city = document.getElementById("client_ville");
    this.street = document.getElementById("client_rue");
    this.num = document.getElementById("client_numero");
    this.post_code = document.getElementById("client_code_postal");
    this.country = document.getElementById("client_pays");
    this.latitude = document.getElementById("client_latitude");
    this.longitude = document.getElementById("client_longitude");
    this.button_get_coordinates = document.getElementById("btn_get_coordinates");
    this.api_manager = api_manager;
    // console.log(this.button_get_coordinates);

    var get_coordinates_button_disable_checker = function () {
      customer_form_manager.get_coordinates_button_disable_checker();
    };
    get_coordinates_button_disable_checker();
    this.city.addEventListener("keyup", get_coordinates_button_disable_checker);
    this.street.addEventListener("keyup", get_coordinates_button_disable_checker);
    this.num.addEventListener("keyup", get_coordinates_button_disable_checker);
    this.post_code.addEventListener("keyup", get_coordinates_button_disable_checker);
    this.country.addEventListener("keyup", get_coordinates_button_disable_checker);

    this.button_get_coordinates.addEventListener("click", function () {
      var customer = customer_form_manager.get_customer_data();
      var coord = customer_form_manager.api_manager.get_coordinates(customer);
      // console.log(coord);
      customer_form_manager.latitude.value = coord.lat;
      customer_form_manager.longitude.value = coord.long;
    }
    );
  }



    get_coordinates_button_disable_checker()
    {
        if (this.city.value.length > 0 &&
            this.street.value.length > 0 &&
            this.num.value.length > 0 &&
            this.post_code.value.length > 0 &&
            this.country.value.length > 0){

            this.button_get_coordinates.disabled = "";
        }
        else{
            this.button_get_coordinates.disable = true;
            this.button_get_coordinates.disabled = "disabled";
        }
        // console.log(this.button_get_coordinates) ;
    }

    get_customer_data(){
        var customer = new Customer(this.name.value,
                                    this.quantity.value,
                                    this.latitude.value,
                                    this.longitude.value,
                                    this.city.value,
                                    this.street.value,
                                    this.num.value,
                                    this.post_code.value,
                                    this.country.value);
        return customer;
    }

    set_customer_data(customer){
        this.name.value = customer.name;
        this.quantity.value = customer.quantity;
        this.city.value = customer.city;
        this.street.value = customer.street;
        this.num.value = customer.num;
        this.post_code.value = customer.post_code;
        this.country.value = customer.country;
        this.latitude.value = customer.latitude;
        this.longitude.value = customer.longitude;
    }
}

class API_manager {
  constructor(api_key) {
    this.api_key = api_key;
  }
  get_coordinates(customer){
    var adress = customer.getadress();
    var request = new XMLHttpRequest();
    request.open('GET', `https://api.openrouteservice.org/geocode/search?api_key=${this.api_key}&text=${encodeURIComponent(adress)}`, false);
    request.setRequestHeader('Accept', 'application/json, application/geo+json, application/gpx+xml, img/png; charset=utf-8');
    request.send();
    console.log(`send request for ${adress}`);
    if (request.status === 200) {
      /* console.log(request.responseText); */
      var arrayCoord = JSON.parse(request.responseText)["features"][0]["geometry"]["coordinates"];
      var coordinates = new Coordinates(arrayCoord[0],arrayCoord[1]);
      return coordinates;
    }
    else{
      return null;
    }
  }

  get_matrix(list_coordinates, metric){
    // longitude then latitude
    // list_coordinates = [[9.70093,48.477473],[9.207916,49.153868],[37.573242,55.801281]];
    var request = new XMLHttpRequest();
    request.open('POST', "https://api.openrouteservice.org/v2/matrix/driving-car",false);
    request.setRequestHeader('Accept', 'application/json, application/geo+json, application/gpx+xml, img/png; charset=utf-8');
    request.setRequestHeader('Content-Type', 'application/json');
    request.setRequestHeader('Authorization', this.api_key);
    var bodyObject = {};
    bodyObject["locations"]=list_coordinates;
    bodyObject["metrics"]=[metric];
    request.send(JSON.stringify(bodyObject));
    if (request.status === 200) {
      var response = JSON.parse(request.responseText);
      var matrix = response[`${metric}s`];
      // console.log(matrix);
      return matrix;
    }
    else{
      console.log("request status =" + request.status);
      return null;
    }
  }

  get_vehicle_cycle_long(list_coord){
    // list_coord = [[8.681495,49.41461],[8.686507,49.41943],[8.687872,49.420318]];
    var body={};
    body["coordinates"] = list_coord;
    let request = new XMLHttpRequest();
    request.open('POST', "https://api.openrouteservice.org/v2/directions/driving-car/geojson", false);  // false makes the request synchronous
    request.setRequestHeader('Accept', 'application/json, application/geo+json, application/gpx+xml, img/png; charset=utf-8');
    request.setRequestHeader('Content-Type', 'application/json');
    request.setRequestHeader('Authorization', this.api_key);
    // console.log(JSON.stringify(body));
    request.send(JSON.stringify(body));
    if (request.status === 200) {
      var response = JSON.parse(request.responseText);
      console.log(response);
      return response["features"][0]["geometry"]["coordinates"];
    }
    else{
      console.log("request status =" + request.status);
      return null;
    }
  }


  get_vehicle_cycle_short(list_coord){
    // list_coord = [[8.681495,49.41461],[8.686507,49.41943],[8.687872,49.420318]];
    var body={};
    body["coordinates"] = list_coord;
    let request = new XMLHttpRequest();
    request.open('POST', "https://api.openrouteservice.org/v2/directions/driving-car", false);  // false makes the request synchronous
    request.setRequestHeader('Accept', 'application/json, application/geo+json, application/gpx+xml, img/png; charset=utf-8');
    request.setRequestHeader('Content-Type', 'application/json');
    request.setRequestHeader('Authorization', this.api_key);
    // console.log(JSON.stringify(body));
    request.send(JSON.stringify(body));
    if (request.status === 200) {
      var response = JSON.parse(request.responseText);
        console.log(response);
        var polyline = response["routes"][0]["geometry"];
        var distance = response["routes"][0]["summary"]["distance"];
        var duration = response["routes"][0]["summary"]["duration"];
        var short_cycle  = new Short_cycle(polyline, distance, duration);
        return short_cycle;
    }
    else{
      console.log("request status =" + request.status);
      return null;
    }
  }
}

class GUI_manager  {
    constructor(model, api_manager) {
        this.model = model;
        this.table_body = document.querySelector("#table_clients > tbody");
        // this.table_detail = document.getElementById("table_detail");
        this.form_client_action = document.getElementById("form_client_action");
        this.btn_client_action = document.getElementById("btn_client_action");
        this.compute_btn = document.getElementById("compute_btn");
        this.clear_map_btn = document.getElementById("clear_map_btn");
        this.clear_list_btn = document.getElementById("clear_list_btn");
        this.api_manager = api_manager;
        this.customer_form_manager = new Customer_form_manager(this.api_manager);
        this._form_display_customize();
        this._setup_compute_button();
        this.clear_map_btn.addEventListener("click", clear_outputs);
        this.input_import = document.getElementById("input_import");
        this.export_btn = document.getElementById("export_btn");
        this._setup_import_btn();
        this._setup_export_btn();
        this._setup_clear_list_btn(); 
        this._setup_settings_form();
        this._setup_depot_form();
        this.hydrate_table_clients();
    }

    _setup_depot_form(){
        this.depot_latitude_input = document.getElementById("depot_latitude");
        this.depot_longitude_input = document.getElementById("depot_longitude");
        this._setup_depot_latitude_input();
        this._setup_depot_longitude_input();
    }

    _setup_settings_form(){
        this.vehicle_max_capacity_input = document.getElementById("vehicule_max_capacity");
        this.n_vehicles_input = document.getElementById("n_vehicles");
        this.heuristic_input = document.getElementById("sel_heuristic");
        this.meta_input = document.getElementById("sel_meta");
        this.use_meta_cb = document.getElementById("use_meta_cb");
        this.temp_init_input = document.getElementById("temp_init_input");
        this.temp_final_input = document.getElementById("temp_final_input");
        this.alpha_input = document.getElementById("alpha");
        this.beta_input = document.getElementById("beta");
        this.n_iter_at_temp_init_input = document.getElementById("n_iter_at_temp_init");
        this.n_iter_without_impr_input = document.getElementById("n_iter_without_impr");
        
        this._setup_max_capacity_vehicle_input();
        this._setup_n_vehicles_input();
        this._setup_heuristic_input();
        this._setup_meta_input();
        this._setup_use_meta_cb();
        this._setup_temp_init_input();
        this._setup_temp_final_input();
        this._setup_alpha_input();
        this._setup_beta_input();
        this._setup_n_iter_at_temp_init_input();
        this._setup_n_iter_without_impr_input();
    }

    _setup_depot_latitude_input(){
        var gui_manager = this;
        var model = this.model;
        // temp_init_input
        this.depot_latitude_input.addEventListener("change", function () {
            model.depot.latitude = parseFloat(this.value);
            model.set_depot(model.depot);
        });
        this.depot_latitude_input.value = model.depot.latitude;
    }
    
    _setup_depot_longitude_input(){
        var gui_manager = this;
        var model = this.model;
        // temp_init_input
        this.depot_longitude_input.addEventListener("change", function () {
            model.depot.longitude = parseFloat(this.value);
            model.set_depot(model.depot);
        });
        this.depot_longitude_input.value = model.depot.longitude;
    }

    
    _setup_max_capacity_vehicle_input(){
        var gui_manager = this;
        var model = this.model;
        this.vehicle_max_capacity_input.addEventListener("change", function () {
            model.set_max_capacity_per_vehicle(parseInt(this.value));
        });
        this.vehicle_max_capacity_input.value = model.max_capacity_per_vehicle;
    }
    
    _setup_n_vehicles_input(){
        var gui_manager = this;
        var model = this.model;
        this.n_vehicles_input.addEventListener("change", function () {
            model.set_n_vehicles(parseInt(this.value));
        });
        this.n_vehicles_input.value = model.n_vehicles;
    }
    
    _setup_heuristic_input(){
        var gui_manager = this;
        var model = this.model;
        this.heuristic_input.addEventListener("change", function () {
            model.set_heuristic(this.value);
        });
        this.heuristic_input.value = model.heuristic;
    }
    
    _setup_meta_input(){
        var gui_manager = this;
        var model = this.model;
        this.meta_input.addEventListener("change", function () {
            model.set_meta(this.value);
        });
        this.meta_input.value = model.meta;
    }
    _setup_use_meta_cb(){
        var gui_manager = this;
        var model = this.model;
        this.use_meta_cb.addEventListener("change", function () {
            // console.log(this.checked);
            model.set_use_meta(this.checked);
        });
        this.use_meta_cb.checked = model.use_meta;
    }

    _setup_temp_init_input(){
        var gui_manager = this;
        var model = this.model;
        // temp_init_input
        this.temp_init_input.addEventListener("change", function () {
            model.meta_parameter.temp_init = parseFloat(this.value);
            model.set_meta_parameter(model.meta_parameter);
        });
        this.temp_init_input.value = model.meta_parameter.temp_init;
    }

    _setup_temp_final_input(){
        var gui_manager = this;
        var model = this.model;
        this.temp_final_input.addEventListener("change", function () {
            model.meta_parameter.temp_final = parseFloat(this.value);
            model.set_meta_parameter(model.meta_parameter);
        });
        this.temp_final_input.value = model.meta_parameter.temp_final;
    }

    _setup_alpha_input(){
        var gui_manager = this;
        var model = this.model;
        this.alpha_input.addEventListener("change", function () {
            model.meta_parameter.alpha = parseFloat(this.value);
            model.set_meta_parameter(model.meta_parameter);
        });
        this.alpha_input.value = model.meta_parameter.alpha;
    }

    _setup_beta_input(){
        var gui_manager = this;
        var model = this.model;
        this.beta_input.addEventListener("change", function () {
            model.meta_parameter.beta = parseFloat(this.value);
            model.set_meta_parameter(model.meta_parameter);
        });
        this.beta_input.value = model.meta_parameter.beta;
    }

    _setup_n_iter_at_temp_init_input(){
        var gui_manager = this;
        var model = this.model;
        this.n_iter_at_temp_init_input.addEventListener("change", function () {
            model.meta_parameter.n_iter_at_temp_init = parseInt(this.value);
            model.set_meta_parameter(model.meta_parameter);
        });
        this.n_iter_at_temp_init_input.value = model.meta_parameter.n_iter_at_temp_init;
    }

    _setup_n_iter_without_impr_input(){
        var gui_manager = this;
        var model = this.model;
        this.n_iter_without_impr_input.addEventListener("change", function () {
            model.meta_parameter.n_iter_without_impr = parseInt(this.value);
            model.set_meta_parameter(model.meta_parameter);
        });
        this.n_iter_without_impr_input.value = model.meta_parameter.n_iter_without_impr;
    }

    _setup_clear_list_btn(){
        var gui_manager = this;
        var model = this.model;
        this.clear_list_btn.addEventListener("click", function () {
            model.empty_model();
            gui_manager.hydrate_table_clients();
        });
    }
    
    _setup_export_btn(){
        var gui_manager = this;
        var model = this.model;
        this.export_btn.addEventListener("click", function () {
            gui_manager.export_instance(model);
        });
    }
    
    export_instance(mObject){
        var filename = prompt("Enregistrer sous","untitled");
        if(!mObject) {
            console.error('No data to export');
            return;
        }
        if(!filename) {
            // filename = 'untitled';
            console.log('Canceled');
            return;
        }
        filename = filename + ".json";
        //Convert JSON Array to string.
        var json = JSON.stringify(mObject, undefined, 4);
        //Convert JSON string to BLOB.
        json = [json];
        var blob1 = new Blob(json, { type: "text/plain;charset=utf-8" });
        //Check the Browser.
        var isIE = false || !!document.documentMode;
        if (isIE) {
            window.navigator.msSaveBlob(blob1, filename);
        } else {
            var url = window.URL || window.webkitURL;
            var link = url.createObjectURL(blob1);
            var a = document.createElement("a");
            a.download = filename;
            a.href = link;
            document.body.appendChild(a);
            a.click();
            document.body.removeChild(a);
        }
    }
    _setup_import_btn(){
        $("#import_btn").click(function(e){
            e.preventDefault();
            $("#input_import").trigger('click');
        });
        var gui_manager = this;
        this.input_import.addEventListener("change",function (event) {
            /* console.log("test") */
            gui_manager._load_instance(event);
        }
                                          );
    }

    _load_instance(event) {
        var input = event.target;
        var model = this.model;
        console.log("model");
        console.log(model);
        var gui_manager = this;
        console.log("gui_manager");
        console.log(gui_manager);
        var reader = new FileReader();

        var onLoad = function(){
            var text = reader.result;
            model.load_from_json(text);
            gui_manager.hydrate_table_clients();
            gui_manager.hydrate_settings();
            gui_manager.hydrate_depot();
        };

        reader.addEventListener("load", onLoad);
        /* reader.onload = ; */
        reader.readAsText(input.files[0]);
    };

    _call_VRP_script(script_param, list_id){
        var gui_manager = this;
        console.log(script_param);
        var jsonString = JSON.stringify(script_param);
        console.log(jsonString);
        $.ajax({
            method: "POST",
            url: "VRP_compute.php",
            data: { json: jsonString}
        })
            .done(function (msg) {
                console.log(msg);
                var received_json = JSON.parse(msg);
                console.log(msg);
                var list_node_list = received_json["vehicles"];
                alert(msg);
                list_id.unshift(0);
                // alert(received_json["cost"]);
                // console.log(received_json["vehicles"]);
                list_node_list = list_node_list.map(node_list => node_list.map(
                    id => list_id[id]));

                console.log(list_id);
                var list_vehicle_cycles = gui_manager._get_vehicle_cycles(list_node_list);
                var solution_cost = 0;
                list_vehicle_cycles.forEach((short_cycle) => {
                    solution_cost += short_cycle.distance;
                });
                save_data_local_storage("best_solution", solution_cost);
                $("#best_solution").text(`Meilleure solution : ${solution_cost.toFixed(2)} m`).show();
                // console.log("test");
                // window.test = list_vehicle_cycles;
                save_data_local_storage("list_vehicle_cycles", list_vehicle_cycles);
                // window.localStorage.getItem("list_vehicle_cycles")
                // console.log(list_vehicle_cycles);
            }
                 );
    }

    _get_vehicle_cycles(list_node_list){
        // console.log(list_node_list)
        var list_vehicle_cycles = [];
        list_node_list.forEach((list_node) => {
            console.log(list_node);
            var list_node_coordinates = this._from_list_id_to_list_coordinates(list_node);
            // list_geojson.push();
            var short_cycle = this.api_manager.get_vehicle_cycle_short(list_node_coordinates);
            list_vehicle_cycles.push(short_cycle);
        });
        // console.log(list_geojson);
        return list_vehicle_cycles;
    }

    _from_list_id_to_list_coordinates(list_id){
        // list_id = [0, 5, 4, 0];
        // return list_id.map(
        // id => this.model.get_customer(id).get_coordinates());
        
        // console.log(this.model.depot.latitude);
        return list_id.map(
            id => id == 0 ? [this.model.depot.longitude, this.model.depot.latitude] : this.model.get_customer(id).get_coordinates());
        // return list_id.map(function (id) {
        //     if(id == 0) {
        //         return [this.model.depot.longitude, this.model.depot.latitude];
        //     }
        //     else {
        //         return this.model.get_customer(id).get_coordinates();
        //     }
        // });
    }

    _compute_VRP(){
        var list_coordinates = this.model.get_list_coordinates_selected_customer();
        list_coordinates.unshift([this.model.depot.longitude, this.model.depot.latitude]);
        console.log(list_coordinates);
        // console.log("test");
        save_data_local_storage("list_client_geojson", this.model.get_list_geojson_selected_customer());
        // var tmpDict = {"instance":{},
        //                "heuristic":null,
        //                "meta":null,
        //                "meta_parameter":{
        //                    {}}};
        // console.log(this.model.get_list_demands_selected_customer());
        var script_param = {"instance":{
            "max_capacity_per_vehicle":this.model.max_capacity_per_vehicle, 
            "nb_vehicles":this.model.n_vehicles, 
            "matrix":this.api_manager.get_matrix(list_coordinates, "distance"), 
            "demands":this.model.get_list_demands_selected_customer()
        },
                       "heuristic":this.model.heuristic,
                       "meta":null,
                       "meta_parameter":null};
        if(this.model.use_meta){
            script_param.meta = this.model.meta;
            script_param.meta_parameter = {"temp_init" :this.model.meta_parameter.temp_init,
                                           "temp_final" :this.model.meta_parameter.temp_final,
                                           "alpha" :this.model.meta_parameter.alpha,
                                           "beta" :this.model.meta_parameter.beta,
                                           "n_iter_at_temp_init" :this.model.meta_parameter.n_iter_at_temp_init,
                                           "n_iter_without_impr" :this.model.meta_parameter.n_iter_without_impr,
                                           "low_cost_threshold" :this.model.meta_parameter.low_cost_threshold
                                          };
        }
        
        console.log(script_param);
        
        var list_id = this.model.get_list_selected_customer_id();
        // console.log(JSON.stringify(matrix));
        // console.log(JSON.stringify(list_demands));
        // console.log(list_id);
        this._call_VRP_script(script_param, list_id);
        // this._call_VRP_script();
        // gui_manager._call_VRP_script();
        // gui_manager.api_manager.get_matrix([], "duration");
        // gui_manager.api_manager.get_vehicle_cycle_long([]);
    }

    _setup_compute_button(){
        // console.log("test")
        var gui_manager = this;
        this.compute_btn.addEventListener("click", function () {
            gui_manager._compute_VRP();
        }
                                         );
    }

    _form_display_customize(){
        var gui_manager = this;
        var customer_form_manager = this.customer_form_manager;

        $('#modal_client_action').on('show.bs.modal', function (event) {
            var add_customer = function () {
                gui_manager.add_customer();
            };
            var edit_customer = function (evt) {
                gui_manager.edit_customer(evt);
            };
            /* Remove listener because it's getting added dynamically everytime */
            var old_element = document.getElementById("btn_client_action");
            var new_element = old_element.cloneNode(true);
            old_element.parentNode.replaceChild(new_element, old_element);
            gui_manager.btn_client_action = new_element;

            /* Get specific action (add or update) */
            var button = $(event.relatedTarget);
            var action = button.data('action');
            var modal = $(this);
            if (action=="Ajouter_client") {
                /* Reset form values */
                var form = document.getElementById("form_client_action").reset();
                gui_manager.customer_form_manager.get_coordinates_button_disable_checker();
                /* Change form text for add client */
                modal.find('.modal-title').text("Ajouter un client");
                gui_manager.btn_client_action.textContent="Ajouter";
                /* Add listener for validation button */
                gui_manager.btn_client_action.addEventListener("click",add_customer);
                gui_manager.btn_client_action.addEventListener("click",function () {
                    $('#modal_client_action').modal("hide");
                }
                                                              );

            }
            else if(action=="Modifier_client") {
                /* Change form text for update client */
                modal.find('.modal-title').text("Modifier un client");
                gui_manager.btn_client_action.textContent="Modifier";
                /* Add listener for validation button */
                gui_manager.btn_client_action.addEventListener("click",edit_customer);
                /* Get id of client clicked */
                let id = button.data('id');
                /* Add id to button (used in binded function) */
                gui_manager.btn_client_action.client_id = id;
                var customer = gui_manager.model.get_customer(id);
                // console.log(customer);
                /* Prefill form with user data*/
                gui_manager.customer_form_manager.set_customer_data(customer);
                customer_form_manager.get_coordinates_button_disable_checker();
            }
        });
    }

    _create_delete_button()
    {
        var td = document.createElement("td");
        var a = document.createElement("a");
        a.classList.add("delete");
        let gui_manager = this;
        a.addEventListener("click", function(){
            // console.log("test");
            gui_manager.delete_client(this);
        });
        var i = document.createElement("i");
        i.classList.add("far");
        i.classList.add("fa-minus-square");
        a.appendChild(i);
        td.appendChild(a);
        // td.innerHTML = '<a class="delete" onclick="delete_client(this)"><i class="far fa-minus-square"></i></a>';
        return td;
    }

    _create_edit_button(id)
  {
    var td = document.createElement("td");
    var a = document.createElement("a");
    a.classList.add("edit");
    let gui_manager = this;
    // a.addEventListener("click", function(){
    // console.log("test");
    // gui_manager.edit_client(this);
    // });
    var i = document.createElement("i");
    // i.classList.add("far");
    // i.classList.add("fa-minus-square");
    a.setAttribute("data-toggle", "modal");
    a.setAttribute("data-target", "#modal_client_action");
    a.setAttribute("data-id", id);
    a.setAttribute("data-action", "Modifier_client");
    i.setAttribute("class", "far fa-edit");
    a.appendChild(i);
    td.appendChild(a);
    // td.innerHTML = '<a class="edit" data-toggle="modal" data-target="#modal_client_action" data-id="'+id+'" data-action="Modifier_client"><i class="far fa-edit"></i></a>';
    return td;
  }

  _remove_all_lines_from_table(){
    while(this.table_body.firstChild){
      this.table_body.removeChild(this.table_body.firstChild);
    }
  }
  _delete_client_row(id){
    var tr = document.getElementById("client_"+id);
    tr.parentNode.removeChild(tr);
  }
  // CRUD
  delete_client(element){
    /* Get client id */
    var tr = element.closest('tr');
    var id = tr.id.substr(7); // client_id -> id
    /* Delete GUI row */
    this._delete_client_row(id);
    /* Remove element from model */
    this.model.delete_customer(id);
  };

  _update_client_row(id, customer)
  {
    /* Get DOM element from id */
    let tr = document.getElementById("client_"+id);
    /* Remove all children */
    while(tr.firstChild){
      tr.removeChild(tr.firstChild);
    }
    /* Add cells  */
    var td = document.createElement("td");
    var checkbox = this._create_client_checkbox(id, customer.isSelected);
    td.appendChild(checkbox);
    tr.append(td);
    td = document.createElement("td");
    td.textContent = customer.name;
    tr.append(td);
    td = document.createElement("td");
    td.textContent = customer.quantity;
    tr.append(td);
    td = document.createElement("td");
    td.textContent = customer.latitude;
    tr.append(td);
    td = document.createElement("td");
    td.textContent = customer.longitude;
    tr.append(td);
    td = this._create_edit_button(id);
    tr.append(td);
    td = this._create_delete_button();
    tr.append(td);
  }

  edit_customer(evt)
  {
    /* Get of client element */
    let id = evt.currentTarget.client_id;
    var isSelected = this.model.get_customer(id).isSelected;
    /* Get data from form */
    var customer = this.customer_form_manager.get_customer_data();
    customer.isSelected = isSelected;
    // console.log(customer);
    /* Update GUI row */
    this._update_client_row(id, customer);
    /* Update model */
    model.update_customer(id, customer);
  };

  _toggle_is_selected(element){
    /* Get client id */
    var tr = element.closest('tr');
    var id = tr.id.substr(7); // client_id -> id
    var isSelected = this.model.toggle_customer_isSelected(id);
    console.log(`${id}:${isSelected}`);
  }

  _create_client_checkbox(id, isSelected){
    var gui_manager = this;
    // console.log(`${id}:${isSelected}`);
    var checkbox = document.createElement("INPUT");
    checkbox.setAttribute("type", "checkbox");
    if (isSelected){
      checkbox.setAttribute("checked", "checked");
    }
    checkbox.addEventListener("change", function () {
      gui_manager._toggle_is_selected(this);
    }
    );
    return checkbox;
  }

  _create_client_row(id, customer)
  {
    var tr = document.createElement("tr");
    tr.id = "client_"+id;
    var td = document.createElement("td");
    var checkbox = this._create_client_checkbox(id, customer.isSelected);
    td.appendChild(checkbox);
    tr.append(td);
    td = document.createElement("td");
    td.textContent = customer.name;
    tr.append(td);
    td = document.createElement("td");
    td.textContent = customer.quantity;
    tr.append(td);
    td = document.createElement("td");
    td.textContent = customer.latitude;
    tr.append(td);
    td = document.createElement("td");
    td.textContent = customer.longitude;
    tr.append(td);
    td = this._create_edit_button(id);
    tr.append(td);
    td = this._create_delete_button();
    tr.append(td);
    return tr;
  };

  // TODO : add latitude longitude entry or API*/
  add_customer(){
    var customer = this.customer_form_manager.get_customer_data();
    var id = this.model.add_customer(customer);
    var tr = this._create_client_row(id, customer);
    this.table_body.append(tr);
  };

    /* UI */
    hydrate_table_clients(){
        /* Remove existing elements from table */
        this._remove_all_lines_from_table();
        console.log(this.model.dict_id_customer);
        /* Loop through array and add row for each client */
        this.model.dict_id_customer.forEach((el)=>{
            let id = el.id;
            var customer = new Customer();
            customer.fromlist(el.data);
            customer.isSelected = el.isSelected;
            // client = client_list_to_object(el.data);
            let tr = this._create_client_row(id, customer);
            this.table_body.append(tr);
        });
  };
    hydrate_settings(){
        this.vehicle_max_capacity_input.value = this.model.max_capacity_per_vehicle;
        this.n_vehicles_input.value = this.model.n_vehicles;
        this.heuristic_input.value = this.model.heuristic;
        this.meta_input.value = this.model.meta;
        this.use_meta_cb.checked = this.model.use_meta;
        this.temp_init_input.value = this.model.meta_parameter.temp_init;
        this.temp_final_input.value = this.model.meta_parameter.temp_final;
        this.alpha_input.value = this.model.meta_parameter.alpha;
        this.beta_input.value = this.model.meta_parameter.beta;
        this.n_iter_at_temp_init_input.value = this.model.meta_parameter.n_iter_at_temp_init;
        this.n_iter_without_impr_input.value = this.model.meta_parameter.n_iter_without_impr;
    }
    hydrate_depot(){
        this.depot_longitude_input.value = this.model.depot.longitude;
        this.depot_latitude_input.value = this.model.depot.latitude;
    }
}

API_KEY = "5b3ce3597851110001cf6248703754048738463ba206b43ed13658a3";

/* Hydrate array_json on startup */
document.addEventListener("DOMContentLoaded",()=>{
  api_manager = new API_manager(API_KEY);
  model = new Model();
  gui_manager = new GUI_manager(model, api_manager);
});
