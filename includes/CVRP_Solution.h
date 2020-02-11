#pragma once
#include "Vehicle.h"
#include<vector>

class CVRP_Solution
{
private:
	std::vector<Vehicle*> m_list_vehicles;
public:
	void set_list_vehicule(std::vector<Vehicle*> t_list_vehicles);
	std::vector<Vehicle*> get_list_vehicles() { return m_list_vehicles; };
	void add_vehicle(Vehicle* vehicle);
	void print()const;
public:
	CVRP_Solution();
	CVRP_Solution(std::vector<Vehicle*> t_list_vehicles);
	~CVRP_Solution();


};

