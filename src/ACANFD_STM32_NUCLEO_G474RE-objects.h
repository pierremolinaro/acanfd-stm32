#pragma once

//----------------------------------------------------------------------------------------

#include <ACANFD_STM32_from_cpp.h>

//----------------------------------------------------------------------------------------
//  NUCLEO-G474RE: STM32G474RE (DS12288 Rev 5, November 2021)
//    FDCAN1_RX : PA_11, PB_8
//    FDCAN1_TX : PA_12, PB_9
//    FDCAN2_RX : PB_5, PB_12
//    FDCAN2_TX : PB_6, PB_13
//    FDCAN3_RX : PA_8, PB_3
//    FDCAN3_TX : PA_15, PB_4
//----------------------------------------------------------------------------------------
//   FDCAN1
//----------------------------------------------------------------------------------------

const ACANFD_STM32::PinPort FDCAN1_TX_PIN_ARRAY [2] {
  {PA_12, 9}, // Tx Pin: PA_12, AF9
  {PB_9,  9}  // Tx Pin: PB_9, AF9
} ;

//----------------------------------------------------------------------------------------

const ACANFD_STM32::PinPort FDCAN1_RX_PIN_ARRAY [2] {
  {PA_11, 9}, // Rx Pin: PA_11, AF9
  {PB_8,  9}  // Rx Pin: PB_9, AF9
} ;

//----------------------------------------------------------------------------------------

ACANFD_STM32 fdcan1 (
  FDCAN1, // CAN Peripheral base address
  SRAMCAN_BASE,
  FDCAN1_IT0_IRQn, // Transmit interrupt
  FDCAN1_IT1_IRQn, // Receive interrupt
  FDCAN1_TX_PIN_ARRAY,
  2, // Tx Pin array size
  FDCAN1_RX_PIN_ARRAY,
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

void FDCAN1_IT1_IRQHandler (void) {
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
  SRAMCAN_BASE + 212 * 4,
  FDCAN2_IT0_IRQn, // Transmit interrupt
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

void FDCAN2_IT1_IRQHandler (void) {
  fdcan2.isr1 () ;
}

//----------------------------------------------------------------------------------------
//   FDCAN3
//----------------------------------------------------------------------------------------

const ACANFD_STM32::PinPort FDCAN3_TX_PIN_ARRAY [2] {
  {PA_15, 11}, // Tx Pin: PA_15, AF11
  {PB_4,  11}  // Tx Pin: PB_4, AF11
} ;

//----------------------------------------------------------------------------------------

const ACANFD_STM32::PinPort FDCAN3_RX_PIN_ARRAY [2] {
  {PA_8, 11}, // Rx Pin: PA_8, AF11
  {PB_3, 11}  // Rx Pin: PB_3, AF11
} ;

//----------------------------------------------------------------------------------------

ACANFD_STM32 fdcan3 (
  FDCAN3, // CAN Peripheral base address
  SRAMCAN_BASE + 212 * 4 * 2,
  FDCAN3_IT0_IRQn, // Transmit interrupt
  FDCAN3_IT1_IRQn, // Receive interrupt
  FDCAN3_TX_PIN_ARRAY,
  2, // Tx Pin array size
  FDCAN3_RX_PIN_ARRAY,
  2  // Rx Pin array size
) ;

//----------------------------------------------------------------------------------------

extern "C" void FDCAN3_IT0_IRQHandler (void) ;
extern "C" void FDCAN3_IT1_IRQHandler (void) ;

//----------------------------------------------------------------------------------------

void FDCAN3_IT0_IRQHandler (void) {
  fdcan3.isr0 () ;
}

//----------------------------------------------------------------------------------------

void FDCAN3_IT1_IRQHandler (void) {
  fdcan3.isr1 () ;
}

//----------------------------------------------------------------------------------------
