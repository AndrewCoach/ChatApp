/*
  ==============================================================================

    ConnectionState.cpp
    Created: 21 Aug 2020 12:34:45pm
    Author:  Ondrej

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ConnectionState.h"
#include "MainComponent.h"

//==============================================================================
ConnectionState::ConnectionState(MainComponent* pMainT) : AppState(pMainT)

{
    addAndMakeVisible(intro);
    addAndMakeVisible(ipLabel);
    addAndMakeVisible(portLabel);
    addAndMakeVisible(ip);
    addAndMakeVisible(port);
    addAndMakeVisible(connects);

    connects.addListener(this);


    intro.setText("A connection interface for connection to Clients.", juce::NotificationType::dontSendNotification);
    intro.setJustificationType(Justification::centred);
    ipLabel.setText("Client's IP address: ", juce::NotificationType::dontSendNotification);
    ipLabel.setJustificationType(Justification::centredRight);
    portLabel.setText("Client's port: ", juce::NotificationType::dontSendNotification);
    portLabel.setJustificationType(Justification::centredRight);
    connects.setButtonText("Connect");
}

ConnectionState::~ConnectionState()
{
}


void ConnectionState::returns()
{
    pMain->setSize(600, 300);
    resized();
}

void ConnectionState::buttonClicked(Button* button)
{
    if (button == &connects)
    {
        if (!ip.isEmpty() && !port.isEmpty() && ip.getText().containsOnly("0123456789.")
            && port.getText().containsOnly("0123456789"))
        {
            if (pMain->pSocket->connectToSocket(ip.getText(), port.getText().getIntValue(), 4000))
            {

                AlertWindow::showMessageBox(AlertWindow::AlertIconType::InfoIcon, "Successful connection!",
                    "Successfully connected to IP: " + ip.getText() + " and PORT: " + port.getText() + "!");
                //state transition - NEEDS TO BE CHANGED LATER TO CHATTING STATE!

                this->pMain->changeState(new ChattingState(pMain, 0)); //also pass information here if we are listener/ server
            }
            else 
            {
                AlertWindow::showMessageBox(AlertWindow::AlertIconType::WarningIcon, "Connection Failure",
                    "Please check, that the Client you are trying to connect to has an active socket that is listening at your specified PORT!");
            } 
        }
        else
        {
            AlertWindow::showMessageBox(AlertWindow::AlertIconType::WarningIcon, "Input violation!",
                "Please check, that your input values are correct : \nIP address example: 192.168.0.2 \n PORT example: 45000");
        }
    }
}

void ConnectionState::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void ConnectionState::resized()
{
    auto curBounds = getLocalBounds();

    curBounds.removeFromTop(getLocalBounds().getHeight() / 10.0F);

    intro.setBounds(curBounds.removeFromTop(30));

    curBounds.removeFromTop(40);

    auto lis2Bounds = curBounds.removeFromTop(40);
    ipLabel.setBounds(lis2Bounds.removeFromLeft(getLocalBounds().getWidth() / 2));
    ip.setBounds(lis2Bounds.removeFromLeft((getLocalBounds().getWidth() / 4)).reduced(2, 7));

    curBounds.removeFromTop(1);

    auto lisBounds = curBounds.removeFromTop(40);
    portLabel.setBounds(lisBounds.removeFromLeft(getLocalBounds().getWidth() / 2));
    port.setBounds(lisBounds.removeFromLeft((getLocalBounds().getWidth() / 10)).reduced(2, 7));

    curBounds.removeFromTop(30);

    connects.setBounds(curBounds.removeFromTop(40).reduced(getLocalBounds().getWidth() / 3, 0));


}
