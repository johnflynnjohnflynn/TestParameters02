/*
  ==============================================================================

    Range.h
    Created: 4 Jul 2016 8:24:01pm
    Author:  John Flynn

  ==============================================================================
  ==============================================================================

   This file is part of the juce_core module of the JUCE library.
   Copyright (c) 2015 - ROLI Ltd.

   Permission to use, copy, modify, and/or distribute this software for any purpose with
   or without fee is hereby granted, provided that the above copyright notice and this
   permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
   TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
   NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
   DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
   IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
   CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ------------------------------------------------------------------------------

   NOTE! This permissive ISC license applies ONLY to files within the juce_core module!
   All other JUCE modules are covered by a dual GPL/commercial license, so if you are
   using any other modules, be sure to check that you also comply with their license.

   For more details, visit www.juce.com

  ==============================================================================
*/

#ifndef RANGE_H_INCLUDED
#define RANGE_H_INCLUDED


//==============================================================================
/**
    Represents a mapping between an arbitrary range of values and a
    normalised 0->1 range.

    The properties of the mapping also include an optional snapping interval
    and skew-factor.
    
    This modifies JUCE's own NormalisableRange to allow more complex logarithmic
    skew factor.

    @see NormalisableRange
*/
template <typename ValueType>
class RangeLog
{
public:
    /** Creates a continuous range that performs a dummy mapping. */
    RangeLog() noexcept
        : start    (static_cast<ValueType> (0)),
          end      (static_cast<ValueType> (1)),
          interval (static_cast<ValueType> (0)),
          skewLog  (static_cast<ValueType> (0))
    {
    }

    /** Creates a copy of another range. */
    RangeLog (const RangeLog& other) noexcept
        : start (other.start), end (other.end),
          interval (other.interval), skewLog (other.skewLog)
    {
        checkInvariants();
    }

    /** Creates a copy of another range. */
    RangeLog& operator= (const RangeLog& other) noexcept
    {
        start = other.start;
        end = other.end;
        interval = other.interval;
        skewLog = other.skewLog;
        checkInvariants();
        return *this;
    }

    /** Creates a RangeLog with a given range, interval and skew factor. */
    RangeLog (ValueType rangeStart,
                       ValueType rangeEnd,
                       ValueType intervalValue,
                       ValueType skewLogFactor) noexcept
        : start (rangeStart), end (rangeEnd),
          interval (intervalValue), skewLog (skewLogFactor)
    {
        checkInvariants();
    }

    /** Creates a RangeLog with a given range and interval, but dummy skew-factors. */
    RangeLog (ValueType rangeStart,
                       ValueType rangeEnd,
                       ValueType intervalValue) noexcept
        : start (rangeStart), end (rangeEnd),
          interval (intervalValue), skewLog (static_cast<ValueType> (0))
    {
        checkInvariants();
    }

    /** Creates a RangeLog with a given range, continuous interval, but a dummy skew-factor. */
    RangeLog (ValueType rangeStart,
                       ValueType rangeEnd) noexcept
        : start (rangeStart), end (rangeEnd),
          interval(), skewLog (static_cast<ValueType> (0))
    {
        checkInvariants();
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
            proportion = (std::log10 ((proportion * (tenPowSkewLog - one)) + one)) / std::log10 (tenPowSkewLog);
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
            proportion = (std::pow (tenPowSkewLog, proportion) - one) / (tenPowSkewLog - one);
        }

        return start + ((end - start) * proportion);
    }

    /** Takes a non-normalised value and snaps it based on the interval property of
        this RangeLog. */
    ValueType snapToLegalValue (ValueType v) const noexcept
    {
        if (interval > ValueType())
            v = start + interval * std::floor ((v - start) / interval + static_cast<ValueType> (0.5));

        if (v <= start || end <= start)
            return start;

        if (v >= end)
            return end;

        return v;
    }

    // Originally in JUCE but don't understand? return a copy range but without interval and skew?
    // RangeLog<ValueType> getRange() const noexcept          { return RangeLog<ValueType> (start, end); }

    /** The start of the non-normalised range. */
    ValueType start;

    /** The end of the non-normalised range. */
    ValueType end;

    /** The snapping interval that should be used (in non-normalised value). Use 0 for a continuous range. */
    ValueType interval;

    /** An optional skew factor that alters the way values are distribute across the range.

        The skew factor lets you skew the mapping logarithmically so that larger or smaller
        values are given a larger proportion of the available space.
        
        Uses a more computationally expensive calculation than JUCE's skew
        but is more accurate for things like decade based frequency scales.

        A factor of 0.0 will be a straight line x=y, (skips
        calculation) 
        
        A factor of 1.0 will have 1 log decade per scale, 2.0 will give 2 etc. A factor of -1.0
        will be the inverse of +1.0.

        For a 3 decade Hz frequency scale, start and end should be 20 and 20000 respectively and
        skewLog should be set to 3.0.
    */
    ValueType skewLog;

    //class Bad {}; // throw on invariant violation

private:
    void checkInvariants() const
    {
        //if (start > end) throw Bad {};
        jassert (end > start);
        jassert (interval >= static_cast<ValueType> (0));
        jassert (interval <= (end - start));
    }
};


//==============================================================================
#if JF_UNIT_TESTS

class RangeLogTests  : public UnitTest
{
public:
    RangeLogTests() : UnitTest ("RangeLog") {}

    bool floatEqual (float a, float b)
    {
        return std::abs(b - a) < 0.01;
    }

    void runTest() override
    {
        Random rnd = getRandom();

        beginTest ("RangeLog<float> default constructor empty");
        RangeLog<float> r1;
        expect (r1.start    == 0.0f);
        expect (r1.end      == 1.0f);
        expect (r1.interval == 0.0f);
        expect (r1.skewLog  == 0.0f);

        beginTest ("RangeLog<float> copy constructor");
        RangeLog<float> r2 {r1};
        expect (r2.start    == 0.0f);
        expect (r2.end      == 1.0f);
        expect (r2.interval == 0.0f);
        expect (r2.skewLog  == 0.0f);

        beginTest ("RangeLog<float> copy assignment");
        RangeLog<float> r3;
        r3 = r1;
        expect (r3.start    == 0.0f);
        expect (r3.end      == 1.0f);
        expect (r3.interval == 0.0f);
        expect (r3.skewLog  == 0.0f);

        beginTest ("RangeLog<float> constructor all args");
        RangeLog<float> r4 {0, 1, 0, 0};
        expect (r4.start    == 0.0f);
        expect (r4.end      == 1.0f);
        expect (r4.interval == 0.0f);
        expect (r4.skewLog  == 0.0f);

        beginTest ("RangeLog<float> constructor first 3 args");
        RangeLog<float> r5 {0, 1, 0};
        expect (r5.start    == 0.0f);
        expect (r5.end      == 1.0f);
        expect (r5.interval == 0.0f);
        expect (r5.skewLog  == 0.0f);

        beginTest ("RangeLog<float> constructor first 2 args");
        RangeLog<float> r6 {0, 1};
        expect (r6.start    == 0.0f);
        expect (r6.end      == 1.0f);
        expect (r6.interval == 0.0f);
        expect (r6.skewLog  == 0.0f);

        beginTest ("RangeLog<float>::checkInvariants()");
        RangeLog<float> {-50, 50, 1, -2};
            // jassert (end > start);
        //RangeLog<float> {0, -1, 1, 0}; // end before start
        //RangeLog<float> {0, 0, 0, 0}; // end == start
            // jassert (interval >= static_cast<ValueType> (0));
        //RangeLog<float> {0, 1, -1, 0}; // interval < 0;
        //RangeLog<float> {0, 1, 0, 0}; // interval < 0;
            // jassert (interval <= (end - start));
        //RangeLog<float> {0, 1, 5, 0}; // interval > (end - start)
        RangeLog<float> {0, 1, 1, 0}; // interval == (end - start)

        beginTest ("RangeLog<float>::convertTo0to1()");
        RangeLog<float> r7 {0, 127, 0, 0};
        expect (r7.convertTo0to1 (127) == 1.0f);
        expect (r7.convertTo0to1 (0)   == 0.0f);
        expect (r7.convertTo0to1 (63.5)  == 0.5f);

        RangeLog<float> r8 {20, 20000, 0, 3}; // 3 decade log frequency scale
        expect (r8.convertTo0to1 (20000) == 1.0f);
        expect (r8.convertTo0to1 (20)    == 0.0f);
        expect (floatEqual (r8.convertTo0to1 (632.456), 0.5f));
        expect (floatEqual (r8.convertTo0to1 (200), 0.333f));
        expect (floatEqual (r8.convertTo0to1 (2000), 0.666f));
        expect (floatEqual (r8.convertTo0to1 (6300), 0.833));

        r8 = RangeLog<float> {20, 20000, 0, 3}; // 3 decade log frequency scale
        beginTest ("RangeLog<float>::convertFrom0to1()");
        expect (floatEqual (r8.convertFrom0to1 (0.5), 632.456f));
        expect (floatEqual (r8.convertFrom0to1 (0.0), 20.0f));
        expect (floatEqual (r8.convertFrom0to1 (1.0), 20000.0f));
        expect (floatEqual (r8.convertFrom0to1 (0.33333), 200.0f));     // long decimal placings needed for these
        expect (floatEqual (r8.convertFrom0to1 (0.666666), 2000.0f));
        expect (floatEqual (r8.convertFrom0to1 (0.8333333), 6324.56f));

        // Todo: RangeLog<float>::snapToLegalValue()
    }
};

static RangeLogTests rangeTests;

#endif


#endif  // RANGE_H_INCLUDED
