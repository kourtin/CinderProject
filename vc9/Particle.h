#pragma once
#include "cinder/Vector.h"
#include <vector>

class Particle {
 public:
	Particle();
	Particle( ci::Vec2f , ci::Vec2f );
	void update( const ci::Vec2i &mouseLoc );
	void draw();
	
	ci::Vec2f	mLoc;
	ci::Vec2f	mVel;

	float		mDecay;	
	float		mRadius, mRadiusDest;	
	float		mScale;

	int			mAge;
	int			mLifespan;
	bool		mIsDead;
};