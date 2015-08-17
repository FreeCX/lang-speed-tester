#include <stdio.h>
#include <stdint.h>

void mult_matrix( uint64_t a[], const uint64_t b[], const uint64_t m ) {
    uint64_t r0, r1, r2, r3;

    r0 = ( a[0] * b[0] + a[1] * b[2] ) % m;
    r1 = ( a[0] * b[1] + a[1] * b[3] ) % m;
    r2 = ( a[2] * b[0] + a[3] * b[2] ) % m;
    r3 = ( a[2] * b[1] + a[3] * b[3] ) % m;
    a[0] = r0; a[1] = r1; a[2] = r2; a[3] = r3;
}

uint64_t fibonacci( uint64_t n, uint64_t module ) {
    uint64_t power[] = { 0, 1, 1, 1 };
    uint64_t result[] = { 1, 0, 0, 1 };

    while ( n ) {
        if ( n & 1 ) {
            mult_matrix( result, power, module );
        }
        mult_matrix( power, power, module );
        n >>= 1;
    }
    return result[1];
}

int main( void ) {
    const uint64_t n = 11527523930876953L, m = 26673;

    fibonacci( n, m );
    return 0;
}