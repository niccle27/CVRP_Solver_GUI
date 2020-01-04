#include "Node.h"

bool Node::isAvailable()
{
	return m_Vehicle == nullptr;
}
void Node::setVehicle(Vehicle* t_Vehicle) {
	m_Vehicle = t_Vehicle;
}

Node::Node(int t_id, int t_demand) :m_id(t_id), m_demand(t_demand)
{

}

Node::~Node()
{
}