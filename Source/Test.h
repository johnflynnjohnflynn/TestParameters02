/*
  ==============================================================================

    Test.h
    Created: 4 Jul 2016 8:01:54pm
    Author:  John Flynn

  ==============================================================================
*/

#ifndef TESTJF_H_INCLUDED
#define TESTJF_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/** Special version of jassert that throws exception instead of assertion when
    unit tests are switched on with the JF_UNIT_TESTS=1 preprocessor flag.
    
    Note: this won't break at the proper point during debugging. If your hitting
    an assert unrelated to the unit tests, try set JF_UNIT_TESTS=0

    @see jassert
*/
#if JF_UNIT_TESTS
 #define jfassert(expression) JUCE_BLOCK_WITH_FORCED_SEMICOLON (if (! (expression)) throw std::logic_error ("");)
#else
 #define jfassert(expression) JUCE_BLOCK_WITH_FORCED_SEMICOLON (jassert (expression);)
#endif

//==============================================================================
/** Boilerplate macro to make sure a static instance of a test gets created in 
    the header. (Otherwise an instance of the class will need to be created 
    somewhere else before the tests run.)

    @see UnitTestRunner
*/

#if JF_UNIT_TESTS
 #define JF_DECLARE_UNIT_TEST_WITH_STATIC_INSTANCE(TestClassName)   \
 class TestClassName  : public UnitTest                                     \
 {                                                                          \
 public:                                                                    \
     TestClassName();                                                       \
     void runTest() override;                                               \
 };                                                                         \
 static TestClassName TestClassName; // eek! instance same as class name
#else
 #define JF_DECLARE_UNIT_TEST_WITH_STATIC_INSTANCE(TestClassName) // do nothing
#endif

namespace jf {

//==============================================================================
class ConsoleLogger : public Logger {};
class ConsoleUnitTestRunner : public UnitTestRunner {};

//==============================================================================
/** Namespace level method creates a UnitTestRunner then calls runAllTests() 
    when JF_UNIT_TESTS=1 preprocessor flag set in Jucer.

   #if JF_UNIT_TESTS
    jf::runUnitTests();
   #endif
   
    ...in plugin processor's constructor will run all unit tests automatically. 
    You will probably need an instance of the class in the plugin somewhere so
    that at the static unit test member is created.

    See bottom of classes for unit tests i.e. @see RangeLog
    
    Leaked object assertions? Remember to set JF_UNIT_TEST=0 and search for a 
    problem jassert outside of the tests.
*/
void runUnitTests();

//==============================================================================
} // namespace jf

#endif  // TESTJF_H_INCLUDED
