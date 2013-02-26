#include "ClientPlayer.h"
#include "Receivers.h"

ClientPlayer::ClientPlayer(const std::string& ip)
	:ClientBase(ip)
{
	mFoundPartner = false;
	mLatestPacket = ClientMessage();
	mListeners = std::vector<IMessageReceiver*>();
	mHasNewMessage = false;
	mLatestMessageRead = true;
	this->mClientID = CLIENT_ID; 
}


ClientPlayer::~ClientPlayer(void)
{
}


int ClientPlayer::connectToServer()
{
	CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)ClientPlayer::run_thread,(LPVOID)this,NULL,NULL);
	return RETURN_OK;
}

bool ClientPlayer::waitForServerResponse(int maxRetry)
{
	int counter = 0;
	mThreadRunning = true;
	const int MAX_RETRYS = maxRetry;
	const int RETRY_INTERVAL = 200;

	while(!mConnected && counter <= MAX_RETRYS)
	{
		std::cout << "Client: Waiting for server response..." << std::endl;		
		int res = connect(mConnectSocket,(SOCKADDR*)&mAddr,sizeof(mAddr));
		if( res == RETURN_OK)
		{
			u_long iMode = 1;
			ioctlsocket(mConnectSocket,FIONBIO,&iMode);
			mConnected = true;
			std::cout << "Server: OK" << std::endl;
			break;
		}
		std::cout << "Client: No response, Retrying in " << RETRY_INTERVAL << "ms" << std::endl;
		Sleep(RETRY_INTERVAL);
		counter++;
	}

	if(!mConnected)
	{
		std::cout << "Client cannot reach server, timeout" << std::endl;
		clientShutdown();
	}

	return mConnected;
}

DWORD ClientPlayer::run()
{
	waitForServerResponse(2);
	handleMessagesFromOtherClients();
	/*long  SLEEP_TIME = 200;
	while(mThreadRunning && mConnected)
	{
		const int bufsz = 64;
		char* buffer = new char[bufsz];
		int i = 0;
		ZeroMemory(buffer, bufsz);
		i = recv(mConnectSocket,buffer,bufsz,NULL);

		int err = WSAGetLastError();
		if(err == WSAECONNRESET)
		{
			delete[] buffer;
			clientShutdown();
			return 1;
		}

		if(WSAGetLastError() == WSAEWOULDBLOCK)
		{
			delete[] buffer;
			continue;
		}


		std::cout << "bytes:  " << i << std::endl;
		std::cout << buffer << std::endl;
		mMessage = std::string(buffer);
		delete[] buffer;
		Sleep(SLEEP_TIME);
	}*/
	return 0;
}	

void ClientPlayer::handleMessagesFromOtherClients()
{
	long  SLEEP_TIME = 200;
	while(mThreadRunning && mConnected)
	{
		ClientMessage msg = ClientMessage();
		int i = 0;
		i = recv(mConnectSocket,reinterpret_cast<char*>(&msg),sizeof(msg),NULL);

		int err = WSAGetLastError();
		if(err == WSAECONNRESET)
		{
			clientShutdown();
			return;
		}

		if(WSAGetLastError() == WSAEWOULDBLOCK)
		{
			if(LatestMessageRead())
				mHasNewMessage = false;

			continue;
		}

		std::cout << "bytes:  " << i << std::endl;
		mMessage = std::string(msg.text);
		mLatestPacket = msg;
		mHasNewMessage = true;
		mLatestMessageRead = false;

		SendMessageToListeners(msg);
		Sleep(SLEEP_TIME);
	}
}

const bool ClientPlayer::LatestMessageRead()
{
	if(mHasNewMessage)
	{
		return mLatestMessageRead;
	}

	return false;
}

void ClientPlayer::SendClientMessage(ClientMessage msg)
{
	send(mConnectSocket,reinterpret_cast<char*>(&msg),sizeof(msg),NULL);
}

ClientMessage ClientPlayer::GetLatestPacketFromServer()
{
	if(mHasNewMessage)
		mLatestMessageRead = true;

	return mLatestPacket;
}

const bool ClientPlayer::hasNewMessage()
{
	return mHasNewMessage;
}

void ClientPlayer::addServerMessageListener(IMessageReceiver* recv)
{
	mListeners.push_back(recv);
}

void ClientPlayer::SendMessageToListeners(ClientMessage msg)
{
	for(size_t i = 0; i < mListeners.size(); i++)
	{
		mListeners.at(i)->ProcessMessage(&msg);
	}

	if(msg.MsgType == ClientMessage::TYPE_SETUP_GAME)
	{
		std::cout << "GAME SETUP";
		this->mFoundPartner = true;
		mServerID = msg.message;
	}
}

void ClientPlayer::AddMessage( SFMessage* msg )
{
	//throw std::exception("The method or operation is not implemented.");
	msg = msg;
}

void ClientPlayer::ProcessMessage( SFMessage* msg )
{
	ClientMessage* cmsg = dynamic_cast<ClientMessage*>(msg);
	SendClientMessage(*cmsg);
	//SendMessageToListeners(*cmsg);
}

int ClientPlayer::ReceiverID()
{
	return CLIENT_ID;
	//throw std::exception("The method or operation is not implemented.");
}

void ClientPlayer::OnMessage( SFMessage* msg )
{
	msg = msg;
	throw std::exception("The method or operation is not implemented.");
}
