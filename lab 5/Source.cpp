/*
*
*	Main.cpp
*	Test of Integral module
* 
*	To change params please open Params.h
*	Also U ARE TO set which of 3 parts of test to run
*	e.g.	> #define PART_2
*	it had already beed defined in the header right after includes
*	just need to writhe number
*	U can also define every of 3 PARTs to run 3 test at once
* 
*	Please read Integral.h description to understand ho library api work
*	(recommend to choose RELEASE solution property)
*
* 
*	https://github.com/jinekgames
*	no license
*
*/



#include <Windows.h>
#include "conio.h"

#include <iostream>
#include <vector>

#include <math.h>

#include "Integral.h"

#include "Params.h"



using namespace Integral_jnk;



int main() {


	//std::cout << Integral(
	//	[](DOUBLE x) { return x * x * x; },
	//	0, 10,
	//	INTERVAL_NUM(1000),
	//	SYMPSON
	//) << std::endl;


#ifdef PART_1

	// std::cout << Integral(f, 1, 2, INTERVAL_NUM(1)) << std::endl;



	std::cout << "Intergal calculation using trapeze meth\n" <<
		"Correct precalculated value\n I = " << precalculates <<
		"\n\n\n";


	std::cout << "Test 1\n\n";

	std::vector<DOUBLE> t1_res;

	size_t k = t1_n;
	for (size_t index = 0u; index < 4; index++) {
		const auto i = Integral(f, a, b, INTERVAL_NUM(k), TRAPEZE);
		t1_res.push_back(i);
		std::cout << " Ih (" << k << ") = " << i << "\n";
		std::cout << "  \t\terror: " << GET_DELTA(i) << "\n";
		k *= 2u;
	}

	std::cout << "\n\n\n";



	std::cout << "Test 2\n\n";

	const auto t2_res1 = Integral(f, a, b, INTERVAL_LEN(t2_l), TRAPEZE);
	std::cout << " Ih (" << t2_l << ") = " << t2_res1 << "\n";
	std::cout << "  \t\terror: " << GET_DELTA(t2_res1);

	const auto t2_res2 = Integral(f, a, b, INTERVAL_LEN(t2_l / 2), TRAPEZE);
	std::cout << "\n Ih (" << t2_l / 2 << ") = " << t2_res2 << "\n";
	std::cout << "  \t\terror: " << GET_DELTA(t2_res2);

	const DOUBLE del = t2_l / 2;
	const auto t2_res3 = Integral(f, a + del, b - del, INTERVAL_LEN(t2_l), TRAPEZE);
	const auto t2_resf = (t2_res2 + t2_res2) / 2;
	std::cout << "\n Ih (calculated from 2 iterations) = " << t2_resf << "\n";
	std::cout << "  \t\terror: " << GET_DELTA(t2_resf);

	std::cout << "\n\n\n";


#endif // PART_1

#ifdef PART_2

	std::cout << "-----Trapeze formula------\n\n\n";

	for (const auto& function : functions) {
		std::cout << "\tnext function\n\n";
		for (auto eps : E) {

			ULONG n = 1u;
			auto cur_i = Integral(function.f, function.a, function.b, INTERVAL_NUM(n), TRAPEZE);
			DOUBLE del;
			while (TRUE) {
				DOUBLE shift = (function.a - function.b) / n / 2;
				auto next_i = (Integral(function.f, function.a + shift, function.b - shift, INTERVAL_NUM(n), TRAPEZE) + cur_i) / 2;
				n *= 2u;
				del = RUNGE_ROOL(cur_i, next_i);
				if (del < eps) {
					cur_i = next_i;
					break;
				}
				cur_i = next_i;
			}

			std::cout << "E = " << eps << std::endl;
			std::cout << " I = " << function.precalculated << std::endl;
			std::cout << " Ih = " << cur_i << std::endl;
			std::cout << " del = " << del << std::endl;
			std::cout << " n = " << n << std::endl << std::endl;

		}
		std::cout << std::endl << std::endl;
	}


	std::cout << "\n\n-----Sympson formula------\n\n\n";

	for (const auto& function : functions) {
		std::cout << "\tnext function\n\n";
		for (auto eps : E) {

			ULONG n = 3u;
			auto cur_i = Integral(function.f, function.a, function.b, INTERVAL_NUM(n), SYMPSON);
			DOUBLE del;
			while (TRUE) {
				n *= 2u;
				auto next_i = Integral(function.f, function.a, function.b, INTERVAL_NUM(n), SYMPSON);
				del = RUNGE_ROOL(cur_i, next_i);
				if (del < eps) {
					cur_i = next_i;
					break;
				}
				cur_i = next_i;
	}

			std::cout << "E = " << eps << std::endl;
			std::cout << " I = " << function.precalculated << std::endl;
			std::cout << " Ih = " << cur_i << std::endl;
			std::cout << " del = " << del << std::endl;
			std::cout << " n = " << n << std::endl << std::endl;

}
		std::cout << std::endl << std::endl;
	}


#endif // PART_2

#ifdef PART_3


	std::cout << "\n\n-----Gaussian formula------\n\n\n";

	for (const auto& function : funcs) {
		std::cout << "\tnext function\n\n";
		for (auto n : N) {

			auto i = Integral(function.f, function.a, function.b, INTERVAL_NUM(n), GAUSS);

			std::cout << "n = " << n << std::endl;
			std::cout << " I = " << function.precalculated << std::endl;
			std::cout << " Ih = " << i << std::endl;
			std::cout << " del = " << abs(function.precalculated - i) << std::endl;

		}
		std::cout << std::endl << std::endl;
	}


	std::cout << "\n\n-Gaussian composite formula-\n\n\n";

	std::cout << "\tnext function\n\n";
	DOUBLE m = 1.0;
	DOUBLE prev_i = 0.0;
	for (auto deg = 0u; deg <= M_MAX_DEG; deg++) {

		auto i = Integral(f3p2.f, f3p2.a, f3p2.b, INTERVAL_NUM(m), GAUSS_MAX);

		std::cout << "m = " << m << std::endl;
		std::cout << " I = " << f3p2.precalculated << std::endl;
		std::cout << " Ih = " << i << std::endl;
		std::cout << " del = " << abs(f3p2.precalculated - i) << std::endl;
		std::cout << " err  = " << RUNGE_ROOL(prev_i, i) << std::endl;

		prev_i = i;
		m *= 2.0;

	}
	std::cout << std::endl << std::endl;


#endif // PART_3


	_getch();
	return 0;

}
