bool checkIfWeArrived( float checkDistance )
{
  if ( checkDistance <= 1.00 ) {  
    Serial2.println("WE ARE WITHIN 3 METERS OF THE DESTINATION! WE HAVE ARRIVED!");
    Serial2.println("Distance to exact destination: ");
    Serial2.println(checkDistance);
    carArrived = true;         
    DCMotorZero();             
    return carArrived;         
  }
  else {                  
    carArrived = false;   
    return carArrived;
  }

}
