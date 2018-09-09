//console.log('sfadf');
var WIDTH=320;
var HEIGHT=200;
var SCREEN_W=WIDTH;
var SCREEN_H=HEIGHT;
var CDEPTH=32;
var GFX_TEXT=-1;
var GFX_AUTODETECT=0;
var GFX_AUTODETECT_FULLSCREEN=1;
var GFX_AUTODETECT_WINDOWED=2;
var buffer;
var allegro_message=console.log;
function update_screen() {
	//console.log('function update_screen() {');
	blit(
		buffer,
		screen,
		0,
		0,
		0,
		0,
		WIDTH,
		HEIGHT
	); // blit the buffer to the screen
}
function init_double_buffering() {
	//console.log('function init_double_buffering() {');
	buffer = create_bitmap(SCREEN_W, SCREEN_H);
	if(!buffer)
		return false;
	return true;
}
function main(){
	//console.log('function main(){');
	var x, y;
	allegro_init();
	install_keyboard();
	set_color_depth(32);
	if(
		set_gfx_mode(
			GFX_AUTODETECT,
			WIDTH,
			HEIGHT,
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
	while(a!=15131){
		if(keypressed()){
			a=readkey();
			switch(a){
				case 20992://left
					x--;
					break;
				case 21504://up
					y--;
					break;
				case 21248://right
					x++;
					break;
				case 21760://down
					y++;
					break;
				//case 19232://space
				//	break;
				default:
					break;
			}
			/*
			*/
		}
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
		textout(
			buffer,
			font,
			"Use arrow keys to move box. ESC to quit.",
			SCREEN_W/2,
			SCREEN_H/2,
			makecol(255,255,255)
		);
		// show the offscreen page
		update_screen();
	}
	return 0;
}
main();
