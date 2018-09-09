//this.a='asdf';
//Uint8Array.allocPlain();
//new ArrayBuffer();
//new Buffer(8);
//console.log('asdf');
/*
var WIDTH=800;
var HEIGHT=600;
var CDEPTH=32;
var GFX_TEXT=-1;
var GFX_AUTODETECT=0;
var GFX_AUTODETECT_FULLSCREEN=1;
var GFX_AUTODETECT_WINDOWED=2;
var y=480/2;
var vx=0;
var vy=0;
var frame=0;
var key;
var x=10;
var y=10;

allegro_init();
install_keyboard();
set_color_depth(CDEPTH);
set_gfx_mode(GFX_AUTODETECT,WIDTH,HEIGHT,0,0);

function hslToRgb(h,s,l){
	var r,g,b;
	if(s==0){
		r=g=b=l;
	}else{
		var hue2rgb=function hue2rgb(p, q, t){
			if(t<0)t+=1;
			if(t>1)t-=1;
			if(t<1/6) return p+(q-p)*6*t;
			if(t<1/2) return q;
			if(t<2/3) return p+(q-p)*(2/3-t)*6;
			return p;
		}
		var q=l<0.5?l*(1+s):l+s-l*s;
		var p=2*l-q;
		r=hue2rgb(p,q,h+1/3);
		g=hue2rgb(p,q,h);
		b=hue2rgb(p,q,h-1/3);
	}
	return [Math.round(r*255),Math.round(g*255),Math.round(b*255)];
}
var color=hslToRgb((frame%25)/25,1.0,0.5);
while(key!=15131){
	if(keypressed()){
		key=readkey();
		if(key==2666){//j
			vx-=0.1;
		}else if(key==2409){//i
			vy-=0.1;
		}else if(key==3180){//l
			vx+=0.1;
		}else if(key==2923){//k
			vy+=0.1;
		}
	}
	x+=vx;
	y+=vy;
	if(x>WIDTH)
		x=0;
	if(x<0)
		x=WIDTH;
	if(y>HEIGHT)
		y=0;
	if(y<0)
		y=HEIGHT;
	//rectfill(0,0,639,479,0,0,0);
	var color=hslToRgb((frame%256)/256,1.0,0.5);
	rectfill(x,y,x+10,y+10,color[0],color[1],color[2]);
	textout(key,0,0,255,255,255);
	rectfill(0,HEIGHT-20,WIDTH,HEIGHT,255,0,0);
	textout(Date(),0,HEIGHT-10,255,255,255);
	frame++;
}
textout('DONE',0,0,255,255,255);
*/
