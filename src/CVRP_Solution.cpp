#include "CVRP_Solution.h"
#include <iostream>

void CVRP_Solution::set_list_vehicule(std::vector<Vehicle> t_list_vehicles)
{
	m_list_vehicles = t_list_vehicles;
}

void CVRP_Solution::display()const
{
	for (int i = 0; i < m_list_vehicles.size(); ++i)
	{
		std::cout << "Vehicle[" << i << "]: ";
		m_list_vehicles[i].display(true,true);
		std::cout << std::endl;
	}
}

int CVRP_Solution::get_cost()
{
	int sum_cost = 0;
	for (int i = 0; i < m_list_vehicles.size(); i++)
	{
		sum_cost += m_list_vehicles[i].get_cost();
	}
	return sum_cost;
}

std::vector<std::vector<int>> CVRP_Solution::toVector()
{
	std::vector<std::vector<int>> v_vehicles;
	for (int i = 0; i < m_list_vehicles.size(); ++i)
	{
		v_vehicles.push_back(m_list_vehicles[i].getListIndexNodes());
	}
	return v_vehicles;
}

std::string CVRP_Solution::to_json()
{
	json j;
	j["vehicles"] = this->toVector();
	j["cost"] = this->get_cost();
	return j.dump();
}

void CVRP_Solution::display_json()
{
	std::cout << this->to_json() << std::endl;
}

void CVRP_Solution::display_cost()
{
	std::cout << "cost: " << get_cost() << std::endl;
}

CVRP_Solution::CVRP_Solution()
{
}

CVRP_Solution::CVRP_Solution(std::vector<Vehicle> t_list_vehicles)
{
	m_list_vehicles = t_list_vehicles;
}

CVRP_Solution::~CVRP_Solution()
{

}
