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

String makeValidXmlName (const String& identifierToTest);

//==============================================================================
class StateAB
{
public:
    StateAB (AudioProcessor& p)
        : pluginProcessor {p}
    {
        copyAB();
    }
    
    void toggleAB()
    {
        XmlElement temp {"Temp"};
        saveStateToXml (pluginProcessor, temp); // current to temp
        loadStateFromXml (ab, pluginProcessor); // ab to current
        ab = temp;                              // temp to ab
    }
    
    void copyAB()
    {
        saveStateToXml (pluginProcessor, ab);
    }

private:
    AudioProcessor& pluginProcessor;
    XmlElement ab {"AB"};

};

//==============================================================================
class StatePresets
{
public:
    StatePresets (AudioProcessor& p)
        : pluginProcessor {p}
    {
    }
    
    void savePreset (String presetName)
    {
        // handle cases:
        // Illegal name?
        // Name already in use

        if (presetName != "")
        {
            XmlElement currentState {presetName};
            saveStateToXml (pluginProcessor, currentState);
            presets.addChildElement (&currentState);
        }
    }

private:
    AudioProcessor& pluginProcessor;
    XmlElement presets {"PRESETS"};

};

//==============================================================================
JF_DECLARE_UNIT_TEST_WITH_STATIC_INSTANCE (StateTests)

//==============================================================================
} // namespace state

#endif  // STATE_H_INCLUDED
