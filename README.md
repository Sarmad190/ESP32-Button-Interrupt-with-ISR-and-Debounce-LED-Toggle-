ESP32 Button Interrupt with ISR and Debounce – LED Toggle (FreeRTOS)
Project Overview

This project demonstrates how to use an Interrupt Service Routine (ISR) on the ESP32 with FreeRTOS to toggle an LED when a button is pressed.
To ensure reliable operation, software debouncing is implemented so that a single press is not registered multiple times due to mechanical switch noise.

Key Features

Configure GPIO pins for button input and LED output

Use Interrupts (ISR) to handle button presses efficiently

Implement debouncing to avoid false triggers

Toggle LED state in real time through ISR

Demonstrates non-blocking event handling with FreeRTOS

Author

Code written by Sarmad Shabbir
