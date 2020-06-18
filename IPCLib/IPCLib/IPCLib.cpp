#include "IPCLib.h"
#include "boost/interprocess/ipc/message_queue.hpp"

using namespace boost::interprocess;

namespace IPC
{
	void createQueue()
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
		}
		catch (interprocess_exception& ex) {
			//message_queue::remove("message_queue");
			std::cout << ex.what() << std::endl;
		}
	}
	
	void sendMessage()
	{
		try
		{
			int message = 10;
			message_queue mq
			(open_only        //only create
				, "message_queue"  //name
			);
			mq.send(&message, sizeof(message), 0);
		}
		catch (interprocess_exception& ex) {
			//message_queue::remove("message_queue");
			//std::cout << ex.what() << std::endl;
		}
	}
	
	int receiveMessage()
	{
		try
		{
			message_queue mq
			(open_only        //only create
				, "message_queue"  //name
			);

			unsigned int priority;
			message_queue::size_type recvd_size;

			int number;
			mq.receive(&number, sizeof(number), recvd_size, priority);
			return number;
			//std::cout << number << "\n";
		}
		catch (interprocess_exception& ex) {
			//message_queue::remove("message_queue");
			return -1;
			//std::cout << ex.what() << std::endl;
		}
	}

	void openQueue()
	{
		try
		{
			message_queue mq
			(open_only        //only create
				, "message_queue"  //name
			);
		}
		catch (interprocess_exception& ex) {
			//message_queue::remove("message_queue");
		}
	}

	void removeQueue()
	{
		message_queue::remove("message_queue");
	}
}