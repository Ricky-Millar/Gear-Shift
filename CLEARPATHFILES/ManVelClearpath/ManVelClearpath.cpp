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
#include "Arduino.h"
#include "ManVelClearpath.h"


/*		
	This is the default constructor.  This intializes the variables.
*/
ManVelClearpath::ManVelClearpath()
{
  _Apin=0;
  _Bpin=0;
  _Epin=0;
  _Hpin=0;
  _absSpeed=0;
}

/*		
	This is the two pin attach function.  
	It asociates the 1st number, as this motors Direction Pin
	and the 2nd number with the Step Pin
*/
void ManVelClearpath::attach(int APin, int BPin)
{
  _Apin=APin;
  _Bpin=BPin;
  _Epin=0;
  _Hpin=0;
  _absSpeed=0;
  if(_Apin-8 > 0)
	_apin=1<<(_Apin-8);
  if(_Bpin-8 > 0)
	_bpin=1<<(_Bpin-8);
  if(_Apin < 8)
	_apin=1<<(_Apin);
  if(_Bpin < 8)
	_bpin=1<<(_Bpin);
  pinMode(_Apin,OUTPUT);
  pinMode(_Bpin,OUTPUT);
  digitalWrite(_Apin,LOW);
  digitalWrite(_Bpin,LOW);
}

/*		
	This is the three pin attach function.  
	It asociates the 1st number, as this motors Direction Pin,
	the 2nd number with the Step Pin,
	and the 3rd number with the Enable Pin
*/
void ManVelClearpath::attach(int APin, int BPin, int EPin)
{
  _Apin=APin;
  _Bpin=BPin;
  _Epin=EPin;
  _Hpin=0;
  _absSpeed=0;
  if(_Apin-8 >= 0)
	_apin=1<<(_Apin-8);
  if(_Bpin-8 >= 0)
	_bpin=1<<(_Bpin-8);
  if(_Apin < 8)
	_apin=1<<(_Apin);
  if(_Bpin < 8)
	_bpin=1<<(_Bpin);
  pinMode(_Apin,OUTPUT);
  pinMode(_Bpin,OUTPUT);
  pinMode(_Epin,OUTPUT);
  digitalWrite(_Apin,LOW);
  digitalWrite(_Bpin,LOW);
}

/*		
	This is the four pin attach function.  
	It asociates the 1st number, as this motors Direction Pin,
	the 2nd number with the Step Pin,
	the 3rd number with the Enable Pin,
	and the 4th number as the HLFB Pin
*/
void ManVelClearpath::attach(int APin, int BPin, int EPin, int HPin)
{
  _Apin=APin;
  _Bpin=BPin;
  _Epin=EPin;
  _Hpin=HPin;
  _absSpeed=0;
  if(_Apin-8 >= 0)
	_apin=1<<(_Apin-8);
  if(_Bpin-8 >= 0)
	_bpin=1<<(_Bpin-8);
  if(_Apin < 8)
	_apin=1<<(_Apin);
  if(_Bpin < 8)
	_bpin=1<<(_Bpin);
  pinMode(_Apin,OUTPUT);
  pinMode(_Bpin,OUTPUT);
  pinMode(_Epin,OUTPUT);
  pinMode(_Hpin,INPUT_PULLUP);
  digitalWrite(_Apin,LOW);
  digitalWrite(_Bpin,LOW);
}

/*		
	This function commands a directional velocity in terms of the resolution in MSP

	This function may take longer to service with larger velocitys
*/
void ManVelClearpath::speed(long dist)
{
	cli();
  if(_Apin < 8 && _Bpin < 8)
  {
	  int OutputBits=PORTD;
  
	  if(_absSpeed<dist)
	  {
		  while(dist!=_absSpeed)
  {
		  OutputBits |= _apin;
		  PORTD=OutputBits;
		  delayMicroseconds(1);
		  OutputBits |= _bpin;
		  PORTD=OutputBits;
		  delayMicroseconds(1);
		  OutputBits &=63-_apin;
		  PORTD=OutputBits;
		  delayMicroseconds(1);
		  OutputBits &=63-_bpin;
		  PORTD=OutputBits;
		  delayMicroseconds(1);
		  _absSpeed++;
	  }
	  }
	  else
	  {
		  while(dist!=_absSpeed)
  {
		  OutputBits |= _bpin;
		  PORTD=OutputBits;
		  delayMicroseconds(1);
		  OutputBits |= _apin;
		  PORTD=OutputBits;
		  delayMicroseconds(1);
		  OutputBits &=63-_bpin;
		  PORTD=OutputBits;
		  delayMicroseconds(1);
		  OutputBits &=63-_apin;
		  PORTD=OutputBits;
		  delayMicroseconds(1);

		  _absSpeed--;
	  }
	  }
  }
  if(_Apin-8 >= 0 && _Bpin-8 >= 0)
  {
	  int OutputBits=PORTB;
	  if(_absSpeed<dist)
	  {
		  while(dist!=_absSpeed)
  {
		  OutputBits |= _apin;
		  PORTB=OutputBits;
		  delayMicroseconds(1);
		  OutputBits |= _bpin;
		  PORTB=OutputBits;
		  delayMicroseconds(1);
		  OutputBits &=63-_apin;
		  PORTB=OutputBits;
		  delayMicroseconds(1);
		  OutputBits &=63-_bpin;
		  PORTB=OutputBits;
		  delayMicroseconds(1);
		  _absSpeed++;
		  }}
	  else
	  {
		  while(dist!=_absSpeed)
  {
		  OutputBits |= _bpin;
		  PORTB=OutputBits;
		  delayMicroseconds(1);
		  OutputBits |= _apin;
		  PORTB=OutputBits;
		  delayMicroseconds(1);
		  OutputBits &=63-_bpin;
		  PORTB=OutputBits;
		  delayMicroseconds(1);
		  OutputBits &=63-_apin;
		  PORTB=OutputBits;
		  delayMicroseconds(1);
		  _absSpeed--;
		  }
	  }
  }
  if(_Apin-8 >= 0 && _Bpin <8)
  {
	  int OutputBitsA=PORTB;
	  int OutputBitsB=PORTD;
	  if(_absSpeed<dist)
	  {
		  while(dist!=_absSpeed)
  {
		  OutputBitsA |= _apin;
		  PORTB=OutputBitsA;
		  delayMicroseconds(1);
		  OutputBitsB |= _bpin;
		  PORTD=OutputBitsB;
		  delayMicroseconds(1);
		  OutputBitsA &=63-_apin;
		  PORTB=OutputBitsA;
		  delayMicroseconds(1);
		  OutputBitsB &=63-_bpin;
		  PORTD=OutputBitsB;
		  delayMicroseconds(1);
		  _absSpeed++;
		  }
	  }
	  else
	  {
		  while(dist!=_absSpeed)
  {
		  OutputBitsB |= _bpin;
		  PORTD=OutputBitsB;
		  delayMicroseconds(1);
		  OutputBitsA |= _apin;
		  PORTB=OutputBitsA;
		  delayMicroseconds(1);
		  OutputBitsB &=63-_bpin;
		  PORTD=OutputBitsB;
		  delayMicroseconds(1);
		  OutputBitsA &=63-_apin;
		  PORTB=OutputBitsA;
		  delayMicroseconds(1);
		  _absSpeed--;
		  }
	  }
  }
  if(_Apin < 8 && _Bpin-8 >= 0)
  {
	  int OutputBitsA=PORTD;
	  int OutputBitsB=PORTB;
	  if(_absSpeed<dist)
	  {
		  while(dist!=_absSpeed)
  {
		  OutputBitsA |= _apin;
		  PORTD=OutputBitsA;
		  delayMicroseconds(1);
		  OutputBitsB |= _bpin;
		  PORTB=OutputBitsB;
		  delayMicroseconds(1);
		  OutputBitsA &=63-_apin;
		  PORTD=OutputBitsA;
		  delayMicroseconds(1);
		  OutputBitsB &=63-_bpin;
		  PORTB=OutputBitsB;
		  delayMicroseconds(1);
		  _absSpeed++;
		  }
	  }
	  else
	  {
		   while(dist!=_absSpeed)
  {
		  OutputBitsB |= _bpin;
		  PORTB=OutputBitsB;
		  delayMicroseconds(1);
		  OutputBitsA |= _apin;
		  PORTD=OutputBitsA;
		  delayMicroseconds(1);
		  OutputBitsB &=63-_bpin;
		  PORTB=OutputBitsB;
		  delayMicroseconds(1);
		  OutputBitsA &=63-_apin;
		  PORTD=OutputBitsA;
		  delayMicroseconds(1);
		  _absSpeed--;
		   }
	  }
  }
  
  sei();
}

/*		
	This function is a debugging function
*/
long ManVelClearpath::test()
{
	return _Apin;
}

/*		
	This function disable the motor
*/
void ManVelClearpath::disable(boolean RememberSpeed)
{

	if(_Epin!=0)
		digitalWrite(_Epin,LOW);
	if(!RememberSpeed)
		_absSpeed=0;
}

/*		
	This function enables the motor
*/
void ManVelClearpath::enable()
{

	if(_Epin!=0)
		digitalWrite(_Epin,HIGH);

}

/*		
	This function returns the commanded velocity in terms of the resolution in MSP
*/
long ManVelClearpath::getSpeed()
{
		return _absSpeed;
}

/*		
	This function returns the value of the HLFB Pin
*/
boolean ManVelClearpath::readHLFB()
{
	if(_Epin!=0)
		return digitalRead(_Hpin);
	else
		return false;
}
