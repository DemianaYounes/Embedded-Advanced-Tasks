

#ifndef RGB_PRIVATE_H_
#define RGB_PRIVATE_H_

static u8 RGB_BasicsColors[NUM_OF_COLORS][RGB]={/* RED  ,GREEN  ,BLUE*/
	{255,   255,   255}, //Black
	{254,   254,   254}, //White
	{254,   255,   255}, //Red
	{255,   254,   255}, //Lime
	{255,   255,   254}, //Blue
	{254,   254,   255}, //Yellow
	{255,   254,   254}, //Cyan / Aqua	
	{254,   255,   254}, //Magenta / Fuchsia	
	{191,   191,   191}, //Silver
	{127,   127,   127}, //Gray
	{127,   255,   255}, //Maroon
	{127,   127,   255}, //Olive
	{255,   127,   255}, //Green
	{127,   255,   127}, //Purple
	{255,127,127},       //Teal
	{255,   255,   127} //Navy
};

static u8 RGB_RedColors[NUM_OF_COLORS][RGB]={/* RED  ,GREEN  ,BLUE*/
		{127,   255,   255}, //maroon
		{138,   255,   255}, //dark red
		{164,   41,   41}, //brown
		{177,   33,   33}, //firebrick
		{219,   19,   59}, //crimson
		{254,   255,   255}, //red
		{254,   98,   70}, //tomato
		{254,   126,   79}, //coral
		{204,   91,   91}, //indian red
		{239,   127,   127}, //light coral
		{233,   149,   121}, //dark salmon
		{249,   127,   113}, //salmon
		{254,   159,   121}, //light salmon
		{254,   68,   255}, //orange red
		};




#endif /* RGB_PRIVATE_H_ */