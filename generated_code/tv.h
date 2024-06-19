/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: tv.h
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

#ifndef tv_h_
#define tv_h_
#ifndef tv_COMMON_INCLUDES_
#define tv_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "math.h"
#endif                                 /* tv_COMMON_INCLUDES_ */

#include "tv_types.h"
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
  real_T Plus;                         /* '<S5>/Plus' */
  real_T Gain;                         /* '<S5>/Gain' */
  real_T Gain1;                        /* '<S5>/Gain1' */
  real_T Product;                      /* '<S4>/Product' */
  real_T Square;                       /* '<S4>/Square' */
  real_T Gain1_j;                      /* '<S4>/Gain1' */
  real_T Sum;                          /* '<S4>/Sum' */
  real_T axlebase;                     /* '<S4>/axlebase' */
  real_T Divide;                       /* '<S4>/Divide' */
  real_T Gain1_jl;                     /* '<S9>/Gain1' */
  real_T Gain2;                        /* '<S9>/Gain2' */
  real_T Sum_p;                        /* '<S9>/Sum' */
  real_T Gain_c;                       /* '<S9>/Gain' */
  real_T Gain1_a;                      /* '<S10>/Gain1' */
  real_T Gain2_j;                      /* '<S10>/Gain2' */
  real_T Sum_d;                        /* '<S10>/Sum' */
  real_T Gain_p;                       /* '<S10>/Gain' */
  real_T Gain1_m;                      /* '<S11>/Gain1' */
  real_T Gain2_g;                      /* '<S11>/Gain2' */
  real_T Sum_c;                        /* '<S11>/Sum' */
  real_T Gain_b;                       /* '<S11>/Gain' */
  real_T Gain1_p;                      /* '<S12>/Gain1' */
  real_T Gain2_m;                      /* '<S12>/Gain2' */
  real_T Sum_k;                        /* '<S12>/Sum' */
  real_T Gain_m;                       /* '<S12>/Gain' */
  real_T Gain1_aq;                     /* '<S13>/Gain1' */
  real_T Sum1;                         /* '<S7>/Sum1' */
  real_T Product1;                     /* '<S7>/Product1' */
  real_T Sum_h;                        /* '<S8>/Sum' */
  real_T Gain_g;                       /* '<S8>/Gain' */
  real_T Integrator;                   /* '<S8>/Integrator' */
  real_T Sum1_f;                       /* '<S8>/Sum1' */
  real_T Gain_cd;                      /* '<S13>/Gain' */
  real_T Sum_l;                        /* '<S13>/Sum' */
  real_T Product_k;                    /* '<S13>/Product' */
  real_T Min;                          /* '<S6>/Min' */
  real_T Gain1_e;                      /* '<S14>/Gain1' */
  real_T Gain_k;                       /* '<S14>/Gain' */
  real_T Sum_pk;                       /* '<S14>/Sum' */
  real_T Product_b;                    /* '<S14>/Product' */
  real_T Min1;                         /* '<S6>/Min1' */
  real_T Gain1_g;                      /* '<S16>/Gain1' */
  real_T Gain_j;                       /* '<S16>/Gain' */
  real_T Sum_f;                        /* '<S16>/Sum' */
  real_T Product_h;                    /* '<S16>/Product' */
  real_T Min2;                         /* '<S6>/Min2' */
  real_T Gain1_c;                      /* '<S15>/Gain1' */
  real_T Gain_md;                      /* '<S15>/Gain' */
  real_T Sum_b;                        /* '<S15>/Sum' */
  real_T Product_c;                    /* '<S15>/Product' */
  real_T Min3;                         /* '<S6>/Min3' */
  real_T Gain1_f;                      /* '<S8>/Gain1' */
  real_T Trq_FL;                       /* '<S1>/Trq_FL' */
  real_T Trq_FR;                       /* '<S1>/Trq_FR' */
  real_T Trq_RL;                       /* '<S1>/Trq_RL' */
  real_T Trq_RR;                       /* '<S1>/Trq_RR' */
} B_tv_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S8>/Integrator' */
} X_tv_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S8>/Integrator' */
} XDot_tv_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<S8>/Integrator' */
} XDis_tv_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Parameters (default storage) */
struct P_tv_T_ {
  real_T L;                            /* Variable: L
                                        * Referenced by:
                                        *   '<S4>/axlebase'
                                        *   '<S9>/Gain'
                                        *   '<S10>/Gain'
                                        *   '<S11>/Gain'
                                        *   '<S12>/Gain'
                                        */
  real_T g;                            /* Variable: g
                                        * Referenced by:
                                        *   '<S9>/Constant'
                                        *   '<S10>/Constant'
                                        *   '<S11>/Constant'
                                        *   '<S12>/Constant'
                                        *   '<S13>/Gain1'
                                        *   '<S14>/Gain1'
                                        *   '<S15>/Gain1'
                                        *   '<S16>/Gain1'
                                        */
  real_T h;                            /* Variable: h
                                        * Referenced by:
                                        *   '<S9>/Gain1'
                                        *   '<S9>/Gain2'
                                        *   '<S10>/Gain1'
                                        *   '<S10>/Gain2'
                                        *   '<S11>/Gain1'
                                        *   '<S11>/Gain2'
                                        *   '<S12>/Gain1'
                                        *   '<S12>/Gain2'
                                        */
  real_T lf;                           /* Variable: lf
                                        * Referenced by:
                                        *   '<S11>/Constant'
                                        *   '<S11>/Gain2'
                                        *   '<S12>/Constant'
                                        *   '<S12>/Gain2'
                                        */
  real_T lr;                           /* Variable: lr
                                        * Referenced by:
                                        *   '<S9>/Constant'
                                        *   '<S9>/Gain2'
                                        *   '<S10>/Constant'
                                        *   '<S10>/Gain2'
                                        */
  real_T ls;                           /* Variable: ls
                                        * Referenced by:
                                        *   '<S9>/Gain2'
                                        *   '<S10>/Gain2'
                                        *   '<S11>/Gain2'
                                        *   '<S12>/Gain2'
                                        *   '<S13>/Gain'
                                        *   '<S14>/Gain'
                                        *   '<S15>/Gain'
                                        *   '<S16>/Gain'
                                        */
  real_T m;                            /* Variable: m
                                        * Referenced by:
                                        *   '<S9>/Gain'
                                        *   '<S10>/Gain'
                                        *   '<S11>/Gain'
                                        *   '<S12>/Gain'
                                        *   '<S13>/Gain1'
                                        *   '<S14>/Gain1'
                                        *   '<S15>/Gain1'
                                        *   '<S16>/Gain1'
                                        */
  real_T rw;                           /* Variable: rw
                                        * Referenced by:
                                        *   '<S5>/Gain1'
                                        *   '<S13>/Gain'
                                        *   '<S14>/Gain'
                                        *   '<S15>/Gain'
                                        *   '<S16>/Gain'
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
  real_T acc_pedal_Value;              /* Expression: 1
                                        * Referenced by: '<S2>/acc_pedal'
                                        */
  real_T ax_Value;                     /* Expression: 1
                                        * Referenced by: '<S2>/ax'
                                        */
  real_T ay_Value;                     /* Expression: 1
                                        * Referenced by: '<S2>/ay'
                                        */
  real_T brake_pedal_Value;            /* Expression: 1
                                        * Referenced by: '<S2>/brake_pedal'
                                        */
  real_T delta_Value;                  /* Expression: 1
                                        * Referenced by: '<S2>/delta'
                                        */
  real_T yaw_rate_Value;               /* Expression: 1
                                        * Referenced by: '<S2>/yaw_rate'
                                        */
  real_T Constant_Value;               /* Expression: 1
                                        * Referenced by: '<S4>/Constant'
                                        */
  real_T Gain_Gain;                    /* Expression: 1/4
                                        * Referenced by: '<S5>/Gain'
                                        */
  real_T Gain1_Gain;                   /* Expression: 1/2500
                                        * Referenced by: '<S4>/Gain1'
                                        */
  real_T Torque_ub_Value;              /* Expression: 21
                                        * Referenced by: '<S6>/Torque_ub'
                                        */
  real_T Constant1_Value;              /* Expression: 84
                                        * Referenced by: '<S7>/Constant1'
                                        */
  real_T Gain_Gain_i;                  /* Expression: 0.5
                                        * Referenced by: '<S8>/Gain'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<S8>/Integrator'
                                        */
  real_T Gain1_Gain_o;                 /* Expression: 0.05
                                        * Referenced by: '<S8>/Gain1'
                                        */
  real_T Trq_FL_Gain;                  /* Expression: 1
                                        * Referenced by: '<S1>/Trq_FL'
                                        */
  real_T Trq_FR_Gain;                  /* Expression: 1
                                        * Referenced by: '<S1>/Trq_FR'
                                        */
  real_T Trq_RL_Gain;                  /* Expression: 1
                                        * Referenced by: '<S1>/Trq_RL'
                                        */
  real_T Trq_RR_Gain;                  /* Expression: 1
                                        * Referenced by: '<S1>/Trq_RR'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_tv_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_tv_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_tv_T *contStateDisabled;
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
extern P_tv_T tv_P;

/* Block signals (default storage) */
extern B_tv_T tv_B;

/* Continuous states (default storage) */
extern X_tv_T tv_X;

/* Disabled states (default storage) */
extern XDis_tv_T tv_XDis;

/* Model entry point functions */
extern void tv_initialize(void);
extern void tv_step(void);
extern void tv_terminate(void);

/* Real-time Model object */
extern RT_MODEL_tv_T *const tv_M;

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
 * '<Root>' : 'tv'
 * '<S1>'   : 'tv/TorqueVectoring'
 * '<S2>'   : 'tv/TorqueVectoring/CarMaker_Inputs'
 * '<S3>'   : 'tv/TorqueVectoring/TorqueVectoring'
 * '<S4>'   : 'tv/TorqueVectoring/TorqueVectoring/Reference generator'
 * '<S5>'   : 'tv/TorqueVectoring/TorqueVectoring/Speed estimaor'
 * '<S6>'   : 'tv/TorqueVectoring/TorqueVectoring/Torque distribution'
 * '<S7>'   : 'tv/TorqueVectoring/TorqueVectoring/Total Torque Request'
 * '<S8>'   : 'tv/TorqueVectoring/TorqueVectoring/Upper Controller'
 * '<S9>'   : 'tv/TorqueVectoring/TorqueVectoring/Torque distribution/Fzfl'
 * '<S10>'  : 'tv/TorqueVectoring/TorqueVectoring/Torque distribution/Fzfr'
 * '<S11>'  : 'tv/TorqueVectoring/TorqueVectoring/Torque distribution/Fzrl'
 * '<S12>'  : 'tv/TorqueVectoring/TorqueVectoring/Torque distribution/Fzrr'
 * '<S13>'  : 'tv/TorqueVectoring/TorqueVectoring/Torque distribution/T_FL'
 * '<S14>'  : 'tv/TorqueVectoring/TorqueVectoring/Torque distribution/T_FR'
 * '<S15>'  : 'tv/TorqueVectoring/TorqueVectoring/Torque distribution/T_FR1'
 * '<S16>'  : 'tv/TorqueVectoring/TorqueVectoring/Torque distribution/T_RL'
 */
#endif                                 /* tv_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
