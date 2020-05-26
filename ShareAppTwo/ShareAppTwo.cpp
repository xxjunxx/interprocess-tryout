#include <iostream>
//#include "ShareDataDll.h"
__declspec(dllimport) int shareI;
int main()
{
    int input;
    while (std::cin >> input)
    {
        std::cout <<"shareI: "<< shareI <<"\n";
    }
}
