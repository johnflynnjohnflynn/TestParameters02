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

    // StatePresets

    beginTest("Load preset 1");                                                 // these tests will quickly go out of sync
    expectDoesNotThrow (proc.statePresets.loadPreset(1));
    DBG(proc.getParameters()[0]->getValue());
    expect (proc.getParameters()[0]->getValue() == 0.18515901267528533936);

    beginTest("Load preset 2");
    expectDoesNotThrow (proc.statePresets.loadPreset(2));
    DBG(proc.getParameters()[0]->getValue());
    expect (proc.getParameters()[0]->getValue() == 0.37275597453117370605);

    beginTest("Load preset 3");
    expectDoesNotThrow (proc.statePresets.loadPreset(3));
    DBG(proc.getParameters()[0]->getValue());
    expect (proc.getParameters()[0]->getValue() == 0.67068374156951904297);

    beginTest("Load preset 0");
    expectDoesNotThrow (proc.statePresets.loadPreset(0));
    DBG(proc.getParameters()[0]->getValue());
    expect (proc.getParameters()[0]->getValue() == 0.0);

    beginTest("Load preset out of range");
    expectThrows (proc.statePresets.loadPreset(999));
}

#endif // JF_UNIT_TESTS