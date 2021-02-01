#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "machine.h"

void backlash_calc_backlash( cmdline_t *current_line, cmdline_t *machine, float backlash_x, float backlash_y, float backlash_z, float delay_x, float delay_y, float delay_z ) {
    /*
     * check if feedrate has change
     */
    if ( current_line->F.argument_bool ) {
        machine->F.argument = current_line->F.argument;
    }
    /*
     * calculate the x achses delay distance from delay_x and current feedrate
     */
    float delay_x_distance = ( machine->F.argument / 60 ) * delay_x;
    /*
     * calculate the x achses delay distance from delay_x and current feedrate
     */
    float delay_y_distance = ( machine->F.argument / 60 ) * delay_y;
    /*
     * calculate the x achses delay distance from delay_x and current feedrate
     */
    float delay_z_distance = ( machine->F.argument / 60 ) * delay_z;
    /*
     * update x coordinate if moved
     */
    if ( current_line->X.argument_bool ) {
        float tmp_X = current_line->X.argument;
        if ( current_line->X.argument > machine->X.argument ) {
            current_line->X.argument = current_line->X.argument + backlash_x + delay_x_distance;
        }
        else if ( current_line->X.argument < machine->X.argument ) {
            current_line->X.argument = current_line->X.argument - backlash_x - delay_x_distance;
        }
        machine->X.argument = tmp_X;
    }
    /*
     * update y coordinate if moved
     */
    if ( current_line->Y.argument_bool ) {
        float tmp_Y = current_line->Y.argument;
        if ( current_line->Y.argument > machine->Y.argument ) {
            current_line->Y.argument = current_line->Y.argument + backlash_y + delay_y_distance;
        }
        else if ( current_line->Y.argument < machine->Y.argument ) {
            current_line->Y.argument = current_line->Y.argument - backlash_y - delay_y_distance;
        }
        machine->Y.argument = tmp_Y;
    }
    /*
     * update z coordinate if moved
     */
    if ( current_line->Z.argument_bool ) {
        float tmp_Z = current_line->Y.argument;
        if ( current_line->Z.argument > machine->Z.argument ) {
            current_line->Z.argument = current_line->Z.argument + backlash_z + delay_z_distance;
        }
        else if ( current_line->Z.argument < machine->Z.argument ) {
            current_line->Z.argument = current_line->Z.argument - backlash_z - delay_z_distance;
        }
        machine->Z.argument = tmp_Z;
    }
}

void backlash_reset_line( cmdline_t *line ) {
    line->F.argument = 0;
    line->F.argument_bool = false;
    line->G.argument = 0;
    line->G.argument_bool = false;
    line->M.argument = 0;
    line->M.argument_bool = false;
    line->P.argument = 0;
    line->P.argument_bool = false;
    line->S.argument = 0;
    line->S.argument_bool = false;
    line->X.argument = 0;
    line->X.argument_bool = false;
    line->Y.argument = 0;
    line->Y.argument_bool = false;
    line->Z.argument = 0;
    line->Z.argument_bool = false;
}

void backlash_pharse_line( char *input, cmdline_t *line ) {
    char *ret;

    backlash_reset_line( line );

    if ( ( ret = strstr( input, ";") ) ) {
        printf("%s", input );
        return;
    }

    if ( ( ret = strstr( input, "G") ) ) {
        *ret++;
        line->G.argument = atof( ret );
        line->G.argument_bool = true;
    }
    if ( ( ret = strstr( input, "M") ) ) {
        *ret++;
        line->M.argument = atof( ret );
        line->M.argument_bool = true;
    }
    if ( ( ret = strstr( input, "X") ) ) {
        *ret++;
        line->X.argument = atof( ret );
        line->X.argument_bool = true;
    }
    if ( ( ret = strstr( input, "Y") ) ) {
        *ret++;
        line->Y.argument = atof( ret );
        line->Y.argument_bool = true;
    }
    if ( ( ret = strstr( input, "Z") ) ) {
        *ret++;
        line->Z.argument = atof( ret );
        line->Z.argument_bool = true;
    }
    if ( ( ret = strstr( input, "S") ) ) {
        *ret++;
        line->S.argument = atof( ret );
        line->S.argument_bool = true;
    }
    if ( ( ret = strstr( input, "F") ) ) {
        *ret++;
        line->F.argument = atof( ret );
        line->F.argument_bool = true;
    }
    if ( ( ret = strstr( input, "P") ) ) {
        *ret++;
        line->P.argument = atof( ret );
        line->P.argument_bool = true;
    }
}

void backlash_print_line( cmdline_t *line ) {
    if ( line->G.argument_bool ) {
        printf("G%.0f ", line->G.argument );
    }
    if ( line->M.argument_bool ) {
        printf("M%.0f ", line->M.argument );
    }
    if ( line->X.argument_bool ) {
        printf("X%.3f ", line->X.argument );
    }
    if ( line->Y.argument_bool ) {
        printf("Y%.3f ", line->Y.argument );
    }
    if ( line->Z.argument_bool ) {
        printf("Z%.3f ", line->Z.argument );
    }
    if ( line->P.argument_bool ) {
        printf("P%.0f ", line->P.argument );
    }
    if ( line->S.argument_bool ) {
        printf("S%.3f ", line->S.argument );
    }
    if ( line->F.argument_bool ) {
        printf("F%.0f ", line->F.argument );
    }
    printf("\n");
}

void backlash_cpy_cmdline( cmdline_t *dest, cmdline_t *src ) {
    memcpy( dest, src, sizeof( cmdline_t ) );
}
