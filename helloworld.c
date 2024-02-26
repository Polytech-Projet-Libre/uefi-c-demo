#include <uefi.h>

#include "assert.h"

uint32_t *framebuffer;

int main(int argc, char **argv)
{
  efi_guid_t gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
  efi_gop_t *gop;

  if (EFI_ERROR(BS->LocateProtocol(&gopGuid, NULL, (void **)&gop))) {
    printf("Unable to locate protocol\n");
    return 1;
  }

  efi_gop_mode_info_t *info;
  uintn_t info_size;

  for (size_t i = 0; i < gop->Mode->MaxMode; i++) {
    if (EFI_ERROR(gop->QueryMode(gop, i, &info_size, (efi_gop_mode_info_t **)&info))) {
      printf("Unable to get modes\n");
      return 1;
    }

    printf("%u: w:%u h:%u pf:%d\n", i,
      info->HorizontalResolution, info->VerticalResolution,
      info->PixelFormat);
  }

  if (EFI_ERROR(gop->QueryMode(gop, gop->Mode->Mode, &info_size, (efi_gop_mode_info_t **)&info))) {
    printf("Unable to get current mode\n");
    return 1;
  }

  if (info->PixelFormat != PixelRedGreenBlueReserved8BitPerColor) {
    printf("Unsupported pixel format");
  }

  framebuffer = calloc(sizeof(uint32_t), info->HorizontalResolution * info->VerticalResolution);
  assert(framebuffer);

  printf("Hello World!\n");
  return 0;
}