This repository hosts my new eurorack mixer modules. It also host an old mixer module, but for reference only. 
New mixers files are stored in "VERSION_2" folder.

# 4CH-Audio/CV-Mixer-Modules
Two different mixers for two different tasks. For modular synthesizers.

1 - Four channels audio mixer module with built-in reference tone generator

2 - Four channels CV mixer module with gain compensation.

![IMG_20250605_125735_risultato](https://github.com/user-attachments/assets/4ea6f8fe-21e1-4f0d-8c9e-be5c377e9424)

# Intro
This follows a previous mixer project I rolled out some time ago for my DIY eurorack synthesizer. 
After years of use and some time spent on the theory, I ended up seeing more clearly the limits of that project and matured some awareness on mixers.

Mixer design cannot lie out of it's final use. Will the mixer be used for audio signal or control voltage signal? Is that audio signal "hot", like the eurorack standard calls for, or "line" level?

We are dealing with two mixer modules here, designed with very different applications in mind: one for audio, the other for control voltages.

The audio mixer circuit is simpler, use a small amount of components and I was able to lay the whole circuit down onto a single PCB (main board).
The full audio mixer module calls for the aforementioned main board and a front panel PCB with no components at all.

The CV mixer module is instead made of three PCBs: main board (the one with main circuitry), front board (the one hosting potentiometers and jacks) and a front panel.
Again, the CV mixer module front panel has no components.

# Audio Mixer Circuit and Module Design
This project follows a [previous 4 channels mixer module](https://www.instructables.com/4-Channels-Mixer-Module-With-A440-Reference-Genera/). The time had come to focus it more to the final application (audio mix) and remove some unecessary feature.

## Improvements
First: **no variable gain**. Eurorack oscillators signal is HOT and needs attenuation before hitting external hardware. Going higher than unity gain in the final stage makes no sense, so we can save some good amount of panel space by omitting a dedicated gain potentiometer.

Second: **no inverted output**. To human hears, direct and inverted audio signals are perceived the same. The most basic audio mixer could use a single op-amp in inverting configuration and your ear would not notice.

## Built-In Reference Tone
A feature I always use with my [analog oscillators](https://www.instructables.com/CEM3340-Voltage-Controlled-Analog-Oscillator-Modul/), **the built-in digital reference tone** for tuning is something I could not live without.

This feature was already present in the previous mixer version, but it is here upgraded by the addiction of a direct control over the pitch and an RC filter with a roll-off frequency of just under 6kHz.

The sketch I have written for the reference tone is also brand new, with a direct square wave generation instead of the adoption of the basic "tune" Arduino function. This made the wave's tuning control way more effective, without the audio glitches the function was generating when moving between semitones.

Reference tone's pitch and volume can be set directly from the front panel through two dedicated potentiometers. These are two trimmers firmly soldered on the PCB, but made acessible through two holes on the front panel.

## Circuit
This new four (monaural) channel audio mixer module's circuit is based on a very simple but effective [design by Doepfer](http://www.doepfer.de/DIY/a100_diy.htm).

The circuit is built around a single dual op-amp in single package. I used common TL072, but one could use any other, pin-compatile op-amp of choice.

A human ear characteristic is it not being sensible to audio DC bias. Anyway, when two (or more) waves are mixed, the resultant wave is actually affected by relative bias. This is why every input of this mixer has an AC coupling capacitor following its voltage divider.

If the audio source is well known to be already AC coupled, one could omit these and replace them with jumpers.

## Module Design
The mixer circuit is made of only few components, and I dedicated due efforts to lay the circuit down onto a **single PCB** (plus the front panel) instead of two stacked PCBs thus keeping costs at minimum level.

All components values are silkscreened on the PCB to make assembly easier (I hate reference sheets).

There are no exhotic components, nor special care is in the need in components selection with the exception of potentiometers.

In the first iteration of the mixer I used linear pots because cheaper and easier to find than logaritmic. Human perception of volume follows a logaritmic law, instead, so in this more "focused to audio" mixer module I had to adopt **logaritmic potentiometers** by default. It is best, but not mandatory, to use logaritmic ("A", or "Audio"), mono, potentiometers instead of linear ("B").

The silkscreen shows 50K ohm potentiometers for input level, but you can also use 100K ohm pots in case you have those laying around.

The module calls for +12V, -12V and +5V. The 5V line is in the need for the digital tone generator, but you can omit it if you don't need the reference tone.

It's **3U tall, 8HP wide** and made of only two boards instead of three (front panel and main board).

Not bad, if you ask me!

# CV Mixer Circuit and Module Design
## CV Mixer Challenges
When dealing with control voltages, you often don't actually need a perfect tracking of the incoming voltage. Think i.e. to the common CVs from your keyboard (velocity, tracking, aftertouch): they could be lowened to some extent while travelling the mixer and you won't even notice.

Different is the case when you want to mix voltages for **pitch control**. A classical example is the application of some vibrato, where you add a certan amount of "oscillation" to your pitch voltage.

Human perception of pitch is extremely accurate and requires closely matched and/or trimmable components, so designing such a mixer calls for some special attentions.

## Circuit
First of all, starting from the possibility that we don't know exactly how the pitch signal is handled by the previous module, we can adopt a **buffering stage** at the input of any of the 4 channels.

Any signal is first buffered by a voltage follower based on an op-amp (a TL074 QUAD OP-AMP in this specific module) so as to not load down the output of whatever module is driving it.

The buffered signals from each input are then fed to an attenuation stage before hitting the mixing stage of the circuit.

Attenuation is simply made with **linear potentiometers** in voltage divider configuration ("Linear" pots because we are not dealing with audio signals, but CVs).

The mixing stage is similar to the one of the audio mixer we have seen in the previous Step, but with "pure" unity gain in sight. A **gain trimmer** is a good way to compensate for losses from the previous circuit sectors. This is placed in series with the appropriate feedback resistor dimensioned for a teoretical unity gain.

I adopted a multi-turn trimmer for fine gain control, which helped keeping the module width small.

The use of 1K ohm current limiting resistors at the **direct and inverted output** placed inside the feedback loop is a further "care" to limit the voltage drop at the output stage.

The 1K Ohm resistors serve not only as short-circuit protection for op-amps (every time you patch, the tip of the mixer output is shorted to the grounded sleeve of a jack), but also protects it from damage by static charge from outside, for example when a cable is inserted but not connected on the other side.

This module calls for +12V and -12V. It's **3U tall and 8HP wide**, like the previous mixer.

# Programming ATtiny85
To turn an ATtiny microcontroller into a "perfectly steady" digital tone generator to be used in the audio mixer module, we need to first program it.

The ATtiny85 microcontroller cannot be directly programmed with the Arduino IDE like a prototype board. It requires an intermediate board (such as an Arduino UNO) to act as an ISP (In-Circuit Serial Programmer).

Don't worry: it's a straightforward process if you follow these instructions carefully!

## 1: Turn Your Arduino UNO into a Programmer
The first step is to configure your Arduino UNO to work as an ISP:
- Open the Arduino IDE.
- Connect your Arduino UNO to your PC.
- Go to File -> Examples -> ArduinoISP and open the ArduinoISP.ino example.
- Upload the ArduinoISP sketch to your Arduino UNO.

## 2: Install the ATtiny Core
There's no more need to install ATtiny Core (by Spence Konde) on Arduino IDE v2 since it is already there. Give it a check, anyway.

## 3: Connect the Arduino UNO and ATtiny85
Now it's time to wire your Arduino UNO to the ATtiny85. Use a breadboard and it's cables for this, or create a little permanent circuit on perfboard if you prefer.

Here follows the wiring to program your ATtiny on breadboard:
(please notice that UNO pinout refers to silk screened pin numbers, while ATtiny pinout refers to package pin numbers)

**Connections:**
Arduino UNO → ATtiny85
5V → Pin 8 (Vcc)
GND → Pin 4 (Gnd)
D13 → Pin 7 (SCK)
D12 → Pin 6 (MISO)
D11 → Pin 5 (MOSI)
D10 → Pin 1 (Reset)

## 4: Upload the Sketch
Select the appropriate microcontroller and clock source:

- Go to Tools -> Board and select "AttinyCore -> ATtiny45/85 Optiboot".
- Under Tools -> Clock Source, select "8MHz Internal" (this should already be set by default, but double-check).
  
Open the sketch you want to upload.

Now, go to Tools -> Programmer and select "Arduino as ISP".

Burn the bootloader:

- Go to Tools -> Burn Bootloader.
  
Upload the sketch:

- Select Sketch -> Upload Using Programmer.
  
**Note:** Burn the bootloader each time you upload a new sketch.

# External Links
https://www.instructables.com/4-Channels-AudioCV-Mixers-for-Eurorack-Synthesizer/

https://synthbrigade.altervista.org/modularita-mixers/


# Acknowledgments
Many thanks to the nice girls and guys at [JLCPCB](https://jlcpcb.com/IAT) for sponsoring mixer modules PCBs manufacturing.
Without their contribution this project (and most of my other projects) would have never reached the current level of development.

JLCPCB is a high-tech manufacturer specialized in the production of high-reliable and cost-effective PCBs. They offer a flexible PCB assembly service with a huge library of more than 600.000 components in stock.
3D printing is part of their portfolio of services so one could create a full finished product, all in one place!

What about nano-coated stencils for your SMD projects? You can take advantage of a coupon and test it for free in these days!

By registering at JLCPCB site via [THIS LINK](https://jlcpcb.com/IAT) (affiliated link) you will receive a series of coupons for your orders. Registering costs nothing, so it could be the right opportunity to give their service a due try ;)

My projects are free and for everybody. You are anyway welcome if you want to donate some change to help me cover components costs and push the development of new projects (I have a new one on a nice sub-oscillator module that could be interesting for some of you... :) )

[>>HERE<<](https://paypal.me/GuidolinMarco?country.x=IT&locale.x=it_IT) is my paypal donation page, just in case ;)






