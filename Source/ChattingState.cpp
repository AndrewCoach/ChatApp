/*
  ==============================================================================

    ChattingState.cpp
    Created: 21 Aug 2020 3:30:42pm
    Author:  Ondrej

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChattingState.h"
#include "MainComponent.h"

//==============================================================================
ChattingState::ChattingState(MainComponent* pMainT, bool server) : AppState(pMainT), isServer(server)
{
    addAndMakeVisible(intro);
    addAndMakeVisible(textBox);
    addAndMakeVisible(input);
    addAndMakeVisible(send);
    addAndMakeVisible(exit);
    
    send.addListener(this);
    exit.addListener(this);

    send.setButtonText("Send");
    exit.setButtonText("Exit");
    intro.setText(pMain->nameString + "\n\nIn this window you can exchange messages with each other, just type in the input box below and anything that has been sent will be displayed in the top box.", juce::NotificationType::dontSendNotification);
    intro.setJustificationType(Justification::centred);
    input.setTextToShowWhenEmpty("Type your message here!", juce::Colours::grey);

    textBox.setReadOnly(1);
    textBox.setText("");
    textBox.setPopupMenuEnabled(1);
    textBox.setMultiLine(1);
    textBox.setFont(juce::Font("Arial", "Bold", 14.0f));

    input.setReturnKeyStartsNewLine(1);
    input.setFont(juce::Font("Arial", "Bold", 12.0f));
    input.setPopupMenuEnabled(1);
    input.setMultiLine(1);
}

ChattingState::~ChattingState()
{

}

void ChattingState::returns()
{
    pMain->setSize(1000, 900);
    resized();
}

void ChattingState::buttonClicked(Button* button)
{
    if (button == &send && !input.isEmpty() && !input.getText().containsOnly("\n"))
    {
        MemoryBlock mb;
        String temp("\n" + pMain->nameString + ": ");
        temp = temp.toUTF8();
        text = text.toUTF8();
        temp.append(input.getText().toUTF8(), 5000);

        text.append(temp,5000);
        mb.append(text.getCharPointer(), CharPointer_UTF8::getBytesRequiredFor(text.getCharPointer()));


        // SENDING
        if (isServer)
        {
            pMain->pServer->theCreatedOne->sendMessage(mb);
            
        }
        else
        {
            pMain->pSocket->sendMessage(mb);
           
        }

        this->textBox.setText(text);
        input.setText("");
        this->textBox.moveCaretToEnd();
        this->textBox.scrollEditorToPositionCaret(0, 0);
        this->textBox.pageDown(0);
        this->resized();
    }
    else if (button == &exit)
    {
        AlertWindow::showMessageBox(AlertWindow::AlertIconType::InfoIcon, "Connection Terminated!",
            "Connection has been terminated.");
        this->pMain->changeState(new InitialState(this->pMain));
    }
    //cleaning the input
    input.setText("");
}

void ChattingState::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

}

void ChattingState::resized()
{
    juce::Rectangle<int> globalBounds = getLocalBounds();

    globalBounds.removeFromTop(50);
    intro.setBounds(globalBounds.removeFromTop(getLocalBounds().getWidth() / 15.0F).reduced(200,0));

    globalBounds.removeFromTop(40);

    textBox.setBounds(globalBounds.removeFromTop(getLocalBounds().getHeight() / 1.7f));
    globalBounds.removeFromLeft(getLocalBounds().getHeight() / 6);
    globalBounds.removeFromRight(getLocalBounds().getHeight() / 6);

    globalBounds.removeFromTop(10);

    auto newBounds = globalBounds.removeFromBottom(45);
    auto newnewBounds = newBounds.removeFromLeft(newBounds.getWidth() / 2);

    send.setBounds(newnewBounds.reduced(10, 0));
    exit.setBounds(newBounds.reduced(10, 0));

    input.setBounds(globalBounds.reduced(-50, 10));

}
