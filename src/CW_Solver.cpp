#include "CW_Solver.h"
#include"Vehicle.h"
#include <algorithm>
#include <functional>

void CW_Solver::show_savings()
{
	for (auto it = m_list_saving.begin(); it != m_list_saving.end(); ++it)
	{
		it->display();
	}
}

CVRP_Solution* CW_Solver::solve(const CVRP_instance& instance)
{
	CVRP_Solution* solution = new CVRP_Solution();
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
//	show_savings(); // IF DISPLAY

	int numberOfCustomer = instance.get_number_of_customers();
	//std::vector<Vehicle*> list_vehicles;
	for (auto it = m_list_saving.begin(); it != m_list_saving.end(); ++it)
	{
		if (!it->isPositive()) break;
		if (numberOfCustomer == 0) break;
		int id_cust_1 = it->get_id_cust_1();
		int id_cust_2 = it->get_id_cust_2();

		if (instance.getNodeByIndex(id_cust_1)->isAvailable() && instance.getNodeByIndex(id_cust_2)->isAvailable())
		{
			int sumDemands = instance.getNodeByIndex(id_cust_1)->getDemand() + instance.getNodeByIndex(id_cust_2)->getDemand();
			if (sumDemands > Vehicle::capacityMax)
			{
				continue;
			}
			Vehicle* el = new Vehicle(instance.getNodeByIndex(id_cust_1), instance.getNodeByIndex(id_cust_2));
			solution->add_vehicle(el);
			numberOfCustomer -= 2;
		}
		else if (instance.getNodeByIndex(id_cust_1)->isAvailable())
		{
			bool isSuccessed = instance.getNodeByIndex(id_cust_2)->getVehicle()->addNode(instance.getNodeByIndex(id_cust_1), instance.getNodeByIndex(id_cust_2));
			if (isSuccessed)
			{
				numberOfCustomer -= 1;
			}
		}
		else if (instance.getNodeByIndex(id_cust_2)->isAvailable())
		{
			bool isSuccessed = instance.getNodeByIndex(id_cust_1)->getVehicle()->addNode(instance.getNodeByIndex(id_cust_2), instance.getNodeByIndex(id_cust_1));
			if (isSuccessed)
			{
				numberOfCustomer -= 1;
			}
		}
	}
	int i = 1;
	while (numberOfCustomer > 0)
	{
		if (instance.getNodeByIndex(i)->isAvailable()) {
			Vehicle* el = new Vehicle(instance.getNodeByIndex(i));
			solution->add_vehicle(el);
			numberOfCustomer -= 1;
		}
		++i;
	}
	return solution;
}


