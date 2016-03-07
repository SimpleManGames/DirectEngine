#ifndef _SHAPE_H
#define _SHAPE_H


struct Shape 
{
public:
	union
	{
		Vector2D position;
		float x, y;
	};
	Shape() { }
	~Shape() { }
};

#endif
