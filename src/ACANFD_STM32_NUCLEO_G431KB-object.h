#pragma once

//----------------------------------------------------------------------------------------

#include <ACANFD_STM32_from_cpp.h>

//----------------------------------------------------------------------------------------
//  NUCLEO-G431KB: STM32G431KB (DS12589 Rev 6, October 2021)
//    FDCAN_RX : PA11, PB8
//    FDCAN_TX : PA12, PB9
//----------------------------------------------------------------------------------------
//   FDCAN1
//----------------------------------------------------------------------------------------

const ACANFD_STM32::PinPort FDCAN_TX_PIN_ARRAY [2] {
  {PA_12, 9}, // Tx Pin: PA_12, AF9
  {PB_9,  9}, // Tx Pin: PB_9, AF9
} ;

//----------------------------------------------------------------------------------------

const ACANFD_STM32::PinPort FDCAN_RX_PIN_ARRAY [2] {
  {PA_11, 9}, // Rx Pin: PA_11, AF9
  {PB_8,  9}, // Rx Pin: PB_9, AF9
} ;

//----------------------------------------------------------------------------------------

ACANFD_STM32 fdcan1 (
  FDCAN1, // CAN Peripheral base address
  SRAMCAN_BASE, // CAN RAM Base Address
  FDCAN1_IT0_IRQn, // Transmit interrupt
  FDCAN1_IT1_IRQn, // Receive interrupt
  FDCAN_TX_PIN_ARRAY,
  2, // Tx Pin array size
  FDCAN_RX_PIN_ARRAY,
  2  // Rx Pin array size
) ;

//----------------------------------------------------------------------------------------

extern "C" void FDCAN1_IT0_IRQHandler (void) ;
extern "C" void FDCAN1_IT1_IRQHandler (void) ;

//----------------------------------------------------------------------------------------

void FDCAN1_IT0_IRQHandler (void) {
  fdcan1.isr0 () ;
}

//----------------------------------------------------------------------------------------

void FDCAN1_IT1_IRQHandler (void){
  fdcan1.isr1 () ;
}

//----------------------------------------------------------------------------------------
