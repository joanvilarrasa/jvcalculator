# jvcalculator

A simple calculator experiment.

https://github.com/user-attachments/assets/ff3188ef-7b3b-43a8-8825-3c3cf99a3341

## Overview

A simple calculator experiment built for the Raspberry Pi Pico 2. This is just a simple project to explore the raspberry Pi, and the operator precedence algorithm proposed by Jonathan Blow.
The calculator uses a 2-line LCD display (16 characters per line) where:
- **Line 1**: Displays the current query/expression being entered
- **Line 2**: Displays the computed result in real-time

Input is provided via an infrared remote control, and the calculator supports basic arithmetic operations: addition (+), subtraction (-), multiplication (*), and division (/).
It only deals with integer numbers because I wanted to keep things as simple as possible.

## Architecture

The calculator processes expressions in two main stages:

### 1. Tokenization (`tokenizer.cpp` / `tokenizer.h`)

The input query string is first converted into a sequence of tokens. Each token can be either:
- A **number** (TOKEN_NUMBER): Integer values
- An **operator** (TOKEN_OPERATOR): +, -, *, or /

Operators are assigned precedence values:
- `+` and `-`: Precedence 1 (lower)
- `*` and `/`: Precedence 2 (higher)

### 2. Recursive Tree Construction (`computer.cpp` / `computer.h`)

The tokenized expression is then parsed into a binary expression tree using a recursive algorithm that respects operator precedence. This approach was inspired by a [Jonathan Blow video](https://youtu.be/fIPO4G42wYE?si=_uVgesvEprFDbIWf&t=2067).

The algorithm is based in the idea that you can separate the problem into 2 subproblems:
- If precedence is increasing you build a right leaning tree by attatching the next steps to the right leaf.
- If precedence is decreasing you build a left leaning tree by using what you have as the left leaf.
- Putting both of those together is the code inside the computer.cpp.

- Once the tree is build we can simply dfs to compute the result. We can assume that the leafs will be numbers and anything that is not a leaf will be an operator.

## Components

- **`jvcalculator.ino`**: Main Arduino sketch handling LCD display, IR input, and UI logic
- **`tokenizer.cpp/h`**: Tokenizes input strings into number and operator tokens
- **`computer.cpp/h`**: Build the tree and computes the result
- **`IR.cpp/h`**: Handles infrared remote control input decoding (This is not my code, it came with the Raspberry Pico)
- **`lib/LiquidCrystal_I2C/`**: Library for I2C LCD display control (This is not my code, it came with the Raspberry Pico)

## Hardware

- Raspberry Pi Pico 2
- 16x2 I2C LCD Display (address 0x27 or 0x3F)
- IR Receiver (connected to pin 16)
- IR Remote Control

To build and upload code to the hardware I installed and used the arduino-cli you can see the compile and build commands in the bin directory.
