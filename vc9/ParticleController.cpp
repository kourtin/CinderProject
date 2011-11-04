#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "ParticleController.h"

using namespace ci;
using std::list;

ParticleController::ParticleController()
{
}

void ParticleController::update( const Vec2i &mouseLoc ) 
{
    for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p )
	{
 		if( p->mIsDead )
		{
			p = mParticles.erase( p );
		} 
		else 
		{
			p->update( mouseLoc );
			//++p;
		}
    }
}

void ParticleController::draw()
{
	for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p )
	{
		p->draw();
	}
}

void ParticleController::addParticles( int amt, const Vec2i &mouseLoc , const Vec2i &mouseVel ) 
{
    for( int i=0; i<amt; i++ ) 
	{
        Vec2f loc = mouseLoc + Rand::randVec2f() * 10.0f;
        Vec2f vel = mouseVel * 0.25f + Rand::randVec2f() * 10.0f;
        mParticles.push_back( Particle( loc, vel ) );
    }
}

void ParticleController::removeParticles( int amt )
{
	for( int i=0; i<amt; i++ )
	{
		mParticles.pop_back();
	}
}