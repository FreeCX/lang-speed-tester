void mult_matrix( ulong a[], ulong b[], ulong m ) {
    ulong r0, r1, r2, r3;

    r0 = ( a[0] * b[0] + a[1] * b[2] ) % m;
    r1 = ( a[0] * b[1] + a[1] * b[3] ) % m;
    r2 = ( a[2] * b[0] + a[3] * b[2] ) % m;
    r3 = ( a[2] * b[1] + a[3] * b[3] ) % m;
    a[0] = r0; a[1] = r1; a[2] = r2; a[3] = r3;
}

ulong fibonacci( ulong n, ulong m ) {
    ulong power[] = [ 0, 1, 1, 1 ];
    ulong result[] = [ 1, 0, 0, 1 ];

    while ( n ) {
        if ( n & 1 ) {
            mult_matrix( result, power, m );
        }
        mult_matrix( power, power, m );
        n >>= 1;
    }
    return result[1];
}

void main() {
    const ulong n = 11527523930876953L, m = 26673;

    fibonacci( n, m );
}