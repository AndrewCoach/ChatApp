/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "ListeningState.h"
#include "InitialState.h"
#include "ConnectionState.h"
#include "ChattingState.h"

// THE INTERPROCESS CONNECTION SERVER MEMBERS DEFINITION
MyInterProcessConnectionServer::MyInterProcessConnectionServer(AppState* pWayBack1) : pWayBack(pWayBack1), theCreatedOne(nullptr)
{

}

MyInterProcessConnectionServer::~MyInterProcessConnectionServer()
{
    if (theCreatedOne != nullptr)
       delete theCreatedOne;
}

InterprocessConnection* MyInterProcessConnectionServer::createConnectionObject()
{

    MyInterProcessConnection* pSocket = new MyInterProcessConnection(pWayBack);

    theCreatedOne = pSocket;
    //TRANSITION TO DIFFERENT STATE, BECAUSE SOMEONE CONNECTED TO US -- needs to be CHATTING STATE? + alert window
    AlertWindow::showMessageBox(AlertWindow::AlertIconType::InfoIcon, "Incoming connection!",
        "There is an Incomming connection !");
    pWayBack->pMain->changeState(new ChattingState(pWayBack->pMain, 1));

    //save pSocket somewhere so I can call sendMessage() on it!
    return pSocket;
}


// THE INTERPROCESS CONNECTION MEMBERS DEFINITION
MyInterProcessConnection::MyInterProcessConnection(AppState* pWayBack1) : pWayBack(pWayBack1)
{

}

MyInterProcessConnection::~MyInterProcessConnection()
{

}

void MyInterProcessConnection::connectionMade()
{

}

void MyInterProcessConnection::connectionLost()
{
    AlertWindow::showMessageBox(AlertWindow::AlertIconType::WarningIcon, "Connection lost!",
        "Connection between you and the other end has been dropped.");
    this->pWayBack->pMain->changeState(new InitialState(this->pWayBack->pMain));
}

void MyInterProcessConnection::messageReceived(const MemoryBlock& message)
{
    if (pWayBack != pWayBack->pMain->pCurAppState)
        pWayBack = pWayBack->pMain->pCurAppState;
    //SO THE POINTER TO APPSTATE DOES NOT REALLY POINT TO CURRENT APPSTATE?

    pWayBack->textBox.setText(message.toString());

    pWayBack->text = String(message.toString().toUTF8());

    pWayBack->textBox.moveCaretToEnd();
    pWayBack->textBox.scrollEditorToPositionCaret(0, 0);
    pWayBack->textBox.pageDown(0);

    pWayBack->resized();
}



//==============================================================================
MainComponent::MainComponent() : nameString(""),
    pCurAppState(new InitialState(this)) //if we need to pass something in to Initialstate, do it here
    , pServer(new MyInterProcessConnectionServer(pCurAppState)), pSocket(new MyInterProcessConnection(pCurAppState))
{


    this->addAndMakeVisible(*pCurAppState);
    
    setSize (1000, 700);

}

MainComponent::~MainComponent()
{
    for (auto& ptr : vecPoint)
    {
        delete ptr;
    }
    delete pCurAppState;

    delete pServer;
    delete pSocket;
}


void MainComponent::changeState(AppState* newState)
{
    AppState* deletThis = pCurAppState;
    pCurAppState = newState;
    this->addAndMakeVisible(*pCurAppState);
    

    vecPoint.push_back(deletThis);
    this->resized();
    // make the class delete itself?
    //delete deletThis; - same problem or leaks
}


//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    pCurAppState->returns();
    pCurAppState->setBounds(getLocalBounds());
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
