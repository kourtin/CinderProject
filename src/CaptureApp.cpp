#include "cinder/app/AppBasic.h"
#include "cinder/ImageIO.h"
#include "cinder/gl/Texture.h"
#include "cinder/Channel.h"
#include "cinder/Capture.h"
#include "cinder/Utilities.h"
#include "../vc9/RectImageController.h"
#include "../vc9/ParticleController.h"
#include "CinderOpenCV.h"

#define RESOLUTION 2
#define NUM_PARTICLES_TO_SPAWN 50

using namespace ci;
using namespace ci::app;

class CaptureApp : public AppBasic 
{
  public:
	void keyDown( KeyEvent event );
	void mouseDown( MouseEvent event );
	void mouseUp( MouseEvent event );
	void mouseMove( MouseEvent event );
	void mouseDrag( MouseEvent event );
	void setup();
	void update();
	void draw();
	
	Capture			mCap;
	Channel32f		mChannel;
	gl::Texture		mTexture;
	Vec2i			mMouseLoc;
	Vec2f			mMouseVel;

	RectImageController mRectImageController;	
	ParticleController	mParticleController;	
	
	bool mDrawParticles;
	bool mDrawVideoCapture;
	bool mDrawVideoCaptureRect;
	bool mIsPressed;
};

void CaptureApp::setup()
{
	try 
	{
		mCap = Capture( 640, 480 );
		mCap.start();
	}
	catch( ... ) 
	{
		console() << "Failed to initialize capture" << std::endl;
	}
	
	mMouseLoc = Vec2i( 0, 0 );
	mMouseVel = Vec2f::zero();

	mDrawParticles			= false;
	mDrawVideoCapture		= false;
	mIsPressed				= false;
	mDrawVideoCaptureRect	= false;

	mRectImageController = RectImageController( RESOLUTION );
}

void CaptureApp::update()
{
	if( mCap && mCap.checkNewFrame() ) 
	{
		cv::Mat input( toOcv( mCap.getSurface() ) );
		//mTexture = gl::Texture( fromOcv( input ) );
		mChannel = Channel32f( fromOcv( input ) );
		mTexture = mChannel;
		mRectImageController.update( mChannel );
	}

	if( mIsPressed )
		mParticleController.addParticles(NUM_PARTICLES_TO_SPAWN, mMouseLoc , mMouseVel );

	mParticleController.update( mMouseLoc );
}

void CaptureApp::draw()
{
	//gl::clear();
	gl::clear( Color( 0, 0, 0 ), true );
	//if( mTexture ) gl::draw( mTexture );

	if( mDrawVideoCapture )
	{
		if( mTexture ) 
		{
			glColor3f( 1, 1, 1 );
			gl::draw( mTexture );
		}
	}

	if( mDrawVideoCaptureRect )
	{
		glDisable( GL_TEXTURE_2D );
		glColor3f( 1, 1, 1 );
		mRectImageController.draw();
	}
	
	if( mDrawParticles )
	{
		glDisable( GL_TEXTURE_2D );
		glColor3f( 1, 1, 1 );
		mParticleController.draw();
	}
}

void CaptureApp::keyDown( KeyEvent event )
{
	if( event.getChar() == '1' )
	{
		mDrawVideoCapture = ! mDrawVideoCapture;
	} 
	else if( event.getChar() == '2' )
	{
		mDrawParticles = ! mDrawParticles;
	}
	else if( event.getChar() == '3' )
	{
		mDrawVideoCaptureRect = ! mDrawVideoCaptureRect;
	}
}

void CaptureApp::mouseDown( MouseEvent event )
{
	mIsPressed = true;
}

void CaptureApp::mouseUp( MouseEvent event )
{
	mIsPressed = false;
}

void CaptureApp::mouseMove( MouseEvent event )
{	
	mMouseVel = ( event.getPos() - mMouseLoc );
	mMouseLoc = event.getPos();
}

void CaptureApp::mouseDrag( MouseEvent event )
{
	mouseMove( event );
}

CINDER_APP_BASIC( CaptureApp , RendererGl )