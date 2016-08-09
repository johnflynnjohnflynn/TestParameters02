/*
  ==============================================================================

    State.h
    Created: 11 Jul 2016 8:24:45pm
    Author:  John Flynn

  ==============================================================================
*/

#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Test.h"

namespace state
{

//==============================================================================
void saveStateToXml (const AudioProcessor& processor, XmlElement& xml);
void loadStateFromXml (const XmlElement& xml, AudioProcessor& processor);

//==============================================================================
/** Handler for AB state toggling and copying in plugin.
    Create public instance in processor and call .toggleAB() and .copyAB()
    methods from button callback in editor.
*/
class StateAB
{
public:
    explicit StateAB (AudioProcessor& p);
    
    void toggleAB();
    void copyAB();

private:
    AudioProcessor& pluginProcessor;
    XmlElement ab {"AB"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StateAB);
};

//==============================================================================
/** Create StatePresets object with XML file saved relative to user
    data directory.
    e.g. StatePresets my_sps {"JohnFlynnPlugins/ThisPlugin/presets.xml"}
    Full path Mac  = ~/Library/JohnFlynnPlugins/ThisPlugin/presets.xml
*/
class StatePresets
{
public:
    explicit StatePresets (AudioProcessor& proc, const String& presetFileLocation);
    ~StatePresets();

    void clearAllPresets();
    void savePreset (const String& presetName); // preset already exists? confirm overwrite
                     
    std::vector<String> getPresetNames() const;

private:
    AudioProcessor& pluginProcessor;
    XmlElement presetXml {"PRESETS"}; // local, in-plugin representation
    File presetFile;                  // on-disk representation
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StatePresets);
};

//==============================================================================
JF_DECLARE_UNIT_TEST_WITH_STATIC_INSTANCE (StateTests)

//==============================================================================
} // namespace state

#endif  // STATE_H_INCLUDED
