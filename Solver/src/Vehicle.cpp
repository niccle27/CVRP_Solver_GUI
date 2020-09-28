#include "Vehicle.h"
#include "Node.h"
#include <iostream>

bool Vehicle::is_enough_capacity_left(int capacity_to_add)
{
	return m_load + capacity_to_add <= m_maxLoad;
}

void Vehicle::print_list()const
{
	for (auto it = listIndexNodes.begin(); it != listIndexNodes.end(); ++it)
	{
		std::cout << (*it);
		auto next = std::next(it, 1);
		if (next != listIndexNodes.end())
		{
			std::cout << ",";
		}
	}
}

void Vehicle::set_customer_at_index(int index, int cust_index)
{
	listIndexNodes[index] = cust_index;
}

void Vehicle::insert_customer_at_index(int index, int cust_index)
{
	listIndexNodes.insert(listIndexNodes.begin() + index, cust_index);
}

void Vehicle::delete_customer_at_index(int index)
{
	listIndexNodes.erase(listIndexNodes.begin() + index);
}

int Vehicle::popFront()
{
	int index = 0;
	if (listIndexNodes.size() > 2) {
		index = listIndexNodes[1];
		listIndexNodes.erase(listIndexNodes.begin() + 1);
	}
	return index;
}

int Vehicle::popBack()
{
	int index = 0;
	if (listIndexNodes.size() > 2) {
		index = listIndexNodes[listIndexNodes.size()-2];
		listIndexNodes.erase(listIndexNodes.end() - 2);
	}
	return index;
}

void Vehicle::add_customer_to_front(int index)
{
	listIndexNodes.insert(listIndexNodes.begin() + 1, index);
}

void Vehicle::add_customer_to_back(int index)
{
	listIndexNodes.insert(listIndexNodes.end() - 1, index);
}

void Vehicle::display(bool disp_load, bool disp_cost)const
{
	std::cout << "[";
	for (auto it = listIndexNodes.begin(); it != listIndexNodes.end(); it++)
	{
		if (it != listIndexNodes.end() - 1) {
			std::cout << (*it) << ",";
		}
		else std::cout << (*it);
	}
	std::cout << "]";
	if (disp_load)
	{
		std::cout<< ", load: " << m_load <<"/"<< m_maxLoad;
	}
	if (disp_cost)
	{
		std::cout << ", cost: " << m_cost;
	}
	std::cout << std::endl;
}

int Vehicle::computeCost(std::vector<std::vector<int>> distance_matrix)
{
	int cost = 0;
	for (int i = 0; i < listIndexNodes.size() - 1; i++)
	{
		//std::cout << distance_matrix[listIndexNodes[i]][listIndexNodes[i + 1]] << " + "  ;
		cost += distance_matrix[listIndexNodes[i]][listIndexNodes[i + 1]];
	}
	return cost;
}

int Vehicle::computeLoad(std::vector<Node> list_nodes)
{
	int demand = 0;
//    std::cout << "start:";
	for (int i = 0; i < listIndexNodes.size() - 1; i++)
	{
//        std::cout << list_nodes[listIndexNodes[i]].getDemand() << "(" << listIndexNodes[i] <<"),";
		demand += list_nodes[listIndexNodes[i]].getDemand();
	}
//    std::cout << "stop:";
	return demand;
}

Vehicle::Vehicle(int t_maxLoad):
	m_maxLoad(t_maxLoad)
{
	listIndexNodes.push_back(0); // start at depot
	listIndexNodes.push_back(0); // end at depot
}

Vehicle::Vehicle(int t_maxLoad, int first_node, int first_node_load):
	m_maxLoad(t_maxLoad)
{
	m_load += first_node_load;
	listIndexNodes.push_back(0); // start at depot
	listIndexNodes.push_back(first_node); // add first customer
	listIndexNodes.push_back(0); // end at depot
}

Vehicle::~Vehicle()
{
}
