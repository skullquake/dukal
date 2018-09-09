//-------------------------
var WIDTH=320;
var HEIGHT=200;
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

function getStr(){
	var retval='';
	for(var i=0;i<(Math.floor(Math.random()*16));i++){
		retval+=i;
	}
	return retval;
}
function getX(){
	return Math.floor(Math.random()*320);
}
function getY(){
	return Math.floor(Math.random()*200);
}
function getColor(){
	return hslToRgb(Math.random(),Math.random(),Math.random());
}
function randomString(){
	var s=["foo","bar","baz"];
	return s[
		Math.floor(Math.random()*s.length)
	];
}
function textoutTest(){
	for(var i=0;i<128;i++){
		var color=getColor();
		textout(
			randomString(),
			Math.floor(Math.random()*320),
			Math.floor(Math.random()*200),
			color[0],
			color[1],
			color[2]
		);
	}
}
function drawLineTest(){
	for(var i=0;i<128;i++){
		var x0=Math.floor(Math.random()*WIDTH);
		var y0=Math.floor(Math.random()*HEIGHT);
		var x1=Math.floor(Math.random()*WIDTH);
		var y1=Math.floor(Math.random()*HEIGHT);
		textout(
			'['+x0+','+y0+']['+x1+','+y1+']',
			0,
			190,
			255,255,255
		);
		var color=getColor();
		line(
			x0,
			y0,
			x1,
			y1,
			color[0],
			color[1],
			color[2]

		);
	}
}
function putpixelTest(){
	var x0;
	var y0;
	var NUMPIXELS=512;
	for(var i=0;i<NUMPIXELS;i++){
		x0=Math.floor(Math.random()*WIDTH);
		y0=Math.floor(Math.random()*HEIGHT);
		textout(
			'['+x0+','+y0+']',
			0,
			190,
			255,255,255
		);
		var color=hslToRgb(i/NUMPIXELS,1.0,0.5);
		putpixel(
			x0,	
			y0,
			color[0],
			color[1],
			color[2]
		);
	}
}
function textoutTest(){
	var x0;
	var y0;
	for(var i=0;i<4096;i++){
		x0=Math.floor(Math.random()*WIDTH);
		y0=Math.floor(Math.random()*HEIGHT);
		var color=getColor();
		textout(
			randomString(),
			x0,
			y0,
			color[0],
			color[1],
			color[2]
		);
	}

}
function rectTest(){
	for(var i=0;i<128;i++){
		var x0=Math.floor(Math.random()*WIDTH);
		var y0=Math.floor(Math.random()*HEIGHT);
		var x1=Math.floor(Math.random()*WIDTH);
		var y1=Math.floor(Math.random()*HEIGHT);
		textout(
			'['+x0+','+y0+']['+x1+','+y1+']',
			0,
			190,
			255,255,255
		);
		var color=getColor();
		rect(
			x0,
			y0,
			x1,
			y1,
			color[0],
			color[1],
			color[2]

		);
	}
}
function rectfillTest(){
	for(var i=0;i<128;i++){
		var x0=Math.floor(Math.random()*WIDTH);
		var y0=Math.floor(Math.random()*HEIGHT);
		var x1=Math.floor(Math.random()*WIDTH);
		var y1=Math.floor(Math.random()*HEIGHT);
		textout(
			'['+x0+','+y0+']['+x1+','+y1+']',
			0,
			190,
			255,255,255
		);
		var color=getColor();
		rectfill(
			x0,
			y0,
			x1,
			y1,
			color[0],
			color[1],
			color[2]

		);
	}
}
function circleTest(){
	for(var i=0;i<128;i++){
		var x0=Math.floor(Math.random()*WIDTH);
		var y0=Math.floor(Math.random()*HEIGHT);
		var r=Math.floor(Math.random()*128);
		textout(
			'['+x0+','+y0+']['+r+']',
			0,
			190,
			255,255,255
		);
		var color=getColor();
		circle(
			x0,
			y0,
			r,
			color[0],
			color[1],
			color[2]

		);
	}
}
function circlefillTest(){
	for(var i=0;i<128;i++){
		var x0=Math.floor(Math.random()*WIDTH);
		var y0=Math.floor(Math.random()*HEIGHT);
		var r=Math.floor(Math.random()*128);
		textout(
			'['+x0+','+y0+']['+r+']',
			0,
			190,
			255,255,255
		);
		var color=getColor();
		circlefill(
			x0,
			y0,
			r,
			color[0],
			color[1],
			color[2]

		);
	}
}
function ellipseTest(){
	for(var i=0;i<32;i++){
		var x0=Math.floor(Math.random()*WIDTH);
		var y0=Math.floor(Math.random()*HEIGHT);
		var rx=Math.floor(Math.random()*128);
		var ry=Math.floor(Math.random()*128);
		textout(
			'['+x0+','+y0+']'+'['+rx+','+ry+']',
			0,
			190,
			255,255,255
		);
		var color=getColor();
		ellipse(
			x0,
			y0,
			rx,
			ry,
			color[0],
			color[1],
			color[2]

		);
	}
}
function ellipsefillTest(){
	for(var i=0;i<32;i++){
		var x0=Math.floor(Math.random()*WIDTH);
		var y0=Math.floor(Math.random()*HEIGHT);
		var rx=Math.floor(Math.random()*128);
		var ry=Math.floor(Math.random()*128);
		textout(
			'['+x0+','+y0+']'+'['+rx+','+ry+']',
			0,
			190,
			255,255,255
		);
		var color=getColor();
		ellipsefill(
			x0,
			y0,
			rx,
			ry,
			color[0],
			color[1],
			color[2]

		);
	}
}
function triangleTest(){
	for(var i=0;i<32;i++){
		var x0=Math.floor(Math.random()*WIDTH);
		var y0=Math.floor(Math.random()*HEIGHT);
		var x1=Math.floor(Math.random()*WIDTH);
		var y1=Math.floor(Math.random()*HEIGHT);
		var x2=Math.floor(Math.random()*WIDTH);
		var y2=Math.floor(Math.random()*HEIGHT);
		textout(
			'['+x0+','+y0+']'+
			'['+x1+','+y1+']'+
			'['+x2+','+y2+']',
			0,
			190,
			255,255,255
		);
		var color=getColor();
		triangle(
			x0,
			y0,
			x1,
			y1,
			x2,
			y2,
			color[0],
			color[1],
			color[2]

		);
	}
}
function hslToRgbTest(){
	for(var x=0;x<WIDTH;x++){
		var color=hslToRgb(x/WIDTH,1.0,0.5);
		line(
			x,
			0,
			x,
			HEIGHT,
			color[0],
			color[1],
			color[2]

		);
	}
}

/*
hslToRgbTest();
putpixelTest();
drawLineTest();
textoutTest();
rectfillTest();
circleTest();
circlefillTest();
ellipseTest();
ellipsefillTest();
triangleTest();
*/
//--------------------------------------
function Point3D(x,y,z) {
            
            this.x = x;
            this.y = y;
            this.z = z;
            this.rotateX = function(currentAngle) {
                
                var rad = currentAngle * Math.PI / 180;
                var cosa = Math.cos(rad);
                var sina = Math.sin(rad);
                var y = this.y * cosa - this.z * sina;
                var z = this.y * sina + this.z * cosa;
                
                return new Point3D(this.x, y, z);
            };
            this.rotateY = function(currentAngle) {
                
                var rad = currentAngle * Math.PI / 180;
                var cosa = Math.cos(rad);
                var sina = Math.sin(rad);
                var z = this.z * cosa - this.x * sina;
                var x = this.z * sina + this.x * cosa;
                
                return new Point3D(x,this.y, z);
            };
            this.rotateZ = function(currentAngle) {
                
                var rad = currentAngle * Math.PI / 180;
                var cosa = Math.cos(rad);
                var sina = Math.sin(rad);
                var x = this.x * cosa - this.y * sina;
                var y = this.x * sina + this.y * cosa;
                
                return new Point3D(x, y, this.z);
            };
            this.project = function(viewWidth, viewHeight, fieldOfView, viewDistance) {
                var factor = fieldOfView / (viewDistance + this.z);
                var x = this.x * factor + viewWidth / 2;
                var y = this.y * factor + viewHeight / 2;
                return new Point3D(x, y, this.z);
            };
        }
        var vertices = [
            new Point3D(-1,1,-1),
            new Point3D(1,1,-1),
            new Point3D(1,-1,-1),
            new Point3D(-1,-1,-1),
            new Point3D(-1,1,1),
            new Point3D(1,1,1),
            new Point3D(1,-1,1),
            new Point3D(-1,-1,1)
        ];
        var cubeFaces = [[0,1,2,3],[1,5,6,2],[5,4,7,6],[4,0,3,7],[0,4,5,1],[3,2,6,7]]
        var currentAngle = 0;
        var screen = {
            w : 128,
            h: 128
        };
var screen={};
screen.w=WIDTH;
screen.h=HEIGHT;
currentAngle=0;
color=hslToRgb(0,1.0,0.5);
function renderLoop(){
	var points = new Array();
	//rectfill(0,0,screen.w, screen.h,0,0,0);
	vertices.map(
		function(vertex){ 
			points.push(
				vertex.rotateX(currentAngle).rotateY(currentAngle).rotateZ(currentAngle).project(
					screen.h,
					screen.w,
					128,
					7
				)
			);
		}
	);
	cubeFaces.map(
		function(cubeFace){
			line(
				points[cubeFace[0]].x,points[cubeFace[0]].y,
				points[cubeFace[1]].x,points[cubeFace[1]].y,
				color[0],
				color[1],
				color[2]
			);
			line(
				points[cubeFace[1]].x,points[cubeFace[1]].y,
				points[cubeFace[1]].x,points[cubeFace[1]].y,
				color[0],
				color[1],
				color[2]
			);
			line(
				points[cubeFace[1]].x,points[cubeFace[1]].y,
				points[cubeFace[2]].x,points[cubeFace[2]].y,
				color[0],
				color[1],
				color[2]
			);
			line(
				points[cubeFace[2]].x,points[cubeFace[2]].y,
				points[cubeFace[3]].x,points[cubeFace[3]].y,
				color[0],
				color[1],
				color[2]
			);
		}
	);
	currentAngle+=2;
}
var FRAMES=32;
for(var i=0;i<FRAMES;i++){
	color=hslToRgb(i/FRAMES,1.0,0.5);
	renderLoop();
}
