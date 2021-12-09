/*
*
*	Integral.cpp
*	Contains defenision for Integral calculation functions
*
* 
*	https://github.com/jinekgames
*	no license
*
*/



#include "Integral.h"


#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


namespace Integral_jnk {


DOUBLE Integral(DOUBLE(*f)(DOUBLE), DOUBLE a, DOUBLE b, INTERVAL_LEN p) {

#ifdef _DEBUG
	std::cout << "Integral function start (param = interval length)" << std::endl;
#endif // _DEBUG

	// interval length
	const DOUBLE iLen = p.v;

	// integral calculated value
	DOUBLE i = 0.0;


	DOUBLE prev_x = a;
	DOUBLE cur_x = prev_x;

	while(cur_x < b) {

		cur_x = prev_x + iLen;
		i += (f(prev_x) + f(cur_x)) / 2.0;

		prev_x = cur_x;


#ifdef _DEBUG
		std::cout << "cur_x = " << prev_x << std::endl <<
			"iter I/iLen = " << i << std::endl;
#endif // _DEBUG

	}

	return i * iLen;

}


DOUBLE Integral(DOUBLE(*f)(DOUBLE), DOUBLE a, DOUBLE b, INTERVAL_NUM p) {

#ifdef _DEBUG
	std::cout << "Integral function start (param = interval number)" << std::endl;
#endif // _DEBUG


	// interval length
	const DOUBLE iLen = (b - a) / p.v;

	return Integral(f, a, b, INTERVAL_LEN(iLen));

}


}
