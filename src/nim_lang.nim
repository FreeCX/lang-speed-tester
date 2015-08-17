type
    Vec4 = array[0..3, int64]

proc mult_matrix( a: Vec4, b: Vec4, m: int64 ): Vec4 =
    [
        ( a[0] * b[0] + a[1] * b[2] ) mod m,
        ( a[0] * b[1] + a[1] * b[3] ) mod m,
        ( a[2] * b[0] + a[3] * b[2] ) mod m,
        ( a[2] * b[1] + a[3] * b[3] ) mod m
    ]

proc fibonacci( n: int64, module: int64 ): int64 =
    var
        power: Vec4 = [ int64( 0 ), int64( 1 ), int64( 1 ), int64( 1 ) ]
        result: Vec4 = [ int64( 1 ), int64( 0 ), int64( 0 ), int64( 1 ) ]
        step: int64 = n
    while step > 0:
        if step mod 2 != 0:
            result = mult_matrix( result, power, module )
        power = mult_matrix( power, power, module )
        step = step shr 1
    result[1]

let n: int64 = 11527523930876953
let m: int64 = 26673
let _: int64 = fibonacci( n, m )
