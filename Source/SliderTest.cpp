/*
  ==============================================================================

    SliderTest.cpp
    Created: 8 Jul 2016 9:13:40pm
    Author:  John Flynn

  ==============================================================================
*/

#include "Slider.h"

namespace jf
{

//==============================================================================
#if JF_UNIT_TESTS

SliderTests::SliderTests()
    : UnitTest ("jf::SliderStep")
{
}

//==============================================================================
class SliderTestsProc  : public AudioProcessor
{
public:
    SliderTestsProc()
        : cont {new ParamStep {"id", "name", 0, 10, 5,  0}},
          step {new ParamStep {"id", "name", 0, 10, 5, 10}},
          stepSizeParam {new ParamStepBroadcast  {"sid", "sname", 0.01,  3, 0.75, 0, 0}},
          gainParam     {new ParamStepListenGain {"gid", "gname",  -10, 10, 1,   20, 0, *stepSizeParam}},
          numFreqStepsParam {new jf::ParamStepBroadcast  {"sid", "sname",    1,    16,    4, 15, 0}},
          freqParam         {new jf::ParamStepListenFreq {"gid", "gname",   20, 20000,  200,  0, 3, *numFreqStepsParam}}
    {
        addParameter (cont);
        addParameter (step);
        addParameter (stepSizeParam);
        addParameter (gainParam);
        addParameter (numFreqStepsParam);
        addParameter (freqParam);
    }

    ~SliderTestsProc() {}

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
    jf::ParamStep* cont {nullptr};                              // 0
    jf::ParamStep* step {nullptr};                              // 1
    jf::ParamStepBroadcast* stepSizeParam {nullptr};            // 2
    jf::ParamStepListenGain* gainParam {nullptr};               // 3
    jf::ParamStepBroadcast* numFreqStepsParam {nullptr};        // 4
    jf::ParamStepListenFreq* freqParam {nullptr};               // 5

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderTestsProc)
};

//==============================================================================
bool doubleEqualApprox (double a, double b)
{
    return std::abs(b - a) < 0.01;
}

void SliderTests::runTest()
{
    Random rnd = getRandom();

    SliderTestsProc proc;

    beginTest ("Create continuous slider 0 to 10, def 5");
    expectDoesNotThrow (SliderStep {*proc.getParameters()[0]});
    SliderStep sCont {*proc.getParameters()[0]};
    expect (sCont.getValue() == 0.5);

    beginTest ("Move to non-stepped and expect same value.");
    expectDoesNotThrow (sCont.setValue (0.23894723894));
    expect (sCont.getValue() == 0.23894723894);

    beginTest ("Test end points");
    expectDoesNotThrow (sCont.setValue (1.0));
    expect (sCont.getValue() == 1.0);
    expectDoesNotThrow (sCont.setValue (0.0));
    expect (sCont.getValue() == 0.0);

    beginTest ("Create stepped slider 0 to 10, def 5, 10 steps");
    expectDoesNotThrow (SliderStep {*proc.getParameters()[1]});
    SliderStep sStep {*proc.getParameters()[1]};
    expect (sStep.getValue() == 0.5);

    beginTest ("Move to non-stepped and expect snapped-to-step value");
    expectDoesNotThrow (sStep.setValue (0.23894723894));
    expect (sStep.getValue() == 0.2); // 10 steps

    beginTest ("Test end points stepped");
    expectDoesNotThrow (sStep.setValue (0.99));
    expect (sStep.getValue() == 1.0);
    expectDoesNotThrow (sStep.setValue (0.01));
    expect (sStep.getValue() == 0.0);

    beginTest ("Create stepSize slider");
    expectDoesNotThrow (SliderStep {*proc.getParameters()[2]});
    SliderStep stepSizeSlider {*proc.getParameters()[2]};

    beginTest ("Create gain slider");
    expectDoesNotThrow (SliderStep {*proc.getParameters()[3]});
    SliderStep gainSlider {*proc.getParameters()[3]};

    beginTest ("Move stepSize slider");
    expect (doubleEqualApprox (stepSizeSlider.getValue(), 0.247492));
    stepSizeSlider.setValue(1.0);
    expect (stepSizeSlider.getValue() == 1.0);

    //beginTest ("Check moved stepSize has updated gainSlider text");
    // Unfortunately no 'getCurrentText()' method only getTextFromValue (float)
    // added 'updateText()' method to timer callback to keep textbox updated

    beginTest ("Create numFreqSteps slider");
    expectDoesNotThrow (SliderStep {*proc.getParameters()[4]});
    SliderStep numFreqStepsSlider {*proc.getParameters()[4]};

    beginTest ("Create freq slider");
    expectDoesNotThrow (SliderStep {*proc.getParameters()[5]});
    SliderStep freqSlider {*proc.getParameters()[5]};

    beginTest ("Move numFreqSteps slider");
    expect (doubleEqualApprox (numFreqStepsSlider.getValue(), 0.2f));
    numFreqStepsSlider.setValue(1.0);
    expect (numFreqStepsSlider.getValue() == 1.0);

    beginTest ("Check numSteps of listening freq slider has updated");
    expect (doubleEqualApprox (numFreqStepsSlider.getInterval(), (1.0f / 15.0f)));
}

#endif // JF_UNIT_TESTS

//==============================================================================
} // namespace jf
