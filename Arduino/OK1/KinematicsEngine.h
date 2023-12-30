#ifndef KINEMATICS_ENGINE_H
#define KINEMATICS_ENGINE_H

class Kinematics{
  private:
    float l1, l2;
    float x;
    float y;
    float z;
    
  public:
    float theta1;
    float theta2;
    float theta3;
    Kinematics();
    void setLegLength(float l1, float l2);
    Kinematics(float length1, float length2);
    void setToPosition(float x, float y, float z);  
    float radToDeg(float rad);     
};

#endif
