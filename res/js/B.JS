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
function getColor(){
	return hslToRgb(Math.random(),Math.random(),Math.random());
}
function randomString(){
	var strings=["foo","bar","baz"];
	return strings[Math.floor(Math.random()*strings.length)];
}
function textoutTest(){
	for(var i=0;i<1024;i++){
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
	var WIDTH=320;
	var HEIGHT=200;
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
	line(
		x0,
		y0,
		x0+1,
		y0+1
	);
}
function putpixelTest(){
	var WIDTH=320;
	var HEIGHT=200;
	var x0=Math.floor(Math.random()*WIDTH);
	var y0=Math.floor(Math.random()*HEIGHT);
	textout(
		'['+x0+','+y0+']['+x1+','+y1+']',
		0,
		190,
		255,255,255
	);
	var color=getColor();
	putpixel(
		1,
		1,
		255,
		255,
		255
	);
}
putpixelTest();
