/**
 * This application tests motor output.
 */

#include "ev3api.h"
#include "app.h"

#define MSG_BUF_SIZE    (64)

const motor_port_t motor_port = EV3_PORT_A;

int motor_power_output = 0;
int motor_power_current = 0;
int motor_counts_current = 0;
int motor_power_output_change = 0;
int cyc_task_1sec_count = 0;
int cyc_task_100msec_count = 0;
//const char *logging_file_name = "Log.csv";

FILE *logging_file = NULL;
const char *logging_file_name_list[10] = {
    "Log_001.csv", "Log_002.csv", "Log_003.csv", "Log_004.csv", "Log_005.csv",
    "Log_006.csv", "Log_007.csv", "Log_008.csv", "Log_009.csv", "Log_010.csv"
    };
char msg_buf[MSG_BUF_SIZE];
/**
 * @biref   Main task of this application.
 *          Initializes parameters, configures device,
 *          creates log file, and starts periodic tasks.
 *          The started tasks will be stopped after a
 *          concrete time passed.
 */
void main_task(intptr_t unused)
{
    int index = 0;
    const char *logging_file_name = NULL;

    //Initialize
    ev3_lcd_set_font(EV3_FONT_SMALL);
    ev3_lcd_draw_string("STARTING", 0, 0);
    ev3_motor_config(motor_port, LARGE_MOTOR);

    for (index = 0; index < 10; index++) {
        logging_file_name = logging_file_name_list[index];
        logging_file = fopen(logging_file_name, "w");
        fprintf(logging_file, "CNT,TARGET,CURRENT,COUNTS\n");

        //Reset paraemters.
        motor_power_output = 0;
        motor_power_current = 0;
        motor_counts_current = 0;
        motor_power_output_change = 5;

        cyc_task_100msec_count = 0;
        cyc_task_1sec_count = 0;

        ev3_motor_reset_counts(motor_port);

        sprintf((char *)&msg_buf[0], "RUNNING:%s", logging_file_name);
        ev3_lcd_draw_string((char *)&msg_buf[0], 0, 0);

        ev3_sta_cyc(CYC_TASK_10MS);
        ev3_sta_cyc(CYC_TASK_1SEC);
        tslp_tsk(85000);

        ev3_stp_cyc(CYC_TASK_10MS);
        ev3_stp_cyc(CYC_TASK_1SEC);

        fclose(logging_file);
        ev3_lcd_draw_string("FINISHED", 0, 0);
    }
}

/**
 * @brief   Periodic task called each 10 mseconds.
 */
void cyc_task_100msec(intptr_t unused)
{
    motor_power_current = ev3_motor_get_power(motor_port);
    motor_counts_current = ev3_motor_get_counts(motor_port);

    if (cyc_task_100msec_count <= 800) {
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

    motor_power_output += motor_power_output_change;
    if (cyc_task_1sec_count <= 80) {
        ev3_motor_set_power(motor_port, motor_power_output);
    } else {
        ev3_motor_set_power(motor_port, 0);
    }

    cyc_task_1sec_count++;
}
