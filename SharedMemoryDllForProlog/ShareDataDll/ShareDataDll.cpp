// ShareDataDll.cpp : Defines the exported functions for the DLL.
//

#include "ShareDataDll.h"

SHAREDATADLL_API bool InitMessageQueue()
{
    try 
    {
        //Erase previous message queue
        message_queue::remove("message_queue");

        //Create a message_queue.
        message_queue mq
        (create_only               //only create
            , "message_queue"           //name
            , 100                        //max message number
            , sizeof(int)               //max message size
        );
    }
    catch (interprocess_exception& ex) 
    {
        std::cout << ex.what() << std::endl;
        return false;
    }
    return true;
}

bool SendMessage(int message)
{
    std::cout << "Send\n ";
     try 
     {
         message_queue mq
         (open_only        //only create
             , "message_queue"  //name
         );

        mq.send(&message, sizeof(message), 0);

     }
    catch (interprocess_exception& ex) {
        std::cout << "diee\n";
        std::cout << ex.what() << std::endl;
        return false;
    }
    return true;
}
#ifdef SHAREDATADLL_EXPORTS

// ---------------- Prolog function -------------------// 
#pragma warning( disable : 4706 )
#include "SWI-cpp.h"
PREDICATE(hello, 1)
{
    std::cout << "Hello " << (char*)A1 << std::endl;
   
    return SendMessage(1);
}

PREDICATE(bye, 1)
{
    std::cout << "Bye " << (char*)A1 << std::endl;

    return  SendMessage(2);
}

#endif