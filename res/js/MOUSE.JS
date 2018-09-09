loadscript('./res/js/hsl.js');
console.log=function(){};//deactivate logging
console.log('----------------------------------------------------------------');
console.log('Mouse Test');
console.log('----------------------------------------------------------------');
var WIDTH=320;
var HEIGHT=240;
var SCREEN_W=WIDTH;
var SCREEN_H=HEIGHT;
var CDEPTH=32;
var GFX_TEXT=-1;
var GFX_AUTODETECT=0;
var GFX_AUTODETECT_FULLSCREEN=1;
var GFX_AUTODETECT_WINDOWED=2;
var buffer;


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

//------------------------------------------------------------------------------
function main(){
	console.log('main()');
	console.log('allegro_init()');
	allegro_init();
	console.log('install_keyboard()');
	install_keyboard();
	console.log('install_mouse()');
	if(install_mouse()<0){
		console.log("No mouse detected, but you need one!");
		return -1;
	}
	console.log('set_color_depth()');
	set_color_depth(32);
	console.log('set_gfx_mode()');
	if(
		set_gfx_mode(
			GFX_AUTODETECT,
			WIDTH,
			HEIGHT,
			0,
			0
		)
	){
		console.log("Unable to set graphics mode.");
		return -1;
	}
	console.log('init_double_buffering()');
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

	var imgbuffer=create_bitmap(SCREEN_W, SCREEN_H);
	clear(imgbuffer);

	console.log('poll_mouse()');
	poll_mouse();
	console.log('acquire_screen()');
	acquire_screen();
	console.log('show_mouse()');
	show_mouse(screen);
	console.log('enable_hardware_cursor()');
	enable_hardware_cursor();
	console.log('position_mouse()');
	position_mouse(80,80);
	var a;
	var color;
	while(a!=15131){
		if(keypressed()){
			console.log('keypressed()');
			a=readkey();
			console.log('\t'+a);
			switch(a){
				case 20992://left
					break;
				case 21504://up
					break;
				case 21248://right
					break;
				case 21760://down
					break;
				default:
					break;
			}
		}
		console.log('poll_mouse()');
		poll_mouse();
		console.log('vsync()');
		//vsync();
		console.log('textout()');
		console.log('clear()');

		color=hslToRgb(new Date().getMilliseconds()/1000,1.0,0.5);
		for(var i=0;i<32;i++){
			putpixel(
				imgbuffer,
				mouse_x+Math.random()*32-16,
				mouse_y+Math.random()*32-16,
				makecol(color[0],color[1],color[2])
			);
		}
		blit(
			imgbuffer,
			buffer,
			0,
			0,
			0,
			0,
			WIDTH,
			HEIGHT
		);
		textout(
			buffer,
			font,
			'mouse_x: '+mouse_x,
			0,
			0,
			makecol(255,255,255)
		);
		textout(
			buffer,
			font,
			'mouse_y: '+mouse_y,
			0,
			10,
			makecol(255,255,255)
		);
		textout(
			buffer,
			font,
			'mouse_z: '+mouse_z,
			0,
			20,
			makecol(255,255,255)
		);
		update_screen();
	}
	set_gfx_mode(
		GFX_TEXT
	);
	remove_mouse();
	console.log(screen);
	return 0;
}
main()
















