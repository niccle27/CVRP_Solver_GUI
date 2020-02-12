#pragma once
#include <list>
#include "Node.h"
#include <vector>
class Vehicle
{
public:
	static const int capacityMax = 40;
public:
	Vehicle(Node* t_customer1);
	Vehicle(Node* t_customer1, Node* t_customer2);
	~Vehicle();
	bool addNode(Node* t_node, Node* neighbour);
	void print_list()const;
	std::vector<int> getVectorOfIds();

private:
	int capacity;
	std::list<Node*> list_customers;
private:
	bool is_enough_capacity_left(int cap1, int cap2 = 0);

};
