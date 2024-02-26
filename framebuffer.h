#ifndef H_FRAMEBUFFER
#define H_FRAMEBUFFER

#include <uefi.h>
#include "utils.h"

/**
 * Framebuffer structure
 */
struct framebuffer {
  efi_gop_t *gop; /* gop object */
  
  uint32_t width, height; /* backbuffer width and height */
  uint32_t *backbuffer; /* backbuffer frame */
  bool bgr; /* bgr ordering */
};

/**
 * Initialize framebuffer with GOP.
 *
 * @return Whether current mode is usable.
 */
bool fb_init(struct framebuffer *fb);

/**
 * Initialize framebuffer with GOP.
 * 
 * @param target_width Prefered width to try to get close at
 * @param target_height Prefered height to try to get close at
 */
void fb_init_with(struct framebuffer *fb, intn_t target_width, intn_t target_height);

/**
 * Cleanup framebuffer and associated ressources.
 */
void fb_cleanup(struct framebuffer *fb);

void fb_redraw(struct framebuffer *fb);
void fb_setcolor(struct framebuffer *fb, uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);

#endif