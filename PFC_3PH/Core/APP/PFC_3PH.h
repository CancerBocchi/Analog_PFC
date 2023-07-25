#ifndef __3PH_PFC_H__
#define __3PH_PFC_H__

#include "inc.h"
#include "ADC_conversion.h"
#include "PFC_Defines.h"

extern Sample_ValueType ADC_Value;

extern ABC_DQ0_NEG PFC_Vgrid_dq_neg_DDR;
extern ABC_DQ0_POS PFC_Vgrid_dq_pos_DDR;
extern ABC_DQ0_POS PFC_Vgrid_dq_pos;

extern DQ0_ABC PFC_Vgrid_dq_abc;

extern Sample_ValueType ADC_Value;

extern SPLL_3PH_DDSRF PFC_SPLL_DDRSRF;
extern SPLL_3PH_SRF PFC_SPLL_SRF;

extern float PFC_AxisTran_sin;
extern float PFC_AxisTran_cos;
extern float PFC_AxisTran_sin_DDR;
extern float PFC_AxisTran_cos_DDR;
extern float PFC_AxisTran_sin_auto;
extern float PFC_AxisTran_cos_auto;

extern float PFC_Angle_Radin_SRF;
extern float PFC_Angle_Radin_DDR;

extern float PFC_Auto_3Ph_Signal_Value[3];

void PFC_Init();
void PFC_AxisTransformer();
void SPLL_lab1();
void PFC_InternalGenerate3PH();
void PFC_SPLL_Run(float v_d_p,float v_q_p,float v_d_n,float v_q_n);







#endif // !__3PH_PFC_H__