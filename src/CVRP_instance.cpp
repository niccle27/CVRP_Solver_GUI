#include "CVRP_instance.h"
#include <iostream>
#include <iomanip>


void CVRP_instance::setDistanceMatrix(std::vector<std::vector<int>> t_distanceMatrix)
{
	m_distanceMatrix = t_distanceMatrix;
}


int CVRP_instance::get_distance_node2node(int id_node1, int id_node2) const
{
	return m_distanceMatrix[id_node1][id_node2];
}

void CVRP_instance::show_matrix()const
{
	for (auto it_row = m_distanceMatrix.begin(); it_row != m_distanceMatrix.end(); ++it_row) {
		for (auto it_column = (*it_row).begin(); it_column != (*it_row).end(); ++it_column)
		{
			std::cout << std::setw(5) << (*it_column);
		}
		std::cout << std::endl;
	}
}

int CVRP_instance::get_distanceMatrix_dim() const
{
	return m_distanceMatrix.size();
}

int CVRP_instance::get_number_of_customers() const
{
	return this->getNodes().size() - 1;
}



void CVRP_instance::set_list_nodes(std::vector<int> t_demands)
{

	for (int i = 0; i < t_demands.size(); ++i)
	{
		Node* el = new Node(i + 1, t_demands.at(i));
		m_vNodes.push_back(el);
	}
}

void CVRP_instance::setMaxCapacityPerVehicle(int t_maxCapacityPerVehicle){
    m_maxCapacityPerVehicle=t_maxCapacityPerVehicle;
}

CVRP_instance::~CVRP_instance()
{
	for (auto it = m_vNodes.begin(); it != m_vNodes.end(); ++it)
	{
		delete* it;
	}
}

CVRP_instance::CVRP_instance()
{
	Node* depot = new Node(0, 0);
	m_vNodes.push_back(depot);
}

CVRP_instance::CVRP_instance(std::vector<int> t_demands, std::vector<std::vector<int>> t_distanceMatrix, int t_maxCapacityPerVehicle)
{
	Node* depot = new Node(0, 0);
	m_vNodes.push_back(depot);
	//CVRP_instance::CVRP_instance();
	set_list_nodes(t_demands);
	setDistanceMatrix(t_distanceMatrix);
    setMaxCapacityPerVehicle(t_maxCapacityPerVehicle);
}
