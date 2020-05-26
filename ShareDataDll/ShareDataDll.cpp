// ShareDataDll.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "ShareDataDll.h"

   
// This is an example of an exported variable
SHAREDATADLL_API int nShareDataDll=0;

// This is an example of an exported function.
SHAREDATADLL_API int fnShareDataDll(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CShareDataDll::CShareDataDll()
{
    return;
}
