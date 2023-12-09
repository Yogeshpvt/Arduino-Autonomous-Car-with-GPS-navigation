void inputDestination() {      

  char d;
  bool Quit = true;

  while ( Quit == true ) {
    Serial2.println("Destination Menu");
    Serial2.println("Please input a destination (latitude, longitude) when prompted.");
    Serial2.println("Warning: Coordinate will be off by a very small amount due to Arduino limitations with float precision");
    delay(5000);
    Serial2.println("Input your latitude coordinate: ");
    latitB = stringToFloatConversion();
    Serial2.println("Input your longitude coordinate: ");
    lonB = stringToFloatConversion();
    Serial2.println("Your destination coordinate is: ");
    Serial2.print("Latitude: ");
    Serial2.println(latitB, 6);
    Serial2.print("Longitude: ");
    Serial2.println(lonB, 6);

    Serial2.println("Is this destination correct?   'y': yes   'n': no   ");
    while (Serial2.available() == 0) {}                                       
    d = Serial2.read();
    if (d == 'y') {                                                        
      Serial2.println("Destination confirmed. Proceeding to main menu.");
      Quit = false;                                                           
    }                                                                         
    else if (d == 'n') {                                                     
      Serial2.println("Destination not confirmed. Going back to Destination menu");
    }
    else {
      Serial2.println("Destination isn't clear. Going back to Destination menu");
    }

  }

}