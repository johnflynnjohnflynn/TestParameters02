/*
  ==============================================================================

    State.cpp
    Created: 11 Jul 2016 8:24:45pm
    Author:  John Flynn

  ==============================================================================
*/

#include "State.h"

namespace state
{

//==============================================================================
XmlElement& saveStateToXml (const AudioProcessor& proc, XmlElement& xml)
{
    xml.removeAllAttributes(); // clear first

    for (const auto& param : proc.getParameters())
        if (auto* p = dynamic_cast<AudioProcessorParameterWithID*> (param))
            xml.setAttribute (p->paramID, p->getValue()); // 0to1

    return xml;
}

AudioProcessor& loadStateFromXml (const XmlElement& xml, AudioProcessor& proc)
{
    for (const auto& param : proc.getParameters())
        if (auto* p = dynamic_cast<AudioProcessorParameterWithID*> (param))
                                                                                  // if not in xml set current
            p->setValueNotifyingHost ((float) xml.getDoubleAttribute (p->paramID, p->getValue()));

    return proc;
}

} // namespace state