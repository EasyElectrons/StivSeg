# StivSeg
Multi-digit seven-segment display library for arduino.  Light-weight design allows the user to continuously write data gathered (ideally) from a TimerOne interrupt.

##Documentation
###Constructors
* **StivSeg(int numDigits, int digitPins[], int segPins[], bool isComCathode)** \- Constructs a StivSeg object with standard multiplexing.  1 object represents the whole display.
  * * **numDigits** is the number of digits you have.
  **digitPins[]** is an array containing the pins connected to the commons of your display, ordered from least to most significant digit.
  **segPins[]** is an array containing the pins connected to the segments of your display, ordered alphabetically with the decimal point last.
  **isComCathode** is for indicating whether your display is common cathode or common anode.  Set **true** for common cathode.

###Functions
* **writeInt(int num)** \- Writes an integer to the display.  NOTE: make sure num does not have more digits than your display.
* **writeFloat(int num)** \- Writes a float to the display.
* **clear()** \- Clears the display.
