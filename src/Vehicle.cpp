#include "Vehicle.h"
#include "Node.h"
#include <iostream>

bool Vehicle::is_enough_capacity_left(int cap1, int cap2)
{
	int capToTest = cap1 + cap2;
	return capacity + capToTest <= capacityMax;
}

void Vehicle::print_list()const
{
	for (auto it = list_customers.begin(); it != list_customers.end(); ++it)
	{
		std::cout << (*it)->getId();
		auto next = std::next(it, 1);
		if (next != list_customers.end())
		{
			std::cout << ",";
		}
	}
}
bool Vehicle::addNode(Node* t_node, Node* neighbour = nullptr)
{
	if (!is_enough_capacity_left(t_node->getDemand()))
	{
		return false;
	}
	else
	{
		capacity += t_node->getDemand();
	}
	if (neighbour != nullptr)
	{
		Node* front_node = list_customers.front();
		Node* back_node = list_customers.back();
		if (neighbour == front_node)
		{
			list_customers.push_front(t_node);
			t_node->setVehicle(this);
			return true;
		}
		if (neighbour == back_node)
		{
			list_customers.push_back(t_node);
			t_node->setVehicle(this);
			return true;
		}
	}
	else
	{
		list_customers.push_back(t_node);
		t_node->setVehicle(this);
		return true;
	}
	return false;
}

Vehicle::Vehicle(Node* t_customer1)
{
	capacity = 0;
	addNode(t_customer1);
}

Vehicle::Vehicle(Node* t_customer1, Node* t_customer2)
{
	capacity = 0;
	addNode(t_customer1);
	addNode(t_customer2);
	//list_customers.push_back(t_customer1);
	//t_customer1->setVehicle(this);
	//list_customers.push_back(t_customer2);
	//t_customer2->setVehicle(this);
}

Vehicle::~Vehicle()
{
}