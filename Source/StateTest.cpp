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
    OwnedArray<AudioProcessorParameter> params;
    params.add (new parameter::ParamStepBroadcast  {"gainStepID", "Gain step size",  0.05f,     3.0f,   0.5f              });
    params.add (new parameter::ParamStepBroadcast  {"freqStepID", "Freq step size",      1,        7,      5,    6        });
    params.add (new parameter::ParamStep           {"qID",        "Q",                0.0707f,  7.07f,  0.707f, 18,   2.0f});
    params.add (new parameter::ParamStep           {"gain2ID",    "Gain2",          -12.0f,    12.0f,   0.0f,   22,   0.0f});

    beginTest ("StatePresets: constructor");
    expectDoesNotThrow (state::StatePresets ("JohnFlynn/TestParameters02/unit-tests-presets.xml"));

    state::StatePresets statePresets ("JohnFlynn/TestParameters02/unit-tests-presets.xml");

    statePresets.clearAllPresets();

    beginTest ("savePreset(One, params)");
    expectDoesNotThrow (statePresets.savePreset("One", params));
    beginTest ("savePreset(Two, params)");
    expectDoesNotThrow (statePresets.savePreset("Two", params));
    beginTest ("savePreset(BLANK, params)");
    expectDoesNotThrow (statePresets.savePreset("", params));
    beginTest ("savePreset(Four !@$@ $, params)");
    expectDoesNotThrow (statePresets.savePreset("Four !@$@ $", params));

    std::vector<String> presetNames {statePresets.getPresetNames()};
    beginTest ("getPresetNames()");
    expect (presetNames[0] == "One");
    expect (presetNames[1] == "Two");
    expect (presetNames[2] == "(Unnamed preset)");
    expect (presetNames[3] == "Four !@$@ $");
}

#endif // JF_UNIT_TESTS

//==============================================================================
} // namespace state
