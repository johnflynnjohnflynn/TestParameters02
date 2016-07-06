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
bool isGoodParameter (float val, float min, float max, int steps)
{
    return (min < max)                      // invariants here
        && (min <= val) && (val <= max)
        && (0 <= steps);
}

void checkParameter (float val, float min, float max, int steps)
{
   #if JF_UNIT_TESTS
    if (! isGoodParameter (val, min, max, steps)) throw std::logic_error ("Invalid\n");
   #endif // JF_UNIT_TESTS

    jassert (isGoodParameter (val, min, max, steps));
}

//==============================================================================
Parameter::Parameter (String pid, String nm, float minValue, float maxValue, float def, int steps, float ske)
   : AudioProcessorParameterWithID (pid, nm),
     range (minValue, maxValue, ske),
     value (def),
     defaultValue (def),
     numSteps (steps)
{
    checkParameter (def, minValue, maxValue, steps);
}

void Parameter::setNumSteps (int newNumSteps)
{
    checkParameter (value, range.getStart(), range.getEnd(), newNumSteps);
    numSteps = newNumSteps;
}

//==============================================================================
float Parameter::getValue() const                           { return range.convertTo0to1 (value); }
void Parameter::setValue (float newValue)                   { value = range.convertFrom0to1 (newValue); }
float Parameter::getDefaultValue() const                    { return range.convertTo0to1 (defaultValue); }
float Parameter::getValueForText (const String& text) const { return range.convertTo0to1 (text.getFloatValue()); }

String Parameter::getText (float v, int length) const
{
    String asText (range.convertFrom0to1 (v)); // see JUCE to constrain decimal places
    return length > 0 ? asText.substring (0, length) : asText;
}


//==============================================================================
#if JF_UNIT_TESTS

class ParameterTests  : public UnitTest
{
public:
    ParameterTests()
        : UnitTest ("jf::Parameter")
    {
    }

    void runTest() override
    {
        Random rnd = getRandom();

        beginTest ("min < max");
        expectDoesNotThrow ((Parameter {"dummyID", "The Name", 0, 10, 0, 0, 0}));
        expectThrows       ((Parameter {"dummyID", "The Name", 0, -1, 0, 0, 0}));

        beginTest ("min <= default");
        expectThrows       ((Parameter {"dummyID", "The Name", 0, 10, -5, 0, 0}));
        expectDoesNotThrow ((Parameter {"dummyID", "The Name", 0, 10,  0, 0, 0}));

        beginTest ("default <= max");
        expectThrows       ((Parameter {"dummyID", "The Name", 0, 10, 20, 0, 0}));
        expectDoesNotThrow ((Parameter {"dummyID", "The Name", 0, 10, 10, 0, 0}));

        beginTest ("0 <= numSteps");
        expectThrows       ((Parameter {"dummyID", "The Name", 0, 10,  0, -1, 0}));
        expectDoesNotThrow ((Parameter {"dummyID", "The Name", 0, 10,  0, 0, 0}));

        beginTest ("set any skew");
        for (int i = 0; i < 1000; ++i)
            expectDoesNotThrow ((Parameter {"dummyID", "The Name", 0, 10,  0, 0, rnd.nextFloat()}));

        Parameter freq  {"id", "nm", 20, 20000, 632.456,   0, 3};
        Parameter steps {"id", "nm",  0,   127,       0, 128, 0};

        beginTest ("get() default");
        expect (freq.get() == 632.456f);

        beginTest ("getNumSteps()");
        expect (freq .getNumSteps() == 0);
        expect (steps.getNumSteps() == 128);

        beginTest ("setNumSteps()");
        expectDoesNotThrow (steps.setNumSteps(10));
        expect (steps.getNumSteps() == 10);
        expectThrows (steps.setNumSteps(-5));

        beginTest("getRange()");
        jf::RangeLog range {20, 20000, 3};
        expect (freq.getRange() == range);
    }
};

static ParameterTests parameterTests;

#endif // JF_UNIT_TESTS

} // namespace jf