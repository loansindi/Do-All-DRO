Do-All-DRO
==========

A simple, attiny85 based digital RPM readout. Uses the MIT attiny libraries.

The code, as it stands, is set up for a 6 digit 7 segment display using shift registers. Speed measurements are made with an external interrupt - in my implementation this is triggered with a hall effect sensor and a magnet. This could easily be a physical microswitch (with appropriate debouncing), an optical switch, a reed switch or anything else that's suitable for your expected rates.

My implementation is accurate to within 20 RPM, tested with an optical tachometer.
