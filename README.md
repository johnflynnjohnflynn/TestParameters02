
TestParameters02
----------------

### Audio plugin state handling including A/B compare and preset file save/load in JUCE

![TestParameters02 image](http://www.johnflynn.info/images/TestParameters02.png)

More robust preset handling system for plugins. Uses more sophisticated (and more readable) parameter/slider stepping system aimed at variably stepped gain and frequency controls.

Also unit testing system that runs whenever the plugin is loaded and the JF_UNIT_TESTS=1 flag is set.

- Auto run unit testing including assert catcher
- A/B comparisons
- Preset file save/load to OS specific application data folder
- Variably stepped parameters/sliders

To do:

- Equaliser. Currently audio passthrough.
- GUI styling with LookAndFeel methods

See [www.johnflynn.info](http://www.johnflynn.info/)
