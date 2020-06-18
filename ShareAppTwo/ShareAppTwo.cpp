#include <iostream>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <thread>
#include "SWI-cpp.h"

using namespace boost::interprocess;
void sendM()
{
	message_queue::remove("message_queue");
	message_queue mq
	(create_only               //only create
		, "message_queue"           //name
		, 100                       //max message number
		, sizeof(int)               //max message size
	);
	int number;
	while (true)
	{
		unsigned int priority;
		message_queue::size_type recvd_size;
		mq.receive(&number, sizeof(number), recvd_size, priority);
		std::cout <<"Other thread receive:"<< number << " \n";
	}
}


bool LoadFile()
{
	try
	{
		// Loads just the next result and immediately quits the query.
		// consult is a prologue command that loads the file.
		PlCall(("consult('C:/Users/Xiaojun Lan/Documents/Visual Studio 2017/interprocess-tryout/x64/Debug/init.pl')"));
		PlCall("consult('C:/Users/Xiaojun Lan/Desktop/packages-cpp/test.pl')");
		std::cout << "File loaded." << "\n";
		return true;
	}
	catch (PlException &ex)
	{
		std::cout << "Exception:" << (char*)ex.name() << "\n";
		return false;
	}

	return false;
}

int
main(int argc, char **argv)
{

	std::thread first(sendM);
	term_t a1;
	term_t a2;
	const char* StdFunctionName = "rosprolog_query";
	predicate_t pre;
	qid_t qid;

	// Set home directory to thirdparty/swipl
	_putenv("SWI_HOME_DIR=C:/Xiaojun/swipl");

	// Values have no influence on PL_initialise
	static char *args[] = { const_cast<char*>(""), NULL };

	if (!PL_initialise(1, args)) {

		// PL_initialise always fails (return 0). PL_cleanup ensures a correct initialization.
		PL_cleanup(1);
	}

	// Tests if PL has been initialized and outputs a log accordingly.
	int* a = nullptr;
	char*** b = nullptr;
	if (PL_is_initialised(a, b))
	{
		std::cout << "PL_init is initialised" << "\n";
		if (LoadFile())
		{
			std::cout << "PL_init load init file. suc." << "\n";
		}
		else
		{
			std::cout << "PL_init could not load init file. ERROR" << "\n";
		}
	}
	else
	{
		std::cout << "PL_init is not initialised" << "\n";
	}
	

	while (true)
	{
		std::string goal;
		std::cin >> goal;
		std::cout << goal.c_str()<<"\n";
		try
		{
			// Generates term for the string and for the returning result.
			a1 = PL_new_term_refs(2);
			a2 = a1 + 1;
			PL_put_atom_chars(a1, goal.c_str());
			pre = PL_predicate(StdFunctionName, 2, NULL);

			// Opens a query. First element designates the SWI-Prolog function, 
			// which should be called (here rosprolog_query from the loaded .pl file).
			qid = PL_open_query(NULL, PL_Q_NORMAL, pre, a1);

			if (!PL_next_solution(qid))
			{
				PL_cut_query(qid);
				PL_reset_term_refs(a1);
				std::cout << "no solution false\n";
			}

			// read the JSON encoded solution.
			atom_t atom;
			const char* AnswerString = "";

			if (!PL_get_atom(a2, &atom))
			{
				std::cout << "Error, no result (atom a2)\n";

			}
			else
			{
				// Fetches the answer from the atom into a string.
				const char* AnswerString = PL_atom_chars(atom); 
				std::cout << "result:" << AnswerString << "\n";
			}

		}
		catch (PlException& e)
		{
			// Indicate that there was an exception.
			std::cout << "Exception:" << (char*)e.name() << "\n";
		}
	}
	first.join();
}



//#define WIN32_LEAN_AND_MEAN
//
//#include <windows.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <iostream>
//
//// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
//#pragma comment (lib, "Ws2_32.lib")
//#pragma comment (lib, "Mswsock.lib")
//#pragma comment (lib, "AdvApi32.lib")
//
//
//#define DEFAULT_BUFLEN 512
//#define DEFAULT_PORT "27015"
//
//int __cdecl main(int argc, char **argv)
//{
//	WSADATA wsaData;
//	SOCKET ConnectSocket = INVALID_SOCKET;
//	struct addrinfo *result = NULL,
//		*ptr = NULL,
//		hints;
//	char *sendbuf = new char[256];
//	char recvbuf[DEFAULT_BUFLEN];
//	int iResult;
//	int recvbuflen = DEFAULT_BUFLEN;
//
//	// Validate the parameters
//	if (argc != 2) {
//		printf("usage: %s server-name\n", argv[0]);
//		return 1;
//	}
//
//	// Initialize Winsock
//	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
//	if (iResult != 0) {
//		printf("WSAStartup failed with error: %d\n", iResult);
//		return 1;
//	}
//
//	ZeroMemory(&hints, sizeof(hints));
//	hints.ai_family = AF_UNSPEC;
//	hints.ai_socktype = SOCK_STREAM;
//	hints.ai_protocol = IPPROTO_TCP;
//
//	// Resolve the server address and port
//	iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
//	if (iResult != 0) {
//		printf("getaddrinfo failed with error: %d\n", iResult);
//		WSACleanup();
//		return 1;
//	}
//
//	// Attempt to connect to an address until one succeeds
//	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
//
//		// Create a SOCKET for connecting to server
//		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
//			ptr->ai_protocol);
//		if (ConnectSocket == INVALID_SOCKET) {
//			printf("socket failed with error: %ld\n", WSAGetLastError());
//			WSACleanup();
//			return 1;
//		}
//
//		// Connect to server.
//		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
//		if (iResult == SOCKET_ERROR) {
//			int iError = WSAGetLastError();
//			if (iError == WSAEWOULDBLOCK)
//				printf("recv failed with error: WSAEWOULDBLOCK\n");
//			else
//				printf("recv failed with error: %ld\n", iError);
//
//			closesocket(ConnectSocket);
//			ConnectSocket = INVALID_SOCKET;
//			continue;
//		}
//		break;
//	}
//
//	freeaddrinfo(result);
//
//	if (ConnectSocket == INVALID_SOCKET) {
//		printf("Unable to connect to server!\n");
//		WSACleanup();
//		return 1;
//	}
//	std::cout << "connected to server, input message\n";
//	
//	while (std::cin >> sendbuf) {
//		// Send an initial buffer
//		iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
//		if (iResult == SOCKET_ERROR) {
//			printf("send failed with error: %d\n", WSAGetLastError());
//			closesocket(ConnectSocket);
//			WSACleanup();
//			return 1;
//		}
//		printf("Bytes Sent: %ld\n", iResult);//
//		if (strcmp(sendbuf, "-1") == 0) {
//			break;
//		}
//	}
//
//	
//
//	// shutdown the connection since no more data will be sent
//	iResult = shutdown(ConnectSocket, SD_SEND);
//	if (iResult == SOCKET_ERROR) {
//		printf("shutdown failed with error: %d\n", WSAGetLastError());
//		closesocket(ConnectSocket);
//		WSACleanup();
//		return 1;
//	}
//
//	// Receive until the peer closes the connection
//	do {
//
//		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
//		if (iResult > 0)
//			printf("Bytes received: %d\n", iResult);
//		else if (iResult == 0)
//			printf("Connection closed\n");
//		else
//			printf("recv failed with error: %d\n", WSAGetLastError());
//
//	} while (iResult > 0);
//
//	// cleanup
//	closesocket(ConnectSocket);
//	WSACleanup();
//
//	return 0;
//}