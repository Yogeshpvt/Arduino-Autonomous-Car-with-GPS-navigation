// Initialization of globals and functions
#include "TinyGPS++.h"
#include "SoftwareSerial.h"
#include <Wire.h>
#include <HMC5883L.h>
#include <math.h>

SoftwareSerial HM10(16, 17);        

// Car variables initialized
#define L_motors_speed 10           // controls the speed of the left motors;
#define R_motors_speed 11           // controls the speed of the right motors;     
#define L1 8                        // controls rotation direction of left motors;
#define L2 9                        // controls rotation direction of left motors;
#define R1 12                       // controls rotation direction of right motors;
#define R2 7                        // controls rotation direction of right motors;

TinyGPSPlus gps;                        // GPS object "gps" that takes in NMEA data
HMC5883L compass;                       // Compass object "compass"

bool stopTelemetry;               // Used in gpsTelemetry() functions. Breaks the infinite while loop
float latitA, lonA;               // Current Latitude/Longitude (point A)
float latitB, lonB;               // Destination Latitude/Longitude (point B)
float latitC, lonC, latitD, lonD; // Multiple destination coordinates (To be used in later versions)
float gpsAngleDegrees;            // Angle to destination B from current location // float or long
float headingDegrees;             // Compass heading angle in degrees
bool carArrived;                  // for function that checks if we've arrived at destination


int frontSent = A4;       // controls the impulse sent from the front sensor
int frontReceive = A5;    // controls the impulse received from the front sensor
int leftSent = A2;        // controls the impulse sent from the left sensor
int leftReceive = A3;     // controls the impulse received from the left sensor
int rightSent = A0;       // controls the impulse sent from the right sensor
int rightReceive = A1;    // controls the impulse received from the right sensor

long frontTime, leftTime, rightTime, frontSensor, leftSensor, rightSensor;

const uint8_t interruptPinTwo = 2;  // Digital pin 2 has an LED that will trigger ISR
volatile bool objectDetected;       // For our ISR interruptLoop() which is for objectAvoid()

void MenuFunction();			        // The main menu in loop()
void inputDestination();		      // The menu used to input GPS coordinates manually
void multipleDestinations();      // The menu used to input multiple GPS destinations manually
float stringToFloatConversion();  // Returns float int from inputted string text

void automation(float lat1, float long1, float lat2, float long2);			          // The main automation procedures of the vehicle
void obstacleAvoid(float lat1, float long1, float lat2, float long2);			        // The obstacle avoidance procedures of the vehicle
void activateObjectAvoid();		                                                    // The ISR that will allow us to go to objectAvoid()

void GPSTelemetry();			                                              // The function that updates current GPS coordinates
void GPSBearingAngle(float lat1, float long1, float lat2, float long2);	// Calculates bearing angle to destination from current GPS coordinates
float GPSDistance(float lat1, float long1, float lat2, float long2);    // returns distance between destination and current location


void compassBearingDegrees();		    // The function that updates current compass bearing


void ultrasonicCheck();			        // Stores ultrasonic data (distance) in three globals

void IsCarFacingDestination();		        // Checks if vehicle is facing destination
bool checkIfWeArrived();		              // Checks if vehicle has arrived at destination


void correctBearingTurn();		                  // Corrects vehicle bearing
void DCMotorZero();				                      // Turns off left and right motors
void goStraightShortDistance( int duration );	  // Go straight for a duration input of milliseconds
void goReverseShortDistance( int duration );	  // Go reverse for a duration input of milliseconds
void goStraightAfterObstacle( int duration ); 	// Same as first go straight function
void leftTurnTimed( int duration );		          // Turn left for a duration input of milliseconds
void rightTurnTimed( int duration );		        // Turn right for a duration input of milliseconds
void stopCar();					                        // Stops car for 100 seconds
void stopCarTimed( int duration );		          // Stops car for a duration input of milliseconds
