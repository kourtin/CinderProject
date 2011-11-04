#include "RectImageController.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Channel.h"
#include "cinder/Vector.h"
#include <list>

using namespace ci;
using std::list;

RectImageController::RectImageController()
{
}

RectImageController::RectImageController( int res )
{
	int mXRes = app::getWindowWidth()/res;
	int mYRes = app::getWindowHeight()/res;
	
	//mRectImages.push_back( RectImage( Vec2f( mXRes, mYRes ) ) );

	for( int y=0; y<mYRes; y++ )
	{
		for( int x=0; x<mXRes; x++ )
		{
			float X = ( x ) * (float)res;
			float Y = ( y ) * (float)res;
			mRectImages.push_back( RectImage( Vec2f( X, Y ) ) );
		}
	}
}

void RectImageController::update( const Channel32f &channel )
{
	for( list<RectImage>::iterator p = mRectImages.begin(); p != mRectImages.end(); ++p )
	{
        p->update( channel );
    }
}

void RectImageController::draw()
{
	for( list<RectImage>::iterator p = mRectImages.begin(); p != mRectImages.end(); ++p )
	{
		p->draw();
	}
}