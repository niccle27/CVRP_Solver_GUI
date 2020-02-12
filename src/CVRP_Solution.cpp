#include "CVRP_Solution.h"
#include <iostream>

void CVRP_Solution::set_list_vehicule(std::vector<Vehicle*> t_list_vehicles)
{
	m_list_vehicles = t_list_vehicles;
}

void CVRP_Solution::add_vehicle(Vehicle* vehicle)
{
	m_list_vehicles.push_back(vehicle);
}

void CVRP_Solution::print() const
{
	for (int i = 0; i<m_list_vehicles.size();++i)
	{
		std::cout << "Vehicle[" << i << "]: ";
		m_list_vehicles[i]->print_list();
		std::cout << std::endl;
	}
}

std::vector<std::vector<int>> CVRP_Solution::toVector()
{
	std::vector<std::vector<int>> v_vehicles;
	for (int i = 0; i < m_list_vehicles.size(); ++i)
	{
		v_vehicles.push_back(m_list_vehicles[i]->getVectorOfIds());		
	}
	return v_vehicles;
}

CVRP_Solution::CVRP_Solution()
{
}

CVRP_Solution::CVRP_Solution(std::vector<Vehicle*> t_list_vehicles=std::vector<Vehicle*>())
{
	set_list_vehicule(t_list_vehicles);
}

CVRP_Solution::~CVRP_Solution()
{
	for (auto it = m_list_vehicles.begin(); it != m_list_vehicles.end(); ++it)
	{
		delete* it;
	}
}