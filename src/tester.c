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

double get_time( void ) {
    static struct timespec tv;
    clock_gettime( CLOCK_REALTIME, &tv );
    return ( (double) tv.tv_sec + (double) tv.tv_nsec / 1.0E9 );
}

int main( int argc, char * argv[] ) {
    size_t j, term_size, counter = 1;
    unsigned int max = 0, step = 1;
    double t0, t1, sum_t, sum;
    struct dirent * dp;
    char buffer[256];
    struct winsize w;
    FILE * data;
    DIR * dir;

    dir = opendir( "./bin/" );
    if ( dir == NULL ) {
        perror( "opendir" );
        exit( EXIT_FAILURE );
    }
    data = fopen( "data/lang-speed-data", "w" );
    fprintf( data, "# iterations " );
    while ( ( dp = readdir( dir ) ) != NULL ) {
        size_t len = strlen( dp->d_name );
        if ( len > max ) {
            max = len;
        }
        if ( dp->d_name[0] != '.' ) {
        	fprintf( data, "%s ", dp->d_name );
    	}
    }
    fprintf( data, "\n" );
    for ( int iterations = 10; iterations <= 1000; iterations += step ) {
    	if ( iterations >= 100 ) {
    		step = 25;
    	}
        rewinddir( dir );
        fprintf( data, "%10d ", iterations );
        fprintf( stdout, "[info] iteration count = %d\n", iterations );
        while ( ( dp = readdir( dir ) ) != NULL ) {
            if ( dp->d_name[0] == '.' ) {
                continue;
            }
            sprintf( buffer, "./bin/%s", dp->d_name );
            sum_t = 0;
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
                system( buffer );
                t1 = get_time();
                sum_t += ( t1 - t0 );
            }
            // clear line
            fprintf( stdout, "%c[2K", 27 );
            sum = ( sum_t * 1.0E6 ) / (double) iterations;
            fprintf( stdout, "\r > %lu: prog '%*s' avg time = %.4lf μs\n", counter, max, dp->d_name, sum );
            fprintf( data, "%5.4lf ", sum );
            counter++;
        }
        counter = 1;
        fprintf( stdout, "\n" );
        fprintf( data, "\n" );
        fflush( data );
    }
    fclose( data );
    closedir( dir );
    return EXIT_SUCCESS;
}