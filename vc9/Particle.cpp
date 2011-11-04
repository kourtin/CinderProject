#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"

using namespace ci;

Particle::Particle()
{
}

Particle::Particle( Vec2f loc , Vec2f vel ) 
{
    mLoc		= loc;
	mVel		= vel;

	mDecay		= Rand::randFloat( 0.96f, 0.99f );
    mRadius		= 2.0f + Rand::randFloat( 0.2 );
	mRadiusDest	= 0.3f;
	mScale		= 0.1f;
	mAge		= 0;
	mLifespan	= 100;
	mIsDead		= false;
}

void Particle::update( const Vec2i &mouseLoc ) 
{	
	mLoc += mVel * 2.0f;
	mVel *= mDecay;
	mRadius -= ( mRadius - mRadiusDest ) * mScale;
	
	mAge++;
	if( mAge > mLifespan ) mIsDead = true;
}

void Particle::draw() 
{
	gl::color( Color( 1.0f, 0.0f, 0.0f ) );
    gl::drawSolidCircle( mLoc, mRadius );
}