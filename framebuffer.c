#include "framebuffer.h"
#include "assert.h"
#include "uefi.h"
#include "utils.h"

bool fb_init(struct framebuffer *fb)
{
  efi_guid_t gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
  printf("Initializating framebuffer\n");

  assert(EFI_OK(BS->LocateProtocol(&gopGuid, NULL, (void **)&fb->gop)));

  efi_gop_mode_info_t *info;
  uintn_t info_size;
  bool usable;

  printf("Available modes :\n");
  for (size_t i = 0; i < fb->gop->Mode->MaxMode; i++) {
    assert(EFI_OK(fb->gop->QueryMode(fb->gop, i, &info_size, (efi_gop_mode_info_t **)&info)));

    bool current = i == fb->gop->Mode->Mode;

    printf("- %u: w:%u h:%u pf:%d%s\n", i,
      info->HorizontalResolution, info->VerticalResolution,
      info->PixelFormat, current ? " (c)" : "");
    
    if (current) {
      fb->width = info->HorizontalResolution;
      fb->height = info->VerticalResolution;

      /* no support for custom pixel format */
      usable = info->PixelFormat == PixelRedGreenBlueReserved8BitPerColor
            || info->PixelFormat == PixelBlueGreenRedReserved8BitPerColor;

      fb->bgr = info->PixelFormat == PixelBlueGreenRedReserved8BitPerColor;
    }
  }

  /* No current mode ? */
  assert(fb->width > 0 && fb->height > 0);

  fb->backbuffer = calloc(fb->width * fb->height, sizeof(uint32_t));
  assert(fb->backbuffer);

  return usable;
}

void fb_init_with(struct framebuffer *fb, intn_t target_width, intn_t target_height)
{
  fb_init(fb);

  /* TODO */
}

void fb_cleanup(struct framebuffer *fb)
{
  /* BS->CloseProtocol ? */
  free(fb->backbuffer);
}

void fb_redraw(struct framebuffer *fb)
{
  fb->gop->Blt(fb->gop, fb->backbuffer, EfiBltBufferToVideo, 0, 0, 0, 0, fb->width, fb->height, 0);
}

void fb_setcolor(struct framebuffer *fb, uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b)
{
  uint32_t color = 0;

  if (fb->bgr) {
    /* BBGGRRXX */
    color |= b << 16;
    color |= g << 8;
    color |= r << 0;
  } else {
    /* RRGGBBXX */
    color |= r << 16;
    color |= g << 8;
    color |= b << 0;
  }

  assert(x < fb->width);
  assert(y < fb->height);

  fb->backbuffer[x + y * fb->width] = color;
}
