/*
  ==============================================================================

    StateTest.cpp
    Created: 28 Jul 2016 9:46:22pm
    Author:  John Flynn

  ==============================================================================
*/

#include "State.h"
#include "Parameter.h"

namespace state
{

//==============================================================================
#if JF_UNIT_TESTS

StateTests::StateTests()
    : UnitTest ("State")
{
}

void StateTests::runTest()
{
    beginTest("state::createFileIfNonExistant()");
    File file {File::getSpecialLocation (File::userApplicationDataDirectory)
               .getChildFile ("JohnFlynn/TestParameters02/unit-test-createFileIfNonExistant.xml")};
    expect (! file.exists());

    state::createFileIfNonExistant(file);
    expect (file.exists());

    state::createFileIfNonExistant(file);
    expect (file.exists());

    file.deleteFile();
    expect (! file.exists());

    beginTest("state::writeXmlElementToFile()");
    state::createFileIfNonExistant(file);

    XmlElement xml1 {"TEST"};
    xml1.setAttribute ("name", "Nigel");
    xml1.setAttribute ("age", "10");

    expectDoesNotThrow(state::writeXmlElementToFile(xml1, file));

    beginTest("state::parseFileToElement()");
    XmlElement xml2 {"CheckTEST"};
    expectDoesNotThrow(state::parseFileToXmlElement(file, xml2));

    expect (xml2.getStringAttribute("name") == "Nigel");
    expect (xml2.getStringAttribute("age") == "10");

    beginTest("state::getNextAvailablePresetID");
    expect (state::getNextAvailablePresetID(xml1) == "preset0");

    std::unique_ptr<XmlElement> child {new XmlElement {"CHILD"}};
    child->setAttribute ("name", "Terry");
    child->setAttribute ("age", "11");
    xml1.addChildElement(child.release());

    expect (state::getNextAvailablePresetID(xml1) == "preset1");

    file.deleteFile();
}

#endif // JF_UNIT_TESTS

//==============================================================================
} // namespace state
