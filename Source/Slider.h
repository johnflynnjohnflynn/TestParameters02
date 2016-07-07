/*
  ==============================================================================

    ParameterSlider.h
    Created: 5 Mar 2016 4:14:53pm

  ==============================================================================
*/

#ifndef PARAMETERSLIDER_H_INCLUDED
#define PARAMETERSLIDER_H_INCLUDED


namespace jf
{

// (Taken from the JUCE demo plugin PluginEditor.cpp)

//==============================================================================
// This is a handy slider subclass that controls an AudioProcessorParameter
// (may move this class into the library itself at some point in the future..)
class SliderStep  : public Slider,
                    private Timer
{
public:
    SliderStep (AudioProcessorParameter& p)
        : Slider (p.getName (256)), param (p)
    {
        if (0 < p.getNumSteps() && p.getNumSteps() <= 100) // <=100? defaults to 37850784 steps!
        {
            //jassert (param.getNumSteps() >= 2); // slider must have at least 2 positions!
            const double normStepSize = 1.0 / (p.getNumSteps()); // YES "/ p.getNumSteps()"
            setRange (0.0, 1.0, normStepSize); // stepped slider
        }
        else
            setRange (0.0, 1.0, 0.0); // continuous slider

        startTimerHz (30);
        updateSliderPos();
    }

    void valueChanged() override
    {
        param.setValueNotifyingHost ((float) Slider::getValue());
    }

    void timerCallback() override       { updateSliderPos(); }

    void startedDragging() override     { param.beginChangeGesture(); }
    void stoppedDragging() override     { param.endChangeGesture();   }

    double getValueFromText (const String& text) override   { return param.getValueForText (text); }
    String getTextFromValue (double value) override         { return param.getText ((float) value, 1024); }

    void updateSliderPos()
    {
        const float newValue = param.getValue();

        if (newValue != (float) Slider::getValue() && ! isMouseButtonDown())
            Slider::setValue (newValue);
    }

    AudioProcessorParameter& param;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderStep)
};


//==============================================================================
#if JF_UNIT_TESTS

class SliderTests  : public UnitTest
{
public:
    SliderTests()
        : UnitTest ("jf::SliderStep")
    {
    }

    class DummyProc  : public AudioProcessor
    {
    public:
        //==============================================================================
        DummyProc()
            : cont {new Parameter {"id", "name", 0, 10, 5,  0}},
              step {new Parameter {"id", "name", 0, 10, 5, 10}}
        {
            addParameter (cont);
            addParameter (step);
        }

        ~DummyProc() {}

        //==============================================================================
        void prepareToPlay (double sampleRate, int samplesPerBlock) override {}
        void releaseResources() override {}

       #ifndef JucePlugin_PreferredChannelConfigurations
        bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override {}
       #endif

        void processBlock (AudioSampleBuffer&, MidiBuffer&) override {}

        //==============================================================================
        AudioProcessorEditor* createEditor() override { return nullptr; }
        bool hasEditor() const override { return true; }

        //==============================================================================
        const String getName() const override { return ""; }

        bool acceptsMidi() const override { return true; }
        bool producesMidi() const override { return true; }
        double getTailLengthSeconds() const override { return 0.0; }

        //==============================================================================
        int getNumPrograms() override { return 0; }
        int getCurrentProgram() override { return 0; }
        void setCurrentProgram (int index) override {}
        const String getProgramName (int index) override { return ""; }
        void changeProgramName (int index, const String& newName) override {}

        //==============================================================================
        void getStateInformation (MemoryBlock& destData) override {}
        void setStateInformation (const void* data, int sizeInBytes) override {}

    private:
        //==============================================================================
        jf::Parameter* cont {nullptr};
        jf::Parameter* step {nullptr};

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DummyProc)
    };

    void runTest() override
    {
        Random rnd = getRandom();

        DummyProc proc;

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
    }
};

static SliderTests sliderTests;

#endif // JF_UNIT_TESTS

} // namespace jf


#endif  // PARAMETERSLIDER_H_INCLUDED
