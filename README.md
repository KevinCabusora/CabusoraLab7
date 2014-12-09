CabusoraLab7
============

IR Sensing

##Prelab
Include whatever information from this lab you think will be useful in creating your program.


Test your sensors with a DMM. Ensure they are functional. What would good reference values be?
* First I will use the DMM to test the extreme values of the sensors.
  - Right Sensor, No wall: 0.211V; Wall: 4.45V
  - Center Sensor, No wall: 0.354V; Wall: 3.85V
  - Left Sensor, No wall: 0.673V; Wall: 5.12V
* Judging from the sensor and the wall distance, I will need to create a good threshold for the sensor readings for which to perform an action.
  - I will choose 5 inches as my standard for the front sensor.
  - The reading says about ~1.05 volts, so my threshold will be 1V, with a noise margin of around 0.2V.
  - Using the same standard for distance for the left sensor, I received 3V.  I will use a noise margin of around 0.2V.
  - For the right sensor, the output voltage was much less.  It was around 0.55V.  My noise margin will be less; around 0.05V.


Consider how you'll setup the ADC10 subsystem. What are the registers you'll need to use? Which bits in those registers are important? What's the initialization sequence you'll need?
* I would first stop the watchdog timer, then enable the interrupts for the ADC10.
  - These interrupts look like the following:
  ```
  ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
  ```
  - ADC10SHT_3 controls the amount of time per sample, which is as long as possible to prevent loading.  ADC10ON turns the subsystem on, and ADC10ON enables the interrupt.
* I would next set the inputs.
  ```
  ADC10CTL1 = INCH_1;                       // input A0
  ADC10AE0 |= BIT1; 
  ADC10CTL1 = INCH_2;                       // input A1
  ADC10AE0 |= BIT2;
  ADC10CTL1 = INCH_3;                       // input A2
  ADC10AE0 |= BIT3;
  ```
* Next I will set up the SMCLK to be the ADC clock source.
* Next I will set P1.0 to the output direction; this will set the LEDs.
* In regards to registers, we are dealing with bits 4-3, or the ADC10 clock source select.  We will also deal with bits 15-12 in INCHx, which are the input channel select controls; in particular A0, A1, and A2.
* In a forever loop, I will then enable the core, in which control bits can only be modified when the core is disabled, then is told to begin a sample-and-conversion sequence.
* In this loop we will next turn off the CPU and then enable the interrupts.  The purpose of the loop is to toggle the led whenever there is a sample detected.

Consider the hardware interface. Which ADC10 channels will you use? Which pins correspond to those channels?
* I will use three separate channels for the ADC10:  A1, A2, and A3.
* Pins 3, 4, and 5 correspond to these channels.
* Below is a diagram of what my connections will look like and which port goes into which sensor.

Consider the interface you'll create to your sensors. Will you block or use interrupts? Will you convert one sensor at a time or multiple?
* For this I will consider how I will have the robot move primarily.  I will have the robot continually sense for a certain distance in the center sensor, then stop.  From there it will measure both left and right.  If the left voltage is less than the right, for instance, then the robot will turn left 90 degrees, and then will revert to looking through the center sensor again.
* I will use interrupts; when the voltage of the center sensor goes high then the robot will stop and turn.
* I will probably convert one sensor at a time since all three sensors are not necessary at the same time for my design.

Redone Voltage Readings (around 5 inches)

Left sensor=1.35 V; Center sensor = 1.22 V; Right sensor = 1.69 V
