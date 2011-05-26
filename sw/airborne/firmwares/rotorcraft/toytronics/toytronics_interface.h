// toytronics_interface.h
// Greg Horn, Joby Robotics 2011

// This file is #included by toytronics_setpoint.c and abstracts out the paparazzi interface

#ifndef __TOYTRONICS_INTERFACE_H__
#define __TOYTRONICS_INTERFACE_H__

#include "toytronics_types.h"

#include "firmwares/rotorcraft/stabilization/stabilization_attitude_ref_quat_int.h" // for RC_UPDATE_FREQ
#include "firmwares/rotorcraft/guidance/guidance_h.h" // for mode #defines

const quat_t * get_q_n2b(void);
const euler_t * get_e_n2b(void);
const rc_t * get_rc(void);
void set_paparazzi_setpoint(const setpoint_t * const setpoint);

void inner_set_forward_gains(void);
void inner_set_hover_gains(void);
void inner_set_aerobatic_gains(void);
void inner_setpoint_reset(void);


#endif // __TOYTRONICS_INTERFACE_H__