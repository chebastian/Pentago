#include "PlayState.h"
#include "InputManager.h"
#include "PentagoBase.h"
#include "Entity.h"
#include "Board.h"
#include "GameBoard.h"
#include "GameRound.h"
#include "PlaceRound.h"
#include "RotateRound.h"
#include "NetworkPlayer.h"
#include "HumanPlayer.h"
#include "NetworkListenerActor.h"

PlayState::PlayState(PentagoBase* base)
	:GameState(base )
{
	mStateID = 5;
	mGame->GetInput()->AddKeyboardListener(this);
	mEntity = new Entity(756);
	mGame->GetInput()->AddMouseListener(mEntity);
}


PlayState::~PlayState(void)
{
	mGame->GetInput()->RemoveKeyboardListener(this);
	mGame->GetInput()->RemoveMouseListener(mEntity);
}

void PlayState::OnEnter()
{
	mGameBoard = new GameBoard();
	mGameBoard->initBoard();

	setupPlayers();

	//NetworkPlayer* nw = new NetworkPlayer(mGame,mGameBoard);
	//HumanPlayer* hp = new HumanPlayer(mGame,mGameBoard);
	//mGame->GetInput()->AddMouseListener(nw);
	
	PlaceRound* round = new PlaceRound(mGame,mGameBoard,PLAYER_1);
	//RotateRound* rotRound = new RotateRound(mGame,mGameBoard,PLAYER_1);
	//mGame->PlayerClient()->addServerMessageListener(round);
	//NetworkListenerActor* nwListener = new NetworkListenerActor(mGame,mGameBoard);
	
	mGame->PlayerClient()->addServerMessageListener(mPlayerOne);
	mGame->PlayerClient()->addServerMessageListener(mPlayerTwo);
	mRoundMachine = new RoundMachine(mGame,mGameBoard,round,mPlayerOne,mPlayerTwo);
	mRoundMachine->InitMachine();
}

void PlayState::setupPlayers()
{
	if(mGame->PlayerClient()->IsPlayerOne())
	{
		mPlayerOne = new NetworkPlayer(mGame,mGameBoard);
		mPlayerTwo = new NetworkListenerActor(mGame,mGameBoard);
		mGame->GetInput()->AddMouseListener(mPlayerOne);
	}
	else
	{
		mPlayerOne = new NetworkListenerActor(mGame,mGameBoard);
		mPlayerTwo = new NetworkPlayer(mGame,mGameBoard);
		mGame->GetInput()->AddMouseListener(mPlayerTwo);
	}
}

void PlayState::Update(const float& time)
{
	mRoundMachine->CurrentPlayer()->update(time);
	mRoundMachine->ActiveRound()->OnUpdate(time);

	if(mRoundMachine->ActiveRound()->isDone())
	{
		mRoundMachine->NextRound();
	}
}

void PlayState::Render(SDL_Surface* gs)
{
	mEntity->Render(gs);
	
	if(!mGame->PlayerClient()->ConnectedToServer())
	{
		SDLWrapper::GetInstance()->RenderString("Waiting for server...", 0,0);
	}
	else
	{
		SDLWrapper::GetInstance()->RenderString("Connection etablished", 0,0);
		//SDLWrapper::GetInstance()->RenderString(mGame->PlayerClient()->latestMsgFromServer(), 10,20);

		//SDLWrapper::GetInstance()->RenderString(mMsg, 10,SDLWrapper::GetInstance()->Screen()->h - 20);
		
		Entity other = Entity(6);
		SFMath::Vector2Di pos = SFMath::Vector2Di(0,0);
		pos.x = mGame->PlayerClient()->GetLatestPacketFromServer().x;
		pos.y = mGame->PlayerClient()->GetLatestPacketFromServer().y;

		other.setPosition(pos);
		other.Render(gs);
		mRoundMachine->ActiveRound()->OnRender(gs);
		mGameBoard->Render(gs);

		SDLWrapper::GetInstance()->RenderString(mRoundMachine->CurrentPlayer()->Name(),20,20);
	}
}

void PlayState::OnExit()
{
	mGame->PlayerClient()->clientShutdown();
}

void PlayState::OnKeyDown(KeyEvent& evt)
{
	std::string validChars = "qwertyuiopasdfghjklzxcvbnm,.1234567890 ";

	if( validChars.find(evt.keyChar) != std::string::npos)
		mMsg += evt.keyChar;

	if(evt.KeyCode == Key_Code::KC_ENTER)
	{
		ClientMessage msg = ClientMessage();
		msg.x = mEntity->Position().x;
		msg.y = mEntity->Position().y;
		mGame->PlayerClient()->SendClientMessage(msg);
		//mGame->PlayerClient()->SendMessageToServer(mMsg);
		mMsg = "";
	}
	if(evt.KeyCode == Key_Code::KC_ESC)
	{
		mGame->ChangeState(new GameState(mGame));
	}
}

const int& PlayState::KeyListenerId()
{
	return this->mStateID;
}