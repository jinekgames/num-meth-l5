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



#include <valarray>

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


struct g_weigth {
	const DOUBLE x;
	const DOUBLE c;
};

// table of weigths for Gaussian integral
struct g_weight_table {

	struct i_vec {

		const std::valarray<g_weigth> i;

	};

	const std::valarray<i_vec> n;
	const size_t size;

};

const g_weight_table _g_weight_table{

	{{
		{{
			{    0.0,            2.0           }
		}},
		{{
			{    -0.5773503,     1.0           },
			{    0.5773503,      1.0           },
		}},
		{{
			{    -0.7745967,     0.5555556     },
			{    0.0,            0.8888889     },
			{    0.7745967,      0.5555556     },
		}},
		{{
			{    -0.8611363,     0.3478548     },
			{    -0.3399810,     0.6521451     },
			{    0.3399810,      0.6521451     },
			{    0.8611363,      0.3478548     },
		}},
		{{
			{    -0.9061798,     0.4786287     },
			{    -0.5384693,     0.2369269     },
			{    0.0,            0.5688888     },
			{    0.5384693,      0.2369269     },
			{    0.9061798,      0.4786287     },
		}},
		{{
			{    -0.9324700,     0.1713245     },
			{    -0.6612094,     0.3607616     },
			{    -0.2386142,     0.4679140     },
			{    0.2386142,      0.4679140     },
			{    0.6612094,      0.3607616     },
			{    0.9324700,      0.1713245     },
		}},
	}},

	6u

};

g_weigth _GetGweigth(size_t n, size_t i) {

	return _g_weight_table.n[n].i[i];

}
g_weigth s_GetGweigth(size_t n, size_t i) {

	if (n >= _g_weight_table.size) {
		throw "Integral.cpp Integral_jnk::g_weigth Integral_jnk::s_GetGweigth(size_t, size_t) error: i > table size";
	}
	if (i > n) {
		throw "Integral.cpp Integral_jnk::g_weigth Integral_jnk::s_GetGweigth(size_t, size_t) error: i > n limit";
	}
	return _g_weight_table.n[n-1].i[i-1];

}


DOUBLE IntegralGaus(DOUBLE(*f)(DOUBLE), DOUBLE a, DOUBLE b, INTERVAL_NUM p) {

#ifdef _DEBUG
	std::cout << "Integral Gaussian function start (param = interval number)" << std::endl;
#endif // _DEBUG

	size_t iNum = p.v;

	const DOUBLE A = (b - a) / 2.0;
	const DOUBLE B = (b + a) / 2.0;

	// integral calculated value
	DOUBLE i = 0.0;


	for (size_t index = 1u; index <= iNum; index++) {

		auto w = s_GetGweigth(iNum, index);
		auto X = B + A * w.x;

		i += w.c * f(X);


#ifdef DEEP_DEBUG
		std::cout << "cur_n = " << index << std::endl <<
			"iter I/iLen = " << i << std::endl;
#endif // DEEP_DEBUG

	}

	return i * A;

}


//DOUBLE IntegralGauM(DOUBLE(*f)(DOUBLE), DOUBLE a, DOUBLE b, INTERVAL_LEN p) {
//
//#ifdef _DEBUG
//	std::cout << "Integral Gaussian composite function start (param = interval length)" << std::endl;
//#endif // _DEBUG
//
//	// interval length
//	const DOUBLE iLen = p.v;
//
//	// integral calculated value
//	DOUBLE i = 0.0;
//
//
//	for (; a <= b; a += iLen) {
//
//		i += IntegralGaus(f, a, a + iLen, INTERVAL_NUM(_g_weight_table.size-1));
//
//	}
//
//	return i * iLen;
//
//}


//DOUBLE IntegralGauM(DOUBLE(*f)(DOUBLE), DOUBLE a, DOUBLE b, INTERVAL_NUM p) {
//
//#ifdef _DEBUG
//	std::cout << "Integral Gaussian composite function start (param = interval number)" << std::endl;
//#endif // _DEBUG
//
//
//	// interval length
//	const DOUBLE iLen = (b - a) / p.v;
//
//	return IntegralGauM(f, a, b, INTERVAL_LEN(iLen));
//
//}



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

	//case integral_formula::GAUSS_MAX: {
	//	return IntegralGauM(f, a, b, p);
	//} break;

	default : {
		throw UnexpectedIntegralFunction("non - existent intergral formula (check last param)");
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
		throw UnexpectedIntegralFunction{ "Gaussian type of integral couldn't be calculated using interval legth param" };
	} break;

	//case integral_formula::GAUSS_MAX: {
	//	return IntegralGauM(f, a, b, p);
	//} break;

	default: {
		throw UnexpectedIntegralFunction("non - existent intergral formula (check last param)");
	}

	}

}

DOUBLE Integral(DOUBLE(*f)(DOUBLE), DOUBLE a, DOUBLE b, GAUSS_PARAM p, integral_formula v) {

	if (v != integral_formula::GAUSS) {
		throw UnexpectedIntegralFunction("non - existent intergral formula (check last param)");
	}


	const ULONG i_num = p.i_num.v;
	const DOUBLE i_len = (b - a) / i_num;
	const ULONG d_num = p.d_num.v;

	DOUBLE A = a;
	DOUBLE B = A + i_len;

	// final integral value
	DOUBLE i = 0.0;

	for (; B <= b; A = B, B += i_len) {

		i += IntegralGaus(f, A, B, p.d_num);

	}

	return i;

}



}
