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

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

const unsigned int WindowWidth = 800U;
const unsigned int WindowHeight = 600U;
const float GraphScale = 20.0f;

const int MaxAttempt = 10;

const unsigned int TotalDifficulty = 3 ;

enum Difficulty {Easy , Normal , Hard};
enum GameMode {Classic , NoChance, Dynamic};
enum class TypeOfCamera {Static, Moveable};
enum class TypeObject
{
    Abstract, Circle, Point, GoalPoint, Enemy, Hero, Integral, Function, Info
};

const char AbstractStr[]  = "Abstract";
const char CircleStr[]  = "Circle";
const char PointStr[]  = "Point";
const char GoalPointStr[]  = "GoalPoint";
const char HeroInitialPosition[] = "HeroPosition";
const char EnemyStr[]  = "Enemy";
const char HeroStr[] = "Hero";
const char IntegralStr[] = "Integral";
const char FunctionStr[] = "Function";
const char InfoStr[] = "Info";

const int Blur = 120;
const int Clear = 220;

const int WidthWorld = 2048;
const int HeightWorld = 2048;

const float ZoomMin = 2000.0f;
const float ZoomMax = 360.0f;

const float Thickness = 4.0f;

const float MaxSizeGraph = 50.0f;
const float Step = 0.2f;

const int WidthSpritePlayer = 24;
const int HeightSpritePlayer = 34;

const int TextPositionX = WindowWidth/2+100;
const int TextPositionY = WindowHeight-100;

const int WidthIcon = 46;
const int HeightIcon = 43;

const float PositionNBAttempX = 0.74f;
const float PositionNBAttempY = 0.925f;

const float PositionButtonResetX = 0.80f;
const float PositionButtonResetY = 0.02f;

const float PositionButtonSoundX = 0.87f;
const float PositionButtonSoundY = 0.02f;

const float PositionButtonBackX = 0.94f;
const float PositionButtonBackY = 0.02f;

const float PositionTextAreaX = 0.02f;
const float PositionTextAreaY = 0.88f;

const float PositionButtonX = 200.0f;
const float OffsetButtonX = 50.0f;
const float OffsetBarY = 50.0f;
const float PositionButtonEasyY = 100.0f ;
const float PositionButtonNormalY = 280.0f;
const float PositionButtonHardY = 430.0f;
const unsigned int nbButtonLevelChoose = 4 ;

const float sizePoint = 0.15f;

const int backgroundColor = 230;
const int gridGameColor = 235;

const int Font  = 15;

const float TimePanel = 10.0f;

//const float CHARACTER_VELOCITY = 6.0f; // vitesse du personnage en graduation/sec
const sf::Vector2f GravityAcceleration(0.0f, -52.0f);
const unsigned int JumpSpeed = 15;

const char Sliding[] = "Sliding";
const char NoSliding[] = "NoSliding";

const float CharSpeed = 15.0f;
const float DefautCharFriction = 0.1;
const unsigned int DefaultCharWidth = 24;
const unsigned int DefaultCharHeight = 34;

const unsigned int Bikefriction = 0.05;
const unsigned int BikeWidth = 50;
const unsigned int BikeHeight = 50;

const float sentinelX = -10000.0f;
const float sentinelY = -10000.0f;

const float offsetNbAttemptEnemy = 15.0f;

const float DefaultSoundVolume = 10.0f;

const sf::Color CurveColor(50,67,135);
const sf::Color PreviousCurveColor(0,150,0,75);
const sf::Color NextCurveColor(255,0,0,75);

#endif // CONSTANTS_HPP
