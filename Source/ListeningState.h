/*
  ==============================================================================

    ListeningState.h
    Created: 14 Aug 2020 2:54:19pm
    Author:  Ondrej

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppState.h"



//==============================================================================
/*
*/
class ListeningState    : public AppState, public TextButton::Listener
{
public:
    ListeningState(MainComponent* pMainT, String buttonText);
    ~ListeningState();


    void returns() override;

    void paint (Graphics&) override;
    void resized() override;
    void buttonClicked(Button* button) override;


    TextButton bConnect;
    TextButton bOpen;
    

    TextEditor input;
    TextButton client1;
    TextButton client2;

public:


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ListeningState)
};
