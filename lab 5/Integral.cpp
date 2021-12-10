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



DOUBLE IntegralTrap(DOUBLE(*f)(DOUBLE), DOUBLE a, DOUBLE b, INTERVAL_LEN p) {

#ifdef _DEBUG
	std::cout << "Integral Trapeze function start (param = interval length)" << std::endl;
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


#ifdef DEEP_DEBUG
		std::cout << "cur_x = " << prev_x << std::endl <<
			"iter I/iLen = " << i << std::endl;
#endif // DEEP_DEBUG

	}

	return i * iLen;

}


DOUBLE IntegralTrap(DOUBLE(*f)(DOUBLE), DOUBLE a, DOUBLE b, INTERVAL_NUM p) {

#ifdef _DEBUG
	std::cout << "Integral Trapeze function start (param = interval number)" << std::endl;
#endif // _DEBUG


	// interval length
	const DOUBLE iLen = (b - a) / p.v;

	return IntegralTrap(f, a, b, INTERVAL_LEN(iLen));

}


DOUBLE IntegralSymp(DOUBLE(*f)(DOUBLE), DOUBLE a, DOUBLE b, INTERVAL_LEN p) {

#ifdef _DEBUG
	std::cout << "Integral Sympson function start (param = interval length)" << std::endl;
#endif // _DEBUG

	// interval length
	const DOUBLE iLen = p.v;

	// integral calculated value
	DOUBLE i = 0.0;


	DOUBLE prev_x = a;
	DOUBLE cur_x = a + iLen;
	DOUBLE next_x = a + iLen + iLen;

	while (next_x <= b) {

		i += f(prev_x) + 4*f(cur_x) + f(next_x);

		prev_x = next_x;
		cur_x += iLen + iLen;
		next_x += iLen + iLen;


#ifdef DEEP_DEBUG
		std::cout << "cur_x = " << prev_x << std::endl <<
			"iter I/iLen = " << i << std::endl;
#endif // DEEP_DEBUG

	}

	return i * iLen / 3.0;

}


DOUBLE IntegralSymp(DOUBLE(*f)(DOUBLE), DOUBLE a, DOUBLE b, INTERVAL_NUM p) {

#ifdef _DEBUG
	std::cout << "Integral Sympson function start (param = interval number)" << std::endl;
#endif // _DEBUG

	// interval length
	const DOUBLE iLen = (b - a) / p.v;

	return IntegralSymp(f, a, b, INTERVAL_LEN(iLen));

}



DOUBLE Integral(DOUBLE(*f)(DOUBLE), DOUBLE a, DOUBLE b, INTERVAL_NUM p, integral_formula v) {

	switch (v) {

	case integral_formula::TRAPEZE: {
		return IntegralTrap(f, a, b, p);
	} break;

	case integral_formula::SYMPSON: {
		return IntegralSymp(f, a, b, p);
	} break;

	case integral_formula::GAUSS: {
		return IntegralGaus(f, a, b, p);
	} break;

	default : {
		throw UnexpectedIntegralFunction{"non - existent intergral formula (check last param)"};
	}
	
	}

}

DOUBLE Integral(DOUBLE(*f)(DOUBLE), DOUBLE a, DOUBLE b, INTERVAL_LEN p, integral_formula v) {

	switch (v) {

	case integral_formula::TRAPEZE: {
		return IntegralTrap(f, a, b, p);
	} break;

	case integral_formula::SYMPSON: {
		return IntegralSymp(f, a, b, p);
	} break;

	case integral_formula::GAUSS: {
		throw UnexpectedIntegralFunction{"Gaussian type of integral couldn;t be calculated using interval legth param"};
	} break;

	default: {
		throw UnexpectedIntegralFunction{"non - existent intergral formula (check last param)"};
	}

	}

}



}
