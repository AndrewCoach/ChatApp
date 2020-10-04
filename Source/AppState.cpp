/*
  ==============================================================================

    AppState.cpp
    Created: 14 Aug 2020 11:42:40am
    Author:  Ondrej

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AppState.h"
#include "MainComponent.h"


static int staticInt = 0;

AppState::AppState(MainComponent* pMainT) : pMain(pMainT)
{
 
}
//==============================================================================


AppState::~AppState()
{

}


//void AppState::buttonClicked(Button* pButton) {
//    if (pButton == &tButton)
//    {
//       pMain->changeState(new ListeningState(pMain, String(staticInt+=5)));
//    }
//}

//void AppState::getMainPtr(MainComponent* pMainT)
//{
//    pMain = pMainT;
//}

//void AppState::paint (Graphics& g)
//{
//    /* This demo code just fills the component's background and
//       draws some placeholder text to get you started.
//
//       You should replace everything in this method with your own
//       drawing code..
//    */
//
//    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
//
//    //g.setColour (Colours::grey);
//    //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
//
//    //g.setColour (Colours::white);
//    //g.setFont (14.0f);
//    //g.drawText ("AppState SAYS HELLO!", getLocalBounds(),
//    //            Justification::centred, true);   // draw some placeholder text
//}

//void AppState::resized()
//{
//    // This method is where you should set the bounds of any child
//    // components that your component contains..
//    
//}
