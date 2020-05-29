#ifdef SHAREDATADLL_EXPORTS
#define SHAREDATADLL_API __declspec(dllexport)
#include <boost/interprocess/ipc/message_queue.hpp>
#else
#define SHAREDATADLL_API __declspec(dllimport)
#endif

#include <iostream>

using namespace boost::interprocess;

SHAREDATADLL_API bool InitMessageQueue();

bool SendMessage(int message); // not sure if declaration is needed
