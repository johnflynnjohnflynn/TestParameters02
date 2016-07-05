/*
  ==============================================================================

    Parameter.h
    Created: 5 Jul 2016 1:01:42pm
    Author:  John Flynn

  ==============================================================================
*/

#ifndef PARAMETER_H_INCLUDED
#define PARAMETER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Range.h"

namespace jf
{

//==============================================================================
/** Modification of AudioParameterFloat using a jf::RangeLog.
    
    A subclass of AudioProcessorParameter that provides an easy way to create a
    parameter which maps onto a given RangeLog

    @see AudioParameterFloat
*/
class Parameter  : public AudioProcessorParameterWithID
{
public:
    Parameter (String parameterID,  // no spaces
               String name,         // spaces allowed
               float minValue,
               float maxValue,
               float defaultValue,
               int numSteps = 0,
               float skewLog = 0.0f);

    ~Parameter() {}

    float get() const noexcept          { return value; }
    operator float() const noexcept     { return value; } // allows dereference access
        //Parameter& operator= (float newValue); // changes value

    jf::RangeLog range;                                  // should we? setRange methods instead?

    int getNumSteps() const override    { return numSteps; }
    void setNumSteps (int newNumSteps);

private:
    float value;
    float defaultValue;
    int numSteps;

    float getValue() const override;                // for base class and host to call.
    void setValue (float newValue) override;        // no need to public. all vals 0to1.
    float getDefaultValue() const override;
    String getText (float, int) const override;
    float getValueForText (const String&) const override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Parameter)
};

} // namespace jf

#endif  // PARAMETER_H_INCLUDED
