//
// additionalMaths.h
//
// some math functions



#include "windows.h"



#define PI 3.14159265358979323846264338327950288419716939937510



namespace jnkMath {

	INT factorial(INT arguement);
	DOUBLE degree(DOUBLE arguement, INT degree);
	DOUBLE degree(INT arguement, INT degree);
	SHORT negOneDeg(INT degree);
	USHORT DigitAfterPoINT(DOUBLE number);
	DOUBLE Grad2Rad(DOUBLE phi);

}
