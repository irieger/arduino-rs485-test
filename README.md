# arduino-rs485-test

Small set of test code to play with Serial communication between two Arduino Mega (Used for ease of use with additional serial ports, can be implemented for smaller ones also).

Should sent data input on serial monitor (expects unsigned int size integer, may overflow). MAX485 chip connected to Serial2 Ports on the Megas, Port 10 is connected to RX_Enable and TX_Enable pin (as RX is inverted it can be just combined).

Code works if Arduinos are connected directly *A0 TX -> A1 RX* and *A0 RX <- A1 TX*, but has problems when using the MAX485 chips. Values are screwed up in transfer as shown in the example. Tried with different baud rates and adjustments on the delays for TX activation.
See output of Serial Monitor in *output-master.txt* and *output-slave.txt*