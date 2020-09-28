function save_data_local_storage(key, mObject){
    console.log(`store ${key}`);
    console.log(mObject);
    window.localStorage.setItem(key, JSON.stringify(mObject));
}

function load_data_local_storage(key){
    return JSON.parse(window.localStorage.getItem(key));
}

function remove_from_local_storage(key) {
    window.localStorage.removeItem(key);
}

function clear_outputs(){
    remove_from_local_storage("list_client_geojson");
    remove_from_local_storage("list_vehicle_cycles");
    remove_from_local_storage("best_solution");
}
