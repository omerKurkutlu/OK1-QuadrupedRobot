//#include "Arduino.h"
#include "Quadruped.h"
#include <stdlib.h>//
#include <math.h>

Quadruped::Quadruped(float l1,float l2){

  leg1.setLegLength(l1, l2);
  leg1.setX(0);
  leg1.setY(0);
  leg1.setZ(10);
  leg1.runKinematics();
  leg2.setLegLength(l1, l2);
  leg2.setX(0);
  leg2.setY(0);
  leg2.setZ(10);
  leg2.runKinematics();
  leg3.setLegLength(l1, l2);
  leg3.setX(0);
  leg3.setY(0);
  leg3.setZ(10);
  leg3.runKinematics();
  leg4.setLegLength(l1, l2);
  leg4.setX(0);
  leg4.setY(0);
  leg4.setZ(10);
  leg4.runKinematics();

  x_axis_walk_cycle=0;
  y_axis_walk_cycle=0;
  spin_walk_cycle=0;
  x_axis_displacement=0;
  y_axis_displacement=0;
  spin_displacement=0;
  high=3;
  total_leg_length=l1+l2;
    }
void Quadruped::setVariables(float x,float y,float roll,float pitch,float yaw,float elevation,float high,int acceX,int acceY)
{
  this->x=x;
  this->y=y;
  this->roll=roll;
  this->pitch=pitch;
  this->yaw=yaw;
  this->elevation=elevation;
  this->high=high;
  CoG_x=acceX;
  CoG_y=acceY;
}

void Quadruped::height(){
  leg1.setZ(elevation);
  leg2.setZ(elevation);
  leg3.setZ(elevation);
  leg4.setZ(elevation);
  leg1.setX(-2);    // -2 is good
  leg1.setY(0);
  leg2.setX(-2);    // -2 is good
  leg2.setY(0);
  leg3.setX(-4);    // -4 is good
  leg3.setY(0);
  leg4.setX(-4);    // -4 is good
  leg4.setY(0);  
}

void Quadruped::balance()
{
  //X-Axis
  leg1.setZ(leg1.getZ()-CoG_x);
  leg2.setZ(leg2.getZ()-CoG_x);
  leg3.setZ(leg3.getZ()+CoG_x);
  leg4.setZ(leg4.getZ()+CoG_x);

  //Y-Axis
    if(CoG_y>0)
    {
    
    }
    if(CoG_y<0)
    {
    
    }
  
}

float Quadruped::toRad(float ang)
{
  return(ang * (pi /180 ));
};


void Quadruped::pose()
{

  //compute for roll
  leg1.setZ(leg1.getZ()+roll);
  leg3.setZ(leg3.getZ()+roll);
  leg2.setZ(leg2.getZ()-roll);
  leg4.setZ(leg4.getZ()-roll);

  //compute for pitch
  leg1.setZ(leg1.getZ()-pitch);
  leg2.setZ(leg2.getZ()-pitch);
  leg3.setZ(leg3.getZ()+pitch);
  leg4.setZ(leg4.getZ()+pitch);

  //compute for yaw   "Rectangle rotation" 
  // I solve it with spin_walk_cycle in gait function 
  /*
  leg1.setX(  leg1.getX() + (leg1.getX()*(cos(toRad(yaw)))-leg1.getY()*(sin(toRad(yaw)))) );
  leg2.setX(  leg2.getX() + (leg2.getX()*(cos(toRad(yaw)))-leg2.getY()*(sin(toRad(yaw)))) );
  leg3.setX(  leg3.getX() + (leg3.getX()*(cos(toRad(yaw)))-leg3.getY()*(sin(toRad(yaw)))) );
  leg4.setX(  leg4.getX() + (leg4.getX()*(cos(toRad(yaw)))-leg4.getY()*(sin(toRad(yaw)))) );

  leg1.setY(  leg1.getY() + (leg1.getX()*(sin(toRad(yaw)))+leg1.getY()*(cos(toRad(yaw))))   );
  leg2.setY(  leg2.getY() + (leg2.getX()*(sin(toRad(yaw)))+leg2.getY()*(cos(toRad(yaw))))   );
  leg3.setY(  leg3.getY() - (leg3.getX()*(sin(toRad(yaw)))+leg3.getY()*(cos(toRad(yaw))))   );
  leg4.setY(  leg4.getY() - (leg4.getX()*(sin(toRad(yaw)))+leg4.getY()*(cos(toRad(yaw))))   );

  leg1.setZ(sqrt(leg1.getZ()*leg1.getZ()-leg1.getY()*leg1.getY()));
  leg2.setZ(sqrt(leg2.getZ()*leg2.getZ()+leg2.getY()*leg2.getY()));
  leg3.setZ(sqrt(leg3.getZ()*leg3.getZ()-leg3.getY()*leg3.getY()));    
  leg4.setZ(sqrt(leg4.getZ()*leg4.getZ()+leg4.getY()*leg4.getY()));
  */
  

  // BU Kode sonradan yazdigim pose , buna yeni joystick koyacagiz
  /* leg1.x=x;
  leg2.x=x;
  leg3.x=x;
  leg4.x=x;

  leg1.y=y;
  leg2.y=y;
  leg3.y=y;
  leg4.y=y;
*/  
 
}

void Quadruped::gait()
{

  //if(x>0 || cycle>0)   //walk forward
  if(x!=0 || x_axis_walk_cycle>0)
  {
  forwardAndBackward();  // x_axis_walk_cycle between 0-7
  }
  if(y!=0 || y_axis_walk_cycle>0)
  {
  leftwardAndRightward();  // y_axis_walk_cycle between 0-7
  }
  if(yaw!=0 || spin_walk_cycle>0)  
  {
  leftdAndRightSpin();  // spin_walk_cycle between 0-7
  }
  
}

void Quadruped::forwardAndBackward()
{
  switch(x_axis_walk_cycle)
  {
  case 0:{
    x_axis_displacement=x; // it updates only in begining of cycle and then on other cycle it is same as in the beginning
    leg1.setZ(leg1.getZ());
    leg2.setZ(leg2.getZ()-high);
    leg3.setZ(leg3.getZ()-high);
    leg4.setZ(leg4.getZ());
    x_axis_walk_cycle++;
  }break;
  case 1:{
    leg1.setX(leg1.getX()-(x_axis_displacement/2));
    leg2.setX(leg2.getX()+(x_axis_displacement/2));
    leg3.setX(leg3.getX()+(x_axis_displacement/2));
    leg4.setX(leg4.getX()-(x_axis_displacement/2));
    leg2.setZ(leg2.getZ()-high);
    leg3.setZ(leg3.getZ()-high);
    x_axis_walk_cycle++;
  }break;
  case 2:{
    leg1.setX(leg1.getX()-x_axis_displacement);
    leg2.setX(leg2.getX()+x_axis_displacement);
    leg3.setX(leg3.getX()+x_axis_displacement);
    leg4.setX(leg4.getX()-x_axis_displacement);
    x_axis_walk_cycle++;
  }break;
  case 3:{
    leg1.setX(leg1.getX()-(x_axis_displacement/2));
    leg2.setX(leg2.getX()+(x_axis_displacement/2));
    leg3.setX(leg3.getX()+(x_axis_displacement/2));
    leg4.setX(leg4.getX()-(x_axis_displacement/2));
    leg1.setZ(leg1.getZ()-(high/2));
    leg4.setZ(leg4.getZ()-(high/2));
    x_axis_walk_cycle++;
  }break;
  case 4:{
    leg1.setX(leg1.getX());
    leg2.setX(leg2.getX());
    leg3.setX(leg3.getX());
    leg4.setX(leg4.getX());
    leg1.setZ(leg1.getZ()-high);
    leg4.setZ(leg4.getZ()-high);
    x_axis_walk_cycle++;
  }break;
  case 5:{
    leg1.setX(leg1.getX()+(x_axis_displacement/2));
    leg2.setX(leg2.getX()-(x_axis_displacement/2));
    leg3.setX(leg3.getX()-(x_axis_displacement/2));
    leg4.setX(leg4.getX()+(x_axis_displacement/2));
    leg1.setZ(leg1.getZ()-high);
    leg4.setZ(leg4.getZ()-high);
    x_axis_walk_cycle++;
  }break;
  case 6:{
    leg1.setX(leg1.getX()+x_axis_displacement);
    leg2.setX(leg2.getX()-x_axis_displacement);
    leg3.setX(leg3.getX()-x_axis_displacement);
    leg4.setX(leg4.getX()+x_axis_displacement);
    x_axis_walk_cycle++;
  }break;
  case 7:{

    leg1.setX(leg1.getX()+(x_axis_displacement/2));
    leg2.setX(leg2.getX()-(x_axis_displacement/2));
    leg3.setX(leg3.getX()-(x_axis_displacement/2));
    leg4.setX(leg4.getX()+(x_axis_displacement/2));
    leg2.setZ(leg2.getZ()-(high/2));
    leg3.setZ(leg3.getZ()-(high/2));
    x_axis_walk_cycle=0;  // that means walk cycle is completed!!!
  }break;
  default:x_axis_walk_cycle=0;  break;
  }
}

void Quadruped::leftwardAndRightward()
{
  switch(y_axis_walk_cycle)
    {
    case 0:{
      y_axis_displacement=y; // it updates only in begining of cycle and then on other cycle it is same as in the beginning
      leg1.setZ(leg1.getZ());
      leg2.setZ(leg2.getZ()-high);
      leg3.setZ(leg3.getZ()-high);
      leg4.setZ(leg4.getZ());
      y_axis_walk_cycle++;
    }break;
    case 1:{
      leg1.setY(leg1.getY()-(y_axis_displacement/2));
      leg2.setY(leg2.getY()+(y_axis_displacement/2));
      leg3.setY(leg3.getY()+(y_axis_displacement/2));
      leg4.setY(leg4.getY()-(y_axis_displacement/2));
      leg2.setZ(leg2.getZ()-high);
      leg3.setZ(leg3.getZ()-high);
      y_axis_walk_cycle++;
    }break;
    case 2:{
      leg1.setY(leg1.getY()-y_axis_displacement);
      leg2.setY(leg2.getY()+y_axis_displacement);
      leg3.setY(leg3.getY()+y_axis_displacement);
      leg4.setY(leg4.getY()-y_axis_displacement);
      y_axis_walk_cycle++;
    }break;
    case 3:{
      leg1.setY(leg1.getY()-(y_axis_displacement/2));
      leg2.setY(leg2.getY()+(y_axis_displacement/2));
      leg3.setY(leg3.getY()+(y_axis_displacement/2));
      leg4.setY(leg4.getY()-(y_axis_displacement/2));
      leg1.setZ(leg1.getZ()-(high/2));
      leg4.setZ(leg4.getZ()-(high/2));
      y_axis_walk_cycle++;
    }break;
    case 4:{
      leg1.setY(leg1.getY());
      leg2.setY(leg2.getY());
      leg3.setY(leg3.getY());
      leg4.setY(leg4.getY());
      leg1.setZ(leg1.getZ()-high);
      leg4.setZ(leg4.getZ()-high);
      y_axis_walk_cycle++;
    }break;
    case 5:{
      leg1.setY(leg1.getY()+(y_axis_displacement/2));
      leg2.setY(leg2.getY()-(y_axis_displacement/2));
      leg3.setY(leg3.getY()-(y_axis_displacement/2));
      leg4.setY(leg4.getY()+(y_axis_displacement/2));
      leg1.setZ(leg1.getZ()-high);
      leg4.setZ(leg4.getZ()-high);
      y_axis_walk_cycle++;
    }break;
    case 6:{
      leg1.setY(leg1.getY()+y_axis_displacement);
      leg2.setY(leg2.getY()-y_axis_displacement);
      leg3.setY(leg3.getY()-y_axis_displacement);
      leg4.setY(leg4.getY()+y_axis_displacement);
      y_axis_walk_cycle++;
    }break;
    case 7:{

      leg1.setY(leg1.getY()+(y_axis_displacement/2));
      leg2.setY(leg2.getY()-(y_axis_displacement/2));
      leg3.setY(leg3.getY()-(y_axis_displacement/2));
      leg4.setY(leg4.getY()+(y_axis_displacement/2));
      leg2.setZ(leg2.getZ()-(high/2));
      leg3.setZ(leg3.getZ()-(high/2));
      y_axis_walk_cycle=0;  // that means walk cycle is completed!!!
    }break;
    default:y_axis_walk_cycle=0;  break;
    }
  
}

void Quadruped::leftdAndRightSpin()
{
  switch(spin_walk_cycle)
    {
    case 0:{
      spin_displacement=yaw; // it updates only in begining of cycle and then on other cycle it is same as in the beginning
      leg1.setZ(leg1.getZ());
      leg2.setZ(leg2.getZ()-high);
      leg3.setZ(leg3.getZ()-high);
      leg4.setZ(leg4.getZ());
      spin_walk_cycle++;
    }break;
    case 1:{
      leg1.setX(leg1.getX()-(spin_displacement/2));
      leg2.setX(leg2.getX()-(spin_displacement/2));
      leg3.setX(leg3.getX()+(spin_displacement/2));
      leg4.setX(leg4.getX()+(spin_displacement/2));

      leg1.setY(leg1.getY()-(spin_displacement/2));
      leg2.setY(leg2.getY()+(spin_displacement/2));
      leg3.setY(leg3.getY()-(spin_displacement/2));
      leg4.setY(leg4.getY()+(spin_displacement/2));

      leg2.setZ(leg2.getZ()-high);
      leg3.setZ(leg3.getZ()-high);      
      spin_walk_cycle++;
    }break;
    case 2:{
      leg1.setX(leg1.getX()-spin_displacement);
      leg2.setX(leg2.getX()-spin_displacement);
      leg3.setX(leg3.getX()+spin_displacement);
      leg4.setX(leg4.getX()+spin_displacement);


      leg1.setY(leg1.getY()-spin_displacement);
      leg2.setY(leg2.getY()+spin_displacement);
      leg3.setY(leg3.getY()-spin_displacement);
      leg4.setY(leg4.getY()+spin_displacement);
      spin_walk_cycle++;
    }break;
    case 3:{
      leg1.setX(leg1.getX()-(spin_displacement/2));
      leg2.setX(leg2.getX()-(spin_displacement/2));
      leg3.setX(leg3.getX()+(spin_displacement/2));
      leg4.setX(leg4.getX()+(spin_displacement/2));

      leg1.setY(leg1.getY()-(spin_displacement/2));
      leg2.setY(leg2.getY()+(spin_displacement/2));
      leg3.setY(leg3.getY()-(spin_displacement/2));
      leg4.setY(leg4.getY()+(spin_displacement/2));
      leg1.setZ(leg1.getZ()-(high/2));
      leg4.setZ(leg4.getZ()-(high/2));
      spin_walk_cycle++;
    }break;
    case 4:{
      leg1.setY(leg1.getY());
      leg2.setY(leg2.getY());
      leg3.setY(leg3.getY());
      leg4.setY(leg4.getY());
      leg1.setZ(leg1.getZ()-high);
      leg4.setZ(leg4.getZ()-high);
      spin_walk_cycle++;
    }break;
    case 5:{
      leg1.setX(leg1.getX()+(spin_displacement/2));
      leg2.setX(leg2.getX()+(spin_displacement/2));
      leg3.setX(leg3.getX()-(spin_displacement/2));
      leg4.setX(leg4.getX()-(spin_displacement/2));

      leg1.setY(leg1.getY()+(spin_displacement/2));
      leg2.setY(leg2.getY()-(spin_displacement/2));
      leg3.setY(leg3.getY()+(spin_displacement/2));
      leg4.setY(leg4.getY()-(spin_displacement/2));
      leg1.setZ(leg1.getZ()-high);
      leg4.setZ(leg4.getZ()-high);
      spin_walk_cycle++;
    }break;
    case 6:{
      leg1.setX(leg1.getX()+spin_displacement);
      leg2.setX(leg2.getX()+spin_displacement);
      leg3.setX(leg3.getX()-spin_displacement);
      leg4.setX(leg4.getX()-spin_displacement);

      leg1.setY(leg1.getY()+spin_displacement);
      leg2.setY(leg2.getY()-spin_displacement);
      leg3.setY(leg3.getY()+spin_displacement);
      leg4.setY(leg4.getY()-spin_displacement);
      spin_walk_cycle++;
    }break;
    case 7:{
      leg1.setX(leg1.getX()+(spin_displacement/2));
      leg2.setX(leg2.getX()+(spin_displacement/2));
      leg3.setX(leg3.getX()-(spin_displacement/2));
      leg4.setX(leg4.getX()-(spin_displacement/2));

      leg1.setY(leg1.getY()+(spin_displacement/2));
      leg2.setY(leg2.getY()-(spin_displacement/2));
      leg3.setY(leg3.getY()+(spin_displacement/2));
      leg4.setY(leg4.getY()-(spin_displacement/2));
      leg2.setZ(leg2.getZ()-(high/2));
      leg3.setZ(leg3.getZ()-(high/2));
      spin_walk_cycle=0;  // that means walk cycle is completed!!!
    }break;
    default:spin_walk_cycle=0;  break;
    }
  
}

void Quadruped::caution(){

  if(leg1.getZ()>total_leg_length) leg1.setZ(total_leg_length-1);  // it max shold be max l1+l2-1 for safety cunku basta x=-3 dedik
  if(leg2.getZ()>total_leg_length) leg2.setZ(total_leg_length-1);
  if(leg3.getZ()>total_leg_length) leg3.setZ(total_leg_length-1);
  if(leg4.getZ()>total_leg_length) leg4.setZ(total_leg_length-1);
  if(leg1.getZ()<1) leg1.setZ(1);
  if(leg2.getZ()<1) leg2.setZ(1);
  if(leg3.getZ()<1) leg3.setZ(1);
  if(leg4.getZ()<1) leg4.setZ(1);

  if(leg1.getX()>7) leg1.setX(7);
  if(leg2.getX()>7) leg2.setX(7);
  if(leg3.getX()>7) leg3.setX(7);
  if(leg4.getX()>7) leg4.setX(7);
  if(leg1.getX()<-7) leg1.setX(-7);
  if(leg2.getX()<-7) leg2.setX(-7);
  if(leg3.getX()<-7) leg3.setX(-7);
  if(leg4.getX()<-7) leg4.setX(-7);

  if(leg1.getY()>7) leg1.setY(7);
  if(leg2.getY()>7) leg2.setY(7);
  if(leg3.getY()>7) leg3.setY(7);
  if(leg4.getY()>7) leg4.setY(7);
  if(leg1.getY()<-7) leg1.setY(-7);
  if(leg2.getY()<-7) leg2.setY(-7);
  if(leg3.getY()<-7) leg3.setY(-7);
  if(leg4.getY()<-7) leg4.setY(-7);
  
}

void Quadruped::engine()
{
  height();
  //balance();
  pose();
  gait();
  caution();

  leg1.runKinematics();
  leg2.runKinematics();
  leg3.runKinematics();
  leg4.runKinematics();    
}

int* Quadruped::signalValues()
{
  static int s[12];
  engine();
  

  s[0]=180-abs(leg1.getElbowAngle());  // cunku kinematik dis aciyi negatif olarak hesapliyor ama bizim ic aciya ihtiyacimiz var
  s[1]=leg1.getSholderAngle()-45;
  s[2]=leg1.getHipAngle()+90;
  
  s[3]=abs(leg2.getElbowAngle() );
  s[4]=180-abs(leg2.getSholderAngle())+45;
  s[5]=leg2.getHipAngle()+90;

  s[6]=180-abs(leg3.getElbowAngle());
  s[7]=leg3.getSholderAngle()-45;
  s[8]=leg3.getHipAngle()+90;
  
  s[9]=abs(leg4.getElbowAngle());
  s[10]=180-abs(leg4.getSholderAngle())+45;
  s[11]=leg4.getHipAngle()+90;

  return s;
}
