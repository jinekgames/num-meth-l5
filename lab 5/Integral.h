/*
* 
*	Integral.h
*	Contains Integral calculation functions with function params classes
* 
*	All objests are located in Integral_jnk namespace
* 
*	To calculate the integral from A to B of function F(X)
*	u should call one of Integral(F, A, B, param) functions
*	Where param is value of namespace type
*	Choose type (e.g. INTERVAL_LEN(0.02))
*	due to param u wanna use
* 
*	Choose DEBUG build to see console debug info,
*	choose RELEASE to not
* 
* 
*	https://github.com/jinekgames
*	no license
* 
*/



#pragma once

#ifndef __INTEGRAL_H__
#define __INTEGRAL_H__



#include <Windows.h>



// Integral module namespace
namespace Integral_jnk {


// Result of Intergral functions
struct Solved_integral {
		
	// Solved integral value
	DOUBLE i;

	// Error rate
	DOUBLE del;

};


// Base big value class
class _DOUBLE_VALUE_ {

	/*
	*	Using as parent for intergral param types
	*/

public:

	DOUBLE v;

public:

	_DOUBLE_VALUE_() : v(0) {}
	_DOUBLE_VALUE_(DOUBLE value) noexcept : v(value) {}
	_DOUBLE_VALUE_(const _DOUBLE_VALUE_& _double_value_) noexcept : v(_double_value_.v) {}
	_DOUBLE_VALUE_(_DOUBLE_VALUE_&& _double_value_) noexcept : v(_double_value_.v) { _double_value_.v = 0; }
	~_DOUBLE_VALUE_() = default;

};

// Lenth of interval param
class INTERVAL_LEN : public _DOUBLE_VALUE_ {

	/*
	*	Using as intergral function param as lenth of each interval
	*/

public:

	INTERVAL_LEN() = delete;
	INTERVAL_LEN(DOUBLE value) noexcept : _DOUBLE_VALUE_(value) {}
	INTERVAL_LEN(const INTERVAL_LEN& _interval_len_) noexcept : _DOUBLE_VALUE_(_interval_len_) {}
	INTERVAL_LEN(INTERVAL_LEN&& _interval_len_) noexcept : _DOUBLE_VALUE_(_interval_len_) { _interval_len_.v = 0; }
	~INTERVAL_LEN() = default;

};

// Number of intervals param
class INTERVAL_NUM : public _DOUBLE_VALUE_ {

	/*
	*	Using as intergral function param as number of intervals to calculate
	*/

public:

	INTERVAL_NUM() = delete;
	INTERVAL_NUM(DOUBLE value) : _DOUBLE_VALUE_(value) {}
	INTERVAL_NUM(const INTERVAL_NUM& _interval_num_) noexcept : _DOUBLE_VALUE_(_interval_num_) {}
	INTERVAL_NUM(INTERVAL_NUM&& _interval_num_) noexcept : _DOUBLE_VALUE_(_interval_num_) { _interval_num_.v = 0; }
	~INTERVAL_NUM() = default;

};


// Prevent using Integral function with unsafe param
DOUBLE Integral(DOUBLE(*f)(DOUBLE), DOUBLE a, DOUBLE b, DOUBLE p) = delete;


// Calculate integral for f(DOUBLE) from a to b by trapezes with lenth p
DOUBLE Integral(DOUBLE(*f)(DOUBLE), DOUBLE a, DOUBLE b, INTERVAL_LEN p);

// Calculate integral for f(DOUBLE) from a to b by trapezes with p intervals
DOUBLE Integral(DOUBLE(*f)(DOUBLE), DOUBLE a, DOUBLE b, INTERVAL_NUM p);


}




#endif // __INTEGRAL_H__
