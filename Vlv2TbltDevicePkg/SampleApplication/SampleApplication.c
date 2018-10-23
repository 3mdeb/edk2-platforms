/** @file
 *
 * Sample UEFI Application 
 *
 * Copyright (c) 2018, CMR Surgical Limited
 *
**/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/ShellParameters.h>

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
  EFI_STATUS                     Status = EFI_SUCCESS;
  EFI_LOADED_IMAGE               *LoadedImage;
  EFI_GUID                       gEfiLoadedImageProtocolGuid      = LOADED_IMAGE_PROTOCOL;
  EFI_GUID                       gEfiShellParametersProtocolGuid  = EFI_SHELL_PARAMETERS_PROTOCOL_GUID;
  EFI_SHELL_PARAMETERS_PROTOCOL  *ShellParameters;
  EFI_INPUT_KEY                  Key;
  UINTN i;

  Print(L"SampleApplication\n");

  Status = gBS->HandleProtocol(
          ImageHandle,
          &gEfiLoadedImageProtocolGuid,
          (VOID **) &LoadedImage);
  if (Status == EFI_SUCCESS) {
    Print(L"LoadOptions: %s\n", (CHAR16 *)LoadedImage->LoadOptions);
  } else {
    Print(L"LoadedImageProtocol: error %x\n", Status & ~0x80000000);
  }

  Status = gBS->HandleProtocol(
          ImageHandle,
          &gEfiShellParametersProtocolGuid,
          (VOID **) &ShellParameters);

  if (Status == EFI_SUCCESS) {
    for (i = 0; i < ShellParameters->Argc; i++) {
      Print(L"Argv[%d]: %s\n", i, ShellParameters->Argv[i]);
    }
  } else {
    Print(L"ShellParametersProtocol: error %x\n", Status & ~0x80000000);
  }

  Print(L"Press any key to continue...\n");

  do {
    Status = SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &Key);
  } while (EFI_ERROR(Status));

  return Status;
}
