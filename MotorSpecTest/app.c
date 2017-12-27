/**
 * This application tests motor output.
 */

#include "ev3api.h"
#include "app.h"

const motor_port_t motor_port = EV3_PORT_A;

int motor_power_output = 0;
int motor_power_current = 0;
int motor_counts_current = 0;
int motor_power_output_change = 0;
int cyc_task_1sec_count = 0;
int cyc_task_100msec_count = 0;
const char *logging_file_name = "Log.csv";

FILE *logging_file = NULL;

/**
 * @biref   Main task of this application.
 *          Initializes parameters, configures device,
 *          creates log file, and starts periodic tasks.
 *          The started tasks will be stopped after a
 *          concrete time passed.
 */
void main_task(intptr_t unused)
{
    //Initialize
    ev3_lcd_set_font(EV3_FONT_SMALL);
    ev3_lcd_draw_string("STARTING", 0, 0);
    ev3_motor_config(motor_port, MEDIUM_MOTOR);

    logging_file = fopen(logging_file_name, "a");
    fprintf(logging_file, "CNT,TARGET,CURRENT,COUNTS\n");

    motor_power_output_change = 5;
    ev3_lcd_draw_string("RUNNING   ", 0, 0);

    ev3_sta_cyc(CYC_TASK_10MS);
    ev3_sta_cyc(CYC_TASK_1SEC);
    tslp_tsk(90000);

    ev3_stp_cyc(CYC_TASK_10MS);
    ev3_stp_cyc(CYC_TASK_1SEC);

    ev3_lcd_draw_string("FINISHED", 0, 0);
    fclose(logging_file);
}

/**
 * @brief   Periodic task called each 10 mseconds.
 */
void cyc_task_100msec(intptr_t unused)
{
    motor_power_current = ev3_motor_get_power(motor_port);
    motor_counts_current = ev3_motor_get_counts(motor_port);

    if (cyc_task_1sec_count <= 80) {
        fprintf(logging_file, "%d,%d,%d,%d\n", 
            cyc_task_100msec_count,
            motor_power_output,
            motor_power_current,
            motor_counts_current);
    }
    cyc_task_100msec_count++;
}

/**
 * @brief   Periodic task called each 1 sencond.
 */
void cyc_task_1sec(intptr_t unused)
{
    if (100 == motor_power_output) {
        motor_power_output_change = -5;
    }
    if (-100 == motor_power_output) {
        motor_power_output_change = 5;
    }

    if (cyc_task_1sec_count <= 80) {
        ev3_motor_set_power(motor_port, motor_power_output);
    } else {
        ev3_motor_set_power(motor_port, 0);
    }

    motor_power_output += motor_power_output_change;
    cyc_task_1sec_count++;
}
