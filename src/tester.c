#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>

uint64_t get_time( void ) {
    static struct timeval tv;
    gettimeofday( &tv, 0 );
    return ( tv.tv_sec * 1000000L + tv.tv_usec );
}

int main( int argc, char * argv[] ) {
    unsigned int max = 0, iterations = 100;
    size_t j, term_size, counter = 1;
    const size_t max_seconds = 10;
    clock_t c0, c1, sum_c;
    struct dirent * dp;
    char buffer[256];
    struct winsize w;
    uint64_t t0, t1;
    double sum_t;
    DIR * dir;

    if ( argc > 1 ) {
        iterations = atol( argv[1] );
    }
    fprintf( stdout, "[info] iteration count = %u\n", iterations );
    dir = opendir( "./bin/" );
    if ( dir == NULL ) {
        perror( "opendir" );
        exit( EXIT_FAILURE );
    }
    while ( ( dp = readdir( dir ) ) != NULL ) {
        size_t len = strlen( dp->d_name );
        if ( len > max ) {
            max = len;
        }
    }
    rewinddir( dir );
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
        fprintf( stdout, "[DONE]" );
        for ( j = 0; j < iterations; j++ ) {
            ioctl( 0, TIOCGWINSZ, &w );
            term_size = w.ws_col - 18;
            fprintf( stdout, "\rprogress: [" );
            uint8_t current = ( j * term_size ) / iterations;
            uint8_t progress = ( j * 100 ) / iterations + 1;
            for ( size_t i = 0; i < term_size; i++ ) {
                if ( i <= current + 1 ) {
                    fputc( '#', stdout );
                } else {
                    fputc( '-', stdout );
                }
            }
            fprintf( stdout, "] %3u %%", progress );
            fflush( stdout );
            t0 = get_time();
            c0 = clock();
            system( buffer );
            t1 = get_time();
            c1 = clock();
            sum_t += ( t1 - t0 );
            sum_c += ( c1 - c0 );
        }
        // clear line
        fprintf( stdout, "%c[2K", 27 );
        fprintf( stdout, "\r > %lu: prog '%*s' avg cpu time = %.4lf cycle, avg time = %.4lf µs\n",
            counter, max, dp->d_name, (double) sum_c / iterations, (double) sum_t / iterations );
        counter++;
    }
    closedir( dir );
    return EXIT_SUCCESS;
}