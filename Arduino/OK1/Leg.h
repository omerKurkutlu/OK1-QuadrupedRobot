#ifndef LEG_H
#define LEG_H
#include "KinematicsEngine.h"

class Leg{
private:
	Kinematics k;
	float l1,l2;
	int elbowAngle;
    int sholderAngle;
    int hipAngle;
    float x,y,z;  // these are the coordinates

public:

    Leg();
    Leg(float l1,float l2);

    void setLegLength(float l1, float l2);
    int getElbowAngle();
	void setElbowAngle(int elbowAngle);
	int getHipAngle();
	void setHipAngle(int hipAngle);
	int getSholderAngle();
	void setSholderAngle(int sholderAngle);
	float getX();
	void setX(float x);
	float getY();
	void setY(float y);
	float getZ();
	void setZ(float z);
	//void displayAngles();
	void runKinematics();
};

#endif
