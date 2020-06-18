#pragma once
#include <iostream>

namespace IPC
{
	void createQueue();
	void removeQueue();
	int receiveMessage();
	void sendMessage();
	void openQueue();
}