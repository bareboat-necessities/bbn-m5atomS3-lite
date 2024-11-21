# Resistance sensor with M5Stack AtomS3-Lite

In order to measure the resistance you can measure voltage using ADC (analog) input esp32 pin on a voltage divider circuit.

Voltage divider circuit consists of:

- Resistor of a known resistance
- Sensor's resistor for which resistance is to be measured
- Known reference voltage (3.3v for esp32 case) applied to those two resistors connected in series

Voltage is measured on ADC (analog) input pin of esp32 connected in between those two resistors.

Ohm Law can be used to calculate unknown resistance from voltage drop (knowing reference voltage and reference resistor resistance)

There are two kinds of configurations for this circuit: 

Either the variable resistor is close to GND (DOWNSTREAM) or it is closer to VCC (UPSTREAM).


![image](img/VoltageDivider.png)


$$
\begin{flalign}
& \large {V _{ref} \over {R _{ref} + R _{sensor}}} = {V _{mes} \over {R _{ref}}} \text{ } \Rightarrow \text{ }
 R _{sensor} = {R _{ref} {{V _{ref} - V _{mes}} \over V _{mes}}} &
\end{flalign}
$$


$$
\begin{flalign}
& \large {V _{ref} \over {R _{ref} + R _{sensor}}} = {V _{mes} \over {R _{sensor}}}&
\end{flalign}
$$



