/*
  ==============================================================================

    InitialState.h
    Created: 21 Aug 2020 11:20:43am
    Author:  Ondrej

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppState.h"
//==============================================================================
/*
*/
class InitialState    : public AppState, public TextButton::Listener
{
public:
    InitialState(MainComponent* pMainT);
    ~InitialState();

    void returns() override;

    void paint (Graphics&) override;
    void resized() override;
    void buttonClicked(Button* button) override;



    Label listenerInfo;
    Label listenerLabel;
    TextEditor listenerPort;
    TextButton listenerButton;
    TextButton connectButton;
    
    Label name;
    TextEditor nameEditor;
    TextButton nameButton;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InitialState)
};
