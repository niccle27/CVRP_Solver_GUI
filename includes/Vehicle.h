#pragma once
#include <list>
#include "Node.h"
#include <vector>
class Vehicle
{
public:
    Vehicle(int t_capacityMax, Node* t_customer1);
    Vehicle(int t_capacityMax, Node* t_customer1, Node* t_customer2);
	~Vehicle();
	bool addNode(Node* t_node, Node* neighbour);
	void print_list()const;
	std::vector<int> getVectorOfIds();

private:
	int capacity;
    int capacityMax;
	std::list<Node*> list_customers;
private:
	bool is_enough_capacity_left(int cap1, int cap2 = 0);

};
