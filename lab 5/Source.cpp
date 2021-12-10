/*
*
*	Main.cpp
*	Test of Integral module
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





#endif // PART_3


	_getch();
	return 0;

}
