/** @file
  Sample UEFI Application 
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
  EFI_STATUS status = EFI_SUCCESS;
  EFI_LOADED_IMAGE* loaded_image;
  EFI_GUID loaded_image_protocol = LOADED_IMAGE_PROTOCOL;
  EFI_GUID gEfiShellParametersProtocolGuid = EFI_SHELL_PARAMETERS_PROTOCOL_GUID;
  EFI_SHELL_PARAMETERS_PROTOCOL  *ShellParameters;
  UINTN i;

  Print(L"Hello World\n");

  status = gBS->HandleProtocol(ImageHandle, &loaded_image_protocol, (void**)&loaded_image);
  if (status == EFI_SUCCESS) {
    Print(L"LoadOptions: %s\n", (CHAR16 *)loaded_image->LoadOptions);
  } else {
    Print(L"LoadedImageProtocol: error %x\n", status & !0x80000000);
  }

  status = gBS->OpenProtocol (
          ImageHandle,
          &gEfiShellParametersProtocolGuid,
          (VOID **) &ShellParameters,
          ImageHandle,
          NULL,
          EFI_OPEN_PROTOCOL_GET_PROTOCOL
         );

  if (status == EFI_SUCCESS) {
    for (i = 0; i < ShellParameters->Argc; i++) {
      Print(L"Argv[%d]: %s\n", i, ShellParameters->Argv[i]);
    }
  } else {
    Print(L"ShellParametersProtocol: error %x\n", status & !0x80000000);
  }

  return status;

  return EFI_SUCCESS;
}
