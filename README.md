Introduction

Motive of this project is to create a cloud based IOT irrigation system for domestic purpose. Using this one can control the water flow in garden/plants using a portable mobile application.
This project is the solution to my personal problem. The story is, my mom has a medium sized terrace garden in our house and while she daily nurture it, it grew so green. Once in a summer we all went out for a  vacation during which there was no one to water our garden. When we returned, we saw all the green turned in to yellow or brown which broke my mom’s heart ! At that time her Computer Engineer son (me) decided to put my knowledge to get the permanent solution for this and here we are.!

Materials and Tools

Hardware

Item

Qty

Description

Node MCU 

1

Controller unit to control the valve, to connect to the internet, for other logic.

TIP122 transistor

1

To turn on/off electromagnetic valve.( because valve may be working on more then 5V which Node MCU can not provide directly )

Electromagnetic valve

1

To control the flow of water

Breadboard

1

As a base for circuit

Jumper Cables

~15

For electrical connections

Buck LM2596 DC-DC Buck Converter Step Down Module

1

To reduce voltage from 12V DC to 5V DC

Power adapter (12V DC)

1

To convert domestic 220V AC to 12V DC

Mobile device

1

For input 

Power supply (220V AC as per indian standards)

1

Power source

Computer ( for development )

1

For development purposes

Software

Description

Arduino Create Agent

To upload Arduino sketch to Node MCU device



Arduino Cloud Integration



Functional Overview



Above diagram shows the functional structure of this project. 

Here electromagnetic valve is connected to 12V DC power supply (converted from 220V AC power supply using adapter) and switching is done by TIP122 transistor in-between the circuit. Positive and negative ends are connected to transistor as shown and one data signal cable is there connected to D5 pin (GPIO pin) of Node MCU. Logic inside Node MCU will perform switching on discreet input signal to transistor. Node MCU is connected to Arduino IOT Cloud using WIFI internet connection. We can change status of valve using a mobile device as shown using Arduino IOT Remote App.

Here we can not power the electromagnetic valve from Node MCU directly and their working voltage levels are different. Valve is working on 12V DC and Node MCU is working on 5V DC. Powering Node MCU directly from adapter can fry the board. To reduce voltage for controller we have used LM2596 DC-DC Buck Converter Step Down Module which will lower the voltage in required range. Valve is directly connected to the 12V DC adapter.

Electromagnetic valve is closed by default. When we flow current in it, it opens and remains open till the current is flowing. Here, we are controlling current using TIP122 transistor which has its signal input wire connected to Node MCU’s D5 GPIO pin.

Circuit Diagram