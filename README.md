# LeafonySTM32
[![Spell Check Status](https://github.com/Leafony/LeafonySTM32/workflows/Spell%20Check/badge.svg)](https://github.com/Leafony/LeafonySTM32/actions?workflow=Spell+Check)

Arduino Library for Leafony STM32 Kit

For more information about this library please visit us at https://docs.leafony.com

## Background

Arduino has an enormous number of libraries for controlling ICs, but it can be a lot of work to achieve power optimized operations for IoT systems.
LeafonySTM32 tries to address the challenges this may cause by providing a much simpler library with a powerful power debugging methods.

## Features

* Power consumption debugging via serial monitor
* Easy installation of all the required libraries
* Power optimized settings available as initial

## Requirements

* Leafony STM32 Basic Kit
* Arduino 1.8.0 or later

## Installation

### Arduino Library Manager

Arduino Library Manager is a pre-installed library managing tool in Arduino.

Open this library manager from `Sketch -> Include Library -> Manage Libraries` and then search `LeafonySTM32`.

### Manual

Download this repository and extract the zip file to `Documents/Arduino/libraries`.

## Examaples

Sample sketches are available from `File -> Examples -> LeafonySTM32`.

## Usage

Make sure to include the LeafonySTM32 library in files that use it.

```cpp
#include <LeafonySTM32.h>
```

and then instantiate LeafonySTM32 class as a static variable.

```cpp
static LeafonySTM32 leafony;
```

## License

MIT
