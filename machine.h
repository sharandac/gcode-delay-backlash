#ifndef MACHINE_H
    #define MACHINE_H

    typedef struct {
        float argument;
        float delay;
        float backlash;
        bool argument_bool;
    } argument_t;

    typedef struct {
        argument_t F;
        argument_t G;
        argument_t M;
        argument_t X;
        argument_t Y;
        argument_t Z;
        argument_t P;
        argument_t S;
    } cmdline_t;

    void backlash_reset_line( cmdline_t *line );
    void backlash_pharse_line( char *input, cmdline_t *line );
    void backlash_print_line( cmdline_t *line );
    void backlash_cpy_cmdline( cmdline_t *dest, cmdline_t *src );
    void backlash_calc_backlash( cmdline_t *current_line, cmdline_t *machine, float backlash_x, float backlash_y, float backlash_z, float delay_x, float delay_y, float delay_z );

#endif // MACHINE_H