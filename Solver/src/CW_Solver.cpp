#include "CW_Solver.h"
#include"Vehicle.h"
#include <algorithm>
#include <functional>
#include <iostream>

CW_Solver::CW_Solver(bool t_isVerbose)
{
	this->isVerbose = t_isVerbose;
}

CW_Solver::~CW_Solver()
{
}

void CW_Solver::show_savings()
{
	for (auto it = m_list_saving.begin(); it != m_list_saving.end(); ++it)
	{
		it->display();
	}
}

void CW_Solver::display_vehicles()
{
	for (auto it = m_list_vehicles.begin(); it != m_list_vehicles.end(); it++)
	{
		if (it->hasCustomers())
		{
			it->display();
		}
	}
}

CVRP_Solution CW_Solver::solve(const CVRP_instance& instance)
{
	std::vector<Node> list_nodes=instance.getList_nodes();
	int max_load = instance.getMaxCapacityPerVehicle();
	m_list_vehicles.clear();
	//CVRP_Solution* solution = new CVRP_Solution();
	const int dim = instance.get_distanceMatrix_dim();

	//Compute savings
	for (int i = 1; i < dim - 1; i++) {
		for (int j = i + 1; j < dim; j++)
		{
			int dist_cust_1_to_depot = instance.get_distance_node2node(0, i);
			int dist_cust_2_to_depot = instance.get_distance_node2node(0, j);
			int dist_cust_1_to_cust_2 = instance.get_distance_node2node(i, j);
			int saving_val = dist_cust_1_to_depot + dist_cust_2_to_depot - dist_cust_1_to_cust_2;
			Saving el(i, j, saving_val);
			m_list_saving.push_back(el);
		}
	}
	std::sort(m_list_saving.begin(), m_list_saving.end(), std::greater<Saving>());

	if (isVerbose)
	{
		show_savings();
	}
	int numberOfCustomer = instance.get_number_of_customers();
	for (int i = 1; i <= numberOfCustomer; i++)
	{
        int demand = list_nodes[i].getDemand();
//        std::cout<<demand<<std::endl;
        Vehicle vehicle(max_load,i,demand);
		m_list_vehicles.push_back(vehicle);
	}
	int nb_vehicules = m_list_vehicles.size();
	for (auto it = m_list_saving.begin(); it != m_list_saving.end(); ++it)
	{
		if (nb_vehicules <= instance.getNumberOfVehicles())break; // if number of vehicle is 

		int id_cust_1 = it->get_id_cust_1();
		int id_cust_2 = it->get_id_cust_2();
		if (isVerbose) {
			it->display();
		}
		if (!it->isPositive())
		{
			if (isVerbose)
			{
				std::cout << "saving negative: no improvements possible" << std::endl;
			}
			if (nb_vehicules > instance.getNumberOfVehicles())
			{
				break; // break only if we have enough vehicles, otherwise we merge even if it doesn't improve
			}

		}
		Vehicle *v1_back=nullptr, *v1_front = nullptr, *v2_back = nullptr, *v2_front=nullptr;
		bool flag_accepted = false;

		for (int i = 0; i < m_list_vehicles.size(); i++)
		{
			if (m_list_vehicles[i].get_first_customer() == id_cust_1)v1_front = &m_list_vehicles[i];
			else if (m_list_vehicles[i].get_last_customer() == id_cust_1)v1_back = &m_list_vehicles[i];
			if (m_list_vehicles[i].get_first_customer() == id_cust_2)v2_front = &m_list_vehicles[i];
			else if (m_list_vehicles[i].get_last_customer() == id_cust_2)v2_back = &m_list_vehicles[i];
		}
		if (v1_back != nullptr && v2_front != nullptr)
		{
			if (v1_back == v2_front)
			{
				if (isVerbose)
				{
					std::cout << "Both customers belongs to the same cycle" << std::endl;
				}
				continue;
			}
			if (v1_back->getLoad() + v2_front->getLoad() < max_load)
			{
				flag_accepted = true;
				while (v2_front->hasCustomers())
				{
					int id = v2_front->popFront();
					int load = list_nodes[id].getDemand();
					v1_back->add_customer_to_back(id);
					v1_back->addLoad(load);
					v2_front->subLoad(load);
				}
			}
			else {
				if (isVerbose)
				{
					std::cout << "Maximum load exceeded:" << v1_back->getLoad() << " + " << v2_front->getLoad() << ">" << max_load << std::endl;
				}
			}
		}
		else if (v2_back != nullptr && v1_front != nullptr)
		{
			if (v2_back == v1_front)continue;
			if (v2_back->getLoad() + v1_front->getLoad() < max_load)
			{
				flag_accepted = true;
				while (v1_front->hasCustomers())
				{
					int id = v1_front->popFront();
					int load = list_nodes[id].getDemand();
					v2_back->add_customer_to_back(id);
					v2_back->addLoad(load);
					v1_front->subLoad(load);
				}
			}
			else {
				if (isVerbose)
				{
					std::cout << "Maximum load exceeded:" << v2_back->getLoad() << " + " << v1_front->getLoad() << ">" << max_load << std::endl;
				}
			}


		}
		else if (v1_front != nullptr && v2_front != nullptr)
		{
			if (v1_front == v2_front)continue;
			if (v2_front->getLoad() + v1_front->getLoad() < max_load)
			{
				flag_accepted = true;
				while (v2_front->hasCustomers())
				{
					int id = v2_front->popFront();
					int load = list_nodes[id].getDemand();
					v1_front->add_customer_to_front(id);
					v1_front->addLoad(load);
					v2_front->subLoad(load);
				}
			}
			else {
				if (isVerbose)
				{
					std::cout << "Maximum load exceeded:" << v2_front->getLoad() << " + " << v1_front->getLoad() << ">" << max_load << std::endl;
				}
			}
		}
		else if (v1_back != nullptr && v2_back != nullptr)
		{
			if (v1_back == v2_back)continue;
			if (v2_back->getLoad() + v1_back->getLoad() < max_load)
			{
				flag_accepted = true;
				while (v2_back->hasCustomers())
				{
					int id = v2_back->popBack();
					int load = list_nodes[id].getDemand();
					v1_back->add_customer_to_back(id);
					v1_back->addLoad(load);
					v2_back->subLoad(load);
				}
			}
			else {
				if (isVerbose)
				{
					std::cout << "Maximum load exceeded:" << v2_back->getLoad() << " + " << v1_back->getLoad() << ">" << max_load << std::endl;
				}
			}
		}
		if (flag_accepted)
		{
			nb_vehicules--;
			if (isVerbose)
			{
				std::cout << "Accepted: join cycle" << std::endl;
				display_vehicles();
			}
		}

	}
	auto it = m_list_vehicles.begin();
	int ctr_id = 0;
	while(it != m_list_vehicles.end())
	{
		if (!it->hasCustomers())it = m_list_vehicles.erase(it);
		else {
			for (int i = 0; i < it->getListIndexNodes().size()-1; i++)
			{
				it->addCost(instance.get_distance_node2node(it->getListIndexNodes()[i], it->getListIndexNodes()[i + 1]));
			}
//            std::cout << it->getLoad() << " == " << it->computeLoad(instance.getList_nodes()) << std::endl;
			assert(it->getLoad() == it->computeLoad(instance.getList_nodes()));
//            std::cout << it->get_cost() << " == " << it->computeCost(instance.get_distance_matrix()) << std::endl;
			assert(it->get_cost() == it->computeCost(instance.get_distance_matrix()));
			it->set_id(ctr_id);
			ctr_id++;
			it++;
		}
	}

	return CVRP_Solution(m_list_vehicles);
}


