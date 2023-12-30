#include "KinematicsEngine.h"
#include <math.h>

Kinematics::Kinematics(){
	l1 = 10;
	l2 = 10;

	theta1 = 90;
	theta2 = -90;
	theta3 = 0;

	x = 10;
	y = 0;
	z = 10;

}


Kinematics::Kinematics(float length1, float length2){
  l1 = length1;
  l2 = length2;

  theta1 = 90;
  theta2 = -90;
  theta3 = 0;

  x = length2;
  y = 0;
  z = length1;
}

void Kinematics::setLegLength(float l1, float l2)
{
	this->l1=l1;
	this->l2=l2;
}

void Kinematics::setToPosition(float x, float y, float z){
  this->x=x;
  this->y=y;
  this->z=z;
  
  float r1 = sqrt(pow(z, 2) + pow(y, 2));
  float r2 = sqrt(pow(r1, 2) + pow(x, 2));
  
  if(x>=0 &&z>=0)    // 1st  quadrant 
  {
    theta3 = radToDeg(atan(y/z));
    theta2 = 180-radToDeg(acos((pow(r2, 2) - pow(l1, 2) - pow(l2, 2))/(-2 * l1 * l2)));
    theta1 = radToDeg(atan(r1/x) ) + radToDeg(acos( ( pow(l2,2) - pow(l1,2) - pow(r2,2) ) / (-2*l1*r2)))   ;
  }
  if(x>=0 && z<0)   // 4th  quadrant 
  {
    theta3 = radToDeg(atan(y/z));
    theta2 = 180-radToDeg(acos((pow(r2, 2) - pow(l1, 2) - pow(l2, 2))/(-2 * l1 * l2)));
    theta1 = radToDeg(atan(r1/x) ) - radToDeg(acos( ( pow(l2,2) - pow(l1,2) - pow(r2,2) ) / (-2*l1*r2)))   ;
  }
  if(x<0 && z<=0)   // 3th  quadrant 
  {
    x = sqrt(pow(x, 2));
    z = sqrt(pow(z, 2));
    
    theta3 = radToDeg(atan(y/z));
    theta2 = 180-radToDeg(acos((pow(r2, 2) - pow(l1, 2) - pow(l2, 2))/(-2 * l1 * l2)));
    theta1 = -90-( radToDeg(atan(x/r1) ) - radToDeg(acos( ( pow(l2,2) - pow(l1,2) - pow(r2,2) ) / (-2*l1*r2))) )  ;
  }
  if(x<=0 && z>0)   // 2th  quadrant 
  {
    x = sqrt(pow(x, 2));
    z = sqrt(pow(z, 2));
    
    theta3 = radToDeg(atan(y/z));
    theta2 = 180-radToDeg(acos((pow(r2, 2) - pow(l1, 2) - pow(l2, 2))/(-2 * l1 * l2)));
    theta1 = 90+( radToDeg(atan(x/r1) ) + radToDeg(acos( ( pow(l2,2) - pow(l1,2) - pow(r2,2) ) / (-2*l1*r2))) )  ;
  }
}

float Kinematics::radToDeg(float rad)
{
  double pi = 3.14159;
  return(rad * (180 / pi));
}
