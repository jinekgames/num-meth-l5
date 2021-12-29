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
#include <vector>

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
	const DOUBLE iLen = (b - a) / (p.v - 1.0);

	return IntegralSymp(f, a, b, INTERVAL_LEN(iLen));

}


struct g_weigth {
	const DOUBLE x;
	const DOUBLE c;
};

// table of weigths for Gaussian integral
struct g_weight_table {

	struct i_vec {

		std::valarray<DOUBLE> i;

	};

	std::valarray<i_vec> n;
	size_t size;

};

const g_weight_table _g_weight_table_x{

	{{
		{{
			{				  0.0	}
		}},
		{{
			{    -sqrt(3.0) / 3.0	},
			{     sqrt(3.0) / 3.0	},
		}},
		{{
			{    -sqrt(15.0) / 5.0	},
			{				   0.0	},
			{     sqrt(15.0) / 5.0	},
		}},
		{{
			{    -sqrt(525.0 + 70.0 * sqrt(30.0)) / 35.0	},
			{    -sqrt(525.0 - 70.0 * sqrt(30.0)) / 35.0	},
			{     sqrt(525.0 - 70.0 * sqrt(30.0)) / 35.0	},
			{     sqrt(525.0 + 70.0 * sqrt(30.0)) / 35.0	},
		}},
		{{
			{    -sqrt(245.0 + 14.0 * sqrt(70.0)) / 21.0	},
			{    -sqrt(245.0 - 14.0 * sqrt(70.0)) / 21.0	},
			{										 0.0	},
			{     sqrt(245.0 - 14.0 * sqrt(70.0)) / 21.0	},
			{     sqrt(245.0 + 14.0 * sqrt(70.0)) / 21.0	},
		}},
	}},

	5u

};

const std::vector< DOUBLE(*)(DOUBLE) > _g_weith_table_poly{

	[](DOUBLE x) { return 1.0; },
	[](DOUBLE x) { return x; },
	[](DOUBLE x) { return 3.0/2.0 * x*x - 1.0/2.0; },
	[](DOUBLE x) { return 5.0/2.0 * x*x*x - 3.0/2.0; },
	[](DOUBLE x) { 
		return 35.0/8.0 * x*x*x*x - 30.0/8.0 * x*x + 3.0/8.0;
		//return 2.0 * (1.0 - x*x) / (16 * p*p);
	},
	[](DOUBLE x) { return 63.0/8.0 * x*x*x*x*x - 70.0/8.0 * x*x*x + 15.0/8.0 * x; },

};



/////////////////

double diff(int n, double xk)
{
	double diff = 0;
	switch (n)
	{
	case 0:
	{
		break;
	}
	case 1:
	{
		diff = 1;
		break;
	}
	case 2:
	{
		diff = 3 * xk;
		break;
	}
	case 3:
	{
		diff = (5 * 3 * xk * xk - 3) / 2;
		break;
	}
	case 4:
	{
		diff = (35 * 4 * xk * xk * xk - 60 * xk) / 8;
		break;
	}
	case 5:
	{
		diff = (63 * 5 * xk * xk * xk * xk - 210 * xk * xk + 15) / 8;
		break;
	}
	default:
		throw "Wrong n in diff!\n";
	}
	return diff;
}

double weightk(int n, double xk)
{
	double tmp = diff(n, xk);
	return 2.0 / ((1.0 - xk * xk) * tmp * tmp);
}

double solves[5][5]{ {0,0,0,0,0},{-1.0 / sqrt(3),1.0 / sqrt(3),0,0,0},{-sqrt(0.6),0,sqrt(0.6),0,0},{-sqrt(3.0 / 7 + 2 * sqrt(1.2) / 7),-sqrt(3.0 / 7 - 2 * sqrt(1.2) / 7),sqrt(3.0 / 7 - 2 * sqrt(1.2) / 7),sqrt(3.0 / 7 + 2 * sqrt(1.2) / 7),0},{-sqrt(5 + 2 * sqrt(10.0 / 7)) / 3,-sqrt(5 - 2 * sqrt(10.0 / 7)) / 3,0,sqrt(5 - 2 * sqrt(10.0 / 7)) / 3,sqrt(5 + 2 * sqrt(10.0 / 7)) / 3} };

/////////////////



g_weigth s_GetGweigth(size_t n, size_t i) {

	if (n > _g_weight_table_x.size) {
		throw "Integral.cpp Integral_jnk::g_weigth Integral_jnk::s_GetGweigth(size_t, size_t) error: i > table size";
	}
	if (i > n) {
		throw "Integral.cpp Integral_jnk::g_weigth Integral_jnk::s_GetGweigth(size_t, size_t) error: i > n limit";
	}

	return {
		_g_weight_table_x.n[n - 1].i[i - 1],
		weightk(n, solves[n-1][i-1])
	};


	//if (n < 4) {
	//	return {
	//		weigth_x,
	//		2.0 * (1.0 - weigth_x * weigth_x) / (n * n * jnkMath::degree(_g_weith_table_poly[n - 1](weigth_x), 2))
	//	};
	//}
	//
	//{
	//	if (n == 4) {
	//		if (i == 1 || i == 4) return { weigth_x, 0.3478548451 };
	//		else			 return { weigth_x, 0.6521451559 };
	//	}
	//	if (n == 5) {
	//		if (i == 1 || i == 5) return { weigth_x, 0.2369268851 };
	//		if (i == 2 || i == 4) return { weigth_x, 0.4786286705 };
	//		else			 return { weigth_x, 0.568888888888889 };
	//	}
	//}

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


//#include <iostream>
//#include "conio.h"
//using namespace std;
//using namespace Integral_jnk;
//void main() {
//
//	for (size_t i = 1u; i <= 5u; i++) {
//
//		for (size_t j = 1u; j <= i; j++) {
//
//			auto t = s_GetGweigth(i, j);
//
//			cout << t.c << "\t" << t.x << endl;
//
//		}
//		
//		cout << endl;
//
//	}
//
//	_getch();
//
//}
