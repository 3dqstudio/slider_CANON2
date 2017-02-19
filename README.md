# slider_CANON2
I did this a while ago for a one time project using an arduino UNO and some VEX robotics metal parts as well as a DC motor with a gear slider. It's really simple, not really good for continuos footage but great for stop motion. The program controls the autofocus and shutter, this way you don't interact with the camera and move it by mistake. 
I know it would be far better to use a stepper motor for positioning and stability but that was what I had at the time. 

The motor has its own 12V source and the arduino uses the USB 5V source. 
I don't have a circuit diagram but you could figure it out in the code. I remember I used two phototransistors 4N25 because I had some weird problems when attaching GND from the 12V source for the motor and GND from arduino. I'm know there is a way to solve it but I did not have the time to figure it out, so it was easier to just use these and use separate GNDs, or something like that! I'm not sure any more haha. I'm sure it's easy to solve it out once you build the circuit.

If you need any help let me know, I'll be glad to help.
