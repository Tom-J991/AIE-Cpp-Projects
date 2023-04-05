#include "shallowclass.h"

#include <iostream>

ShallowClass::ShallowClass()
	: m_data{new int(0)}
{}
ShallowClass::ShallowClass(int value)
	: m_data{new int(value)}
{}
ShallowClass::~ShallowClass()
{
	if (m_data != nullptr)
		delete m_data;
	m_data = nullptr;
}

void ShallowClass::print()
{
	std::cout << "Value " << *m_data << ", at memory location " << m_data << std::endl;
}
