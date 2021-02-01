#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "machine.h"

int main( int argc, char *argv[] )
{
    int arg = 1;
    FILE * input_file;
    char * line = NULL;
    char * filename = NULL;
    size_t len = 0;
    size_t read;

    cmdline_t machine;
    cmdline_t current_line;

    float backlash_x = 0;
    float backlash_y = 0;
    float backlash_z = 0;
    float delay_x = 0;
    float delay_y = 0;
    float delay_z = 0;

    if ( argc <= 1 ) {
        printf( "help:\r\n"
                "\r\n"
                "-i <file>      set input file name\r\n"
                "-x <backlash>  set x axis backlash in mm\r\n"
                "-y <backlash>  set y axis backlash in mm\r\n"
                "-z <backlash>  set z axis backlash in mm\r\n"
                "-dx <delay>    laser x axis on/off delay in second\r\n"
                "-dy <delay>    laser y axis on/off delay in second\r\n"
                "-dz <delay>    laser z axis on/off delay in second\r\n"
                );
            return(0);
    }

    /*
     * zero out machine and current line state
     */
    backlash_reset_line( &machine );
    backlash_reset_line( &current_line );
    /*
     * read cmd parameter
     */
    while( arg < argc ) {
        if ( !strcmp( argv[ arg ], "-i" ) ) {
            arg++;
            if ( argv[ arg ] != NULL ) {
                filename = argv[ arg ];
            }
            else {
                return(1);
            }
            arg++;
        }
        else if ( !strcmp( argv[ arg ], "-x" ) ) {
            arg++;
            if ( argv[ arg ] != NULL ) {
                backlash_x = atof( argv[ arg ] );
            }
            else {
                return(1);
            }
            arg++;
        }
        else if ( !strcmp( argv[ arg ], "-y" ) ) {
            arg++;
            if ( argv[ arg ] != NULL ) {
                backlash_y = atof( argv[ arg ] );
            }
            else {
                return(1);
            }
            arg++;
        }
        else if ( !strcmp( argv[ arg ], "-z" ) ) {
            arg++;
            if ( argv[ arg ] != NULL ) {
                backlash_z = atof( argv[ arg ] );
            }
            else {
                return(1);
            }
            arg++;
        }
        else if ( !strcmp( argv[ arg ], "-dx" ) ) {
            arg++;
            if ( argv[ arg ] != NULL ) {
                delay_x = atof( argv[ arg ] );
            }
            else {
                return(1);
            }
            arg++;
        }
        else if ( !strcmp( argv[ arg ], "-dy" ) ) {
            arg++;
            if ( argv[ arg ] != NULL ) {
                delay_y = atof( argv[ arg ] );
            }
            else {
                return(1);
            }
            arg++;
        }
        else if ( !strcmp( argv[ arg ], "-dz" ) ) {
            arg++;
            if ( argv[ arg ] != NULL ) {
                delay_z = atof( argv[ arg ] );
            }
            else {
                return(1);
            }
            arg++;
        }
    }

    if ( filename ) {
        if ( ( input_file = fopen( filename, "r") ) == NULL )
        {
            fprintf( stderr, "%s: can't open open file '%s' for input: ", argv[0], filename );
            perror("");
            return(1);
        }
    }
    else {
        printf("no filename\r\n");
        return(1);
    }

    /*
     * read file line by line
     */
    while ( ( read = getline( &line, &len, input_file ) ) != -1 ) {
        /*
         * pharse a gcode line into current line data
         */
        backlash_pharse_line( line, &current_line );
        /*
         * calculate backlash based on last machine data
         * after calculating backlash over currentline copy it
         * into machine data for the next round
         */
        backlash_calc_backlash( &current_line, &machine, backlash_x, backlash_y, backlash_z, delay_x, delay_y, delay_z );
        /*
         * printf out new gcode
         */
        backlash_print_line( &current_line );
    }


    return(0);
}
