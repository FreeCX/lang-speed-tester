package main

func mult_matrix( a [4] int64, b [4] int64, m int64 ) ( [4] int64 ) {
    var r = [4] int64 { 0 }
    r[0] = ( a[0] * b[0] + a[1] * b[2] ) % m
    r[1] = ( a[0] * b[1] + a[1] * b[3] ) % m
    r[2] = ( a[2] * b[0] + a[3] * b[2] ) % m
    r[3] = ( a[2] * b[1] + a[3] * b[3] ) % m
    return r
}

func fibonacci( n int64, mod int64 ) int64 {
    var power = [...] int64 { 0, 1, 1, 1 }
    var result = [...] int64 { 1, 0, 0, 1 }
    for ( n > 0 ) {
        if ( n % 2 == 0 ) {
            result = mult_matrix( result, power, mod )
        }
        power = mult_matrix( power, power, mod )
        n >>= 1
    }
    return result[1]
}

func main() {
    var n int64 = 11527523930876953
    var m int64 = 26673
    fibonacci( n, m )
}