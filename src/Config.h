#pragma once

// window config
const int WindowXPos = 50;
const int WindowYPos = 50;
const int WindowWidth = 1200;
const int WindowHeight = 1200;

const float  PI = 3.14159265358979323846f;

// Sun&Earth&Moon config
const float sunScale = 5.0f;
const float moonScale = 0.3f;
const float earthScale = 1.25f;
const float merScale = 0.625f;
const float venScale = 0.95f;
const float marScale = 1.15f;
const float jupScale = 2.6f;
const float satScale = 2.55f;
const float uraScale = 1.35f;
const float nepScale = 2.0f;



const float ErothAxialAngle = 23.44;
const float SunEarthDistance = 20.0f;
const float MoonEarthDistance = 2.0f;
const float merDistance = 10.f;
const float venDistance = 15.0f;
const float marDistance = 25.0f;
const float jupDistance = 33.0f;
const float satDistance = 40.0f;
const float uraDistance = 45.0f;
const float nepDistance = 50.0f;

const int StarsNum = 10;

const int TimePast = 1;			//Ĭ��һ�����һ��
const float SelfRotate = 3.0;		//��ת�ٶ�
const int REST = 700;
const int REST_Y = -REST;
const int REST_Z = REST;
const int OFFSET = 20;

enum STARS
{
	Sun,
	Mercury,
	Venus,
	Earth,
	Moon,
	Mars,
	Jupiter,
	Saturn,
	Uranus,
	Neptune
};

#define SET_VALUE_3(name, value0, value1, value2) \
                   ((name)[0])=(value0), ((name)[1])=(value1), ((name)[2])=(value2)

#define SUN_RADIUS 48.74
#define MER_RADIUS  7.32
#define VEN_RADIUS 18.15
#define EAR_RADIUS 19.13
#define MOO_RADIUS  6.15
#define MAR_RADIUS 10.19
#define JUP_RADIUS 42.90
#define SAT_RADIUS 36.16
#define URA_RADIUS 25.56
#define NEP_RADIUS 24.78

#define MER_DIS   62.06
#define VEN_DIS  115.56
#define EAR_DIS  168.00
#define MOO_DIS   26.01
#define MAR_DIS  228.00
#define JUP_DIS  333.40
#define SAT_DIS  428.10
#define URA_DIS 848.00
#define NEP_DIS 949.10

#define MER_SPEED   87.0
#define VEN_SPEED  225.0
#define EAR_SPEED  365.0
#define MOO_SPEED   30.0
#define MAR_SPEED  687.0
#define JUP_SPEED 1298.4
#define SAT_SPEED 3225.6
#define URA_SPEED 3066.4
#define NEP_SPEED 6014.8

