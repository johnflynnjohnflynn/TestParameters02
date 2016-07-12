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
XmlElement& saveStateToXml (const AudioProcessor& processor, XmlElement& xml);
AudioProcessor& loadStateFromXml (const XmlElement& xml, AudioProcessor& processor);

//==============================================================================
/*class PluginState
{
public:
    PluginState (AudioProcessor& p)
        : pluginProcessor {p}
    {
    }

private:
    AudioProcessor& pluginProcessor;

};
*/
//==============================================================================
} // namespace state

#endif  // STATE_H_INCLUDED
