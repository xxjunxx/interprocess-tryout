#include <iostream>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <vector>

using namespace boost::interprocess;

int main()
{   
     try 
     {
         //Erase previous message queue
         message_queue::remove("message_queue");

         //Create a message_queue.
         message_queue mq
         (create_only               //only create
             , "message_queue"           //name
             , 100                       //max message number
             , sizeof(int)               //max message size
         );

        unsigned int priority;
        message_queue::size_type recvd_size;

        while(true)
        {
            int number;
            mq.receive(&number, sizeof(number), recvd_size, priority);
            std::cout << number << "\n";
            if (number == 99)
                return 1;
        }
    }
    catch (interprocess_exception& ex) {
        message_queue::remove("message_queue");
        std::cout << ex.what() << std::endl;
        return 1;
    }
    message_queue::remove("message_queue");
    return 0;
}
