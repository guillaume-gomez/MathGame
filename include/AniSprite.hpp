#ifndef ANISPRITE_H
#define ANISPRITE_H

#ifdef DEBUG
	 #include <iostream>
#endif //DEBUG

#pragma once
#include <SFML/Graphics.hpp>

class AniSprite : public sf::Sprite
{
public:
	AniSprite();
		//initialtion list

	AniSprite(const sf::Texture& Img, int frameWidth, int frameHeight);
	~AniSprite(void);
	//Get
	sf::IntRect GetFramePosition(int frame);
	int GetFrameCount();
	//set
	void SetFrameSize(int frameWidth, int frameHeight);
	//Sets current frame
	void SetFrame(int frame);
	//sets loop speed in fps
	void SetLoopSpeed(float fps);
	//sets loop speed in seconds
	void SetLoopTime(float seconds);
	//start looping
	void Play();
	void Play(int start, int end);
	void Pause();
	//stop
	void Stop(int frameStop);
	//draw functions
	void Update();

	int getCurrentFrame()const;
	void setCurrentFrame( int frame );
	
private:
	sf::Clock clock;
	int currentFrame;
	int frameWidth;
	int frameHeight;
	float fps;
	bool isPlaying;
	int loopStart;
	int loopEnd;
};

#endif // ANISPRITE_H
