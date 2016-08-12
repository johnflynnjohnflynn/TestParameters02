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
StateAB::StateAB (AudioProcessor& p)
    : pluginProcessor {p}
{
    copyAB();
}

void StateAB::toggleAB()
{
    XmlElement temp {"Temp"};
    saveStateToXml (pluginProcessor, temp); // current to temp
    loadStateFromXml (ab, pluginProcessor); // ab to current
    ab = temp;                              // temp to ab
}

void StateAB::copyAB()
{
    saveStateToXml (pluginProcessor, ab);
}

//==============================================================================
void createFileIfNonExistant (const File& file)
{
    if (! file.exists())
        file.create();
    jassert (file.exists());
}

void parseFileToXmlElement (const File& file, XmlElement& xml)                  // what could go wrong here?
{
    std::unique_ptr<XmlElement> parsed {XmlDocument::parse (file)};
    if (parsed)
        xml = *parsed;
}

void writeXmlElementToFile (const XmlElement& xml, File& file)
{
    createFileIfNonExistant (file);
    xml.writeToFile (file, "");         // "" is DTD (unused)
}

String getNextAvailablePresetID (const XmlElement& presetXml)
{
    int newPresetIDNumber = presetXml.getNumChildElements() + 1; // 1 indexed to match ComboBox
    return "preset" + static_cast<String> (newPresetIDNumber);   // format: preset##
}

//==============================================================================
StatePresets::StatePresets (AudioProcessor& proc, const String& presetFileLocation)
    : pluginProcessor {proc},
      presetFile {File::getSpecialLocation (File::userApplicationDataDirectory)
                    .getChildFile (presetFileLocation)}
{
    parseFileToXmlElement (presetFile, presetXml);
}

StatePresets::~StatePresets()
{
    writeXmlElementToFile (presetXml, presetFile);
}

void StatePresets::savePreset (const String& presetName)
{
    String newPresetID = getNextAvailablePresetID (presetXml); // presetID format: "preset##"

    std::unique_ptr<XmlElement> currentState {new XmlElement {newPresetID}};    // must be pointer as
    saveStateToXml (pluginProcessor, *currentState);                            // parent takes ownership
    currentState->setAttribute ("presetName", presetName);
    
    presetXml.addChildElement (currentState.release());                         // will be deleted by parent element
}

void StatePresets::loadPreset (int presetID)
{
    if (1 <= presetID && presetID <= presetXml.getNumChildElements()) // 1 indexed to match ComboBox
    {
        XmlElement loadThisChild {*presetXml.getChildElement (presetID - 1)}; // (0 indexed method)
        loadStateFromXml (loadThisChild, pluginProcessor);
    }
    currentPresetID = presetID; // allow 0 for 'no preset selected' (?)
}

void StatePresets::deletePreset()
{
    XmlElement* childToDelete {presetXml.getChildElement (currentPresetID - 1)};
    if (childToDelete)
        presetXml.removeChildElement (childToDelete, true);
}

StringArray StatePresets::getPresetNames() const
{
    StringArray names;

    forEachXmlChildElement(presetXml, child)                                    // should avoid macro?
    {
        String n = child->getStringAttribute("presetName");
        if (n == "")
            n = "(Unnamed preset)";
        names.add (n);
    }
    return names; // hopefully moves
}

int StatePresets::getNumPresets() const
{
    return presetXml.getNumChildElements();
}

int StatePresets::getCurrentPresetId() const
{
    return currentPresetID;
}

} // namespace state