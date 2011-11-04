#include "RectImage.h"
#include "cinder/Channel.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "cinder/gl/gl.h"

using namespace ci;

RectImage::RectImage()
{
}

RectImage::RectImage( Vec2f loc )
{
	mLoc	= loc;
	mRadius	= 3.0f;
}

void RectImage::update( const Channel32f &channel )
{
	float gray = channel.getValue( mLoc );
    mColor = Color( gray, gray, gray );
}

void RectImage::draw()
{
	gl::color( mColor );
	//gl::color( Color( 1.0f, 0.0f, 0.0f ) );
	//gl::drawSolidCircle( mLoc, mRadius );
	Rectf rect( mLoc.x, mLoc.y, mLoc.x + mRadius, mLoc.y + mRadius );
	gl::drawSolidRect( rect );
}