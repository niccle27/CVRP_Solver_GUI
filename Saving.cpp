#include "Saving.h"
#include <iostream>

bool operator>(const Saving& c1, const Saving& c2)
{
	return c1.m_saving > c2.m_saving;
}

void Saving::display() const
{
	std::cout << "[" << id_cust_1 << "," << id_cust_2 << "]:" << m_saving << std::endl;
}
Saving::Saving(int id_cust_1, int id_cust_2, int m_saving) :id_cust_1(id_cust_1), id_cust_2(id_cust_2), m_saving(m_saving)
{
}


Saving::~Saving()
{
}
