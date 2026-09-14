# File Transformation Tool — COMP 348

A command-line text transformation tool developed in **C** as part of  
**COMP 348 – Principles of Programming Languages** at Concordia University.

The application processes text files using multiple transformation modes, including Caesar cipher encryption, XOR transformation, and dictionary-based word substitution.

> This project was developed as a group assignment.

## Overview

The goal of this project was to build a modular command-line program capable of reading an input file, applying a selected transformation, and writing the transformed content to standard output.

The program supports three transformation modes:

- Caesar transformation
- XOR transformation
- Dictionary-based word replacement

The project was implemented using multiple C source and header files to separate the command-line interface from the transformation logic.

## Features

### Caesar Transformation

The Caesar mode shifts:

- Uppercase letters within `A-Z`
- Lowercase letters within `a-z`
- Digits within `0-9`

The implementation supports positive and negative shift values and wraps characters around their respective ranges.

Example:

```bash
./ftrans caesar 3 input.txt
