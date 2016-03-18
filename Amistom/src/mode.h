/*
 * mode.h
 *
 *  Created on: 20 окт. 2015 г.
 *      Author: mos-rk-753
 */

#ifndef MODE_H_
#define MODE_H_

#include "main.h"


//exposition for different teeth, *20 ms
typedef enum
{
	UINC_TIME_S = 13,
    UINC_TIME_M = 16,
    UINC_TIME_L = 25,
	UPMO_TIME_S = 16,
	UPMO_TIME_M = 25,
	UPMO_TIME_L = 35,
	UMOL_TIME_S = 18,
	UMOL_TIME_M = 33,
	UMOL_TIME_L = 40,
	DINC_TIME_S = 12,
	DINC_TIME_M = 15,
	DINC_TIME_L = 24,
	DPMO_TIME_S = 15,
	DPMO_TIME_M = 20,
	DPMO_TIME_L = 30,
	DMOL_TIME_S = 18,
	DMOL_TIME_M = 25,
	DMOL_TIME_L = 35
}EXPOSITION_t;

typedef enum
{
	PAT1 = 1,
	PAT2 = 2,
	PAT3 = 3,
}PAT_t;

typedef enum
{
	UIN = 0,
	DIN = 1,
	UPM = 2,
	DPM = 3,
	UMO = 4,
	DMO = 5,
}TOOTH_t;


/*//voltage correction (divide by 100)
typedef enum
{
	VOLT192 = 220,
	VOLT195 = 200,
	VOLT200 = 180,
	VOLT205 = 150,
	VOLT210 = 130,
	VOLT215 = 100,
	VOLT225 = 85,
	VOLT230 = 72,
	VOLT235 = 60,
	VOLT240 = 54
}VOLT_t;*/

typedef enum
{
	PREHEAT192 = 145,
	PREHEAT200 = 125,
	PREHEAT210 = 105,
	PREHEAT230 = 85,
	PREHEAT240 = 65
}PREHEAT_t;


//film sensitivity factor(divide by 10)
typedef enum
{
	FILM_1 = 10,
	FILM_2 = 7,
	FILM_3 = 2
}FILM_SENS_t;

//voltage correction (divide by 100)
typedef enum
{
	volt192_195 = 220,
	volt195_200 = 200,
	volt200_205 = 180,
	volt205_210 = 150,
	volt210_215 = 130,
	volt215_225 = 100,
	volt225_230 = 85,
	volt230_235 = 72,
	volt235_240 = 60,
	volt240_247 = 54
}VOLT_t;

typedef struct {

		PAT_t			patient_type;
		TOOTH_t			tooth;
		FILM_SENS_t		film;

		EXPOSITION_t	man_exposition;
		VOLT_t			voltage_correction;
		PREHEAT_t		preheat_time;
		_Bool			mode;					//auto = 1, manual = 0

} MODE_TypeDef;

EXPOSITION_t exposition(MODE_TypeDef mode_struct);
VOLT_t exposition_count(void);

#endif /* MODE_H_ */
