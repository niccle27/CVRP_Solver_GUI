#pragma once
#include <vector>
#include "Node.h"
class CVRP_instance
{
private:
	std::vector<Node> list_nodes;
	std::vector<std::vector<int>> m_distanceMatrix;
    int m_maxCapacityPerVehicle;
	int m_nb_vehicles;
private:
	void set_list_nodes(std::vector<int> t_demands);
public:
	CVRP_instance(std::vector<int> t_demands, std::vector<std::vector<int>> t_distanceMatrix, int t_maxCapacityPerVehicle, int t_nb_vehicles);
	CVRP_instance();
	~CVRP_instance();
	int get_distance_node2node(int id_node1, int id_node2)const; 
	std::vector<std::vector<int>> get_distance_matrix()const { return m_distanceMatrix; };
	std::vector<Node> get_list_nodes() { return list_nodes; };
	void show_matrix()const;
	int get_distanceMatrix_dim()const;
	Node getNodeByIndex(int index)const { return list_nodes[index]; };	
    int getMaxCapacityPerVehicle()const{return m_maxCapacityPerVehicle;};
	int get_number_of_customers()const { return list_nodes.size() - 1; };
	std::vector<Node> getList_nodes()const{ return list_nodes; };
	int getNumberOfVehicles() const{ return m_nb_vehicles; };
};

