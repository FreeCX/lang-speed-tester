#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>

struct timeval tv;

uint64_t get_time( void ) {
    gettimeofday( &tv, 0 );
    return ( tv.tv_sec * 1000000L + tv.tv_usec );
}

int main( int argc, char * argv[] ) {
    unsigned int max = 0, iterations = 100;
    const size_t max_seconds = 10;
    clock_t c0, c1, sum_c;
    struct dirent * dp;
    char buffer[256];
    size_t i, j, len;
    uint64_t t0, t1;
    double sum_t;
    DIR * dir;

    iterations = atoi( argv[1] );
    for ( i = 2; i < argc; i++ ) {
        len = strlen( argv[i] ) - 2;
        if ( max < len ) {
            max = (unsigned int) len;
        }
    }
    fprintf( stdout, "[info] iteration count = %d\n", iterations );
    dir = opendir( "./bin/" );
    if ( dir == NULL ) {
        perror( "opendir" );
        exit( EXIT_FAILURE );
    }
    while ( ( dp = readdir( dir ) ) != NULL ) {
        if ( dp->d_name[0] == '.' ) {
            continue;
        }
        sprintf( buffer, "./bin/%s", dp->d_name );
        fprintf( stdout, "[info] wait %lu seconds to offload CPU", max_seconds );
        for ( j = 0; j < max_seconds; j++ ) {
            fputc( '.', stdout );
            fflush( stdout );
            sleep( 1 );
        }
        sum_c = sum_t = 0;
        fprintf( stdout, "[DONE]\r > %lu: prog '%*s' ", i - 1, max, dp->d_name );
        fflush( stdout );
        for ( j = 0; j < iterations; j++ ) {
            t0 = get_time();
            c0 = clock();
            system( buffer );
            t1 = get_time();
            c1 = clock();
            sum_t += ( t1 - t0 );
            sum_c += ( c1 - c0 );
        }
        fprintf( stdout, "avg cpu time = %lf cycle, avg time = %lf µs\n",
                 (double) sum_c / iterations, (double) sum_t / iterations );
    }
    return 0;
}
