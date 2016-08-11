/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
void populateComboBox (ComboBox& comboBox, const std::vector<String> listItems)
{
    const int listItems_size {static_cast<int> (listItems.size())};
    for (int i = 0; i < listItems_size; ++i)
        comboBox.addItem (listItems[i], i + 1); // 1-indexed ID for ComboBox
}

//==============================================================================
TestParameters02AudioProcessorEditor::TestParameters02AudioProcessorEditor (TestParameters02AudioProcessor& p)
    : AudioProcessorEditor (&p),
      toggleABButton {"A-B"},
      copyABButton {"Copy"},
      savePresetButton {"Save preset"},
      deletePresetButton {"Delete preset"},
      gainStepSizeSlider {*p.getParameters()[0]},                           // better way than indices?
      freqStepSizeSlider {*p.getParameters()[1]},
      gainSlider         {*p.getParameters()[2]},
      freqSlider         {*p.getParameters()[3]}, //freqStepSizeSlider.slider_},
      qSlider            {*p.getParameters()[4]},
      gain2Slider        {*p.getParameters()[5]},
      freq2Slider        {*p.getParameters()[6]},
      q2Slider           {*p.getParameters()[7]},
      processor (p)
{
    addAndMakeVisible (toggleABButton);
    addAndMakeVisible (copyABButton);
    toggleABButton.addListener (this);
    copyABButton.addListener (this);

    addAndMakeVisible (presetBox);
    presetBox.setTextWhenNothingSelected("Load preset...");
    updatePresetBox();
    presetBox.addListener (this);

    addAndMakeVisible (savePresetButton);
    savePresetButton.addListener (this);
    addAndMakeVisible (deletePresetButton);
    deletePresetButton.addListener (this);
    
    addAndMakeVisible (&gainStepSizeSlider);
    addAndMakeVisible (&freqStepSizeSlider);
    addAndMakeVisible (&gainSlider);
    addAndMakeVisible (&freqSlider);
    addAndMakeVisible (&qSlider);
    addAndMakeVisible (&gain2Slider);
    addAndMakeVisible (&freq2Slider);
    addAndMakeVisible (&q2Slider);

    setSize (400, 700); // remember to set before xtor finished
}

TestParameters02AudioProcessorEditor::~TestParameters02AudioProcessorEditor()
{
}

//==============================================================================
void TestParameters02AudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::lightgrey);
}

void TestParameters02AudioProcessorEditor::resized()
{
    Rectangle<int> r (getLocalBounds().reduced (10));

    const int sliderHeight {50};

    toggleABButton    .setBounds (r.removeFromTop (sliderHeight));
    copyABButton      .setBounds (r.removeFromTop (sliderHeight));
    presetBox         .setBounds (r.removeFromTop (sliderHeight));
    savePresetButton  .setBounds (r.removeFromTop (sliderHeight));
    deletePresetButton.setBounds (r.removeFromTop (sliderHeight));
    gainStepSizeSlider.setBounds (r.removeFromTop (sliderHeight));
    freqStepSizeSlider.setBounds (r.removeFromTop (sliderHeight));
    gainSlider        .setBounds (r.removeFromTop (sliderHeight));
    freqSlider        .setBounds (r.removeFromTop (sliderHeight));
    qSlider           .setBounds (r.removeFromTop (sliderHeight));
    gain2Slider       .setBounds (r.removeFromTop (sliderHeight));
    freq2Slider       .setBounds (r.removeFromTop (sliderHeight));
    q2Slider          .setBounds (r.removeFromTop (sliderHeight));
}

void TestParameters02AudioProcessorEditor::buttonClicked (Button* clickedButton)
{
    if (clickedButton == &toggleABButton)   processor.stateAB.toggleAB();
    if (clickedButton == &copyABButton)     processor.stateAB.copyAB();
    if (clickedButton == &savePresetButton) savePresetAlertWindow();
}

void TestParameters02AudioProcessorEditor::comboBoxChanged (ComboBox* changedComboBox)
{
    int selectedId {changedComboBox->getSelectedId()};
    processor.statePresets.loadPreset (selectedId);
}

void TestParameters02AudioProcessorEditor::updatePresetBox()
{
    presetBox.clear();
    const std::vector<String>& presetNames {processor.statePresets.getPresetNames()};

    populateComboBox (presetBox, presetNames);
}

void TestParameters02AudioProcessorEditor::savePresetAlertWindow()
{
    enum choice { ok, cancel };

    AlertWindow alert {"Save preset...", "", AlertWindow::AlertIconType::NoIcon};
    alert.addTextEditor ("presetEditorID", "Enter preset name");
    alert.addButton ("OK",     choice::ok,     KeyPress (KeyPress::returnKey, 0, 0));
    alert.addButton ("Cancel", choice::cancel, KeyPress (KeyPress::escapeKey, 0, 0));
    
    if (alert.runModalLoop() == choice::ok) // runModalLoop to show alert, check okay   // LEAKS when quit while open !!!
    {
        String presetName {alert.getTextEditorContents ("presetEditorID")};
        processor.statePresets.savePreset (presetName);

        updatePresetBox();

        //int lastID {updatePresetBox()};
        //presetBox.setSelectedId(lastID);
    }
}
