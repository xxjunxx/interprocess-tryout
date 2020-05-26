#ifdef SHAREDATADLL_EXPORTS
#define SHAREDATADLL_API __declspec(dllexport)
#else
#define SHAREDATADLL_API __declspec(dllimport)
#endif

#pragma data_seg ("Shared")
SHAREDATADLL_API int shareI = 0;
#pragma data_seg()
#pragma comment(linker, "/Section:Shared,RWS")

// This class is exported from the dll
class SHAREDATADLL_API CShareDataDll {
public:
	CShareDataDll(void);
	// TODO: add your methods here.
};

extern SHAREDATADLL_API int nShareDataDll;

SHAREDATADLL_API int fnShareDataDll(void);
