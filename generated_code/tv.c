/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: tv.c
 *
 * Code generated for Simulink model 'tv'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Fri Jul  5 00:15:46 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "tv.h"
#include <math.h>
#include "rtwtypes.h"
#include "tv_private.h"

/* Block signals (default storage) */
B_tv_T tv_B;

/* Continuous states */
X_tv_T tv_X;

/* Disabled State Vector */
XDis_tv_T tv_XDis;

/* Real-time model */
static RT_MODEL_tv_T tv_M_;
RT_MODEL_tv_T *const tv_M = &tv_M_;

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 1;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  tv_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  tv_step();
  tv_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  tv_step();
  tv_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  tv_step();
  tv_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void tv_step(void)
{
  real_T Gain1_tmp;
  real_T Gain2_tmp;
  real_T Gain2_tmp_0;
  real_T Gain2_tmp_1;
  real_T Gain_b_tmp;
  real_T P_el_total;
  real_T Product_b_tmp;
  if (rtmIsMajorTimeStep(tv_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&tv_M->solverInfo,((tv_M->Timing.clockTick0+1)*
      tv_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(tv_M)) {
    tv_M->Timing.t[0] = rtsiGetT(&tv_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(tv_M)) {
    /* Gain: '<S13>/Gain2' incorporates:
     *  Constant: '<S2>/WheelSp_FL'
     *  Constant: '<S2>/WheelSp_FR'
     *  Constant: '<S2>/WheelSp_RL'
     *  Constant: '<S2>/WheelSp_RR'
     *  Gain: '<S6>/Gain'
     *  Gain: '<S6>/Gain1'
     *  Sum: '<S6>/Plus'
     */
    tv_B.Gain2 = ((tv_P.WheelSp_FL_Value + tv_P.WheelSp_FR_Value) +
                  tv_P.WheelSp_RL_Value) + tv_P.WheelSp_RR_Value;
    tv_B.Gain2 *= tv_P.Gain_Gain;
    tv_B.Gain2 *= tv_P.rw;

    /* Sum: '<S9>/Sum' incorporates:
     *  Constant: '<S2>/yaw_rate'
     *  Product: '<S5>/Product'
     */
    tv_B.Sum = tv_P.yaw_rate_Value * tv_B.Gain2;

    /* Gain: '<S13>/Gain2' incorporates:
     *  Constant: '<S5>/Constant'
     *  Gain: '<S5>/Gain1'
     *  Gain: '<S5>/axlebase'
     *  Math: '<S5>/Square'
     *  Sum: '<S5>/Sum'
     */
    tv_B.Gain2 *= tv_B.Gain2;
    tv_B.Gain2 *= tv_P.Gain1_Gain;
    tv_B.Gain2 += tv_P.Constant_Value;
    tv_B.Gain2 *= tv_P.L;

    /* Sum: '<S9>/Sum' incorporates:
     *  Constant: '<S2>/delta'
     *  Product: '<S5>/Divide'
     */
    tv_B.Sum /= tv_B.Gain2;
    tv_B.Sum -= tv_P.delta_Value;

    /* Gain: '<S9>/Gain' */
    tv_B.Gain = tv_P.Gain_Gain_p * tv_B.Sum;

    /* Gain: '<S13>/Gain2' incorporates:
     *  Constant: '<S2>/acc_pedal'
     *  Constant: '<S2>/brake_pedal'
     *  Sum: '<S8>/Sum1'
     */
    tv_B.Gain2 = tv_P.acc_pedal_Value - tv_P.brake_pedal_Value;

    /* Product: '<S8>/Product1' incorporates:
     *  Constant: '<S8>/Constant1'
     */
    tv_B.Product1 = tv_P.Constant1_Value * tv_B.Gain2;
  }

  /* Product: '<S16>/Product' incorporates:
   *  Integrator: '<S9>/Integrator'
   *  Sum: '<S9>/Sum1'
   */
  tv_B.Product = tv_X.Integrator_CSTATE;
  tv_B.Product += tv_B.Gain;

  /* Gain: '<S14>/Gain' incorporates:
   *  Gain: '<S15>/Gain'
   *  Gain: '<S16>/Gain'
   *  Gain: '<S17>/Gain'
   */
  P_el_total = tv_P.rw / tv_P.ls * tv_B.Product;

  /* Product: '<S17>/Product' incorporates:
   *  Gain: '<S14>/Gain'
   */
  tv_B.Product_b = P_el_total;

  /* Sum: '<S14>/Sum' incorporates:
   *  Sum: '<S17>/Sum'
   */
  Product_b_tmp = tv_B.Product1 - tv_B.Product_b;

  /* Product: '<S17>/Product' incorporates:
   *  Sum: '<S14>/Sum'
   */
  tv_B.Product_b = Product_b_tmp;
  if (rtmIsMajorTimeStep(tv_M)) {
    /* Gain: '<S10>/Gain1' incorporates:
     *  Constant: '<S2>/ax'
     *  Gain: '<S11>/Gain1'
     */
    Gain2_tmp = tv_P.h * tv_P.ax_Value;

    /* Gain: '<S13>/Gain2' incorporates:
     *  Gain: '<S10>/Gain1'
     */
    tv_B.Gain2 = Gain2_tmp;

    /* Gain: '<S10>/Gain2' incorporates:
     *  Constant: '<S2>/ay'
     *  Gain: '<S11>/Gain2'
     */
    Gain_b_tmp = tv_P.h * tv_P.lr / tv_P.ls * tv_P.ay_Value;

    /* Gain: '<S13>/Gain' incorporates:
     *  Gain: '<S10>/Gain2'
     */
    tv_B.Gain_b = Gain_b_tmp;

    /* Sum: '<S10>/Sum' incorporates:
     *  Constant: '<S10>/Constant'
     *  Constant: '<S11>/Constant'
     *  Sum: '<S11>/Sum'
     */
    Gain2_tmp_0 = tv_P.g * tv_P.lr;

    /* Gain: '<S13>/Gain2' incorporates:
     *  Constant: '<S10>/Constant'
     *  Sum: '<S10>/Sum'
     */
    tv_B.Gain2 = (Gain2_tmp_0 - tv_B.Gain2) - tv_B.Gain_b;

    /* Gain: '<S10>/Gain' incorporates:
     *  Gain: '<S11>/Gain'
     */
    Gain2_tmp_1 = tv_P.m / (2.0 * tv_P.L);

    /* Gain: '<S13>/Gain2' incorporates:
     *  Gain: '<S10>/Gain'
     */
    tv_B.Gain2 *= Gain2_tmp_1;

    /* Gain: '<S14>/Gain1' incorporates:
     *  Gain: '<S15>/Gain1'
     */
    Gain1_tmp = 1.0 / (tv_P.m * tv_P.g);

    /* Gain: '<S14>/Gain1' */
    tv_B.Gain1 = Gain1_tmp * tv_B.Gain2;

    /* Gain: '<S13>/Gain' incorporates:
     *  Gain: '<S11>/Gain1'
     */
    tv_B.Gain_b = Gain2_tmp;

    /* Gain: '<S13>/Gain2' incorporates:
     *  Gain: '<S11>/Gain2'
     */
    tv_B.Gain2 = Gain_b_tmp;

    /* Gain: '<S13>/Gain' incorporates:
     *  Gain: '<S11>/Gain'
     *  Sum: '<S11>/Sum'
     */
    tv_B.Gain_b = (Gain2_tmp_0 - tv_B.Gain_b) + tv_B.Gain2;
    tv_B.Gain_b *= Gain2_tmp_1;

    /* Gain: '<S15>/Gain1' */
    tv_B.Gain1_g = Gain1_tmp * tv_B.Gain_b;
  }

  /* Product: '<S17>/Product' incorporates:
   *  Product: '<S14>/Product'
   */
  tv_B.Product_b *= tv_B.Gain1;

  /* MinMax: '<S7>/Min' incorporates:
   *  Constant: '<S7>/Torque_ub'
   */
  tv_B.Min = fmin(tv_P.Torque_ub_Value, tv_B.Product_b);

  /* Product: '<S17>/Product' incorporates:
   *  Gain: '<S15>/Gain'
   */
  tv_B.Product_b = P_el_total;

  /* Sum: '<S15>/Sum' incorporates:
   *  Sum: '<S16>/Sum'
   */
  P_el_total = tv_B.Product1 + tv_B.Product_b;

  /* Product: '<S17>/Product' incorporates:
   *  Product: '<S15>/Product'
   *  Sum: '<S15>/Sum'
   */
  tv_B.Product_b = P_el_total;
  tv_B.Product_b *= tv_B.Gain1_g;

  /* MinMax: '<S7>/Min1' incorporates:
   *  Constant: '<S7>/Torque_ub'
   */
  tv_B.Min1 = fmin(tv_P.Torque_ub_Value, tv_B.Product_b);
  if (rtmIsMajorTimeStep(tv_M)) {
    /* Gain: '<S13>/Gain' incorporates:
     *  Constant: '<S2>/ax'
     *  Gain: '<S12>/Gain1'
     */
    tv_B.Gain_b = tv_P.h * tv_P.ax_Value;

    /* Gain: '<S12>/Gain2' incorporates:
     *  Constant: '<S2>/ay'
     *  Gain: '<S13>/Gain2'
     */
    Gain2_tmp = tv_P.h * tv_P.lf / tv_P.ls * tv_P.ay_Value;

    /* Gain: '<S13>/Gain2' incorporates:
     *  Gain: '<S12>/Gain2'
     */
    tv_B.Gain2 = Gain2_tmp;

    /* Sum: '<S12>/Sum' incorporates:
     *  Constant: '<S12>/Constant'
     *  Constant: '<S13>/Constant'
     *  Sum: '<S13>/Sum'
     */
    Gain_b_tmp = tv_P.g * tv_P.lf;

    /* Gain: '<S13>/Gain' incorporates:
     *  Constant: '<S12>/Constant'
     *  Sum: '<S12>/Sum'
     */
    tv_B.Gain_b = (Gain_b_tmp + tv_B.Gain_b) - tv_B.Gain2;

    /* Gain: '<S12>/Gain' incorporates:
     *  Gain: '<S13>/Gain'
     */
    Gain2_tmp_0 = tv_P.m / (2.0 * tv_P.L);

    /* Gain: '<S13>/Gain' incorporates:
     *  Gain: '<S12>/Gain'
     */
    tv_B.Gain_b *= Gain2_tmp_0;

    /* Gain: '<S17>/Gain1' incorporates:
     *  Gain: '<S16>/Gain1'
     */
    Gain2_tmp_1 = 1.0 / (tv_P.m * tv_P.g);

    /* Gain: '<S17>/Gain1' */
    tv_B.Gain1_gv = Gain2_tmp_1 * tv_B.Gain_b;

    /* Gain: '<S13>/Gain' incorporates:
     *  Constant: '<S2>/ax'
     *  Gain: '<S13>/Gain1'
     */
    tv_B.Gain_b = tv_P.h * tv_P.ax_Value;

    /* Gain: '<S13>/Gain2' */
    tv_B.Gain2 = Gain2_tmp;

    /* Gain: '<S13>/Gain' incorporates:
     *  Sum: '<S13>/Sum'
     */
    tv_B.Gain_b = (Gain_b_tmp + tv_B.Gain_b) + tv_B.Gain2;
    tv_B.Gain_b *= Gain2_tmp_0;

    /* Gain: '<S16>/Gain1' */
    tv_B.Gain1_m = Gain2_tmp_1 * tv_B.Gain_b;
  }

  /* Product: '<S17>/Product' incorporates:
   *  Sum: '<S17>/Sum'
   */
  tv_B.Product_b = Product_b_tmp;
  tv_B.Product_b *= tv_B.Gain1_gv;

  /* MinMax: '<S7>/Min2' incorporates:
   *  Constant: '<S7>/Torque_ub'
   */
  tv_B.Min2 = fmin(tv_P.Torque_ub_Value, tv_B.Product_b);

  /* Product: '<S16>/Product' incorporates:
   *  Sum: '<S16>/Sum'
   */
  tv_B.Product = P_el_total;
  tv_B.Product *= tv_B.Gain1_m;

  /* MinMax: '<S7>/Min3' incorporates:
   *  Constant: '<S7>/Torque_ub'
   */
  tv_B.Min3 = fmin(tv_P.Torque_ub_Value, tv_B.Product);

  /* MATLAB Function: '<S18>/MATLAB Function' incorporates:
   *  Constant: '<S18>/P_max'
   *  Constant: '<S18>/eta'
   *  Constant: '<S2>/WheelSp_FL'
   *  Constant: '<S2>/WheelSp_FR'
   *  Constant: '<S2>/WheelSp_RL'
   *  Constant: '<S2>/WheelSp_RR'
   */
  P_el_total = (((tv_B.Min * tv_P.WheelSp_FL_Value + tv_B.Min1 *
                  tv_P.WheelSp_FR_Value) + tv_B.Min2 * tv_P.WheelSp_RL_Value) +
                tv_B.Min3 * tv_P.WheelSp_RR_Value) / tv_P.eta_Value;
  if (P_el_total > tv_P.P_max_Value) {
    P_el_total = tv_P.P_max_Value / P_el_total;
    tv_B.Trq_FL_scaled = tv_B.Min * P_el_total;
    tv_B.Trq_FR_scaled = tv_B.Min1 * P_el_total;
    tv_B.Trq_RL_scaled = tv_B.Min2 * P_el_total;
    tv_B.Trq_RR_scaled = tv_B.Min3 * P_el_total;
  } else {
    tv_B.Trq_FL_scaled = tv_B.Min;
    tv_B.Trq_FR_scaled = tv_B.Min1;
    tv_B.Trq_RL_scaled = tv_B.Min2;
    tv_B.Trq_RR_scaled = tv_B.Min3;
  }

  /* End of MATLAB Function: '<S18>/MATLAB Function' */

  /* Gain: '<S4>/Trq_FL' */
  tv_B.Trq_FL = tv_P.Trq_FL_Gain * tv_B.Trq_FL_scaled;

  /* Gain: '<S4>/Trq_FR' */
  tv_B.Trq_FR = tv_P.Trq_FR_Gain * tv_B.Trq_FR_scaled;

  /* Gain: '<S4>/Trq_RL' */
  tv_B.Trq_RL = tv_P.Trq_RL_Gain * tv_B.Trq_RL_scaled;

  /* Gain: '<S4>/Trq_RR' */
  tv_B.Trq_RR = tv_P.Trq_RR_Gain * tv_B.Trq_RR_scaled;
  if (rtmIsMajorTimeStep(tv_M)) {
    /* Gain: '<S9>/Gain1' */
    tv_B.Gain1_e = tv_P.Gain1_Gain_f * tv_B.Sum;
  }

  if (rtmIsMajorTimeStep(tv_M)) {
    rt_ertODEUpdateContinuousStates(&tv_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++tv_M->Timing.clockTick0;
    tv_M->Timing.t[0] = rtsiGetSolverStopTime(&tv_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.2s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.2, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      tv_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void tv_derivatives(void)
{
  XDot_tv_T *_rtXdot;
  _rtXdot = ((XDot_tv_T *) tv_M->derivs);

  /* Derivatives for Integrator: '<S9>/Integrator' */
  _rtXdot->Integrator_CSTATE = tv_B.Gain1_e;
}

/* Model initialize function */
void tv_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&tv_M->solverInfo, &tv_M->Timing.simTimeStep);
    rtsiSetTPtr(&tv_M->solverInfo, &rtmGetTPtr(tv_M));
    rtsiSetStepSizePtr(&tv_M->solverInfo, &tv_M->Timing.stepSize0);
    rtsiSetdXPtr(&tv_M->solverInfo, &tv_M->derivs);
    rtsiSetContStatesPtr(&tv_M->solverInfo, (real_T **) &tv_M->contStates);
    rtsiSetNumContStatesPtr(&tv_M->solverInfo, &tv_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&tv_M->solverInfo,
      &tv_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&tv_M->solverInfo,
      &tv_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&tv_M->solverInfo,
      &tv_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&tv_M->solverInfo, (boolean_T**)
      &tv_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&tv_M->solverInfo, (&rtmGetErrorStatus(tv_M)));
    rtsiSetRTModelPtr(&tv_M->solverInfo, tv_M);
  }

  rtsiSetSimTimeStep(&tv_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&tv_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&tv_M->solverInfo, false);
  tv_M->intgData.y = tv_M->odeY;
  tv_M->intgData.f[0] = tv_M->odeF[0];
  tv_M->intgData.f[1] = tv_M->odeF[1];
  tv_M->intgData.f[2] = tv_M->odeF[2];
  tv_M->intgData.f[3] = tv_M->odeF[3];
  tv_M->contStates = ((X_tv_T *) &tv_X);
  tv_M->contStateDisabled = ((XDis_tv_T *) &tv_XDis);
  tv_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&tv_M->solverInfo, (void *)&tv_M->intgData);
  rtsiSetSolverName(&tv_M->solverInfo,"ode4");
  rtmSetTPtr(tv_M, &tv_M->Timing.tArray[0]);
  tv_M->Timing.stepSize0 = 0.2;

  /* InitializeConditions for Integrator: '<S9>/Integrator' */
  tv_X.Integrator_CSTATE = tv_P.Integrator_IC;
}

/* Model terminate function */
void tv_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
