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




#endif // __PARAMS_H__
