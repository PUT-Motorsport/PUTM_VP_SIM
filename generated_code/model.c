/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: model.c
 *
 * Code generated for Simulink model 'model'.
 *
 * Model version                  : 1.13
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Tue Jun 25 15:58:24 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "model.h"
#include "rtwtypes.h"
#include "model_private.h"

/* Block signals (default storage) */
B_model_T model_B;

/* Continuous states */
X_model_T model_X;

/* Disabled State Vector */
XDis_model_T model_XDis;

/* Real-time model */
static RT_MODEL_model_T model_M_;
RT_MODEL_model_T *const model_M = &model_M_;

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
  model_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  model_step();
  model_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  model_step();
  model_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  model_step();
  model_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void model_step(void)
{
  real_T rtb_Sum_p;
  if (rtmIsMajorTimeStep(model_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&model_M->solverInfo,((model_M->Timing.clockTick0+1)*
      model_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(model_M)) {
    model_M->Timing.t[0] = rtsiGetT(&model_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(model_M)) {
    /* Gain: '<S6>/Gain1' incorporates:
     *  Constant: '<S2>/WheelSp_FL'
     *  Constant: '<S2>/WheelSp_FR'
     *  Constant: '<S2>/WheelSp_RL'
     *  Constant: '<S2>/WheelSp_RR'
     *  Gain: '<S6>/Gain'
     *  Sum: '<S6>/Plus'
     */
    rtb_Sum_p = (((model_P.WheelSp_FL_Value + model_P.WheelSp_FR_Value) +
                  model_P.WheelSp_RL_Value) + model_P.WheelSp_RR_Value) *
      model_P.Gain_Gain * model_P.rw;

    /* Gain: '<S9>/Gain1' incorporates:
     *  Constant: '<S2>/delta'
     *  Constant: '<S2>/yaw_rate'
     *  Constant: '<S5>/Constant'
     *  Gain: '<S5>/Gain1'
     *  Gain: '<S5>/axlebase'
     *  Math: '<S5>/Square'
     *  Product: '<S5>/Divide'
     *  Product: '<S5>/Product'
     *  Sum: '<S5>/Sum'
     *  Sum: '<S9>/Sum'
     */
    model_B.Gain1_m = (model_P.yaw_rate_Value * rtb_Sum_p / ((rtb_Sum_p *
      rtb_Sum_p * model_P.Gain1_Gain + model_P.Constant_Value) * model_P.L) -
                       model_P.delta_Value) * model_P.Gain1_Gain_p;
  }

  if (rtmIsMajorTimeStep(model_M)) {
    rt_ertODEUpdateContinuousStates(&model_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++model_M->Timing.clockTick0;
    model_M->Timing.t[0] = rtsiGetSolverStopTime(&model_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.2s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.2, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      model_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void model_derivatives(void)
{
  XDot_model_T *_rtXdot;
  _rtXdot = ((XDot_model_T *) model_M->derivs);

  /* Derivatives for Integrator: '<S9>/Integrator' */
  _rtXdot->Integrator_CSTATE = model_B.Gain1_m;
}

/* Model initialize function */
void model_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&model_M->solverInfo, &model_M->Timing.simTimeStep);
    rtsiSetTPtr(&model_M->solverInfo, &rtmGetTPtr(model_M));
    rtsiSetStepSizePtr(&model_M->solverInfo, &model_M->Timing.stepSize0);
    rtsiSetdXPtr(&model_M->solverInfo, &model_M->derivs);
    rtsiSetContStatesPtr(&model_M->solverInfo, (real_T **) &model_M->contStates);
    rtsiSetNumContStatesPtr(&model_M->solverInfo, &model_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&model_M->solverInfo,
      &model_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&model_M->solverInfo,
      &model_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&model_M->solverInfo,
      &model_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&model_M->solverInfo, (boolean_T**)
      &model_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&model_M->solverInfo, (&rtmGetErrorStatus(model_M)));
    rtsiSetRTModelPtr(&model_M->solverInfo, model_M);
  }

  rtsiSetSimTimeStep(&model_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&model_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&model_M->solverInfo, false);
  model_M->intgData.y = model_M->odeY;
  model_M->intgData.f[0] = model_M->odeF[0];
  model_M->intgData.f[1] = model_M->odeF[1];
  model_M->intgData.f[2] = model_M->odeF[2];
  model_M->intgData.f[3] = model_M->odeF[3];
  model_M->contStates = ((X_model_T *) &model_X);
  model_M->contStateDisabled = ((XDis_model_T *) &model_XDis);
  model_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&model_M->solverInfo, (void *)&model_M->intgData);
  rtsiSetSolverName(&model_M->solverInfo,"ode4");
  rtmSetTPtr(model_M, &model_M->Timing.tArray[0]);
  model_M->Timing.stepSize0 = 0.2;

  /* InitializeConditions for Integrator: '<S9>/Integrator' */
  model_X.Integrator_CSTATE = model_P.Integrator_IC;
}

/* Model terminate function */
void model_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
