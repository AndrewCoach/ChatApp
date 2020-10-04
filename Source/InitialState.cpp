/*
  ==============================================================================

    InitialState.cpp
    Created: 21 Aug 2020 11:20:44am
    Author:  Ondrej

  ==============================================================================
*/

#include <JuceHeader.h>
#include "InitialState.h"
#include "MainComponent.h"
//==============================================================================
InitialState::InitialState(MainComponent* pMainT) : AppState(pMainT)
{
    

    addAndMakeVisible(intro);
    addAndMakeVisible(listenerInfo);
    addAndMakeVisible(listenerPort);
    addAndMakeVisible(listenerButton);
    addAndMakeVisible(connectButton);
    addAndMakeVisible(listenerLabel);
    addAndMakeVisible(name);
    addAndMakeVisible(nameEditor);
    addAndMakeVisible(nameButton);
    


    
    listenerButton.addListener(this);
    connectButton.addListener(this);
    nameButton.addListener(this);

    intro.setText("A basic messaging client! \n Developed by Andrew.", juce::NotificationType::dontSendNotification);
    intro.setJustificationType(Justification::centred);
    listenerInfo.setText("If you wish to start a listening server, please choose a valid port and click 'Open Listener'.  \n If you wish to connect to an open client yourself, click the 'Connect' button to go to the connection screen.", juce::NotificationType::dontSendNotification);
    listenerInfo.setJustificationType(Justification::centred);

    name.setJustificationType(Justification::centredRight);
    name.setText("Choose a nickname: ", juce::NotificationType::dontSendNotification);
    
    Random random;
    random.setSeedRandomly();
    //FIRST SETTING OF THE STRING NAME 
    int rand = random.nextInt() % 100;
    rand = rand < 0 ? rand * -1 : rand;
    nameEditor.setText("Client " + String(rand));
    pMain->nameString = nameEditor.getText();

    nameButton.setButtonText("Select Name");

    //listenerPort.setText("Change your bind PORT");
    listenerLabel.setText("Bound PORT for incoming connections: ", juce::NotificationType::dontSendNotification);
    listenerLabel.setJustificationType(Justification::centredRight);

    listenerButton.setButtonText("Open Listener");
    connectButton.setButtonText("Connect to a defined client");


}

InitialState::~InitialState()
{

}



void InitialState::returns()
{
    pMain->setSize(700, 400);
    resized();

}


void InitialState::buttonClicked(Button* button)
{

        
    if (button == &listenerButton)
    {
        if (!listenerPort.isEmpty() && listenerPort.getText().containsOnly("0123456789") && !pMain->pServer->beginWaitingForSocket(listenerPort.getText().getIntValue()))
        {
            //if the listener does not open, we set the label to reflect this;
            AlertWindow::showMessageBox(AlertWindow::AlertIconType::WarningIcon, "Listener failure",
                "An attempt to open a listener on PORT: " + listenerPort.getText()
                + "failed. Please check that your input PORT has correct format eg. 50000 or choose a different Bound PORT...");
        }
        else if (listenerPort.isEmpty())
        {
            AlertWindow::showMessageBox(AlertWindow::AlertIconType::WarningIcon, "Listener failure",
                "PORT field cannot be empty!");
        } else
        {    //if listener open, we fill the texteditor for port to reflect the right port  
            listenerPort.setText(String(pMain->pServer->getBoundPort()));
            AlertWindow::showMessageBox(AlertWindow::AlertIconType::InfoIcon, "Listener Success",
                "Successfully opened a listener on PORT: " + listenerPort.getText());
        }
    }
    else if (button == &connectButton)
    {
        //TRANSITION  TO CONNECTION STATE
        this->pMain->changeState(new ConnectionState(pMain));
        
        pMain->resized();
    }
    else if (button == &nameButton)
    {
        if (nameEditor.isEmpty() || nameEditor.getText().length() > 50)
        {
            AlertWindow::showMessageBox(AlertWindow::AlertIconType::WarningIcon, "Namechange failure",
                "Names cannot be longer than 50 characters! Name field also cannot be left empty!");
        }
        else
        {
            pMain->nameString = nameEditor.getText();
            AlertWindow::showMessageBox(AlertWindow::AlertIconType::InfoIcon, "Name Saved!",
                "Successfully changed your name to: " + nameEditor.getText());
        }
    }

    

}

void InitialState::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void InitialState::resized()
{
    auto curBounds = getLocalBounds();

    curBounds.removeFromTop(getLocalBounds().getHeight() / 6.7F);

    intro.setBounds(curBounds.removeFromTop(80));

    curBounds.removeFromTop(40);

    auto lisBounds = curBounds.removeFromTop(40);
    listenerInfo.setBounds(lisBounds.reduced(40,0));

    curBounds.removeFromTop(20);
    //
    auto lis2Bounds = curBounds.removeFromTop(40);
    name.setBounds(lis2Bounds.removeFromLeft(getLocalBounds().getWidth() / 2));
    nameEditor.setBounds(lis2Bounds.removeFromLeft((getLocalBounds().getWidth() / 7)).reduced(2, 7));

    lis2Bounds.removeFromLeft(5);

    nameButton.setBounds(lis2Bounds.removeFromLeft(getLocalBounds().getWidth() / 5));

    curBounds.removeFromTop(5);
    //
    auto lis3Bounds = curBounds.removeFromTop(40);
    listenerLabel.setBounds(lis3Bounds.removeFromLeft(getLocalBounds().getWidth() / 2));
    listenerPort.setBounds(lis3Bounds.removeFromLeft((getLocalBounds().getWidth() / 10)).reduced(2,7));

    lis3Bounds.removeFromLeft(5);

    listenerButton.setBounds(lis3Bounds.removeFromLeft(getLocalBounds().getWidth() / 5));

    curBounds.removeFromTop(20);

    connectButton.setBounds(curBounds.removeFromTop(40).reduced( getLocalBounds().getWidth() / 3 , 0));

    // This method is where you should set the bounds of any child
    // components that your component contains..

}
