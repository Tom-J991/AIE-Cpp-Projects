#include <iostream>

#include "deepclass.h"
#include "shallowclass.h"

int main()
{
    ShallowClass shallow1(10);
    ShallowClass shallow2 = shallow1;
    ShallowClass shallow3;

    shallow3 = shallow1;

    shallow1.setValue(27);

    shallow1.print();
    shallow2.print();
    shallow3.print();

    DeepClass deep1(15);
    DeepClass deep2 = deep1;
    DeepClass deep3;

    deep3 = deep1;

    deep1.setValue(27);

    deep1.print();
    deep2.print();
    deep3.print();

    std::cin.ignore();
    return 0;
}
