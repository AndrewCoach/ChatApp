/*
  ==============================================================================

    ListeningState.cpp
    Created: 14 Aug 2020 2:54:19pm
    Author:  Ondrej

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ListeningState.h"

//THIS IS A NEW TEST
#include "MainComponent.h" // will this compile?
//==============================================================================
ListeningState::ListeningState(MainComponent* pMainT, String buttonText) : AppState(pMainT) 
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(bConnect);
    addAndMakeVisible(bOpen);
    addAndMakeVisible(textBox);
    addAndMakeVisible(input);

    addAndMakeVisible(client1);
    addAndMakeVisible(client2);

    bConnect.addListener(this);
    bOpen.addListener(this);
    client1.addListener(this);
    client2.addListener(this);

    bConnect.setButtonText("Connect To a client");
    bOpen.setButtonText("Start listening for Connections");

    client1.setButtonText("S - send to Client 1:");
    client2.setButtonText("C - send to Client 2:");


    textBox.setReadOnly(1);
    textBox.setText("");
    textBox.setPopupMenuEnabled(1);
    textBox.setMultiLine(1);   
    textBox.setFont(juce::Font("Arial", "Bold", 14.0f));


    input.setReturnKeyStartsNewLine(1);
    input.setFont(juce::Font("Arial", "Bold", 12.0f));
    input.setText("Type Here");
    input.setPopupMenuEnabled(1);
    input.setMultiLine(1);
    
}

void ListeningState::returns()
{
    pMain->setSize(1000, 700);

}

ListeningState::~ListeningState()
{

}

void ListeningState::buttonClicked(Button* button)
{

    if (button == &client1)
    {
        //AlertWindow("heloo", "click something", AlertWindow::AlertIconType::WarningIcon);
        
        MemoryBlock mb;
        // mb.setSize(200);
         //mb.fillWith(0);

        String temp("Client 1: \n");
        
        temp.append(input.getText().toUTF8(),5000); //pokus

        //mb.append(L"Client 1: ", sizeof(L"Client 1: ") - 1);
        mb.append(temp.getCharPointer(), CharPointer_UTF8::getBytesRequiredFor(temp.getCharPointer()));


        //char text[] = "Hi you despicable human beings! this is a hi from client number one.\0";
        //mb.append(text, sizeof(text));
        pMain->pSocket->sendMessage(mb);
        this->resized();
    }
    else if (button == &client2)
    {
        if (pMain->pServer->theCreatedOne!=nullptr && pMain->pServer->theCreatedOne->isConnected())
        {
            MemoryBlock mb;
            //mb.append(L"Client 2: ", sizeof(L"Client 2: ") - 1);
            String temp("Client 2: \n");
            temp.toUTF8();
            temp.append(input.getText().toUTF8(), 5000);
            mb.append(temp.getCharPointer(), CharPointer_UTF8::getBytesRequiredFor(temp.getCharPointer()));

            pMain->pServer->theCreatedOne->sendMessage(mb);
            this->resized();
        }


    }


}

void ListeningState::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    //g.setColour (Colours::grey);
    //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    //g.setColour (Colours::white);
    //g.setFont (14.0f);
    //g.drawText ("ListeningState", getLocalBounds(),
    //            Justification::centred, true);   // draw some placeholder text
}

void ListeningState::resized()
{
    juce::Rectangle<int> globalBounds = getLocalBounds();


    textBox.setBounds(globalBounds.removeFromTop(getLocalBounds().getHeight() / 2));
    globalBounds.removeFromLeft(getLocalBounds().getHeight() / 3);
    globalBounds.removeFromRight(getLocalBounds().getHeight() / 3);

    globalBounds.removeFromTop(10);
    bOpen.setBounds(globalBounds.removeFromTop(45));

    globalBounds.removeFromTop(10);

    bConnect.setBounds(globalBounds.removeFromTop(45));

    auto newBounds = globalBounds.removeFromBottom(45);
    auto newnewBounds = newBounds.removeFromLeft(newBounds.getWidth() / 2);

    client1.setBounds(newnewBounds.reduced(10, 0));
    client2.setBounds(newBounds.reduced(10, 0));
    
    input.setBounds(globalBounds.reduced(-50,10));

    // this method is where you should set the bounds of any child
    // components that your component contains..

}
