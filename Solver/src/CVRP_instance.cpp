#include "CVRP_instance.h"
#include <iostream>
#include <iomanip>

int CVRP_instance::get_distance_node2node(int id_node1, int id_node2) const
{
	return m_distanceMatrix[id_node1][id_node2];
}

void CVRP_instance::show_matrix()const
{
	for (auto it_row = m_distanceMatrix.begin(); it_row != m_distanceMatrix.end(); ++it_row) {
		for (auto it_column = (*it_row).begin(); it_column != (*it_row).end(); ++it_column)
		{
			//std::cout << std::setw(5) << (*it_column);
			std::cout << "\t" << (*it_column);
		}
		std::cout << std::endl;
	}
}

int CVRP_instance::get_distanceMatrix_dim() const
{
	return m_distanceMatrix.size();
}

void CVRP_instance::set_list_nodes(std::vector<int> t_demands)
{

	for (int i = 0; i < t_demands.size(); ++i)
	{
		Node el(i + 1, t_demands.at(i));
		this->list_nodes.push_back(el);
	}
}

CVRP_instance::~CVRP_instance()
{
}

CVRP_instance::CVRP_instance(std::vector<int> t_demands, std::vector<std::vector<int>> t_distanceMatrix, int t_maxCapacityPerVehicle, int t_nb_vehicles)
{
	Node depot(0, 0);
	this->list_nodes.push_back(depot);
	//CVRP_instance::CVRP_instance();
	set_list_nodes(t_demands);
	this->m_distanceMatrix = t_distanceMatrix;
	this->m_maxCapacityPerVehicle = t_maxCapacityPerVehicle;
	this->m_nb_vehicles = t_nb_vehicles;
}

CVRP_instance::CVRP_instance()
{
}

