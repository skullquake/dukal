var alconsole={};
alconsole.col=0;
alconsole.row=0;
alconsole.color=[255,255,255];
alconsole.buffer=null
//remember to set the buffer to screen or some other bitmap before starting to use it
alconsole.log=function(str){
	if(alconsole.buffer!=null){
		//alconsole.color=hslToRgb(new Date().getMilliseconds()/1000,1.0,0.5);
		textout(
			alconsole.buffer,
			font,
			str,
			alconsole.col*10,
			alconsole.row*10,
			makecol(
				alconsole.color[0],
				alconsole.color[1],
				alconsole.color[2]
			)
		);
		alconsole.row+=1;
		if(alconsole.row*10>HEIGHT)
			alconsole.row=0;
	}
}
