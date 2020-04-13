#include "IMetaheuristic.h"
#include <iostream>
#include <assert.h> 

IMetaheuristic::IMetaheuristic(bool t_isVerbose)
{
	this->m_isVerbose = t_isVerbose;
}

Vehicle* IMetaheuristic::pick_random_vehicle()
{
	int index = rand() % current_solution.get_number_of_vehicles();
	return current_solution.get_vehicle_by_index(index);
}

int IMetaheuristic::pick_random_customer_index(Vehicle* vehicle)
{
	int index = rand() % vehicle->get_number_of_customers()+1;// cannot be depot, so +1
	return index;
}

int IMetaheuristic::pick_random_insert_location_index(Vehicle* vehicle)
{
	int index = rand() % (vehicle->get_number_of_customers()+1) + 1;// cannot be depot, so +1
	return index;
}

int IMetaheuristic::get_distance_node2node(int id_node1, int id_node2)
{
	return cvrp_instance.get_distance_node2node(id_node1, id_node2);
}

Node IMetaheuristic::get_customer_at_index(int index)
{
	return cvrp_instance.getNodeByIndex(index);
}

bool IMetaheuristic::exchange_customers_between_vehicles()
{
	Vehicle* v_1, * v_2;
	int delta;
	do {
		v_1 = pick_random_vehicle();
		v_2 = pick_random_vehicle();
	} while (v_1 == v_2);
	int index_cust_1 = pick_random_customer_index(v_1);
	int load_v1 = v_1->getLoad();
	int load_v2 = v_2->getLoad();
	int index_cust_2 = pick_random_customer_index(v_2);
	int demand_cust_1 = get_customer_at_index(v_1->get_node_at_index(index_cust_1)).getDemand();
	int demand_cust_2 = get_customer_at_index(v_2->get_node_at_index(index_cust_2)).getDemand();
	if (((load_v1 - demand_cust_1 + demand_cust_2) > cvrp_instance.getMaxCapacityPerVehicle()) ||
		((load_v2 - demand_cust_2 + demand_cust_1) > cvrp_instance.getMaxCapacityPerVehicle())) {
		return false;
	}
	int delta_v1 = (get_distance_node2node(v_1->get_node_at_index(index_cust_1 - 1), v_2->get_node_at_index(index_cust_2)) +
		get_distance_node2node(v_2->get_node_at_index(index_cust_2), v_1->get_node_at_index(index_cust_1 + 1))) -
		(get_distance_node2node(v_1->get_node_at_index(index_cust_1 - 1), v_1->get_node_at_index(index_cust_1)) +
			get_distance_node2node(v_1->get_node_at_index(index_cust_1), v_1->get_node_at_index(index_cust_1 + 1)));
	int delta_v2 = (get_distance_node2node(v_2->get_node_at_index(index_cust_2 - 1), v_1->get_node_at_index(index_cust_1)) +
		get_distance_node2node(v_1->get_node_at_index(index_cust_1), v_2->get_node_at_index(index_cust_2 + 1))) -
		(get_distance_node2node(v_2->get_node_at_index(index_cust_2 - 1), v_2->get_node_at_index(index_cust_2)) +
			get_distance_node2node(v_2->get_node_at_index(index_cust_2), v_2->get_node_at_index(index_cust_2 + 1)));
	delta = delta_v1 + delta_v2;
	if (isSolutionAccepted(delta))
	{
		int tmp_cust1 = v_1->get_node_at_index(index_cust_1);
		int tmp_cust2 = v_2->get_node_at_index(index_cust_2);
		v_1->set_customer_at_index(index_cust_1, tmp_cust2);
		v_1->subLoad(demand_cust_1);
		v_1->addLoad(demand_cust_2);
		v_1->addCost(delta_v1);
		v_2->set_customer_at_index(index_cust_2, tmp_cust1);
		v_2->subLoad(demand_cust_2);
		v_2->addLoad(demand_cust_1);
		v_2->addCost(delta_v2);
//        std::cout << v_1->get_cost() << " == " << v_1->computeCost(cvrp_instance.get_distance_matrix()) << std::endl;
		//std::cout << (v_1->get_cost() == v_1->computeCost(cvrp_instance.get_distance_matrix())) << std::endl;
		//std::cout << (int(v_1->get_cost()) == int(v_1->computeCost(cvrp_instance.get_distance_matrix()))) << std::endl;
		assert(v_1->get_cost() == v_1->computeCost(cvrp_instance.get_distance_matrix()));
//        std::cout << v_2->get_cost() << " == " << v_2->computeCost(cvrp_instance.get_distance_matrix()) << std::endl;
		//std::cout << (v_2->get_cost() == v_2->computeCost(cvrp_instance.get_distance_matrix())) << std::endl;
		//std::cout << (int(v_2->get_cost()) == int(v_2->computeCost(cvrp_instance.get_distance_matrix()))) << std::endl;
		assert(v_2->get_cost() == v_2->computeCost(cvrp_instance.get_distance_matrix()));
//        std::cout << v_1->getLoad() << " == " << v_1->computeLoad(cvrp_instance.getList_nodes()) << std::endl;
//        std::cout << v_2->getLoad() << " == " << v_2->computeLoad(cvrp_instance.getList_nodes()) << std::endl;
		assert(v_1->getLoad() == v_1->computeLoad(cvrp_instance.getList_nodes()));
		assert(v_2->getLoad() == v_2->computeLoad(cvrp_instance.getList_nodes()));

	}
	return delta<0;
}

bool IMetaheuristic::transfert_customer()
{
	Vehicle* v_1, * v_2;
	int delta;
	do {
		v_1 = pick_random_vehicle();
		v_2 = pick_random_vehicle();
	} while (v_1 == v_2 || v_1->get_number_of_customers()<2);
	int load_v1 = v_1->getLoad();
	int load_v2 = v_2->getLoad();
	int index_cust_1 = pick_random_customer_index(v_1);
	int index_insertion = pick_random_insert_location_index(v_2);
	int tmp_cust_1 = v_1->get_node_at_index(index_cust_1);
	int demand_cust_1 = get_customer_at_index(tmp_cust_1).getDemand();



	if ((load_v2 + demand_cust_1) > cvrp_instance.getMaxCapacityPerVehicle()) {
		return false;
	}
	int delta_v1 = (get_distance_node2node(v_1->get_node_at_index(index_cust_1 - 1), v_1->get_node_at_index(index_cust_1+1))-
	(get_distance_node2node(v_1->get_node_at_index(index_cust_1 - 1), v_1->get_node_at_index(index_cust_1))+
		get_distance_node2node(v_1->get_node_at_index(index_cust_1), v_1->get_node_at_index(index_cust_1 + 1))));
	int delta_v2 = (get_distance_node2node(v_2->get_node_at_index(index_insertion - 1), v_1->get_node_at_index(index_cust_1)) +
		get_distance_node2node(v_1->get_node_at_index(index_cust_1), v_2->get_node_at_index(index_insertion))) -
		get_distance_node2node(v_2->get_node_at_index(index_insertion - 1), v_2->get_node_at_index(index_insertion));
		
	delta = delta_v1 + delta_v2;
	if (isSolutionAccepted(delta))
	{		
		v_2->insert_customer_at_index(index_insertion, tmp_cust_1);
		v_1->delete_customer_at_index(index_cust_1);
		v_1->subLoad(demand_cust_1);
		v_1->addCost(delta_v1);
		v_2->addLoad(demand_cust_1);
		v_2->addCost(delta_v2);
//        std::cout << v_1->get_cost() << " == " << v_1->computeCost(cvrp_instance.get_distance_matrix()) << std::endl;
		//std::cout << (v_1->get_cost() == v_1->computeCost(cvrp_instance.get_distance_matrix())) << std::endl;
		//std::cout << int(v_1->get_cost()) << " == " << int(v_1->computeCost(cvrp_instance.get_distance_matrix())) << std::endl;
		//std::cout << (int(v_1->get_cost()) == int(v_1->computeCost(cvrp_instance.get_distance_matrix()))) << std::endl;
		assert(v_1->get_cost() - v_1->computeCost(cvrp_instance.get_distance_matrix()) <= 1);
//        std::cout << v_2->get_cost() << " == " << v_2->computeCost(cvrp_instance.get_distance_matrix()) << std::endl;
		//std::cout << (v_2->get_cost() == v_2->computeCost(cvrp_instance.get_distance_matrix())) << std::endl;
		//std::cout << int(v_2->get_cost()) << " == " << int(v_2->computeCost(cvrp_instance.get_distance_matrix())) << std::endl;
		//std::cout << (int(v_2->get_cost()) == int(v_2->computeCost(cvrp_instance.get_distance_matrix()))) << std::endl;
		assert(v_2->get_cost() == v_2->computeCost(cvrp_instance.get_distance_matrix()));
//        std::cout << v_1->getLoad() << " == " << v_1->computeLoad(cvrp_instance.getList_nodes()) << std::endl;
//        std::cout << v_2->getLoad() << " == " << v_2->computeLoad(cvrp_instance.getList_nodes()) << std::endl;
		assert(v_1->getLoad() == v_1->computeLoad(cvrp_instance.getList_nodes()));
		assert(v_2->getLoad() == v_2->computeLoad(cvrp_instance.getList_nodes()));
		//std::cout << "---------------------------------" << std::endl;
		//std::cout <<"vehicule["<<v_1->get_id()<<"] cust: "<< tmp_cust_1 << " at pos: "<< index_cust_1 << std::endl;
		//std::cout << "vehicule[" << v_2->get_id() << "] " << "insert at : " << index_insertion << std::endl;
		//std::cout << "index_insertion : " << index_insertion << std::endl;
//        current_solution.display();
		//current_solution.display_cost();
	}
	//std::cout << "delta: " << delta << std::endl;
	return delta < 0;
}

bool IMetaheuristic::exchange_customers_in_vehicle()
{
	Vehicle* v_1;
	int delta;
	int index_cust_1, prev_cust_1, next_cust_1;
	int index_cust_2, prev_cust_2, next_cust_2;
	do {
		v_1 = pick_random_vehicle();
	} while (v_1->get_number_of_customers()<2);
	do {
		index_cust_1 = pick_random_customer_index(v_1);
		index_cust_2 = pick_random_customer_index(v_1);
	} while (index_cust_1== index_cust_2);
	int cust1 = v_1->get_node_at_index(index_cust_1);
	int cust2 = v_1->get_node_at_index(index_cust_2);
	if ((index_cust_2 - index_cust_1) == 1)
	{
		prev_cust_2 = v_1->get_node_at_index(index_cust_1 - 1);
		next_cust_2 = cust1;
		prev_cust_1 = cust2;
		next_cust_1 = v_1->get_node_at_index(index_cust_2 + 1);
	}
	else if((index_cust_1 - index_cust_2) == 1){
		prev_cust_2 = cust1;
		next_cust_2 = v_1->get_node_at_index(index_cust_1 + 1);
		prev_cust_1 = v_1->get_node_at_index(index_cust_2 - 1);
		next_cust_1 = cust2;
	}
	else {
		prev_cust_2 = v_1->get_node_at_index(index_cust_1 - 1);
		next_cust_2 = v_1->get_node_at_index(index_cust_1 + 1);
		prev_cust_1 = v_1->get_node_at_index(index_cust_2 - 1);
		next_cust_1 = v_1->get_node_at_index(index_cust_2 + 1);
	}

	int demand_cust_1 = get_customer_at_index(index_cust_1).getDemand();
	int demand_cust_2 = get_customer_at_index(index_cust_1).getDemand();

	delta = (get_distance_node2node(prev_cust_2, cust2) +
			 get_distance_node2node(cust2, next_cust_2) +
			 get_distance_node2node(prev_cust_1, cust1) +
			 get_distance_node2node(cust1, next_cust_1)) -
			(get_distance_node2node(v_1->get_node_at_index(index_cust_1 - 1), cust1) +
			 get_distance_node2node(cust1, v_1->get_node_at_index(index_cust_1 + 1)) +
			 get_distance_node2node(v_1->get_node_at_index(index_cust_2 - 1), cust2) +
			 get_distance_node2node(cust2, v_1->get_node_at_index(index_cust_2 + 1)));

	//delta = (get_distance_node2node(v_1->get_node_at_index(index_cust_1 - 1), cust2) +
	//	     get_distance_node2node(cust2, v_1->get_node_at_index(index_cust_1 + 1)) +
	//	     get_distance_node2node(v_1->get_node_at_index(index_cust_2 - 1), cust1) +
	//	     get_distance_node2node(cust1, v_1->get_node_at_index(index_cust_2 + 1))) -
	//	    (get_distance_node2node(v_1->get_node_at_index(index_cust_1 - 1), cust1) +
	//		 get_distance_node2node(cust1, v_1->get_node_at_index(index_cust_1 + 1)) +
	//		 get_distance_node2node(v_1->get_node_at_index(index_cust_2 - 1), cust2) +
	//		 get_distance_node2node(cust2, v_1->get_node_at_index(index_cust_2 + 1))) ;

	if (isSolutionAccepted(delta))
	{

		v_1->set_customer_at_index(index_cust_1, cust2);
		v_1->set_customer_at_index(index_cust_2, cust1);
		v_1->addCost(delta);
//        std::cout << v_1->getLoad() << " == " << v_1->computeLoad(cvrp_instance.getList_nodes()) << std::endl;
//        std::cout << v_1->get_cost() << " == " << v_1->computeCost(cvrp_instance.get_distance_matrix()) << std::endl;
		//std::cout << (v_1->get_cost() == v_1->computeCost(cvrp_instance.get_distance_matrix())) << std::endl;
		//std::cout << int(v_1->get_cost()) << " == " << int(v_1->computeCost(cvrp_instance.get_distance_matrix())) << std::endl;
		//std::cout << (int(v_1->get_cost()) == int(v_1->computeCost(cvrp_instance.get_distance_matrix()))) << std::endl;
		assert(v_1->get_cost() - v_1->computeCost(cvrp_instance.get_distance_matrix()) <= 1);
		assert(v_1->getLoad() == v_1->computeLoad(cvrp_instance.getList_nodes()));
		//std::cout << "---------------------------------" << std::endl;		
		//std::cout << "vehicule[" << v_1->get_id() << "] " << "Switch "<< cust1 <<" with "<< cust2 <<" delta : "<<delta<< std::endl;
		//current_solution.display();
		//current_solution.display_cost();
	}
	return delta < 0;
}
