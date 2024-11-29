# Alternator Wave Form (from 'W' terminal) to Frequency and to RPM via PC817 optocoupler

There are small ready-to-use PCBs which include PC817 optocoupler and a circuit with one light emiting diode, two resistors and
two screw-in terminals (2-pole for input and 3-pole for output GND/OUT/VCC)

You can find them searching Internet for:

817 optocoupler isolation module

The circuit of the boars looks like this:


![PC817 optocoupler isolation module board](img/PC817_optocoupler_circuit.png)


There are different variations of the board for 12V input signal or 24V with different pull down resistor on the board.

Select appropriate one for your alternator voltage. 

Alternator has a terminal marked 'W' which gives a sine wave form of the alternator output.

## Connections

Input from alternator:
- Alternator ground to Board '-' INPUT on 2-pin terminal
- Alternator 'W' to Board '+' INPUT on 2-pin terminal

Output to esp32:
- Board 3-pin output terminal GND to esp32 GND
- Board 3-pin output terminal VCC to esp32 +3.3v VCC
- Board 3-pin output terminal OUT to some analog input pin on esp32
