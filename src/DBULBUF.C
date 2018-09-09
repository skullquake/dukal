include <allegro.h>
BITMAP *buffer;
void update_screen(void) {
	blit(
		buffer,
		screen,
		0,
		0,
		0,
		0,
		SCREEN_W,
		SCREEN_H
	); // blit the buffer to the screen
}
int init_double_buffering() {
// create the memory buffer
	buffer = create_bitmap(SCREEN_W, SCREEN_H);
	if(!buffer)
		return FALSE;
	return TRUE; }
int main() {
	int x, y;
	// install allegro, set graphics mode, etc
	allegro_init();
	install_keyboard();
	set_color_depth(32);
	if(
		set_gfx_mode(
			GFX_AUTODETECT_WINDOWED,
			640,
			480,
			0,
			0
		)
	){
		allegro_message(
			"Unable to set graphics mode.\n"
		);
		return 1;
	}
	// initialize page flipping
	if(
		!init_double_buffering()
	){
		set_gfx_mode(GFX_TEXT,0,0,0,0);
		allegro_message(
			"Unable to initialize page flipping.\n"
		);
		return 1;
	}
	// default coordinates for the rectangle
	x = SCREEN_W / 2 - 5;
	y = SCREEN_H / 2 - 5;
	// main game loop
	while (!key[KEY_ESC]){
		// game logic
		if(key[KEY_LEFT] && x)
			--x;
		if(key[KEY_RIGHT] && x < SCREEN_W-10)
			++x;
		if (key[KEY_UP] && y)
			--y;
		if (key[KEY_DOWN] && y < SCREEN_H-10)
			++y;
		// you draw everything to buffer
		clear(buffer);
		rect(
			buffer,
			x,
			y,
			x+9,
			y+9,
			makecol(
				255,
				255,
				255
			)
		);
		textout_centre_ex(
			buffer,
			font,
			"Use arrow keys to move box. ESC to quit.",
			SCREEN_W/2,
			SCREEN_H/2,
			makecol(255,255,255),
			-1
		);
		// show the offscreen page
		update_screen();
	}
	return 0;
} END_OF_MAIN() </highlightSyntax> 
