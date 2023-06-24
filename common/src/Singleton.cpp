#include "Singleton.h"

#include <iostream>

void Singleton::setName(const std::string& vName) {
	m_Name = vName;
}

void Singleton::print() {
	printf("Singleton::print() : my name is %s\n", m_Name.c_str());
}
