#pragma once

//----------------------------------------------------------------------------------------

#include <ACANFD_STM32_from_cpp.h>

//----------------------------------------------------------------------------------------
//  NUCLEO-H743ZI2: STM32H743 (DS12110 Rev 9, March 2022)
//    FDCAN1_RX : PA11, PB8, PD0 (ZIO D67), PH14
//    FDCAN1_TX : PA12, PB9, PD1 (ZIO D66), PH13
//    FDCAN2_RX : PB12 (ZIO D19), PB5 (ZIO D11 or D22 ?)
//    FDCAN2_TX : PB13 (ZIO D18), PB6 (ZIO D1)
//----------------------------------------------------------------------------------------
//   FDCAN1
//----------------------------------------------------------------------------------------

const ACANFD_STM32::PinPort FDCAN1_TX_PIN_ARRAY [3] {
  {PD_1,  9}, // Tx Pin: PD_1, AF9
  {PB_9,  9}, // Tx Pin: PB_9, AF9
  {PA_12, 9}  // Tx Pin: PA_12, AF9
} ;

//----------------------------------------------------------------------------------------

const ACANFD_STM32::PinPort FDCAN1_RX_PIN_ARRAY [3] {
  {PD_0,  9}, // Rx Pin: PD_0, AF9
  {PB_8,  9}, // Rx Pin: PB_9, AF9
  {PA_11, 9}  // Rx Pin: PA_11, AF9
} ;

//----------------------------------------------------------------------------------------

ACANFD_STM32 fdcan1 (
  FDCAN1, // CAN Peripheral base address
  0, // Message RAM start word offset
  FDCAN1_MESSAGE_RAM_WORD_SIZE, // Message RAM word size
  FDCAN1_IT0_IRQn, // Transmit interrupt
  FDCAN1_IT1_IRQn, // Receive interrupt
  FDCAN1_TX_PIN_ARRAY,
  3, // Tx Pin array size
  FDCAN1_RX_PIN_ARRAY,
  3  // Rx Pin array size
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
//   FDCAN2
//----------------------------------------------------------------------------------------

const ACANFD_STM32::PinPort FDCAN2_TX_PIN_ARRAY [2] {
  {PB_6,  9}, // Tx Pin: PB_6, AF9
  {PB_13, 9}  // Tx Pin: PB_13, AF9
} ;

//----------------------------------------------------------------------------------------

const ACANFD_STM32::PinPort FDCAN2_RX_PIN_ARRAY [2] {
  {PB_5,  9}, // Rx Pin: PB_5, AF9
  {PB_12, 9}  // Rx Pin: PB_12, AF9
} ;

//----------------------------------------------------------------------------------------

ACANFD_STM32 fdcan2 (
  FDCAN2, // CAN Peripheral base address
  FDCAN1_MESSAGE_RAM_WORD_SIZE, // Message RAM start word offset
  FDCAN2_MESSAGE_RAM_WORD_SIZE, // Message RAM word size
  FDCAN2_IT0_IRQn,  // Transmit interrupt
  FDCAN2_IT1_IRQn, // Receive interrupt
  FDCAN2_TX_PIN_ARRAY,
  2, // Tx Pin array size
  FDCAN2_RX_PIN_ARRAY,
  2  // Rx Pin array size
) ;

//----------------------------------------------------------------------------------------

extern "C" void FDCAN2_IT0_IRQHandler (void) ;
extern "C" void FDCAN2_IT1_IRQHandler (void) ;

//----------------------------------------------------------------------------------------

void FDCAN2_IT0_IRQHandler (void) {
  fdcan2.isr0 () ;
}

//----------------------------------------------------------------------------------------

void FDCAN2_IT1_IRQHandler (void){
  fdcan2.isr1 () ;
}

//----------------------------------------------------------------------------------------
