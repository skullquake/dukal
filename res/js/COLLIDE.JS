function bounding_box_collision(
	b1_x,
	b1_y,
	b1_w,
	b1_h,
	b2_x,
	b2_y,
	b2_w,
	b2_h){
	if(
		(b1_x>b2_x+b2_w-1)||//isb1ontherightsideofb2?
		(b1_y>b2_y+b2_h-1)||//isb1underb2?
		(b2_x>b1_x+b1_w-1)||//isb2ontherightsideofb1?
		(b2_y>b1_y+b1_h-1))//isb2underb1?
	{
		//nocollision
		return 0;
	}
	//collision
	return 1;
}
