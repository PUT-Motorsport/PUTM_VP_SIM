/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: tv.c
 *
 * Code generated for Simulink model 'tv'.
 *
 * Model version                  : 1.19
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Mon Jun 17 15:23:14 2024
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

static void read_values()
{
  tv_P.WheelSp_FL_Value = 0;
  tv_P.WheelSp_FR_Value = 0;
  tv_P.WheelSp_RL_Value = 0;
  tv_P.WheelSp_RR_Value = 0;
  tv_P.acc_pedal_Value = 0; // Acceleration pedal 0-1
  tv_P.ax_Value = 0;
  tv_P.ay_Value = 0;
  tv_P.brake_pedal_Value = 0; // Brake pedal 0-1
  tv_P.delta_Value = 0; // Steering angle
  tv_P.yaw_rate_Value = 0;
}
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si)
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
  rtsiSetSimTimeStep(si, MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void)memcpy(y, x,
               (uint_T)nXc * sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  tv_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++)
  {
    x[i] = y[i] + (temp * f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  tv_step();
  tv_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++)
  {
    x[i] = y[i] + (temp * f1[i]);
  }

  rtsiSetdX(si, f2);
  tv_step();
  tv_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++)
  {
    x[i] = y[i] + (h * f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  tv_step();
  tv_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++)
  {
    x[i] = y[i] + temp * (f0[i] + 2.0 * f1[i] + 2.0 * f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si, MAJOR_TIME_STEP);
}

/* Model step function */
void tv_step(void)
{
  real_T Gain1_jl_tmp;
  real_T Gain2_tmp;
  real_T Sum_p_tmp;
  real_T minV_tmp;
  real_T minV_tmp_0;
  if (rtmIsMajorTimeStep(tv_M))
  {
    /* set solver stop time */
    rtsiSetSolverStopTime(&tv_M->solverInfo, ((tv_M->Timing.clockTick0 + 1) *
                                              tv_M->Timing.stepSize0));
  } /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(tv_M))
  {
    tv_M->Timing.t[0] = rtsiGetT(&tv_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(tv_M))
  {
    /* Sum: '<S5>/Plus' incorporates:
     *  Constant: '<S2>/WheelSp_FL'
     *  Constant: '<S2>/WheelSp_FR'
     *  Constant: '<S2>/WheelSp_RL'
     *  Constant: '<S2>/WheelSp_RR'
     */
    tv_B.Plus = ((tv_P.WheelSp_FL_Value + tv_P.WheelSp_FR_Value) +
                 tv_P.WheelSp_RL_Value) +
                tv_P.WheelSp_RR_Value;

    /* Gain: '<S5>/Gain' */
    tv_B.Gain = tv_P.Gain_Gain * tv_B.Plus;

    /* Gain: '<S5>/Gain1' */
    tv_B.Gain1 = tv_P.rw * tv_B.Gain;

    /* Product: '<S4>/Product' incorporates:
     *  Constant: '<S2>/yaw_rate'
     */
    tv_B.Product = tv_P.yaw_rate_Value * tv_B.Gain1;

    /* Math: '<S4>/Square' */
    tv_B.Square = tv_B.Gain1 * tv_B.Gain1;

    /* Gain: '<S4>/Gain1' */
    tv_B.Gain1_j = tv_P.Gain1_Gain * tv_B.Square;

    /* Sum: '<S4>/Sum' incorporates:
     *  Constant: '<S4>/Constant'
     */
    tv_B.Sum = tv_P.Constant_Value + tv_B.Gain1_j;

    /* Gain: '<S4>/axlebase' */
    tv_B.axlebase = tv_P.L * tv_B.Sum;

    /* Product: '<S4>/Divide' */
    tv_B.Divide = tv_B.Product / tv_B.axlebase;

    /* Gain: '<S9>/Gain1' incorporates:
     *  Constant: '<S2>/ax'
     *  Gain: '<S10>/Gain1'
     *  Gain: '<S11>/Gain1'
     *  Gain: '<S12>/Gain1'
     */
    Gain1_jl_tmp = tv_P.h * tv_P.ax_Value;

    /* Gain: '<S9>/Gain1' */
    tv_B.Gain1_jl = Gain1_jl_tmp;

    /* Gain: '<S9>/Gain2' incorporates:
     *  Constant: '<S2>/ay'
     *  Gain: '<S10>/Gain2'
     */
    minV_tmp_0 = tv_P.h * tv_P.lr / tv_P.ls;
    Gain2_tmp = minV_tmp_0 * tv_P.ay_Value;

    /* Gain: '<S9>/Gain2' */
    tv_B.Gain2 = Gain2_tmp;

    /* Sum: '<S9>/Sum' incorporates:
     *  Constant: '<S10>/Constant'
     *  Constant: '<S9>/Constant'
     *  Sum: '<S10>/Sum'
     */
    minV_tmp_0 = tv_P.g * tv_P.lr;
    Sum_p_tmp = minV_tmp_0 - tv_B.Gain1_jl;

    /* Sum: '<S9>/Sum' */
    tv_B.Sum_p = Sum_p_tmp - tv_B.Gain2;

    /* Gain: '<S9>/Gain' incorporates:
     *  Gain: '<S10>/Gain'
     *  Gain: '<S11>/Gain'
     *  Gain: '<S12>/Gain'
     */
    minV_tmp = tv_P.m / (2.0 * tv_P.L);
    minV_tmp_0 = minV_tmp;

    /* Gain: '<S9>/Gain' */
    tv_B.Gain_c = minV_tmp_0 * tv_B.Sum_p;

    /* Gain: '<S10>/Gain1' */
    tv_B.Gain1_a = Gain1_jl_tmp;

    /* Gain: '<S10>/Gain2' */
    tv_B.Gain2_j = Gain2_tmp;

    /* Sum: '<S10>/Sum' */
    tv_B.Sum_d = Sum_p_tmp + tv_B.Gain2_j;

    /* Gain: '<S10>/Gain' */
    tv_B.Gain_p = minV_tmp_0 * tv_B.Sum_d;

    /* Gain: '<S11>/Gain1' */
    tv_B.Gain1_m = Gain1_jl_tmp;

    /* Gain: '<S11>/Gain2' incorporates:
     *  Constant: '<S2>/ay'
     *  Gain: '<S12>/Gain2'
     */
    minV_tmp_0 = tv_P.h * tv_P.lf / tv_P.ls;
    Gain2_tmp = minV_tmp_0 * tv_P.ay_Value;

    /* Gain: '<S11>/Gain2' */
    tv_B.Gain2_g = Gain2_tmp;

    /* Sum: '<S11>/Sum' incorporates:
     *  Constant: '<S11>/Constant'
     *  Constant: '<S12>/Constant'
     *  Sum: '<S12>/Sum'
     */
    minV_tmp_0 = tv_P.g * tv_P.lf;
    Sum_p_tmp = minV_tmp_0 + tv_B.Gain1_m;

    /* Sum: '<S11>/Sum' */
    tv_B.Sum_c = Sum_p_tmp - tv_B.Gain2_g;

    /* Gain: '<S11>/Gain' */
    minV_tmp_0 = minV_tmp;

    /* Gain: '<S11>/Gain' */
    tv_B.Gain_b = minV_tmp_0 * tv_B.Sum_c;

    /* Gain: '<S12>/Gain1' */
    tv_B.Gain1_p = Gain1_jl_tmp;

    /* Gain: '<S12>/Gain2' */
    tv_B.Gain2_m = Gain2_tmp;

    /* Sum: '<S12>/Sum' */
    tv_B.Sum_k = Sum_p_tmp + tv_B.Gain2_m;

    /* Gain: '<S12>/Gain' */
    tv_B.Gain_m = minV_tmp_0 * tv_B.Sum_k;

    /* Gain: '<S13>/Gain1' */
    minV_tmp_0 = 1.0 / (tv_P.m * tv_P.g);

    /* Gain: '<S13>/Gain1' */
    tv_B.Gain1_aq = minV_tmp_0 * tv_B.Gain_c;

    /* Sum: '<S7>/Sum1' incorporates:
     *  Constant: '<S2>/acc_pedal'
     *  Constant: '<S2>/brake_pedal'
     */
    tv_B.Sum1 = tv_P.acc_pedal_Value - tv_P.brake_pedal_Value;

    /* Product: '<S7>/Product1' incorporates:
     *  Constant: '<S7>/Constant1'
     */
    tv_B.Product1 = tv_P.Constant1_Value * tv_B.Sum1;

    /* Sum: '<S8>/Sum' incorporates:
     *  Constant: '<S2>/delta'
     */
    tv_B.Sum_h = tv_B.Divide - tv_P.delta_Value;

    /* Gain: '<S8>/Gain' */
    tv_B.Gain_g = tv_P.Gain_Gain_i * tv_B.Sum_h;
  }

  /* Integrator: '<S8>/Integrator' */
  tv_B.Integrator = tv_X.Integrator_CSTATE;

  /* Sum: '<S8>/Sum1' */
  tv_B.Sum1_f = tv_B.Gain_g + tv_B.Integrator;

  /* Gain: '<S13>/Gain' incorporates:
   *  Gain: '<S14>/Gain'
   *  Gain: '<S15>/Gain'
   *  Gain: '<S16>/Gain'
   */
  minV_tmp_0 = tv_P.rw / tv_P.ls;
  Gain1_jl_tmp = minV_tmp_0 * tv_B.Sum1_f;

  /* Gain: '<S13>/Gain' */
  tv_B.Gain_cd = Gain1_jl_tmp;

  /* Sum: '<S13>/Sum' incorporates:
   *  Sum: '<S16>/Sum'
   */
  minV_tmp = tv_B.Product1 - tv_B.Gain_cd;

  /* Sum: '<S13>/Sum' */
  tv_B.Sum_l = minV_tmp;

  /* Product: '<S13>/Product' */
  tv_B.Product_k = tv_B.Gain1_aq * tv_B.Sum_l;

  /* MinMax: '<S6>/Min' incorporates:
   *  Constant: '<S6>/Torque_ub'
   */
  minV_tmp_0 = fmin(tv_P.Torque_ub_Value, tv_B.Product_k);

  /* MinMax: '<S6>/Min' */
  tv_B.Min = minV_tmp_0;
  if (rtmIsMajorTimeStep(tv_M))
  {
    /* Gain: '<S14>/Gain1' */
    minV_tmp_0 = 1.0 / (tv_P.m * tv_P.g);

    /* Gain: '<S14>/Gain1' */
    tv_B.Gain1_e = minV_tmp_0 * tv_B.Gain_p;
  }

  /* Gain: '<S14>/Gain' */
  tv_B.Gain_k = Gain1_jl_tmp;

  /* Sum: '<S14>/Sum' incorporates:
   *  Sum: '<S15>/Sum'
   */
  Gain2_tmp = tv_B.Product1 + tv_B.Gain_k;

  /* Sum: '<S14>/Sum' */
  tv_B.Sum_pk = Gain2_tmp;

  /* Product: '<S14>/Product' */
  tv_B.Product_b = tv_B.Gain1_e * tv_B.Sum_pk;

  /* MinMax: '<S6>/Min1' incorporates:
   *  Constant: '<S6>/Torque_ub'
   */
  minV_tmp_0 = fmin(tv_P.Torque_ub_Value, tv_B.Product_b);

  /* MinMax: '<S6>/Min1' */
  tv_B.Min1 = minV_tmp_0;
  if (rtmIsMajorTimeStep(tv_M))
  {
    /* Gain: '<S16>/Gain1' */
    minV_tmp_0 = 1.0 / (tv_P.m * tv_P.g);

    /* Gain: '<S16>/Gain1' */
    tv_B.Gain1_g = minV_tmp_0 * tv_B.Gain_b;
  }

  /* Gain: '<S16>/Gain' */
  tv_B.Gain_j = Gain1_jl_tmp;

  /* Sum: '<S16>/Sum' */
  tv_B.Sum_f = minV_tmp;

  /* Product: '<S16>/Product' */
  tv_B.Product_h = tv_B.Gain1_g * tv_B.Sum_f;

  /* MinMax: '<S6>/Min2' incorporates:
   *  Constant: '<S6>/Torque_ub'
   */
  minV_tmp_0 = fmin(tv_P.Torque_ub_Value, tv_B.Product_h);

  /* MinMax: '<S6>/Min2' */
  tv_B.Min2 = minV_tmp_0;
  if (rtmIsMajorTimeStep(tv_M))
  {
    /* Gain: '<S15>/Gain1' */
    minV_tmp_0 = 1.0 / (tv_P.m * tv_P.g);

    /* Gain: '<S15>/Gain1' */
    tv_B.Gain1_c = minV_tmp_0 * tv_B.Gain_m;

    /* Gain: '<S8>/Gain1' */
    tv_B.Gain1_f = tv_P.Gain1_Gain_o * tv_B.Sum_h;
  }

  /* Gain: '<S15>/Gain' */
  tv_B.Gain_md = Gain1_jl_tmp;

  /* Sum: '<S15>/Sum' */
  tv_B.Sum_b = Gain2_tmp;

  /* Product: '<S15>/Product' */
  tv_B.Product_c = tv_B.Gain1_c * tv_B.Sum_b;

  /* MinMax: '<S6>/Min3' incorporates:
   *  Constant: '<S6>/Torque_ub'
   */
  minV_tmp_0 = fmin(tv_P.Torque_ub_Value, tv_B.Product_c);

  /* MinMax: '<S6>/Min3' */
  tv_B.Min3 = minV_tmp_0;

  /* Gain: '<S1>/Trq_FL' */
  tv_B.Trq_FL = tv_P.Trq_FL_Gain * tv_B.Min;

  /* Gain: '<S1>/Trq_FR' */
  tv_B.Trq_FR = tv_P.Trq_FR_Gain * tv_B.Min1;

  /* Gain: '<S1>/Trq_RL' */
  tv_B.Trq_RL = tv_P.Trq_RL_Gain * tv_B.Min2;

  /* Gain: '<S1>/Trq_RR' */
  tv_B.Trq_RR = tv_P.Trq_RR_Gain * tv_B.Min3;
  if (rtmIsMajorTimeStep(tv_M))
  {
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
  } /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void tv_derivatives(void)
{
  XDot_tv_T *_rtXdot;
  _rtXdot = ((XDot_tv_T *)tv_M->derivs);

  /* Derivatives for Integrator: '<S8>/Integrator' */
  _rtXdot->Integrator_CSTATE = tv_B.Gain1_f;
}

/* Model initialize function */
void tv_initialize(void)
{
  read_values();
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&tv_M->solverInfo, &tv_M->Timing.simTimeStep);
    rtsiSetTPtr(&tv_M->solverInfo, &rtmGetTPtr(tv_M));
    rtsiSetStepSizePtr(&tv_M->solverInfo, &tv_M->Timing.stepSize0);
    rtsiSetdXPtr(&tv_M->solverInfo, &tv_M->derivs);
    rtsiSetContStatesPtr(&tv_M->solverInfo, (real_T **)&tv_M->contStates);
    rtsiSetNumContStatesPtr(&tv_M->solverInfo, &tv_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&tv_M->solverInfo,
                                    &tv_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&tv_M->solverInfo,
                                       &tv_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&tv_M->solverInfo,
                                      &tv_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&tv_M->solverInfo, (boolean_T **)&tv_M->contStateDisabled);
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
  tv_M->contStates = ((X_tv_T *)&tv_X);
  tv_M->contStateDisabled = ((XDis_tv_T *)&tv_XDis);
  tv_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&tv_M->solverInfo, (void *)&tv_M->intgData);
  rtsiSetSolverName(&tv_M->solverInfo, "ode4");
  rtmSetTPtr(tv_M, &tv_M->Timing.tArray[0]);
  tv_M->Timing.stepSize0 = 0.2;

  /* InitializeConditions for Integrator: '<S8>/Integrator' */
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
