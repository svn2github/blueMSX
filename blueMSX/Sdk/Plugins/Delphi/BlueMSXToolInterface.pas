(*
*****************************************************************************
** $Source: /cygdrive/d/Private/_SVNROOT/bluemsx/blueMSX/Sdk/Plugins/Delphi/BlueMSXToolInterface.pas,v $
**
** $Revision: 1.1 $
**
** $Date: 2005-03-04 14:51:12 $
**
** More info: http://www.bluemsx.com
**
** Copyright (C) 2003 - 2005 Daniel Vik
** Copyright (C) 2005 Johan van Leur
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
unit BlueMSXToolInterface;

interface

Uses
  Windows;

Type
  UInt8  = Byte;
  UInt16 = Word;
  UInt32 = DWORD;
  UInt64 = Int64;
  Int8   = Shortint;
  Int16  = Smallint;
  Int32  = Longint;


  TEmulatorState =
    (
      EMULATOR_STOPPED,
      EMULATOR_PAUSED,
      EMULATOR_RUNNING
    );

  TDeviceType =
    (
      DEVTYPE_UNKNOWN,
      DEVTYPE_CPU,
      DEVTYPE_CART,
      DEVTYPE_BIOS,
      DEVTYPE_RAM,
      DEVTYPE_AUDIO,
      DEVTYPE_VIDEO,
      DEVTYPE_IOPORT
    );

  TDevice =
    Record
      name       : Array [ 0 .. 63 ] of Char;
      deviceType : TDeviceType;
      deviceId   : Integer;
    End;
  PDevice = ^TDevice;

  TMemoryBlock =
    Record
      deviceId       : Integer;
      name           : Array [ 0 .. 31 ] of Char;
      writeProtected : Integer;
      startAddress   : DWORD;
      size           : DWORD;
      memory         : Array [ 0 .. 0 ] of Byte;
    end;
  PMemoryBlock = ^TMemoryBlock;

  TRegister =
    Record
      name: Array [ 0 .. 6 ] of Char;
      width: Byte;
      value: DWORD;
    end;
  PRegister = ^TRegister;

  TRegisterBank =
    Record
      deviceId : Integer;
      name     : array [ 0 .. 31 ] of Char;
      count    : DWORD;
      reg      : Array [ 0 .. 0 ] of TRegister;
    end;
  PRegisterBank = ^TRegisterBank;

  TCallstack =
    Record
      deviceId: Integer;
      name: Array [ 0 .. 31 ] of Char;
      size: DWORD;
      callstack: array [ 0 .. 0 ] of DWORD;
    end;
  PCallstack = ^TCallstack;


  TIoPort =
    Record
      port:  Word;
      value: Byte;
    end;
  PIoPort = ^TIoPort;

  TIoPorts =
    Record
      deviceId: Integer;
      name: Array [ 0 .. 31 ] of Char;
      count: DWORD;
      Port: Array [ 0 .. 0 ] of TIoPort;
    end;
  PIoPorts = ^TIoPorts;

  TSnapshot =
    Record
    end;
  PSnapshot = ^TSnapshot;


  TToolSnapshotCreate                = function: PSnapshot; stdcall;
  TToolSnapshotDestroy               = procedure ( Snapshot: PSnapshot ); stdcall;
  TToolGetEmulatorState              = function: TEmulatorState; stdcall;
  TToolSnapshotGetDeviceCount        = function( Snapshot: PSnapshot ): Integer; stdcall;
  TToolSnapshotGetDevice             = function( Snapshot: PSnapshot; deviceIndex: Integer ) : PDevice; stdcall;

  TToolDeviceGetMemoryBlockCount     = function( Device: PDevice ): integer; stdcall;
  TToolDeviceGetMemoryBlock          = function ( Device: PDevice; memBlockIndex: Integer ) : PMemoryBlock; stdcall;
  TToolDeviceWriteMemory             = function ( memoryBlock: PMemoryBlock; data: pointer; startAddr, size: Integer ): integer; stdcall;
  TToolDeviceGetRegisterBankCount    = function ( Device: pDevice ) : Integer; stdcall;
  TToolDeviceGetRegisterBank         = function ( Device: PDevice; regBankIndex: Integer ): PRegisterBank; stdcall;
  TToolDeviceWriteRegister           = function ( regBank: PRegisterBank; regIndex: Integer; value: DWORD ): integer; stdcall;
  TToolDeviceGetCallstackCount       = function ( Device: PDevice ): Integer; stdcall;
  TToolDeviceGetCallstack            = function ( Device: PDevice; callstackIndex: Integer ) : PCallstack; stdcall;
  TToolDeviceGetIoPortsCount         = function ( Device: PDevice ) : Integer; stdcall;
  TToolDeviceGetIoPorts              = function ( Device: PDevice; ioPortIndex: Integer ) : PIoPorts; stdcall;
  TToolDeviceWriteIoPort             = function  ( ioPorts: PIoPorts; portIndex: Integer; value: DWORD ): integer; stdcall;
  TToolAction                        = procedure; stdcall;
  TToolBreakpoint                    = procedure ( value: Word ); stdcall;


  TInterface =
    Record

      create                    : TToolSnapshotCreate;
      destroy                   : TToolSnapshotDestroy;
      getState                  : TToolGetEmulatorState;
      getDeviceCount            : TToolSnapshotGetDeviceCount;
      getDevice                 : TToolSnapshotGetDevice;

      getMemoryBlockCount       : TToolDeviceGetMemoryBlockCount;
      getMemoryBlock            : TToolDeviceGetMemoryBlock;
      writeMemoryBlockSement    : TToolDeviceWriteMemory;
      getRegisterBankCount      : TToolDeviceGetRegisterBankCount;
      getRegisterBank           : TToolDeviceGetRegisterBank;
      writeRegisterBankRegister : TToolDeviceWriteRegister;
      getCallstackCount         : TToolDeviceGetCallstackCount;
      getCallstack              : TToolDeviceGetCallstack;
      getIoPortsCount           : TToolDeviceGetIoPortsCount;
      getIoPorts                : TToolDeviceGetIoPorts;
      writeIoPortsPort          : TToolDeviceWriteIoPort;

      run                       : TToolAction;
      stop                      : TToolAction;
      pause                     : TToolAction;
      step                      : TToolAction;

      setBreakpoint             : TToolBreakpoint;
      clearBreakPoint           : TToolBreakpoint;

    end;
  PInterface = ^TInterface;

  CreateFn = function ( toolInterface: PInterface; name: PChar; length: integer ): integer; stdcall;
  NotifyFn = procedure; stdcall;

implementation

end.
