/*
 * mode.c
 *
 *  Created on: 20 окт. 2015 г.
 *      Author: Yulia
 */
#include "mode.h"

//exposition for different teeth, *20 ms
EXPOSITION_t exposition(MODE_TypeDef mode_struct)
{
	switch(mode_struct.tooth){

	case(UIN):
		{
		if (mode_struct.patient_type == PAT1) mode_struct.man_exposition = UINC_TIME_S;
		if (mode_struct.patient_type == PAT2) mode_struct.man_exposition = UINC_TIME_M;
		if (mode_struct.patient_type == PAT3) mode_struct.man_exposition = UINC_TIME_L;
		}
	break;

	case(UPM):
		{
		if (mode_struct.patient_type == PAT1) mode_struct.man_exposition = UPMO_TIME_S;
		if (mode_struct.patient_type == PAT2) mode_struct.man_exposition = UPMO_TIME_M;
		if (mode_struct.patient_type == PAT3) mode_struct.man_exposition = UPMO_TIME_L;
		}
	break;

	case(UMO):
		{
		if (mode_struct.patient_type == PAT1) mode_struct.man_exposition = UMOL_TIME_S;
		if (mode_struct.patient_type == PAT2) mode_struct.man_exposition = UMOL_TIME_M;
		if (mode_struct.patient_type == PAT3) mode_struct.man_exposition = UMOL_TIME_L;
		}
	break;

	case(DIN):
		{
		if (mode_struct.patient_type == PAT1) mode_struct.man_exposition = DINC_TIME_S;
		if (mode_struct.patient_type == PAT2) mode_struct.man_exposition = DINC_TIME_M;
		if (mode_struct.patient_type == PAT3) mode_struct.man_exposition = DINC_TIME_L;
		}
	break;

	case(DPM):
		{
		if (mode_struct.patient_type == PAT1) mode_struct.man_exposition = DPMO_TIME_S;
		if (mode_struct.patient_type == PAT2) mode_struct.man_exposition = DPMO_TIME_M;
		if (mode_struct.patient_type == PAT3) mode_struct.man_exposition = DPMO_TIME_L;
		}
	break;

	case(DMO):
		{
		if (mode_struct.patient_type == PAT1) mode_struct.man_exposition = DMOL_TIME_S;
		if (mode_struct.patient_type == PAT2) mode_struct.man_exposition = DMOL_TIME_M;
		if (mode_struct.patient_type == PAT3) mode_struct.man_exposition = DMOL_TIME_L;
		}
	break;

	}
	return(mode_struct.man_exposition);
}


