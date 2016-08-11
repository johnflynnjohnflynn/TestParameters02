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
                                                // Backup actual presets file.
                                                // Work off presets-unit-test.xml for the tests.
    File presetsUnitTest {File::getSpecialLocation (File::userApplicationDataDirectory)
                         .getChildFile ("JohnFlynn/TestParameters02/presets-unit-test.xml")};
    File presets         {File::getSpecialLocation (File::userApplicationDataDirectory)
                         .getChildFile ("JohnFlynn/TestParameters02/presets.xml")};
    File presetsBackup   {File::getSpecialLocation (File::userApplicationDataDirectory)
                         .getChildFile ("JohnFlynn/TestParameters02/presets-backup.xml")};
    presets.copyFileTo (presetsBackup);
    presetsUnitTest.copyFileTo (presets);

    {                                           // Keep proc in its own scope so the destructor
        TestParameters02AudioProcessor proc;    // writes to the preset file before we reinstate
                                                // the preset backup.
        // StateAB
        
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

        beginTest("Load preset 1");
        expectDoesNotThrow (proc.statePresets.loadPreset(2));
        expect (proc.getParameters()[0]->getValue() == 0.67068374156951904297);

        beginTest("Load preset 2");
        expectDoesNotThrow (proc.statePresets.loadPreset(3));
        expect (proc.getParameters()[0]->getValue() == 0.75203621387481689453);

        beginTest("Load preset 3");
        expectDoesNotThrow (proc.statePresets.loadPreset(4));
        expect (proc.getParameters()[0]->getValue() == 0.79138964414596557617);

        beginTest("Load preset 0");
        expectDoesNotThrow (proc.statePresets.loadPreset(1));
        expect (proc.getParameters()[0]->getValue() == 0.37275597453117370605);

        beginTest("Load preset out of range");
        expectThrows (proc.statePresets.loadPreset(999));

        beginTest("getNumPresets()");
        expect (proc.statePresets.getNumPresets() == 4);

        beginTest("deletePreset()");
        expectDoesNotThrow (proc.statePresets.deletePreset());
        expect (proc.statePresets.getNumPresets() == 3);
    }                                                       // proc destructor called

    presetsBackup.copyFileTo (presets);                     // now copy presets file back in place
}

#endif // JF_UNIT_TESTS