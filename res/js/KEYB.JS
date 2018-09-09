var a=null;
var x=640/2;
var y=480/2;
var vx=0;
var vy=0;
while(a!=15131){
	if(keypressed()){
		a=readkey();
		if(a==2666){//j
			vx-=0.1;
		}else if(a==2409){//i
			vy-=0.1;
		}else if(a==3180){//l

			vx+=0.1;
		}else if(a==2923){//k
			vy+=0.1;
		}
	}
	x+=vx;
	y+=vy;
	
	rectfill(0,0,639,479,0,0,0);
	rectfill(x,y,x+10,y+10,255,255,255);
	textout(a,0,0,255,255,255);
}
textout('DONE',0,0,255,255,255);


