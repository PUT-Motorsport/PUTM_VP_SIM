/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ert_main.c
 *
 * Code generated for Simulink model 'tv_code'.
 *
 * Model version                  : 1.10
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Sat Oct  5 19:41:48 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include <stddef.h>
#include <stdio.h>            /* This example main program uses printf/fflush */
#include "tv_code.h"                   /* Model header file */

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void read_inputs(){
  tv_code_P.whl_speed_fl_Value = 0;
  tv_code_P.whl_speed_fr_Value = 0;
  tv_code_P.whl_speed_rl_Value = 0;
  tv_code_P.whl_speed_rr_Value = 0;
  tv_code_P.delta_Value = 0;
  tv_code_P.acc_pedal_Value = 1; 
  tv_code_P.ax_Value = 0;
  tv_code_P.ay_Value = 0;
  tv_code_P.yaw_rate_Value = 0
  ;
}


void rt_OneStep(void);
void rt_OneStep(void)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(tv_code_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  tv_code_step();

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example main function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific. This example
 * illustrates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
  /* Unused arguments */
  (void)(argc);
  (void)(argv);

  /* Initialize model */
  tv_code_initialize();

  /* Simulating the model step behavior (in non real-time) to
   *  simulate model behavior at stop time.
   */
  while ((rtmGetErrorStatus(tv_code_M) == (NULL)) && !rtmGetStopRequested
         (tv_code_M)) {
    read_inputs();
    tv_code_P.delta_Value *=3.14/180;
    rt_OneStep();
    printf("Front left %f\n",tv_code_B.trq_fl);
    printf("Front right %f\n",tv_code_B.trq_fr);
    printf("Rear left %f\n",tv_code_B.trq_rl);
    printf("Rear right %f\n",tv_code_B.trq_rr);
  }

  /* Terminate model */
  tv_code_terminate();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
