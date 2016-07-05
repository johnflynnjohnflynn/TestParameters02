/*
  ==============================================================================

    Range.h
    Created: 4 Jul 2016 8:24:01pm
    Author:  John Flynn

  ==============================================================================
*/

#ifndef RANGE_H_INCLUDED
#define RANGE_H_INCLUDED


namespace jf {

template <typename ValueType>                                       // forward declares
bool isGood (ValueType start, ValueType end, ValueType interval);
template <typename ValueType>
void checkInvariants (ValueType start, ValueType end, ValueType interval);

//==============================================================================
/** 
    Represents a mapping between an arbitrary range of values and a
    normalised 0->1 range.

    The properties of the mapping also include an optional snapping interval
    and skew-factor.
    
    Modifies JUCE's own NormalisableRange to allow more complex logarithmic
    skew factor.

    @see juce::NormalisableRange
*/
template <typename ValueType>
class RangeLog
{
public:
    /** Creates a continuous range that performs a dummy mapping.
    */
    RangeLog() // noexcept                                  // All xtors need to
        : start    (static_cast<ValueType> (0)),            // except for unit tests!
          end      (static_cast<ValueType> (1)),
          interval (static_cast<ValueType> (0)),
          skewLog  (static_cast<ValueType> (0))
    {
    }

    /** Creates a RangeLog with a given range, interval and skew factor. 
    */
    RangeLog (ValueType rangeStart,
              ValueType rangeEnd,
              ValueType intervalValue,
              ValueType skewLogFactor)
        : start (rangeStart), end (rangeEnd),
          interval (intervalValue), skewLog (skewLogFactor)
    {
        checkInvariants (start, end, interval);
    }

    /** Creates a RangeLog with a given range and interval, but dummy skew-factors. 
    */
    RangeLog (ValueType rangeStart,
              ValueType rangeEnd,
              ValueType intervalValue)
        : start (rangeStart), end (rangeEnd),
          interval (intervalValue), skewLog (static_cast<ValueType> (0))
    {
        checkInvariants (start, end, interval);
    }

    /** Creates a RangeLog with a given range, continuous interval, but a dummy skew-factor. 
    */
    RangeLog (ValueType rangeStart,
              ValueType rangeEnd)
        : start (rangeStart), end (rangeEnd),
          interval(), skewLog (static_cast<ValueType> (0))
    {
        checkInvariants (start, end, interval);
    }

    /** Uses the properties of this mapping to convert a non-normalised value to
        its 0->1 representation.
    */
    ValueType convertTo0to1 (ValueType v) const noexcept
    {
        ValueType proportion = (v - start) / (end - start);

        if (skewLog != static_cast<ValueType> (0))
        {
            const ValueType one = static_cast<ValueType> (1.0);
            const ValueType ten = static_cast<ValueType> (10.0);
            const ValueType tenPowSkewLog = std::pow (ten, skewLog);
            proportion = (std::log10 ((proportion * (tenPowSkewLog - one)) + one))
                        / std::log10 (tenPowSkewLog);
        }

        return proportion;
    }

    /** Uses the properties of this mapping to convert a normalised 0->1 value to
        its full-range representation.
    */
    ValueType convertFrom0to1 (ValueType proportion) const noexcept
    {
        if (skewLog != static_cast<ValueType> (0))
        {
            const ValueType one = static_cast<ValueType> (1.0);
            const ValueType ten = static_cast<ValueType> (10.0);
            const ValueType tenPowSkewLog = std::pow (ten, skewLog);
            proportion = (std::pow (tenPowSkewLog, proportion) - one)
                       / (tenPowSkewLog - one);
        }

        return start + ((end - start) * proportion);
    }

    /** The start of the non-normalised range. 
    */
    ValueType getStart() const noexcept { return start; }
    void setStart (ValueType newStart)
    {
        checkInvariants (newStart, end, interval);
        start = newStart;
    }

    /** The end of the non-normalised range. 
    */
    ValueType getEnd() const noexcept { return end; }
    void setEnd (ValueType newEnd)
    {
        checkInvariants (start, newEnd, interval);
        end = newEnd;
    }

    /** The snapping interval that should be used (in non-normalised value). 
        Use 0 for a continuous range. 
    */
    ValueType getInterval() const noexcept { return interval; }
    void setInterval (ValueType newInterval)
    {
        checkInvariants (start, end, newInterval);
        interval = newInterval;
    }

    /** An optional skew factor that alters the way values are distributed across the range.

        The skew factor lets you skew the mapping logarithmically so that larger or smaller
        values are given a larger proportion of the available space.
        
        Uses a more computationally expensive calculation than JUCE's skew
        but is more accurate for things like decade based frequency scales.

        A factor of 0.0 will be a straight line x=y, (skips calculation)
        
        A factor of 1.0 will have 1 log decade per scale, 2.0 will give 2 etc. 
        A factor of -1.0 will be the inverse of +1.0.

        For a 3 decade Hz frequency scale, start and end should be 20 and 20000 
        respectively and skewLog should be set to 3.0.
    */
    ValueType getSkewLog() const noexcept { return interval; }
    void setSkewLog (ValueType newSkewLog)
    {
        checkInvariants (start, end, interval);
        skewLog = newSkewLog;
    }

private:
    ValueType start;
    ValueType end;
    ValueType interval;
    ValueType skewLog;
};

//==============================================================================
/** Non-members 
*/
template <typename ValueType>
bool operator== (const RangeLog<ValueType>& a, const RangeLog<ValueType>& b)
{
    return a.getStart()    == b.getStart()
        && a.getEnd()      == b.getEnd()
        && a.getInterval() == b.getInterval()
        && a.getSkewLog()  == b.getSkewLog();
}

template <typename ValueType>
bool isGood (ValueType start, ValueType end, ValueType interval)
{
    return (end > start)
        && (interval >= static_cast<ValueType> (0))
        && (interval <= (end - start));
}

/** Throws on creation of invalid object if JF_UNIT_TESTS preprocessor flag
    is set in jucer. Unit test then catches any throws. Otherwise enforce 
    regular run-time assertions
*/
template <typename ValueType>
void checkInvariants (ValueType start, ValueType end, ValueType interval) // skewLog can be any value
{
   #if JF_UNIT_TESTS
    if (! isGood(start, end, interval)) throw std::logic_error ("Invalid RangeLog<>\n");
   #endif // JF_UNIT_TESTS

    jassert (isGood(start, end, interval));
}

} // namespace jf


//==============================================================================
#if JF_UNIT_TESTS

class RangeLogTests  : public UnitTest
{
public:
    RangeLogTests() : UnitTest ("jf::RangeLog<float>") {}

    bool floatEqualApprox (float a, float b)
    {
        return std::abs(b - a) < 0.01;
    }

    void runTest() override
    {
        Random rnd = getRandom();

        beginTest ("Default constructor");
        jf::RangeLog<float> r1;
        expect (r1.getStart()    == 0.0f);
        expect (r1.getEnd()      == 1.0f);
        expect (r1.getInterval() == 0.0f);
        expect (r1.getSkewLog()  == 0.0f);

        beginTest ("operator==");
        jf::RangeLog<float> rEquals;
        expect (rEquals == r1);

        beginTest ("Copy constructor");
        jf::RangeLog<float> rCopy {r1};
        expect (rCopy == r1);

        beginTest ("Copy assignment");
        jf::RangeLog<float> rCopyA;
        rCopyA = r1;
        expect (rCopyA == r1);

        beginTest ("Constructor all 4 args");
        jf::RangeLog<float> rAllArgs {0, 1, 0, 0};
        expect (rAllArgs == r1);

        beginTest ("Constructor 3of4 args");
        jf::RangeLog<float> r3Args {0, 1, 0};
        expect (r3Args == r1);

        beginTest ("Constructor first 2 args");
        jf::RangeLog<float> r2Args {0, 1};
        expect (r2Args == r1);

        beginTest ("checkInvariants()");
        expectDoesNotThrow ((jf::RangeLog<float> {-50, 50, 1, -2}));
        expectThrows ((jf::RangeLog<float> {0, -1, 1, 0})); // end before start
        expectThrows ((jf::RangeLog<float> {0, 0, 0, 0}));  // end == start
        expectThrows ((jf::RangeLog<float> {0, 1, -1, 0})); // interval < 0;
        expectDoesNotThrow ((jf::RangeLog<float> {0, 1, 0, 0}));  // interval == 0;
        expectThrows ((jf::RangeLog<float> {0, 1, 5, 0}));  // interval > (end - start)
        expectDoesNotThrow ((jf::RangeLog<float> {0, 1, 1, 0})); // interval == (end - start)

        beginTest ("convertTo0to1()");
        jf::RangeLog<float> r0to127 {0, 127, 0, 0};
        expect (r0to127.convertTo0to1 (127) == 1.0f);
        expect (r0to127.convertTo0to1 (0)   == 0.0f);
        expect (r0to127.convertTo0to1 (63.5)  == 0.5f);

        jf::RangeLog<float> rFreq {20, 20000, 0, 3}; // 3 decade log frequency scale
        expect (rFreq.convertTo0to1 (20000) == 1.0f);
        expect (rFreq.convertTo0to1 (20)    == 0.0f);
        expect (floatEqualApprox (rFreq.convertTo0to1 (632.456), 0.5f));
        expect (floatEqualApprox (rFreq.convertTo0to1 (200), 0.333f));
        expect (floatEqualApprox (rFreq.convertTo0to1 (2000), 0.666f));
        expect (floatEqualApprox (rFreq.convertTo0to1 (6300), 0.833));

        beginTest ("convertFrom0to1()");
        expect (floatEqualApprox (rFreq.convertFrom0to1 (0.5), 632.456f));
        expect (floatEqualApprox (rFreq.convertFrom0to1 (0.0), 20.0f));
        expect (floatEqualApprox (rFreq.convertFrom0to1 (1.0), 20000.0f));
        expect (floatEqualApprox (rFreq.convertFrom0to1 (0.33333), 200.0f));
        expect (floatEqualApprox (rFreq.convertFrom0to1 (0.666666), 2000.0f));
        expect (floatEqualApprox (rFreq.convertFrom0to1 (0.8333333), 6324.56f));
                                                         // long decimals needed, why?

                                    // Todo: beginTest ("RangeLog<float>::snapToLegalValue()");

        jf::RangeLog<float> rMemSets;

        beginTest ("setStart()");
        expect (rMemSets == r1);
        expectThrows (rMemSets.setStart(99999));
        expect (rMemSets == r1);
        expectDoesNotThrow (rMemSets.setStart(-1));
        expectDoesNotThrow (rMemSets.setStart(0));
        expect (rMemSets == r1);

        beginTest ("setEnd()");
        expectThrows (rMemSets.setEnd(-99999));
        expectDoesNotThrow (rMemSets.setEnd(99));
        expectDoesNotThrow (rMemSets.setEnd(1));
        expect (rMemSets == r1);
        
        beginTest ("setInterval()");
        expectDoesNotThrow (rMemSets.setInterval(0.5));
        expect (! (rMemSets == r1));
        expectDoesNotThrow (rMemSets.setInterval(0));
        expectThrows (rMemSets.setInterval(555));
        expect (rMemSets == r1);
        
        beginTest ("setSkewLog()");
        for (int i = 0; i < 1000; ++i)
            expectDoesNotThrow (rMemSets.setSkewLog (rnd.nextFloat()));
    }
};

static RangeLogTests rangeTests;

#endif // JF_UNIT_TESTS


#endif  // RANGE_H_INCLUDED
