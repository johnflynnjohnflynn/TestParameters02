/*
  ==============================================================================

    PluginProcessorTest.cpp
    Created: 11 Jul 2016 9:10:18pm
    Author:  John Flynn

  ==============================================================================
*/

#include "PluginProcessor.h"

//==============================================================================
#if JF_UNIT_TESTS

PluginProcessorTests::PluginProcessorTests()
    : UnitTest ("Processor")
{
}

void PluginProcessorTests::runTest()
{
    Random rnd = getRandom();

    // StateAB

    TestParameters02AudioProcessor proc;
    XmlElement xml {"TestXml"};

    beginTest ("State: Store current plugin settings as a state");
    expectDoesNotThrow (state::saveStateToXml(proc, xml));

    beginTest ("State: Check parameter was stored");
    expect (xml.getDoubleAttribute ("gainID") == 0.5);
    beginTest ("State: Check first parameter was stored");
    expect (test::equalApprox (xml.getDoubleAttribute ("gainStepID"), 0.152542));
    beginTest ("State: Check last parameter was stored");
    expect (xml.getDoubleAttribute ("q2ID") == 0.5);

    xml.setAttribute("gainStepID", 0.11f);   // 0. change parameters in xml
    xml.setAttribute("gainID", 0.75f);       // 2.
    xml.setAttribute("q2ID", 0.93f);         // 7.

    beginTest ("State: Load state from changed xml");
    expectDoesNotThrow (state::loadStateFromXml(xml, proc));

    beginTest ("State: Check first parameter was loaded");
    expect (proc.getParameters()[0]->getValue() == 0.11f);
    beginTest ("State: Check a parameter was loaded");
    expect (proc.getParameters()[2]->getValue() == 0.75f);
    beginTest ("State: Check last parameter was loaded");
    expect (proc.getParameters()[7]->getValue() == 0.93f);

    beginTest ("State: Toggle AB state");
    expectDoesNotThrow(proc.stateAB.toggleAB());
    beginTest ("State: Check parameter is same");
    expect (proc.getParameters()[0]->getValue() == 0.11f);

    beginTest ("State: Change parameter");
    expectDoesNotThrow(proc.getParameters()[0]->setValueNotifyingHost(0.2));
    beginTest ("State: Toggle AB state and check");
    expectDoesNotThrow(proc.stateAB.toggleAB());
    expect (proc.getParameters()[0]->getValue() == 0.11f);
    beginTest ("State: Toggle AB state and check");
    expectDoesNotThrow(proc.stateAB.toggleAB());
    expect (proc.getParameters()[0]->getValue() == 0.2f);
}

#endif // JF_UNIT_TESTS