/*
  ManVelClearpath.h - Library for interfacing with Clearpath motors using an Arduino- Version 1
  Teknic 2014 Brendan Flosenzier

  This library is free software; you can redistribute it and/or
  modify it.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

/* 
  
  A ManVelClearpath is activated by creating an instance of the ManVelClearpath class. 

  There can several instances of ManVelClearpath however each must be attached to different pins.

  The unique functions for a Manual Velocity motor are:

   ManVelClearpath - default constructor for initializing the motor

   attach() - Attachs pins to this motor, and declares them as input/outputs

   speed() - commands the given speed to the motor

   getSpeed() - returns the commanded speed

   disable() - disables the motor

   enable() - enables the motor

   readHLFB() - Returns the value of the HLFB Pin
 */
#ifndef ManVelClearpath_h
#define ManVelClearpath_h
#include "Arduino.h"
class ManVelClearpath
{
  public:
  ManVelClearpath();
  void attach(int, int);
  void attach(int, int, int);
  void attach(int, int, int, int);
  void speed(long);
  long test();
  void disable(boolean);
  void enable();
  long getSpeed();
  boolean readHLFB();

private:

uint8_t _Apin;
uint8_t _Bpin;
uint8_t _Epin;
uint8_t _Hpin;
uint8_t _apin;
uint8_t _bpin; 
 boolean _direction;
long _absSpeed;

};
#endif