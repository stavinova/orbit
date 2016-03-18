// OrbitTests2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "OrbitSimulator.cpp"
using namespace std;

//Check that spaceship is not heating if speed is zero.
TEST_CASE("Calculate Aerodynamic heating", "[AerodynamicHeating]") {
	vec speedZero = {0, 0, 0};
	double T = 100;
	double result = aerodynamicHeating(T, speedZero);
	REQUIRE(result==100); 
}

//Angular velocity, result values from Maple 14
TEST_CASE("Calculate Angular Velocity", "[AngularVelocity]") {
	//all zero test
	vec tractiveForce = { 0,0,0 },
		aeroDynamicForce = { 0,0,0 },
		gravity = { 0,0,0 },
		previous = { 0,0,0 };
	Rotation rotate = { 0,0,0 };
	double quantSize = 0,
		length = 0;
	
	vec result = { 0,0,0 };
	REQUIRE(result == calculateAngularVelocity(gravity, aeroDynamicForce, tractiveForce, rotate,
		quantSize, length, previous));

	//some average values
	tractiveForce = { 100,200,300 };
	aeroDynamicForce = { 100,200,300 };
	gravity = { 100,200,300 };
	previous = { 100,200,300 };
	rotate = { 100,200,300 };
	length = 1000;
	quantSize = 100;
	result = { 150100, -149800, 50300 };
	REQUIRE(result == calculateAngularVelocity(gravity, aeroDynamicForce, tractiveForce, rotate,
		quantSize, length, previous));

	//big values (max double value C++ ~e308)
	tractiveForce = { 1e300,1e300,1e300 };
	aeroDynamicForce = { 1e300,1e300,1e300 };
	gravity = { 1e300,1e300,1e300 };
	previous = { 1e300,1e300,1e300 };
	rotate = { 1e300,1e300,1e300 };
	length = 1e300;
	quantSize = 100;
    result = { 1e300,1e300,1e300 };
	REQUIRE(result == calculateAngularVelocity(gravity, aeroDynamicForce, tractiveForce, rotate,
		quantSize, length, previous));
}

//Check the temperature at 6 km
TEST_CASE("Calculate temperature", "[temperature]") {
	double H = 6 + EarthRadius;
	double result = temperature(H);
	REQUIRE(result == 255.7); 
}

//Check the air density at 40 km
TEST_CASE("Calculate air density", "[airDensity]") {
	double H = 40 + EarthRadius;
	double result = airDensity(H);
	REQUIRE(result ==  0.004);
}

TEST_CASE("Calculate Gravity force", "[GravityForce]") {
    SECTION( "if position is the center of the Earth" ) {
        vec position = {0, 0, 0};
        double mass = 100;
        vec result = calculateGravityForce(position, mass);
        vec zeroVec = {0, 0, 0};
        REQUIRE(result == zeroVec);
    }
    SECTION( "normal values" ) {
        vec position = {1, 0, 0};
        double mass = 1;
        vec result = calculateGravityForce(position, mass);
        REQUIRE(result.x >= 398709.1466);
        REQUIRE(result.x <= 398709.1468);
    }
}

TEST_CASE("Calculate Tractive force", "[TractiveForce]") {
    SECTION( "if the speed is zero" ) {
        vec speed = {0, 0, 0};
        double massLevel = 1;
        double specificImpulse = 1;
        vec result = calculateTractiveForce(massLevel, specificImpulse, speed);
        vec zeroVec = {0, 0, 0};
        REQUIRE(result == zeroVec);
    }
    SECTION( "normal values" ) {
        vec speed = {10, 0, 0};
        double massLevel = 0.5;
        double specificImpulse = 20;
        vec result = calculateTractiveForce(massLevel, specificImpulse, speed);
        vec calculatedVec = {10, 0, 0};
        REQUIRE(result == calculatedVec);
    }
    SECTION( "calculation doesn't depend on scalar of the speed, only on it's direction)" ) {
        vec speed1 = {0, 1, 0};
        vec speed2 = {0, 10, 0};
        double massLevel = 2;
        double specificImpulse = 5;
        vec result1 = calculateTractiveForce(massLevel, specificImpulse, speed1);
        vec result2 = calculateTractiveForce(massLevel, specificImpulse, speed2);
        vec calculatedVec = {0, 10, 0};
        REQUIRE(result1 == calculatedVec);
        REQUIRE(result2 == calculatedVec);
    }
}

TEST_CASE("Calculate Aerodynamic force", "[AerodynamicForce]") {
    SECTION( "if we are too far from Earth" ) {
        vec speed = {1, 1, 1};
        double square = 2;
        double height = 100000;
        vec result = calculateAerodynamicForce (speed, square, height);
        vec zeroVec = {0, 0, 0};
        REQUIRE(result == zeroVec);
    }
    SECTION( "if we have zero speed" ) {
        vec speed = {0, 0, 0};
        double square = 2;
        double height = 6471;
        vec result = calculateAerodynamicForce (speed, square, height);
        vec zeroVec = {0, 0, 0};
        REQUIRE(result == zeroVec);
    }
}





