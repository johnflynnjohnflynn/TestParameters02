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

    beginTest ("StateAB: Store current plugin settings as a state");
    expectDoesNotThrow (state::saveStateToXml(proc, xml));

    beginTest ("StateAB: Check parameter was stored");
    expect (xml.getDoubleAttribute ("gainID") == 0.5);
    beginTest ("StateAB: Check first parameter was stored");
    expect (test::equalApprox (xml.getDoubleAttribute ("gainStepID"), 0.152542));
    beginTest ("StateAB: Check last parameter was stored");
    expect (xml.getDoubleAttribute ("q2ID") == 0.5);

    xml.setAttribute("gainStepID", 0.11f);   // 0. change parameters in xml
    xml.setAttribute("gainID", 0.75f);       // 2.
    xml.setAttribute("q2ID", 0.93f);         // 7.

    beginTest ("StateAB: Load state from changed xml");
    expectDoesNotThrow (state::loadStateFromXml(xml, proc));

    beginTest ("StateAB: Check first parameter was loaded");
    expect (proc.getParameters()[0]->getValue() == 0.11f);
    beginTest ("StateAB: Check a parameter was loaded");
    expect (proc.getParameters()[2]->getValue() == 0.75f);
    beginTest ("StateAB: Check last parameter was loaded");
    expect (proc.getParameters()[7]->getValue() == 0.93f);

    beginTest ("StateAB: Toggle AB state");
    expectDoesNotThrow(proc.stateAB.toggleAB());
    beginTest ("StateAB: Check parameter is same");
    expect (proc.getParameters()[0]->getValue() == 0.11f);

    beginTest ("StateAB: Change parameter");
    expectDoesNotThrow(proc.getParameters()[0]->setValueNotifyingHost(0.2));
    beginTest ("StateAB: Toggle AB state and check");
    expectDoesNotThrow(proc.stateAB.toggleAB());
    expect (proc.getParameters()[0]->getValue() == 0.11f);
    beginTest ("StateAB: Toggle AB state and check");
    expectDoesNotThrow(proc.stateAB.toggleAB());
    expect (proc.getParameters()[0]->getValue() == 0.2f);
}

#endif // JF_UNIT_TESTS