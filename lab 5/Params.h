/*
*
*	Params.h
*	Recompiling params for Test
*
*
*	https://github.com/jinekgames
*	no license
*
*/



#pragma once

#ifndef __PARAMS_H__
#define __PARAMS_H__



#include <Windows.h>
#include <vector>
#include <math.h>
#include "jnkMath.h"


#define PART_2


#ifdef PART_1

// Function to calcalate
DOUBLE f(DOUBLE x) {

	return
		x*x;

};


// Edges
const DOUBLE a = 0.0;
const DOUBLE b = 10.0;


// Test 1

// Number of intervals
const DOUBLE t1_n = 5u;


// Test 2

// Length of intervals
const DOUBLE t2_l = 0.25;



// Solved integral true result
const DOUBLE tru_res = 333.333333333333333333333333333333333333333333333333333333333333333333333333;

#endif // PART_1

#ifdef PART_2

// Epsilon values
const std::vector<DOUBLE> E{ 5e-4, 5e-5, 5e-6 };

// Error value by Runge
#define RUNGE_ROOL(ih, ih_2) \
	abs((ih - ih_2) / 3)

DOUBLE f1(DOUBLE x) {
	return x * x;
}
DOUBLE f2(DOUBLE x) {
	return sin(PI * x);
}

struct data2solve {
	DOUBLE(*f)(DOUBLE);
	DOUBLE a, b;
	DOUBLE precalculated;
};

// Functions with params 2 calculate
const std::vector<data2solve> functions{
	{ f1, 0.0, 1.0, 0.33333333333333333333333 },
	{ f2, 0.0, 1.0, 0.6366197723 },
};



#endif // PART_1





#endif // __PARAMS_H__
