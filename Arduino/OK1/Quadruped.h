#ifndef QUADRUPED_H
#define QUADRUPED_H

//#include "Arduino.h"
#include "Leg.h"

class Quadruped{

private:

    Leg leg1; //robot legs
    Leg leg2;
    Leg leg3;
    Leg leg4;

    /////////////////////////
    // remote controller data
    /////////////////////////
    float x,y; // remote controller datas
    float elevation;   // no use for now,but it is as z-axis
    float roll,pitch,yaw;  // remote controller datas
    float high;
    //int Speed;

    /////////////////////////
    //IMU datas
    /////////////////////////
    int CoG_x;   // center of gravity on x-axis
    int CoG_y;   // center of gravity on y-axis

    /////////////////////////
    //class variables
    /////////////////////////
    int x_axis_walk_cycle; //for walk cycle on x_axis
    int y_axis_walk_cycle; //for walk cycle on y_axis
    int  spin_walk_cycle; //for spining with yaw input
    float h; // height of legs from groung while walk cycle
    float x_axis_displacement;   // it is same as "x" above but it will update on every gait cycle , not on every loop
    float y_axis_displacement;
    float spin_displacement;
    double pi = 3.14159265359;
    float total_leg_length; // l1+l2
public:

    Quadruped(float l1,float l2);
    void setVariables(float x,float y,float roll,float pitch,float yaw,float elevation,float high,int acceX,int acceY);
    //void displayVariables();
    //void initialize();
    //float* runKinematics(float x_pos,float y_pos,float z_pos);
    void height();   // 1
    void pose();     //2
    void gait(); // It has 4 subfunctions forward,backward,leftward,rightward
    void forwardAndBackward(); void leftwardAndRightward(); void leftdAndRightSpin();
    void balance();
    void caution();
    void engine();    //pose + gait + transition => kinematics =>send servo angles to arduino
    int* signalValues();

    float toRad(float ang);
};

#endif
