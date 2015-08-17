fn mult_matrix( a: [u64; 4], b: [u64; 4], m: u64 ) -> [u64; 4] {
    let r0 = ( a[0] * b[0] + a[1] * b[2] ) % m;
    let r1 = ( a[0] * b[1] + a[1] * b[3] ) % m;
    let r2 = ( a[2] * b[0] + a[3] * b[2] ) % m;
    let r3 = ( a[2] * b[1] + a[3] * b[3] ) % m;
    [r0, r1, r2, r3]
}

fn fibonacci( n: u64, module: u64 ) -> u64 {
    let mut power = [ 0, 1, 1, 1 ];
    let mut result = [ 1, 0, 0, 1 ];
    let mut step = n;

    while step > 0 {
        if step % 2 != 0 {
            result = mult_matrix( result, power, module );
        }
        power = mult_matrix( power, power, module );
        step >>= 1;
    }
    result[1]
}

fn main() {
    let n = 11527523930876953u64;
    let m = 26673u64;

    fibonacci( n, m );
}