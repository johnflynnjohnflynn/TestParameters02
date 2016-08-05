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
class StateAB
{
public:
    StateAB (AudioProcessor& p);
    
    void toggleAB();
    void copyAB();

private:
    AudioProcessor& pluginProcessor;
    XmlElement ab {"AB"};

};

//==============================================================================
class StatePresets
{
public:
    StatePresets (AudioProcessor& p);
    ~StatePresets();
    
    void savePreset (String presetName);

private:
    AudioProcessor& pluginProcessor;
    XmlElement presetXml {"PRESETS"};
    File presetFile {File::getSpecialLocation (File::userApplicationDataDirectory)
                    .getChildFile ("JohnFlynn/TestParameters02/presets.xml")};
};

//==============================================================================
JF_DECLARE_UNIT_TEST_WITH_STATIC_INSTANCE (StateTests)

//==============================================================================
} // namespace state

#endif  // STATE_H_INCLUDED
