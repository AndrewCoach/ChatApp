/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//add all the new state imports here
#include "ListeningState.h"
#include "InitialState.h"
#include "ConnectionState.h"
#include "ChattingState.h"

class MyInterProcessConnection;

// THE INTERPROCESS CONNECTION SERVER CLASS
class MyInterProcessConnectionServer : public InterprocessConnectionServer
{
public:
    MyInterProcessConnectionServer(AppState* pWayBack1);
    ~MyInterProcessConnectionServer();

    InterprocessConnection* createConnectionObject() override;

    InterprocessConnection* theCreatedOne;
    AppState* pWayBack;
private:

};

// THE INTERPROCESS CONNECTION CLASS
class MyInterProcessConnection : public InterprocessConnection
{
public:
    MyInterProcessConnection(AppState* pWayBack1);
    ~MyInterProcessConnection();
    
    void connectionMade() override;
    void connectionLost() override;
    void messageReceived(const MemoryBlock& message) override;
    
    AppState* pWayBack;

private:
   
};

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint(Graphics&) override;
    void resized() override;
    void changeState(AppState* neWState);



    String nameString;
    AppState* pCurAppState;
    std::vector<AppState*> vecPoint;

    MyInterProcessConnectionServer* pServer;
    MyInterProcessConnection* pSocket;
    
    
    
    //==============================================================================
    // Your private member variables go here...
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
