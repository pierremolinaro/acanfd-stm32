//----------------------------------------------------------------------------------------

#pragma once

//----------------------------------------------------------------------------------------

#ifndef ARDUINO_ARCH_STM32
  #error "This sketch should be compiled for STM32"
#endif

//----------------------------------------------------------------------------------------

#include <ACANFD_STM32_Settings.h>
#include <ACANFD_STM32_FIFO.h>
#include <CANFDMessage.h>
#include <Arduino.h>

//----------------------------------------------------------------------------------------

#ifdef ARDUINO_NUCLEO_H743ZI2
  #include "ACANFD-STM32-programmable-ram-sections.h"
#elif defined (ARDUINO_NUCLEO_G431KB)
  #include "ACANFD-STM32-fixed-ram-sections.h"
#elif defined (ARDUINO_NUCLEO_G474RE)
  #include "ACANFD-STM32-fixed-ram-sections.h"
#else
  #error "Unhandled Nucleo Board"
#endif

//----------------------------------------------------------------------------------------
