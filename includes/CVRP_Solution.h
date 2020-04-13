#pragma once
#include "Vehicle.h"
#include<vector>
#include<string>
#include "json.hpp"
using json = nlohmann::json;
class CVRP_Solution
{
private:
	std::vector<Vehicle> m_list_vehicles;
public:
	void set_list_vehicule(std::vector<Vehicle> t_list_vehicles);
	std::vector<Vehicle> get_list_vehicles() { return m_list_vehicles; };
	int get_nb_of_vehicles(){ return m_list_vehicles.size(); };
	Vehicle* get_vehicle_by_index(int index) { return &m_list_vehicles[index]; };
	int get_number_of_vehicles() { return m_list_vehicles.size(); };
	void display() const;
	int get_cost();
	std::vector<std::vector<int>> toVector();
	std::string to_json();
	void display_json();
	void display_cost();
 
public:
	CVRP_Solution();
	CVRP_Solution(std::vector<Vehicle> t_list_vehicles);
	~CVRP_Solution();


};

