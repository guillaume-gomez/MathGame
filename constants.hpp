#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/System/Vector2.hpp>

const unsigned int WindowWidth = 800U;
const unsigned int WindowHeight = 600U;
const float GraphScale = 20.0f;

const unsigned int TotalDifficulty = 3 ;

enum Difficulty {Easy , Normal , Hard};
enum GameMode {Classic , NoChance};
enum class TypeObject
{
    Abstract, Circle, Point, GoalPoint, Enemy, Hero
};

const char AbstractStr[]  = "Abstract";
const char CircleStr[]  = "Circle";
const char PointStr[]  = "Point";
const char GoalPointStr[]  = "GoalPoint";
const char EnemyStr[]  = "Enemy";
const char HeroStr[] = "Hero";

const int Blur = 120;
const int Clear = 220;

const float ZoomMin = 2000.0f;
const float ZoomMax = 360.0f;

const float Thickness = 4.0f;

const float MaxSizeGraph = 25.0f;
const float Step = 0.2f;

const int WidthSpritePlayer = 24;
const int HeightSpritePlayer = 34;

const int TextPositionX = WindowWidth/2+100;
const int TextPositionY = WindowHeight-100;

const int WidthIcon = 46;
const int HeightIcon = 43;

const float PositionNBAttempX = 0.74f;
const float PositionNBAttempY = 0.90f;

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

const int Font  = 16;

const float TimePanel = 10.0f;

//const float CHARACTER_VELOCITY = 6.0f; // vitesse du personnage en graduation/sec
const sf::Vector2f GravityAcceleration(0.0f, -16.677f);

const char Sliding[] = "Sliding";
const char NoSliding[] = "NoSliding";

const float DefautCharFriction = 0.1;
const unsigned int DefaultCharWidth = 24;
const unsigned int DefaultCharHeight = 34;

const unsigned int Bikefriction = 0.05;
const unsigned int BikeWidth = 50;
const unsigned int BikeHeight = 50;

const float sentinelX = -10000.0f;
const float sentinelY = -10000.0f;

const float offsetNbAttemptEnemy = 15.0f;
#endif // CONSTANTS_HPP
