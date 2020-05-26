#include <iostream>

//#include "ShareDataDll.h"
__declspec(dllimport) int shareI;
int main()
{
    int input;
    while (std::cin >> input)
    {
        shareI += 1;
        std::cout << "increase one success\n";
    }
}