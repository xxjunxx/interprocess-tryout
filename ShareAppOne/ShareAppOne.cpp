#include <iostream>
#include <boost/interprocess/ipc/message_queue.hpp>
#include "ShareDataDll.h"
using namespace boost::interprocess;

int main()
{
 /*   std::cout << nShareDataDll << "\n";
    int input;
    if(std::cin >> input)
    { }*/
    //try {
    //    //Erase previous message queue
    //    message_queue::remove("message_queue");

    //    //Create a message_queue.
    //    message_queue mq
    //    (create_only               //only create
    //        , "message_queue"           //name
    //        , 100                       //max message number
    //        , sizeof(int)               //max message size
    //    );

    //    int input;
    //    while(std::cin >> input)
    //    {
    //        mq.send(&input, sizeof(input), 0);
    //        if (input == 99)
    //        {
    //            return 1;
    //        }
    //    }
    //}
    //catch (interprocess_exception& ex) {
    //    std::cout << ex.what() << std::endl;
    //    return 1;
    //}

}