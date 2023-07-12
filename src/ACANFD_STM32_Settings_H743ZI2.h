//--------------------------------------------------------------------------------------------------

#pragma once

//--------------------------------------------------------------------------------------------------
//  ACANFD_STM32_Settings class for NUCLEO-H743ZI2
//--------------------------------------------------------------------------------------------------

static const uint32_t FDCAN_ROOT_CLOCK_FREQUENCY = 120 * 1000 * 1000 ;
static const uint32_t FDCAN_MESSAGE_RAM_WORD_SIZE = 2560 ;

//--------------------------------------------------------------------------------------------------

class ACANFD_STM32_Settings {

//··································································································
//   Enumerations
//··································································································

  public: typedef enum : uint8_t {
    NORMAL_FD,
    INTERNAL_LOOP_BACK,
    EXTERNAL_LOOP_BACK,
    BUS_MONITORING
  } ModuleMode ;

//··································································································

  public: typedef enum : uint8_t {
    PAYLOAD_8_BYTES  = 0,
    PAYLOAD_12_BYTES = 1,
    PAYLOAD_16_BYTES = 2,
    PAYLOAD_20_BYTES = 3,
    PAYLOAD_24_BYTES = 4,
    PAYLOAD_32_BYTES = 5,
    PAYLOAD_48_BYTES = 6,
    PAYLOAD_64_BYTES = 7
  } Payload ;

//··································································································

  public: static uint32_t wordCountForPayload (const Payload inPayload) {
    const uint32_t WORD_COUNT [8] = {4, 5, 6, 7, 8, 10, 14, 18} ;
    return WORD_COUNT [uint32_t (inPayload)] ;
  }

//··································································································

  public: static uint32_t frameDataByteCountForPayload (const Payload inPayload) {
    return (wordCountForPayload (inPayload) - 2) * 4 ;
  }

//··································································································
//    Constructor for a given baud rate
//··································································································

  public: ACANFD_STM32_Settings (const uint32_t inDesiredArbitrationBitRate,
                                 const DataBitRateFactor inDataBitRateFactor,
                                 const uint32_t inTolerancePPM = 1000) ;

  public: ACANFD_STM32_Settings (const uint32_t inDesiredArbitrationBitRate,
                                 const uint32_t inDesiredArbitrationSamplePoint,
                                 const DataBitRateFactor inDataBitRateFactor,
                                 const uint32_t inDesiredDataSamplePoint,
                                 const uint32_t inTolerancePPM = 1000) ;

//··································································································
//    Properties
//··································································································

//--- CAN FD bit timing
  public: const uint32_t mDesiredArbitrationBitRate ; // In bit/s
  public: const DataBitRateFactor mDataBitRateFactor ;
//--- bitrate prescaler is common to arbitration bitrate and data bitrate
  public: uint8_t mBitRatePrescaler = 32 ; // 1...32
//--- Arbitration segments
  public: uint16_t mArbitrationPhaseSegment1 = 256 ; // 1...256
  public: uint8_t mArbitrationPhaseSegment2 = 128 ;  // 2...128
  public: uint8_t mArbitrationSJW = 128 ; // 1...128
//--- Data segments
  public: uint8_t mDataPhaseSegment1 = 32 ; // 1...32
  public: uint8_t mDataPhaseSegment2 = 16 ;  // 2...16
  public: uint8_t mDataSJW = 16 ; // 1...16

  public: bool mTripleSampling = false ; // true --> triple sampling, false --> single sampling
  public: bool mBitSettingOk = true ; // The above configuration is correct

//--- Module Mode
  public : ModuleMode mModuleMode = NORMAL_FD ;

//--- Driver receive FIFO Sizes
  public: uint16_t mDriverReceiveFIFO0Size = 60 ;
  public: uint16_t mDriverReceiveFIFO1Size = 60 ;

//--- Hardware Rx FIFO 0
  public: uint8_t mHardwareRxFIFO0Size = 20 ; // 0 ... 64
  public: Payload mHardwareRxFIFO0Payload = PAYLOAD_64_BYTES ;

//--- Hardware Rx FIFO 1
  public: uint8_t mHardwareRxFIFO1Size = 2 ; // 0 ... 64
  public: Payload mHardwareRxFIFO1Payload = PAYLOAD_64_BYTES ;

//--- Remote frame reception
  public: bool mDiscardReceivedStandardRemoteFrames = false ;
  public: bool mDiscardReceivedExtendedRemoteFrames = false ;

//-- Accept non matching frames ?
  public: ACANFD_STM32_FilterAction mNonMatchingStandardFrameReception = ACANFD_STM32_FilterAction::FIFO0 ;
  public: ACANFD_STM32_FilterAction mNonMatchingExtendedFrameReception = ACANFD_STM32_FilterAction::FIFO0 ;
  public: void (*mNonMatchingStandardMessageCallBack) (const CANFDMessage & inMessage) = nullptr ;
  public: void (*mNonMatchingExtendedMessageCallBack) (const CANFDMessage & inMessage) = nullptr ;

//--- Driver transmit buffer Size
  public: uint16_t mDriverTransmitFIFOSize = 10 ;

//--- Hardware Transmit Buffers
//    Required: mHardwareTransmitTxFIFOSize + mHardwareDedicacedTxBufferCount <= 32
  public: uint8_t mHardwareTransmitTxFIFOSize = 10 ; // 1 ... 32
  public: uint8_t mHardwareDedicacedTxBufferCount = 1 ; // 0 ... 30
  public: Payload mHardwareTransmitBufferPayload = PAYLOAD_64_BYTES ;

//--- Automatic retransmission
  public: bool mEnableRetransmission = true ;

//--- Transceiver Delay Compensation
  public: uint8_t mTransceiverDelayCompensation = 5 ; // 0 ... 127

//--- Open collector output
  public: bool mOpenCollectorOutput = false ; // true --> open collector, false --> push / pull

//--- Tx Pin
  public: uint8_t mTxPin = 255 ; // By default, uses the first entry of Tx pin array

//--- Rx Pin
  public: uint8_t mRxPin = 255 ; // By default, uses the first entry of Rx pin array

//··································································································
// Accessors
//··································································································

//--- Compute actual bitrate
  public: uint32_t actualArbitrationBitRate (void) const ;
  public: uint32_t actualDataBitRate (void) const ;

//--- Exact bitrate ?
  public: bool exactArbitrationBitRate (void) const ;
  public: bool exactDataBitRate (void) const ;

//--- Distance between actual bitrate and requested bitrate (in ppm, part-per-million)
  public: uint32_t ppmFromWishedBitRate (void) const ;

//--- Distance of sample point from bit start (in ppc, part-per-cent, denoted by %)
  public: uint32_t arbitrationSamplePointFromBitStart (void) const ;
  public: uint32_t dataSamplePointFromBitStart (void) const ;

//--- Bit settings are consistent ? (returns 0 if ok)
  public: uint32_t CANFDBitSettingConsistency (void) const ;

//··································································································
// Constants returned by CANBitSettingConsistency
//··································································································

  public: static const uint32_t kBitRatePrescalerIsZero                       = 1U <<  0 ;
  public: static const uint32_t kBitRatePrescalerIsGreaterThan32              = 1U <<  1 ;
  public: static const uint32_t kArbitrationPhaseSegment1IsZero               = 1U <<  2 ;
  public: static const uint32_t kArbitrationPhaseSegment1IsGreaterThan256     = 1U <<  3 ;
  public: static const uint32_t kArbitrationPhaseSegment2IsLowerThan2         = 1U <<  4 ;
  public: static const uint32_t kArbitrationPhaseSegment2IsGreaterThan128     = 1U <<  5 ;
  public: static const uint32_t kArbitrationSJWIsZero                         = 1U <<  6 ;
  public: static const uint32_t kArbitrationSJWIsGreaterThan128               = 1U <<  7 ;
  public: static const uint32_t kArbitrationSJWIsGreaterThanPhaseSegment2     = 1U <<  8 ;
  public: static const uint32_t kArbitrationPhaseSegment1Is1AndTripleSampling = 1U <<  9 ;
  public: static const uint32_t kDataPhaseSegment1IsZero                      = 1U << 10 ;
  public: static const uint32_t kDataPhaseSegment1IsGreaterThan32             = 1U << 11 ;
  public: static const uint32_t kDataPhaseSegment2IsLowerThan2                = 1U << 12 ;
  public: static const uint32_t kDataPhaseSegment2IsGreaterThan16             = 1U << 13 ;
  public: static const uint32_t kDataSJWIsZero                                = 1U << 14 ;
  public: static const uint32_t kDataSJWIsGreaterThan16                       = 1U << 15 ;
  public: static const uint32_t kDataSJWIsGreaterThanPhaseSegment2            = 1U << 16 ;

//··································································································

} ;

//--------------------------------------------------------------------------------------------------
