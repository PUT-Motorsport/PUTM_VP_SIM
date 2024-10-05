/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: tv_code.h
 *
 * Code generated for Simulink model 'tv_code'.
 *
 * Model version                  : 1.12
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Sat Oct  5 19:47:47 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_tv_code_h_
#define RTW_HEADER_tv_code_h_
#ifndef tv_code_COMMON_INCLUDES_
#define tv_code_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* tv_code_COMMON_INCLUDES_ */

#include "tv_code_types.h"
#include "rtGetInf.h"
#include <string.h>
#include "rt_nonfinite.h"

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

/* Block signals (default storage) */
typedef struct {
  real_T Product1;                     /* '<S8>/Product1' */
  real_T Saturation[4];                /* '<S6>/Saturation' */
  real_T Gain1;                        /* '<S5>/Gain1' */
  real_T Switch;                       /* '<S7>/Switch' */
  real_T Gain1_o;                      /* '<S14>/Gain1' */
  real_T DotProduct;                   /* '<S9>/Dot Product' */
  real_T Integrator;                   /* '<S9>/Integrator' */
  real_T Gain1_l;                      /* '<S15>/Gain1' */
  real_T Gain1_lh;                     /* '<S17>/Gain1' */
  real_T Gain1_j;                      /* '<S16>/Gain1' */
  real_T trq_fl;                       /* '<Root>/trq_fl' */
  real_T trq_fr;                       /* '<Root>/trq_fr' */
  real_T trq_rl;                       /* '<Root>/trq_rl' */
  real_T trq_rr;                       /* '<Root>/trq_rr' */
  real_T DotProduct1;                  /* '<S9>/Dot Product1' */
  real_T DotProduct_a;                 /* '<S7>/Dot Product' */
  real_T DotProduct1_f;                /* '<S7>/Dot Product1' */
  real_T DotProduct2;                  /* '<S7>/Dot Product2' */
  real_T DotProduct3;                  /* '<S7>/Dot Product3' */
  real_T Switch_b[4];                  /* '<S3>/Switch' */
  real_T Sum;                          /* '<S9>/Sum' */
  real_T Saturation3;                  /* '<S7>/Saturation3' */
  real_T Gain;                         /* '<S13>/Gain' */
  real_T Saturation2;                  /* '<S7>/Saturation2' */
  real_T Gain2;                        /* '<S13>/Gain2' */
} B_tv_code_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S9>/Integrator' */
} X_tv_code_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S9>/Integrator' */
} XDot_tv_code_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<S9>/Integrator' */
} XDis_tv_code_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Parameters (default storage) */
struct P_tv_code_T_ {
  real_T Ku;                           /* Variable: Ku
                                        * Referenced by: '<S4>/Desired Understeer Gradient'
                                        */
  real_T L;                            /* Variable: L
                                        * Referenced by:
                                        *   '<S4>/axlebase'
                                        *   '<S10>/Gain'
                                        *   '<S11>/Gain'
                                        *   '<S12>/Gain'
                                        *   '<S13>/Gain'
                                        */
  real_T Mz_I;                         /* Variable: Mz_I
                                        * Referenced by: '<S2>/Mz Integative Gain'
                                        */
  real_T Mz_p;                         /* Variable: Mz_p
                                        * Referenced by: '<S2>/Mz Proportional Gain'
                                        */
  real_T drive_ratio;                  /* Variable: drive_ratio
                                        * Referenced by:
                                        *   '<S7>/Saturation'
                                        *   '<S7>/Saturation1'
                                        *   '<S7>/Saturation2'
                                        *   '<S7>/Saturation3'
                                        *   '<S8>/Constant1'
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
  real_T max_moment;                   /* Variable: max_moment
                                        * Referenced by:
                                        *   '<S7>/Saturation'
                                        *   '<S7>/Saturation1'
                                        *   '<S7>/Saturation2'
                                        *   '<S7>/Saturation3'
                                        *   '<S8>/Constant1'
                                        */
  real_T rw;                           /* Variable: rw
                                        * Referenced by:
                                        *   '<S5>/Gain1'
                                        *   '<S14>/Gain'
                                        *   '<S15>/Gain'
                                        *   '<S16>/Gain'
                                        *   '<S17>/Gain'
                                        */
  real_T Saturation_LowerSat;          /* Expression: 0
                                        * Referenced by: '<S7>/Saturation'
                                        */
  real_T Saturation1_LowerSat;         /* Expression: 0
                                        * Referenced by: '<S7>/Saturation1'
                                        */
  real_T Saturation2_LowerSat;         /* Expression: 0
                                        * Referenced by: '<S7>/Saturation2'
                                        */
  real_T Saturation3_LowerSat;         /* Expression: 0
                                        * Referenced by: '<S7>/Saturation3'
                                        */
  real_T Constant_Value;               /* Expression: 1
                                        * Referenced by: '<S7>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: -1
                                        * Referenced by: '<S7>/Constant1'
                                        */
  real_T acc_pedal_Value;              /* Expression: 1
                                        * Referenced by: '<S2>/acc_pedal'
                                        */
  real_T Constant_Value_o;             /* Expression: 0
                                        * Referenced by: '<S8>/Constant'
                                        */
  real_T Gain_Gain;                    /* Expression: 1/4
                                        * Referenced by: '<S6>/Gain'
                                        */
  real_T Saturation_UpperSat;          /* Expression: inf
                                        * Referenced by: '<S6>/Saturation'
                                        */
  real_T Saturation_LowerSat_e;        /* Expression: 0
                                        * Referenced by: '<S6>/Saturation'
                                        */
  real_T whl_speed_fl_Value;           /* Expression: 1
                                        * Referenced by: '<S2>/whl_speed_fl'
                                        */
  real_T whl_speed_fr_Value;           /* Expression: 1
                                        * Referenced by: '<S2>/whl_speed_fr'
                                        */
  real_T whl_speed_rl_Value;           /* Expression: 1
                                        * Referenced by: '<S2>/whl_speed_rl'
                                        */
  real_T whl_speed_rr_Value;           /* Expression: 1
                                        * Referenced by: '<S2>/whl_speed_rr'
                                        */
  real_T Gain_Gain_j;                  /* Expression: 1/4
                                        * Referenced by: '<S5>/Gain'
                                        */
  real_T Switch_Threshold;             /* Expression: 0
                                        * Referenced by: '<S7>/Switch'
                                        */
  real_T ax_Value;                     /* Expression: 1
                                        * Referenced by: '<S2>/ax'
                                        */
  real_T ay_Value;                     /* Expression: 1
                                        * Referenced by: '<S2>/ay'
                                        */
  real_T yaw_rate_Value;               /* Expression: 1
                                        * Referenced by: '<S2>/yaw_rate'
                                        */
  real_T delta_Value;                  /* Expression: 1
                                        * Referenced by: '<S2>/delta'
                                        */
  real_T Constant_Value_c;             /* Expression: 1
                                        * Referenced by: '<S4>/Constant'
                                        */
  real_T Saturation1_UpperSat;         /* Expression: inf
                                        * Referenced by: '<S4>/Saturation1'
                                        */
  real_T Saturation1_LowerSat_j;       /* Expression: 0.3
                                        * Referenced by: '<S4>/Saturation1'
                                        */
  real_T Saturation_UpperSat_h;        /* Expression: 6
                                        * Referenced by: '<S4>/Saturation'
                                        */
  real_T Saturation_LowerSat_h;        /* Expression: -6
                                        * Referenced by: '<S4>/Saturation'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<S9>/Integrator'
                                        */
  real_T Switch_Threshold_i;           /* Expression: 0
                                        * Referenced by: '<S3>/Switch'
                                        */
  real_T trq_fl_Gain;                  /* Expression: 1
                                        * Referenced by: '<Root>/trq_fl'
                                        */
  real_T trq_fr_Gain;                  /* Expression: 1
                                        * Referenced by: '<Root>/trq_fr'
                                        */
  real_T trq_rl_Gain;                  /* Expression: 1
                                        * Referenced by: '<Root>/trq_rl'
                                        */
  real_T trq_rr_Gain;                  /* Expression: 1
                                        * Referenced by: '<Root>/trq_rr'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_tv_code_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_tv_code_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_tv_code_T *contStateDisabled;
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
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_tv_code_T tv_code_P;

/* Block signals (default storage) */
extern B_tv_code_T tv_code_B;

/* Continuous states (default storage) */
extern X_tv_code_T tv_code_X;

/* Model entry point functions */
extern void tv_code_initialize(void);
extern void tv_code_step(void);
extern void tv_code_terminate(void);

/* Real-time Model object */
extern RT_MODEL_tv_code_T *const tv_code_M;

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
 * '<Root>' : 'tv_code'
 * '<S1>'   : 'tv_code/The Best TorqueVectoring'
 * '<S2>'   : 'tv_code/The Best TorqueVectoring/CarMaker_Inputs'
 * '<S3>'   : 'tv_code/The Best TorqueVectoring/TorqueVectoring'
 * '<S4>'   : 'tv_code/The Best TorqueVectoring/TorqueVectoring/Reference generator'
 * '<S5>'   : 'tv_code/The Best TorqueVectoring/TorqueVectoring/Speed estimaor'
 * '<S6>'   : 'tv_code/The Best TorqueVectoring/TorqueVectoring/Toque distibution NO Tv'
 * '<S7>'   : 'tv_code/The Best TorqueVectoring/TorqueVectoring/Torque distribution Tv'
 * '<S8>'   : 'tv_code/The Best TorqueVectoring/TorqueVectoring/Total Torque Request'
 * '<S9>'   : 'tv_code/The Best TorqueVectoring/TorqueVectoring/Upper Controller'
 * '<S10>'  : 'tv_code/The Best TorqueVectoring/TorqueVectoring/Torque distribution Tv/Fzfl'
 * '<S11>'  : 'tv_code/The Best TorqueVectoring/TorqueVectoring/Torque distribution Tv/Fzfr'
 * '<S12>'  : 'tv_code/The Best TorqueVectoring/TorqueVectoring/Torque distribution Tv/Fzrl'
 * '<S13>'  : 'tv_code/The Best TorqueVectoring/TorqueVectoring/Torque distribution Tv/Fzrr'
 * '<S14>'  : 'tv_code/The Best TorqueVectoring/TorqueVectoring/Torque distribution Tv/T_FL'
 * '<S15>'  : 'tv_code/The Best TorqueVectoring/TorqueVectoring/Torque distribution Tv/T_FR'
 * '<S16>'  : 'tv_code/The Best TorqueVectoring/TorqueVectoring/Torque distribution Tv/T_FR1'
 * '<S17>'  : 'tv_code/The Best TorqueVectoring/TorqueVectoring/Torque distribution Tv/T_RL'
 */
#endif                                 /* RTW_HEADER_tv_code_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
