/*
*
*	Params.h
*	Recompiling params for Test in 1 place2optimize compiling
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


#define PART_11
#define PART_3



struct data2solve {
	DOUBLE(*f)(DOUBLE);
	DOUBLE a, b;
	DOUBLE precalculated;
};



#ifdef PART_1

// Function to calcalate
DOUBLE f(DOUBLE x) {

	return
		x*x;

};


// Edges
const DOUBLE a = 0.0;
const DOUBLE b = 1.0;


// Test 1

// Number of intervals
const DOUBLE t1_n = 5u;


// Test 2

// Length of intervals
const DOUBLE t2_l = 0.25;



// Solved integral true result
const DOUBLE precalculates = 1.0 / 3.0;


// Get error value
#define GET_DELTA(res) \
	abs(res - precalculates)



#endif // PART_1

#ifdef PART_2

// Epsilon values
const std::vector<DOUBLE> E{ 5e-4, 5e-5, 5e-6 };

DOUBLE f1(DOUBLE x) {
	return x * x;
}
DOUBLE f2(DOUBLE x) {
	return sin(pi_const * x);
}
DOUBLE true_if2(DOUBLE x) {
	return -cos(pi_const * x) / pi_const;
}

// Functions with params 2 calculate
const std::vector<data2solve> functions{
	{ f1, 0.0, 1.0, 1.0/3 },
	{ f2, 0.0, 1.0, true_if2(1.0) - true_if2(0.0) },
};





#endif // PART_2

#ifdef PART_3

#define L 9

std::vector<data2solve> funcs{
	{
		[](DOUBLE x) { return L + jnkMath::degree(x - L, 7); },
		L,	L + 1,
		[](DOUBLE x) { return L*x + jnkMath::degree(x - L, 8)/8; }(L + 1) - [](DOUBLE x) { return L*x + jnkMath::degree(x - L, 8)/8; }(L)
	},
	{
		[](DOUBLE x) { return L + jnkMath::degree(x - L, 10); },
		L,	L + 4,
		[](DOUBLE x) { return L*x + jnkMath::degree(x - L, 11)/11; }(L + 4) - [](DOUBLE x) { return L*x + jnkMath::degree(x - L, 11)/11; }(L)
	},
};

std::vector<size_t> N{ 1u, 2, 3, 4, 5, 10, 100 };


#define M_MAX_DEG 4u

data2solve f3p2{
	[](DOUBLE x) { return sin(x); },
	0, 15,
	1.7596879128
};





#endif // PART_3







#endif // __PARAMS_H__
