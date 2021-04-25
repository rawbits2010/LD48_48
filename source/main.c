#include <tonc.h>
#include <string.h>

#include "double_sprite.h"
#include "sprite.h"
#include "sprite_buffer.h"
#include "enemy_buffer.h"
#include "level_map.h"

// gfx data
#include "worm.h"
#include "worm_hit.h"
#include "fish_1_A.h"
#include "fish_1_B.h"
#include "fish_2_A.h"
#include "fish_2_B.h"
#include "platform.h"
#include "bg.h"



void handleInput( Sprite *obj ) {

	key_poll();

	s32 force_x = 0;
	s32 force_y = 0;

	force_x += 1*key_tri_horz();
	force_y += 1*key_tri_vert();

	obj->pos_x += force_x;
	obj->pos_y += force_y;

	if(force_x != 0) {
		if(force_x > 0) {
			spriteSetHFlipped( obj, true );
		} else {
			spriteSetHFlipped( obj, false );
		}
	}

	if( key_hit(KEY_B) || key_hit(KEY_A) ) {

		if( key_hit(KEY_B) ) {
			spriteSetAnimationFrame( obj, 1 );
			spriteSetHFlipped( obj, false );
		}

		if( key_hit(KEY_A) ) {
			spriteSetAnimationFrame( obj, 1 );
			spriteSetHFlipped( obj, true );
		}

	}

	spriteSetPosition( obj );

}

//
// helpers

void createAnimation( Animation *out, const unsigned int *tiles, u32 frame_count, u32 h_offset ) {
	out->tiles = tiles;
	out->tile_size = 32;
	out->tiles_per_frame = 4;
	out->frame_count = frame_count;
	out->h_offset = h_offset;
}

void createSprite( Sprite *out, Animation *anim_arr, const unsigned short *pal ) {
	out->anims = &anim_arr[0];
	out->default_anim_idx = 0;
	out->palette = pal;
	out->palette_startidx = 0;
	out->palette_count = 16;	// use only the first 16 colors
}



int main() {

	// init graphics mode
	spritebufferInit();
	REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_OBJ | DCNT_OBJ_1D;
	REG_BG0CNT= BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_32x32;
	REG_BG1CNT= BG_CBB(0) | BG_SBB(31) | BG_4BPP | BG_REG_32x32;

	//
	// create the worm sprite with animations
	Animation worm_anims[2];

	Animation worm_wiggle; // 16x16@4
	createAnimation( &worm_wiggle, wormTiles, 4, 0 );
	animationInit(&worm_wiggle, 15, true, false);

	worm_anims[0] = worm_wiggle;

	Animation worm_hit; // 16x16@4
	createAnimation( &worm_hit, worm_hitTiles, 4, -5 );
	animationInit(&worm_hit, 4, false, false);

	worm_anims[1] = worm_hit;

	Sprite worm;
	createSprite( &worm, &worm_anims[0], wormPal );
	spriteLoadPalette( &worm );
	spritebufferAddSprite( &worm );

	//
	// create the double sprite fish
	// TODO: should be somewhere else like in an enemy pool

	// fish1
	Animation fish1A_anims[1];

	Animation fish1A_swim; // 16x16@4
	createAnimation( &fish1A_swim, fish_1_ATiles, 3, 0 );
	animationInit(&fish1A_swim, 15, true, true);

	fish1A_anims[0] = fish1A_swim;

	Animation fish1B_anims[1];

	Animation fish1B_swim; // 16x16@4
	createAnimation( &fish1B_swim, fish_1_BTiles, 3, 0 );
	animationInit(&fish1B_swim, 15, true, true);

	fish1B_anims[0] = fish1B_swim;

	Sprite fish1A;
	createSprite( &fish1A, &fish1A_anims[0], fish_1_APal );
	spriteLoadPalette( &fish1A );
	spritebufferAddSprite( &fish1A );
	
	Sprite fish1B;
	createSprite( &fish1B, &fish1B_anims[0], fish_1_BPal );
	spriteLoadPalette( &fish1B );
	spritebufferAddSprite( &fish1B );

	DoubleSprite fish1;
	fish1.left = &fish1A;
	fish1.right = &fish1B;
	doublespriteSetHidden( &fish1, true );

	// fish2
	Animation fish2A_anims[1];

	Animation fish2A_swim; // 16x16@4
	createAnimation( &fish2A_swim, fish_2_ATiles, 3, 0 );
	animationInit(&fish2A_swim, 15, true, true);

	fish2A_anims[0] = fish2A_swim;

	Animation fish2B_anims[1];

	Animation fish2B_swim; // 16x16@4
	createAnimation( &fish2B_swim, fish_2_BTiles, 3, 0 );
	animationInit(&fish2B_swim, 15, true, true);

	fish2B_anims[0] = fish2B_swim;

	Sprite fish2A;
	createSprite( &fish2A, &fish2A_anims[0], fish_2_APal );
	spriteLoadPalette( &fish2A );
	spritebufferAddSprite( &fish2A );
	
	Sprite fish2B;
	createSprite( &fish2B, &fish2B_anims[0], fish_2_BPal );
	spriteLoadPalette( &fish2B );
	spritebufferAddSprite( &fish2B );

	DoubleSprite fish2;
	fish2.left = &fish2A;
	fish2.right = &fish2B;
	doublespriteSetHidden( &fish2, true );

	// create an enemy buffer
	enemybufferInit();

	// load level map tiles
	memcpy(&pal_bg_mem[16], platformPal, 16*2);
	memcpy(&tile_mem[0][1], platformTiles, platformTilesLen);
	memcpy(&pal_bg_mem[16*2], bgPal, 16*2);
	memcpy(&tile_mem[0][10], bgTiles, bgTilesLen);

	// setup the background
	levelmapInit();

	// enable isr switchboard and VBlank interrupt
	irq_init(NULL);
	irq_add(II_VBLANK, NULL);


	// game logic
	// TODO: not here


	//
	// TEMP

	// try to spawn fish1 in
	enemybufferSpawnEnemy(&fish1, 50, 1);
	enemybufferSpawnEnemy(&fish1, 30, 1);
	enemybufferSpawnEnemy(&fish2, 70, 1);

	// position the worm and fish
	worm.pos_x = 96;
	worm.pos_y = 32;
	spriteSetPosition( &worm );



	while(1) {

		VBlankIntrWait();

		// do animation
		spriteAdvanceAnimation( &worm );
		doublespriteAdvanceAnimation( &fish1 );
		doublespriteAdvanceAnimation( &fish2 );

		// update game state
		enemybufferUpdateEnemies( &worm );
		levelmapUpdate();

		// do that
		handleInput( &worm );

		// finalize
		spritebufferUpload(128);

	}

	return 0;
}