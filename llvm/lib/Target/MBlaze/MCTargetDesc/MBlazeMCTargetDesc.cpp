//===-- MBlazeMCTargetDesc.cpp - MBlaze Target Descriptions ---------------===//
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

#include "MBlazeMCTargetDesc.h"
#include "InstPrinter/MBlazeInstPrinter.h"
#include "MBlazeMCAsmInfo.h"
#include "MBlazeMCCodeEmitter.cpp"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "MBlazeGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "MBlazeGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "MBlazeGenRegisterInfo.inc"

using namespace llvm;


static MCInstrInfo *createMBlazeMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitMBlazeMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createMBlazeMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitMBlazeMCRegisterInfo(X, MBlaze::R15);
  return X;
}

static MCSubtargetInfo *createMBlazeMCSubtargetInfo(const Triple &TT, 
                                                    StringRef CPU,
                                                    StringRef FS) {
  return createMBlazeMCSubtargetInfoImpl(TT, CPU, CPU, FS);
}

static MCAsmInfo *createMBlazeMCAsmInfo(const MCRegisterInfo &MRI,
                                        const Triple &TT, 
                                        const MCTargetOptions &Options) {
  return new MBlazeMCAsmInfo();
}

static MCCodeEmitter *createMBlazeMCCodeEmitter(const MCInstrInfo &II,
                                                const MCRegisterInfo &MRI,
                                                MCContext &Ctx) {
  return new MBlazeMCCodeEmitter(II);
}

static MCStreamer
*createMBlazeELFStreamer(const Triple &T, MCContext &Ctx,
                         std::unique_ptr<MCAsmBackend> &&TAB,
                         std::unique_ptr<MCObjectWriter> &&OW,
                         std::unique_ptr<MCCodeEmitter> &&Emitter,
                         bool RelaxAll) {
  return createELFStreamer(Ctx, std::move(TAB), std::move(OW), 
                          std::move(Emitter), RelaxAll);
}

static MCInstPrinter *createMBlazeMCInstPrinter(const Triple &T,
                                                unsigned SyntaxVariant,
                                                const MCAsmInfo &MAI,
                                                const MCInstrInfo &MII,
                                                const MCRegisterInfo &MRI) {
  if (SyntaxVariant == 0)
    return new MBlazeInstPrinter(MAI, MII, MRI);
  return 0;
}

// Force static initialization.
extern "C" void LLVMInitializeMBlazeTargetMC() {
  // Register the MC asm info.
  TargetRegistry::RegisterMCAsmInfo(TheMBlazeTarget, createMBlazeMCAsmInfo);

  // Register the MC codegen info.
  TargetRegistry::RegisterMCCodeEmitter(TheMBlazeTarget,
                                        createMBlazeMCCodeEmitter);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheMBlazeTarget, 
                                      createMBlazeMCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheMBlazeTarget,
                                    createMBlazeMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheMBlazeTarget,
                                          createMBlazeMCSubtargetInfo);

  // Register the asm backend
  TargetRegistry::RegisterMCAsmBackend(TheMBlazeTarget,
                                       createMBlazeAsmBackend);

  // Register the MCInstPrinter.
  TargetRegistry::RegisterMCInstPrinter(TheMBlazeTarget,
                                        createMBlazeMCInstPrinter);
  
  // Register the ELF streamer.
  TargetRegistry::RegisterELFStreamer(TheMBlazeTarget, 
                                      createMBlazeELFStreamer);
}
