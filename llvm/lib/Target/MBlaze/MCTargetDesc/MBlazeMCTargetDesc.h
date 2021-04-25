//===-- MBlazeMCTargetDesc.h - MBlaze Target Descriptions -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides MBlaze specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef MBLAZEMCTARGETDESC_H
#define MBLAZEMCTARGETDESC_H

#include "llvm/Support/DataTypes.h"

namespace llvm {
class MCAsmBackend;
class MCContext;
class MCInstrInfo;
class MCObjectWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class Target;
class StringRef;
class raw_ostream;

extern Target TheMBlazeTarget;

MCAsmBackend *createMBlazeAsmBackend(const Target &T,
                                     const MCSubtargetInfo &STI,
                                     const MCRegisterInfo &MRI,
                                     const MCTargetOptions &Options);

MCObjectWriter *createMBlazeELFObjectWriter(raw_ostream &OS, uint8_t OSABI);
} // End llvm namespace

// Defines symbolic names for MBlaze registers.  This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "MBlazeGenRegisterInfo.inc"

// Defines symbolic names for the MBlaze instructions.
#define GET_INSTRINFO_ENUM
#include "MBlazeGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "MBlazeGenSubtargetInfo.inc"

#endif
