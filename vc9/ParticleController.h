#pragma once
#include "Particle.h"
#include "cinder/Vector.h"
#include <list>

class ParticleController {
 public:
	ParticleController();
	void update( const ci::Vec2i &mouseLoc );
	void draw();
	void addParticles( int amt, const ci::Vec2i &mouseLoc , const ci::Vec2i &mouseVel );
	void removeParticles( int amt );
	
	std::list<Particle>	mParticles;
};