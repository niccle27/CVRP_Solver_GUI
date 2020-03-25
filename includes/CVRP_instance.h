#pragma once
#include <vector>
#include "Node.h"
class CVRP_instance
{
private:
	std::vector<Node*> m_vNodes;
	std::vector<std::vector<int>> m_distanceMatrix;
    int m_maxCapacityPerVehicle;
public:
	void setDistanceMatrix(std::vector<std::vector<int>> t_distanceMatrix);
	
public:
	int get_distance_node2node(int id_node1, int id_node2)const; 
	void show_matrix()const;
	int get_distanceMatrix_dim()const;
	int get_number_of_customers()const;

	CVRP_instance();
    CVRP_instance(std::vector<int> t_demands, std::vector<std::vector<int>> t_distanceMatrix, int t_maxCapacityPerVehicle);
	~CVRP_instance();

	std::vector<Node*> getNodes()const { return m_vNodes; };
	Node* getNodeByIndex(int index)const { return m_vNodes[index]; };
	void set_list_nodes(std::vector<int> t_demands);
    void setMaxCapacityPerVehicle(int t_maxCapacityPerVehicle);
    int getMaxCapacityPerVehicle()const{return m_maxCapacityPerVehicle;};


};

