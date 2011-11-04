#pragma once
#include "RectImage.h"
#include "cinder/Channel.h"
#include "cinder/Vector.h"
#include <list>

using namespace ci;

class RectImageController
{
public:
	RectImageController();
	RectImageController( int res );
	void update( const Channel32f &channel );
	void draw();

	std::list<RectImage>	mRectImages;
};
