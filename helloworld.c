#include <uefi.h>

#include "assert.h"
#include "framebuffer.h"

int main(int argc, char **argv)
{
  printf("Hello World!\n");

  struct framebuffer fb;
  
  if (!fb_init(&fb)) {
    printf("Framebuffer unusable");
    return 0;
  }

  for (int x = 0; (x < 255 * 255) && (x < fb.width); x++)
    for (int y = 0; y < fb.height; y++)
      fb_setcolor(&fb, x, y, x % 255, x / 255, y % 255);

  fb_redraw(&fb);

  getchar();
  return 0;
}