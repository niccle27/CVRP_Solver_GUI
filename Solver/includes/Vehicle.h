#pragma once
#include <list>
#include "Node.h"
#include <vector>
class Vehicle
{
public:
    Vehicle(int t_maxLoad);
	Vehicle(int t_maxLoad, int first_node, int first_node_load);
	~Vehicle();
	void print_list()const;
	std::vector<int> getListIndexNodes() { return listIndexNodes; };
    int getLoad()const {return m_load;};
	int get_first_customer() { return listIndexNodes[1]; };
	int get_last_customer() { return listIndexNodes[listIndexNodes.size()-2]; };
	int get_node_at_index(int index) { return listIndexNodes[index]; };
	int get_number_of_customers() { return listIndexNodes.size() - 2; };
	int get_cost() { return m_cost; };
	void set_customer_at_index(int index, int cust_index);
	void insert_customer_at_index(int index, int cust_index);
	void delete_customer_at_index(int index);
	void addCost(int add) { m_cost += add; };
	void subCost(int sub) { m_cost -= sub; };
	void addLoad(int add) { m_load += add; };
	void subLoad(int sub) { m_load -= sub; };
	int popFront();
	int popBack();
	void add_customer_to_front(int index);
	void add_customer_to_back(int index);
	bool hasCustomers() { return listIndexNodes.size() > 2; };
	void display(bool disp_load = true, bool disp_cost = false)const;
	int computeCost(const std::vector < std::vector<int>> distance_matrix);
	int computeLoad(const std::vector<Node> list_nodes);
	void set_id(int t_id) { m_id = t_id; };
	int get_id() { return m_id; };


private: 
    int m_load=0;
    int m_maxLoad;
	int m_cost = 0;
	std::vector<int> listIndexNodes;
	int m_id = 0;
private:
	bool is_enough_capacity_left(int capacity_to_add);
};
