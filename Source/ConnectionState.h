/*
  ==============================================================================

    ConnectionState.h
    Created: 21 Aug 2020 12:34:45pm
    Author:  Ondrej

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppState.h"
//==============================================================================
/*
*/
class ConnectionState    : public AppState, public TextButton::Listener
{
public:
    ConnectionState(MainComponent* pMainT);
    ~ConnectionState();


    void returns() override;

    void paint (Graphics&) override;
    void resized() override;
    void buttonClicked(Button* button) override;



    Label ipLabel;
    Label portLabel;

    TextEditor ip;
    TextEditor port;

    TextButton connects;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConnectionState)
};
