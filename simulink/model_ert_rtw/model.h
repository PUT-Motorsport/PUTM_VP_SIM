/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: model.h
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

#ifndef model_h_
#define model_h_
#ifndef model_COMMON_INCLUDES_
#define model_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "math.h"
#endif                                 /* model_COMMON_INCLUDES_ */

#include "model_types.h"
#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Gain1_m;                      /* '<S9>/Gain1' */
} B_model_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S9>/Integrator' */
} X_model_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S9>/Integrator' */
} XDot_model_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<S9>/Integrator' */
} XDis_model_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Parameters (default storage) */
struct P_model_T_ {
  real_T L;                            /* Variable: L
                                        * Referenced by:
                                        *   '<S5>/axlebase'
                                        *   '<S10>/Gain'
                                        *   '<S11>/Gain'
                                        *   '<S12>/Gain'
                                        *   '<S13>/Gain'
                                        */
  real_T g;                            /* Variable: g
                                        * Referenced by:
                                        *   '<S10>/Constant'
                                        *   '<S11>/Constant'
                                        *   '<S12>/Constant'
                                        *   '<S13>/Constant'
                                        *   '<S14>/Gain1'
                                        *   '<S15>/Gain1'
                                        *   '<S16>/Gain1'
                                        *   '<S17>/Gain1'
                                        */
  real_T h;                            /* Variable: h
                                        * Referenced by:
                                        *   '<S10>/Gain1'
                                        *   '<S10>/Gain2'
                                        *   '<S11>/Gain1'
                                        *   '<S11>/Gain2'
                                        *   '<S12>/Gain1'
                                        *   '<S12>/Gain2'
                                        *   '<S13>/Gain1'
                                        *   '<S13>/Gain2'
                                        */
  real_T lf;                           /* Variable: lf
                                        * Referenced by:
                                        *   '<S12>/Constant'
                                        *   '<S12>/Gain2'
                                        *   '<S13>/Constant'
                                        *   '<S13>/Gain2'
                                        */
  real_T lr;                           /* Variable: lr
                                        * Referenced by:
                                        *   '<S10>/Constant'
                                        *   '<S10>/Gain2'
                                        *   '<S11>/Constant'
                                        *   '<S11>/Gain2'
                                        */
  real_T ls;                           /* Variable: ls
                                        * Referenced by:
                                        *   '<S10>/Gain2'
                                        *   '<S11>/Gain2'
                                        *   '<S12>/Gain2'
                                        *   '<S13>/Gain2'
                                        *   '<S14>/Gain'
                                        *   '<S15>/Gain'
                                        *   '<S16>/Gain'
                                        *   '<S17>/Gain'
                                        */
  real_T m;                            /* Variable: m
                                        * Referenced by:
                                        *   '<S10>/Gain'
                                        *   '<S11>/Gain'
                                        *   '<S12>/Gain'
                                        *   '<S13>/Gain'
                                        *   '<S14>/Gain1'
                                        *   '<S15>/Gain1'
                                        *   '<S16>/Gain1'
                                        *   '<S17>/Gain1'
                                        */
  real_T rw;                           /* Variable: rw
                                        * Referenced by:
                                        *   '<S6>/Gain1'
                                        *   '<S14>/Gain'
                                        *   '<S15>/Gain'
                                        *   '<S16>/Gain'
                                        *   '<S17>/Gain'
                                        */
  real_T WheelSp_FL_Value;             /* Expression: 1
                                        * Referenced by: '<S2>/WheelSp_FL'
                                        */
  real_T WheelSp_FR_Value;             /* Expression: 1
                                        * Referenced by: '<S2>/WheelSp_FR'
                                        */
  real_T WheelSp_RL_Value;             /* Expression: 1
                                        * Referenced by: '<S2>/WheelSp_RL'
                                        */
  real_T WheelSp_RR_Value;             /* Expression: 1
                                        * Referenced by: '<S2>/WheelSp_RR'
                                        */
  real_T Gain_Gain;                    /* Expression: 1/4
                                        * Referenced by: '<S6>/Gain'
                                        */
  real_T yaw_rate_Value;               /* Expression: 1
                                        * Referenced by: '<S2>/yaw_rate'
                                        */
  real_T Constant_Value;               /* Expression: 1
                                        * Referenced by: '<S5>/Constant'
                                        */
  real_T Gain1_Gain;                   /* Expression: 1/2500
                                        * Referenced by: '<S5>/Gain1'
                                        */
  real_T delta_Value;                  /* Expression: 1
                                        * Referenced by: '<S2>/delta'
                                        */
  real_T Gain_Gain_j;                  /* Expression: 0.5
                                        * Referenced by: '<S9>/Gain'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<S9>/Integrator'
                                        */
  real_T Constant1_Value;              /* Expression: 84
                                        * Referenced by: '<S8>/Constant1'
                                        */
  real_T acc_pedal_Value;              /* Expression: 1
                                        * Referenced by: '<S2>/acc_pedal'
                                        */
  real_T brake_pedal_Value;            /* Expression: 1
                                        * Referenced by: '<S2>/brake_pedal'
                                        */
  real_T ax_Value;                     /* Expression: 1
                                        * Referenced by: '<S2>/ax'
                                        */
  real_T ay_Value;                     /* Expression: 1
                                        * Referenced by: '<S2>/ay'
                                        */
  real_T Torque_ub_Value;              /* Expression: 21
                                        * Referenced by: '<S7>/Torque_ub'
                                        */
  real_T Trq_FL_Gain;                  /* Expression: 1
                                        * Referenced by: '<S4>/Trq_FL'
                                        */
  real_T Trq_FR_Gain;                  /* Expression: 1
                                        * Referenced by: '<S4>/Trq_FR'
                                        */
  real_T Trq_RL_Gain;                  /* Expression: 1
                                        * Referenced by: '<S4>/Trq_RL'
                                        */
  real_T Trq_RR_Gain;                  /* Expression: 1
                                        * Referenced by: '<S4>/Trq_RR'
                                        */
  real_T Gain1_Gain_p;                 /* Expression: 0.05
                                        * Referenced by: '<S9>/Gain1'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_model_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_model_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_model_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[1];
  real_T odeF[4][1];
  ODE4_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    time_T tStart;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_model_T model_P;

/* Block signals (default storage) */
extern B_model_T model_B;

/* Continuous states (default storage) */
extern X_model_T model_X;

/* Disabled states (default storage) */
extern XDis_model_T model_XDis;

/* Model entry point functions */
extern void model_initialize(void);
extern void model_step(void);
extern void model_terminate(void);

/* Real-time Model object */
extern RT_MODEL_model_T *const model_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'model'
 * '<S1>'   : 'model/TorqueVectoring'
 * '<S2>'   : 'model/TorqueVectoring/CarMaker_Inputs'
 * '<S3>'   : 'model/TorqueVectoring/TorqueVectoring'
 * '<S4>'   : 'model/TorqueVectoring/power_limiter_system'
 * '<S5>'   : 'model/TorqueVectoring/TorqueVectoring/Reference generator'
 * '<S6>'   : 'model/TorqueVectoring/TorqueVectoring/Speed estimaor'
 * '<S7>'   : 'model/TorqueVectoring/TorqueVectoring/Torque distribution'
 * '<S8>'   : 'model/TorqueVectoring/TorqueVectoring/Total Torque Request'
 * '<S9>'   : 'model/TorqueVectoring/TorqueVectoring/Upper Controller'
 * '<S10>'  : 'model/TorqueVectoring/TorqueVectoring/Torque distribution/Fzfl'
 * '<S11>'  : 'model/TorqueVectoring/TorqueVectoring/Torque distribution/Fzfr'
 * '<S12>'  : 'model/TorqueVectoring/TorqueVectoring/Torque distribution/Fzrl'
 * '<S13>'  : 'model/TorqueVectoring/TorqueVectoring/Torque distribution/Fzrr'
 * '<S14>'  : 'model/TorqueVectoring/TorqueVectoring/Torque distribution/T_FL'
 * '<S15>'  : 'model/TorqueVectoring/TorqueVectoring/Torque distribution/T_FR'
 * '<S16>'  : 'model/TorqueVectoring/TorqueVectoring/Torque distribution/T_FR1'
 * '<S17>'  : 'model/TorqueVectoring/TorqueVectoring/Torque distribution/T_RL'
 */
#endif                                 /* model_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
