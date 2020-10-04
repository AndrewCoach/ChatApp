/*
  ==============================================================================

    ChattingState.h
    Created: 21 Aug 2020 3:30:42pm
    Author:  Ondrej

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppState.h"
//==============================================================================
/*
*/
class ChattingState    : public AppState, public TextButton::Listener
{
public:
    ChattingState(MainComponent* pMainT, bool server);
    ~ChattingState();

    void paint (Graphics&) override;
    void resized() override;
    void returns() override;
    void buttonClicked(Button* button) override;

    bool isServer{ 0 };

    TextEditor input;
    TextButton send;
    
    TextButton exit;
    

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChattingState)
};
