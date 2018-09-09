console.log=function(a){};
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

//-----------------------------------
var WIDTH=640;
var HEIGHT=480;
var CDEPTH=32;
var GFX_TEXT=-1;
var GFX_AUTODETECT=0;
var GFX_AUTODETECT_FULLSCREEN=1;
var GFX_AUTODETECT_WINDOWED=2;
allegro_init();
console.log('init');
install_keyboard();
console.log('keyboard');
set_color_depth(CDEPTH);
console.log('cdepth');
set_gfx_mode(GFX_AUTODETECT,WIDTH,HEIGHT,0,0);
				rectfill(
					screen,
					0,
					0,
					10,
					10,
					255,
					255,
					255
				);


readkey();
console.log('gfxmod');
console.log(screen);
//-----------------------------------
function StarField(screen,width, height, num_stars) {
	console.log('StarField(screen, width, height, num_stars)');
	var width = width ? width : 600,
		height = height ? height : 600,
		origin_x = width / 2,
		origin_y = height / 2,
		stars = [],
		num_stars = num_stars ? num_stars : 50;
	function create_star() {
		console.log('function create_star()');
		var star = {};
		star.x = Math.random() * width - origin_x;
		star.y = Math.random() * height - origin_y;
		star.z = star.max_depth = Math.max(width, height);

		var xcoeff = star.x > 0 ? 1 : -1;
		var ycoeff = star.y > 0 ? 1 : -1;

		if (Math.abs(star.x) > Math.abs(star.y)) {
			star.dx = 1.0;
			star.dy = Math.abs(star.y / star.x);
		} else {
			star.dx = Math.abs(star.x / star.y);
			star.dy = 1.0;
		}

		star.dx *= xcoeff;
		star.dy *= ycoeff;
		star.dz = -1;

		star.ddx = .1 * star.dx;
		star.ddy = .1 * star.dy;

		star.width = 2;
		return star;
	}
	function move(star) {
		console.log('function move(star)');
		star.x += star.dx;
		star.y += star.dy;
		star.z += star.dz;
		star.dx += star.ddx;
		star.dy += star.ddy;
		star.width = 2 + ((star.max_depth - star.z) * .1);
	}
	function update_stars(screen) {
		console.log('function update_stars(ctx)');
		console.log(screen);
		for (var i = 0; i < stars.length; i++) {
			move(stars[i]);
			if (stars[i].x < -origin_x || stars[i].x > origin_x ||
				stars[i].y < -origin_y || stars[i].y > origin_y) {
				// remove
				stars[i] = create_star();
			} else {
				rectfill(
					screen,
					stars[i].x + origin_x,
					stars[i].y + origin_y,
					stars[i].width,
					stars[i].width,
					255,
					255,
					255
				);
			}
		}
	}

	// drawing routine
	this.draw = function() {
		console.log('function draw()');
		console.log(screen);
		rectfill(
			screen,
			0,
			0,
			WIDTH,
			HEIGHT,
			0,
			0,
			0
		);
		update_stars(screen);
		// repeat
		t = setTimeout("draw()", 30);
	}
	for (var i=0; i < num_stars; i++) {
		stars.push(create_star());
	}
	return this;
}

//-----------------------------------
var starfield=StarField(screen,WIDTH,HEIGHT,8);
console.log(starfield);
starfield.draw(screen);

//-----------------------------------
set_gfx_mode(GFX_TEXT,WIDTH,HEIGHT,0,0);
console.log('textmod');
