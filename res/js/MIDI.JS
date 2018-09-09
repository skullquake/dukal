//import scripts
//console.log('loading sylvester...');
//loadscript('./res/js/vendor/sylv.js');
//console.log('loading hsl...');
loadscript('./res/js/hsl.js');
//console.log('loading alconsole...');
loadscript('./res/js/alconsol.js');
//console.log('loading collide...');
loadscript('./res/js/collide.js');

//------------------------------------------------------------------------------
//set up console
//------------------------------------------------------------------------------
var allegro_message=console.log;
//console.log=alconsole.log
//alconsole.log=function(){};//deactivate
//------------------------------------------------------------------------------
var WIDTH=320;
var HEIGHT=240;
var SCREEN_W=WIDTH;
var SCREEN_H=HEIGHT;
var CDEPTH=16;
var GFX_TEXT=-1;
var GFX_AUTODETECT=0;
var GFX_AUTODETECT_FULLSCREEN=1;
var GFX_AUTODETECT_WINDOWED=2;
var DIGI_VOICES     =64;      /* Theoretical maximums: */
var DIGI_AUTODETECT =-1;       /* for passing to install_sound() */
var DIGI_NONE       =0;
var MIDI_AUTODETECT =-1;
var MIDI_NONE       =0;

//------------------------------------------------------------------------------
//double buffering
//------------------------------------------------------------------------------
var buffer;
function update_screen(){
		blit(
			buffer,
			screen,
			0,
			0,
			0,
			0,
			WIDTH,
			HEIGHT
		);
}
function init_double_buffering() {
	buffer = create_bitmap(SCREEN_W, SCREEN_H);
	if(!buffer)
		return false;
	return true;
}
function main(){
	allegro_init();
	set_color_depth(CDEPTH);
	install_keyboard();
	install_keyboard(); 
	install_timer();
	console.log(0)
	if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, null) != 0) {
		allegro_message("Error initialising sound system\n%s\n", allegro_error);
		return 1;
	}
	console.log(1);
	/*
	set_gfx_mode(GFX_AUTODETECT,WIDTH,HEIGHT,0,0);
	if(
		!init_double_buffering()
	){
		set_gfx_mode(GFX_TEXT,0,0,0,0);
		allegro_message(
			"Unable to initialize page flipping.\n"
		);
		return 1;
	}
	*/




	var the_music;
	var length, pos;
	var beats, beat;
	var paused = 0;
	var done = 0;
	console.log(2);
	the_music = load_midi("./res/a.mid");
	console.log(3);
	console.log(the_music);
	if(the_music==0){
		console.log("Error reading MIDI file");
		return 1;
	}
	console.log(4);
	length = get_midi_length(the_music);
	console.log(length);
	console.log(5);
	play_midi(the_music, 1);
	console.log(3);
	readkey();
	destroy_midi(the_music);
	console.log(4);
	set_gfx_mode(GFX_TEXT,WIDTH,HEIGHT,0,0);
	return 0;
}
main();

