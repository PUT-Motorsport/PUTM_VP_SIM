/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: tv_code_data.c
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

#include "tv_code.h"

/* Block parameters (default storage) */
P_tv_code_T tv_code_P = {
  /* Variable: Ku
   * Referenced by: '<S4>/Desired Understeer Gradient'
   */
  -0.0025,

  /* Variable: L
   * Referenced by:
   *   '<S4>/axlebase'
   *   '<S10>/Gain'
   *   '<S11>/Gain'
   *   '<S12>/Gain'
   *   '<S13>/Gain'
   */
  2.6,

  /* Variable: Mz_I
   * Referenced by: '<S2>/Mz Integative Gain'
   */
  70.0,

  /* Variable: Mz_p
   * Referenced by: '<S2>/Mz Proportional Gain'
   */
  1000.0,

  /* Variable: drive_ratio
   * Referenced by:
   *   '<S7>/Saturation'
   *   '<S7>/Saturation1'
   *   '<S7>/Saturation2'
   *   '<S7>/Saturation3'
   *   '<S8>/Constant1'
   */
  14.25,

  /* Variable: g
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
  9.81,

  /* Variable: h
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
  0.25,

  /* Variable: lf
   * Referenced by:
   *   '<S12>/Constant'
   *   '<S12>/Gain2'
   *   '<S13>/Constant'
   *   '<S13>/Gain2'
   */
  0.765,

  /* Variable: lr
   * Referenced by:
   *   '<S10>/Constant'
   *   '<S10>/Gain2'
   *   '<S11>/Constant'
   *   '<S11>/Gain2'
   */
  0.765,

  /* Variable: ls
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
  1.242,

  /* Variable: m
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
  180.0,

  /* Variable: max_moment
   * Referenced by:
   *   '<S7>/Saturation'
   *   '<S7>/Saturation1'
   *   '<S7>/Saturation2'
   *   '<S7>/Saturation3'
   *   '<S8>/Constant1'
   */
  9.8,

  /* Variable: rw
   * Referenced by:
   *   '<S5>/Gain1'
   *   '<S14>/Gain'
   *   '<S15>/Gain'
   *   '<S16>/Gain'
   *   '<S17>/Gain'
   */
  0.217,

  /* Expression: 0
   * Referenced by: '<S7>/Saturation'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S7>/Saturation1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S7>/Saturation2'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S7>/Saturation3'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S7>/Constant'
   */
  1.0,

  /* Expression: -1
   * Referenced by: '<S7>/Constant1'
   */
  -1.0,

  /* Expression: 1
   * Referenced by: '<S2>/acc_pedal'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S8>/Constant'
   */
  0.0,

  /* Expression: 1/4
   * Referenced by: '<S6>/Gain'
   */
  0.25,

  /* Expression: inf
   * Referenced by: '<S6>/Saturation'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S6>/Saturation'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S2>/whl_speed_fl'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S2>/whl_speed_fr'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S2>/whl_speed_rl'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S2>/whl_speed_rr'
   */
  1.0,

  /* Expression: 1/4
   * Referenced by: '<S5>/Gain'
   */
  0.25,

  /* Expression: 0
   * Referenced by: '<S7>/Switch'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<S2>/ax'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S2>/ay'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S2>/yaw_rate'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S2>/delta'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<S4>/Constant'
   */
  1.0,

  /* Expression: inf
   * Referenced by: '<S4>/Saturation1'
   */
  0.0,

  /* Expression: 0.3
   * Referenced by: '<S4>/Saturation1'
   */
  0.3,

  /* Expression: 6
   * Referenced by: '<S4>/Saturation'
   */
  6.0,

  /* Expression: -6
   * Referenced by: '<S4>/Saturation'
   */
  -6.0,

  /* Expression: 0
   * Referenced by: '<S9>/Integrator'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S3>/Switch'
   */
  0.0,

  /* Expression: 1
   * Referenced by: '<Root>/trq_fl'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<Root>/trq_fr'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<Root>/trq_rl'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<Root>/trq_rr'
   */
  1.0
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
