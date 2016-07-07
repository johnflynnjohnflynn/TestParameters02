/*
  ==============================================================================

    Parameter.cpp
    Created: 5 Jul 2016 1:01:42pm
    Author:  John Flynn

  ==============================================================================
*/

#include "Parameter.h"

namespace jf
{

//==============================================================================
bool isGoodParamStep (float val, float min, float max, int steps)
{
    return (min < max)                      // invariants here
        && (min <= val) && (val <= max)
        && (0 <= steps);
}

void checkParamStep (float val, float min, float max, int steps)
{
   #if JF_UNIT_TESTS
    if (! isGoodParamStep (val, min, max, steps)) throw std::logic_error ("Invalid\n");
   #endif // JF_UNIT_TESTS

    jassert (isGoodParamStep (val, min, max, steps));
}

//==============================================================================
ParamStep::ParamStep (String pid, String nm, float minValue, float maxValue, float def, int steps, float ske)
   : AudioProcessorParameterWithID (pid, nm),
     value (def),
     range (minValue, maxValue, ske),
     defaultValue (def),
     numSteps (steps)
{
    checkParamStep (def, minValue, maxValue, steps);
}

void ParamStep::setNumSteps (int newNumSteps)
{
    checkParamStep (value, range.getStart(), range.getEnd(), newNumSteps);
    numSteps = newNumSteps;
}

void ParamStep::setRange(float start, float end, float skewLog)
{
    range.setStart (start);     // range does invariant checks
    range.setEnd (end);
    range.setSkewLog (skewLog);
}

// private:
float ParamStep::getValue() const                           { return range.convertTo0to1 (value); }
void ParamStep::setValue (float newValue)                   { value = range.convertFrom0to1 (newValue); }
float ParamStep::getDefaultValue() const                    { return range.convertTo0to1 (defaultValue); }
float ParamStep::getValueForText (const String& text) const { return range.convertTo0to1 (text.getFloatValue()); }

String ParamStep::getText (float v, int length) const
{
    String asText (range.convertFrom0to1 (v)); // see JUCE to constrain decimal places
    return length > 0 ? asText.substring (0, length) : asText;
}

//==============================================================================
ParamStepBroadcast::ParamStepBroadcast (String parameterID,  // no spaces
                                        String name,         // spaces allowed
                                        float minValue,
                                        float maxValue,
                                        float defaultValue,
                                        int numSteps,
                                        float skewLog)
    : ParamStep {parameterID, name, minValue, maxValue, defaultValue, numSteps, skewLog}
{
}

// private:
void ParamStepBroadcast::setValue (float newValue)
{
    jassert (0.0f <= newValue && newValue <= 1.0f);
    value = getRange().convertFrom0to1 (newValue);

   #if JF_UNIT_TESTS
    sendSynchronousChangeMessage(); // Unit test demands blocking synchronous call
   #endif

    sendChangeMessage(); // Async fine otherwise.
}

//==============================================================================
ParamStepListenGain::ParamStepListenGain (String parameterID,  // no spaces
                                          String name,         // spaces allowed
                                          float minValue,
                                          float maxValue,
                                          float defaultValue,
                                          int numSteps,
                                          float skewLog,
                                          ParamStepBroadcast& stepParam)
    : ParamStep {parameterID, name, minValue, maxValue, defaultValue, numSteps, skewLog},
      stepSizeParam {stepParam}
{
    stepSizeParam.addChangeListener (this);
}

// private:
void ParamStepListenGain::changeListenerCallback (ChangeBroadcaster* source)
{
    if (source == &stepSizeParam)
    {
            // calc temp values
        const float newStepSize = stepSizeParam.get();

        const int numSteps = getNumSteps();
        const float oldMin = getRange().getStart();
        const float oldMax = getRange().getEnd();
        const float centre = oldMin + (oldMax - oldMin) / 2.0f;
        
        const float newMin = centre - (numSteps * newStepSize) / 2.0f;
        const float newMax = centre + (numSteps * newStepSize) / 2.0f;

            // hold parameter position before, to avoid clamping
        const float val0to1 = getRange().convertTo0to1 (get());

            // set range for parameter (warning this can clamp the value!)
        setRange (newMin, newMax, getRange().getSkewLog());

            // set value for parameter (setValueNotifyingHost expects 0to1)
        setValueNotifyingHost (val0to1);
    }
}

//==============================================================================
#if JF_UNIT_TESTS

ParamStepTests::ParamStepTests()
    : UnitTest ("jf::ParamStep")
{
}

//==============================================================================
class ParamStepTestsProc  : public AudioProcessor
{
public:
    ParamStepTestsProc()
        : stepSizeParam {new ParamStepBroadcast  {"sid", "sname", 0.01,  3, 0.75, 0, 0}},
          gainParam     {new ParamStepListenGain {"gid", "gname",  -10, 10, 0,   20, 0, *stepSizeParam}}
    {
        addParameter (stepSizeParam);
        addParameter (gainParam);
    }

    ~ParamStepTestsProc() {}

    void prepareToPlay (double, int) override {}
    void releaseResources() override {}

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override {}
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override {}

    AudioProcessorEditor* createEditor() override { return nullptr; }
    bool hasEditor() const override { return true; }

    const String getName() const override { return ""; }

    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return true; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 0; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const String getProgramName (int) override { return ""; }
    void changeProgramName (int, const String&) override {}

    void getStateInformation (MemoryBlock&) override {}
    void setStateInformation (const void*, int) override {}

private:
    jf::ParamStepBroadcast* stepSizeParam {nullptr};
    jf::ParamStepListenGain* gainParam {nullptr};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParamStepTestsProc)
};

//==============================================================================
void ParamStepTests::runTest()
{
    Random rnd = getRandom();

    beginTest ("min < max");
    expectDoesNotThrow ((ParamStep {"dummyID", "The Name", 0, 10, 0, 0, 0}));
    expectThrows       ((ParamStep {"dummyID", "The Name", 0, -1, 0, 0, 0}));

    beginTest ("min <= default");
    expectThrows       ((ParamStep {"dummyID", "The Name", 0, 10, -5, 0, 0}));
    expectDoesNotThrow ((ParamStep {"dummyID", "The Name", 0, 10,  0, 0, 0}));

    beginTest ("default <= max");
    expectThrows       ((ParamStep {"dummyID", "The Name", 0, 10, 20, 0, 0}));
    expectDoesNotThrow ((ParamStep {"dummyID", "The Name", 0, 10, 10, 0, 0}));

    beginTest ("0 <= numSteps");
    expectThrows       ((ParamStep {"dummyID", "The Name", 0, 10,  0, -1, 0}));
    expectDoesNotThrow ((ParamStep {"dummyID", "The Name", 0, 10,  0, 0, 0}));

    beginTest ("set any skew");
    for (int i = 0; i < 1000; ++i)
        expectDoesNotThrow ((ParamStep {"dummyID", "The Name", 0, 10,  0, 0, rnd.nextFloat()}));

    ParamStep freq  {"id", "nm", 20, 20000, 632.456f,   0, 3};
    ParamStep steps {"id", "nm",  0,   127,        0, 128, 0};

    beginTest ("get() default");
    expect (freq.get() == 632.456f);

    beginTest ("getNumSteps()");
    expect (freq .getNumSteps() == 0);
    expect (steps.getNumSteps() == 128);

    beginTest ("setNumSteps()");
    expectDoesNotThrow (steps.setNumSteps(10));
    expect (steps.getNumSteps() == 10);
    expectThrows (steps.setNumSteps(-5));

    beginTest ("getRange()");
    jf::RangeLog range {20, 20000, 3};
    expect (freq.getRange() == range);

    beginTest ("setRange(f,f,f)");
    expectDoesNotThrow (freq.setRange (0, 1, 0));
    jf::RangeLog range010 {0, 1, 0};
    expect (freq.getRange() == range010);

    beginTest ("Create ParamStepBroadcast");
    expectDoesNotThrow ((ParamStepBroadcast {"id", "name", -10, 10, 0, 20, 0}));

    beginTest ("Create ParamStepBroadcast and ParamStepListenGain in dummy processor");
    expectDoesNotThrow (ParamStepTestsProc());
    ParamStepTestsProc paramStepTestsProc;

    beginTest ("Change stepSize parameter");
    expect (paramStepTestsProc.getParameters()[0]->getValue() != 1.0f);
    expectDoesNotThrow (paramStepTestsProc.getParameters()[0]->setValueNotifyingHost (1.0f)); // +3dB steps
    expect (paramStepTestsProc.getParameters()[0]->getValue() == 1.0f);

    beginTest ("Check listening gain parameter's range changed");
    RangeLog expectedRange {-30, 30, 0}; // now +3dB steps, so 10 steps times 3 is +/-30
    ParamStepListenGain& gainParam = dynamic_cast<ParamStepListenGain&> (*paramStepTestsProc.getParameters()[1]);
    expect (gainParam.getRange() == expectedRange);
}

#endif // JF_UNIT_TESTS

} // namespace jf