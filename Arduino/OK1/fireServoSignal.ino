void fireServoSignal(int cycle[])
{
    int maxDiff=0;
        
    for(int i=0;i<12;i++)                // set the target angles
    {
      s[i].setTargetAngle(cycle[i]);
    }
    
     
    for(int i=0;i<12;i++)                             // find the time interval 
    {
      if(s[i].absDiff>maxDiff)  maxDiff=s[i].absDiff;
    }
   // Serial.println(maxDiff);

  int angles[12];             // we store current angle in different variable
  for(int i=0;i<12;i++)
  {
    angles[i]=s[i].currentAngle;   
  }
  
   for(int i=0;i<maxDiff;i++)   // write the servo values as sweep in maxDiff millisec * delay()
   {
    for(int j=0;j<12;j++)
    {
        if(s[j].diff<0) //if diff is -ve
        {
          angles[j]= s[j].currentAngle-( ( (i*s[j].absDiff)/maxDiff  )+1 );     
        }
        
        if(s[j].diff>0)// if diff is +ve
        {
          angles[j]= s[j].currentAngle+( ( (i*s[j].absDiff)/maxDiff  ) +1 );  
        }
        s[j].servoWrite( angles[j] );
        //  Serial.print("Servo ");Serial.print(j+1);Serial.print(" position=");Serial.println(angles[j]);      
    }
    // Serial.println("////////////////////////////////////////////// ");
    delay(delayForServos);
   }

  for(int i=0;i<12;i++)
  {
    s[i].currentAngle=angles[i];   
  }
   
 // delay(5000);
/*  for(int i=0;i<12;i++)
  {
    Serial.print("Servo ");Serial.print(i);Serial.print(" curr=");Serial.println(s[i].currAngle);
    Serial.print("Servo ");Serial.print(i);Serial.print(" Target=");Serial.println(s[i].targetAngle);
    Serial.print("Servo ");Serial.print(i);Serial.print(" diff=");Serial.println(s[i].diff);
  }
  delay(5000);
*/
   
}
