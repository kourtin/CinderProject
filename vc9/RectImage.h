#pragma once
#include "cinder/Channel.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include <vector>
using namespace ci;


class RectImage
{
public:
	RectImage();
	RectImage( Vec2f Loc );
	void update( const Channel32f &channel );
	void draw();

	Vec2f	mLoc;
	float	mRadius;	
	Color	mColor;
};
