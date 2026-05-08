**Dedicated Motion Controller for 2-/3-Phase PMSM** **INTEGRATED CIRCUITS**

# TMC4671 Datasheet


IC Version V1.3 | Document Revision V2.08 • 2022-July-26


**The TMC4671 is a fully integrated servo controller, providing Field Oriented Control for BLDC/PMSM**
**and 2-phase Stepper Motors as well as DC motors and voice coils.** **All control functions are imple-**
**mented** **in** **hardware.** **Integrated** **ADCs,** **position** **sensor** **interfaces,** **position** **interpolators,** **enable**


Features


                                      - Servo Controller
w/ Field Oriented Control (FOC)

                                      - Torque Control (FOC),
Velocity Control, Position Control

                                      - Integrated ADCs, ∆Σ-ADC Frontend

                                      - Encoder Engine: Hall analog/digital,
Encoder analog/digital

                                      - Supports 3-Phase PMSM/BLDC,
2-Phase Stepper Motors,
and 1-Phase DC Motors

                                      - Fast PWM Engine (25kHz ...100kHz)

                                      - Application SPI + Debug (UART, SPI)

                                      - Step-Direction Interface (S/D)
Applications



![](images/TMC4671-LA_datasheet_rev2.08.pdf-0-0.png)


- Robotics

- Pick and Place Machines

- Factory Automation

## Simplified Block Diagram




- E-Mobility

- Laboratory Automation

- Blowers




- Pumps



![](images/TMC4671-LA_datasheet_rev2.08.pdf-0-1.png)

©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
Download newest version at: [www.trinamic.com](http://www.trinamic.com)


Read entire documentation.


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 2 / 153

## **Contents**


**1** **Order Codes** **6**


**2** **Functional Summary** **7**


**3** **FOC Basics** **9**
3.1 Why FOC? . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 9
3.2 What is FOC? . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 9
3.3 Why FOC as pure Hardware Solution? . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 9
3.4 How does FOC work? . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 10
3.5 What is Required for FOC? . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 10
3.5.1 Coordinate Transformations - Clarke, Park, iClarke, iPark . . . . . . . . . . . . . . . . 11
3.5.2 Measurement of Stator Coil Currents . . . . . . . . . . . . . . . . . . . . . . . . . . . . 11
3.5.3 Stator Coil Currents I_U, I_V, I_W and Association to Terminal Voltages U_U, U_V, U_W 11
3.5.4 IgainADC[A/LSB] - ADC Integer Current Value to Real World Unit . . . . . . . . . . . . 12
3.5.5 UgainADC[V/LSB] - ADC Integer Voltage Value to Real World Unit . . . . . . . . . . . . 12
3.5.6 Measurement of Rotor Angle . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 12
3.5.7 Measured Rotor Angle vs. Magnetic Axis of Rotor vs. Magnetic Axis of Stator . . . . 12
3.5.8 Knowledge of Relevant Motor Parameters and Position Sensor (Encoder) Parameters 13
3.5.9 Proportional Integral (PI) Controllers for Closed Loop Current Control . . . . . . . . 14
3.5.10 Pulse Width Modulation (PWM) and Space Vector Pulse Width Modulation (SVPWM) 14
3.5.11 Orientations, Models of Motors, and Coordinate Transformations . . . . . . . . . . . 15


**4** **Functional Description** **16**
4.1 Functional Blocks . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 16
4.2 Communication Interfaces . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 17
4.2.1 SPI Slave User Interface . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 17
4.2.2 TRINAMIC Real-Time Monitoring Interface (SPI Master) . . . . . . . . . . . . . . . . . . 20
4.2.3 UART Interface . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 21
4.2.4 Step/Direction Interface . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 22
4.2.5 Single Pin Interface . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 22
4.2.6 GPIO Interface . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 23
4.3 Numerical Representation, Electrical Angle, Mechanical Angle, and Pole Pairs . . . . . . . . . 24
4.3.1 Numerical Representation . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 24
4.3.2 N_POLE_PAIRS, PHI_E, PHI_M . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 25
4.3.3 Numerical Representation of Angles PHI . . . . . . . . . . . . . . . . . . . . . . . . . . 26
4.4 ADC Engine . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 28
4.4.1 ADC current sensing channels ADC_I1 and ADC_I0 . . . . . . . . . . . . . . . . . . . . 28
4.4.2 ADC for analog Hall signals or analog sin-cos-encoders AENC_UX, AENC_VN, AENC_WY 28
4.4.3 ADC supply voltage measurement ADC_VM . . . . . . . . . . . . . . . . . . . . . . . . 28
4.4.4 ADC_VM for Brake Choppper . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 29
4.4.5 ADC EXT register option . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 29
4.4.6 ADC general purpose analog inputs AGPI_A and AGPI_B . . . . . . . . . . . . . . . . . 29
4.4.7 ADC RAW values . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 29
4.4.8 ADC_SCALE and ADC_OFFSET . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 29
4.4.9 ADC Gain Factors for Real World Values . . . . . . . . . . . . . . . . . . . . . . . . . . 29
4.4.10 Internal Delta Sigma ADCs . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 30
4.4.11 Internal Delta Sigma ADC Input Stage Configuration . . . . . . . . . . . . . . . . . . . 30
4.4.12 External Delta Sigma ADCs . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 32
4.4.13 ADC Group A and ADC Group B . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 32
4.4.14 Delta Sigma Configuration and Timing Configuration . . . . . . . . . . . . . . . . . . . 32
4.4.15 Internal Delta Sigma Modulators - Mapping of V_RAW to ADC_RAW . . . . . . . . . . 36
4.4.16 External Delta Sigma Modulator Interface . . . . . . . . . . . . . . . . . . . . . . . . . 37


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 3 / 153


4.5 Analog Signal Conditioning . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 39
4.5.1 FOC3 - Stator Coil Currents I_U, I_V, I_W and associated Voltages U_U, U_V, U_W . . 39
4.5.2 FOC2 - Stepper Coil Currents I_X, I_Y and associated Voltages U_X, U_Y . . . . . . . . 40
4.5.3 FOC1 - DC Motor Coil Current I_X1, I_X2, and associated Voltage U_X1, U_X2 . . . . . 40
4.5.4 ADC Selector & ADC Scaler w/ Offset Correction . . . . . . . . . . . . . . . . . . . . . . 41
4.6 Encoder Engine . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 42
4.6.1 Open-Loop Encoder . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 42
4.6.2 Incremental ABN Encoder . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 43
4.6.3 Secondary Incremental ABN Encoder . . . . . . . . . . . . . . . . . . . . . . . . . . . . 45
4.6.4 Digital Hall Sensor Interface with optional Interim Position Interpolation . . . . . . . 45
4.6.5 Digital Hall Sensor - Interim Position Interpolation . . . . . . . . . . . . . . . . . . . . 46
4.6.6 Digital Hall Sensors - Masking, Filtering, and PWM center sampling . . . . . . . . . . 46
4.6.7 Digital Hall Sensors together with Incremental Encoder . . . . . . . . . . . . . . . . . 48
4.6.8 Analog Hall and Analog Encoder Interface (SinCos of 0° 90° or 0° 120° 240°) . . . . . 48
4.6.9 Analog Position Decoder (SinCos of 0°90° or 0°120°240°) . . . . . . . . . . . . . . . . 49
4.6.10 Encoder Initialization Support . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 50
4.6.11 Velocity Measurement . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 50
4.6.12 Reference Switches . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 51
4.7 FOC23 Engine . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 52
4.7.1 ENI and ENO pins . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 52
4.7.2 PI Controllers . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 52
4.7.3 PI Controller Calculations - Classic Structure . . . . . . . . . . . . . . . . . . . . . . . . 52
4.7.4 PI Controller Calculations - Advanced Structure . . . . . . . . . . . . . . . . . . . . . . 54
4.7.5 PI Controller - Clipping . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 56
4.7.6 PI Flux & PI Torque Controller . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 57
4.7.7 PI Velocity Controller . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 57
4.7.8 P Position Controller . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 58
4.7.9 Inner FOC Control Loop - Flux & Torque . . . . . . . . . . . . . . . . . . . . . . . . . . 58
4.7.10 FOC Transformations and PI(D) for control of Flux & Torque . . . . . . . . . . . . . . 58
4.7.11 Motion Modes . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 59
4.7.12 Brake Chopper . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 60
4.8 Filtering and Feed-Forward Control . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 61
4.8.1 Biquad Filters . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 61
4.8.2 Standard Velocity Filter . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 62
4.8.3 Feed-Forward Control Structure . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 62
4.9 PWM Engine . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 63
4.9.1 PWM Polarities . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 63
4.9.2 PWM Engine and associated Motor Connectors . . . . . . . . . . . . . . . . . . . . . . 64
4.9.3 PWM Frequency . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 65
4.9.4 PWM Resolution . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 65
4.9.5 PWM Modes . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 65
4.9.6 Break-Before-Make (BBM) . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 65
4.9.7 Space Vector PWM (SVPWM) . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 66
4.9.8 Real- and Integer-Conversions . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 66


**5** **Safety Functions** **67**


**6** **FOC Setup - How to Turn a Motor** **70**
6.1 Select Motor Type . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 70
6.1.1 FOC1 Setup - How to Turn a Single Phase DC Motor . . . . . . . . . . . . . . . . . . . 70
6.1.2 FOC2 Setup - How to Turn a Two Phase Motor (Stepper) . . . . . . . . . . . . . . . . . 70
6.1.3 FOC3 Setup - How to Turn a Three Phase Motor (PMSM or BLDC) . . . . . . . . . . . 70
6.2 Set Number of Pole Pairs (NPP) . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 70
6.3 Run Motor Open Loop . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 71


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 4 / 153


6.3.1 Determination of Association between Phase Voltage and Phase Currents . . . . . . 71
6.3.2 Determination of Direction of Rotation and Phase Shift of Angles . . . . . . . . . . . 71
6.4 Selection of Position Sensors . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 71
6.4.1 Selection of FOC sensor for PHI_E . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 71
6.4.2 Selection of sensor for VELOCITY . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 71
6.4.3 Selection of sensor for POSITION . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 71
6.5 Modes of Operation - (Open Loop), Torque, Velocity, Positioning . . . . . . . . . . . . . . . . . 72
6.6 Controller Tuning . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 72


**7** **Register Map** **72**
7.1 Register Map - Overview . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 73
7.2 Register Map - Functional Description . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 77
7.3 Register Map - Defaults, min, max . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 111


**8** **Pinning** **128**


**9** **TMC4671 Pin Table** **130**


**10** **Electrical Characteristics** **134**
10.1 Absolute Maximum Ratings . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 134
10.2 Electrical Characteristics . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 134

10.2.1 Operational Range . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 134
10.2.2 DC Characteristics . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 135


**11** **Sample Circuits** **136**
11.1 Supply Pins . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 136
11.2 Clock and Reset Circuitry . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 136
11.3 Digital Encoder, Hall Sensor Interface and Reference Switches . . . . . . . . . . . . . . . . . . 136
11.4 Analog Frontend . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 137
11.5 Phase Current Measurement . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 137
11.6 Power Stage Interface . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 139


**12** **Setup Guidelines** **140**


**13** **Package Dimensions** **141**


**14** **Supplemental Directives** **144**
14.1 Producer Information . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 144
14.2 Copyright . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 144
14.3 Trademark Designations and Symbols . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 144
14.4 Target User . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 144
14.5 Disclaimer: Life Support Systems . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 144
14.6 Disclaimer: Intended Use . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 144
14.7 Collateral Documents & Tools . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 145


**15** **Errata of TMC4671-LA/-ES2/-ES** **146**
15.1 Errata of TMC4671-LA . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 146
15.2 Fixes of TMC4671-LA/-ES2 vs. Errata of TMC4671-ES . . . . . . . . . . . . . . . . . . . . . . . . 146
15.3 Errata of TMC4671-ES Engineering Samples as Reference . . . . . . . . . . . . . . . . . . . . . 147
15.4 Actions to Avoid Trouble . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 148
15.5 Recommendations . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 148


**16** **Figures Index** **149**


**17** **Tables Index** **150**


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 5 / 153


**18** **Revision History** **151**
18.1 IC Revision . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 151
18.2 Document Revision . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 151


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 6 / 153

## **1 Order Codes**

|Order Code|Description|Size|
|---|---|---|
|TMC4671-LA|TMC4671 FOC Servo Controller IC|10.5mm x 6.5mm|
|TMC4671-EVAL<br>TMC4671-BOB<br>Landungsbruecke<br>TMC-UPS-2A24V-A-EVAL<br>TMC-UPS-10A70V-A-EVAL<br>TMC4671-2A24V-EV-KIT<br>TMC4671-10A70V-EV-KIT<br>USB-2-RTMI|TMC4671 Evaluation Board<br>TMC4671 Breakout Board<br>MCU Board<br>Power Stage Board<br>Power Stage Board<br>Evaluation Kit<br>Evaluation Kit<br>Interface Adapter to use RTMI|55mm x 85mm<br>38mm x 40mm<br>85mm x 55mm<br>85mm x 55mm<br>85mm x 55mm<br>—<br>—<br>40mm x 20mm|



_Table 1:_ _Order codes_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 7 / 153

## **2 Functional Summary**


  - **Servo Controller with Field Oriented Control (FOC)**


**–** Torque (and flux) control mode


**–** Velocity control mode


**–** Position control mode


  - **Control Functions/PI Controllers**


**–** Programmable clipping of inputs and outputs of interim results


**–** Integrator windup protection for all controllers


**–** Status output with programmable mask for internal status signal selection


  - **Supported Motor Types**


**–** FOC3 : 3-phase permanent magnet synchronous motors (PMSM) / brushless DC motor (BLDC)


**–** FOC2 : 2-phase stepper motors


**–** FOC1 : 1-phase brushed DC motors, or linear voice coil motors


  - **ADC Engine with Offset Correction and Scaling**


**–** Integrated Delta Sigma ADCs for current sense voltage, supply voltage, analog encoder, AGPIs


**–** Interface for isolated external current sensing Delta Sigma modulators


  - **Position Feedback**


**–** Open loop position generator (programmable [rpm], [rpm/s]) for initial setup


**–** Digital incremental encoder (ABN resp. ABZ, up to 2 MHz)


**–** Secondary digital incremental encoder


**–** Digital Hall sensor interface (H1, H2, H3 resp. H_U, H_V, H_W) with interim position interpolation


**–** Analog encoder/analog Hall sensor interface (SinCos (0°, 90°) or 0°, 120°, 240°)


**–** Position target, velocity and target torque filters (Biquad)


**–** multi-turn position counter (32-bit)


  - **PWM Engine Including SVPWM**


**–** Programmable PWM frequency within the range of 25 kHz ...100 kHz


**–** PWM auto scaling for transparent change of PWM frequency during motion


**–** Programmable Brake-Before-Make (BBM) times (0 ns ...2.5 _µ_ s) for digital gate control signals


**–** Single bit SVPWM control (on/off) for Space Vector Modulation (switchable during operation)


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 8 / 153


  - **SPI Application Communication Interface**


**–** 40 bit datagram length (1 ReadWrite bit + 7 address bits + 32 data bits)


**–** Immediate SPI read response (register read access by single datagram)


**–** SPI clock frequency fSCK up to 2 MHz (8 MHz write, 8 MHz read w/ 500 ns pause after address)


  - **TRINAMIC Real Time Monitoring Interface**


**–** High frequency sampling of real-time data via TRINAMIC’s real-time monitoring system


**–** Only single 10 pin high density connector on PCB needed


**–** Enables frequency response identification and auto tuning options with TRINAMIC’s IDE


  - **UART Debug Interface**


**–** Three pin (GND, RxD, TxD) 3.3 V UART interface (1N8; 9600 (default), 115200, 921600, 3M bps)


**–** Available as port for external position sensors (e.g. absolute encoder together with processor)


**–** Transparent register access parallel to embedded user application interface (SPI)


  - **Supply Voltages**


**–** 5V and 3.3V; VCC_CORE is internally generated


  - **IO Voltage**


**–** 3.3V for all digital IOs (choosable by VCCIO Supply)


**–** 5V common mode analog input voltage range (1.25V ... 2.5V differential operating range)


  - **Clock Frequency**


**–** 25 MHz (from external oscillator)


  - **Packages**


**–** QFN76


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 9 / 153

## **3 FOC Basics**


This section gives a short introduction into some basics of Field Oriented Control (FOC) of electric motors.


**3.1** **Why FOC?**


The Field Oriented Control (FOC), alternatively named Vector Control (VC), is a method for the most energyefficient way of turning an electric motor.


**3.2** **What is FOC?**


The Field Oriented Control was independently developed by K. Hasse, TU Darmstadt, 1968, and by Felix
Blaschke, TU Braunschweig, 1973. The FOC is a current regulation scheme for electro motors that takes
the orientation of the magnetic field and the position of the rotor of the motor into account, regulating
the strength in such way that the motor gives that amount of torque that is requested as target torque.
The FOC maximizes active power and minimizes idle power - that finally results in power dissipation - by
intelligent closed-loop control illustrated by figure 1.


_Figure 1:_ _Illustration of the FOC basic principle by cartoon:_ _Maximize active power and minimize idle power_
_and power dissipation by intelligent closed-loop control._


**3.3** **Why FOC as pure Hardware Solution?**


The initial setup of the FOC is usually very time consuming and complex, although source code is freely
available for various processors. This is because the FOC has many degrees of freedom that all need to
fit together in a chain in order to work.


The hardware FOC as an existing standard building block drastically reduces the effort in system setup.
With that off the shelf building block, the starting point of FOC is the setup of the parameters for the FOC.
Setting up and implement the FOC itself and building and programming required interface blocks is no
longer necessary. The real parallel processing of hardware blocks de-couples the higher lever application
software from high speed real-time tasks and simplifies the development of application software. With
the TMC4671, the user is free to use its qualified CPU together with its qualified tool chain, freeing the
user from fighting with processer-specific challenges concerning interrupt handling and direct memory
access. There is no need for a dedicated tool chain to access the TMC4671 registers and to operate it just SPI (or UART) communication needs to be enabled for any given CPU.


The hardware integration of the FOC drastically reduces the number of required components and reduces
the required PCB space. This is in contrast to classical FOC servos formed by motor block and separate


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-8-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 10 / 153


controller box wired with motor cable and encoder cable. The high integration of FOC, together with
velocity controller and position controller, enables the FOC as a standard peripheral component that
transforms digital information into physical motion. Compact size together with high performance and
energy efficiency especially for battery powered mobile systems are enabling factors when embedded
goes autonomous.


**3.4** **How does FOC work?**


Two force components act on the rotor of an electric motor. One component is just pulling in radial
direction (ID) where the other component is applying torque by pulling tangentially (IQ). The ideal FOC
performs a closed loop current control that results in a pure torque generating current IQ – without direct
current ID.


_Figure 2:_ _FOC optimizes torque by closed loop control while maximizing IQ and minimizing ID to 0_


From top point of view, the FOC for 3-phase motors uses three phase currents of the stator interpreted
as a current vector (Iu; Iv; Iw) and calculates three voltages interpreted as a voltage vector (Uu; Uv; Uw)
taking the orientation of the rotor into account in a way that only a torque generating current IQ results.


From top point of view, the FOC for 2-phase motors uses two phase currents of the stator interpreted
as a current vector (Ix; Iy) and calculates two voltages interpreted as a voltage vector (Ux; Uy) taking the
orientation of the rotor into account in a way that only a torque generating current IQ results.


To do so, the knowledge of some static parameters (number of pole pairs of the motor, number of pulses
per revolution of an used encoder, orientation of encoder relative to magnetic axis of the rotor, count
direction of the encoder) is required together with some dynamic parameters (phase currents, orientation
of the rotor).


The adjustment of P parameter P and I parameters of two PI controllers for closed loop control of the
phase currents depends on electrical parameters of the motor (resistance, inductance, back EMF constant
of the motor that is also the torque constant of the motor, supply voltage).


**3.5** **What is Required for FOC?**


The FOC needs to know the direction of the magnetic axis of the rotor of the motor in reference to the
magnetic axis of the stator of the motor. The magnetic flux of the stator is calculated from the currents
through the phases of the motor. The magnetic flux of the rotor is fixed to the rotor and thereby determined by an encoder device.


For the FOC, the user needs to measure the currents through the coils of the stator and the angle of the
rotor. The measured angle of the rotor needs to be adjusted to the magnetic axes.


The challenge of the FOC is the high number of degrees of freedom in all parameters.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-9-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 11 / 153


**3.5.1** **Coordinate Transformations - Clarke, Park, iClarke, iPark**


The FOC requires different coordinate transformations formulated as a set of matrix multiplications. These
are the Clarke Transformation (Clarke), the Park Transformation (Park), the inverse Park Transformation
(iPark) and the inverse Clarke Transformation (iClarke). The Park transformation is also known as DQ
transformation, whereas the Clarke transformation is known as _αβ_ transformation.


The TMC4671 takes care of the required transformations so the user no longer has to fight with implementation details of these transformations.


**3.5.2** **Measurement of Stator Coil Currents**


The measurement of the stator coil currents is required for the FOC to calculate a magnetic axis out of
the stator field caused by the currents flowing through the stator coils.


Coil current stands for motor torque in context of FOC. This is because motor torque is proportional
to motor current, defined by the torque constant of a motor. In addition, the torque depends on the
orientation of the rotor of the motor relative to the magnetic field produced by the current through the
coils of the stator of the motor.


**3.5.3** **Stator Coil Currents I_U, I_V, I_W and Association to Terminal Voltages U_U, U_V, U_W**


The correct association between stator terminal voltages U_U, U_V, U_W and stator coil currents I_U, I_V,
I_W is essential for the FOC. In addition to the association, the signs of each current channel need to
fit. Signs of the current can be adapted numerically by the ADC scaler. The mapping of ADC channels is
programmable via configuration registers for the ADC selector. Initial setup is supported by the integrated
open loop encoder block, that can support the user to turn a motor open loop.


**3.5.3.1** **Chain of Gains for ADC Raw Values**
An ADC raw value is a result of a chain of gains that determine it. A coil current I_SENSE flowing through a
sense resistor causes a voltage difference according to Ohm’s law. The resulting ADC raw value is a result
of the analog signal path according to


ADC_RAW = (I_SENSE _∗_ ADC_GAIN) + ADC_OFFSET _._ (1)


The ADC_GAIN is a result of a chain of gains with individual signs. The sign of the ADC_GAIN is positive
or negative, depending on the association of connections between sense amplifier inputs and the sense
resistor terminals. The ADC_OFFSET is the result of electrical offsets of the phase current measurement
signal path. For the TMC4671, the maximum ADC_RAW value ADC_RAW_MAX = (2 [16] _−_ 1) and the minimum
ADC raw value is ADC_RAW_MIN = 0.


ADC_GAIN = ( I_SENSE_MAX _∗_ R_SENSE )



_∗_ SENSE_AMPLIFIER_GAIN


_∗_ ( ADC_RAW_MAX _/_ ADC_U_MAX )



(2)



For the FOC, the ADC_RAW is scaled by the ADC scaler of the TMC4671 together with subtraction of offset
to compensate it. Internally, the TMC4671 FOC engine calculates with s16 values. Thus, the ADC scaling
needs to be chosen so that the measured currents fit into the s16 range. With the ADC scaler, the user
can choose a scaling with physical units like [ _mA_ ].


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 12 / 153


**3.5.4** **IgainADC** [ **A/LSB** ] **- ADC Integer Current Value to Real World Unit**


Together with ADC_I0_SCALE and ADC_I0_OFFSET and ADC_I1_SCALE and ADC_I1_OFFSET, measured ADC
currents represented as 16 bit signed interger numbers (s16) represent real world currents. Multiplication
of integer current value with gain scaling factor in unit Ampere per LSB (Low Significant Bit) gives the real
world value of current in unit Ampere.


_I_ 0[ _A_ ] = IgainADC[ _A/LSB_ ] _∗_ ADC_I0

(3)
_I_ 1[ _A_ ] = IgainADC[ _A/LSB_ ] _∗_ ADC_I1


Different scalings between two associated current ADC channels can be trimmed by programing ADC_I0_SCALE
and ADC_I1_SCALE. The IgainADC[A/LSB] needs to be determined from ADC gain factors, ADC reference
voltage selection, and actual ADC scaling factor settings.


**3.5.5** **UgainADC** [ **V/LSB** ] **- ADC Integer Voltage Value to Real World Unit**


Measured ADC voltages represented as 16 bit signed interger numbers (s16) represent real world voltages.
Multiplication of integer voltage value with gain scaling factor in unit Volt per LSB (Low Significant Bit) gives
the real world value of voltage in unit Volt.


_U_ [ _V_ ] = UgainADC[ _V/LSB_ ] _∗_ ADC_U (4)


The UgainADC[V/LSB] needs to be determined from ADC gain factors, actual ADC gains, and ADC reference
voltage settings.


**3.5.6** **Measurement of Rotor Angle**


Determination of the rotor angle is either done by sensors (digital encoder, analog encoder, digital Hall
sensors, analog Hall sensors) or sensorless by a reconstruction of the rotor angle. Currently, there are no
sensorless methods available for FOC that work in a general purpose way as a sensor down to velocity
zero.


The TMC4671 does not support sensorless FOC.


**3.5.7** **Measured Rotor Angle vs.** **Magnetic Axis of Rotor vs.** **Magnetic Axis of Stator**


The rotor angle, measured by an encoder, needs to be adjusted to the magnetic axis of the rotor. This
is because an incremental encoder has an arbitrary orientation relative to the magnetic axis of the rotor,
and the rotor has an arbitrary orientation to magnetic axis of the stator.


The direction of counting depends on the encoder, its mounting, and wiring and polarities of encoder
signals and motor type. So, the direction of encoder counting is programmable for comfortable definition
for a given combination of motor and encoder.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 13 / 153


**3.5.7.1** **Direction of Motion - Magnetic Field vs.** **Position Sensor**


For FOC it is essential, that the direction of revolution of the magnetic field is compatible with the direction of motion of the rotor position reconstructed from encoder signals: For revolution of magnetic field
with positive direction, the decoder position needs to turn into the same positive direction. For revolution of magnetic field with negative direction, the decoder position needs to turn into the same negative
direction.


With an absolute encoder, once adjusted to the relative orientation of the rotor and to the relative orientation of the stator, one could start the FOC without initialization of the relative orientations.


**3.5.7.2** **Bang-Bang Initialization of the Encoder**


A Bang-Bang initialization is an initialization where the motor is forced with high current into a specific
position. For Bang-Bang initialization, the user sets a current into direction D that is strong enough to
move the rotor into the desired direction. Other initialization methods ramp up the current smoothly
and adjust the current vector to rotor movement detected by the encoder.


**3.5.7.3** **Encoder Initialization using Hall Sensors**


The encoder can be initialized using digital Hall sensor signals. Digital Hall sensor signals give absolute
positions within each electrical period with a resolution of sixty degrees. If the Hall sensor signals are
used to initialize the encoder position on the first change of a Hall sensor signal, an absolute reference
within the electrical period for commutation is given.


**3.5.7.4** **Minimum Movement Initialization of the Encoder**


For minimal movement initialization of the encoder, the user slowly increases a current into direction D
and adjusts an offset of the measured angle in a way that the rotor of the motor does not move during
initialization while the offset of the measured angle is determined.


**3.5.8** **Knowledge of Relevant Motor Parameters and Position Sensor (Encoder) Parameters**


**3.5.8.1** **Number of Pole Pairs of a Motor**


The number of pole pairs is an essential motor parameter. It defines the ratio between electrical revolutions and mechanical revolutions. For a motor with one pole pair, one mechanical revolution is equivalent
to one electrical revolution. For a motor with npp pole pairs, one mechanical revolution is equivalent to
npp electrical revolutions, with n = 1, 2, 3, 4, ....


Some define the number of poles NP instead of number of pole pairs NPP for a motor, which results in a
factor of two that might cause confusion. For the TMC4671, we use NPP number of pole pairs.


**3.5.8.2** **Number of Encoder Positions per Revolution**


For the encoder, the number of positions per revolution (PPR) is an essential parameter. The number of
positions per revolution is essential for the FOC.


Some encoder vendors give the number of lines per revolution (LPR) or just named line count (LC) as
encoder parameter. Line count and positions per revolution might differ by a factor of four. This is because of the quadrature encoding - A signal and B signal with phase shift - that give four positions per


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 14 / 153


line, enabling the determination of the direction of revolution. Some encoder vendors associate counts
per revolution (CPR) or pulses per revolution associated to PPR acronym.


The TMC4671 uses Positions Per Revolution (PPR) as encoder parameter.


**3.5.9** **Proportional Integral (PI) Controllers for Closed Loop Current Control**


Last but not least, two PI controllers are required for the FOC. The TMC4671 is equipped with two PI
controllers - one for control of torque generating current I_Q and one to control current I_D to zero.


**3.5.10** **Pulse Width Modulation (PWM) and Space Vector Pulse Width Modulation (SVPWM)**


The PWM power stage is a must-have for energy efficient motor control. The PWM engine of the TMC4671
just needs a couple of parameters to set PWM frequency fPWM and switching pauses for both high side
switches tBBM_H and low side switches tBBM_L. Some control bits are for the programming of power
switch polarities for maximum flexibility in the selection in gate drivers for the power MOS-FETs. An additional control bit selects SVPWM on or off. The TMC4671 allows for change of PWM frequency by a single
parameter during operation.


With this, the TMC4671 is advanced compared to software solutions where PWM and SVPM configuration
of CPU internal peripherals normally needs settings of many parameters.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 15 / 153


**3.5.11** **Orientations, Models of Motors, and Coordinate Transformations**


The orientation of magnetic axes (U, V, W for FOC3 resp. X, Y for FOC2) is essential for the FOC together
with the relative orientation of the rotor. Here, the rotor is modeled by a bar magnet with one pole pair
(n_pole_pairs = 1) with magnetic axis in north-south direction.
The actual magnetic axis of the stator - formed by the motor coils - is determined by measurement of the
coil currents.
The actual magnetic axis of the rotor is determined by incremental encoder or by Hall sensors. Incremental encoders need an initialization of orientation, where Hall sensors give an absolute orientation, but with
low resolution. A combination of Hall sensor and incremental encoder is useful for start-up initialization.


_Figure 3:_ _Orientations UVW (FOC3) and XY (FOC2)_


_Figure 4:_ _Compass Motor Model w/ 3 Phases UVW (FOC3) and Compass Motor Model w/ 2 Phases (FOC2)_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-14-0.png)

![](images/TMC4671-LA_datasheet_rev2.08.pdf-14-1.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 16 / 153

## **4 Functional Description**


The TMC4671 is a fully integrated controller for field-oriented control (FOC) of either one 3-phase brushless motor (FOC3) or one 2-phase stepper motor (FOC2) or, as well as 1-phase DC motor or voice coil
actuator (FOC1). Containing the complete control loop core architecture (position, velocity, torque), the
TMC4671 also has the required peripheral interfaces for communication with an application controller,
for feedback (digital encoder, analog interpolator encoder, digital Hall with interpolator, analog inputs for
current and voltage measurement), and helpful additional IOs. The TMC4671 supports highest control
loop speed and PWM frequencies.


The TMC4671 is the building block which takes care of all real-time critical tasks of field-oriented motor
control. It decouples the real-time field-oriented motor control and its real-time sub-tasks such as current
measurement, real-time sensor signal processing, and real-time PWM signal generation from the user
application layer as outlined by figure 5.


_Figure 5:_ _Hardware FOC Application Diagram_


**4.1** **Functional Blocks**


The Application interface, register bank, ADC engine, encoder engine, FOC torque PI controller, velocity PI
controller, position P controller, and PWM engine make up the TMC4671.


_Figure 6:_ _Hardware FOC Block Diagram_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-15-0.png)

![](images/TMC4671-LA_datasheet_rev2.08.pdf-15-1.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 17 / 153


The ADC engine interfaces the integrated ADC channels and maps raw ADC values to signed 16 bit (s16)
values for the inner FOC current control loop based on programmable offset and scaling factors. The FOC
torque PI controller forms the inner base component including required transformations (Clark, Park,
inverse Park, inverse Clark). All functional blocks are pure hardware.


**4.2** **Communication Interfaces**


The TMC4671 is equipped with an SPI slave user interface for access to all registers of the TMC4671. The
SPI slave user interface is the main application interface.
An additional UART interface is intended for system setup. With that interface, the user can access all
registers of the TMC4671 in parallel to the application accessing them via the SPI communication interface

- via the user’s firmware or via evaluation boards and the TMCL-IDE. The data format of the UART interface
is similar to the SPI communication interface - SPI 40 bit datagrams sent to the TMC4671 and SPI 40 bit
datagrams received by the MCU vs. five bytes sent via UART and five bytes received via UART. Sending
a burst of different real-time data for visualization and analysis via the TMCL-IDE can be triggered using
special datagrams. With that, the user can set up an embedded application together with the TMCL-IDE,
without having to write a complex set of visualization and analysis functions. The user can focus on its
application.
The TMC4671 is also equipped with an additional SPI master interface (TRINAMIC Real-time Monitoring
Interface, DBGSPI) for high-speed visualization of real-time data together with the TMCL-IDE.


**4.2.1** **SPI Slave User Interface**


The SPI of the TMC4671 for the user application has an easy command and control structure. The TMC4671
user SPI acts as a slave. The SPI datagram length is 40 bit with a clock rate up to 8 MHz (1 MHz for the
TMC4671-ES).


   - The MSB (bit#39) is sent first. The LSB (bit#0) is sent last.


   - The MSB (bit#39) is the WRITE_notREAD (WRnRD) bit.


   - The bits (bit#39 to bit#32) are the address bits (ADDR).


   - Bits (bit#31) to (bit#0) are 32 data bits.


The SPI of the TMC4671 immediately responses within the actual SPI datagram on read and write for
ease-of-use communication and uses SPI mode 3 with CPOL = 1 and CPHA = 1.


_Figure 7:_ _SPI Datagram Structure_


A simple SPI datagram example:


0x8100000000 // 1st write 0x00000000 into address 0x01 (CHIPINFO_ADDR)
0x0000000000 // 2nd read register 0x00 (CHIPINFO_DATA), returns 0x34363731 <=> ACSII "4671"


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-16-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 18 / 153


_Figure 8:_ _SPI Timing_



![](images/TMC4671-LA_datasheet_rev2.08.pdf-17-0.png)





|SPI Interface Timing|Characteristics, fCLK = 25MHz|Col3|Col4|Col5|Col6|
|---|---|---|---|---|---|
|**Parameter**|**Symbol**|**Min**|**Typ**|**Max**|**Unit**|
|SCK valid before or after change of nSCS|_tCC_|62.5|||ns|
|nSCS high time|_tCSH_|62.5|||ns|
|nSCS low time|_tCSL_|62.5|||ns|
|SCK high time|_tCH_|62.5|||ns|
|SCK low time|_tCL_|62.5|||ns|
|tSCKpause time after read address byte|_tSCKpause_|500|||ns|
|SCK frequency with tSCKpause after write ad-<br>dress|_fSCKpauseW R_|||8|MHz|
|SCK frequency for write access without pause|_fSCKwr_|||8|MHz|
|SCK frequency with tSCKpause after read address|_fSCKpauseRD_|||8|MHz|
|SCK frequency for read access without tSCKpause|_fSCKrd_|||2|MHz|
|MOSI setup time before rising edge of SCK|_tDU_|62.5|||ns|
|MOSI hold time after falling edge of SCK|_tDH_|62.5|||ns|
|MISO data valid time after falling edge of SCK|_tDO_||20||ns|


_Table 2:_ _SPI Timing Parameter_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 19 / 153


_**Info**_ SPI write access can be performed up to 8 MHz SPI clock frequency. SPI read
access can be performed up to 8 MHz SPI clock frequency if a pause of at least
500 ns is inserted after transfer of the address byte of the SPI datagram. Without
a pause of 500 ns after address byte, SPI read access can be performed up to 2
MHz SPI clock frequency.


_Figure 9:_ _SPI Timing of Write Access without pause with fSCK up to 8MHz_


_Figure 10:_ _SPI Timing of Read Access with pause (tPAUSE) of 500 ns with fSCK up to 8MHz._


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-18-0.png)

![](images/TMC4671-LA_datasheet_rev2.08.pdf-18-1.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 20 / 153


**4.2.2** **TRINAMIC Real-Time Monitoring Interface (SPI Master)**


The TRINAMIC Real-Time Monitoring Interface (RTMI, SPI Master) is an additional fast interface enabling
real-time identification of motor and system parameters. The user can check configuration and access
registers in the TMC4671 via the TMCL-IDE with its build-in configuration wizards for FOC setup in parallel
to the user firmware. TRINAMIC provides a Monitoring Adapter to access the interface, which connects
easily to a single 10 pin high density connector (Type: Hirose DF20F-10DP-1V) on the user’s PCB or on the
evaluation board. If the interface is not needed, pins can be left open or can be used as GPIOs according
to the specification. The connector needs to be placed near the TMC4671. Its assignment is pictured in
figure 11.


_Figure 11:_ _Connector for Real-Time Monitoring Interface (Connector Type:_ _Hirose DF20F-10DP-1V)_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-19-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 21 / 153


**4.2.3** **UART Interface**


The UART interface is a simple three pin (GND, RxD, TxD) 3.3V UART interface with up to 3 Mbit/s transfer
speed with one start bit, eight data bits, one stop bit, and no parity bits (1N8). The default speed is 9600
bps. Other supported speeds are 115200 bps, 921600 bps, and 3000000 bps. The speed must be changed
manually in register 0x79 UART_BPS.


_**Info**_ The baudrates must be entered as hexadecimal numbers. Table 3 lists the register value and its corresponding baudrate.

|Value of register 0x79|selected baudrate|
|---|---|
|0x00009600|9600 bps|
|0x00115200|115200 bps|
|0x00921600|921600 bps|
|0x03000000|3000000 bps|



_Table 3:_ _Possible baudrates and corresponding values for register 0x79_


With an 3.3V-UART-to-USB adapter cable (e.g. FTDI TTL-232R-RPi), the user can use the full maximum data
rate. The UART port enables In-System-Setup-Support by multiple-ported register access.


An UART datagram consists of five bytes - similar to the datagrams of the SPI. In contrast to SPI, the UART
interface has a time out feature. So, the five bytes of a UART datagram need to be send within one second.
A pause of sending more than one second causes a time out and sets the UART protocol handler back
into IDLE state. In other words, waiting for more than one second in sending via UART ensures that the
UART protocol handler is in IDLE state.


A simple UART example (similar to the simple SPI example):


0x81 0x00 0x00 0x00 0x00 // 1st write 0x00000000 into address 0x01 (CHIPINFO_ADDR)
0x00 0x00 0x00 0x00 0x00 // 2nd read register 0x00 (CHIPINFO_DATA), returns 0x34363731


Why UART Interface? It might become necessary during the system setup phase to simply access some internal registers without disturbing the application, without changing the actual user application software,
and without adding additional debugging code that might disturb the application software itself. The
UART enables this supporting function. In addition, it also enables easy access for monitoring purposes
with its very simple and direct five byte protocol. The UART interface is available to write periodically positions into the TMC4671 via an external CPU used as a protocol translator to enable absolute encoders
for the TMC4671.


_**Info**_ The UART-write response of the TMC4671 depicted in figure 13 does not contain
any useful information. It is only used to signal that the IC has received and
processed the write datagram sent by the master.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 22 / 153


_Figure 12:_ _UART Read Datagram (TMC4671 register read via UART)_


_Figure 13:_ _UART Write Datagram (TMC4671 register write via UART)_


**4.2.4** **Step/Direction Interface**


The user can manipulate the target position via the step direction interface. It can be enabled by setting
the STEP_WIDTH (s32) register to a proper step width. The power-on default value of STEP_WIDTH is 0
that causes position target update with 0 step width that is no stepping. With STEP_WIDTH _̸_ = 0 each step
pulse on STEP input causes incrementing or decrementing of target position depending on polarity of DIR
input. For positive STEP_WIDTH, DIR = 0 causes incrementing and the DIR = 1 causes decrementing of the
target position. For negative STEP_WIDTH, DIR = 0 causes decrementing and DIR = 1 causes incrementing
of the target position. This is because the STEP_WIDTH is represented as a signed number.


**4.2.5** **Single Pin Interface**


The TMC4671 can be operated in Motion Modes in which the main target value is calculated from either
a PWM input signal on PIN PWM_I or by analog input to AGPI_A.

|Number|Motion Mode|Using PWM_I or AGPI_A|
|---|---|---|
|0|Stopped Mode|no|
|1|Torque Mode|no|
|2|Velocity Mode|no|
|3|Position Mode|no|
|4|PRBS Flux Mode|no|
|5|PRBS Torque Mode|no|
|6|PRBS Velocity Mode|no|



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-21-0.png)

![](images/TMC4671-LA_datasheet_rev2.08.pdf-21-1.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 23 / 153

|Number|Motion Mode|Using PWM_I or AGPI_A|
|---|---|---|
|7|PRBS Position Mode|no|
|8|UQ UD Ext Mode|no|
|9|(reserved)|no|
|10|AGPI_A Torque Mode|AGPI_A|
|11|AGPI_A Velocity Mode|AGPI_A|
|12|AGPI_A Position Mode|AGPI_A|
|13|PWM_I Torque Mode|PWM_I|
|14|PWM_I Velocity Mode|PWM_I|
|15|PWM_I Position Mode|PWM_I|



_Table 4:_ _Single Pin Interface Motion Modes_


Registers SINGLE_PIN_IF_OFFSET and SINGLE_PIN_IF_SCALE can be used to scale the value to desired
range. In case of the PWM input, a permanent low input signal or permanent high signal is treated as
input error and chosen target value is set to zero.
Register SINGLE_PIN_IF_CFG configures the length of a digital filter for the PWM_I signal. Spikes on the
signal can be thereby suppressed. Bit 0 in register SINGLE_PIN_IF_STATUS is set high when PWM_I is
constant low, Bit 1 is set high when the PWM_I is constant high. Writing to this register resets these flags.
Maximum PWM period of the PWM signal must be 65000 x 40 ns. The calculation of the normalized duty
cycle is started on the rising edge of PWM_I. The PWM frequency needs to be constant as big variations
(tolerance of 4 us in PWM period) in the PWM frequency are treated as error.
A duty cycle of 50% equals an input value of 32768. With the offset and scaling factors it can be mapped
to desired range.


**4.2.6** **GPIO Interface**


The TMC4671 has eight GPIO-pins that are arranged in group A (GPIO 0 to 3) and group B (GPIO 4 to 7).
These pins can be configured using bits 0 to 6 of the register GPIO_dsADCI_CONFIG (0x7B). The configurations include RTMI, GPI or GPO as well as clock signals, in and out, for external delta sigma modulators.
Groups A and B can individually be configured as in or outputs. Single pins within these groups can not be
individually configured. Bits 16 to 19 set the GPO values for group A and bits 20 to 23 set the GPO values
for group B. If configured as GPIs bits 24 to 27 display the input on group A whereas bits 28 to 31 display
the input on the group B GPIs.

|GPIO_dsADCI_CONFIG (bits 6 to 0)|Configured as|group A|group B|
|---|---|---|---|
|xxxxxx0b|RTMI|0: Z<br>1: Z<br>2: Z<br>3: /CS|4: SCK<br>5: MOSI<br>6: MISO<br>7: TRG|
|xx11001b|GPIO|GPO|GPO|
|xx00001b|GPIO|GPI|GPI|
|xx01001b|GPIO|GPO|GPI|
|xx10001b|GPIO|GPI|GPO|



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 24 / 153

|GPIO_dsADCI_CONFIG (bits 6 to 0)|Configured as|group A|group B|
|---|---|---|---|
|11xx111b|Delta Sigma ADC|MCLK_out|MCLK_out|
|11xx111b|Delta Sigma ADC|0: ADCI0<br>1: ADCI1<br>2: ADCVM<br>3: ADCAGPI_A|4: ADCAGPI_B<br>5: AENC_UX<br>6: AENC_VN<br>7: AENC_WY|
|00xx111b|Delta Sigma ADC|MCLK_in|MCLK_in|
|00xx111b|Delta Sigma ADC|0: ADCI0<br>1: ADCI1<br>2: ADCVM<br>3: ADCAGPI_A|4: ADCAGPI_B<br>5: AENC_UX<br>6: AENC_VN<br>7: AENC_WY|



_Table 5:_ _GPIO Configuration Overview with ’x’ as don’t care_


_**Info**_ When the RTMI-option is selected it is not possible to use the GPIOs and the other
way around. On default the RTMI-Mode is chosen and the unused GPIOs 0,1 and
2 are configured as inputs on high impedance Z.
In addition, the only possible Delta Sigma ADC configurations are the ones listed
in table 5.


**4.3** **Numerical Representation, Electrical Angle, Mechanical Angle, and Pole Pairs**


The TMC4671 uses different numerical representations for different parameters, measured values, and
interim results. The terms electrical angle PHI_E, mechanical angle PHI_M, and number of pole pairs
(N_POLE_PAIRS) of the motor are important for setup of FOC. This section describes the different numerical representations of parameters and terms.


**4.3.1** **Numerical Representation**


The TMC4671 uses signed and unsigned values of different lengths and fixed point representations for
parameters that require a non-integer granularity.






|Symbol|Description|Min|Max|
|---|---|---|---|
|u16|unsigned 16 bit value|0|65535|
|s16|signed 16 bit values, 2’th complement|-32767|32767|
|u32|unsigned 32 bit value|0|232 = 4294967296|
|s32|signed 32 bit values, 2’th complement|-2147483647|231 - 1 = 2147483647|
|q8.8|signed ﬁx point value with 8 bit integer part<br>and 8 bit fractional part|-32767/256|32767/256|
|q4.12|signed ﬁx point value with 4 bit integer part<br>and 12 bit fractional part|-32767/4096|32767/4096|



_Table 6:_ _Numerical Representations_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 25 / 153


_**Info**_ Two’s complement of n bit is _−_ 2 [(] _[n][−]_ [1)] ... _−_ 2 [(] _[n][−]_ [1)] _−_ 1. To avoid unwanted overflow,
the range is clipped to _−_ 2 [(] _[n][−]_ [1)] + 1 ... _−_ 2 [(] _[n][−]_ [1)] _−_ 1.


Because the zero is interpreted as a positive number for 2’th complement representation of integer n bit
number, the smallest negative number is _−_ 2 [(] _[n][−]_ [1)] where the largest positive number is 2 [(] _[n][−]_ [1)] _−_ 1. Using
the smallest negative number _−_ 2 [(] _[n][−]_ [1)] might cause critical underflow or overflow. Internal clipping takes
this into account by mapping _−_ 2 [(] _[n][−]_ [1)] to _−_ 2 [(] _[n][−]_ [1)] + 1.

|Hexadecimal Value|u16|s16|q8.8|q4.12|
|---|---|---|---|---|
|0x0000h|0|0|0.0|0.0|
|0x0001h|1|1|1 / 256|1 / 4096|
|0x0002h|2|2|2 / 256|2 / 4096|
|0x0080h|128|128|0.5|0.03125|
|0x0100h|256|256|1.0|0.0625|
|0x0200h|512|512|2.0|0.125|
|0x3FFFh|16383|16383|16383 / 256|16383 / 4096|
|0x5A81h|23169|23169|23169 / 256|23169 / 4096|
|0x7FFFh|32767|32767|32767 / 256|32767 / 4096|
|0x8000h|32768|-32768|-32768 / 256|-32768 / 4096|
|0x8001h|32769|-32767|-32767 / 256|-32767 / 4096|
|0x8002h|32770|-32766|-32766 / 256|-32766 / 4096|
|0xC001h|49153|-16383|-16383 / 256|-16383 / 4096|
|0xFFFEh|65534|-2|-2 / 256|-2 / 4096|
|0xFFFFh|65535|-1|-1 / 256|-1 / 4096|



_Table 7:_ _Examples of u16, s16, q8.8, q4.12_


The q8.8 and q4.12 are used for P and I parameters which are positive numbers. Note that q8.8 and q4.12
are used as signed numbers. This is because theses values are multiplied with signed error values resp.
error integral values.


**4.3.2** **N_POLE_PAIRS, PHI_E, PHI_M**


The parameter N_POLE_PAIRS defines the factor between electrical angle PHI_E and mechanical angle
PHI_M of a motor (pls. refer figure 14).
A motor with one (1) pole pair turns once for each electrical period. A motor with two (2) pole pairs turns
once for every two electrical periods. A motor with three (3) pole pairs turns once for every three electrical
periods. A motor with four pole (4) pairs turns once for every four electrical periods.


The electrical angle PHI_E is relevant for the commutation of the motor. It is relevant for the torque control
of the inner FOC loop.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 26 / 153


PHI_E = PHI_M _·_ N_POLE_PAIRS (5)


The mechanical angle PHI_M is primarily relevant for velocity control and for positioning. This is because
one wants to control the motor speed in terms of mechanical turns and not in terms of electrical turns.


PHI_M = PHI_E _/_ N_POLE_PAIRS (6)


Different encoders give different kinds of position angles. Digital Hall sensors normally give the electrical
position PHI_E that can be used for commutation. Analog encoders give - depending on their resolution angles that have to be scaled first to mechanical angles PHI_M and to electrical angles PHI_E for commutation.


_Figure 14:_ _N_POLE_PAIRS - Number of Pole Pairs (Number of Poles)_


**4.3.3** **Numerical Representation of Angles PHI**


Electrical angles and mechanical angles are represented as 16 bit integer values. One full revolution of
360 deg is equivalent to 2 [16] = 65536 steps. Any position coming from a sensor is mapped to this integer
range. Adding an offset of PHI_OFFSET causes a rotation of an angle PHI_OFFSET _/_ 2 [16] . Subtraction of an
offset causes a rotation of an angle PHI_OFFSET in opposite direction.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-25-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 27 / 153


_Figure 15:_ _Integer Representation of Angles as 16 Bit signed (s16) resp._ _16 Bit unsigned (u16)_

|Hexadecimal Value|u16|s16|PHI[°]<br>u16|PHI[°]<br>s16|
|---|---|---|---|---|
|0x0000h|0|0|0.0|0.0|
|0x1555h|5461|5461|30.0|30.0|
|0x2AAAh|10922|10922|60.0|60.0|
|0x4000h|16384|16384|90.0|90.0|
|0x5555h|21845|21845|120.0|120.0|
|0x6AAAh|27306|27768|150.0|150.0|
|0x8000h|32768|-32768|180.0|-180.0|
|0x9555h|38229|-27307|210.0|-150.0|
|0xAAAAh|43690|-21846|240.0|-120.0|
|0xC000h|49152|-16384|270.0|-90.0|
|0xD555h|54613|-10923|300.0|-60.0|
|0xEAAAh|60074|-5462|330.0|-30.0|



_Table 8:_ _Examples of u16, s16, q8.8_


The option of adding an offset is for adjustment of angle shift between the motor and stator and the rotor
and encoder. Finally, the relative orientations between the motor and stator and the rotor and encoder
can be adjusted by just one offset. Alternatively, one can set the counter position of an incremental
encoder to zero on initial position. For absolute encoders, one needs to use the offset to set an initial
position.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-26-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 28 / 153


**4.4** **ADC Engine**


The ADC engine controls the sampling, selection, scaling and offset correction of different available ADC
channels. Two ADC channels are for phase current measurement, three ADC channels are for analog Hall
signals or for analog sin-cos-encoder, one ADC channel is for optional measurement of the motor spupply
voltage, two additional ADC channals are general purpose where one general purpose analog input can
be used as analog target value by the single pin interface.


**4.4.1** **ADC current sensing channels ADC_I1 and ADC_I0**


The ADC channels (ADC_I0_POS, ADC_I0_NEG, ADC_I1_POS, ADC_I1_NEG) are for current sensing in differential input configuration. In differential configuration, the ADC_I0_POS and ADC_I0_POS are the inputs
for the sense amplifier output signals where ADC_I1_NEG and ADC_I0_NEG) are for the zero current sensing reference of the sense amplifiers. In single ended configuration, the ADC_I0_POS and ADC_I0_POS
are the inputs for the sense amplifier output signals where ADC_I1_NEG and ADC_I0_NEG) are internally
connected to ground. The third current channel ADC_I2 as required for three phase FOC is calculated
using Kirchhoff’s law ADC_I2 = - (ADC_I1 + ADC_I0).


_**Info**_ ADC_I0_POS, ADC_I0_NEG, ADC_I1_POS, ADC_I1_NEG are low voltage analog inputs and must not directly connected to in-line sense resistors. The TMC4671
requires external dfferential motor supply common mode range current sensing amplifiers for in-line current sensing.


**4.4.2** **ADC for analog Hall signals or analog sin-cos-encoders AENC_UX, AENC_VN, AENC_WY**


For analog Hall and for analog encoder, the ADC engine has three disserential input channles (AENC_UX_POS,
AENC_UX_NEG), (AENC_VN_POS, AENC_VN_NEG), and AENC_WY_POS, AENC_WY_NEG). The analog encoder
ADC inputs can be configured single ended (AENC_UX_POS, AENC_VN_POS, AENC_WY_POS) with negative
inputs (AENC_UX_NEG, AENC_VN_NEG, AENC_WY_NEG) internally connected to ground.


The three channels AENC_UX, AENC_VN, AENC_WY are for three phase analog sine (with +/-120° phase
shift) wave Hall signals. The Signals AENC_UX and AENC_WY are for two phase analog sine wave and cosin
wave Hall signals. The Signals AENC_UX and AENC_WY are for analog sin-cos-encoder. The AENC_VN is
for an optional zero pulse channel of sin-cos-encoders. The AENC_VN is available for read out by the
application software but it is not hardware handled by the TMC4671 for position zerroing.


For long analog signal lines, it might be necessary to use external differential receivers with twisted pair
line termination resistors to drive the single ended analog encoder inputs of the TMC4671.


**4.4.3** **ADC supply voltage measurement ADC_VM**


The ADC channel for measurement of supply voltage (ADC_VM) and is associated with the brake chopper.
The ADC_VM is available as raw value only without digital scaling. This is because it is not directly processed
by the FOC engine.


_**Info**_ ADC_VM must be scaled down electrically by voltage divider to the allowed voltage range, and might require additional supply voltage spike protection.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 29 / 153


**4.4.4** **ADC_VM for Brake Choppper**


The ADC_VM is available as input for optional brake chopper as raw value u16. The brake chopper thresholds have to be set as absolute u16 values to activate and deactivate the brake chopper output depending
on the ADC_VM value.


**4.4.5** **ADC EXT register option**


The user can write ADC values into the ADC_EXT registers of the register bank from external sources or
for evaluation purposes. These values can be selected as raw current ADC values by selection. ADC_EXT
registers are primarily intended for test purposes as optional inputs for external current measurement
sources.


**4.4.6** **ADC general purpose analog inputs AGPI_A and AGPI_B**


Two general purpose ADC channels are single-ended analog inputs (AGPI_A, AGPI_B). The general purpose analog ADC inputs AGPI_A and AGPI_B are available as raw values only without digital scaling. This is
because these values are not directly processed by the FOC engine. These general purpose analog inputs
(AGPI) are intended to monitor analog voltage signals representing MOSFET temperature or motor temperature. They are two additional ADC channels for the user. Optional, the AGPI_A is availabe as analog
target value signal.


**4.4.7** **ADC RAW values**


The sampled raw ADC values are available for read out by the user. This is important during the system
setup phase to determine offset and scaling factors.


**4.4.8** **ADC_SCALE and ADC_OFFSET**


The FOC engine expects offset corrected ADC current values scaled to the used 16 bit (s16) fixed point
representation. The integrated scaler and offset compensator maps raw ADC samples of current measurement channels to 16 bit two’s complement values (s16). While the offset is compensated by subtraction,
the offset is represented as an unsigned value. The scaling value is signed to compensate wrong measurement direction. The s16 scaled ADC values are available for read out from the register (ADC_I1, ADC_I0)
resp. (AENC_UX, AENC_VN, AENC_WY) by the user.


_**Info**_ Wrong scaling factors (ADC_SCALE) or wrong offsets (ADC_OFFSET) might cause
damages when the FOC is active. Integrated hardware limiters allow protection especially in the setup phase when using careful limits.


**4.4.9** **ADC Gain Factors for Real World Values**


Each ADC channel of the TMC4671 has an individual gain factor determined by its associated chain of gain
factors and by digital scaling factors if available for an ADC channel. ADC register values are either 16 bit
unsigned vaulues (u16) or 16 bit signed vaules (s16). With gain factors one can calculate ADC values as
real world values if required.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 30 / 153


Gain factors IgainADC for ADC current values are typical in units [A/LSB] or [mA/LSB]. Gain factors UgainADC
for ADC voltage values are typical in units [V/LSB] or [mV/LSB].


ADCmeasuredCurrent[A] = IgainADC[A/LSB]        - ADC_CURRENT_S16 (7)


ADCmeasuredVoltage[V] = UgainADC[V/LSB]        - ADC_VOLTAGE_S16 (8)


ADCmeasuredVoltage[V] = UgainADC[V/LSB]        - ADC_VOLTAGE_U16 (9)


**4.4.10** **Internal Delta Sigma ADCs**


The TMC4671 is equipped with internal delta sigma ADCs for current measurement, supply voltage measurement, analog GPIs and analog encoder signal measurement. Delta sigma ADCs, as integrated within
the TMC4671, together with programmable digital filters are flexible in parameterizing concerning resolution vs. speed. The advantage of delta sigma ADCs is that the user can adjust measurement from lower
speed with higher resolution to higher speed with lower resolution. This fits with motor control application. Higher resolution is required for low speed signals, while lower resolution satisfies the needs for
high speed signals.


Due to high oversampling, the analog input front-end is easier to implement than for successive approximation register ADCs as anti aliasing filters can be chosen to a much higher cutoff frequency. The ADC
Engine processes all ADC channels in parallel hardware - avoiding phase shifts between the channels
compared to ADC channels integrated in MCUs.


**4.4.11** **Internal Delta Sigma ADC Input Stage Configuration**


ADC channels can be configured either as differential ended analog inputs (ADC_I0, ADC_I1, AENC_UX,
AENC_VN, AENC_WY) or as single ended analog inputs (ADC_VM, AGPI_A, AGPI_B). Additionally, the ADC
all channels can be set to fixed voltages (0V, VREF/4, VREF/2, 3*VREF/4) for calibrations purposes.

|STAGE_CFG(n+2:n)|CONFIGURATION|DESCRIPTION|COMMENT|
|---|---|---|---|
|0|INP vs. INN|diﬀerential mode|default conﬁguration|
|1|GND vs. INN|single ended negative INN vs. GND|(for test purposes only)|
|2|VDD/4|25% ADC reference voltage|calibration aid|
|3|3*VDD/4|75% ADC reference voltage|calibration aid|
|4|INP vs. GND|single ended mode INP vs. GND|(half voltage range, oﬀset)|
|5|VDD/2|50% ADC reference voltage|calibration aid|
|6|VDD/4|25% ADC reference voltage|(redundant conﬁguration)|
|7|3*VDD/4|75% ADC reference voltage|(redundant conﬁguration)|



_Table 9:_ _Delta Sigma (_ ∆Σ _) ADC Input Stage Configurations_


The three bit vector ADC_STAGES_CFG(n+2:n) is part of the DS_ANALOG_INPUT_STAGE_CFG(31:0) with
n = 0, 4, 8, 12, 16, 20, 24, 28 for the eigth delta sigma ADC channels. DS_ANALOG_INPUT_STAGE_CFG


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 31 / 153


configures the associated delta sigma ADC input stages according to table 17. For association of the bit
position (bit n+2 to bit n) refere register bank section 7.2.

|STAGE_CFG(n+2:n)|ADC channel|function|
|---|---|---|
|STAGE_CFG(2:0)|ADC_I0|sense voltage of current I0|
|STAGE_CFG(6:4)|ADC_I1|sense voltage of current I1|
|STAGE_CFG(9:8)|ADC_VM|down divided supply voltage|
|STAGE_CFG(10)|’1’|ﬁxed for ADC_VM (STAGE_CFG=4,5,6,7)|
|STAGE_CFG(13:12)|ADC_AGPI_A|general purpose analog input A|
|STAGE_CFG(14)|’1’|ﬁxed for ADC_AGPI_A (STAGE_CFG=4,5,6,7)|
|STAGE_CFG(17:16)|ADC_AGPI_B|general purpose analog input B|
|STAGE_CFG(18)|’1’|ﬁxed for ADC_AGPI_B (STAGE_CFG=4,5,6,7)|
|STAGE_CFG(22:20)|ADC_AENC_UX|analog Hall UX / analog encoder COS|
|STAGE_CFG(26:24)|ADC_AENC_VN|analog Hall V / analog encoder N|
|STAGE_CFG(30:28)|ADC_AENC_WY|analog Hall WY / analog encoder SIN|



_Table 10:_ _Delta Sigma (_ ∆Σ _) ADC Input Stage Configurations_


_Figure 16:_ _Input Voltage Ranges of internal Delta Sigma ADC Channels)_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-30-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 32 / 153


Figure 16 illustrates typical relation between input voltage and corresponding raw ADC output. For differential operation the input range between 25% and 75% corresponds to voltage values between 1.25V to
3.75V. This is the recommended operation area of the ADC. Below 25% and above 75% the ADC shows
significant non-linearity due to the Delta Sigma measurement principle.
In single ended operation the recommended input range starts at 0V and ends at 1.25V. Measurement
below GND might be distorted and is not recommended.


_**Info**_ Due to manufacturing tolerances calibration of offset and amplitude is always
recommended. Please also consider stability of the reference voltage.


**4.4.12** **External Delta Sigma ADCs**


The delta sigma front-end of the ADC engine supports external delta sigma modulators to enable isolated delta sigma modulators for the TMC4671. Additionally, the delta sigma front-end supports low-cost
comparators together with two resistors and one capacitor (R-C-R-CMP) forming first order delta sigma
modulators, as generic analog front-end for pure digital variants of the TMC4671 core.


**4.4.13** **ADC Group A and ADC Group B**


ADC channels of the TMC4671 are grouped into two groups, to enable different sample rates for two
groups of analog signals if needed. Running both ADC groups with same sampling frequency is recommended for almost all applications. It might be necessary to run its ADC channels of analog encoder
with a much higher frequency than the ADC channels for current measurement in case of using a high
resolution analog encoder.


**4.4.14** **Delta Sigma Configuration and Timing Configuration**


The delta sigma configuration is programmed via MCFG register that selects the mode (internal/external
delta sigma modulator with programmable MCLK; delta sigma modulator clock mode (MCLK output, MCLK
input, MCLK used as MDAC output with external R-C-R-CMP configuration); delta sigma modulator clock
and its polarity; and the polarity of the delta sigma modulator data signal MDAT).


_**Info**_ The power-on delta sigma configuration should fit with most applications when
using the intergated delta sigma ADCs of the TMC4671. Primarily, the default
delta sigma configuration needs to be adapted when using external delta sigma
modulators or to select differential ADC input configurations, or in case of enhanced sampling requirenment for high resolution analog encoders.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 33 / 153


_Figure 17:_ _Delta Sigma ADC Configurations dsADC_CONFIG (internal:_ _ANALOG vs._ _external:_ _MCLKO, MCLKI,_
_MDAC)_



![](images/TMC4671-LA_datasheet_rev2.08.pdf-32-0.png)




|dsADC_CONFIG|Description|NC_MCLKO_MCLKI_MDAC|VIN_MDAT|
|---|---|---|---|
|ANALOG|integrated internal ADC mode,<br>VIN_MDAT is analog input VIN|MCLK not connected (NC)|VIN (analog)|
|MCLKO|external<br>dsModulator<br>(e.g.<br>AD7403)<br>with<br>MCLK<br>input<br>driven by MCLKO|MCLK output|MDAT input|
|MCLKI|external<br>dsModulator<br>(e.g.<br>AD7400)<br>with<br>MCLK<br>output<br>that drives MCLKI|MCLK input|MDAT input|
|MDAC|external<br>dsModulator<br>(e.g.<br>LM339) realized by external<br>comparator CMP with two R<br>and one C|MDAC output (= MCLK out)|MDAT input for CMP|



_Table 11:_ _Delta Sigma ADC Configurations (figure 17), selected with dsADC_MCFG_A and dsADC_MCFG_B._


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 34 / 153

|register|function|
|---|---|
|dsADC_MCFG_B|delta sigma modulator conﬁguration MCFG (ANALOG, MCLKI, MCLKO, MDAC), group B|
|dsADC_MCFG_A|delta sigma modulator conﬁguration MCFG (ANALOG, MCLKI, MCLKO, MDAC), group A|
|dsADC_MCLK_B|delta sigma modulator clock MCLK, group B|
|dsADC_MCLK_A|delta sigma modulator clock MCLK, group A|
|dsADC_MDEC_B|delta sigma decimation parameter MDEC, group B|
|dsADC_MDEC_A|delta sigma decimation parameter MDEC, group A|



_Table 12:_ _Registers for Delta Sigma Configuration_


**4.4.14.1** **Timing Configuration MCLK**


When the programmable MCLK is selected, the MCLK_A and MCLK_B parameter registers define the programmable clock frequency fMCLK of the delta sigma modulator clock signal MCLK for delta sigma modulator group A and group B. For a given target delta sigma modulator frequency fMCLK, together with the
internal clock frequency fCLK = 100MHz, the MCLK frequency parameter is calculated by


MCLK = 2 [31] _·_ fMCLK[ _Hz_ ] _/_ fCLK[ _Hz_ ] (10)


Due to the 32 bit’s length of the MCLK frequency parameter, the resulting frequency fMCLK might differ
from the desired frequency fMCLK. The back calculation of the resulting frequency fMCLK for a calculated
MCLK parameter with 32 bit length is defined by


fMCLK[ _Hz_ ] = fCLK[ _Hz_ ] _·_ MCLK _/_ 2 [31] (11)


The precise programming of the MCLK frequency is primarily intended for external delta sigma modulators to meet given EMI requirements. With that, the user can programm frequencies fMCLK with a resolution better than 0.1 Hz. This advantage concerning EMI might cause trouble when using external delta
sigma modulators if they are sensitive to slight frequency alternating. This is not an issue when using external first-order delta sigma modulators based on R-C-R-CMP (e.g. LM339). But for external second-order
delta sigma modulators, it is recommended to configure the MCLK parameter for frequencies fMCLK with
kHz quantization (e.g. 10,001,000 Hz instead of 10,000,001 Hz).

|fMCLK_target|MCLK|fMCLK_resulting|comment|
|---|---|---|---|
|25 MHz|0x20000000|25 MHz|w/o fMCLK frequency jitter, recommended|
|20 MHz|0x19000000|20 MHz -468750 Hz|recommended for ext. ∆Σ modulator|
|20 MHz|0x19999999|20 MHz -0.03 Hz|might be critical for ext. ∆Σ modulator|
|12.5 MHz|0x10000000|12.5 MHz|w/o fMCLK frequency jitter, recommended|
|10 MHz|0x0CCCCCCC|10 MHz -0.04 Hz|might be critical for ext. ∆Σ modulator|
|10 MHz|0x0CC00000|10 MHz -39062.5 Hz|recommended for ext. ∆Σ modulator|



_Table 13:_ _Delta Sigma MCLK Configurations_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 35 / 153


**4.4.14.2** **Decimation Parameter MDEC**


The high oversampled single bit delta sigma data stream (MDAT) is digitally filtered by Sinc3 filters. To get
raw ADC data, the actual digitally filtered values need to be sampled periodically with a lower rate called
decimation ratio. The decimation is controlled by parameter MDEC_A for ADC group A and MDEC_B for
ADC group B. A new ADC_RAW value is available after MDEC delta sigma pulses of MCLK. As such, the
parameters MCLK and MDEC together define the sampling rate of the 16 bit ADC_RAW values.


The delta sigma modulator with Sinc3 filter works with best noise reduction performance when the length
of the step response time tSINC3 of the Sinc3 filter is equal to the length of the PWM period tPWM =
(PWM_MAXCNT+1) / fPWMCLK = ((PWM_MAXCNT+1) * 10 ns) of the period. The length of the step function
response of a Sinc3 filter is


tSINC3 = (3 _·_ (MDEC _−_ 1) + 1) _·_ tMCLK (12)


tPWM
MDECrecommended = 3 _·_ tMCLK _[−]_ [2] (13)

|fMCLK|tMCLK|MDEC25 (25 kHz, 40µs)|MDEC50 (50 kHz, 20µs)|MDEC100 (100 kHz, 10µs)|
|---|---|---|---|---|
|50 MHz|20 ns|665|331|165|
|25 MHz|40 ns|331|165|81|
|20 MHz|50 ns|265|131|65|
|12.5 MHz|80 ns|165|81|40|
|10 MHz|100 ns|131|65|31|



_Table 14:_ _Optimal Decimation Parameter MDEC (according to equation (13) for different PWM frequencies_
_fPWM (MDEC25 for fPWM=25kHz w/ PWM_MAXCNT=3999, MDEC50 for fPWM=50kHz w/_
_PWM_MAXCNT=1999, MDEC100 for fPWM=100kHz w/ PWM_MAXCNT=999)._


_**Info**_ MDEC parameter can be changed during operation. This enables adaptive
adjustment of performance with respect to resolution versus speed on demand.


For most applications, the power-on decimation setting of MDEC should
be sufficient.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 36 / 153


**4.4.15** **Internal Delta Sigma Modulators - Mapping of V_RAW to ADC_RAW**


Generally, delta sigma modulators work best for a typical input voltage range of 25% V_MAX ...75% V_MAX
(unsigned 0% ... 100%). For the integrated delta sigma modulators, this input voltage operation range is
recommended with V_MAX = 5V where V_MAX = 3.3V is possible. The table 15 defines the recommended
voltage ranges for both 5V and 3.3V analog supply voltages.

|V_SUPPLY[V]|(V_MIN[V])|V_MIN25%[V]|V_MAX50%[V]|V_MAX75%[V]|(V_MAX[V])|
|---|---|---|---|---|---|
|(3.3)|(0.0)|(0.825)|(1.65)|(2.75)|(3.3)|
|5.0|(0.0)|1.250|2.50|3.75|(5.0)|



_Table 15:_ _Recommended input voltage range from V_MIN25%[V] to V_MAX75%[V] for internal Delta Sigma_
_Modulators; V_SUPPLY[V] = 5V is recommended for the analog part of the TMC4671._



V_RAW =











V_MAX for V_IN _>_ V_MAX


(V_IN _−_ V_REF) for V_MIN _<_ (V_IN _−_ V_REF) _<_ V_MAX


V_MIN for V_IN _<_ V_MIN



(14)



The resulting raw ADC value is


ADC_RAW = (2 [16] _−_ 1) _·_ [V_RAW] for V_MIN25%[V] _<_ V_RAW _<_ V_MAX75%[V] _._ (15)

V_MAX


The idealized expression (equation 14) is valid for recommended voltage ranges (table 15) neglecting deviations in linearities. These deviations primarily depend on different impedance on the analog signal
path, but also on digital parameterization. Finally, the deviation is quantified in terms of resulting ADC
resolution. So, the Delta Sigma ADC engine maps the analog input voltages V_RAW = V_IN - V_REF of voltage range V_MIN < V_RAW < V_MAX to ADC_RAW values of range _{_ 0 _. . ._ (2 [16] ) _−_ 1 _} <_ = _> {_ 0 _. . ._ 65535 _} <_ = _>_
0x0000 _. . ._ 0xFFFF.

|Vmin[V]|Vref[V]|Vmax[V]|VIN[V]|DUTY[%]|ADC_RAW|
|---|---|---|---|---|---|
|0.0|2.5|5.0|(0.0)|(0%)|(0x0000)|
|0.0|2.5|5.0|1.0|25%|0x4000|
|0.0|2.5|5.0|2.5|50%|0x7ﬀf|
|0.0|2.5|5.0|3.75|75%|0xC000|
|0.0|2.5|5.0|(5.0)|(100%)|(0xﬀﬀ)|



_Table 16:_ _Delta Sigma input voltage mapping of internal Delta Sigma Modulators_


_**Info**_ For calibrating purposes, the input voltage of the delta sigma ADC inputs can be
programmed to fixed voltages (25%, 50%, 75% of analog supply voltage) via the
associated configuration register DS_ANALOG_INPUT_STAGE_CFG.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 37 / 153


**4.4.16** **External Delta Sigma Modulator Interface**


The TMC4671 is equipped with integrated digital filters for extraction of ADC raw values from delta sigma
data stream for both internal and external delta sigma modulators. The interface for external delta sigma
modulators is intended for external isolated sigma delta modulators, such as AD7401 (with MCLK input
driven by TMC4671), or AD7402 (with MCLK output to drive TMC4671). In addition, the external delta
sigma interface supports the use of simple comparator with a R-C-R network as external low cost delta
sigma modulators (R-C-R-CMP, e.g. LM339).


_**Info**_ When selecting the external delta sigma ADC Interface, the high-performance
Debug SPI Interface (RTMI) it not available in parallel due to pin sharing. The
UART is always available, but with less performance than the RTMI.


Each external delta sigma modulator channel (dsMOD) has two signals (pls. refer figure 17), one dedicated
input, and one programmable input/output. The configuration of the external delta sigma modulator
interface is defined by programming associated registers. When selecting external delta sigma ADC, the
associated analog ADC inputs are configured as digital inputs for the delta sigma signal data stream MDAT.


**4.4.16.1** **External Delta Sigma Modulator Interface - MDAC Configuration**


_Figure 18:_ ∆Σ _ADC Configuration - MDAC (Comparator-R-C-R as_ ∆Σ _-Modulator)_


In the MDAC delta sigma modulator, the delay of the comparator CMP determines the MCLK of the comparator modulator. A capacitor _CMCCMP_ within a range of 100 pF ...1nF fits in most cases. The time
constant _τ_ RC should be in a range of 0.1 tCMP ...tCMP of the comparator. The resistors should be in the
range of 1K to 10K. The fMAXtyp depends also on the choice of the decimation ratio.

|CMP|tCMPtyp [ns]|RMCMP [kΩ]|RMDAC [kΩ]|CMCMP [pF]|fMCLKmaxTYP|
|---|---|---|---|---|---|
|LM339|1000|<br>1|<br>1|<br>100|1 MHz|
|LM339|1000|10|10|100|100 kHz|
|LM339|1000|100|100|100|10 kHz|



_Table 17:_ _Delta Sigma R-C-R-CMP Configurations (pls._ _refer 17)_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-36-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 38 / 153


For external Delta Sigma R-C-R-CMP modulators, one gets the Delta Sigma input voltage mapping according to table 18. The support of low-cost external comparators used as first order delta sigmal modulators
is intended as an generic analog interface option for compatibility of the TMC4671 core in case it would
be embedded within a pure digital technology environment.

|Vmin[V]|Vref[V]|Vmax[V]|VIN[V]|DUTY[%]|ADC_RAW|
|---|---|---|---|---|---|
|0.0|1.65|3.3|0.0|0%|0x0000|
|0.0|1.65|3.3|0.825|25%|0x4000|
|0.0|1.65|3.3|1.65|50%|0x7ﬀf|
|0.0|1.65|3.3|2.475|75%|0xC000|
|0.0|1.65|3.3|3.3|100%|0xﬀﬀ|
|Vmin[V]|Vref[V]|Vmax[V]|VIN[V]|DUTY[%]|ADC_RAW|
|0.0|2.5|5.0|0.0|0%|0x0000|
|0.0|2.5|5.0|1.0|25%|0x4000|
|0.0|2.5|5.0|2.5|50%|0x7ﬀf|
|0.0|2.5|5.0|3.75|75%|0xC000|
|0.0|2.5|5.0|5.0|100%|0xﬀﬀ|



_Table 18:_ _Delta Sigma input voltage mapping of external comparator (CMP)_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 39 / 153


**4.5** **Analog Signal Conditioning**


The range of measured coil currents, resp. the measured voltages of sense resistors, needs to be mapped
to the valid input voltage range of the delta sigma ADC inputs. This analog preprocessing is the task of
the analog signal conditioning.


**4.5.0.1** **Chain of Gains for ADC Raw Values**


An ADC raw value is a result of a chain of gains that determine it. A coil current I_SENSE flowing through a
sense resistor causes a voltage difference according to Ohm’s law. Finally, a current is mapped to an ADC
raw value


ADC_RAW = (I_SENSE _·_ ADC_GAIN) + ADC_OFFSET _._ (16)


The ADC_GAIN is a result of a chain of gains with individual signs. The sign of the ADC_GAIN is positive
or negative, depending on the association of connections between sense amplifier inputs and the sense
resistor terminals. The ADC_OFFSET is the result of electrical offsets of the phase current measurement
signal path. For the TMC4671, the maximum ADC_RAW value is ADC_RAW_MAX = (2 [16] _−_ 1) and the minimum ADC raw value is ADC_RAW_MIN = 0.


ADC_GAIN = ( I_SENSE_MAX _·_ R_SENSE )




_·_ SENSE_AMPLIFIER_GAIN


_·_ ( ADC_RAW_MAX _/_ ADC_U_MAX )

|Rsense [mΩ]|Isense [A]|Usense [mV ]|GAIN[V/V ]|ADC_GAIN[A/V ]|Sense Amplifier|
|---|---|---|---|---|---|
|5|10|50|20|10|AD8418|
|10|5|50|20|5|AD8418|



_Table 19:_ _Example Parameters for ADC_GAIN_



(17)



For the FOC, the ADC_RAW is scaled by the ADC scaler of the TMC4671 together with subtraction of offset
to compensate it. Internally, the TMC4671 FOC engine calculates with s16 values. So, the ADC scaling
needs to be chosen so that the measured currents fit into the s16 range. With the ADC scaler, the user can
choose a scaling with physical units like [ _mA_ ]. A scaling to [ _mA_ ] covers a current range of _−_ 32 _A . . ._ +32 _A_ with
_m_ [ _A_ ] resolution. For higher currents, the user can choose unusual units like centi Ampere [ _cA_ ] covering

_−_ 327 _A . . ._ + 327 _A_ or deci Ampere _−_ 3276 _A . . ._ + 3276 _A_ .


ADC scaler and offset compensators are for mapping raw ADC values to s16 scaled and offset cleaned
current measurement values that are adequate for the FOC.


**4.5.1** **FOC3 - Stator Coil Currents I_U, I_V, I_W and associated Voltages U_U, U_V, U_W**


The correct association between stator terminal voltages U_U, U_V, U_W and stator coil currents I_U, I_V,
I_W is essential for the FOC.


For three-phase motors with three terminals U, V, W, the voltage U_U is in phase with the current I_U, U_V
is in phase with I_V, and U_W is in phase with I_W according to equations (18) and (19) for FOC3.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 40 / 153



_UU_ ( _φe_ ) = _UD_ _·_ _sin_ ( _φe_ )


_UV_ ( _φe_ ) = _UD_ _·_ _sin_ ( _φe_ + 120 _[o]_ )


_UW_ ( _φe_ ) = _UD_ _·_ _sin_ ( _φe −_ 120 _[o]_ )


_IU_ ( _φe_ ) = _ID_ _·_ _sin_ ( _φe_ )


_IV_ ( _φe_ ) = _ID_ _·_ _sin_ ( _φe_ + 120 _[o]_ )


_IW_ ( _φe_ ) = _ID_ _·_ _sin_ ( _φe −_ 120 _[o]_ )



U_UVW_FOC3(U_D, PHI_E) =


I_UVW_FOC3(I_D, PHI_E) =


















(18)


(19)



**4.5.2** **FOC2 - Stepper Coil Currents I_X, I_Y and associated Voltages U_X, U_Y**


For two-phase motors (stepper) with four terminals UX1, VX2, and WY1, Y2, voltage U_Ux = U_X1 - U_X2
is in phase with the measured current I_X and U_Wy = U_Y1 - U_Y2 is in phase with the measured current
I_Y according to equations (20) and (21) for FOC2.



(20)
_UY_ ( _φe_ ) = _UY_ _·_ _sin_ ( _φe_ + 90 _[o]_ )



U_XY_FOC2 =


I_XY_FOC2 =








 _UX_ ( _φe_ ) = _UX_ _·_ _sin_ ( _φe_ )


 _UY_ ( _φe_ ) = _UY_ _·_ _sin_ ( _φe_



 _IX_ ( _φe_ ) = _ID_ _·_ _sin_ ( _φe_ )


 _IY_ ( _φe_ ) = _ID_ _·_ _sin_ ( _φe_








(21)
_IY_ ( _φe_ ) = _ID_ _·_ _sin_ ( _φe_ + 90 _[o]_ )



**4.5.3** **FOC1 - DC Motor Coil Current I_X1, I_X2, and associated Voltage U_X1, U_X2**


For DC motor with with two terminals UX1, VX2, voltage U_X = U_X1 - U_X2 is in phase (same sign) with the
measured current I_X. U_X is in phase (same sign) with the measured current I_X according to equations
(22) and (23) for FOC1.


U_XY_FOC1 = _UX_ 1 _−_ _VX_ 2 (22)


I_XY_FOC1 = _IX_ 1 (23)


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 41 / 153


**4.5.4** **ADC Selector & ADC Scaler w/ Offset Correction**


The ADC selector selects ADC channels for FOC. The 3-phase FOC uses two ADC channels for measurement
and calculates the third channel via Kirchhoff’s Law using the scaled and offset-corrected ADC values.
The 2-phase FOC just uses two ADC channels because for a 2-phase stepper motor, the two phases are
independent from each other.


_**Note**_ The open-loop encoder is useful for setting up ADC channel selection, scaling,
and offset by running a motor open-loop.


The FOC23 Engine processes currents as 16 bit signed (s16) values. Raw ADC values are expanded to 16
bit width, regardless of their resolution. With this, each ADC is available for read out as a 16 bit number.
The ADC scaler w/ offset correction is for the preprocessing of measured raw current values. It might be
used to map to user’s own units (e.g. A or mA). For scaling, gains of current amplifiers, reference voltages,
and offsets have to be taken into account.


_**Info**_ Raw ADC values generally are of 16 bit width, regardless of their real resolution.


_**Info**_ The ADC scaler maps raw ADC values to the 16 bit signed (s16) range and centers
the values to zero by removing offsets.


_Figure 19:_ _ADC Selector & Scaler w/ Offset Correction_


ADC offsets and ADC scalers for the analog current measurement input channels need to be programmed
into the associated registers. Each ADC_I_U, ADC_I_V, ADC_I0_EXT, and ADC_I1_EXT are mapped either to
ADC_I0_RAW or to ADC_I1_RAW by ADC_I0_SELECT and ADC_I1_SELECT.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-40-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 42 / 153


In addition, the ADC_OFFSET is for conversion of unsigned ADC values into signed ADC values as required
for the FOC. For FOC3, the third current ADC_I2 is calculated via Kirchhoff’s Law. This requires the correct
scaling and offset correction beforehand. For FOC2, there is no calculation of a third current. The scaling
factors ADC_I0_SCALE and ADC_I1_SCALE are displayed in a Q8.8 format which results in the following
equations:


ADC_I0 = (ADC_I0_RAW _−_ ADC_I0_OFFSET) _·_ ADC_I0_SCALE / 256 (24)


ADC_I1 = (ADC_I1_RAW _−_ ADC_I1_OFFSET) _·_ ADC_I1_SCALE / 256 (25)


The ADC_UX_SELECT selects one of the three ADC channels ADC_I0, ADC_I1, or ADC_I2 for ADC_UX.


The ADC_V_SELECT selects one of the three ADC channels ADC_I0, ADC_I1, or ADC_I2 for ADC_V.


The ADC_WY_SELECT selects one of the three ADC channels ADC_I0, ADC_I1, or ADC_I2 for ADC_WY.


The ADC_UX, ADC_V, and ADC_WY are for the FOC3 (U, V, W).


The ADC_UX and ADC_WY (X, Y) are for the FOC2 (UX, WY).


_**Note**_ The open-loop encoder is useful to run a motor open loop for setting up the ADC
channel selection with correct association between phase currents I_U, I_V, I_W
and phase voltages U_U, U_V, U_W.


**4.6** **Encoder Engine**


The encoder engine is an unified position sensor interface. It maps the selected encoder position information to electrical position (phi_e) and to mechanical position (phi_m). Both are 16 bit values. The encoder
engine maps single turn positions from position sensors to multi-turn positions. The user can overwrite
the multi-turn position for initialization.


The different position sensors are the position sources for torque and flux control via FOC, for velocity
control, and for position control. The PHI_E_SELECTION selects the source of the electrical angle phi_e
for the inner FOC control loop. VELOCITY_SELECTION selects the source for velocity measurement. With
phi_e selected as source for velocity measurement, one gets the electrical velocity. With the mechanical
angle phi_m selected as source for velocity measurement, one gets the mechanical velocity taking the
set number of pole pairs (N_POLE_PAIRS) of the motor into account. Nevertheless, for a highly precise
positioning, it might be useful to do positioning based on the electrical angle phi_e.


**4.6.1** **Open-Loop Encoder**


For initial system setup, the encoder engine is equipped with an open-loop position generator. This allows
for turning the motor open-loop by specifying speed in rpm and acceleration in rpm/s, together with a
voltage UD_EXT in D direction. As such, the open-loop encoder is not a real encoder. It simply gives
positions as an encoder does. The open-loop decoder has a direction bit to define direction of motion for
the application.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 43 / 153


_**Note**_ The open-loop encoder is useful for initial ADC setup, encoder setup, Hall signal
validation, and for validation of the number of pole pairs of a motor. The openloop encoder turns a motor open with programmable velocity in unit [RPM] with
programmable acceleration in unit [RPM/s].


With the open-loop encoder, the user can turn a motor without any position sensor and without any
current measurement as a first step of doing the system setup. With the turning motor, the user can
adjust the ADC scales and offsets and set up positions sensors (Hall, incremental encoder, ...) according
to resolution, orientation, and direction of rotation.


**4.6.2** **Incremental ABN Encoder**


The incremental encoders give two phase shifted incremental pulse signals A and B. Some incremental
encoders have an additional null position signal N or zero pulse signal Z. An incremental encoder (called
ABN encoder or ABZ encoder) has an individual number of incremental pulses per revolution. The number
of incremental pulses define the number of positions per revolution (PPR). The PPR might mean pulses
per revolution or periods per revolution. Instead of positions per revolution, some incremental encoder
vendors call these CPR counts per revolution.


The PPR parameter is the most important parameter of the incremental encoder interface. With that, it
forms a modulo (PPR) counter, counting from 0 to (PPR-1). Depending on the direction, it counts up or
down. The modulo PPR counter is mapped into the register bank as a dual ported register. The user can
overwrite it with an initial position. The ABN encoder interface provides both the electrical position and
the multi-turn position, which are accessible through dual-ported read-write registers.


_**Note**_ The PPR parameter must be set exactly according to the used encoder.


_Figure 20:_ _Number of Pole Pairs NPP vs._ _mechanical angle phi_m and electrical angle phi_e_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-42-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 44 / 153


The goal of the initialization of an incremental encoder is to set it up so that the magnetic axis of the rotor
fits with the electrical angle phi_e with the angle zero on D axis. For this, one needs to know the number of
pole pairs NPP, the resolution of the incremental encoder in pulses per revolution PPR, and the orientation
between measured encoder angle of the rotor and the electrical angle of the field orientation. An encoder
measures mechanical angle phi_m were the FOC needs the electrical angle phi_e for commutation. The
number of pole pairs NPP determines the ratio between mechanical angle phi_m and electrical angle
phi_e. The parameters phi_m_offset and phi_e_offset are for compensation of differences in orientation
angle by adjustments.


_Figure 21:_ _ABN Incremental Encoder N Pulse_


The N pulse from an encoder triggers either sampling of the actual encoder count to fetch the position
at the N pulse or it re-writes the fetched n position on an N pulse. The N pulse can either be used as
stand alone pulse or and-ed with NAB = N and A and B. It depends on the decoder what kind of N pulse
has to be used - either N or NAB. For those encoders with precise N pulse within one AB quadrant, the N
pulse must be used. For those encoders with N pulse over four AB quadrants the user can enhance the
precision of the N pulse position detection by using NAB instead of N.


_**Note**_ Incremental encoders are available with N pulse and without N pulse.


The polarity of N pulse, A pulse and B pulse are programmable. The N pulse is for re-initialization with
each turn of the motor. Once fetched, the ABN decoder can be configured to write back the fetched N
pulse position with each N pulse.


_**Note**_ The ABN encoder interface has a direction bit to set to match wiring of motor to
direction of encoder.


Logical ABN = A and B and N might be useful for incremental encoders with low resolution N pulse to
enhance the resolution. On the other hand, for incremental encoders with high resolution N pulse a
logical ABN = A and B and N might totally suppress the resulting N pulse.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-43-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 45 / 153


_Figure 22:_ _Encoder ABN Timing - high precise N pulse and less precise N pulse_


**4.6.3** **Secondary Incremental ABN Encoder**


For commutating a motor with FOC, the user selects a position sensor source (digital incremental encoder,
digital Hall, analog Hall, analog incremental encoder, ...) that is mounted close to the motor. The inner
FOC loop controls torque and flux of the motor based on the measured phase currents and the electrical
angle of the rotor.


The TMC4671 is equipped with a secondary incremental encoder interface. This secondary encoder interface is available as source for velocity control or position control. This is for applications where a motor
with a gearing positions an object.


_**Info**_ The secondary incremental encoder is not available for commutation (phi_e) for
the inner FOC. In others words, there is no electrical angle phi_e selectable from
the secondary encoder.


**4.6.4** **Digital Hall Sensor Interface with optional Interim Position Interpolation**


The digital Hall interface is the position sensor interface for digital Hall signals. The digital Hall signal
interface first maps the digital Hall signals to an electrical position PHI_E_RAW. An offset PHI_E_OFFSET
can be used to rotate the orientation of the Hall signal angle. The electrical angle PHI_E is for commutation.
Optionally, the default electrical positions of the Hall sensors can be adjusted by writes into the associated
registers.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-44-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 46 / 153


_Figure 23:_ _Hall Sensor Angles_


Hall sensors give absolute positions within an electrical period with a resolution of 60° as 16 bit positions
(s16 resp. u16) PHI. With activated interim Hall position interpolation, the user gets high resolution interim
positions when the motor is running at a speed above 60 rpm.


**4.6.5** **Digital Hall Sensor - Interim Position Interpolation**


For lower torque ripple the user can switch on the position interpolation of interim Hall positions. This
function is useful for motors that are compatible with sine wave commutation, but equipped with digital
Hall sensors. When the position interpolation is switched on, it becomes active on speeds above 60 rpm.
For lower speeds it automatically disables itself. This is especially important when the motor has to be at
rest. Hall sensor position interpolation might fail when Hall sensors are not properly placed in the motor.
Please adjust Hall sensor positions for this case.


_**Info**_ Hall interpolation is not intended for positioning applications, especially not with
changes of direction. Please check errata section if you want to use hall interpolation and positioning. When using interpolated angles PID_POSITION_ACTUAL
might glitch when direction is changed or the motor operates at very low velocity.


**4.6.6** **Digital Hall Sensors - Masking, Filtering, and PWM center sampling**


Sometimes digital Hall sensor signals get disturbed by switching events in the power stage. The TMC4671
can automatically mask switching distortions by correct setting of the HALL_MASKING register. When a
switching event occurs, the Hall sensor signals are held for HALL_MASKING value times 10 ns. This way,
Hall sensor distortions are eliminated.


Uncorrelated distortions can be filtered via a digital filter of configurable length. If the input signal to the
filter does not change for HALL_DIG_FILTER_LENGTH times 5 us, the signal can pass the filter. This filter
eliminates issues with bouncing Hall signals. naming with Elliot: Masking is better then Blanking


Spikes on Hall signals (Hx that stands for H1, H2, H3) disturb the FOC loop when Hall signals are used for
commutation or for initialization of incremental encoders. Spikes on hall signal lines might occur when


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-45-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 47 / 153


Hall signals are feed on singled ended signal lines in parallel to motor power lines due to electromagnetic
cross talk in a single cable. Long Hall signal lines might cause digital Hall signal cross talk even in separate
fed cables. Cables that provide Hall signals without spikes should be preferred. A good ground for digital
Hall signals is important for clean Hall signals. A good ground shield of the motor might help for clean Hall
signals. In best case, Hall signals are fed within separate shielded signal lines together with differential
line drivers.


_Figure 24:_ _Outline of noisy Hall signals (left) due to electromagnetic interference with PWM switching and noise_
_cleaned Hall signals (right) by PWM center synced sampling of Hall signal vector (H1 H2 H3)_


The best is avoiding spikes on digital Hall signals. Nevertheless, to enable lower cost motors with lower
performance Hall signal shielding, the TMC4671 is equipped with Hall Signal spike suppression and PWM
centered Hall signal vector sampling.


To reduce possible current ripple that might be caused by noisy Hall signals, the sampling of the Hall signal
vector can be programmed for sampling once per PWM period at its center for the desired noise reduction. The PWM centered Hall signal sampling is programmable by HALL_MODE(4) control bit. Continuous
sampling is default. This function is not available for TMC4671-ES engineering samples.


_Figure 25:_ _Hall Signal PWM Center Sampling on PWM_CENTER_


The PWM center synchronization needs to be qualified for high speed applications due to reduction of
Hall signals for PWM frequency. The PWM center might have an influence on Hall signal interpolation and
needs to be qualified if Hall signal interpolation is enabled.


For additional spike suppression, the TMC4671 is equipped with a digital hall signal blanking, to support lower performance cabling environments. The blank time for the Hall signals is programmable
(HALL_BLANK) in steps of 10 ns from 0 ns up to 4095 ns. The Hall signal blanking time should be programmed as long as necessary for safe suppression of spikes of maximum duration. On the other side,
the Hall signal blanking should be programmed as short as possible to avoid disturbance by too strong
filtering that might also disturbe the FOC.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-46-0.png)

![](images/TMC4671-LA_datasheet_rev2.08.pdf-46-1.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 48 / 153


_Figure 26:_ _Hall Signal Blanking_


**4.6.7** **Digital Hall Sensors together with Incremental Encoder**


If a motor is equipped with both Hall sensors and incremental encoder, the Hall sensors can be used for
the initialization as a low resolution absolute position sensor. Later on, the incremental encoder can be
used as a high resolution sensor for commutation.


**4.6.8** **Analog Hall and Analog Encoder Interface (SinCos of 0° 90° or 0° 120° 240°)**


An analog encoder interface is part of the decoder engine. It is able to handle analog position signals of 0°
and 90° and of 0° 120° 240°. The analog decoder engine adds offsets and scales the raw analog encoder
signals, while also calculating the electrical angle PHI_E from these analog position signals by an ATAN2
algorithm.


**SIN/COS Hall**



![](images/TMC4671-LA_datasheet_rev2.08.pdf-47-0.png)

![](images/TMC4671-LA_datasheet_rev2.08.pdf-47-1.png)



**SIN/COS with 10 PPR**


**3-phase Analog Hall**



![](images/TMC4671-LA_datasheet_rev2.08.pdf-47-2.png)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-47-3.png)



_Figure 27:_ _Analog Encoder (AENC) signal waveforms_


An individual signed offset is added to each associated raw ADC channel and scaled by its associated
scaling factors according to


AENC_VALUE = (AENC_RAW + AENC_OFFSET) _·_ AENC_SCALE (26)


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 49 / 153


In addition, the AENC_OFFSET is for conversion of unsigned ADC values into signed ADC values as required
for the FOC.


_**Info**_ The control bit 0 in register AENC_DECODER_MODE (0x3B) selects either processing of analog position signals of 0° and 90° (0b0) or analog signals of 0° 120° 240°
on (0b1).


_Figure 28:_ _Analog Encoder (AENC) Selector & Scaler w/ Offset Correction_


In Fig. 27 possible waveforms are shown. The graphs show usual SIN/COS track signals with one and multiple periods per revolution as well as typical waveforms of three phase analog Hall signals for one electrical revolution. The number of periods per revolution can be configured by register AENC_DECODER_PPR.
The position in one period (AENC_DECODER_PHI_A) is calculated by an ATAN2 algorithm. The periods
are counted with respect to the number of periods per revolution to calculate AENC_DECODER_PHI_E
and AENC_DECODER_PHI_M. If PPR is the same as the number of pole pairs, AENC_DECODER_PHI_E and
AENC_DECODER_PHI_A are identical. This is usually the case for analog hall signals.


_**Info**_ The analog N pulse is just a raw ADC value. Handling of analog N pulse similar
to N pulse handling of digital encoder N pulse is not implemented for analog
encoder.


**4.6.9** **Analog Position Decoder (SinCos of 0°90° or 0°120°240°)**


The extracted positions from the analog decoder are available for read out from registers.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-48-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 50 / 153


**4.6.9.1** **Multi-Turn Counter**


Electrical angles are mapped to a multi-turn position counter. The user can overwrite this multi-turn
position for initialization purposes.


**4.6.9.2** **Encoder Engine Phi Selector**


The angle selector selects the source for the commutation angle PHI_E. That electrical angle is available
for commutation.


**4.6.9.3** **External Position Register**


A register value written into the register bank via the application interface is available for commutation
as well. With this, the user can interface to any encoder by just writing positions extracted from external
encoder into this regulator. From the decoder engine point of view this is just one more selectable encoder
source.


**4.6.10** **Encoder Initialization Support**


The TMC4671 needs proper feedback for correct and stable operation. One main parameter is the commutation angle offset PHI_E_OFFSET. This offset must not be calculated when an absolute sensor system
like analog or digital Hall sensors is used. All other supported feedback systems need to be initialized their PHI_E_OFFSETs need to be identified. The user has several options to determine PHI_E_OFFSET with
support of the TMC4671.


**4.6.10.1** **Encoder Initialization in Open-Loop Mode**


In the case of a free driving motor, the motor can be switched to Open-Loop Mode. In this mode, the
used commutation angle (PHI_OPEN_LOOP) can be used to match the measured PHI_E. This method is
supported by the TMCL-IDE.


**4.6.10.2** **Encoder Initialization by Hall sensors**


The TMC4671 can calculate PHI_E_OFFSET very precisely at a Hall state change for a second encoder system, when Hall sensors are correctly aligned. Therefore, the function needs to be enabled and calculate a
new offset at the next Hall state change. After disabling of the module, the process can be started again.
This function can also be used as a rough plausibility check during longer operation.


**4.6.10.3** **Encoder Initialization by N Pulse Detection**


After determination of a correct offset, the value can be used again after power cycle. The encoder’s N
pulse can be used as reference for this. For starters the user can drive the motor in open-loop mode or
by using digital Hall sensor signals. After passing the encoder’s N pulse, the ABN encoder is initialized and
can be used for operation.


**4.6.11** **Velocity Measurement**


Servo control comprises position, velocity and current control. The position and the current are measured
by separate sensors. The actual velocity has to be calculated by time discrete differentiation from the
position signal. the user can choose a calculated position from the various encoder interfaces for velocity
measurement by parameter VELOCITY_SELECTION.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 51 / 153


The user can switch between two different velocity calculation algorithms with the parameter VELOCITY_METER_SELECTION. Default setting (VELOCITY_METER_SELECTION = 0) is the standard velocity meter,
which calculates the velocity at a sampling rate of about 4369.067 Hz by differentiation. Output value is
displayed in rpm (revolutions per minute). This option is recommended for usage with the standard PI
controller structure.
By choosing the second option (VELOCITY_METER_SELECTION = 1), the sampling frequency is synchronized to the PWM frequency. This option is recommended for usage with the advanced PI controller
structure. Otherwise, the controller structure might tend to be unstable due to non-matched sampling.
Velocity filters can be applied to reduce noise on velocity signals. Section 4.8 describes filtering opportunities in detail.


**4.6.12** **Reference Switches**


The TMC4671 is equipped with three input pins for reference switches (REF_SW_L, REF_SW_H and REF_SW_R).
These pins can be used to determine three reference positions. The TMC4671 displays the status of the
reference switches in the register TMC4671_INPUTS_RAW and is able to store the actual position at rising
edge of the corresponding signal. The signal polarities are programmable and the module reacts only on
toggling the ENABLE register. The signals can be filtered with a configurable digital filter, which suppresses
spike errors.
With the STATUS_FLAGS and STATUS_MASK register the STATUS output can be configured as an IRQ for
passing a reference switch.
The actual position can be latched when passing a reference switch. The latched positions can be displayed in register INTERIM_DATA (0x6E). Register INTERIM_ADDR (0x6F) selects the data displayed in INTERIM_DATA with HOME_POSITION at address 31, LEFT_POSITION at adress 32 and RIGHT_POSITION at
adress 33.
The position latching can be enabled via register CONFIG_DATA (0x4D) with CONFIG_ADDR (0x4E) set
to 51 (ref_switch_config). Position latching is enabled by setting bit 0 of ref_switch_config to 1.If a reference switched is passed the corresponding status bit (HOME_SWITCH_PASSED, LEFT_SWITCH_PASSED,
and RIGHT_SWITCH_PASSED) in REF_SWITCH_STATUS (INTERIM_DATA with INTERIM_ADDRESS = 30) is enabled. The bits can only be cleared by toggling/disabling the enable bit in ref_switch_config.


_**Info**_ The polarity registers do not affect the status registers. The status flag only represents the current logical state of the switch.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 52 / 153


**4.7** **FOC23 Engine**


The FOC23 engine performs the inner current control loop for the torque current _IQ_ and the flux current
_ID_ including the required transformations. Programmable limiters take care of clipping of interim results.
Per default, the programmable circular limiter clips U_D and U_Q to U_D_R = �(2) _·_ U_Q and U_R_R = ~~�~~ (2) _·_
U_D. PI controllers perform the regulation tasks. Please make sure to enable controllers by pulling ENI
pin to high level.


**4.7.1** **ENI and ENO pins**


The ENI (Enable input) can be used to start and stop control action. During reset ENO (Enable out) is low
and afterwards it forwards ENI signal. Thereby it can be used to enable the power stage. When ENI is low,
all controllers are deactivated and PWM operates at 50% duty cycle. ENI input value can be read through
TMC4671_INPUTS_RAW register.


**4.7.2** **PI Controllers**


PI controllers are used for current control and velocity control. A P controller is used for position control.
The derivative part is not yet supported but might be added in the future. The user can choose between
two PI controller structures: The classic PI controller structure, which is also used in the TMC4670, and
the advanced PI controller structure. The advanced PI controller structure shows better performance in
dynamics and is recommended for high performance applications. User can switch between controllers
by setting register MODE_PID_TYPE. Controller type can not be switched individually for each cascade
level.


**4.7.3** **PI Controller Calculations - Classic Structure**


The PI controllers in the classic structure perform the following calculation



with




      - _t_
Y = P _·_ e + I _·_ e(t) d _t_ (27)

0


e = X_TARGET _−_ X (28)



where X_TARGET stands for target flux (s16), target torque (s16), target velocity (s32), or target position
(s32) with error e, which is the difference between target value and actual values. The Y stands for the
output of the PI controller feed as target input to the successive PI controller of the FOC servo controller
cascade (position _→_ PI _→_ velocity _→_ PI _→_ current _→_ PI _→_ voltage).


Y_PID_FLUX = PID_FLUX_P     - ERROR_FLUX / 256


Y_PID_FLUX_RATE = PID_FLUX_I     - ERROR_FLUX / 65536 / (32 _µ_ s)


Y_PID_TORQUE = PID_FLUX_P     - ERROR_TORQUE / 256


Y_PID_TORQUE_RATE = PID_TORQUE_I     - ERROR_TORQUE / 65536 / (32 _µ_ s)


Y_PID_VELOCITY = PID_VELOCITY_P     - ERROR_VELOCITY / 256


Y_PID_VELOCITY_RATE = PID_VELOCITY_I     - ERROR_VELOCITY / 65536 / (256 _µ_ s)


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 53 / 153


Y_PID_POSITION = PID_POSITION_P     - ERROR_POSITION / 65536


Y_PID_POSITION_RATE = PID_POSITION_I     - ERROR_POSITION / 65536 / (256 _µ_ s)


_Table 20:_ _Scalings and Change Rate Timings of PID controllers (classic structure) for currents, velocity, and_
_position for clock frequency fCLK = 25MHz_

|Number|Motion Mode|Description|
|---|---|---|
|0|Stopped Mode|Disabling all controllers|
|1|Torque Mode|Standard Torque Control Mode|
|2|Velocity Mode|Standard Velocity Control Mode|
|3|Position Mode|Standard Position Control Mode|
|4|PRBS Flux Mode|PRBS Value is used as Target Flux Value for Ident.|
|5|PRBS Torque Mode|PRBS Value is used as Target Torque Value for Ident.|
|6|PRBS Velocity Mode|PRBS Value is used as Target Velocity Value for Ident.|
|7|PRBS Position Mode|PRBS Value is used as Target Position Value for Ident.|
|8|UQ UD Ext Mode|Voltage control mode (Software Mode)|
|9|reserved|reserved|
|10|AGPI_A Torque Mode|AGPI_A used as Target Torque value|
|11|AGPI_A Velocity Mode|AGPI_A used as Target Velocity value|
|12|AGPI_A Position Mode|AGPI_A used as Target Position value|
|13|PWM_I Torque Mode|PWM_I used as Target Torque value|
|14|PWM_I Velocity Mode|PWM_I used as Target Velocity value|
|15|PWM_I Position Mode|PWM_I used as Target Position value|



_Table 21:_ _Motion Modes_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 54 / 153


_Figure 29:_ _Classic PI Controller_


_**Info**_ Changing the I-parameter of the classic PI controller during operation causes
the controller output to jump, as the control error is first integrated and then
gained by the I parameter. Jumps can be avoided by incremental changes of
I-parameter.


_**Info**_ Support for the TMC4671 is integrated into the TMCL-IDE including wizards for
set up and configuration. With the TMCL-IDE, configuration and operation can be
done in a few steps and the user gets direct access to all registers of the TMC4671.


**4.7.4** **PI Controller Calculations - Advanced Structure**


The PI controllers in the advanced controller structure perform the calculation



![](images/TMC4671-LA_datasheet_rev2.08.pdf-53-0.png)

with




      - _t_
dXdT = P _·_ e + P _·_ I _·_ e(t) d _t_ (29)

0


e = X_TARGET _−_ X (30)



where X_TARGET represents target flux, target torque, target velocity, or target position with control error
e, which is the difference between target value and actual values. The time constant d _t_ is set according
to the PWM period but can be downsampled for the position controller by register MODE_PID_SMPL.
Position controller evaluation can be downsampled by a constant factor when needed.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 55 / 153


_Figure 30:_ _Advanced PI Controller_


_**Info**_ The P Factor normalization as Q8.8 of the advanced PI controller of the TMC4671ES is selectable for the TMC4671-LA as either Q8.8 or Q4.12. This can be configured in register 0x4D CONFIG_DATA when register 0x4E CONFIG_ADDR is set to
0x3E. For more information refer to section 7.2. Using Q4.12 needs changes in
the user’s application controller software when using the Advanced PI position
controller.


The transfer function of the advanced PI controller can be described by the following pseudo code:


dXdT = e _·_ P + integrator

(31)
integrator = integrator + (P _·_ I _·_ e) _/_ 256


_**Info**_ For the advanced control structure the integrator input value is additionally divided by 256. (s. equation 31)


P and I are either displayed as Q8.8 (P/256) or Q4.12 (P/4096). This is individually configurable for each
controller parameter in the controller cascade. Table 22 gives an overview on how the representation
affects the integrator and the output of the PI controller.



![](images/TMC4671-LA_datasheet_rev2.08.pdf-54-0.png)







|PI representation|I 8.8|I 4.12|
|---|---|---|
|P 8.8|dXdT = e_ ·_ P<br>256 + integrator<br>integrator = integrator +<br> P<br>256 _·_<br>I<br>256 _·_ e<br><br>_/_256|dXdT = e_ ·_ P<br>256 + integrator<br>integrator = integrator +<br> P<br>256 _·_<br>I<br>4096 _·_ e<br><br>_/_256|
|P 4.12|dXdT = e_ ·_<br>P<br>4096 + integrator<br>integrator = integrator +<br> P<br>4096 _·_<br>I<br>256 _·_ e<br><br>_/_256|dXdT = e_ ·_<br>P<br>4096 + integrator<br>integrator = integrator +<br> P<br>4096 _·_<br>I<br>4096 _·_ e<br><br>_/_256|


_Table 22:_ _PI normalization overview_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 56 / 153


Downsampling of the advanced position controller can be configured by register MODE_PID_SMPL. When
the register is 0 the controllers will sample on the PWM-frequency fPWM. The new samplerate will be
derived from fPWM and the downsampling-value assigned to register MODE_PID_SMPL (range: 0 to 127).
The derived sampling frequency is calculated as follows:


f
PWM
Sampleratenew = (32)
downsampling + 1


**4.7.5** **PI Controller - Clipping**


The limiting of target values for PI controllers and output values of PI controllers is programmable. Per
power on default these limits are set to maximum values. During initialization, these limits should be set
properly for correct operation and clipping.
The target input is clipped to X_TARGET_LIMIT. The output of a PI controller is named dXdT because it gives
the desired derivative d/dt as a target value to the following stage: The position (x) controller gives velocity (dx/dt). The output of the PI Controller is clipped to dXdT_LIMIT. The error integral of (27) is clipped to
dXdT_LIMIT / I in the classic controller structure, and the integrator output is clipped to dXdT_output_limit
in the advanced controller structure.


The output of the torque and flux controller is limited by register 0x5D PIDOUT_UQ_UD_LIMITS.
The input of the torque and flux controller is limited by register 0x5E PID_TORQUE_FLUX_LIMITS.
The input of the velocity controller is limited by register 0x60 PID_VELOCITY_LIMIT.
The minimum input of the position controller is limited by register 0x61 PID_POSITION_LIMIT_LOW.
The maximum input of the position controller is limited by register 0x62 PID_POSITION_LIMIT_HIGH.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 57 / 153


_Figure 31:_ _PI Controllers for position, velocity and current_


**4.7.6** **PI Flux & PI Torque Controller**


The P part is represented as q8.8 and I is the I part represented as q0.15.


**4.7.7** **PI Velocity Controller**


The P part is represented as q8.8 and I is the I part represented as q0.15.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-56-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 58 / 153


**4.7.8** **P Position Controller**


For the position regulator, the P part is represented as q4.12 to be compatible with the high resolution
positions - one single rotation is handled as an s16. For the advanced controller structure the P part is
represented by q8.8.


**4.7.9** **Inner FOC Control Loop - Flux & Torque**


The inner FOC loop (figure 32) controls the flux current to the flux target value and the torque current
to the desired torque target. The inner FOC loop performs the desired transformations according to
figure 33 for 3-phase motors (FOC3). For 2-phase motors (FOC2) both Clarke (CLARKE) transformation
and inverse Clarke (iCLARKE) are bypassed. For control of DC motors, transformations are bypassed and
only the first full bridge (connected to X1 and X2) is used.


The inner FOC control loop gets a target torque value (I_Q_TARGET) which represents acceleration, the rotor position, and the measured currents as input data. Together with the programmed P and I parameters,
the inner FOC loop calculates the target voltage values as input for the PWM engine.


_Figure 32:_ _Inner FOC Control Loop_


**4.7.10** **FOC Transformations and PI(D) for control of Flux & Torque**


The Clarke transformation (CLARKE) maps three motor phase currents ( _IU_, _IV_, _IW_ ) to a two-dimensional
coordinate system with two currents ( _Iα_, _Iβ_ ). Based on the actual rotor angle determined by an encoder
or via sensorless techniques, the Park transformation (PARK) maps these two currents to a quasi-static
coordinate system with two currents ( _ID_, _IQ_ ). The current _ID_ represents flux and the current _IQ_ represents
torque. The flux just pulls on the rotor but does not affect torque. The torque is affected by _IQ_ . Two PI
controllers determine two voltages ( _UD_, _UQ_ ) to drive desired currents for a target torque and a target
flux. The determined voltages ( _UD_, _UQ_ ) are re-transformed into the stator system by the inverse Park
transformation (iPARK). The inverse Clarke Transformation (iCLARKE) transforms these two currents into
three voltages ( _UU_, _UV_, _UW_ ). Theses three voltage are the input of the PWM engine to drive the power
stage.


In case of the FOC2, Clarke transformation CLARKE and inverse Clarke Transformation iCLARKE are skipped.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-57-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 59 / 153


_Figure 33:_ _FOC3 Transformations (FOC2 just skips CLARKE and iCLARKE)_


**4.7.11** **Motion Modes**


The user can operate the TMC4671 in several motion modes. Standard motion modes are position control,
velocity control and torque control, where target values are fed into the controllers via register access. The
motion mode UD_UQ_EXTERN allows the user to set voltages for open-loop operation and for tests during
setup.


_Figure 34:_ _Standard Motion Modes_


In position control mode, the user can feed the step and direction interface to generate a position target
value for the controller cascade. In additional motion modes target values are fed into the TMC4671 via
PWM interface (Pin: PWM_IN) or analog input via pin AGPI_A.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-58-0.png)

![](images/TMC4671-LA_datasheet_rev2.08.pdf-58-1.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 60 / 153


There are additional motion modes, which are using input from the PWM_I input or the AGPI_A input.
Input signals can be scaled via a standard scaler providing offset and gain correction. The interface can
be configured via the registers SINGLE_PIN_IF_OFFSET_SCALE and SINGLE_PIN_IF_STATUS_CFG, where the
status of the interface can be monitored as well. PWM input signals which are out of frequency range can
be neglected. In case of wrong input data, last correct position is used or velocity and torque are set to
zero.

|Number|Motion Mode|Description|
|---|---|---|
|0|Stopped Mode|Disabling all controllers|
|1|Torque Mode|Standard Torque Control Mode|
|2|Velocity Mode|Standard Velocity Control Mode|
|3|Position Mode|Standard Position Control Mode|
|4|PRBS Flux Mode|PRBS Value is used as Target Flux Value for Ident.|
|5|PRBS Torque Mode|PRBS Value is used as Target Torque Value for Ident.|
|6|PRBS Velocity Mode|PRBS Value is used as Target Velocity Value for Ident.|
|7|PRBS Position Mode|PRBS Value is used as Target Position Value for Ident.|
|8|UQ UD Ext Mode|Voltage control mode (Software Mode)|
|9|reserved|reserved|
|10|AGPI_A Torque Mode|AGPI_A used as Target Torque value|
|11|AGPI_A Velocity Mode|AGPI_A used as Target Velocity value|
|12|AGPI_A Position Mode|AGPI_A used as Target Position value|
|13|PWM_I Torque Mode|PWM_I used as Target Torque value|
|14|PWM_I Velocity Mode|PWM_I used as Target Velocity value|
|15|PWM_I Position Mode|PWM_I used as Target Position value|



_Table 23:_ _Motion Modes_


**4.7.12** **Brake Chopper**


During regenerative braking of the motor, current is driven into the DC link. If the power frontend is not
actively controlled, the DC link voltage will rise. The brake chopper output pin (BRAKE) can be used for
control of an external brake chopper, which burns energy over a brake resistor. The BRAKE pin is set to
high for a complete PWM cycle if measured voltage is higher then ADC_VM_LIMIT_HIGH. Once active it will
be deactivated when voltage drops below ADC_VM_LIMIT_LOW. This acts like a hysteresis. BRAKE can be
deactivated by setting both registers to Zero. By setting proper values in the registers it is automatically
enabled.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 61 / 153


**4.8** **Filtering and Feed-Forward Control**


The TMC4671 uses different filters for certain target and actual values. When using standard velocity
meter, a standard velocity filter is used which is optimized for velocity signals from Hall sensors. Additional
Biquad filters can be used to suppress measurement noise or damp resonances.


**4.8.1** **Biquad Filters**


The TMC4671 uses standard biquad filters (standard IIR filter of second order, [Wikipedia](https://en.wikipedia.org/wiki/Digital_biquad_filter) Article) in the
following structure.


Y(n) = X(n) _·_ b_0 + X(n-1) _·_ b_1 + X(n-2) _·_ b_2 + Y(n-1) _·_ a_1 + Y(n-2) _·_ a_2 (33)


In this equation X(n) is the actual input sample, while Y(n-1) is the filter output of the last cycle. All coefficients are S32 values and are normalized to a Q3.29 format. Users must take care of correct parametrization of the filter. There is no built-in plausibility or stability check. All filters can be disabled or enabled
via register access. Biquad state variables are reset when parameters are changed. The TRINAMIC IDE
supports parametrization with wizards.
A standard biquad filter has the following transfer function in the Laplace-Domain:


G(s) = [b_2_cont] _[ ·][ s]_ [2][ +][ b_1_cont] _[ ·]_ [ s][ +][ b_0_cont] (34)

a_2_cont _· s_ [2] + a_1_cont _·_ s + a_0_cont


The transfer function needs to be transformed to time discrete domain by Z-Transformation and coefficients need to be normalized. This is done by the following equations.


_b_ _2_ _z_ = ( _b_ _0_ _cont · T_ [2] + 2 _· b_ _1_ _cont · T_ + 4 _· b_ _2_ _cont_ ) _/_ ( _T_ [2] _−_ 2 _· a_ _1_ _cont · T_ + 4 _· a_ _2_ _cont_ ) (35)

_b_ _1_ _z_ = (2 _· b_ _0_ _cont · T_ [2] _−_ 8 _· b_ _2_ _cont_ ) _/_ ( _T_ [2] _−_ 2 _· a_ _1_ _cont · T_ + 4 _· a_ _2_ _cont_ ) (36)

_b_ _0_ _z_ = ( _b_ _0_ _cont · T_ [2] _−_ 2 _· b_ _1_ _cont · T_ + 4 _· b_ _2_ _cont_ ) _/_ ( _T_ [2] _−_ 2 _· a_ _1_ _cont · T_ + 4 _· a_ _2_ _cont_ ) (37)

_a_ _2_ _z_ = ( _T_ [2] + 2 _· a_ _1_ _cont · T_ + 4 _· a_ _2_ _cont_ ) _/_ ( _T_ [2] _−_ 2 _· a_ _1_ _cont · T_ + 4 _· a_ _2_ _cont_ ) (38)

_a_ _1_ _z_ = (2 _· T_ [2] _−_ 8 _· a_ _2_ _cont_ ) _/_ ( _T_ [2] _−_ 2 _· a_ _1_ _cont · T_ + 4 _· a_ _2_ _cont_ ) (39)

_b_ _0 = _round_ ( _b_ _0_ _z ·_ 2 [29] ) (40)

_b_ _1 = _round_ ( _b_ _1_ _z ·_ 2 [29] ) (41)

_b_ _2 = _round_ ( _b_ _2_ _z ·_ 2 [29] ) (42)

_a_ _1 = _round_ ( _−a_ _1_ _z ·_ 2 [29] ) (43)

_a_ _2 = _round_ ( _−a_ _2_ _z ·_ 2 [29] ) (44)


while T is the sampling time according to PWM_MAX_COUNT _·_ 10 ns and variables with index z are auxiliary
variables.
A standard second order lowpass filter with given cutoff frequency _ωc_ and damping factor D has the following transfer function in the Laplace-Domain:


1
_GLP_ ( _s_ ) = _ω_ 1 _c_ [2] _[·][ s]_ [2] [+] [2] _ω_ _[ D]_ _c_ _[·][ s]_ [ + 1] (45)


Users can determine filter coefficients with the upper equations by comparing coefficients of both transfer
functions. The TMCL-IDE also provides a dimensioning tool.


There are four biquad filters in the control structure. Figure 35 illustrates their placement in the control
structure.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 62 / 153


_Figure 35:_ _Biquad Filters_


The biquad filter for the position target value is intended to be used as a low-pass filter for smoothening
position input to the control structure. It is evaluated in every PWM cycle, or down-sampled according to
the down-sampling factor for the position controller. After powering on it is disabled.
The biquad filter for the flux target value is also intended to be used as a low-pass filter for input values
from the user’s microcontroller. Sampling frequency is fixed to the PWM frequency.
The biquad filter for the torque target value can be used as a low-pass filter for bandwidth limitation
and noise suppression. Moreover, it can be designed to suppress a resonance or anti-resonance. Same
statements are correct for the velocity biquad filter. Both filters’ sampling times are fixed to the PWM
period.
The velocity target value biquad is configured as a second order low-pass with a cutoff frequency at 200 Hz

- by default at a sampling frequency of 25 kHz. Biquad filters can be activated separately.


**4.8.2** **Standard Velocity Filter**


By using the standard velocity measurement algorithm, the default velocity filter is enabled and can not
be switched off. The standard velocity filter is a low-pass filter with a cutoff frequency of 20 Hz (slope of
-20 dB/Decade). In this configuration, a new velocity is calculated at a sample rate of approx. 4369.067 Hz.
This configuration is intended to be used in low-performance applications with a simple position feedback
system like digital Hall sensors.


**4.8.3** **Feed-Forward Control Structure**


_**Note**_ Software feed forward control via offset registers is recommended, due to missing amplification possibility. Utilize feedforward to actively increase the target value of a controller besides the normal target input. For Torque/Flux use
register 0x65 PID_TORQUE_FLUX_OFFSET and for the velocity use register 0x67
PID_VELOCITY_OFFSET.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-61-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 63 / 153


**4.9** **PWM Engine**


The PWM engine takes care of converting voltage vectors to pulse width modulated (PWM) control signals.
These digital PWM signals control the gate drivers of the power stage. For a detailed description of the
PWM control registers and PWM register control bits pls. refer section 7 page 72.


The ease-of-use PWM engine requires just a couple of parameter settings. Primarily, the polarities for the
gate control signal of high-side and low-side must be set. The power on default PWM mode is 0, meaning
PWM = OFF. For operation, the centered PWM mode must be switched on by setting the PWM mode to 7.
A single bit switches the space vector PWM (SVPWM) on. For 3-phase PMSM, the SVPWM = ON gives more
effective voltage. Nevertheless, for some applications it makes sense to switch the SVPWM = OFF to keep
the star point voltage of a motor almost at rest.


**4.9.1** **PWM Polarities**


The PWM polarities register (PWM_POLARITIES) controls the polarities of the logic level gate control signals. The polarities of the gate control signals are individually programmable for low-side gate control
and for high-side gate control. The PWM polarities register controls the polarity of other control signals as well. PWM_POLARITIES[1] controls the polarity of the logic level high side gate control signal.
PWM_POLARITIES[0] controls the polarity of the logic level low side gate control signal.


_Figure 36:_ _PWM Gate Driver Control Polarities_

|PWM_POLARITIES[1...0]|PWM_HIGH_SIDE|PWM_LOW_SIDE|
|---|---|---|
|0 0|PWM_H|PWM_L|
|0 1|PWM_H|not PWM_L|
|1 0|not PWM_H|PWM_L|
|1 1|not PWM_H|not PWM_L|



_Table 24:_ _Status Flags Register_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-62-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 64 / 153


**4.9.2** **PWM Engine and associated Motor Connectors**


The PWM engine of the TMC4671 has eight gate control outputs to control up to four power MOS half
bridges. For three-phase motors three half bridges are used (U, V, W). For two-phase stepper motors four
half bridges are used for (U, V, W, Y). For DC motor control, the first two half bridges (U, V) are used.

|Gate Control Signals|FOC3: 3 Phase Motor|FOC2: 2 Phase Stepper|FOC1: Single Phase DC Motor|
|---|---|---|---|
|PWM_UX1_H<br>PWM_UX1_L|U|X1|X1|
|PWM_VX2_H<br>PWM_VX2_L|V|X2|X2|
|PWM_WY1_H<br>PWM_WY1_L|W|Y1|-|
|PWM_Y2_H<br>PWM_Y2_L|-|Y2|-|



_Table 25:_ _FOC321 Gate Control Signal Configurations_


For the DC motor current control (here named FOC1), the number of pole pairs is not relevant - in contrast
to closed loop current control of two-phase stepper motors (FOC2) and three-phase permanent magnet
motors (FOC3). For DC motor control, the number of pole pairs should be set to 1 to equal mechanical
angle and electrical angle for velocity control and for position control.


_Figure 37:_ _FOC3 (three phase motor), FOC2 (two phase stepper motor), FOC1 (single phase DC motor)_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-63-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 65 / 153


**4.9.3** **PWM Frequency**


The PWM counter maximum length register PWM_MAXCNT controls the PWM frequency. For a clock
frequency fCLK = 25 MHz, the PWM frequency fPWM[Hz] = (4.0 _·_ fCLK [Hz]) / (PWM_MAXCNT + 1). With
fCLK = 25 MHz and power-on reset (POR) default of PWM_MAXCNT=3999, the PWM frequency fPWM =
25 kHz.


_**Note**_ The PWM frequency is the fundamental frequency of the control system. It can
be changed at any time, also during motion for the classic PI controller structure.
The advanced PI controller structure is tied to the PWM frequency and integrator gains have to be changed. Please make sure to set current measurement
decimation rates to fit PWM period in high performance applications.


**4.9.4** **PWM Resolution**


The base resolution of the PWM is 12 bit internally mapped to 16 bit range. The minimal PWM increment
is 20ns due to the symmetrical PWM with 100 MHz counter frequency. MAX_PWMCNT = 4095 gives the
full resolution of 12 bit with _≈_ 25 kHz w/ fCLK=25 MHz. MAX_PWMCNT=2047 results in 11 bit resolution,
but with _≈_ 50kHz w/ fCLK=25 MHz. So the PWM_MAXCNT defines the PWM frequency, but also affects the
resolution of the PWM.


**4.9.5** **PWM Modes**


The power-on reset (POR) default of the PWM is OFF. The standard PWM scheme is the centered PWM.
Passive braking and freewheeling modes are available on demand. Please refer to section 7 concerning
the settings.


**4.9.6** **Break-Before-Make (BBM)**


One register controls BBM time for the high side, another register controls BBM time for the low side. The
BBM times are programmable in 10 ns steps. The BBM time can be set to zero for gate drivers that have
their own integrated BBM timers.


_Figure 38:_ _BBM Timing_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-64-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 66 / 153


_**Info**_ Measured BBM times at MOS-FET gates differ from programmed BBM times due
to driver delays and possible additional gate driver BBM times. The programmed
BBM times are for the digital control signals.


_**Note**_ Too short BBM times cause electrical shortcuts of the MOS-FET bridges - so called
shoot through - that short the power supply and might damage the power stage
and the power supply.


**4.9.7** **Space Vector PWM (SVPWM)**


A single bit enables the Space Vector PWM (SVPWM). No further settings are required for the space vector
PWM - just ON or OFF. The power on default for the SVPWM is OFF. Space Vector PWM can be enabled
to maximize voltage utilization in the case of an isolated star point of the motor. If the star point is not
isolated, SVPWM might cause unintended current flows through the star point. Space Vector PWM is only
used for three-phase motors. For other motors the SVPWM must be switched off.


_**Note**_ For engineering samples TMC4671-ES, the Space Vector PWM does not allow
higher voltage utilization. This is fixed for the release version TMC4671-LA.


**4.9.8** **Real- and Integer-Conversions**


The TMC4671 displays voltages and currents as integer values. The following tables show how one can
convert integer values to real values, see table 26, and the other way round, see table 27. Equation 2
in section 4.5.0.1 describes the chain of gains and introduces ADC_GAIN. This variable depends on resistance of the shuntresistor as well as the properties of the senseamplifier. It is needed for the current
conversions. The voltage conversion depends on the supply voltage VM.
Senseamps and their respective shunt resistors can deviate in their properties due to part tolerances or
aging. However, their values must still be comparable. This is done by using a scaling factor for both ADCs
in order to harmonize their signals.


ADC_GAINscaled = (ADC_GAIN _·_ [ADC][_][SCALE] ) (46)

256




















|Col1|integer to real|
|---|---|
|Iuvw,real|Iuvw_,_s16<br>ADC_GAINscaled|
|I_αβ_,real|I_αβ,_s16<br>ADC_GAINscaled|
|Idq,real|Idq_,_s16<br>ADC_GAINscaled|
|Udq,real|Udq_,_s16 _·_ VM<br>215|
|U_αβ_,real|U_αβ,_s16 _·_ VM<br>215|
|FOCuvw,real|FOCuvw_,_s16 _·_ VM<br>215|
|PWMuvw,real|PWMuvw_,_s16 _·_ VM<br>215|



_Table 26:_ _Factors for integer to real conversion_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 67 / 153










|Col1|real to integer|
|---|---|
|Iuvw,s16|Iuvw_,_real _·_ ADC_GAINscaled|
|I_αβ_,s16|I_αβ,_real _·_ ADC_GAINscaled|
|Idq,s16|Idq_,_real _·_ ADC_GAINscaled|
|Udq,s16|Udq_,_real _·_ 215<br>VM|
|U_αβ_,s16|U_αβ,_real _·_ 215<br>VM|
|FOCuvw,s16|FOCuvw_,_real _·_ 215<br>VM|
|PWMuvw,s16|PWMdq_,_real _·_ 215<br>VM|



_Table 27:_ _Factors for real to integer conversion_


The PWM value defines the outputvoltage. It is calculated using the content of register INTERIM_DATA
while INTERIM_ADDR is 0x11 or 0x12. The s16 PWM value is converted to an u16 value by adding 0x8000.
Equation 47 applies for the highside PWM when connected to a DC- or Stepper-motor as well as the three
phases of a BLDC-motor when spacevector pwm is inactive:


Uclamp = (PWMuvw _,_ s16 + 0x8000) _·_ [V][M] (47)

2 [16]


Equation 48 describes the outputvoltage on the clamps for the lowside PWM when connected to a DC- or
Stepper-motor:

Uclamp = ( _−_ PWMuxwy _,_ s16 + 0x8000) _·_ [V][M] (48)

2 [16]

The following equation describes the integer to real transformation for three-phase spacevector-PWM:


FOCMIN= min(FOCu _,_ FOCv _,_ FOCw)



FOCMAX= max(FOCu _,_ FOCv _,_ FOCw)



(49)



Uclamp _,_ uvw= ( ~~_√_~~ [2]



3 _[·]_ [ (PWM][uvw] _[,]_ [s16] _[ −]_ [FOC][MAX][ + FOC] 2 [MIN]




[ + FOC][MIN]

) + 0x8000) _·_ [V][M]
2 2 [16]



2 [16]


## **5 Safety Functions**

Different safety functions are integrated and mapped to status bits. A programmable mask register selects bits for activation of the STATUS output.


Internal hardware limiters for real time clipping and monitoring of interim values are available. LIMIT or
LIMITS is part of register names of registers associated to internal limiters. Please refer to table 28.

|Bit|Source|
|---|---|
|0|pid_x_target_limit|
|1|pid_x_target_ddt_limit|
|2|pid_x_errsum_limit|
|3|pid_x_output_limit|
|4|pid_v_target_limit|



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 68 / 153

|5|pid_v_target_ddt_limit|
|---|---|
|6|pid_v_errsum_limit|
|7|pid_v_output_limit|
|8|pid_id_target_limit|
|9|pid_id_target_ddt_limit|
|10|pid_id_errsum_limit|
|11|pid_id_output_limit|
|12|pid_iq_target_limit|
|13|pid_iq_target_ddt_limit|
|14|pid_iq_errsum_limit|
|15|pid_iq_output_limit|
|16|ipark_cirlim_limit_u_d|
|17|ipark_cirlim_limit_u_q|
|18|ipark_cirlim_limit_u_r|
|19|not_PLL_locked|
|20|ref_sw_r|
|21|ref_sw_h|
|22|ref_sw_l|
|23|——-|
|24|pwm_min|
|25|pwm_max|
|26|adc_i_clipped|
|27|adc_aenc_clipped|
|28|ENC_N|
|29|ENC2_N|
|30|AENC_N|
|31|reserved|



_Table 28:_ _Status Flags Register_


All controllers have input limiters as offsets can be added to target values and they can be limited to
remain in certain ranges. Also all controller outputs can be limited and the integrating parts (error sum)
of the PI controllers are also limited to controller outputs. If d/dt-limiters are enabled they are also capable
of limiting target values.
If one of these limiters gets active, the flag will go to high state. This is usually a normal operation, when
controllers are working on the borders of their working area. With STATUS_MASK register corresponding
flags can be activated.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 69 / 153


Other status flags go to high state whether the voltage limitation is reached (circular limiter in iPark transformation) or PWM is saturated (pwm_min and pwm_max). This is also usual operation as the current
controller has to deal with voltage limitation at high velocity operation.
The user can also use the status output to generate an IRQ on reference switch or N-channel of encoder.
Also ADC clipping can be monitored which is a good indicator of wrong or faulty behavior.
Remaining wd_error status flag indicates an error on the clock input of the TMC4671 (see following section).
Status flags register can be written directly. It is not possible to clear individual bits.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 70 / 153

## **6 FOC Setup - How to Turn a Motor**


This section summarizes the basic steps that are required to turn a motor with TMC4671. The wizard of the
TMCL-IDE guides the user through theses basic steps. Schematics and Layout of the TMC4671 evaluation
kit are open source and available for download from www.trinamic.com


_**Note**_ TRINAMIC recommends to use a TMC4671 evaluation kit together with the TMCLIDE with its integrated wizards for initial evaluation and setup.


[In order to create own application software please check TRINAMIC’s API to reduce software development](https://github.com/trinamic/TMC-API)
efforts.


**6.1** **Select Motor Type**


The TMC4671 supports closed loop control of single phase DC motors, stepper motors, and three phase
motors. The selection of the motor type defines the configuration of the gate control channels for the
power stage and either the usage or bypass of FOC transformations (Clarke, Park, iPark, iClark).


**6.1.1** **FOC1 Setup - How to Turn a Single Phase DC Motor**


In case of DC motor, the mechanical commutator of the DC motor realizes something like mechanical field
oriented control where the TMC4671 just realizes closed loop current control of the DC motor. From FOC
point of view, the FOC converts a brushless motor (BLDC) resp. Permanent Magnet Synchronous Motor
(PMSM) into a closed loop current controlled DC motor.


From closed loop velocity control point of view and from closed loop position control point of view there
is no difference between electronically FOC controlled BLDC motor or PMSM motor and a mechanical
commutated DC motor with electronic closed loop current control.


**6.1.2** **FOC2 Setup - How to Turn a Two Phase Motor (Stepper)**


The TMC4671 is able to turn a two-phase stepper motor with FOC by internal skip of Clarke transformation
and iClarke transformation. A special feature of stepper motors is the high number of pole pairs (NPP)
that are typical 50. For stepper motors it is usual to give the number of full steps (FS) per revolution, with
NPP = (FS/revolution) / 4. A stepper with 200 full steps per revolution has 50 pole pairs.


**6.1.3** **FOC3 Setup - How to Turn a Three Phase Motor (PMSM or BLDC)**


A three phase motor is the classical FOC controlled brushless motor. Users have to take care concerning
number of pole pairs (NPP) and the number of poles (NP) with NPP = NP/2.


**6.2** **Set Number of Pole Pairs (NPP)**


The number of (magnetic) pole pairs (NPP) is characteristic for each motor and it is essential for commutation of two phase motors and three phase motors with FOC. For DC motor the NPP is not important for
commutation itself, but is should be set to one to have same scaling for electrical angle and mechanical
angle.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 71 / 153


**6.3** **Run Motor Open Loop**


Initial turning a motor open loop is useful for determination of the association between phase voltage,
phase currents and for position sensor setup. Position sensors that are mounted on a motor might have
an opposite direction of rotation compared to the motor. The same direction of rotation is essential for
the FOC. In addition, the phase shift between rotor angle and angle that is measured by a position sensor
needs to be zero in best case. Otherwise the motor is operated at lower efficiency or turns in wrong
direction which causes instability.


**6.3.1** **Determination of Association between Phase Voltage and Phase Currents**


For starters, the motor should be turned open loop to measure ADC offsets and set ADC scaler offset.
Additionally, the open loop turn is useful to validate (or to determine) the association between motor
phase currents and motor phase terminal voltages. This association is essential for the FOC. With proper
ADC channel selection setup, voltage U_UX1 is in phase with current I_UX1, voltage U_VX2 is in phase
with current I_VX2, and voltage U_WY1 is in phase with I_WY1. For two phase stepper motor, the voltage
U_Y2 is in phase with current I_Y2. Only two currents are measured and the other current is calculated by
TMC4671. For DC motor only one current is measured.


**6.3.2** **Determination of Direction of Rotation and Phase Shift of Angles**


For absolute position sensors like Hall sensors, the phase shift an the direction of rotation only need to
be determined once initially. For relative position sensors, like incremental encoders, the direction of
turning needs to be determined everytime after power cycle. The relative orientation between measured
incremental encoder angle and rotor angle needs to be determined on each power-up.


**6.4** **Selection of Position Sensors**


For closed loop operation, the type of encoder (digital hall, ABN encoder, analog Hall, SinCos) needs to
be set. For analog Hall signals or analog incremental encoders the user needs to adjust the analog ADC
channels for the analog encoders - similar to ADC offset and ADC scaling as for current measuring ADC
channels. The TMC4671 allows the selection of different types of position sensors for different tasks. One
position sensor is for the inner FOC closed loop current control loop.


**6.4.1** **Selection of FOC sensor for PHI_E**


One sensor needs to be selected for the FOC to measure the electrical angle PHI_E. This sensor is used
for the inner closed loop control loop for closed loop current control.


**6.4.2** **Selection of sensor for VELOCITY**


One sensor needs to be selected for measurement of velocity. This can be the sensor selected for measurement of PHI_E but it is more common to use the mechanical angle PHI_M for measurement of velocity.
Using electrical angles can give advantages for applications with slow motion for NPP more than one because the minimum velocity in RPM [revolutions per minute] is one and the electrical angles have higher
speed than mechanical angles.


**6.4.3** **Selection of sensor for POSITION**


One sensor needs to be selected for measurement of position of the rotor, the angle of the rotor. This can
be the sensor selected for measurement PHI_E but it is more usual to use the mechanical angle PHI_M for
measurement of position. For stepper motors it might make sense to select the electrical angle PHI_E for


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 72 / 153


positioning to have a benefit from higher resolution using electrical angles. This is because each period electrical or mechanical - is normalized to 2 [16] = 65536 positions.


**6.5** **Modes of Operation - (Open Loop), Torque, Velocity, Positioning**


The TMC4671 can operate in torque mode, velocity mode, or position mode. The control loops (current,
velocity, position) are cascaded, thus the outer loops depend on the tuning of the inner loops. So, the
current loop must be adjusted first. The velocity loop must be adjusted after the current control loop is
adjusted. The position control loop must be adjusted last.


**6.6** **Controller Tuning**


PI controller tuning is described throughout the control theory literature. In general there are two main
strategies to tune the controllers. First strategy is to observe controller step response for different parameter sets and tune parameters to fit dynamics and settling time. With this approach sampling target and
actual value as well as controller output (check for saturation) at fixed frequency is recommended. The
USB-2-RTMI adapter in combination with the TMCL-IDE provide tuning tools to support this strategy.
Another approach is to identify controller plant parameters and calculate controller parameters from
these parameters. This is also supported by the TMCL-IDE for the current control loop. For the other
control loops the first strategy is recommended.

## **7 Register Map**


The TMC4671 has an register address range of 128 addresses with registers up to 32 bit data width. Some
registers hold 32 bit data fields, some hold 2 x 16 bit data fileds and other hold combinations of different
data fields with individual data types. Data fields need to extracted by masking and shifting after read from
a TMC4671 register within the application. Data fields need to be composed by masking and shifting by
the application before writing into a TMC4671 register. [Please check TRINAMIC’s API to reduce software](https://github.com/trinamic/TMC-API)
development efforts. This section describes the register bank of the TMC4671.


Section 7.1 gives an overview over all registers. It is is intended to give an initial over view of all registers.


Section 7.2 is the detailed reference of all registers and the register fields.


Section 7.3 gives the description of power-on-reset default values of all registers.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 73 / 153


**7.1** **Register Map - Overview**


Registers in TMC4671 have different purposes. Some registers are used for test only, other can be used
to monitor internal states (e.g. ADC values). Most registers are only accessed during initialisation (e.g.
calibration or control parameters). Control registers are used for input of target values to controllers and
should be updated regularly according to chosen motion modes (e.g PID_VELOCITY_TARGET should be
updated in velocity mode). If users don’t use a certain functional block they don’t need to parametrize it.


The TMC4671 has an address space of 128 addresses. In order to display more then 128 registers, so called
stacked registers were added. These are CHIPINFO_DATA, ADC_RAW_DATA, PID_ERROR_DATA, CONFIG_DATA
and INTERIM_DATA. These data registers display or give access to different subregisters according to their
corresponding address registers (CHIPINFO_ADDR, ADC_RAW_ADDR, PID_ERROR_ADDR, CONFIG_ADDR
and INTERIM_ADDR). Read access to a subregister requires a write access to address register and a read
access to the data register.

|Address|Registername|Access|Usage|
|---|---|---|---|
|0x00h|CHIPINFO_DATA|R|Test|
|0x01h|CHIPINFO_ADDR|RW|Test|
|0x02h|ADC_RAW_DATA|R|Monitor|
|0x03h|ADC_RAW_ADDR|RW|Monitor|
|0x04h|dsADC_MCFG_B_MCFG_A|RW|Init|
|0x05h|dsADC_MCLK_A|RW|Init|
|0x06h|dsADC_MCLK_B|RW|Init|
|0x07h|dsADC_MDEC_B_MDEC_A|RW|Init|
|0x08h|ADC_I1_SCALE_OFFSET|RW|Init|
|0x09h|ADC_I0_SCALE_OFFSET|RW|Init|
|0x0Ah|ADC_I_SELECT|RW|Init|
|0x0Bh|ADC_I1_I0_EXT|RW|Test|
|0x0Ch|DS_ANALOG_INPUT_STAGE_CFG|RW|Test|
|0x0Dh|AENC_0_SCALE_OFFSET|RW|Init|
|0x0Eh|AENC_1_SCALE_OFFSET|RW|Init|
|0x0Fh|AENC_2_SCALE_OFFSET|RW|Init|
|0x11h|AENC_SELECT|RW|Init|
|0x12h|ADC_IWY_IUX|R|Monitor|
|0x13h|ADC_IV|R|Monitor|
|0x15h|AENC_WY_UX|R|Monitor|
|0x16h|AENC_VN|R|Monitor|
|0x17h|PWM_POLARITIES|RW|Init|
|0x18h|PWM_MAXCNT|RW|Init|
|0x19h|PWM_BBM_H_BBM_L|RW|Init|
|0x1Ah|PWM_SV_CHOP|RW|Init|



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 74 / 153

|Address|Registername|Access|Usage|
|---|---|---|---|
|0x1Bh|MOTOR_TYPE_N_POLE_PAIRS|RW|Init|
|0x1Ch|PHI_E_EXT|RW|Test|
|0x1Fh|OPENLOOP_MODE|RW|Init|
|0x20h|OPENLOOP_ACCELERATION|RW|Init|
|0x21h|OPENLOOP_VELOCITY_TARGET|RW|Init|
|0x22h|OPENLOOP_VELOCITY_ACTUAL|RW|Monitor|
|0x23h|OPENLOOP_PHI|RW|Monitor/Test|
|0x24h|UQ_UD_EXT|RW|Init/Test|
|0x25h|ABN_DECODER_MODE|RW|Init|
|0x26h|ABN_DECODER_PPR|RW|Init|
|0x27h|ABN_DECODER_COUNT|RW|Init/Test/Monitor|
|0x28h|ABN_DECODER_COUNT_N|RW|Init/Test/Monitor|
|0x29h|ABN_DECODER_PHI_E_PHI_M_OFFSET|RW|Init|
|0x2Ah|ABN_DECODER_PHI_E_PHI_M|R|Monitor|
|0x2Ch|ABN_2_DECODER_MODE|RW|Init|
|0x2Dh|ABN_2_DECODER_PPR|RW|Init|
|0x2Eh|ABN_2_DECODER_COUNT|RW|Init/Test/Monitor|
|0x2Fh|ABN_2_DECODER_COUNT_N|RW|Init/Test/Monitor|
|0x30h|ABN_2_DECODER_PHI_M_OFFSET|RW|Init|
|0x31h|ABN_2_DECODER_PHI_M|R|Monitor|
|0x33h|HALL_MODE|RW|Init|
|0x34h|HALL_POSITION_060_000|RW|Init|
|0x35h|HALL_POSITION_180_120|RW|Init|
|0x36h|HALL_POSITION_300_240|RW|Init|
|0x37h|HALL_PHI_E_PHI_M_OFFSET|RW|Init|
|0x38h|HALL_DPHI_MAX|RW|Init|
|0x39h|HALL_PHI_E_INTERPOLATED_PHI_E|R|Monitor|
|0x3Ah|HALL_PHI_M|R|Monitor|
|0x3Bh|AENC_DECODER_MODE|RW|Init|
|0x3Ch|AENC_DECODER_N_THRESHOLD|RW|Init|
|0x3Dh|AENC_DECODER_PHI_A_RAW|R|Monitor|
|0x3Eh|AENC_DECODER_PHI_A_OFFSET|RW|Init|
|0x3Fh|AENC_DECODER_PHI_A|R|Monitor|
|0x40h|AENC_DECODER_PPR|RW|Init|



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 75 / 153

|Address|Registername|Access|Usage|
|---|---|---|---|
|0x41h|AENC_DECODER_COUNT|R|Monitor|
|0x42h|AENC_DECODER_COUNT_N|RW|Monitor/Init|
|0x45h|AENC_DECODER_PHI_E_PHI_M_OFFSET|RW|Init|
|0x46h|AENC_DECODER_PHI_E_PHI_M|R|Monitor|
|0x4Dh|CONFIG_DATA|RW|Init|
|0x4Eh|CONFIG_ADDR|RW|Init|
|0x50h|VELOCITY_SELECTION|RW|Init|
|0x51h|POSITION_SELECTION|RW|Init|
|0x52h|PHI_E_SELECTION|RW|Init|
|0x53h|PHI_E|R|Monitor|
|0x54h|PID_FLUX_P_FLUX_I|RW|Init|
|0x56h|PID_TORQUE_P_TORQUE_I|RW|Init|
|0x58h|PID_VELOCITY_P_VELOCITY_I|RW|Init|
|0x5Ah|PID_POSITION_P_POSITION_I|RW|Init|
|0x5Dh|PIDOUT_UQ_UD_LIMITS|RW|Init|
|0x5Eh|PID_TORQUE_FLUX_LIMITS|RW|Init|
|0x60h|PID_VELOCITY_LIMIT|RW|Init|
|0x61h|PID_POSITION_LIMIT_LOW|RW|Init|
|0x62h|PID_POSITION_LIMIT_HIGH|RW|Init|
|0x63h|MODE_RAMP_MODE_MOTION|RW|Init|
|0x64h|PID_TORQUE_FLUX_TARGET|RW|Control|
|0x65h|PID_TORQUE_FLUX_OFFSET|RW|Control|
|0x66h|PID_VELOCITY_TARGET|RW|Control|
|0x67h|PID_VELOCITY_OFFSET|RW|Control|
|0x68h|PID_POSITION_TARGET|RW|Control|
|0x69h|PID_TORQUE_FLUX_ACTUAL|R|Monitor|
|0x6Ah|PID_VELOCITY_ACTUAL|R|Monitor|
|0x6Bh|PID_POSITION_ACTUAL|RW|Monitor/Init|
|0x6Ch|PID_ERROR_DATA|R|Test|
|0x6Dh|PID_ERROR_ADDR|RW|Test|
|0x6Eh|INTERIM_DATA|RW|Monitor|
|0x6Fh|INTERIM_ADDR|RW|Monitor|
|0x75h|ADC_VM_LIMITS|RW|Init|
|0x76h|TMC4671_INPUTS_RAW|R|Test/Monitor|



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 76 / 153

|Address|Registername|Access|Usage|
|---|---|---|---|
|0x77h|TMC4671_OUTPUTS_RAW|R|Test/Monitor|
|0x78h|STEP_WIDTH|RW|Init|
|0x79h|UART_BPS|RW|Init|
|0x7Bh|GPIO_dsADCI_CONFIG|RW|Init|
|0x7Ch|STATUS_FLAGS|RW|Monitor|
|0x7Dh|STATUS_MASK|RW|Monitor|



_Table 29:_ _TMC4671 Registers_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 77 / 153


**7.2** **Register Map - Functional Description**


**DATA TYPE**


version information of the accessed IC. It can be used for test
of communication.


date stamp yyyymmdd).


time stamp –hhmmss)


displayed information in register
CHIPINFO_DATA.


1: SI_VERSION


2: SI_DATE


3: SI_TIME


4: SI_VARIANT


5: SI_BUILD


ues. Th displayed registers can be
switched by register ADC_RAW_
ADDR.

|NAME|(BIT MASK)|
|---|---|
|CHIPINFO_DATA<br>SI_TYPE<br>SI_VERSION<br>SI_DATE<br>SI_TIME<br>SI_VARIANT<br>SI_BUILD|u32(31:0)<br>u32(31:0)<br>u32(31:0)<br>u32(31:0)<br>u32(31:0)<br>u32(31:0)|
|CHIPINFO_ADDR<br>CHIP_INFO_ADDRESS|u8(7:0)|
|ADC_RAW_DATA<br>ADC_I0_RAW<br>ADC_I1_RAW<br>ADC_VM_RAW<br>ADC_AGPI_A_RAW<br>ADC_AGPI_B_RAW<br>ADC_AENC_UX_RAW<br>ADC_AENC_VN_RAW<br>ADC_AENC_WY_RAW|u16(15:0)<br>u16(31:16)<br>u16(15:0)<br>u16(31:16)<br>u16(15:0)<br>u16(31:16)<br>u16(15:0)<br>u16(31:16)|



0x03h ADC_RAW_ADDR This register is used to change
displayed information in register
ADC_RAW_DATA.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 78 / 153

|Col1|ADC_RAW_ADDR|u8(7:0)|0: ADC_I1_RAW & ADC_I0_RAW<br>1: ADC_AGPI_A_RAW & ADC_VM_<br>RAW<br>2: ADC_AENC_UX_RAW & ADC_<br>AGPI_B_RAW<br>3: ADC_AENC_WY_RAW & ADC_<br>AENC_VN_RAW|
|---|---|---|---|
|0x04h|dsADC_MCFG_B_MCFG_A<br>cfg_dsmodulator_a<br>mclk_polarity_a<br>mdat_polarity_a<br>sel_nclk_mclk_i_a<br>cfg_dsmodulator_b<br>mclk_polarity_b<br>mdat_polarity_b<br>sel_nclk_mclk_i_b|u2(1:0)<br>bit(2)<br>bit(3)<br>bit(4)<br>u2(17:16)<br>bit(18)<br>bit(19)<br>bit(20)|This register is used to conﬁgure<br>internal ADCs (delta sigma modu-<br>lators). Don’t modify if you want<br>to use internal Delta Sigma modu-<br>lators (Standard use case).<br>0: int. dsMOD<br>1: ext. MCLK input<br>2: ext. MCLK output<br>3: ext. CMP<br>0: oﬀ<br>1: on<br>0: oﬀ<br>1: on<br>0: oﬀ<br>1: on<br>0: int. dsMOD<br>1: ext. MCLK input<br>2: ext. MCLK output<br>3: ext. CMP<br>0: oﬀ<br>1: on<br>0: oﬀ<br>1: on<br>0: oﬀ<br>1: on|
|0x05h|dsADC_MCLK_A<br>dsADC_MCLK_A|u32(31:0)|This register is used to modify<br>Delta Sigma modulator clock. Do<br>not modify if you use internal<br>delta sigma modulators (Standard<br>use case).<br>dsADC_MCLK_A = (231_·_fMCLK)<br>fCLK|



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 79 / 153

|0x06<br>h|dsADC_MCLK_B<br>dsADC_MCLK_B|u32(31:0)|This register is used to modify<br>Delta Sigma modulator clock. Do<br>not modify if you use internal<br>delta sigma modulators (Standard<br>use case).<br>(231·fMCLK)<br>dsADC_MCLK_B =<br>fCLK|
|---|---|---|---|
|0x07h|dsADC_MDEC_B_MDEC_A<br>dsADC_MDEC_A<br>dsADC_MDEC_B|u16(15:0)<br>u16(31:16)|This register is used to change dec-<br>imation rates of SINC3 ﬁlters for<br>Delta Sigma modulators. Set val-<br>ues according to actual PWM fre-<br>quency.<br>See functional descrip-<br>tion of ADC engine.<br>0: PWM synchronous, others ac-<br>cording to register content<br>0: PWM synchronous, others ac-<br>cording to register content|
|0x08h|ADC_I1_SCALE_OFFSET<br>ADC_I1_OFFSET<br>ADC_I1_SCALE|u16(15:0)<br>s16(31:16)|This register is used to set calibra-<br>tion data for ADC channel I1 (Oﬀ-<br>set and amplitude correction).<br>Oﬀset for current ADC channel 1.<br>Scaling factor for current ADC<br>channel 1.|
|0x09h|ADC_I0_SCALE_OFFSET<br>ADC_I0_OFFSET<br>ADC_I0_SCALE|u16(15:0)<br>s16(31:16)|This register is used to set calibra-<br>tion data for ADC channel I0 (Oﬀ-<br>set and amplitude correction).<br>Oﬀset for current ADC channel 0.<br>Scaling factor for current ADC<br>channel 0.|
|0x0Ah|ADC_I_SELECT<br>ADC_I0_SELECT|u8(7:0)|This register is used to assign cor-<br>rect ADC channel to PWM output<br>channel. For each FOC input cur-<br>rent either an ADC value or the<br>calculated sum of the currents (I2)<br>can be assigned to match internal<br>data processing to power stage<br>design.<br>Select input for raw current ADC_<br>I0_RAW.<br>0:<br>ADCSD_I0_RAW (sigma delta<br>ADC)<br>1:<br>ADCSD_I1_RAW (sigma delta<br>ADC)<br>2: ADC_I0_EXT (from register)<br>3: ADC_I1_EXT (from register)|



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 80 / 153


ADC_I1_SELECT u8(15:8) Select input for raw current ADC_
I1_RAW.


0: ADCSD_I0_RAW (sigma delta
ADC)


1: ADCSD_I1_RAW (sigma delta
ADC)


2: ADC_I0_EXT (from register)


3: ADC_I1_EXT (from register)


ADC_I_UX_SELECT u2(25:24) 0: UX = ADC_I0 (default)


1: UX = ADC_I1


2: UX = ADC_I2


ADC_I_V_SELECT u2(27:26) 0: V = ADC_I0


1: V = ADC_I1 (default)


2: V = ADC_I2


ADC_I_WY_SELECT u2(29:28) 0: WY = ADC_I0


1: WY = ADC_I1


2: WY = ADC_I2 (default)


0x0Bh ADC_I1_I0_EXT This register can be used to write
ADC values via SPI in case external ADCs are used or controller
cascade function shall be tested.
using external ADCs will probably
effect control performance is not
recommended.


ADC_I0_EXT u16(15:0) Register for write of ADC_I0 value
from external source (eg. CPU).


ADC_I1_EXT u16(31:16) Register for write of ADC_I1 value
from external source (eg. CPU).


0x0Ch DS_ANALOG_INPUT_STAGE_CFG This register is used to configure
ADC channels for different input
configurations and test modes.


ADC_I0 u4(3:0) 0: INP vs. INN


1: GND vs. INN


2: VDD/4


3: 3*VDD/4


4: INP vs. GND


5: VDD/2


6: VDD/4


7: 3*VDD/4


ADC_I1 u4(7:4) 0: INP vs. INN


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 81 / 153


1: GND vs. INN


2: VDD/4


3: 3*VDD/4


4: INP vs. GND


5: VDD/2


6: VDD/4


7: 3*VDD/4


ADC_VM u4(11:8) 0: INP vs. INN


1: GND vs. INN


2: VDD/4


3: 3*VDD/4


4: INP vs. GND


5: VDD/2


6: VDD/4


7: 3*VDD/4


ADC_AGPI_A u4(15:12) 0: INP vs. INN


1: GND vs. INN


2: VDD/4


3: 3*VDD/4


4: INP vs. GND


5: VDD/2


6: VDD/4


7: 3*VDD/4


ADC_AGPI_B u4(19:16) 0: INP vs. INN


1: GND vs. INN


2: VDD/4


3: 3*VDD/4


4: INP vs. GND


5: VDD/2


6: VDD/4


7: 3*VDD/4


ADC_AENC_UX u4(23:20) 0: INP vs. INN


1: GND vs. INN


2: VDD/4


3: 3*VDD/4


4: INP vs. GND


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 82 / 153

|Col1|ADC_AENC_VN<br>ADC_AENC_WY|u4(27:24)<br>u4(31:28)|5: VDD/2<br>6: VDD/4<br>7: 3*VDD/4<br>0: INP vs. INN<br>1: GND vs. INN<br>2: VDD/4<br>3: 3*VDD/4<br>4: INP vs. GND<br>5: VDD/2<br>6: VDD/4<br>7: 3*VDD/4<br>0: INP vs. INN<br>1: GND vs. INN<br>2: VDD/4<br>3: 3*VDD/4<br>4: INP vs. GND<br>5: VDD/2<br>6: VDD/4<br>7: 3*VDD/4|
|---|---|---|---|
|0x0Dh|AENC_0_SCALE_OFFSET<br>AENC_0_OFFSET<br>AENC_0_SCALE|u16(15:0)<br>s16(31:16)|This register is used to set calibra-<br>tion data for ADC channel AENC 0<br>(Oﬀset and amplitude correction).<br>Oﬀset for Analog Encoder ADC<br>channel 0.<br>Scaling factor for Analog Encoder<br>ADC channel 0.|
|0x0Eh|AENC_1_SCALE_OFFSET<br>AENC_1_OFFSET<br>AENC_1_SCALE|u16(15:0)<br>s16(31:16)|This register is used to set calibra-<br>tion data for ADC channel AENC 1<br>(Oﬀset and amplitude correction).<br>Oﬀset for Analog Encoder ADC<br>channel 1.<br>Scaling factor for Analog Encoder<br>ADC channel 1.|
|0x0Fh|AENC_2_SCALE_OFFSET<br>AENC_2_OFFSET<br>AENC_2_SCALE|u16(15:0)<br>s16(31:16)|This register is used to set calibra-<br>tion data for ADC channel AENC 2<br>(Oﬀset and amplitude correction).<br>Oﬀset for Analog Encoder ADC<br>channel 2.<br>Scaling factor for Analog Encoder<br>ADC channel 2.|



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 83 / 153

|0x11<br>h|AENC_SELECT<br>AENC_0_SELECT<br>AENC_1_SELECT<br>AENC_2_SELECT|u8(7:0)<br>u8(15:8)<br>u8(23:16)|This register is used to select cor-<br>rect ADC to compensate wiring<br>twists.<br>Select analog encoder ADC chan-<br>nel for raw analog encoder signal<br>AENC_0_RAW.<br>0: <AENC_UX_RAW><br>1: AENC_VN_RAW<br>2: AENC_WY_RAW<br>Select analog encoder ADC chan-<br>nel for raw analog encoder signal<br>AENC_1_RAW.<br>0: AENC_UX_RAW<br>1: <AENC_VN_RAW><br>2: AENC_WY_RAW<br>Select analog encoder ADC chan-<br>nel for raw analog encoder signal<br>AENC_2_RAW.<br>0: AENC_UX_RAW<br>1: AENC_VN_RAW<br>2: <AENC_WY_RAW>|
|---|---|---|---|
|0x12h|ADC_IWY_IUX<br>ADC_IUX<br>ADC_IWY|s16(15:0)<br>s16(31:16)|This<br>register<br>can<br>be<br>used<br>to<br>monitor<br>phase<br>current<br>values<br>(oﬀset-compensated, scaled and<br>correctly assigned).<br>Register of scaled current ADC<br>value including signed added oﬀ-<br>set as input for the FOC.<br>Register of scaled current ADC<br>value including signed added oﬀ-<br>set as input for the FOC.|
|0x13h|ADC_IV<br>ADC_IV|s16(15:0)|This<br>register<br>can<br>be<br>used<br>to<br>monitor phase current ADC_IV<br>(oﬀset-compensated, scaled and<br>correctly assigned).<br>Register of scaled current ADC<br>value including signed added oﬀ-<br>set as input for the FOC.|
|0x15h|AENC_WY_UX||This register displays AENC in-<br>put signals (oﬀset-compensated,<br>scaled and correctly assigned).|



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 84 / 153


AENC_UX s16(15:0) Register of scaled analog encoder
value including signed added offset as input for the interpolator.


AENC_WY s16(31:16) Register of scaled analog encoder
value including signed added offset as input for the interpolator.


input signal AENC_VN (offsetcompensated, scaled and correctly assigned).


value including signed added offset as input for the interpolator.


PWM output signal to match gate
driver.


0: off


1: on


0: off


1: on


PWM output frequency.


PWM frequency is fPWM[Hz]
= 100MHz/(PWM_MAXCNT+1)


for PWM output signals. BBM time
must be matched power stage
needs to avoid cross conduction
in half bridge.


L[10ns] for low side MOS-FET gate
control


H[10ns] for high side MOS-FET
gate control

|AENC_VN<br>AENC_VN|s16(15:0)|
|---|---|
|PWM_POLARITIES<br>PWM_POLARITIES[0]<br>PWM_POLARITIES[1]|bit(0)<br>bit(1)|
|PWM_MAXCNT<br>PWM_MAXCNT|u12(11:0)|
|PWM_BBM_H_BBM_L<br>PWM_BBM_L<br>PWM_BBM_H|u8(7:0)<br>u8(15:8)|



0x1Ah PWM_SV_CHOP This register is used to enable
PWM, set different PWM test
modes and switch on the SVPWM
feature for higher voltage utilization (BLDC/PMSM only).


PWM_CHOP u8(7:0) PWM chopper mode, defining
how to chopper


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 85 / 153


0: off, free running


1: off, low side permanent = ON


2: off, high side permanent = ON


3: off, free running


4: off, free running


5: low side chopper, high side off


6: high side chopper, low side off


7: centered PWM for FOC


PWM_SV bit(8) use Space Vector PWM


0: Space Vector PWM disabled


1: Space Vector PWM enabled


type and number of pole pairs.


tor for calcualtion phi_e = phi_m _·_
N_POLE_PAIRS.


1: Single phase DC


2: Two phase Stepper


3: Three phase BLDC


trical angle for SW mode when encoder is connected to MCU and
not to TMC4671.


ternal writing into this register.


rection of openloop angle.


0: positive


1: negative


celeration when openloop angle
velocity should change.

|MOTOR_TYPE_N_POLE_PAIRS<br>N_POLE_PAIRS<br>MOTOR_TYPE|u16(15:0)<br>u8(23:16)|
|---|---|
|PHI_E_EXT<br>PHI_E_EXT|s16(15:0)|
|OPENLOOP_MODE<br>OPENLOOP_PHI_DIRECTION|bit(12)|
|OPENLOOP_ACCELERATION<br>OPENLOOP_ACCELERATION|u32(31:0)|



0x21h OPENLOOP_VELOCITY_TARGET This register is used to set a target
velocity for openloop angle generator. The velocity is ramped
up and down according to OPENLOOP_ACCELERATION and PID_
VELOCITY_LIMIT.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 86 / 153


loop angle velocity in RPM.


ator.


put of openloop angle generator


mapped to electrical angel phi_e
or mechanical angle phi_m).


values for openllop current control mode (UQ_UD_EXT_MODE).


open loop voltage control mode,
usefull during system setup, U_D
component.


open loop voltage control mode,
usefull during system setup, U_Q
component.

|OPENLOOP_VELOCITY_TARGET|s32(31:0)|
|---|---|
|OPENLOOP_VELOCITY_ACTUAL<br>OPENLOOP_VELOCITY_ACTUAL|s32(31:0)|
|OPENLOOP_PHI<br>OPENLOOP_PHI|s16(15:0)|
|UQ_UD_EXT<br>UD_EXT<br>UQ_EXT|s16(15:0)<br>s16(31:16)|



0x25h ABN_DECODER_MODE This register is used to configure
decoder input signals and N pulse
action as well as count direction.


apol bit(0) Polarity of A pulse.


0: off


1: on


bpol bit(1) Polarity of B pulse.


0: off


1: on


npol bit(2) Polarity of N pulse.


0: off


1: on


use_abn_as_n bit(3) N and A and B


0: Ignore A and B polarity with
Npulse = N


1: Npulse = N and A and B


cln bit(8) Write direction at Npulse event
between ABN_DECODER_COUNT_
N and ABN_DECODER_COUNT.


0: COUNT => COUNT_N


1: COUNT_N => COUNT


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 87 / 153


direction bit(12) Decoder count direction.


0: positive


1: negative


number of encoder.


revolution.


count of encoder steps. It can be
overwritten for initialization.


coder engine counts modulo (decoder_ppr).


value at last N pulse event. It can
also be used to overwrite Decoder
count at N pulse evenet accroding
to decoder mode register setting.


when N pulse clears decoder_
count also decoder_count_n is 0.


sets for electrical and mechanical
angle calculated from decoder.


shift (rotate) angle DECODER_PHI_
M.


shift (rotate) angle DECODER_PHI_
E.


values for ABN encoder.


DECODER_COUNT                         - 2^16 / ABN_
DECODER_PPR + ABN_DECODER_
PHI_M_OFFSET;


DECODER_PHI_M                          - N_POLE_
PAIRS_) + ABN_DECODER_PHI_E_
OFFSET

|ABN_DECODER_PPR<br>ABN_DECODER_PPR|u24(23:0)|
|---|---|
|ABN_DECODER_COUNT<br>ABN_DECODER_COUNT|u24(23:0)|
|ABN_DECODER_COUNT_N<br>ABN_DECODER_COUNT_N|u24(23:0)|
|ABN_DECODER_PHI_E_PHI_M_OFFSET<br>ABN_DECODER_PHI_M_OFFSET<br>ABN_DECODER_PHI_E_OFFSET|s16(15:0)<br>s16(31:16)|
|ABN_DECODER_PHI_E_PHI_M<br>ABN_DECODER_PHI_M<br>ABN_DECODER_PHI_E|s16(15:0)<br>s16(31:16)|



0x2Ch ABN_2_DECODER_MODE This register is used to configure
decoder input signals and N pulse
action as well as count direction.


apol bit(0) Polarity of A pulse.


0: off


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 88 / 153

|Col1|bpol<br>npol<br>use_abn_as_n<br>cln<br>direction|bit(1)<br>bit(2)<br>bit(3)<br>bit(8)<br>bit(12)|1: on<br>Polarity of B pulse.<br>0: off<br>1: on<br>Polarity of N pulse.<br>0: off<br>1: on<br>0: Ignore A and B polarity with<br>Npulse = N, 1 : Npulse = N and A<br>and B<br>0: Ignore A and B polarity with<br>Npulse = N<br>1: Npulse = N and A and B<br>Write direction at Npulse event be-<br>tween ABN_2_DECODER_COUNT_<br>N and ABN_2_DECODER_COUNT.<br>0: COUNT => COUNT_N<br>1: COUNT_N => COUNT<br>Decoder count direction.<br>0: positive<br>1: negative|
|---|---|---|---|
|0x2Dh|ABN_2_DECODER_PPR<br>ABN_2_DECODER_PPR|u24(23:0)|This register is used to set PPR<br>number of encoder.<br>Decoder_2 pules per mechanical<br>revolution. This 2nd ABN encoder<br>interface is for positioning or ve-<br>locity control but NOT for motor<br>commutation.|
|0x2Eh|ABN_2_DECODER_COUNT<br>ABN_2_DECODER_COUNT|u24(23:0)|This register displays the actual<br>count of encoder steps. It can be<br>overwritten for initialization.<br>Raw decoder_2 count; the digi-<br>tal decoder engine counts modulo<br>(decoder_2_ppr).|
|0x2Fh|ABN_2_DECODER_COUNT_N<br>ABN_2_DECODER_COUNT_N|u24(23:0)|This register displays the count<br>value at last N pulse event. It can<br>also be used to overwrite decoder<br>count at N pulse event according<br>to decoder mode register setting.<br>Decoder_2 count latched on N<br>pulse, when N pulse clears de-<br>coder_2_count<br>also<br>decoder_2_<br>count_n is 0.|



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 89 / 153

|0x30<br>h|ABN_2_DECODER_PHI_M_OFFSET<br>ABN_2_DECODER_PHI_M_OFFSET|s16(15:0)|This register can be used to set off-<br>sets for electrical and mechanical<br>angle calculated from decoder.<br>ABN_2_DECODER_PHI_M_OFFSET<br>to shift (rotate) angle DECODER_<br>2_PHI_M.|
|---|---|---|---|
|0x31h|ABN_2_DECODER_PHI_M<br>ABN_2_DECODER_PHI_M|s16(15:0)|This register displays actual angle<br>values for ABN encoder.<br>ABN_2_DECODER_PHI_M = ABN_<br>2_DECODER_COUNT<br>*<br>2^16<br>/<br>ABN_2_DECODER_PPR + ABN_2_<br>DECODER_PHI_M_OFFSET;|
|0x33h|HALL_MODE<br>polarity<br>synchronous PWM sampling<br>interpolation<br>direction<br>HALL_BLANK|bit(0)<br>bit(4)<br>bit(8)<br>bit(12)<br>u12(27:16)|This register is used to set basic<br>settings for the digital Hall inter-<br>face.<br>polarity<br>0: oﬀ<br>1: on<br>enable sampling synchronous to<br>PWM<br>0: oﬀ<br>1: on<br>interpolation<br>0: oﬀ<br>1: on<br>direction<br>0: oﬀ<br>1: on<br>tBLANK = 10ns * HALL_BLANK|
|0x34h|HALL_POSITION_060_000<br>HALL_POSITION_000<br>HALL_POSITION_060|s16(15:0)<br>s16(31:16)|This register is used to calibrate<br>hall sensor oﬀset.<br>s16 hall sensor position at 0°<br>s16 hall sensor position at 60°.|
|0x35h|HALL_POSITION_180_120<br>HALL_POSITION_120<br>HALL_POSITION_180|s16(15:0)<br>s16(31:16)|This register is used to calibrate<br>hall sensor oﬀset.<br>s16 hall sensor position at 120°.<br>s16 hall sensor position at 180°.|
|0x36h|HALL_POSITION_300_240<br>HALL_POSITION_240|s16(15:0)|This register is used to calibrate<br>hall sensor oﬀset.<br>s16 hall sensor position at 240°.|



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 90 / 153


for calculated angles from hall interface.


phi_m of hall decoder.


e of hall decoder.


maxim difference of two hall sensor transitions for Hall position extrapolation.


fault for digital hall: u16/6).


and raw angle of Hall interface.


of hall decoder, selection programmed via HALL_MODE control
bit.


phi_e_interpolated, selection programmed via HALL_MODE control
bit.


ical angle calculated in Hall sensor
interface.


hall decoder.


tion for the analog encoder interface.


0: 90 degree


1: 120 degree


0: positive


1: negative

|HALL_POSITION_300|s16(31:16)|
|---|---|
|HALL_PHI_E_PHI_M_OFFSET<br>HALL_PHI_M_OFFSET<br>HALL_PHI_E_OFFSET|s16(15:0)<br>s16(31:16)|
|HALL_DPHI_MAX<br>HALL_DPHI_MAX|u16(15:0)|
|HALL_PHI_E_INTERPOLATED_PHI_E<br>HALL_PHI_E<br>HALL_PHI_E_INTERPOLATED|s16(15:0)<br>s16(31:16)|
|HALL_PHI_M<br>HALL_PHI_M|s16(15:0)|
|AENC_DECODER_MODE<br>AENC_DECODER_MODE[0]<br>AENC_DECODER_MODE[12]|bit(0)<br>bit(12)|



0x3Ch AENC_DECODER_N_THRESHOLD This registers sets analog encoder
N pulse processing function.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 91 / 153

|Col1|AENC_DECODER_N_THRESHOLD|u16(15:0)|Threshold for generating of N<br>pulse from analog AENC_N signal<br>(only needed for analog SinCos en-<br>coders with analog N signal).|
|---|---|---|---|
|0x3Dh|AENC_DECODER_PHI_A_RAW<br>AENC_DECODER_PHI_A_RAW|s16(15:0)|Displays raw angle after ATAN2<br>calculation.<br>Raw analog angle phi calculated<br>from analog AENC inputs (analog<br>hall, analog SinCos, ...).|
|0x3Eh|AENC_DECODER_PHI_A_OFFSET<br>AENC_DECODER_PHI_A_OFFSET|s16(15:0)|This register sets the oﬀset of PHI_<br>A for phase alignment.<br>Oﬀset for angle phi from analog<br>decoder (analog hall, analog Sin-<br>Cos, ...).|
|0x3Fh|AENC_DECODER_PHI_A<br>AENC_DECODER_PHI_A|s16(15:0)|This register displays oﬀset com-<br>pensated PHI_A angle.<br>Resulting phi available for the FOC<br>(phi_e might need to be calculated<br>from this angle via aenc_decoder_<br>ppr, for analog hall sensors phi_a<br>might be used directly as phi_e de-<br>pends on analog hall signal type).|
|0x40h|AENC_DECODER_PPR<br>AENC_DECODER_PPR|s16(15:0)|This register sets the number of<br>periods per revolution for analog<br>encoder.<br>Number of periods per revolution<br>also called lines per revolution (dif-<br>ferent nomenclatur compared to<br>digital ABN encoders).|
|0x41h|AENC_DECODER_COUNT<br>AENC_DECODER_COUNT|s32(31:0)|Displays the count value of Analog<br>encoder periods.<br>Decoder position, raw unscaled.|
|0x42h|AENC_DECODER_COUNT_N<br>AENC_DECODER_COUNT_N|s32(31:0)|Displays the count value at last N<br>pulse event. Can also be used to<br>auto-overwrite decoder count at<br>N pulse event.<br>Latched decoder position on ana-<br>log N pulse event.|
|0x45h|AENC_DECODER_PHI_E_PHI_M_OFFSET<br>AENC_DECODER_PHI_M_OFFSET<br>AENC_DECODER_PHI_E_OFFSET|s16(15:0)<br>s16(31:16)|This register sets oﬀsets for elec-<br>trical and mechanical angle calcu-<br>lated from AENC interface.<br>Oﬀset for mechanical angle phi_<br>m.<br>Oﬀset for electrical angle phi_e.|



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 92 / 153

|0x46<br>h|AENC_DECODER_PHI_E_PHI_M<br>AENC_DECODER_PHI_M<br>AENC_DECODER_PHI_E|s16(15:0)<br>s16(31:16)|Displays actual angle values of<br>analog encoder interface.<br>Resulting angle phi_m.<br>Resulting angle phi_e.|
|---|---|---|---|
|0x4Dh|CONFIG_DATA<br>biquad_x_a_1<br>biquad_x_a_2<br>biquad_x_b_0<br>biquad_x_b_1<br>biquad_x_b_2<br>biquad_x_enable<br>biquad_v_a_1<br>biquad_v_a_2<br>biquad_v_b_0<br>biquad_v_b_1<br>biquad_v_b_2<br>biquad_v_enable<br>biquad_t_a_1<br>biquad_t_a_2<br>biquad_t_b_0<br>biquad_t_b_1<br>biquad_t_b_2<br>biquad_t_enable<br>biquad_f_a_1<br>biquad_f_a_2<br>biquad_f_b_0<br>biquad_f_b_1<br>biquad_f_b_2<br>biquad_f_enable<br>prbs_amplitude|s32(31:0)<br>s32(31:0)<br>s32(31:0)<br>s32(31:0)<br>s32(31:0)<br>bit(31)<br>s32(31:0)<br>s32(31:0)<br>s32(31:0)<br>s32(31:0)<br>s32(31:0)<br>bit(31)<br>s32(31:0)<br>s32(31:0)<br>s32(31:0)<br>s32(31:0)<br>s32(31:0)<br>bit(31)<br>s32(31:0)<br>s32(31:0)<br>s32(31:0)<br>s32(31:0)<br>s32(31:0)<br>bit(31)<br>s32(31:0)|This<br>multi-purpose<br>register<br>is<br>used to set conﬁguration param-<br>eters of controller cascade and<br>input signal conditioning.<br>0: oﬀ<br>1: on<br>0: oﬀ<br>1: on<br>0: oﬀ<br>1: on<br>0: oﬀ<br>1: on|



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 93 / 153


prbs_down_sampling_ratio s32(31:0)


ref_switch_config u16(15:0)


Encoder_Init_hall_Enable bit(0) 0: off


1: on


SINGLE_PIN_IF_CFG u8(7:0)


SINGLE_PIN_IF_STATUS u16(31:16)


SINGLE_PIN_IF_OFFSET u16(15:0) Offset for scaling of Single pin Interface input


SINGLE_PIN_IF_SCALE s16(31:16) Gain factor of Single pin Interface
input


CURRENT_I_nQ8.8_Q4.12 bit(0) If this bit is set Q4.12 representation of I parameter for torque/flux
control is used. If bit is not set
Q8.8 representation is used


0: Q8.8 representation is used


1: Q4.12 representation is used


CURRENT_P_nQ8.8_Q4.12 bit(1) If this bit is set Q4.12 representation of P for parameter for
torque/flux control is used. If bit
is not set Q8.8 representation is
used


0: Q8.8 representation is used


1: Q4.12 representation is used


VELOCITY_I_nQ8.8_Q4.12 bit(2) If this bit is set Q4.12 representation of I parameter for velocity
control is used. If bit is not set
Q8.8 representation is used


0: Q8.8 representation is used


1: Q4.12 representation is used


VELOCITY_P_nQ8.8_Q4.12 bit(3) If this bit is set Q4.12 representation of P for parameter for velocity control is used. If bit is not set
Q8.8 representation is used


0: Q8.8 representation is used


1: Q4.12 representation is used


POSITION_I_nQ8.8_Q4.12 bit(4) If this bit is set Q4.12 representation of I parameter for position
control is used. If bit is not set
Q8.8 representation is used


0: Q8.8 representation is used


1: Q4.12 representation is used


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 94 / 153


POSITION_P_nQ8.8_Q4.12 bit(5) If this bit is set Q4.12 representation of P for parameter for position control is used. If bit is not set
Q8.8 representation is used


0: Q8.8 representation is used


1: Q4.12 representation is used


0x4Eh CONFIG_ADDR This register is used to select function of CONFIG_DATA register.


CONFIG_ADDR u32(31:0) 1: biquad_x_a_1


2: biquad_x_a_2


4: biquad_x_b_0


5: biquad_x_b_1


6: biquad_x_b_2


7: biquad_x_enable


9: biquad_v_a_1


10: biquad_v_a_2


12: biquad_v_b_0


13: biquad_v_b_1


14: biquad_v_b_2


15: biquad_v_enable


17: biquad_t_a_1


18: biquad_t_a_2


20: biquad_t_b_0


21: biquad_t_b_1


22: biquad_t_b_2


23: biquad_t_enable


25: biquad_f_a_1


26: biquad_f_a_2


28: biquad_f_b_0


29: biquad_f_b_1


30: biquad_f_b_2


31: biquad_f_enable


32: prbs_amplitude


33: prbs_down_sampling_ratio


51: ref_switch_config


52: Encoder_Init_hall_Enable


60: SINGLE_PIN_IF_STATUS_CFG


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 95 / 153


61: SINGLE_PIN_IF_SCALE_OFFSET


62: ADVANCED_PI_REPRESENT.


0x50h VELOCITY_SELECTION This register is used to select an
angle signal for the velocity control loop and velocity calculation.


VELOCITY_SELECTION u8(7:0) Selects the source of the velocity
source for velocity measurement.


0: PHI_E_SELECTION


1: phi_e_ext


2: phi_e_openloop


3: phi_e_abn


4: reserved


5: phi_e_hal


6: phi_e_aenc


7: phi_a_aenc


8: reserved


9: phi_m_abn


10: phi_m_abn_2


11: phi_m_aenc


12: phi_m_hal


VELOCITY_METER_SELECTION u8(15:8) 0: default


1: advanced


0x51h POSITION_SELECTION This register is used to select an
angle signal for the position calculation and control loop.


POSITION_SELECTION u8(7:0) 0: phi_e selected via PHI_E_
SELECTION


1: phi_e_ext


2: phi_e_openloop


3: phi_e_abn


4: reserved


5: phi_e_hal


6: phi_e_aenc


7: phi_a_aenc


8: reserved


9: phi_m_abn


10: phi_m_abn_2


11: phi_m_aenc


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 96 / 153


12: phi_m_hal


angle signal for FOC transformation as electrical angle of the motor.


1: phi_e_ext


2: phi_e_openloop


3: phi_e_abn


4: reserved


5: phi_e_hal


6: phi_e_aenc


7: phi_a_aenc


chosen electrical angle value.


eters for flux controller.


eters for torque controller.


eters for velocity controller.


eters for position controller.

|PHI_E_SELECTION<br>PHI_E_SELECTION|u8(7:0)|
|---|---|
|PHI_E<br>PHI_E|s16(15:0)|
|PID_FLUX_P_FLUX_I<br>PID_FLUX_I<br>PID_FLUX_P|s16(15:0)<br>s16(31:16)|
|PID_TORQUE_P_TORQUE_I<br>PID_TORQUE_I<br>PID_TORQUE_P|s16(15:0)<br>s16(31:16)|
|PID_VELOCITY_P_VELOCITY_I<br>PID_VELOCITY_I<br>PID_VELOCITY_P|s16(15:0)<br>s16(31:16)|
|PID_POSITION_P_POSITION_I<br>PID_POSITION_I<br>PID_POSITION_P|s16(15:0)<br>s16(31:16)|



0x5Dh PIDOUT_UQ_UD_LIMITS This register sets the output voltage/duty cycle limit for the current
controllers. iPARK CIRLIM block
limits voltage output vector length
to this value.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 97 / 153


PIDOUT_UQ_UD_LIMITS s16(15:0) Two dimensional circular limiter
for inputs of iPark. HINT: The absolute value of the register is used
(possible values: 0 ... 32767).


current limit for both controllers.


limits the target values coming
from the target registers.


lute velocity limit for velocity controller input.


limit for position controller input.


position barrier.


limit for position controller input.


position barrier.

|PID_TORQUE_FLUX_LIMITS<br>PID_TORQUE_FLUX_LIMITS|u16(15:0)|
|---|---|
|PID_VELOCITY_LIMIT<br>PID_VELOCITY_LIMIT|u32(31:0)|
|PID_POSITION_LIMIT_LOW<br>PID_POSITION_LIMIT_LOW|s32(31:0)|
|PID_POSITION_LIMIT_HIGH<br>PID_POSITION_LIMIT_HIGH|s32(31:0)|



0x63h MODE_RAMP_MODE_MOTION This register is used to set a motion mode, a downsampling factor
for velocity and position control
loop, and the PI controller structure type.


MODE_MOTION u8(7:0) 0: stopped_mode


1: torque_mode


2: velocity_mode


3: position_mode


4: prbs_flux_mode


5: prbs_torque_mode


6: prbs_velocity_mode


7: prbs_position_mode


8: uq_ud_ext


9: reserved


10: AGPI_A torque_mode


11: AGPI_A velocity_mode


12: AGPI_A position_mode


13: PWM_I torque_mode


14: PWM_I velocity_mode


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 98 / 153


15: PWM_I position_mode


MODE_PID_SMPL u7(30:24)


MODE_PID_TYPE bit(31) 0: parallel/classic PI


1: sequential/advanced PI


controllers in torque mode.


flux control loop inputs for feedforward control.


trol.


control.


controller in velocity mode.


ity mode).


controller in velocity and position
mode.


control.


controller in position mode.


tion mode).


sured by ADC and depending on
the motor type after park and
clarke transformation.


from chosen angle signal.

|PID_TORQUE_FLUX_TARGET<br>PID_FLUX_TARGET<br>PID_TORQUE_TARGET|s16(15:0)<br>s16(31:16)|
|---|---|
|PID_TORQUE_FLUX_OFFSET<br>PID_FLUX_OFFSET<br>PID_TORQUE_OFFSET|s16(15:0)<br>s16(31:16)|
|PID_VELOCITY_TARGET<br>PID_VELOCITY_TARGET|s32(31:0)|
|PID_VELOCITY_OFFSET<br>PID_VELOCITY_OFFSET|s32(31:0)|
|PID_POSITION_TARGET<br>PID_POSITION_TARGET|s32(31:0)|
|PID_TORQUE_FLUX_ACTUAL<br>PID_FLUX_ACTUAL<br>PID_TORQUE_ACTUAL|s16(15:0)<br>s16(31:16)|
|PID_VELOCITY_ACTUAL<br>PID_VELOCITY_ACTUAL|s32(31:0)|



0x6Bh PID_POSITION_ACTUAL Actual position derived from chosen position signal.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 99 / 153


PID_POSITION_ACTUAL s32(31:0) Actual multi turn position for positioning. Input position differences
are accumulated. Lower 16 bits
display one revolution of input angle. Upper 16 bits display revolutions. WRITE on PID_POSITION_
ACTUAL writes same value into
PID_POSITION_TARGET to avoid
unwanted move.


controllers for testing according
to selection PID_ERROR_ADDR .


PID_ERROR_DATA register.


1: PID_FLUX_ERROR


2: PID_VELOCITY_ERROR


3: PID_POSITION_ERROR


4: PID_TORQUE_ERROR_SUM


5: PID_FLUX_ERROR_SUM


6: PID_VELOCITY_ERROR_SUM


7: PID_POSITION_ERROR_SUM

|PID_ERROR_DATA<br>PID_TORQUE_ERROR<br>PID_FLUX_ERROR<br>PID_VELOCITY_ERROR<br>PID_POSITION_ERROR<br>PID_TORQUE_ERROR_SUM<br>PID_FLUX_ERROR_SUM<br>PID_VELOCITY_ERROR_SUM<br>PID_POSITION_ERROR_SUM|s32(31:0)<br>s32(31:0)<br>s32(31:0)<br>s32(31:0)<br>s32(31:0)<br>s32(31:0)<br>s32(31:0)<br>s32(31:0)|
|---|---|
|PID_ERROR_ADDR<br>PID_ERROR_ADDR|u8(7:0)|



0x6Eh INTERIM_DATA This register is used to display internal signals from controller cascade for monitoring.


PIDIN_TARGET_TORQUE s32(31:0) PIDIN target torque.


PIDIN_TARGET_FLUX s32(31:0) PIDIN target flux.


PIDIN_TARGET_VELOCITY s32(31:0) PIDIN target velocity.


PIDIN_TARGET_POSITION s32(31:0) PIDIN target position.


PIDOUT_TARGET_TORQUE s32(31:0) PIDOUT target torque.


PIDOUT_TARGET_FLUX s32(31:0) PIDOUT target flux.


PIDOUT_TARGET_VELOCITY s32(31:0) PIDOUT target velocity.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 100 / 153


PIDOUT_TARGET_POSITION s32(31:0) PIDOUT target position.


FOC_IUX s16(15:0)


FOC_IWY s16(31:16)


FOC_IV s16(15:0)


FOC_IA s16(15:0)


FOC_IB s16(31:16)


FOC_ID s16(15:0)


FOC_IQ s16(31:16)


FOC_UD s16(15:0)


FOC_UQ s16(31:16)


FOC_UD_LIMITED s16(15:0)


FOC_UQ_LIMITED s16(31:16)


FOC_UA s16(15:0)


FOC_UB s16(31:16)


FOC_UUX s16(15:0)


FOC_UWY s16(31:16)


FOC_UV s16(15:0)


PWM_UX s16(15:0)


PWM_WY s16(31:16)


PWM_V s16(15:0)


ADC_I_0 s16(15:0)


ADC_I_1 s16(31:16)


PID_FLUX_ACTUAL_DIV256 s8(7:0)


PID_TORQUE_ACTUAL_DIV256 s8(15:8)


PID_FLUX_TARGET_DIV256 s8(23:16)


PID_TORQUE_TARGET_DIV256 s8(31:24)


PID_TORQUE_ACTUAL s16(15:0)


PID_TORQUE_TARGET s16(31:16)


PID_FLUX_ACTUAL s16(15:0)


PID_FLUX_TARGET s16(31:16)


PID_VELOCITY_ACTUAL_DIV256 s16(15:0)


PID_VELOCITY_TARGET_DIV256 s16(31:16)


PID_VELOCITY_ACTUAL_LSB s16(15:0)


PID_VELOCITY_TARGET_LSB s16(31:16)


PID_POSITION_ACTUAL_DIV256 s16(15:0)


PID_POSITION_TARGET_DIV256 s16(31:16)


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 101 / 153


PID_POSITION_ACTUAL_LSB s16(15:0)


PID_POSITION_TARGET_LSB s16(31:16)


FF_VELOCITY s32(31:0)


FF_TORQUE s16(15:0)


ACTUAL_VELOCITY_PPTM s32(31:0)


REF_SWITCH_STATUS u16(15:0)


HOME_POSITION s32(31:0)


LEFT_POSITION s32(31:0)


RIGHT_POSITION s32(31:0)


ENC_INIT_HALL_STATUS u16(15:0)


ENC_INIT_HALL_PHI_E_ABN_OFFSET u16(15:0)


ENC_INIT_HALL_PHI_E_AENC_OFFSET u16(15:0)


ENC_INIT_HALL_PHI_A_AENC_OFFSET u16(15:0)


SINGLE_PIN_IF_TARGET_TORQUE s16(15:0)


SINGLE_PIN_IF_PWM_DUTY_CYCLE s16(31:16)


SINGLE_PIN_IF_TARGET_VELOCITY s32(31:0)


SINGLE_PIN_IF_TARGET_POSITION s32(31:0)


0x6Fh INTERIM_ADDR Sets function of register INTERIM_
DATA.


INTERIM_ADDR u8(7:0) 0: PIDIN_TARGET_TORQUE


1: PIDIN_TARGET_FLUX


2: PIDIN_TARGET_VELOCITY


3: PIDIN_TARGET_POSITION


4: PIDOUT_TARGET_TORQUE


5: PIDOUT_TARGET_FLUX


6: PIDOUT_TARGET_VELOCITY


7: PIDOUT_TARGET_POSITION


8: FOC_IWY_IUX


9: FOC_IV


10: FOC_IB_IA


11: FOC_IQ_ID


12: FOC_UQ_UD


13: FOC_UQ_UD_LIMITED


14: FOC_UB_UA


15: FOC_UWY_UUX


16: FOC_UV


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 102 / 153


17: PWM_WY_UX


18: PWM_UV


19: ADC_I1_I0


20: PID_TORQUE_TARGET_FLUX_
TARGET_TORQUE_ACTUAL_FLUX_
ACTUAL_DIV256


21: PID_TORQUE_TARGET_
TORQUE_ACTUAL


22: PID_FLUX_TARGET_FLUX_
ACTUAL


23: PID_VELOCITY_TARGET_
VELOCITY_ACTUAL_DIV256


24: PID_VELOCITY_TARGET_
VELOCITY_ACTUAL


25: PID_POSITION_TARGET_
POSITION_ACTUAL_DIV256


26: PID_POSITION_TARGET_
POSITION_ACTUAL


27: FF_VELOCITY


28: FF_TORQUE


29: ACTUAL_VELOCITY_PPTM


30: REF_SWITCH_STATUS


31: HOME_POSITION


32: LEFT_POSITION


33: RIGHT_POSITION


34: ENC_INIT_HALL_STATUS


35: ENC_INIT_HALL_PHI_E_ABN_
OFFSET


36: ENC_INIT_HALL_PHI_E_AENC_
OFFSET


37: ENC_INIT_HALL_PHI_A_AENC_
OFFSET


42: SINGLE_PIN_IF_PWM_DUTY_
CYCLE_TORQUE_TARGET


43: SINGLE_PIN_IF_VELOCITY_
TARGET


44: SINGLE_PIN_IF_POSITION_
TARGET


0x75h ADC_VM_LIMITS Sets supply voltage limits for
brake chopper output action.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 103 / 153


ADC_VM_LIMIT_LOW u16(15:0) Low limit for brake chopper output BRAKE_OUT.


ADC_VM_LIMIT_HIGH u16(31:16) High limit for brake chopper output BRAKE_OUT.


0x76h TMC4671_INPUTS_RAW Displays actual input signals of
IC for monitoring and connection
testing.


A of ABN_RAW bit(0) A of ABN_RAW


0: off


1: on


B of ABN_RAW bit(1) B of ABN_RAW


0: off


1: on


N of ABN_RAW bit(2) N of ABN_RAW


0: off


1: on


         - bit(3)         

0: off


1: on


A of ABN_2_RAW bit(4) A of ABN_2_RAW


0: off


1: on


B of ABN_2_RAW bit(5) B of ABN_2_RAW


0: off


1: on


N of ABN_2_RAW bit(6) N of ABN_2_RAW


0: off


1: on


         - bit(7)         

0: off


1: on


HALL_UX of HALL_RAW bit(8) HALL_UX of HALL_RAW


0: off


1: on


HALL_V of HALL_RAW bit(9) HALL_V of HALL_RAW


0: off


1: on


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 104 / 153


HALL_WY of HALL_RAW bit(10) HALL_WY of HALL_RAW


0: off


1: on


         - bit(11)         

0: off


1: on


REF_SW_R_RAW bit(12) REF_SW_R_RAW


0: off


1: on


REF_SW_H_RAW bit(13) REF_SW_H_RAW


0: off


1: on


REF_SW_L_RAW bit(14) REF_SW_L_RAW


0: off


1: on


ENABLE_IN_RAW bit(15) ENABLE_IN_RAW


0: off


1: on


STP of DIRSTP_RAW bit(16) STP of DIRSTP_RAW


0: off


1: on


DIR of DIRSTP_RAW bit(17) DIR of DIRSTP_RAW


0: off


1: on


PWM_IN_RAW bit(18) PWM_IN_RAW


0: off


1: on


         - bit(19)         

0: off


1: on


HALL_UX_FILT bit(20) ESI_0 of ESI_RAW


0: off


1: on


HALL_V_FILT bit(21) ESI_1 of ESI_RAW


0: off


1: on


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 105 / 153


HALL_WY_FILT bit(22) ESI_2 of ESI_RAW


0: off


1: on


         - bit(23)         

0: off


1: on


         - bit(24) CFG_0 of CFG


0: off


1: on


         - bit(25) CFG_1 of CFG


0: off


1: on


         - bit(26) CFG_2 of CFG


0: off


1: on


         - bit(27) CFG_3 of CFG


0: off


1: on


PWM_IDLE_L_RAW bit(28) PWM_IDLE_L_RAW


0: off


1: on


PWM_IDLE_H_RAW bit(29) PWM_IDLE_H_RAW


0: off


1: on


         - bit(30) DRV_ERR_IN_RAW


0: off


1: on


         - bit(31)         

0: off


1: on


0x77h TMC4671_OUTPUTS_RAW Displays actual output signals of
IC for monitoring and connection
testing.


TMC4671_OUTPUTS_RAW[0] bit(0) PWM_UX1_L


0: off


1: on


TMC4671_OUTPUTS_RAW[1] bit(1) PWM_UX1_H


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 106 / 153


0: off


1: on


TMC4671_OUTPUTS_RAW[2] bit(2) PWM_VX2_L


0: off


1: on


TMC4671_OUTPUTS_RAW[3] bit(3) PWM_VX2_H


0: off


1: on


TMC4671_OUTPUTS_RAW[4] bit(4) PWM_WY1_L


0: off


1: on


TMC4671_OUTPUTS_RAW[5] bit(5) PWM_WY1_H


0: off


1: on


TMC4671_OUTPUTS_RAW[6] bit(6) PWM_Y2_L


0: off


1: on


TMC4671_OUTPUTS_RAW[7] bit(7) PWM_Y2_H


0: off


1: on


put step signal on STEP/DIR interface. Target position is decreased/increased by this value
according to Dir signal.


ignored, resulting direction = DIR
XOR sign(STEP_WIDTH), effects
PID_POSITION_TARGET


Must be entered as hexadecimal
number (e.g baudrate 9600 is set
by entering 0x00009600h)


0x00921600h, 0x03000000h
(default=0x00009600)

|STEP_WIDTH<br>STEP_WIDTH|s32(31:0)|
|---|---|
|UART_BPS<br>UART_BPS|u24(23:0)|



0x7Bh GPIO_dsADCI_CONFIG Sets the function and controls the
GPIOs if RTMI is not used. Check
functional description for detailed
explanation of options.


GPIO_dsADCI_CONFIG[0] bit(0) SEL_nDBGSPIM_GPIO


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 107 / 153


0: off


1: on


GPIO_dsADCI_CONFIG[1] bit(1) SEL_nGPIO_dsADCS_A


0: off


1: on


GPIO_dsADCI_CONFIG[2] bit(2) SEL_nGPIO_dsADCS_B


0: off


1: on


GPIO_dsADCI_CONFIG[3] bit(3) SEL_GPIO_GROUP_A_nIN_OUT


0: off


1: on


GPIO_dsADCI_CONFIG[4] bit(4) SEL_GPIO_GROUP_B_nIN_OUT


0: off


1: on


GPIO_dsADCI_CONFIG[5] bit(5) SEL_GROUP_A_DSADCS_nCLKIN_
CLKOUT


0: off


1: on


GPIO_dsADCI_CONFIG[6] bit(6) SEL_GROUP_B_DSADCS_nCLKIN_
CLKOUT


0: off


1: on


GPO u8(23:16)


GPI u8(31:24)


0x7Ch STATUS_FLAGS Displays actual status flags to set
status output. The register is also
used to reset status flags.


STATUS_FLAGS[0] bit(0) pid_x_target_limit


0: off


1: on


STATUS_FLAGS[1] bit(1) pid_x_target_ddt_limit


0: off


1: on


STATUS_FLAGS[2] bit(2) pid_x_errsum_limit


0: off


1: on


STATUS_FLAGS[3] bit(3) pid_x_output_limit


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 108 / 153


0: off


1: on


STATUS_FLAGS[4] bit(4) pid_v_target_limit


0: off


1: on


STATUS_FLAGS[5] bit(5) pid_v_target_ddt_limit


0: off


1: on


STATUS_FLAGS[6] bit(6) pid_v_errsum_limit


0: off


1: on


STATUS_FLAGS[7] bit(7) pid_v_output_limit


0: off


1: on


STATUS_FLAGS[8] bit(8) pid_id_target_limit


0: off


1: on


STATUS_FLAGS[9] bit(9) pid_id_target_ddt_limit


0: off


1: on


STATUS_FLAGS[10] bit(10) pid_id_errsum_limit


0: off


1: on


STATUS_FLAGS[11] bit(11) pid_id_output_limit


0: off


1: on


STATUS_FLAGS[12] bit(12) pid_iq_target_limit


0: off


1: on


STATUS_FLAGS[13] bit(13) pid_iq_target_ddt_limit


0: off


1: on


STATUS_FLAGS[14] bit(14) pid_iq_errsum_limit


0: off


1: on


STATUS_FLAGS[15] bit(15) pid_iq_output_limit


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 109 / 153


0: off


1: on


STATUS_FLAGS[16] bit(16) ipark_cirlim_limit_u_d


0: off


1: on


STATUS_FLAGS[17] bit(17) ipark_cirlim_limit_u_q


0: off


1: on


STATUS_FLAGS[18] bit(18) ipark_cirlim_limit_u_r


0: off


1: on


STATUS_FLAGS[19] bit(19) not_PLL_locked


0: off


1: on


STATUS_FLAGS[20] bit(20) ref_sw_r


0: off


1: on


STATUS_FLAGS[21] bit(21) ref_sw_h


0: off


1: on


STATUS_FLAGS[22] bit(22) ref_sw_l


0: off


1: on


STATUS_FLAGS[23] bit(23)      

0: off


1: on


STATUS_FLAGS[24] bit(24) pwm_min


0: off


1: on


STATUS_FLAGS[25] bit(25) pwm_max


0: off


1: on


STATUS_FLAGS[26] bit(26) adc_i_clipped


0: off


1: on


STATUS_FLAGS[27] bit(27) aenc_clipped


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 110 / 153


0: off


1: on


STATUS_FLAGS[28] bit(28) enc_n


0: off


1: on


STATUS_FLAGS[29] bit(29) enc_2_n


0: off


1: on


STATUS_FLAGS[30] bit(30) aenc_n


0: off


1: on


STATUS_FLAGS[31] bit(31) reserved


0: off


1: on


0x7Dh STATUS_MASK Register is used to set a mask for
STATUS_FLAGS register to set STATUS output pin.


STATUS_MASK u32(31:0)


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 111 / 153


**7.3** **Register Map - Defaults, min, max**


**RD/WR** **ADDR** **NAME** **DEFAULT** **MIN** **MAX**


R 0x00h CHIPINFO_DATA


SI_TYPE 0x0h 0x0h 0xFFFFFFFFh


SI_VERSION 0x0h 0x0h 0xFFFFFFFFh


SI_DATE 0x0h 0x0h 0xFFFFFFFFh


SI_TIME 0x0h 0x0h 0xFFFFFFh


SI_VARIANT 0x0h 0x0h 0xFFFFFFFFh


SI_BUILD 0x0h 0x0h 0xFFFFFFFFh


RW 0x01h CHIPINFO_ADDR


CHIP_INFO_ADDRESS 0x0h 0x0h 0x5h


R 0x02h ADC_RAW_DATA


ADC_I0_RAW 0x0h 0x0h 0xFFFFh


ADC_I1_RAW 0x0h 0x0h 0xFFFFh


ADC_VM_RAW 0x0h 0x0h 0xFFFFh


ADC_AGPI_A_RAW 0x0h 0x0h 0xFFFFh


ADC_AGPI_B_RAW 0x0h 0x0h 0xFFFFh


ADC_AENC_UX_RAW 0x0h 0x0h 0xFFFFh


ADC_AENC_VN_RAW 0x0h 0x0h 0xFFFFh


ADC_AENC_WY_RAW 0x0h 0x0h 0xFFFFh


RW 0x03h ADC_RAW_ADDR


ADC_RAW_ADDR 0x0h 0x0h 0x3h


RW 0x04h dsADC_MCFG_B_
MCFG_A


cfg_dsmodulator_a 0x0h 0x0h 0x3h


mclk_polarity_a 0x0h 0x0h 0x1h


mdat_polarity_a 0x0h 0x0h 0x1h


sel_nclk_mclk_i_a 0x0h 0x0h 0x1h


cfg_dsmodulator_b 0x0h 0x0h 0x3h


mclk_polarity_b 0x0h 0x0h 0x1h


mdat_polarity_b 0x0h 0x0h 0x1h


sel_nclk_mclk_i_b 0x0h 0x0h 0x1h


RW 0x05h dsADC_MCLK_A


dsADC_MCLK_A 0x20000000h 0x0h 0xFFFFFFFFh


RW 0x06h dsADC_MCLK_B


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 112 / 153


dsADC_MCLK_B 0x20000000h 0x0h 0xFFFFFFFFh


RW 0x07h dsADC_MDEC_B_
MDEC_A


dsADC_MDEC_A 0x100h 0x0h 0xFFFFh


dsADC_MDEC_B 0x100h 0x0h 0xFFFFh


RW 0x08h ADC_I1_SCALE_
OFFSET


ADC_I1_OFFSET 0x0h 0x0h 0xFFFFh


ADC_I1_SCALE 0x100h -0x8000h 0x7FFFh


RW 0x09h ADC_I0_SCALE_
OFFSET


ADC_I0_OFFSET 0x0h 0x0h 0xFFFFh


ADC_I0_SCALE 0x100h -0x8000h 0x7FFFh


RW 0x0Ah ADC_I_SELECT


ADC_I0_SELECT 0x0h 0x0h 0x3h


ADC_I1_SELECT 0x1h 0x0h 0x3h


ADC_I_UX_SELECT 0x0h 0x0h 0x2h


ADC_I_V_SELECT 0x1h 0x0h 0x2h


ADC_I_WY_SELECT 0x2h 0x0h 0x2h


RW 0x0Bh ADC_I1_I0_EXT


ADC_I0_EXT 0x0h 0x0h 0xFFFFh


ADC_I1_EXT 0x0h 0x0h 0xFFFFh


RW 0x0Ch DS_ANALOG_INPUT_
STAGE_CFG


ADC_I0 0x0h 0x0h 0x7h


ADC_I1 0x0h 0x0h 0x7h


ADC_VM 0x0h 0x0h 0x7h


ADC_AGPI_A 0x0h 0x0h 0x7h


ADC_AGPI_B 0x0h 0x0h 0x7h


ADC_AENC_UX 0x0h 0x0h 0x7h


ADC_AENC_VN 0x0h 0x0h 0x7h


ADC_AENC_WY 0x0h 0x0h 0x7h


RW 0x0Dh AENC_0_SCALE_
OFFSET


AENC_0_OFFSET 0x0h 0x0h 0xFFFFh


AENC_0_SCALE 0x100h -0x8000h 0x7FFFh


RW 0x0Eh AENC_1_SCALE_
OFFSET


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 113 / 153


AENC_1_OFFSET 0x0h 0x0h 0xFFFFh


AENC_1_SCALE 0x100h -0x8000h 0x7FFFh


RW 0x0Fh AENC_2_SCALE_
OFFSET


AENC_2_OFFSET 0x0h 0x0h 0xFFFFh


AENC_2_SCALE 0x100h -0x8000h 0x7FFFh


RW 0x11h AENC_SELECT


AENC_0_SELECT 0x0h 0x0h 0x2h


AENC_1_SELECT 0x1h 0x0h 0x2h


AENC_2_SELECT 0x2h 0x0h 0x2h


R 0x12h ADC_IWY_IUX


ADC_IUX 0x0h -0x8000h 0x7FFFh


ADC_IWY 0x0h -0x8000h 0x7FFFh


R 0x13h ADC_IV


ADC_IV 0x0h -0x8000h 0x7FFFh


R 0x15h AENC_WY_UX


AENC_UX 0x0h -0x8000h 0x7FFFh


AENC_WY 0x0h -0x8000h 0x7FFFh


R 0x16h AENC_VN


AENC_VN 0x0h -0x8000h 0x7FFFh


RW 0x17h PWM_POLARITIES


PWM_POLARITIES[0] 0x0h 0x0h 0x1h


PWM_POLARITIES[1] 0x0h 0x0h 0x1h


RW 0x18h PWM_MAXCNT


PWM_MAXCNT 0xF9Fh 0x0h 0xFFFFh


RW 0x19h PWM_BBM_H_BBM_L


PWM_BBM_L 0x14h 0x0h 0xFFh


PWM_BBM_H 0x14h 0x0h 0xFFh


RW 0x1Ah PWM_SV_CHOP


PWM_CHOP 0x0h 0x0h 0x7h


PWM_SV 0x0h 0x0h 0x1h


RW 0x1Bh MOTOR_TYPE_N_
POLE_PAIRS


N_POLE_PAIRS 0x1h 0x1h 0xFFFFh


MOTOR_TYPE 0x0h 0x0h 0x3h


RW 0x1Ch PHI_E_EXT


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 114 / 153


PHI_E_EXT 0x0h -0x8000h 0x7FFFh


RW 0x1Fh OPENLOOP_MODE



OPENLOOP_PHI_
DIRECTION


RW 0x20h OPENLOOP_
ACCELERATION


OPENLOOP_
ACCELERATION


RW 0x21h OPENLOOP_
VELOCITY_TARGET


OPENLOOP_
VELOCITY_TARGET


RW 0x22h OPENLOOP_
VELOCITY_ACTUAL


OPENLOOP_
VELOCITY_ACTUAL


RWI 0x23h OPENLOOP_PHI



0x0h 0x0h 0x1h


0x0h 0x0h 0xFFFFFh


0x0h -0x80000000h 0x7FFFFFFFh


0x0h -0x80000000h 0x7FFFFFFFh



OPENLOOP_PHI 0x0h -0x8000h 0x7FFFh


RW 0x24h UQ_UD_EXT


UD_EXT 0x0h -0x8000h 0x7FFFh


UQ_EXT 0x0h -0x8000h 0x7FFFh


RW 0x25h ABN_DECODER_
MODE


apol 0x0h 0x0h 0x1h


bpol 0x0h 0x0h 0x1h


npol 0x0h 0x0h 0x1h


use_abn_as_n 0x0h 0x0h 0x1h


cln 0x0h 0x0h 0x1h


direction 0x0h 0x0h 0x1h


RW 0x26h ABN_DECODER_PPR


ABN_DECODER_PPR 0x10000h 0x0h 0xFFFFFFh


RW 0x27h ABN_DECODER_
COUNT



ABN_DECODER_
COUNT


RW 0x28h ABN_DECODER_
COUNT_N


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



0x0h 0x0h 0xFFFFFFh


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 115 / 153



ABN_DECODER_
COUNT_N


RW 0x29h ABN_DECODER_PHI_
E_PHI_M_OFFSET


ABN_DECODER_PHI_
M_OFFSET


ABN_DECODER_PHI_
E_OFFSET


R 0x2Ah ABN_DECODER_PHI_
E_PHI_M


ABN_DECODER_PHI_
M


ABN_DECODER_PHI_
E


RW 0x2Ch ABN_2_DECODER_
MODE



0x0h 0x0h 0xFFFFFFh


0x0h -0x8000h 0x7FFFh


0x0h -0x8000h 0x7FFFh


0x0h -0x8000h 0x7FFFh


0x0h -0x8000h 0x7FFFh



apol 0x0h 0x0h 0x1h


bpol 0x0h 0x0h 0x1h


npol 0x0h 0x0h 0x1h


use_abn_as_n 0x0h 0x0h 0x1h


cln 0x0h 0x0h 0x1h


direction 0x0h 0x0h 0x1h


RW 0x2Dh ABN_2_DECODER_
PPR



ABN_2_DECODER_
PPR


RW 0x2Eh ABN_2_DECODER_
COUNT


ABN_2_DECODER_
COUNT


RW 0x2Fh ABN_2_DECODER_
COUNT_N


ABN_2_DECODER_
COUNT_N


RW 0x30h ABN_2_DECODER_
PHI_M_OFFSET


ABN_2_DECODER_
PHI_M_OFFSET


R 0x31h ABN_2_DECODER_
PHI_M



0x10000h 0x1h 0xFFFFFFh


0x0h 0x0h 0xFFFFFFh


0x0h 0x0h 0xFFFFFFh


0x0h -0x8000h 0x7FFFh



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 116 / 153



ABN_2_DECODER_
PHI_M


RW 0x33h HALL_MODE



0x0h -0x8000h 0x7FFFh



polarity 0x0h 0x0h 0x1h



synchronous PWM
sampling



0x0h 0x0h 0x1h



interpolation 0x0h 0x0h 0x1h


direction 0x0h 0x0h 0x1h


HALL_BLANK 0x0h 0x0h 0xFFFh


RW 0x34h HALL_POSITION_
060_000


HALL_POSITION_000 0x0h -0x8000h 0x7FFFh


HALL_POSITION_060 0x2AAAh -0x8000h 0x7FFFh


RW 0x35h HALL_POSITION_
180_120


HALL_POSITION_120 0x5555h -0x8000h 0x7FFFh


HALL_POSITION_180 -0x8000h -0x8000h 0x7FFFh


RW 0x36h HALL_POSITION_
300_240


HALL_POSITION_240 -0x5556h -0x8000h 0x7FFFh


HALL_POSITION_300 -0x2AABh -0x8000h 0x7FFFh


RW 0x37h HALL_PHI_E_PHI_M_
OFFSET


HALL_PHI_M_OFFSET 0x0h -0x8000h 0x7FFFh


HALL_PHI_E_OFFSET 0x0h -0x8000h 0x7FFFh


RW 0x38h HALL_DPHI_MAX


HALL_DPHI_MAX 0x2AAAh 0x0h 0xFFFFh


R 0x39h HALL_PHI_E_
INTERPOLATED_
PHI_E


HALL_PHI_E 0x0h -0x8000h 0x7FFFh



HALL_PHI_E_
INTERPOLATED


R 0x3Ah HALL_PHI_M



0x0h -0x8000h 0x7FFFh



HALL_PHI_M 0x0h -0x8000h 0x7FFFh


RW 0x3Bh AENC_DECODER_
MODE



AENC_DECODER_
MODE[0]


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



0x0h 0x0h 0x1h


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 117 / 153









|AENC_DECODER_<br>MODE[12]|0x0<br>h|0x0 0x1<br>h h|
|---|---|---|
|RW<br>0x3Ch<br>AENC_DECODER_N_<br>THRESHOLD<br>AENC_DECODER_N_<br>THRESHOLD|0x0h|0x0h<br>0xFFFFh|
|R<br>0x3Dh<br>AENC_DECODER_<br>PHI_A_RAW<br>AENC_DECODER_<br>PHI_A_RAW|0x0h|-0x8000h<br>0x7FFFh|
|RW<br>0x3Eh<br>AENC_DECODER_<br>PHI_A_OFFSET<br>AENC_DECODER_<br>PHI_A_OFFSET|0x0h|-0x8000h<br>0x7FFFh|
|R<br>0x3Fh<br>AENC_DECODER_<br>PHI_A<br>AENC_DECODER_<br>PHI_A|0x0h|-0x80000000h<br>0x7FFFFFFFh|
|RW<br>0x40h<br>AENC_DECODER_PPR<br>AENC_DECODER_PPR|0x1h|-0x8000h<br>0x7FFFh|
|R<br>0x41h<br>AENC_DECODER_<br>COUNT<br>AENC_DECODER_<br>COUNT|0x0h|-0x80000000h<br>0x7FFFFFFFh|
|RW<br>0x42h<br>AENC_DECODER_<br>COUNT_N<br>AENC_DECODER_<br>COUNT_N|0x0h|-0x80000000h<br>0x7FFFFFFFh|
|RW<br>0x45h<br>AENC_DECODER_<br>PHI_E_PHI_M_OFFSET<br>AENC_DECODER_<br>PHI_M_OFFSET<br>AENC_DECODER_<br>PHI_E_OFFSET|0x0h<br>0x0h|-0x8000h<br>0x7FFFh<br>-0x8000h<br>0x7FFFh|
|R<br>0x46h<br>AENC_DECODER_<br>PHI_E_PHI_M<br>AENC_DECODER_<br>PHI_M<br>AENC_DECODER_<br>PHI_E|0x0h<br>0x0h|-0x8000h<br>0x7FFFh<br>-0x8000h<br>0x7FFFh|


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)




TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 118 / 153


RW 0x4Dh CONFIG_DATA


biquad_x_a_1 0x0h -0x80000000h 0x7FFFFFFFh


biquad_x_a_2 0x0h -0x80000000h 0x7FFFFFFFh


biquad_x_b_0 0x0h -0x80000000h 0x7FFFFFFFh


biquad_x_b_1 0x0h -0x80000000h 0x7FFFFFFFh


biquad_x_b_2 0x0h -0x80000000h 0x7FFFFFFFh


biquad_x_enable 0x0h 0x0h 0x1h


biquad_v_a_1 0x0h -0x80000000h 0x7FFFFFFFh


biquad_v_a_2 0x0h -0x80000000h 0x7FFFFFFFh


biquad_v_b_0 0x0h -0x80000000h 0x7FFFFFFFh


biquad_v_b_1 0x0h -0x80000000h 0x7FFFFFFFh


biquad_v_b_2 0x0h -0x80000000h 0x7FFFFFFFh


biquad_v_enable 0x0h 0x0h 0x1h


biquad_t_a_1 0x0h -0x80000000h 0x7FFFFFFFh


biquad_t_a_2 0x0h -0x80000000h 0x7FFFFFFFh


biquad_t_b_0 0x0h -0x80000000h 0x7FFFFFFFh


biquad_t_b_1 0x0h -0x80000000h 0x7FFFFFFFh


biquad_t_b_2 0x0h -0x80000000h 0x7FFFFFFFh


biquad_t_enable 0x0h 0x0h 0x1h


biquad_f_a_1 0x0h -0x80000000h 0x7FFFFFFFh


biquad_f_a_2 0x0h -0x80000000h 0x7FFFFFFFh


biquad_f_b_0 0x0h -0x80000000h 0x7FFFFFFFh


biquad_f_b_1 0x0h -0x80000000h 0x7FFFFFFFh


biquad_f_b_2 0x0h -0x80000000h 0x7FFFFFFFh


biquad_f_enable 0x0h 0x0h 0x1h


prbs_amplitude 0x0h -0x80000000h 0x7FFFFFFFh



prbs_down_
sampling_ratio


feed_forward_
velocity_gain


feed_forward_
velocity_filter_
constant


feed_forward_
torque_gain


feed_forward_
torgue_filter_
constant


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



0x0h -0x80000000h 0x7FFFFFFFh


0x0h -0x80000000h 0x7FFFFFFFh


0x0h -0x80000000h 0x7FFFFFFFh


0x0h -0x80000000h 0x7FFFFFFFh


0x0h -0x80000000h 0x7FFFFFFFh


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 119 / 153

























|VELOCITY_METER_<br>PPTM_MIN_POS_DEV<br>ref_switch_config<br>Encoder_Init_hall_<br>Enable<br>SINGLE_PIN_IF_CFG<br>SINGLE_PIN_IF_<br>STATUS<br>SINGLE_PIN_IF_<br>OFFSET<br>SINGLE_PIN_IF_<br>SCALE<br>CURRENT_P_nQ8.8_<br>Q4.12<br>CURRENT_I_nQ8.8_<br>Q4.12<br>VELOCITY_P_nQ8.8_<br>Q4.12<br>VELOCITY_I_nQ8.8_<br>Q4.12<br>POSITION_P_nQ8.8_<br>Q4.12<br>POSITION_I_nQ8.8_<br>Q4.12|0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h|0x0 0xFFFF<br>h h<br>0x0 0xFFFF<br>h h<br>0x0 0x1<br>h h<br>0x0 0xFF<br>h h<br>0x0 0xFFFF<br>h h<br>0x0 0xFFFF<br>h h<br>-0x7FFF 0x7FFF<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h|
|---|---|---|
|RW<br>0x4Eh<br>CONFIG_ADDR<br>CONFIG_ADDR|0x0h|0x1h<br>0x3Eh|
|RW<br>0x50h<br>VELOCITY_<br>SELECTION<br>VELOCITY_<br>SELECTION<br>VELOCITY_METER_<br>SELECTION|0x0h<br>0x0h|0x0h<br>0xCh<br>0x0h<br>0x1h|
|RW<br>0x51h<br>POSITION_<br>SELECTION<br>POSITION_<br>SELECTION|0x0h|0x0h<br>0xCh|
|RW<br>0x52h<br>PHI_E_SELECTION<br>PHI_E_SELECTION|0x0h|0x0h<br>0x7h|
|R<br>0x53h<br>PHI_E<br>PHI_E|0x0h|-0x8000h<br>0x7FFFh|


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 120 / 153













|RW 0x54 PID_FLUX_P_FLUX_I<br>h<br>PID_FLUX_I<br>PID_FLUX_P|0x0<br>h<br>0x0<br>h|0x0 0x7FFF<br>h h<br>0x0 0x7FFF<br>h h|
|---|---|---|
|RW<br>0x56h<br>PID_TORQUE_P_<br>TORQUE_I<br>PID_TORQUE_I<br>PID_TORQUE_P|0x0h<br>0x0h|0x0h<br>0x7FFFh<br>0x0h<br>0x7FFFh|
|RW<br>0x58h<br>PID_VELOCITY_P_<br>VELOCITY_I<br>PID_VELOCITY_I<br>PID_VELOCITY_P|0x0h<br>0x0h|0x0h<br>0x7FFFh<br>0x0h<br>0x7FFFh|
|RW<br>0x5Ah<br>PID_POSITION_P_<br>POSITION_I<br>PID_POSITION_I<br>PID_POSITION_P|0x0h<br>0x0h|0x0h<br>0x7FFFh<br>0x0h<br>0x7FFFh|
|RW<br>0x5Dh<br>PIDOUT_UQ_UD_<br>LIMITS<br>PIDOUT_UQ_UD_<br>LIMITS|0x5A81h|0x0h<br>0x7FFFh|
|RW<br>0x5Eh<br>PID_TORQUE_FLUX_<br>LIMITS<br>PID_TORQUE_FLUX_<br>LIMITS|0x7FFFh|0x0h<br>0x7FFFh|
|RW<br>0x60h<br>PID_VELOCITY_LIMIT<br>PID_VELOCITY_LIMIT|0x7FFFFFFFh|0x0h<br>0xFFFFFFFFh|
|RW<br>0x61h<br>PID_POSITION_<br>LIMIT_LOW<br>PID_POSITION_<br>LIMIT_LOW|-0x7FFFFFFFh|-0x80000000h<br>0x7FFFFFFFh|
|RW<br>0x62h<br>PID_POSITION_<br>LIMIT_HIGH<br>PID_POSITION_<br>LIMIT_HIGH|0x7FFFFFFFh|-0x80000000h<br>0x7FFFFFFFh|
|RW<br>0x63h<br>MODE_RAMP_<br>MODE_MOTION<br>MODE_MOTION<br>MODE_PID_SMPL<br>MODE_PID_TYPE|0x0h<br>0x0h<br>0x0h|0x0h<br>0xFh<br>0x0h<br>0x7Fh<br>0x0h<br>0x1h|


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 121 / 153





















|RW 0x64 PID_TORQUE_FLUX_<br>h<br>TARGET<br>PID_FLUX_TARGET<br>PID_TORQUE_<br>TARGET|0x0<br>h<br>0x0<br>h|-0x8000 0x7FFF<br>h h<br>-0x8000 0x7FFF<br>h h|
|---|---|---|
|RW<br>0x65h<br>PID_TORQUE_FLUX_<br>OFFSET<br>PID_FLUX_OFFSET<br>PID_TORQUE_<br>OFFSET|0x0h<br>0x0h|-0x8000h<br>0x7FFFh<br>-0x8000h<br>0x7FFFh|
|RW<br>0x66h<br>PID_VELOCITY_<br>TARGET<br>PID_VELOCITY_<br>TARGET|0x0h|-0x80000000h<br>0x7FFFFFFFh|
|RW<br>0x67h<br>PID_VELOCITY_<br>OFFSET<br>PID_VELOCITY_<br>OFFSET|0x0h|-0x80000000h<br>0x7FFFFFFFh|
|RW<br>0x68h<br>PID_POSITION_<br>TARGET<br>PID_POSITION_<br>TARGET|0x0h|-0x80000000h<br>0x7FFFFFFFh|
|R<br>0x69h<br>PID_TORQUE_FLUX_<br>ACTUAL<br>PID_FLUX_ACTUAL<br>PID_TORQUE_<br>ACTUAL|0x0h<br>0x0h|-0x8000h<br>0x7FFFh<br>-0x8000h<br>0x7FFFh|
|R<br>0x6Ah<br>PID_VELOCITY_<br>ACTUAL<br>PID_VELOCITY_<br>ACTUAL|0x0h|-0x80000000h<br>0x7FFFFFFFh|
|RW<br>0x6Bh<br>PID_POSITION_<br>ACTUAL<br>PID_POSITION_<br>ACTUAL|0x0h|-0x80000000h<br>0x7FFFFFFFh|
|R<br>0x6Ch<br>PID_ERROR_DATA<br>PID_TORQUE_ERROR<br>PID_FLUX_ERROR<br>PID_VELOCITY_<br>ERROR|0x0h<br>0x0h<br>0x0h|-0x80000000h<br>0x7FFFFFFFh<br>-0x80000000h<br>0x7FFFFFFFh<br>-0x80000000h<br>0x7FFFFFFFh|


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)




TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 122 / 153



PID_POSITION_
ERROR


PID_TORQUE_
ERROR_SUM


PID_FLUX_ERROR_
SUM


PID_VELOCITY_
ERROR_SUM


PID_POSITION_
ERROR_SUM


RW 0x6Dh PID_ERROR_ADDR



0x0h -0x80000000h 0x7FFFFFFFh


0x0h -0x80000000h 0x7FFFFFFFh


0x0h -0x80000000h 0x7FFFFFFFh


0x0h -0x80000000h 0x7FFFFFFFh


0x0h -0x80000000h 0x7FFFFFFFh



PID_ERROR_ADDR 0x0h 0x0h 0x7h


RW 0x6Eh INTERIM_DATA



PIDIN_TARGET_
TORQUE



0x0h -0x80000000h 0x7FFFFFFFh



PIDIN_TARGET_FLUX 0x0h -0x80000000h 0x7FFFFFFFh



PIDIN_TARGET_
VELOCITY


PIDIN_TARGET_
POSITION


PIDOUT_TARGET_
TORQUE


PIDOUT_TARGET_
FLUX


PIDOUT_TARGET_
VELOCITY


PIDOUT_TARGET_
POSITION



0x0h -0x80000000h 0x7FFFFFFFh


0x0h -0x80000000h 0x7FFFFFFFh


0x0h -0x80000000h 0x7FFFFFFFh


0x0h -0x80000000h 0x7FFFFFFFh


0x0h -0x80000000h 0x7FFFFFFFh


0x0h -0x80000000h 0x7FFFFFFFh



FOC_IUX 0x0h -0x8000h 0x7FFFh


FOC_IWY 0x0h -0x8000h 0x7FFFh


FOC_IV 0x0h -0x8000h 0x7FFFh


FOC_IA 0x0h -0x8000h 0x7FFFh


FOC_IB 0x0h -0x8000h 0x7FFFh


FOC_ID 0x0h -0x8000h 0x7FFFh


FOC_IQ 0x0h -0x8000h 0x7FFFh


FOC_UD 0x0h -0x8000h 0x7FFFh


FOC_UQ 0x0h -0x8000h 0x7FFFh


FOC_UD_LIMITED 0x0h -0x8000h 0x7FFFh


FOC_UQ_LIMITED 0x0h -0x8000h 0x7FFFh


FOC_UA 0x0h -0x8000h 0x7FFFh


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 123 / 153


FOC_UB 0x0h -0x8000h 0x7FFFh


FOC_UUX 0x0h -0x8000h 0x7FFFh


FOC_UWY 0x0h -0x8000h 0x7FFFh


FOC_UV 0x0h -0x8000h 0x7FFFh


PWM_UX 0x0h -0x8000h 0x7FFFh


PWM_WY 0x0h -0x8000h 0x7FFFh


PWM_V 0x0h -0x8000h 0x7FFFh


ADC_I_0 0x0h -0x8000h 0x7FFFh


ADC_I_1 0x0h -0x8000h 0x7FFFh



PID_FLUX_ACTUAL_
DIV256


PID_TORQUE_
ACTUAL_DIV256


PID_FLUX_TARGET_
DIV256


PID_TORQUE_
TARGET_DIV256


PID_TORQUE_
ACTUAL


PID_TORQUE_
TARGET



0x0h -0x80h 0x7Fh


0x0h -0x80h 0x7Fh


0x0h -0x80h 0x7Fh


0x0h -0x80h 0x7Fh


0x0h -0x8000h 0x7FFFh


0x0h -0x8000h 0x7FFFh



PID_FLUX_ACTUAL 0x0h -0x8000h 0x7FFFh


PID_FLUX_TARGET 0x0h -0x8000h 0x7FFFh



PID_VELOCITY_
ACTUAL_DIV256


PID_VELOCITY_
TARGET_DIV256


PID_VELOCITY_
ACTUAL_LSB


PID_VELOCITY_
TARGET_LSB


PID_POSITION_
ACTUAL_DIV256


PID_POSITION_
TARGET_DIV256


PID_POSITION_
ACTUAL_LSB


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



0x0h -0x8000h 0x7FFFh


0x0h -0x8000h 0x7FFFh


0x0h -0x8000h 0x7FFFh


0x0h -0x8000h 0x7FFFh


0x0h -0x8000h 0x7FFFh


0x0h -0x8000h 0x7FFFh


0x0h -0x8000h 0x7FFFh


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 124 / 153



PID_POSITION_
TARGET_LSB



0x0h -0x8000h 0x7FFFh



FF_VELOCITY 0x0h -0x80000000h 0x7FFFFFFFh


FF_TORQUE 0x0h -0x8000h 0x7FFFh



ACTUAL_VELOCITY_
PPTM



0x0h -0x80000000h 0x7FFFFFFFh



REF_SWITCH_STATUS 0x0h 0x0h 0xFFFFh


HOME_POSITION 0x0h -0x80000000h 0x7FFFFFFFh


LEFT_POSITION 0x0h -0x80000000h 0x7FFFFFFFh


RIGHT_POSITION 0x0h -0x80000000h 0x7FFFFFFFh



ENC_INIT_HALL_
STATUS


ENC_INIT_HALL_PHI_
E_ABN_OFFSET


ENC_INIT_HALL_PHI_
E_AENC_OFFSET


ENC_INIT_HALL_PHI_
A_AENC_OFFSET


SINGLE_PIN_IF_
TARGET_TORQUE


SINGLE_PIN_IF_
PWM_DUTY_CYCLE


SINGLE_PIN_IF_
TARGET_VELOCITY


SINGLE_PIN_IF_
TARGET_POSITION


RW 0x6Fh INTERIM_ADDR



0x0h 0x0h 0xFFFFh


0x0h 0x0h 0xFFFFh


0x0h 0x0h 0xFFFFh


0x0h 0x0h 0xFFFFh


0x0h -0x8000h 0x8000h


0x0h -0x8000h 0x8000h


0x0h -0x80000000h 0x7FFFFFFFh


0x0h -0x80000000h 0x7FFFFFFFh



INTERIM_ADDR 0x0h 0x0h 0xD7h


RW 0x75h ADC_VM_LIMITS


ADC_VM_LIMIT_LOW 0xFFFFh 0x0h 0xFFFFh


ADC_VM_LIMIT_HIGH 0xFFFFh 0x0h 0xFFFFh


R 0x76h TMC4671_INPUTS_
RAW


A of ABN_RAW 0x0h 0x0h 0x1h


B of ABN_RAW 0x0h 0x0h 0x1h


N of ABN_RAW 0x0h 0x0h 0x1h


                    - 0x0h 0x0h 0x1h


A of ABN_2_RAW 0x0h 0x0h 0x1h


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 125 / 153


B of ABN_2_RAW 0x0h 0x0h 0x1h


N of ABN_2_RAW 0x0h 0x0h 0x1h


                    - 0x0h 0x0h 0x1h



HALL_UX of HALL_
RAW



0x0h 0x0h 0x1h



HALL_V of HALL_RAW 0x0h 0x0h 0x1h



HALL_WY of HALL_
RAW



0x0h 0x0h 0x1h




            - 0x0h 0x0h 0x1h


REF_SW_R_RAW 0x0h 0x0h 0x1h


REF_SW_H_RAW 0x0h 0x0h 0x1h


REF_SW_L_RAW 0x0h 0x0h 0x1h


ENABLE_IN_RAW 0x0h 0x0h 0x1h


STP of DIRSTP_RAW 0x0h 0x0h 0x1h


DIR of DIRSTP_RAW 0x0h 0x0h 0x1h


PWM_IN_RAW 0x0h 0x0h 0x1h


            - 0x0h 0x0h 0x1h


HALL_UX_FILT 0x0h 0x0h 0x1h


HALL_V_FILT 0x0h 0x0h 0x1h


HALL_WY_FILT 0x0h 0x0h 0x1h


            - 0x0h 0x0h 0x1h


            - 0x0h 0x0h 0x1h


            - 0x0h 0x0h 0x1h


            - 0x0h 0x0h 0x1h


            - 0x0h 0x0h 0x1h


PWM_IDLE_L_RAW 0x0h 0x0h 0x1h


PWM_IDLE_H_RAW 0x0h 0x0h 0x1h


            - 0x0h 0x0h 0x1h


            - 0x0h 0x0h 0x1h


R 0x77h TMC4671_OUTPUTS_
RAW



TMC4671_OUTPUTS_
RAW[0]


TMC4671_OUTPUTS_
RAW[1]


TMC4671_OUTPUTS_
RAW[2]


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



0x0h 0x0h 0x1h


0x0h 0x0h 0x1h


0x0h 0x0h 0x1h


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 126 / 153



TMC4671_OUTPUTS_
RAW[3]


TMC4671_OUTPUTS_
RAW[4]


TMC4671_OUTPUTS_
RAW[5]


TMC4671_OUTPUTS_
RAW[6]


TMC4671_OUTPUTS_
RAW[7]


RW 0x78h STEP_WIDTH



0x0h 0x0h 0x1h


0x0h 0x0h 0x1h


0x0h 0x0h 0x1h


0x0h 0x0h 0x1h


0x0h 0x0h 0x1h



STEP_WIDTH 0x0h -0x80000000h 0x7FFFFFFFh


RW 0x79h UART_BPS


UART_BPS 0x00009600h 0x0h 0xFFFFFFh


RW 0x7Bh GPIO_dsADCI_
CONFIG



GPIO_dsADCI_
CONFIG[0]


GPIO_dsADCI_
CONFIG[1]


GPIO_dsADCI_
CONFIG[2]


GPIO_dsADCI_
CONFIG[3]


GPIO_dsADCI_
CONFIG[4]


GPIO_dsADCI_
CONFIG[5]


GPIO_dsADCI_
CONFIG[6]



0x0h 0x0h 0x1h


0x0h 0x0h 0x1h


0x0h 0x0h 0x1h


0x0h 0x0h 0x1h


0x0h 0x0h 0x1h


0x0h 0x0h 0x1h


0x0h 0x0h 0x1h



GPO 0x0h 0x0h 0xFFh


GPI 0x0h 0x0h 0xFFh


RW 0x7Ch STATUS_FLAGS


STATUS_FLAGS[0] 0x0h 0x0h 0x1h


STATUS_FLAGS[1] 0x0h 0x0h 0x1h


STATUS_FLAGS[2] 0x0h 0x0h 0x1h


STATUS_FLAGS[3] 0x0h 0x0h 0x1h


STATUS_FLAGS[4] 0x0h 0x0h 0x1h


STATUS_FLAGS[5] 0x0h 0x0h 0x1h


STATUS_FLAGS[6] 0x0h 0x0h 0x1h


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 127 / 153

|STATUS_FLAGS[7]<br>STATUS_FLAGS[8]<br>STATUS_FLAGS[9]<br>STATUS_FLAGS[10]<br>STATUS_FLAGS[11]<br>STATUS_FLAGS[12]<br>STATUS_FLAGS[13]<br>STATUS_FLAGS[14]<br>STATUS_FLAGS[15]<br>STATUS_FLAGS[16]<br>STATUS_FLAGS[17]<br>STATUS_FLAGS[18]<br>STATUS_FLAGS[19]<br>STATUS_FLAGS[20]<br>STATUS_FLAGS[21]<br>STATUS_FLAGS[22]<br>STATUS_FLAGS[23]<br>STATUS_FLAGS[24]<br>STATUS_FLAGS[25]<br>STATUS_FLAGS[26]<br>STATUS_FLAGS[27]<br>STATUS_FLAGS[28]<br>STATUS_FLAGS[29]<br>STATUS_FLAGS[30]<br>STATUS_FLAGS[31]|0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h<br>0x0<br>h|0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h<br>0x0 0x1<br>h h|
|---|---|---|
|RW<br>0x7Dh<br>STATUS_MASK<br>WARNING_MASK|0x0h|0x0h<br>0xFFFFFFFFh|



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 128 / 153

## **8 Pinning**


_Figure 39:_ _TMC4671 Pinout with 3 phase Power stage and BLDC Motor_


_Figure 40:_ _TMC4671 Pinout with Stepper Motor_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-127-0.png)

![](images/TMC4671-LA_datasheet_rev2.08.pdf-127-1.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 129 / 153


_Figure 41:_ _TMC4671 Pinout with DC Motor or Voice Coil_


_**Info**_ All power supply pins (VCC, VCC_CORE) must be connected.


All ground pins (GND, GNDA, ...) must be connected.


Analog inputs (AI) are 5V single ended or differential inputs (Input range: GNDA
to V5). Use voltage dividers or operational amplifiers to scale down higher input
voltages.


Digital inputs (I) resp. (IO) are 3.3V single ended inputs.

|IO|Description|
|---|---|
|AI|analog input, 3.3V|
|I|digital input, 3.3V|
|IO|digital input or digital output, direction programmable, 3.3V|
|O|digital output, 3.3V|



_Table 32:_ _Pin Type Definition_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-128-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 130 / 153

## **9 TMC4671 Pin Table**

|Name|Pin|IO|Description|
|---|---|---|---|
|nRST|50|I|active low reset input|
|CLK|51|I|clock input; needs to be 25 MHz for correct timing|
|TEST|54|I|TEST input, must be connected to GND|
|ENI|55|I|enable input; If high, controllers and PWM are en-<br>abled|
|ENO|32|O|enable output; feeds through ENI when CLK is ap-<br>plied and IC is not in reset condition|
|STATUS|12|O|output for interrupt of CPU (Warning & Status<br>Change)|
|SPI_nSCS|6|I|SPI active low chip select input|
|SPI_SCK|7|I|SPI clock input|
|SPI_MOSI|8|I|SPI master out slave input|
|SPI_MISO|9|O|SPI master in slave output, high impedance, when<br>SPI_nSCS = ’1’|
|UART_RXD|10|I|UART receive data RxD for in-system-user com-<br>munication channel|
|UART_TXD|11|O|UART transmit data TXD for in-system-user com-<br>munication channel|
|PWM_I|58|I|PWM input for target value generation|
|DIR|56|I|direction input of step-direction interface|
|STP|57|I|step pulse input for step-direction interface|
|HALL_UX|38|I|digital hall input H1 for 3-phase (U) or 2-phase (X)|
|HALL_V|37|I|digital hall input H2 for 3-phase (V)|
|HALL_WY|36|I|digital hall input H3 for 3-phase (W) or 2-phase (Y)|
|ENC_A|35|I|A input of incremental encoder|
|ENC_B|34|I|B input of incremental encoder|
|ENC_N|33|I|N input of incremental encoder|
|ENC2_A|64|I|A input of incremental encoder|
|ENC2_B|65|I|B input of incremental encoder|
|ENC2_N|66|I|N input of incremental encoder|
|REF_L|67|I|Left (L) reference switch|
|REF_H|68|I|Home (H) reference switch|
|REF_R|69|I|Right (R) reference switch|
|ADC_I0_POS|16|AI|pos. input for phase current signal measurement<br>I0 (I_U, I_X)|



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 131 / 153

|Name|Pin|IO|Description|
|---|---|---|---|
|ADC_I0_NEG|17|AI|neg. input for phase current signal measurement<br>I0 (I_U, I_X)|
|ADC_I1_POS|18|AI|pos. input for phase current signal measurement<br>I1 (I_V, I_W, I_Y)|
|ADC_I1_NEG|19|AI|neg. input for phase current signal measurement<br>I1 (I_V, I_W, I_Y)|
|ADC_VM|20|AI|analog input for motor supply voltage divider (VM)<br>measurement|
|AGPI_A|21|AI|analog general purpose input A (analog GPI)|
|AGPI_B|22|AI|analog general purpose input B (analog GPI)|
|AENC_UX_POS|25|AI|pos. analog input for Hall or analog encoder sig-<br>nal, 3-phase (U) or 2-phase (X (cos))|
|AENC_UX_NEG|26|AI|neg. analog input for Hall or analog encoder sig-<br>nal, 3-phase (U) or 2-phase (X (cos))|
|AENC_VN_POS|27|AI|pos. analog input for Hall or analog encoder sig-<br>nal, 3-phase (V) or 2-phase (N)|
|AENC_VN_NEG|28|AI|neg. analog input for Hall or analog encoder sig-<br>nal, 3-phase (V) or 2-phase (N)|
|AENC_WY_POS|29|AI|pos. analog input for Hall or analog encoder sig-<br>nal, 3-phase (W) or 2-phase (Y (sin))|
|AENC_WY_NEG|30|AI|neg. analog input for Hall or analog encoder sig-<br>nal, 3-phase (W) or 2-phase (Y (sin))|
|GPIO0 / ADC_I0_MCD|70|IO|GPIO or ∆Σ-Demodulator clock input MCLKI,<br>clock output MCLKO, or single bit DAC output<br>MDAC for ADC_I_0|
|GPIO1 / ADC_I1_MCD|71|IO|GPIO or ∆Σ-Demodulator clock input MCLKI,<br>clock output MCLKO, or single bit DAC output<br>MDAC for ADC_I_1|
|GPIO2 / ADC_VM_MCD|74|IO|GPIO or ∆Σ-Demodulator clock input MCLKI,<br>clock output MCLKO, or single bit DAC output<br>MDAC for ADC_VM_MCD|
|GPIO3 / AGPI_A_MCD / DBGSPI_nSCS|75|IO|GPIO or ∆Σ-Demodulator clock input MCLKI,<br>clock output MCLKO, or single bit DAC output<br>MDAC for AENC_UX_MCD, SPI debug port pin<br>DBGSPI_nSCS|
|GPIO4 / AGPI_B_MCD / DBGSPI_SCK|76|IO|GPIO or ∆Σ-Demodulator clock input MCLKI,<br>clock output MCLKO, or single bit DAC output<br>MDAC for AENC_VN_MCD, SPI debug port pin<br>DBGSPI_SCK|
|GPIO5 / AENC_UX_MCD / DBGSPI_MOSI|1|IO|GPIO or ∆Σ-Demodulator clock input MCLKI,<br>clock output MCLKO, or single bit DAC output<br>MDAC for AENC_WY_MCD, SPI debug port pin<br>DBGSPI_MOSI|



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 132 / 153

|Name|Pin|IO|Description|
|---|---|---|---|
|GPIO6 / AENC_VN_MCD / DBGSPI_MISO|4|IO|GPIO or ∆Σ-Demodulator clock input MCLKI,<br>clock output MCLKO, or single bit DAC out-<br>put MDAC for AGPI_A_MCD, SPI debug port pin<br>DBGSPI_MISO|
|GPIO7 / AENC_WY_MCD / DBGSPI_TRG|5|IO|GPIO or ∆Σ-Demodulator clock input MCLKI,<br>clock output MCLKO, or single bit DAC out-<br>put MDAC for AGPI_B_MCD, SPI debug port pin<br>DBGSPI_TRG|
|PWM_IDLE_H|59|I|idle level of high side gate control signals (not<br>used)|
|PWM_IDLE_L|60|I|idle level of low side gate control signals (not<br>used)|
|PWM_UX1_H|39|O|high side gate control output U (3-phase) resp. X1<br>(2-phase)|
|PWM_UX1_L|40|O|low side gate control output U (3-phase) resp. X1<br>(2-phase)|
|PWM_VX2_H|41|O|high side gate control output V (3-phase) resp. X2<br>(2-phase)|
|PWM_VX2_L|42|O|low side gate control output V (3-phase) resp. X2<br>(2-phase)|
|PWM_WY1_H|46|O|high side gate control output W (3-phase) resp. Y1<br>(2-phase)|
|PWM_WY1_L|47|O|low side gate control output W (3-phase) resp. Y1<br>(2-phase)|
|PWM_Y2_H|48|O|high side gate control output Y2 (2-phase only)|
|PWM_Y2_L|49|O|low side gate control output Y2 (2-phase only)|
|BRAKE|31|O|brake chopper control output signal|



_Table 33:_ _Functional Pin Description_


Feedback input pins that are not needed in target application can be left open or tied to GND.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 133 / 153

|Name|Pin|IO|Description|
|---|---|---|---|
|VCCIO1|2|3.3V|digital IO supply voltage; use 100 nF decoupling capacitor|
|VCCIO2|13|3.3V|digital IO supply voltage; use 100 nF decoupling capacitor|
|VCCIO3|43|3.3V|digital IO supply voltage; use 100 nF decoupling capacitor|
|VCCIO4|52|3.3V|digital IO supply voltage; use 100 nF decoupling capacitor|
|VCCIO5|61|3.3V|digital IO supply voltage; use 100 nF decoupling capacitor|
|VCCIO6|72|3.3V|digital IO supply voltage; use 100 nF decoupling capacitor|
|GNDIO1|3|0V|digital IO ground|
|GNDIO2|14|0V|digital IO ground|
|GNDIO3|44|0V|digital IO ground|
|GNDIO4|53|0V|digital IO ground|
|GNDIO5|62|0V|digital IO ground|
|GNDIO6|73|0V|digital IO ground|
|VCCCORE1|15|1.8V|digital core supply voltage output; use 100 nF decoupling ca-<br>pacitor|
|VCCCORE2|45|1.8V|digital core supply voltage output; use 100 nF decoupling ca-<br>pacitor|
|VCCCORE3|63|1.8V|digital core supply voltage output; use 100 nF decoupling ca-<br>pacitor|
|V5|23|5V|analog reference voltage|
|GNDA|24|0V|analog reference ground|
|GNDPAD|–|0V|bottom ground pad|



_Table 34:_ _Supply Voltage Pins and Ground Pins_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 134 / 153

## **10 Electrical Characteristics**


**10.1** **Absolute Maximum Ratings**


The maximum ratings may not be exceeded under any circumstances. Operating the circuit at or
near more than one maximum rating at a time for extended periods shall be avoided by application
design.













|Parameter|Symbol|Min|Max|Unit|
|---|---|---|---|---|
|Digital I/O supply voltage|VCCIO||3.6|V|
|Logic input voltage|VI||3.6|V|
|Maximum current drawn on VCCIO with no load on pins|I_IO||70|mA|
|Maximum current drawn on VCCIO with no load on pins and<br>clock oﬀ|I_IO_0Hz||3|mA|
|Maximum current drawn on V5 at fCLK = 25MHz|I_V5||25|mA|
|Maximum current to / from digital pins and analog low voltage<br>I/Os|IIO||10|mA|
|Junction temperature|TJ|-40|125|°C|
|Storage temperature|TSTG|-55|150|°C|
|ESD-Protection for interface pins (Human body model, HBM)|VESDAP||2|kV|
|ESD-Protection for handling (Human body model, HBM)|VESD1||2|kV|
|ADC input voltage|VAI|0|5|V|


_Table 35:_ _Absolute Maximum Ratings_


VCCCORE is generated internally from VCCIO and shall not be overpowered by external supply.


**10.2** **Electrical Characteristics**


**10.2.1** **Operational Range**

|Parameter|Symbol|Min|Max|Unit|
|---|---|---|---|---|
|Junction temperature|TJ|-40|125|°C|
|Digital I/O 3.3V supply voltage|VIO3V|3.15|3.45|V|
|Core supply voltage|VCC_CORE|1.65|1.95|V|



_Table 36:_ _Operational Range_


The ∆Σ ADCs can operate in differential or single ended mode. In differential mode the differential input
voltage range must be in between -2.5V and +2.5V. However, it is recommended to use the input voltage
range from -1.25V to 1.25V, due to non-linearity of ∆Σ ADCs. In Single ended mode the operational input range of the positive input channel should be between 0V and 2.5V. Recommended maximum input
voltage is 1.25V.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 135 / 153


**10.2.2** **DC Characteristics**


DC characteristics contain the spread of values guaranteed within the specified supply voltage range unless otherwise specified. Typical values represent the average value of all parts measured at +25 °C. Temperature variation also causes stray to some values. A device with typical values will not leave Min/Max
range within the full temperature range.

|Parameter|Symbol|Condition|Min|Typ|Max|Unit|
|---|---|---|---|---|---|---|
|Input voltage low level|VINL|VCCIO = 3.3V|-0.3||0.8|V|
|Input voltage high level|VINH|VCCIO = 3.3V|2.3||3.6|V|
|Input with pull-down||VIN = 3.3V|5|30|110|_µ_A|
|Input with pull-up||VIN = 0V|-110|-30|-5|_µ_A|
|Input low current||VIN = 0V|-10||10|_µ_A|
|Input high current||VIN = VCCIO|-10||10|_µ_A|
|Output voltage low level|VOUTL|VCCIO = 3.3V|0.4|||V|
|Output voltage high level|VOUTH|VCCIO = 3.3V|2.64|||V|
|Output driver strength standard|IOUT_DRV||4|||mA|
|Input impedance of Analog Input|R_ADC|TJ = 25°C|85|100|115|kΩ|



_Table 37:_ _DC Characteristics_


All I/O lines include Schmitt-Trigger inputs to enhance noise margin.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 136 / 153

## **11 Sample Circuits**


Please consider electrical characteristics while designing electrical circuitry. Most Sample Circuits in this
chapter were taken from the evalutation board for the TMC4671 (TMC4671-EVAL).


**11.1** **Supply Pins**


Please provide VCCIO and V5 to the TMC4671. VCC_CORE is internally generated and needs just an external decoupling capacitor. Place one 100nF decoupling capacitor at every supply pin. Table 38 lists
additional needed decoupling capacitors.

|Pin Name|Supply Voltage|Additional Cap.|
|---|---|---|
|V5|5V|4.7uF|
|VCCIO|3.3V|4.7uF & 470nF|
|VCCCORE|1.8V|none|



_Table 38:_ _Additional decoupling capacitors for supply voltages_


**11.2** **Clock and Reset Circuitry**


The TMC4671 needs an external oscillator for correct operation at 25 MHz. Lower frequency results in
respective scaling of timings. Higher frequency is not supported. The internally generated active low
reset can be externally overwritten. If users want to toggle the reset, a pulse length of at least 500 ns is
recommended. When not used, please apply a 10k Pull up resistor and make sure all supply voltages are
stable.


**11.3** **Digital Encoder, Hall Sensor Interface and Reference Switches**


Digital encoders, Hall sensors and reference switches usually operate on a supply voltage of 5V. As the
TMC4671 is usually operated at a VCCIO Voltage of 3.3V, a protection circuit for the TMC4671 input pin is
needed. In fig. 42 a sample circuit for the ENC_A signal is shown, which can be reused for all encoder and
Hall signals as well as for reference switch signals. Parametrization of the components is given in table
39 for different operations.


_Figure 42:_ _Sample Circuit for Interfacing of an Encoder Signal_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-135-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 137 / 153

|Application|R<br>P U|R<br>P D|R<br>LN|C<br>P|
|---|---|---|---|---|
|5 V Encoder signal|4K7|n.c.|100R|100pF|



_Table 39:_ _Reference Values for circuitry components_


The raw signal (ENC_A_RAW) is divided by a voltage divider and filtered by a low-pass filter. A pull up
resistor is applied for open collector encoder output signals. Diodes protect the input pin (ENC_A) against
over- and undervoltage. The cutoff-frequency of the low-pass is:


1
_fc_ = (50)
2 _π RP DCP_


**11.4** **Analog Frontend**


Analog Encoders are encoding the motor position into sinusoidal signals. These signals need to be digitalized by the TMC4671 in order to determine the rotor position. The input voltage range depends on V5
input, which is usually 5V and GNDA (usually 0V). Due to nonlinearity issues of the ADC near input limits,
an ADC input value from 1V to 4V is recommended. For a single ended application, the sample circuit
from fig. 43 can be used. All single ended analog input pins (AGPI_A, AGPI_B and ADC_VM) have their
negative input value tied to GNDA internally, so this sample circuit can also be used for them.


_Figure 43:_ _Sample Circuit for Interfacing of a single ended analog signal_


If the power stage and the TMC4671 share a common ground, the ADC_VM input signal can be generated
by a voltage divider to scale the voltage down to the needed range.
If the analog encoder has differential output signals, these can be used without signal conditioning (no OP
AMPs), when voltage range matches. Differential analog inputs can be used to digitize differential analog
input signals with high common mode voltage error suppression.


**11.5** **Phase Current Measurement**


The TMC4671 requires two phase currents of a 2 or 3 phase motor to be measured. For a DC Motor only
one current in the phase needs to be measured (see Fig. 45). In the ADC engine mapping of current signals
to motor phases can be changed. Default setting is I0 to be the current running into the motor in phase
U for a 3 phase motor. Respectively the current running into the motor from half-bridge X1 of a 2 phase
motor. Figs. 44 and 45 illustrates the currents to be measured and their positive direction.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-136-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 138 / 153


_Figure 44:_ _Phase current measurement:_ _Current directions for 2 and 3 phase motors_


_Figure 45:_ _Phase current measurement:_ _Current direction for DC or Voice Coil Motor_


There are two main options for measuring the phase currents as described above. First option is to use
a shunt resistor and a shunt amplifier like the LT1999 or the AD8418A. The other option is to use a real
current sensor, which uses the Hall effect or other magnetic effects to implement an isolated current
measurement. Shunt measurement might be the more cost-effective solution for low voltage applications
up to 100V, while current sensors are more useful at higher voltage levels.
In general the sample circuit in fig. 46 can be used for shunt measurement circuitry. Please consider
design guidelines of shunt amplifier supplier additionally. TRINAMIC also supplies power stage boards


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-137-0.png)

![](images/TMC4671-LA_datasheet_rev2.08.pdf-137-1.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 139 / 153


with current shunt measurement circuitry (TMC-UPS10A/70V-EVAL). For current measurement also current sensors with voltage output can be used. These could use the Hall effect or other magnetic effects.
Main concerns to take about is bandwidth, accuracy and measurement range.


_Figure 46:_ _Current Shunt Amplifier Sample Circuit_


**11.6** **Power Stage Interface**


The TMC4671 is equipped with a configurable PWM engine for control of various gate drivers. Gate driver
switch signals can be matched to power stage needs. This includes signal polarities, frequency, BBMtimes for low and high side switches, and an enable signal. Please consider gate driver circuitry, when
connecting to the TMC4671.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-138-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 140 / 153

## **12 Setup Guidelines**


For easy setup of the TMC4671 on a given hardware platform like the TMC4671 Evaluation-Kit, the user
should follow these general guidelines in order to safely set up the system for various modes of operation.


_**Info**_ These guidelines fit to hardware platforms which are comparable to the
TMC4671-Evaluation Kit. If system structure differs, configuration has to be adjusted.
Please also make use of the RTMI Adapter and the TMCL IDE to setup the system
as it reduces commissioning time significantly.


**Step 0:** **Setup of SPI communication**
As a first step of the configuration of the TMC4671 the SPI communication should be tested by reading
and writing for example to the first registers for identification of the silicon. If communication fails, please
check CLK and nRST signals. For easy software setup the TMC API provided on the TRINAMIC website can
be used.
**Step 1:** **Check connections**
Register TMC4671_INPUTS_RAW can be accessed to see if all connected digital inputs are working correctly
e.g. sensor signals can be checked by turning the motor manually.
**Step 2:** **Setup of PWM and Gatedriver configuration**
The user should choose the connected motor and the number of polepairs by setting register MOTOR_
TYPE_N_POLE_PAIRS. For a DC motor the number of pole pairs should be set to one. The PWM can be configured with the corresponding registers PWM_POLARITIES (Gate Driver Polarities), PWM_MAXCNT (PWM
Frequency), PWM_BBM_H_BBM_L (BBM times), and PWM_SV_CHOP (PWM mode). After setting the register PWM_SV_CHOP to 7 the PWM is on and ready to use.
Please check PWM outputs after turning on the PWM, if you are using a new hardware design.
**Step 3:** **Open Loop Mode**
In the Open Loop Mode the motor is turned by applying voltage to the motor. This mode is useful for test
and setup of ADCs and position sensors. It is activated by setting the corresponding registers for PHI_
E_SELECTION, and MODE_MOTION. With UD_EXT the applied voltage can be regulated upwards until the
motor starts to turn. Acceleration and target velocity can be changed by their respective registers.
**Step 4:** **Setup of ADC for current measurement**
Please setup the current measurement by choosing your applications ADC configuration. Make sure to
match decimation rate of the Delta Sigma ADCs to your chosen PWM frequency.
When the motor turns in Open Loop Mode the current measurement can be easily calibrated. Please
match offset and gain of phase current signals by setting the corresponding registers. Please also make
sure for a new hardware setup, that current measurements and PWM channels are matched. This can
be done by matching phase voltages and phase currents. Register ADC_I_SELECT can be used to switch
relations.
**Step 5:** **Setup of Feedback Systems**
In Open Loop Mode also the feedback systems can be checked for correct operation. Please configure
registers related to used position sensor(s) and compare against Open Loop angles. Use encoder initialization routines to set angle offsets for relative position encoders according to application needs.
**Step 6:** **Setup of FOC Controllers**
Please configure your application’s feedback system and configure position and velocity signal switches
accordingly inside the FOC. Configure controller output limits according to you needs.
Setup PI controller parameters for used FOC controllers. Start with the current controller, followed by the
velocity controller, followed by the position controller. Stop configuration at your desired cascade level.
TRINAMIC recommends to set the PI controller parameters by support of the RTMI, as it supports realtime access to registers and the TMCL IDE offers tools for automated controller tuning. Controller tuning
without realtime access might lead to poor performance.
Please choose afterwards your desired Motion Mode and feed in reference values.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 141 / 153


**Step 7:** **Advanced Functions**
For performance improvements Biquad filters and feed forward control can be applied.

## **13 Package Dimensions**


Package: QFN76, 0.4 mm pitch, size 11.5 mm x 6.5 mm.


_Figure 47:_ _QFN76 Package Outline_


QFN76 Package Dimensions in mm

|Description|Dimension[mm]|min. typ. max.|
|---|---|---|
|Total Thickness<br>Stand Oﬀ<br>Mold Thickness<br>L/F Thickness<br>Lead Width<br>Body Width|A<br>A1<br>A2<br>A3<br>b<br>D|0.80<br>0.85<br>0.90<br>0.00<br>0.035<br>0.05<br>—<br>0.65<br>—<br>0.203 REF<br>0.15<br>0.2<br>0.25<br>10.5 BSC|



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-140-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 142 / 153



![](images/TMC4671-LA_datasheet_rev2.08.pdf-141-0.png)



_Table 40:_ _Package Outline Dimensions_


Figure 48 shows the package from top view. Decals for some CAD programs are available on the product’s
website.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 143 / 153


_Figure 48:_ _Pinout of TMC4671 (Top View)_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



![](images/TMC4671-LA_datasheet_rev2.08.pdf-142-0.png)
TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 144 / 153

## **14 Supplemental Directives**


**14.1** **Producer Information**


**14.2** **Copyright**


TRINAMIC owns the content of this user manual in its entirety, including but not limited to pictures, logos,
trademarks, and resources. © Copyright 2022 TRINAMIC. All rights reserved. Electronically published by
TRINAMIC, Germany.


Redistribution of sources or derived formats (for example, Portable Document Format or Hypertext Markup
Language) must retain the above copyright notice, and the complete data sheet, user manual, and documentation of this product including associated application notes; and a reference to other available
product-related documentation.


**14.3** **Trademark Designations and Symbols**


Trademark designations and symbols used in this documentation indicate that a product or feature is
owned and registered as trademark and/or patent either by TRINAMIC or by other manufacturers, whose
products are used or referred to in combination with TRINAMIC’s products and TRINAMIC’s product documentation.


This Datasheet is a non-commercial publication that seeks to provide concise scientific and technical user
information to the target user. Thus, trademark designations and symbols are only entered in the Short
Spec of this document that introduces the product at a quick glance. The trademark designation /symbol
is also entered when the product or feature name occurs for the first time in the document. All trademarks
and brand names used are property of their respective owners.


**14.4** **Target User**


The documentation provided here, is for programmers and engineers only, who are equipped with the
necessary skills and have been trained to work with this type of product.


The Target User knows how to responsibly make use of this product without causing harm to himself or
others, and without causing damage to systems or devices, in which the user incorporates the product.


**14.5** **Disclaimer:** **Life Support Systems**


TRINAMIC Motion Control GmbH & Co. KG does not authorize or warrant any of its products for use in
life support systems, without the specific written consent of TRINAMIC Motion Control GmbH & Co. KG.


Life support systems are equipment intended to support or sustain life, and whose failure to perform,
when properly used in accordance with instructions provided, can be reasonably expected to result in
personal injury or death.


Information given in this document is believed to be accurate and reliable. However, no responsibility
is assumed for the consequences of its use nor for any infringement of patents or other rights of third
parties which may result from its use. Specifications are subject to change without notice.


**14.6** **Disclaimer:** **Intended Use**


The data specified in this user manual is intended solely for the purpose of product description. No representations or warranties, either express or implied, of merchantability, fitness for a particular purpose


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 145 / 153


or of any other nature are made hereunder with respect to information/specification or the products to
which information refers and no guarantee with respect to compliance to the intended use is given.


In particular, this also applies to the stated possible applications or areas of applications of the product.
TRINAMIC products are not designed for and must not be used in connection with any applications where
the failure of such products would reasonably be expected to result in significant personal injury or death
(safety-Critical Applications) without TRINAMIC’s specific written consent.


TRINAMIC products are not designed nor intended for use in military or aerospace applications or environments or in automotive applications unless specifically designated for such use by TRINAMIC. TRINAMIC
conveys no patent, copyright, mask work right or other trade mark right to this product. TRINAMIC assumes no liability for any patent and/or other trade mark rights of a third party resulting from processing
or handling of the product and/or any other use of the product.


**14.7** **Collateral Documents & Tools**


This product documentation is related and/or associated with additional tool kits, firmware and other
items, as provided on the product page at: [www.trinamic.com.](http://www.trinamic.com)


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 146 / 153

## **15 Errata of TMC4671-LA/-ES2/-ES**


**15.1** **Errata of TMC4671-LA**


**PID_POSITION_ACTUAL** **glitches** **when** **calculated** **from** **Hall** **sensor** **angle** **and** **Hall** **Interpolation** **is**
**activated**
Hall interpolation is not intended for positioning applications, especially not with changes of direction.
In the following register configuration glitches on PID_POSITION_ACTUAL 0x6B can occur:










|Register|Value (descr.)|Note|
|---|---|---|
|0x51 POSITION_SELECTION|5 (PHI_E_HALL selected)<br>6 (PHI_M_HALL selected)<br>0 (Use selection in register 0x52)|Here PID_POSITION_ACTUAL<br>is calculated from PHI_E_HALL<br>or PHI_M_HALL.|
|0x52 PHI_E_SELECTION|5 (PHI_E_HALL selected)|5 (PHI_E_HALL selected)|
|0x33 HALL_MODE|bit 8 = 1 (Hall interpolation enabled)|bit 8 = 1 (Hall interpolation enabled)|



_Table 41:_ _Registersettings susceptible to glitches_


In this configuration PID_POSITION_ACTUAL might not be able to count full revolutions correctly as the
interpolated PHI_E_HALL might glitch when motor stops. As a result a full revolution is counted where
there was not one completed. If the user does not rely on correct position information in register PID_
POSITION_ACTUAL the silicon error does not affect the application.


**Workaround**
The hall sensor interpolation needs to be switched off.


**15.2** **Fixes of TMC4671-LA/-ES2 vs.** **Errata of TMC4671-ES**







|#|TMC4671-ES Erratum|TMC4671-LA Fix|Description|
|---|---|---|---|
|1|SPI slave MSB read error|SPI slave correction|read via SPI slave now works correct|
|2|RTMI critical timing|RTMI enhanced|RTMI works with isolated RTMI-USB<br>IF|
|3|PI advanced controller|PI scaling updated|scaling selectable available|
|4|ADC group clock cross talk|ADC clocks corrected|crosstalk eliminated|
|5|PWM_IDLE_L/_H un-used|PWM outputs are at high<br>impedance until ENI is<br>high|User can conﬁgure PWM signal polar-<br>ity and afterwards enable PWM sig-<br>nals. Idle state can be set with PD or<br>PU resistor on PWM outputs|
|6|Space Vector PWM|SVPWM<br>scaling<br>cor-<br>rected|SVPWM gives +12% eﬀective voltage.<br>With Space Vector PWM enabled volt-<br>age scaling is modiﬁed.|
|7|step direction target position|processing corrected|step direction as target position|
|8|ABN encoder register access|access corrected|ABN counter over-writeable|


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 147 / 153







|9|ENI and ENO|function updated|ENI and ENO act as enable signals|
|---|---|---|---|
|10|-|Hall sync PWM sample|optional Hall sampling at PWM cen-<br>ter|
|11|-|PWM_POLARITIES regis-<br>ter initialized to 0x0|Active high PWM signal polarity is pre-<br>ferred|
|12|-|Registers<br>PHI_M_EXT<br>and<br>POSITION_EXT<br>removed|Registers were not used|
|13|Watchdog not properly working|Watchdog removed|Watchdog was intended to monitor<br>CLK. Watchdog ﬂag can not be reset.|


_Table 42:_ _TMC4671-ES Errata vs._ _TMC4671-ES2/-LA Fixes_


**15.3** **Errata of TMC4671-ES Engineering Samples as Reference**


1. SPI Slave Interface
The SPI Slave Interface in the TMC4671-ES might show corrupted MSB of read data.


2. Realtime Monitoring Interface
The RTMI of TMC4671-ES could not be used with galvanic isolation due to timing issue.


3. PI Controllers
The P Factor of the TMC4671-ES in the advanced position controller was not properly scaled and the
integrator in the advanced PI controller was not reset when P or I parameters are set to zero.


4. Integrated ADCs
The Delta Sigma ADCs of TMC4671-ES showed signal cross talk caused by ADC clock cross talk.


5. Pins PWM_IDLE_H and PWM_IDLE_L without function
Pins PWM_IDLE_H and PWM_IDLE_L of TMC4671-ES were proposed to set gate driver control polarity.


6. Space Vector PWM does not allow higher voltage utilization
The Space vector PWM of the TMC4671-ES does not allow higher voltage utilization.


7. Step Direction Counter not used as Target Position
The step direction counter of the TMC4671-ES correctly counts but is not available as target position.


8. Register write access to ABN encoder count register and N pulse status bits
Write access to count registers of TMC4671-ES cleared theses to zero and encoder N pulse input
signals were not available within the status register.


9. ENO and ENI
ENI (ENable Input) and ENO (ENable Output) of TMC4671-ES did partially work as intended (incomplete reset assignment, missing error sum clear on disable).


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 148 / 153


**15.4** **Actions to Avoid Trouble**


What should be taken into account when moving from TMC4671-ES to TMC4671-LA?


  - update P and I parameter for the advanced PI controller in case of switching numerical representation from Q8.8 to Q4.12 (classical PI controller is un-changed)


  - mount pull-up resistors if required for gate driver control signals during power-on reset


  - check setting of SVPWM control bit to avoid un-wanted speed-up by SVPWM in torque mode (poweron default is disable without speed-up)


  - check setting of additional hall_sync_pwm_enable bit for high speed application with usage of Hall
signals (power-on default is disable)


**15.5** **Recommendations**


  - TMC4671-LA (TMC4671-ES2) is drop-in compatible to the TMC4671-ES. Nevertheless, the TMC4671LA needs to be functional qualified as replacement to avoid un-wanted behavior caused by corrections of errata of TMC4671-ES.


For example: The space vector PWM /SVPWM) control bit does not have an effect for the TMC4671-ES
in torque mode. The space vector PWM is corrected for the TMC4671-LA. So, if the SVPWM control bit
is un-wanted enabled for the TMC4671-ES, the TMC4671-LA would run approximately +12% faster
in torque mode with the same settings.


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 149 / 153

## **16 Figures Index**



1 FOC Basic Principle . . . . . . . . . . . 9
2 PID Architectures and Motion Modes 10
3 Orientations UVW (FOC3) and XY (FOC2) 15
4 Compass Motor Model w/ 3 Phases
UVW (FOC3) and Compass Motor
Model w/ 2 Phases (FOC2) . . . . . . . 15
5 Hardware FOC Application Diagram . 16
6 Hardware FOC Block Diagram . . . . . 16
7 SPI Datagram Structure . . . . . . . . 17
8 SPI Timing . . . . . . . . . . . . . . . . 18
9 SPI Timing of Write Access without
pause with fSCK up to 8MHz . . . . . 19
10 SPI Timing of Read Access with pause
(tPAUSE) of 500 ns with fSCK up to
8MHz. . . . . . . . . . . . . . . . . . . . 19
11 Connector for Real-Time Monitoring
Interface (Connector Type: Hirose
DF20F-10DP-1V) . . . . . . . . . . . . . 20
12 UART Read Datagram (TMC4671 register read via UART) . . . . . . . . . . . 22
13 UART Write Datagram (TMC4671 register write via UART) . . . . . . . . . . 22
14 N_POLE_PAIRS - Number of Pole Pairs
(Number of Poles) . . . . . . . . . . . . 26
15 Integer Representation of Angles as
16 bit signed (s16) resp. 16 bit unsigned (u16) . . . . . . . . . . . . . . . 27
16 Input Voltage Ranges of internaql
Delta Sigma ADC Channels . . . . . . 31
17 Delta Sigma ADC Configurations
dsADC_CONFIG (ANALOG (internal),
MCLKO, MCLKI, MDAC) . . . . . . . . . 33
18 ∆Σ ADC Configurations  - MDAC
(Comparator-R-C-R as ∆Σ-Modulator) 37
19 ADC Selector and Scaler with Offset
Correction . . . . . . . . . . . . . . . . 41
20 Number of Pole Pairs npp vs. mechanical angle phi_m and electrical angle
phi_e . . . . . . . . . . . . . . . . . . . 43
21 ABN Incremental Encoder N Pulse . . 44
22 Encoder ABN Timing . . . . . . . . . . 45
23 Hall Sensor Angles . . . . . . . . . . . 46


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



24 Outline of noisy Hall signals (left) due
to electromagnetic interference with
PWM switching and noise cleaned
Hall signals (right) by PWM center
synced sampling of Hall signal vector
(H1 H2 H3) . . . . . . . . . . . . . . . . 47
25 Hall Signal PWM Center Sampling on
PWM_CENTER . . . . . . . . . . . . . . 47
26 Hall Signal Blanking . . . . . . . . . . . 48
27 Analog Encoder (AENC) signal waveforms . . . . . . . . . . . . . . . . . . . 48
28 Analog Encoder (AENC) Selector &
Scaler w/ Offset Correction . . . . . . 49
29 Classic PI Controller Structure . . . . . 54
30 Advanced PI Controller Structure . . . 55
31 PI Controllers for position, velocity
and current . . . . . . . . . . . . . . . 57
32 Inner FOC Control Loop . . . . . . . . 58
33 FOC Transformations . . . . . . . . . . 59
34 Motion Modes . . . . . . . . . . . . . . 59
35 Biquad Filters in Control Structure . . 62
36 PWM Gate Driver Control Polarities . 63
37 FOC3 (three phase motor), FOC2 (two
phase stepper motor), FOC1 (single
phase DC motor) . . . . . . . . . . . . 64
38 BBM Timing . . . . . . . . . . . . . . . 65
39 TMC4671 Pinout with 3 phase Power
stage and BLDC Motor . . . . . . . . . 128
40 TMC4671 Pinout with Stepper Motor 128
41 TMC4671 Pinout with DC Motor or
Voice Coil . . . . . . . . . . . . . . . . . 129
42 Sample Circuit for Interfacing of an Encoder Signal . . . . . . . . . . . . . . . 136
43 Sample Circuit for Interfacing of a single ended analog signal . . . . . . . . 137
44 Phase current measurement: Current
directions for 2 and 3 phase motors . 138
45 Phase current measurement: Current
direction for DC or Voice Coil Motor . 138
46 Current Shunt Amplifier Sample Circuit 139
47 QFN76 Package Outline . . . . . . . . 141
48 Pinout of TMC4671 (Top View) . . . . 143


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 150 / 153

## **17 Tables Index**



1 Order codes . . . . . . . . . . . . . . . 6
2 SPI Timing Parameter . . . . . . . . . 18
3 Possible baudrates and corresponding values for register 0x79 . . . . . . 21
4 Single Pin Interface Motion Modes . . 23
5 GPIO Configuration Overview with ’x’
as don’t care . . . . . . . . . . . . . . . 24
6 Numerical Representations . . . . . . 24
7 Examples of u16, s16, q8.8, q4.12 . . 25
8 Examples of u16, s16, q8.8 . . . . . . 27
9 Delta Sigma ∆Σ ADC Input Stage Configurations . . . . . . . . . . . . . . . . 30
10 Delta Sigma ∆Σ ADC Input Stage Configurations . . . . . . . . . . . . . . . . 31
11 ∆Σ ADC Configurations . . . . . . . . 33
12 Registers for Delta Sigma Configuration 34
13 Delta Sigma MCLK Configurations . . 34
14 Recommended Decimation Parameter MDEC . . . . . . . . . . . . . . . . . 35
15 Recommended input voltage range
from V_MIN25%[V] to V_MAX75%[V]
for internal Delta Sigma Modulators;
V_SUPPLY[V] = 5V is recommended
for the analog part of the TMC4671. . 36
16 Delta Sigma input voltage mapping of
internal Delta Sigma Modulators . . . 36
17 Delta Sigma R-C-R-CMP Configurations 37
18 Delta Sigma input voltage mapping of
external comparator (CMP) . . . . . . 38
19 Example Parameters for ADC_GAIN . 39


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)



20 Scalings and Change Rate Timings of
classical PID controllers for currents,
velocity, and position . . . . . . . . . . 53
21 Motion Modes . . . . . . . . . . . . . . 53
22 PI normalization overview . . . . . . . 55
23 Motion Modes . . . . . . . . . . . . . . 60
24 TABSTatusFlags . . . . . . . . . . . . . 63
25 FOC321 Gate Control Signal Configurations . . . . . . . . . . . . . . . . . . 64
26 Factors for integer to real conversion 66
27 Factors for real to integer conversion 67
28 TABSTatusFlags . . . . . . . . . . . . . 68
29 TMC4671 Registers . . . . . . . . . . . 76
32 Pin Type Definition . . . . . . . . . . . 129
33 Functional Pin Description . . . . . . . 132
34 Supply Voltage Pins and Ground Pins 133
35 Absolute Maximum Ratings . . . . . . 134
36 Operational Range . . . . . . . . . . . 134
37 DC Characteristics . . . . . . . . . . . 135
38 Additional decoupling capacitors for
supply voltages . . . . . . . . . . . . . 136
39 Reference Values for circuitry components . . . . . . . . . . . . . . . . . . . 137
40 Package Outline Dimensions . . . . . 142
41 Registersettings susceptible to glitches 146
42 TMC4671-ES Errata vs. TMC4671ES2/-LS Fixes . . . . . . . . . . . . . . . 147
43 IC Revision . . . . . . . . . . . . . . . . 151
44 Document Revision . . . . . . . . . . . 153


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 151 / 153

## **18 Revision History**


**18.1** **IC Revision**

|Version|Date|Author|Description|
|---|---|---|---|
|V1.0|2017-JUL-03|LL, OM|Engineering samples TMC4671-ES (1v0 2017-07-03-19:43)|
|V1.3|2019-APR-30|LL, OM|Release version TMC4671-LA (1v3 2019-04-30-12:55)|



_Table 43:_ _IC Revision_


**18.2** **Document Revision**

|Version|Date|Author|Description|
|---|---|---|---|
|V0.9|2017-SEP-29|LL, OM|Pre-liminary TMC4671-ES datasheet.|
|V0.91|2018-JAN-30|OM|Changed some typos and added some notes.|
|V0.92|2018-FEB-28|OM|Changed register descriptions.|
|V0.93|2018-MAR-07|OM|Changed some typos and bugs in graphics.|
|V0.94|2018-MAR-14|OM|Added Errata Section.|
|V0.95|2018-MAY-08|OM|Preparations for launch.|
|V1.00|2018-JUN-28|LL|Errata Section updated concerning Step/Dir.|
|V1.01|2018-JUL-19|OM|Added Description for Status Flags|
|V1.02|2018-JUL-31|OM|Added Description for Feed Forward Control Structure|
|V1.03|2018-SEP-06|OM|Description of single pin interface and motion modes added|
|V1.04|2018-DEC-11|OM|Register map and pictures of PI controllers corrected|
|V1.05|2019-JAN-02|OM|Figure 9 corrected, order codes for eval kits added.|
|V1.06|2019-FEB-06|OM|Reference switch processing explained.|
|V1.07|2019-MAR-22|LL|errata updated concerning encoder N pulse, ENI and ENO; ﬁgure il-<br>lustrating PPR, NPP, phi_m, phi_e added; PWM polarities and Hall<br>signal blanking expained in more detail together with drawings.|
|V1.99|2019-SEP-12|LL|register map structure with enhanced readability, minimal move<br>PI controller section of TMC4671-ES removed for TMC4671-LA; SPI<br>timing with tPAUSE added; ﬁgure of Hall signal PWM synced sam-<br>pling option added; section ADC Gain Factors added; section ADC<br>engine updated; sense ampliﬁer type corrected to AD8418; LM319<br>removed as dsMOD example; ADC engine section updated; PWM<br>Engine FOC321 with associated motor connectors added; PID T_N<br>(Nachstellzeit = Reset Time) dsADC input stage conﬁguration, ADC<br>real world scaling (IgainADC[A/LSB], UgainADC[V/LSB]) added, errata<br>section updated;|



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 152 / 153

|Version|Date|Author|Description|
|---|---|---|---|
|V1.99|2019-DEC-06|LL|functional summary updated for TMC4671-LA, FOC basics updated,<br>functional description updated, SPI read write access timing updated<br>for TMC4671-LA, ADC Engine section updated w/ voltage scalings,<br>step direction interface correction updated, order codes updated,<br>section ’Calculative PI Controller Setup - Classic Structure’ added;<br>TMC4671-ES Erratum vs. TMC4671-LA ﬁxes added, PWM center Hall<br>vector sampling added; section watchdog updated; section ﬁxes vs.<br>errata updated concerning actions to avoid trouble with recommen-<br>dations; section How to Turn a Motor updated; entry (signal of max.<br>of q4.12) in table (6) corrected,|
|V1.99|2019-DEC-20|LL|watchdog section updated, order codes updated, 1st page block di-<br>agram updated, DS_ANALOG_INPUT_STAGE_CFG updated|
|V1.99|2020-FEB-10|LL|Encoder Engine section: mechanical position (phi_m) corrected, sec-<br>tion Safety Functions: hint according to status bit write added,|
|V2.00|2020-APR-16|OM|feedforward control and PI control section updated; ENO/ENI pin<br>functionality added; Register map updated|
|V2.01|2020-JUL-13|KK|Register map updated (added missing registers, removed unused<br>registers), added section for controller sampling rates, added ta-<br>ble for real2int and int2real conversions, added section for GPIO-<br>usage, updated controller q8.8 and q4.12 representation, ﬁxed<br>num_representation for angles|
|V2.02|2020-SEP-22|OM|Register map updated (removed feed forward control registers),<br>added descriptions for register usage and register function, ﬁxed<br>exponents in tables for real/integer pwm conversion, updated feed-<br>foward, updated AENC_DECODER_MODE register info and infobox<br>in Analog Hall and Analog Encoder Interface|
|V2.03|2020-OCT-08|KK|Fixed several typos, added missing information about UART bau-<br>drate in 4.2.3, ﬁxed default values for UART_BPS register and added<br>hint in registermap about baudrate settings.|
|V2.04|2021-JAN-06|KK|Removed obsolete register AENC_DECODER_N_MASK from register<br>0x3C in 7.2 and 7.3, added errata on hall interpolation|
|V2.05|2021-JAN-06|KK|updated errata section|
|V2.06|2021-APR-12|KK|corrected names of "Phase Current Measurement" on graphics 39,<br>40 and 41 so they match the pin table, removed registers PIDIN_<br>VELOCITY_TARGET and PID_IN_POSITION_TARGET from registermap<br>as they are not connected, updated order codes, removed note on<br>ES2|



©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


TMC4671 Datasheet • IC Version V1.3 | Document Revision V2.08 • 2022-July-26 153 / 153

|Version|Date|Author|Description|
|---|---|---|---|
|V2.07|2022-JAN-07|KK|Table 2: removed double SCK low time, changed MISO data valid<br>time after falling edge of SCK to 20ns Typ; removed mentioning of<br>negative voltages in section 4.4.15, ﬁxed description error in reg-<br>ister 0x69 from target position to ﬂux torque actual, removed un-<br>used mode_ramp and mode_ﬀfrom register 0x63, removed an un-<br>ﬁnished sentence from 10.2.1, corrected formula for register 0x05<br>and 0x06 in section 7.2; replaced TMC_INPUTS_RAW by TMC4671_<br>INPUTS_RAW; Added info on UART-write response; added a table on<br>PI-representations for the advanced control structure; Removed un-<br>used comment section in section 7.3|
|V2.08|2022-JUL-26|KK|corrected register description 0x1B N_POLE_PAIRS; Add limits<br>with respective registeraddress to 4.7.5;<br>remove unused PID_<br>ACCELERATION_LIMIT register from 7.3; removed blanking_a and<br>blanking_b from register 0x04 dsADC_MCFG_B_MCFG_A as it is not<br>used;|



_Table 44:_ _Document Revision_


©2022 TRINAMIC Motion Control GmbH & Co. KG, Hamburg, Germany
Terms of delivery and rights to technical change reserved.
[Download newest version at www.trinamic.com](https://www.trinamic.com)


