#pragma once
#include "CVRP_instance.h"
#include "CVRP_Solution.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
class IMetaheuristic
{
	protected:
		bool m_isVerbose;
	protected:	
		CVRP_instance cvrp_instance;
		CVRP_Solution best_solution;
		CVRP_Solution current_solution;
	protected:
		IMetaheuristic(bool t_isVerbose = false);
		virtual CVRP_Solution optimize(const CVRP_instance& instance, const CVRP_Solution& solution) = 0;
		virtual bool isSolutionAccepted(int delta) = 0;
		Vehicle* pick_random_vehicle();
		int pick_random_customer_index(Vehicle* vehicle);
		int pick_random_insert_location_index(Vehicle* vehicle);
        int get_distance_node2node(int id_node1, int id_node2);
		Node get_customer_at_index(int index); 
		bool exchange_customers_between_vehicles();
		bool transfert_customer();
		bool exchange_customers_in_vehicle();
};

