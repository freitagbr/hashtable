#include "prime.h"

#include <math.h>

/**
 * Determines if x is prime or not.
 * Returns:
 *   -1 - undefined (x < 2)
 *   0  - not prime
 *   1  - prime
 */
int is_prime(const int x) {
    if (x < 2)
        return -1;
    if (x == 3)
        return 1;
    if ((x & 1) == 0)
        return 0;
    for (int i = 3; i <= floor(sqrt((double) x)); i += 2) {
        if ((x % i) == 0)
            return 0;
    }
    return 1;
}

/**
 * Returns the next number after x that is prime,
 * or x if x is already prime.
 */
int next_prime(int x) {
    while (is_prime(x) != 1) {
        x++;
    }
    return x;
}
