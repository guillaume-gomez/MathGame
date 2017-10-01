/*
 *  A 2D video game in C++ with SFML where platforms are actually Maths Curves resulting of equations you write
 *  Copyright (C) 2013,2017  Gomez Guillaume, Jarretier Adrien
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.*
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Contact us on Github : https://github.com/guillaume-gomez/MathGame
 *                      or https://github.com/AdrienJarretier
 */

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
