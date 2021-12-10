#include "jnkMath.h"
#include <iostream>
#include <math.h>



INT jnkMath::factorial(INT x) {

    if (x < 0) {
        throw "negative argument in factorial function";
    }

    if (x == 0) {
        return 1;
    }

    return x * factorial(x - 1);
}

DOUBLE jnkMath::degree(DOUBLE x, INT n) {

    if (n < 0) {
        throw "negative degree in degree function";
    }

    DOUBLE result = 1;
    for (auto i = 0; i < n; i++) {
        result *= x;
    }

    return result;
}

DOUBLE jnkMath::degree(INT x, INT n) {

    if (n < 0) {
        throw "negative degree in degree function";
    }

    DOUBLE result = 1;
    for (auto i = 0; i < n; i++) {
        result *= x;
    }

    return result;
}

SHORT jnkMath::negOneDeg(INT n) {
    if (n % 2) {
        return -1;
    }
    return 1;
}

USHORT jnkMath::DigitAfterPoINT(DOUBLE number) {

    DOUBLE fractpart = number - (INT)number;
    USHORT count = 0u;

    while (fractpart - (INT)fractpart != 0.0) {
        fractpart *= 10;
        count++;
    }

    return count;
}

DOUBLE jnkMath::Grad2Rad(DOUBLE phi) {
    return phi * PI / 180.0;
}
