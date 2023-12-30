class myServo{
  public:
  Servo s;
  int currentAngle;
  int targetAngle;
  int startAngle;
  int offset;
  int diff;
  int absDiff;
  void setPin(int pin)
  {
    s.attach(pin);
  }
  void setOffset(int o)
  {
    offset=o;
    targetAngle=offset;
    currentAngle=offset;
    s.write(o);
  }
  void setTargetAngle(int p)
  {
    targetAngle=p;
    diff=targetAngle-currentAngle;
    absDiff=abs(diff);
  }
  void setCurrentAngle(int c)
  {
    currentAngle=c;
  }
  void setStartAngle(int s)
  {
    startAngle=s;
  }
  void servoWrite(int a)
  {
    s.write(a);
  }
};
