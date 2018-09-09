//todo: fix up new stuff for base initializatino (buffer and screen stuff)

var WIDTH=640;
var HEIGHT=480;
var frame=0;
var FRAMES=128;
var CDEPTH=32;
var GFX_TEXT=-1;
var GFX_AUTODETECT=0;
var GFX_AUTODETECT_FULLSCREEN=1;
var GFX_AUTODETECT_WINDOWED=2;
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
function Point3D(x,y,z) {
	this.x=x;
	this.y=y;
	this.z=z;
	this.rotateX=function(currentAngle) {
		var rad=currentAngle * Math.PI / 180;
		var cosa=Math.cos(rad);
		var sina=Math.sin(rad);
		var y=this.y * cosa - this.z * sina;
		var z=this.y * sina + this.z * cosa;
		return new Point3D(this.x, y, z);
	};
	this.rotateY=function(currentAngle) {
		var rad=currentAngle * Math.PI / 180;
		var cosa=Math.cos(rad);
		var sina=Math.sin(rad);
		var z=this.z * cosa - this.x * sina;
		var x=this.z * sina + this.x * cosa;
		return new Point3D(x,this.y, z);
	};
	this.rotateZ=function(currentAngle) {
		var rad=currentAngle * Math.PI / 180;
		var cosa=Math.cos(rad);
		var sina=Math.sin(rad);
		var x=this.x * cosa - this.y * sina;
		var y=this.x * sina + this.y * cosa;
		return new Point3D(x, y, this.z);
	};
	this.project=function(viewWidth, viewHeight, fieldOfView, viewDistance) {
		var factor=fieldOfView / (viewDistance + this.z);
		var x=this.x*factor+viewWidth/2;
		var y=this.y*factor+viewHeight/2;
		return new Point3D(x,y,this.z);
	};
}
var vertices=[
	new Point3D(-1,1,-1),
	new Point3D(1,1,-1),
	new Point3D(1,-1,-1),
	new Point3D(-1,-1,-1),
	new Point3D(-1,1,1),
	new Point3D(1,1,1),
	new Point3D(1,-1,1),
	new Point3D(-1,-1,1)
];
var cubeFaces=[[0,1,2,3],[1,5,6,2],[5,4,7,6],[4,0,3,7],[0,4,5,1],[3,2,6,7]]
var currentAngle=0;
var scr={
	w : WIDTH,
	h:  HEIGHT
};
currentAngle=0;
color=hslToRgb(0,1.0,0.5);
function renderLoop(){
	var points=new Array();
	vertices.map(
		function(vertex){ 
			points.push(
				vertex.rotateX(currentAngle).rotateY(currentAngle).rotateZ(currentAngle).project(
					scr.w,
					scr.h,
					196,//90,//128,
					4//7
				)
			);
		}
	);
	rectfill(
		screen,
		0,
		0,
		scr.w,
		scr.h,
		0,
		0,
		0
	);
	cubeFaces.map(
		function(cubeFace){
			line(
				screen,
				points[cubeFace[0]].x,points[cubeFace[0]].y,
				points[cubeFace[1]].x,points[cubeFace[1]].y,
				color[0],
				color[1],
				color[2]
			);
			line(
				screen,
				points[cubeFace[1]].x,points[cubeFace[1]].y,
				points[cubeFace[1]].x,points[cubeFace[1]].y,
				color[0],
				color[1],
				color[2]
			);
			line(
				screen,
				points[cubeFace[1]].x,points[cubeFace[1]].y,
				points[cubeFace[2]].x,points[cubeFace[2]].y,
				color[0],
				color[1],
				color[2]
			);
			line(
				screen,
				points[cubeFace[2]].x,points[cubeFace[2]].y,
				points[cubeFace[3]].x,points[cubeFace[3]].y,
				color[0],
				color[1],
				color[2]
			);
			textout(
				screen,
				'Frame: '+frame,
				0,
				HEIGHT-20,
				color[0],
				color[1],
				color[2]
			);
			textout(
				screen,
				'Angle: '+currentAngle,
				0,
				HEIGHT-10,
				color[0],
				color[1],
				color[2]
			);
			textout(screen,"     _ ____   ____ _   _ ____  _____    ",   0, 0+frame/FRAMES*HEIGHT,color[0],color[1],color[2]);
			textout(screen,"    | / ___| / ___| | | | __ )| ____|   ",   0,10+frame/FRAMES*HEIGHT,color[0],color[1],color[2]);
			textout(screen," _  | \\___ \\| |   | | | |  _ \\|  _|  ",   0,20+frame/FRAMES*HEIGHT,color[0],color[1],color[2]);
			textout(screen,"| |_| |___) | |___| |_| | |_) | |___    ",   0,30+frame/FRAMES*HEIGHT,color[0],color[1],color[2]);
			textout(screen," \\___/|____/ \\____|\\___/|____/|_____|",   0,40+frame/FRAMES*HEIGHT,color[0],color[1],color[2]);
			currentAngle+=0.5;
		}
	);
}
for(frame=0;frame<FRAMES;frame++){
	//color=hslToRgb((frame%25)/25,1.0,0.5);
	renderLoop();
}
readkey();
set_gfx_mode(GFX_TEXT,WIDTH,HEIGHT,0,0);
