#include "double_sprite.h"


inline void doublespriteCopy( DoubleSprite *src, DoubleSprite *dst ) {
	doublespriteSetHFlipped( dst, false );
	spriteCopySprite(src->left, dst->left);
	spriteCopySprite(src->right, dst->right);

}

inline void doublespriteUpdateGfx( DoubleSprite *obj ) {
	spriteUpdateGfx(obj->left);
	spriteUpdateGfx(obj->right);
}

inline void doublespriteSetHidden( DoubleSprite *obj, bool hide ) {

	spriteSetHidden( obj->left, hide );
	spriteSetHidden( obj->right, hide );
	obj->hidden = hide;

}

inline void doublespriteSetHFlipped( DoubleSprite * obj, bool state ) {

	// change their side so set position will work correctly
	if( obj->h_mirror != state ) {

		Sprite *temp = obj->left;
		obj->left = obj->right;
		obj->right = temp;

		spriteSetHFlipped( obj->left, state );
		spriteSetHFlipped( obj->right, state );

		doublespriteSetPosition( obj );
	}

	obj->h_mirror = state;

}

inline void doublespriteSetPosition( DoubleSprite *obj ) {

	// TODO: obviously this position would be better at the sprite center but I don't have the strength now
	obj->left->pos_x = obj->pos_x;
	obj->left->pos_y = obj->pos_y;
	spriteSetPosition(obj->left);

	// NOTE: for now there are only 16x16@4 sprites 'cause I only have those figured out
	obj->right->pos_x = obj->pos_x + 16;
	obj->right->pos_y = obj->pos_y;
	spriteSetPosition(obj->right);

}

inline void doublespriteAdvanceAnimation( DoubleSprite *obj ) {
	spriteAdvanceAnimation( obj->left );
	spriteAdvanceAnimation( obj->right );
}

inline void doublespriteSetAnimationFrame( DoubleSprite *obj, u32 anim_idx ) {
	spriteSetAnimationFrame( obj->left, anim_idx );
	spriteSetAnimationFrame( obj->right, anim_idx );
}


u32 doublespriteGetCollisionPosX( DoubleSprite *obj ) {
	if( obj->h_mirror ) {
		return spriteGetCollisionPosX( obj->right );
	} else {
		return spriteGetCollisionPosX( obj->left );
	}
}

u32 doublespriteGetCollisionPosY( DoubleSprite *obj ) {
	if( obj->h_mirror ) {
		return spriteGetCollisionPosY( obj->right );
	} else {
		return spriteGetCollisionPosY( obj->left );
	}
}
