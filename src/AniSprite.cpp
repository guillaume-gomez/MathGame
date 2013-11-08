#include "../include/AniSprite.hpp"

AniSprite::AniSprite(void)
	: sf::Sprite()
{
	this->fps=1;
	this->currentFrame=0;
	this->isPlaying = false;
	this->loopStart = 0;
	this->SetFrameSize(0, 0);
}

AniSprite::AniSprite(const sf::Texture& Img, int frameW, int frameH)
		: sf::Sprite(Img)
{
	this->fps=1;
	this->currentFrame=0;
	this->isPlaying = false;
	this->loopStart = 0;
	this->SetFrameSize(frameW, frameH);
	//now calculate stuff
}

AniSprite::~AniSprite(void)
{
}
int AniSprite::GetFrameCount()
{
	unsigned int across =
		getTexture()->getSize().x /
		this->frameWidth;
	unsigned int down =
		getTexture()->getSize().y /
		this->frameHeight;

	return across*down;
}
//first frame is frame ZERO
sf::IntRect AniSprite::GetFramePosition(int frame)
{
	unsigned int across =
		getTexture()->getSize().x /
		this->frameWidth;
	sf::IntRect result(
		(frame%int(across))*frameWidth,
		(frame/int(across))*frameHeight,
		frameWidth,
		frameHeight);
	return result;

}
//
void
AniSprite::SetFrameSize(int frameW, int frameH)
{
	this->frameWidth = (frameW>0 ? frameW : 1);
	this->frameHeight = (frameH>0 ? frameH : 1);
	this->setTextureRect(sf::IntRect(0,0,frameW,frameH));
}
//Sets current frame
void
AniSprite::SetFrame(int frame)
{
	this->currentFrame = frame;
}
//sets loop speed in fps
void
AniSprite::SetLoopSpeed(float newfps)
{
	this->fps = newfps;
}

//sets loop speed in seconds
void AniSprite::SetLoopTime(float seconds)
{
	fps = GetFrameCount()/seconds;
}

//start looping
void
AniSprite::Play()
{
	this->Play(0,GetFrameCount());
}
void
AniSprite::Play(int start, int end)
{
	loopStart = start;
	loopEnd = end;
	isPlaying = true;
}
//stop
void
AniSprite::Pause()
{
	isPlaying = false;
}

void AniSprite::Stop(int frameStop)
{
	loopStart = loopEnd = frameStop;
	clock.restart();
	Update();
	isPlaying = false;
}
//update function
void
AniSprite::Update()
{
	if(isPlaying)
	{
		int frameCount = (loopEnd+1) - loopStart;

 		float timePosition = (clock.getElapsedTime().asSeconds() * fps);

		currentFrame = loopStart +
			(int)timePosition % frameCount;

		this->setTextureRect(GetFramePosition(currentFrame));
	}
}

int AniSprite::getCurrentFrame()const
{
    return currentFrame;
}

void AniSprite::setCurrentFrame( int frame )
{
    currentFrame = frame;
}
