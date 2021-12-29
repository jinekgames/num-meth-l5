//
// additionalMaths.h
//
// some math functions

#pragma once

#ifndef __JNKMATH_H__
#define __JNKMATH_H__



#include <windows.h>
#include <math.h>


#define PI_CONST \
	acos(-1)

const DOUBLE pi_const = acos(-1);

#define E_CONST	\
	exp(1)

const DOUBLE e_const = exp(1);


namespace jnkMath {

	INT factorial(INT arguement);
	DOUBLE degree(DOUBLE arguement, INT degree);
	DOUBLE degree(INT arguement, INT degree);
	SHORT negOneDeg(INT degree);
	USHORT DigitAfterPoINT(DOUBLE number);
	DOUBLE Grad2Rad(DOUBLE phi);

}



#endif // __JNKMATH_H__