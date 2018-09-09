//------------------------------------------------------------------------------
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


	console.log(ALLEGRO_VERSION);
	console.log(ALLEGRO_SUB_VERSION);
	console.log(ALLEGRO_WIP_VERSION);
	console.log(ALLEGRO_DATE_STR);
	console.log(ALLEGRO_DATE);
	console.log(allegro_id);
	console.log(ALLEGRO_ERROR_SIZE);
	console.log(allegro_error);
	console.log(os_type);
	console.log(os_version);
	console.log(os_revision);
	console.log(os_multitasking);
	var a;
	var b;
	get_desktop_resolution(a,b);
	check_cpu();
	console.log(cpu_vendor);
	console.log(cpu_family);
	console.log(cpu_model);
	console.log(cpu_capabilities);
	//readkey();
	//return 1;

	install_timer();
	if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, null) != 0) {
		allegro_message("Error initialising sound system\n%s\n", allegro_error);
		return 1;
	}
	var the_music;
	var length, pos;
	var beats, beat;
	var paused = 0;
	var done = 0;
	the_music = load_midi("./res/a.mid");
	if(the_music==0){
		console.log("Error reading MIDI file");
		return 1;
	}
	length = get_midi_length(the_music);
	play_midi(the_music, 1);

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
	//------------------------------------------------------------------------------
	//menu
	//------------------------------------------------------------------------------
	var imgMnu=load_png("./res/img/chibi.png",null);
	stretch_blit(
		imgMnu,
		screen,
		0,
		0,
		320,
		240,
		0,
		0,
		WIDTH,
		HEIGHT
	);
	readkey();
	destroy_bitmap(buffer);
	//------------------------------------------------------------------------------
	//game vars
	//------------------------------------------------------------------------------
	textout(screen,font,'Loading image...',0,0,makecol(255,255,255));
	var img=load_png("./res/img/tiles.png",null);
	clear_bitmap(screen)
	textout(screen,font,'Done',0,0,makecol(255,255,255));
	clear_bitmap(screen)
	var pos={};
	pos.x=WIDTH/2;
	pos.y=HEIGHT/2;
	pos.vx=0;
	pos.vy=0;
	pos.k=0;
	//------------------------------------------------------------------------------
	//background for game
	//------------------------------------------------------------------------------
	var bg=create_bitmap(WIDTH,HEIGHT);
	for(var y=0;y<HEIGHT/32;y++){
		for(var x=0;x<WIDTH/32;x++){
			masked_blit(
				img,
				bg,
				4*32,
				2*32,
				x*32,
				y*32,
				32,
				32
			);
		}
	}

	//------------------------------------------------------------------------------
	//game loop
	//------------------------------------------------------------------------------
	var bullets=[];
	var a;
	var buffer=create_bitmap(WIDTH,HEIGHT);
	alconsole.buffer=buffer
	clear_bitmap(buffer);
	//clocking
	var c0;
	var c1;
	c0=new Date();
	c1=new Date();
	clb=new Date();//date of last bullet fired
	while(a!=15131){
		c0=new Date();
		if(keypressed()){
			a=readkey();
			pos.k=a;
			switch(a){
				case 20992://left
					pos.vx-=0.1;
					break;
				case 21504://up
					pos.vy-=0.1;
					break;
				case 21248://right
					pos.vx+=0.1;
					break;
				case 21760://down
					pos.vy+=0.1;
					break;
				case 19232://space
					if((new Date()-clb)>150){//clamp rate
						var bullet={};
						bullet.x=pos.x;
						bullet.y=pos.y;
						bullet.vy=pos.vy;
						bullet.vx=pos.vx;
						bullet.vy-=1;
						bullets.push(bullet);
						clb=new Date();
					}
					break;
				default:
					break;
			}
		}
		pos.x+=pos.vx;
		pos.y+=pos.vy;
		if(pos.x>WIDTH){
			pos.x=0;
		}
		if(pos.x<0){
			pos.x=WIDTH;
		}

		if(pos.y>HEIGHT){
			pos.y=0;
		}
		if(pos.y<0){
			pos.y=HEIGHT;
		}
		//recalc bullet pos
		for(var i=0;i<bullets.length;i++){
			bullets[i].x+=bullets[i].vx;
			bullets[i].y+=bullets[i].vy;
			if(
				bullets[i].x<0||
				bullets[i].x>WIDTH||
				bullets[i].y<0||
				bullets[i].y>HEIGHT
			){
				bullets=bullets.slice(1,bullets.length);
			}
		}
		clear_bitmap(buffer);
		//redraw bg
		masked_blit(
			bg,
			buffer,
			0,
			0,
			0,
			0,
			WIDTH,
			HEIGHT
		);

		//redraw bullet
		for(var i=0;i<bullets.length;i++){
			masked_blit(
				img,
				buffer,
				8*32,
				0,
				bullets[i].x,
				bullets[i].y,
				32,
				32
			);
		}
		//redraw player
		masked_blit(
			img,
			buffer,
			10*32,
			0,
			pos.x,
			pos.y,
			32,
			32
		);
		alconsole.row=0;
		alconsole.log('Player');
		alconsole.log(pos.x);
		alconsole.log(pos.y);
		alconsole.log(pos.vx);
		alconsole.log(pos.vy);
		alconsole.log('Bullets');
		alconsole.log(bullets.length);
		alconsole.log(c1.getMilliseconds()-c0.getMilliseconds());
		//finally blit (still trying to figure out flipping)
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
		c1=new Date();
		//update_screen();
	}

	stop_midi(the_music);
	destroy_midi(the_music);

	//------------------------------------------------------------------------------
	//deinitialize
	//------------------------------------------------------------------------------
	destroy_bitmap(img);
	destroy_bitmap(buffer);
	set_gfx_mode(GFX_TEXT,WIDTH,HEIGHT,0,0);
	//------------------------------------------------------------------------------
	return 0;
}
main();







