# Cat Feeder

## About
This cat feeder, as the name implies, is a food dispenser for my cat. It is an automatic feeder that will dispense food two times a day. It runs off an ESP32S3 and is paired with an RTC that controls the feeding time. The PCB is also connected to pins that will attach itself to a servo motor to complete the action of turning the door to dispense food. The power source of this feeder is from the USBC port connected to the PCB, and the USBC will get electricity from outside. 
<img width="1247" height="708" alt="Screenshot 2026-05-31 201840" src="https://github.com/user-attachments/assets/41e73844-8ed7-434c-a862-4864a89e3033" />
<img width="503" height="673" alt="Screenshot 2026-06-06 190411" src="https://github.com/user-attachments/assets/625171b3-f4f2-437a-b930-6bdd2b9f595f" />

## Parts explained 
PCB: I used Kicad to create the schematic and PCB. I took a look online to see what the main components were that other people used. And I found that it consisted of an MCU, a motor, a clock, and a display for the clock, so that is what I based my schematic on. I connected my ESP32S3 to a clock, and I added pins on my PCB to connect to a display as well as a servo motor. For the clock, I also added a small battery so it can run even if the feeder gets disconnected from power for a bit. There is also a button on the PCB meant for resetting the machine if that ever needs to be done. 

Case: For the case, I used Fusion 360. Before I made my case, I did a lot of research on what other people made. I found that there were two main disperser mechanisms that are commonly used: An arger and an open and closed mechanism (I hope that is understandable language). I ended up  using the open and closed door mechanism. Tweaking it slightly by making my door more like a turning door. Before I was worried about the weight of the kibble, but the whole dispenser isn't that big so there isn't a ton of kibble in there; the weight shouldn't be much of an issue. Other than that, everything else is pretty straightforward. There are two main spaces in the feeder. The top is for the PCB, while the bottom is kibble. 

Firmware: I tried to make it as simple as possible. Since the main purpose of the firmware is to program the times that the feeder will dispense food and let the servo know when it moves. I don't know if my firmware will even work yet, but it didnt give me any issues so I'll have to see if it works after I make the feeder.

## How to use 
The feeder has many lid-like tops, and the only screws in the whole machine are for the PCB to attach to the feeder. So the main thing that needs to be done is every couple of days to remove the top compartment and add kibble into it. I didn't use many screws because I thought it would be quite inconvenient to have to unscrew something every other day, since this whole machine is supposedly allowing you to become more lazy. Other than adding kibble, you don't really have to do anything!

## Why I made this
I decided to do this project since I thought that this would be a fun and useful project that I could actually use in my house, so it wouldn't become an object collecting dust. Compared to other machine-like projects, this one had relatively not amount of componnets, so it was still within my abilities to figure this project out.

# Zine 
<img width="536" height="761" alt="Screenshot 2026-06-07 113851" src="https://github.com/user-attachments/assets/45316196-468f-4ed5-b8b6-604cbecc036f" />

