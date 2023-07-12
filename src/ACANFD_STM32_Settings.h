//--------------------------------------------------------------------------------------------------

#pragma once

//--------------------------------------------------------------------------------------------------

#include <ACANFD_DataBitRateFactor.h>

class CANFDMessage ;

//--------------------------------------------------------------------------------------------------

enum class ACANFD_STM32_FilterAction {
  FIFO0 = 0,
  FIFO1 = 1,
  REJECT = 2
} ;

//--------------------------------------------------------------------------------------------------

uint32_t fdcanClock (void) ;

//--------------------------------------------------------------------------------------------------

#ifdef ARDUINO_NUCLEO_H743ZI2
  #include "ACANFD_STM32_Settings_H743ZI2.h"
#elif defined (ARDUINO_NUCLEO_G431KB)
  #include "ACANFD_STM32_Settings_G431KB.h"
#elif defined (ARDUINO_NUCLEO_G474RE)
  #include "ACANFD_STM32_Settings_G474RE.h"
#else
  #error "Unhandled Nucleo Board"
#endif


//--------------------------------------------------------------------------------------------------
