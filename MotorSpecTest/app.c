/**
 * This application tests motor output.
 */

#include "ev3api.h"
#include "app.h"

const motor_port_t motor_port = EV3_PORT_A;

bool_t runs_main_task = false;
int motor_power_output = 0;
int motor_power_current = 0;
int motor_counts_current = 0;
int motor_power_output_change = 0;
int main_task_counter = 0;
const char *logging_file_name = "Log.csv";

FILE *logging_file = NULL;

void main_task(intptr_t unused)
{
    //Configure device.
    ev3_lcd_draw_string("STARTING", 0, 0);
    ev3_lcd_set_font(EV3_FONT_SMALL);
    ev3_motor_config(motor_port, MEDIUM_MOTOR);

    logging_file = fopen(logging_file_name, "a");
    fprintf(logging_file, "CNT,TARGET,CURRENT,COUNTS\n");

    motor_power_output_change = 5;
    runs_main_task = true;
    ev3_lcd_draw_string("RUNNING   ", 0, 0);
    while (runs_main_task) {
        tslp_tsk(100);

        if (0 == (main_task_counter % 10)) {
            if (100 == motor_power_output) {
                motor_power_output_change = -5;
            } else if (-100 == motor_power_output)  {
                motor_power_output_change = 5;
            }
            motor_power_output += motor_power_output_change;
        }

        ev3_motor_set_power(motor_port, motor_power_output);
        motor_power_current = ev3_motor_get_power(motor_port);
        motor_counts_current = ev3_motor_get_counts(motor_port);

        fprintf(logging_file, "%d,%d,%d,%d\n", 
            main_task_counter, 
            motor_power_output,
            motor_power_current,
            motor_counts_current);

        if (800 <= main_task_counter) {
            break;
        }
        main_task_counter++;
    }

    ev3_motor_set_power(motor_port, 0);
    tslp_tsk(1000);

    ev3_lcd_draw_string("FINISHED", 0, 0);
    fclose(logging_file);
}
