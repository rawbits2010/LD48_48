#ifndef SPRITE_H
#define SPRITE_H

#include <tonc.h> // actually only types are needed at the momo
#include "animation.h"

// unified 16x16@4 sprites with multiple animation frames
typedef struct Sprite {

	// animation
	Animation *anims;
	u32 default_anim_idx;
	u32 curr_anim_idx; // handled internally

	// all animation using the same sprite palette
	const short unsigned int *palette;
	u32 palette_startidx;
	u32 palette_count;
	u32 palmem_start_idx;	// ahndled internally

	// points to a place in the buffer - filled by sprite_buffer
	OBJ_ATTR *obj_attr;

	// these are the options you are looking for
	u32 pos_x;		// storing x position on screen
	u32 pos_y;		// storing y position on screen

	bool h_mirror;
	bool hidden;

} Sprite;

extern void createSprite( Sprite *out, Animation *anim_arr, const unsigned short *pal );
extern void spriteCopySprite( Sprite *src, Sprite *dst );

// like having cloned sprites with exactly the same animation
extern void spriteUpdateGfx( Sprite *obj );

extern void spriteLoadPalette( Sprite *obj );

extern void spriteSetPosition( Sprite *obj );
extern void spriteSetHFlipped( Sprite *obj, bool state );
extern void spriteSetHidden( Sprite *obj, bool hide );

extern void spriteSetAnimationFrame( Sprite *obj, u32 anim_idx );
extern void spriteAdvanceAnimation( Sprite *obj );

extern u32 spriteGetCollisionPosX( Sprite *obj );
extern u32 spriteGetCollisionPosY( Sprite *obj );

#endif // SPRITE_H