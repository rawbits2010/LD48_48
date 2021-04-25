#ifndef DOUBLE_SPRITE_H
#define DOUBLE_SPRITE_H

#include <tonc.h>
#include "sprite.h"

typedef struct DoubleSprite {

	// only 16x16@4 for now
	Sprite *left;
	Sprite *right;

	// NOTE: all internal below this point

	// actual sprite position - left and right will be set internally
	u32 pos_x;
	u32 pos_y;

	// need to change the sides and also flip
	bool h_mirror;

} DoubleSprite;


extern void doublespriteSetHFlipped( DoubleSprite *obj, bool state );
extern void doublespriteSetPosition( DoubleSprite *obj );

// convenience
extern void doublespriteSetAnimationFrame( DoubleSprite *obj, u32 anim_idx );
extern void doublespriteAdvanceAnimation( DoubleSprite *obj );


#endif // DOUBLE_SPRITE_H