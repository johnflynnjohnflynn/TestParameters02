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
void saveStateToXml (const AudioProcessor& proc, XmlElement& xml)
{
    xml.removeAllAttributes(); // clear first

    for (const auto& param : proc.getParameters())
        if (auto* p = dynamic_cast<AudioProcessorParameterWithID*> (param))
            xml.setAttribute (p->paramID, p->getValue()); // 0to1
}

void loadStateFromXml (const XmlElement& xml, AudioProcessor& proc)
{
    for (const auto& param : proc.getParameters())
        if (auto* p = dynamic_cast<AudioProcessorParameterWithID*> (param))
                                                                                  // if not in xml set current
            p->setValueNotifyingHost ((float) xml.getDoubleAttribute (p->paramID, p->getValue()));
}
//==============================================================================
/** Checks string doesn't start with number or underscore then 
    removes any character that isn't alphanumeric or an underscore.
    Returns an "_" instead of an empty string.
*/
String makeValidXmlName (const String& in)
{
    String out = in.trimCharactersAtStart ("1234567890_");
    out = out.retainCharacters("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789_");
    if (out == "")
        return "_";
    return out;
}

} // namespace state