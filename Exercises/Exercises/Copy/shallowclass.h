#pragma once

class ShallowClass
{
public:
	ShallowClass();
	ShallowClass(int value);
	~ShallowClass();

	void print();

	void setValue(int value) { *m_data = value; }

private:
	int *m_data;

};
