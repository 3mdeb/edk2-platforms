/** @file
 *
 * Sample UEFI Application 
 *
 * Copyright (c) 2019, 3mdeb Embedded Systems Consulting
 *
**/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>

/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  UINT64 rax;

  Print(L"This is sample application.\n\
It prints some text and does CPUID to talk to Bareflank based hypervisor.\n");

  Print(L"\nTest String Number 1.\n");
  gBS->Stall (1000000);
  Print(L"cpuid (RAX=0x4BF00101)\n");
  rax = 0x4BF00101;
  asm volatile (
    "cpuid\n\t"
    : "+a"(rax));

  Print(L"\nTest String Number 2.\n");
  gBS->Stall (1000000);
  Print(L"cpuid (RAX=0x4BF00102)\n");
  rax = 0x4BF00102;
  asm volatile (
    "cpuid\n\t"
    : "+a"(rax));

  Print(L"\nTest String Number 3.\n");
  gBS->Stall (1000000);
  Print(L"cpuid (RAX=0x4BF00103)\n");
  rax = 0x4BF00103;
  asm volatile (
    "cpuid\n\t"
    : "+a"(rax));

  Print(L"\nTest String Number 4.\n");
  gBS->Stall (1000000);
  Print(L"cpuid (RAX=0x4BF00104)\n");
  rax = 0x4BF00104;
  asm volatile (
    "cpuid\n\t"
    : "+a"(rax));

  Print(L"\nTest String Number 5.\n");
  gBS->Stall (1000000);
  Print(L"cpuid (RAX=0x4BF00100)\n");
  rax = 0x4BF00100;
  asm volatile (
    "cpuid\n\t"
    : "+a"(rax));

  Print(L"\nTest String Number 6.\n");
  gBS->Stall (1000000);
  Print(L"\n\nThat's all, returning to Shell.\n");

  return EFI_SUCCESS;
}
