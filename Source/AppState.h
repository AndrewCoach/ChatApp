/*
  ==============================================================================

    AppState.h
    Created: 14 Aug 2020 11:42:40am
    Author:  Ondrej

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class MainComponent;    // Fixed my circular dependency issues (Predeclaring a class)


class AppState    : public Component
{
public:
    AppState(MainComponent* pMainT);

   virtual ~AppState();

    //void paint (Graphics&) override;
    //void resized() override;
    //void buttonClicked(Button*) override;


   virtual void returns()=0;
    

public:
    TextEditor textBox;
    MainComponent* pMain;
    Label intro;
    String text;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AppState)
};
