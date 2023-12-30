#include "Leg.h"
#include "KinematicsEngine.h"

Leg::Leg(){
	k.setLegLength(12, 12); //it is dummy valuem, we set the lenght in the Quadruped constructor
	x=0;
	y=0;
	z=5;
}

Leg::Leg(float l1,float l2){
	k.setLegLength(l1, l2);
	x=0;
	y=0;
	z=5;
}

void Leg::setLegLength(float l1, float l2)
{
	this->l1=l1;
	this->l2=l2;
}


void Leg::runKinematics()
{
  k.setToPosition(x,y,z);
  
  sholderAngle=k.theta1;
  elbowAngle=k.theta2;
  hipAngle=k.theta3;
}



int Leg::getElbowAngle()  {
	return elbowAngle;
}

void Leg::setElbowAngle(int elbowAngle) {
	this->elbowAngle = elbowAngle;
}

int Leg::getHipAngle()  {
	return hipAngle;
}

void Leg::setHipAngle(int hipAngle) {
	this->hipAngle = hipAngle;
}

int Leg::getSholderAngle()  {
	return sholderAngle;
}

void Leg::setSholderAngle(int sholderAngle) {
	this->sholderAngle = sholderAngle;
}

float Leg::getX()  {
	return x;
}

void Leg::setX(float x) {
	this->x = x;
}

float Leg::getY()  {
	return y;
}

void Leg::setY(float y) {
	this->y = y;
}

float Leg::getZ()  {
	return z;
}

void Leg::setZ(float z) {
	this->z = z;
}
