CabusoraLab7
============

IR Sensing

#Prelab
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


Consider the hardware interface. Which ADC10 channels will you use? Which pins correspond to those channels?
* 

Consider the interface you'll create to your sensors. Will you block or use interrupts? Will you convert one sensor at a time or multiple?
* For this I will consider how I will have the robot move primarily.  I will have the robot continually sense for a certain distance in the center sensor, then stop.  From there it will measure both left and right.  If the left voltage is less than the right, for instance, then the robot will turn left 90 degrees, and then will revert to looking through the center sensor again.
* I will use interrupts; when the voltage of the center sensor goes high then the robot will stop and turn.
* I will probably convert one sensor at a time since all three sensors are not necessary at the same time for my design.
