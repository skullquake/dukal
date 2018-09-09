function hslToRgb(h,s,l){
	var r, g, b;
	if(s == 0){
		r = g = b = l;
	}else{
		var hue2rgb = function hue2rgb(p, q, t){
			if(t < 0) t += 1;
			if(t > 1) t -= 1;
			if(t < 1/6) return p + (q - p) * 6 * t;
			if(t < 1/2) return q;
			if(t < 2/3) return p + (q - p) * (2/3 - t) * 6;
			return p;
		}
		var q = l < 0.5 ? l * (1 + s) : l + s - l * s;
		var p = 2 * l - q;
		r = hue2rgb(p, q, h + 1/3);
		g = hue2rgb(p, q, h);
		b = hue2rgb(p, q, h - 1/3);
	}
	return [Math.round(r * 255), Math.round(g * 255), Math.round(b * 255)];
}


//double buffering example
var WIDTH=320;
var HEIGHT=200;
var CDEPTH=32;
var GFX_TEXT=-1;
var GFX_AUTODETECT=0;
var GFX_AUTODETECT_FULLSCREEN=1;
var GFX_AUTODETECT_WINDOWED=2;
allegro_init();
install_keyboard();
set_color_depth(CDEPTH);
set_gfx_mode(GFX_AUTODETECT,WIDTH,HEIGHT,0,0);
console.log('gfx');
putpixel(screen,WIDTH/2,HEIGHT/2,255,255,255);
var buffer = create_bitmap(
	WIDTH,
	HEIGHT
);
var FRAMES=128;
var NUMPIXELS=128;
var a=0;
while(a!=15131){
	if(keypressed()){
		a=readkey();
		if(a==2666){//j
		}else if(a==2409){//i
		}else if(a==3180){//l
		}else if(a==2923){//k
		}
	}
	var color=hslToRgb(new Date().getMilliseconds()/1000,1.0,0.5);
	rectfill(
		buffer,
		0,
		0,
		WIDTH-1,
		HEIGHT-1,
		color[0],
		color[1],
		color[2]
	);
	/*
	for(var j=0;j<NUMPIXELS;j++){
		var colorPixel=color;//hslToRgb(j/NUMPIXELS,1.0,0.5);
		putpixel(
			buffer,
			Math.floor(Math.random()*WIDTH),
			Math.floor(Math.random()*HEIGHT),
			colorPixel[0],
			colorPixel[1],
			colorPixel[2]
		);
	}
	*/
	blit(buffer,screen,0,0,0,0,WIDTH,HEIGHT);
}
set_gfx_mode(GFX_TEXT,WIDTH,HEIGHT,0,0);
