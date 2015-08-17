#include <iostream>
#include <stdint.h>

void mult_matrix( uint64_t A[], const uint64_t B[], const uint64_t mod ) {
    uint64_t r0, r1, r2, r3;

    r0 = ( A[0] * B[0] + A[1] * B[2] ) % mod;
    r1 = ( A[0] * B[1] + A[1] * B[3] ) % mod;
    r2 = ( A[2] * B[0] + A[3] * B[2] ) % mod;
    r3 = ( A[2] * B[1] + A[3] * B[3] ) % mod;
    A[0] = r0; A[1] = r1; A[2] = r2; A[3] = r3;
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