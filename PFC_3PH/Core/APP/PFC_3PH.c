#include "PFC_3PH.h"

ABC_DQ0_NEG PFC_Vgrid_dq_neg_DDR;
ABC_DQ0_POS PFC_Vgrid_dq_pos_DDR;
ABC_DQ0_POS PFC_Vgrid_dq_pos;

DQ0_ABC PFC_Vgrid_dq_abc;

Sample_ValueType ADC_Value;

SPLL_3PH_DDSRF PFC_SPLL_DDRSRF;
SPLL_3PH_SRF PFC_SPLL_SRF;

float PFC_AxisTran_sin;
float PFC_AxisTran_cos;
float PFC_AxisTran_sin_DDR;
float PFC_AxisTran_cos_DDR;
float PFC_AxisTran_sin_auto;
float PFC_AxisTran_cos_auto;

float PFC_Angle_Radin_SRF;
float PFC_Angle_Radin_DDR;

float PFC_Auto_3Ph_Signal_Value[3];

void PFC_Init()
{   
    DQ0_ABC_reset(&PFC_Vgrid_dq_abc);
    ABC_DQ0_NEG_reset(&PFC_Vgrid_dq_neg_DDR);
    ABC_DQ0_POS_reset(&PFC_Vgrid_dq_pos_DDR);
    ABC_DQ0_POS_reset(&PFC_Vgrid_dq_pos);


    SPLL_3PH_DDSRF_init(PFC_GRID_FRE,(float)(1.0f/PFC_SPLL_FRE)
                        ,0.00933678,-0.9813264,&PFC_SPLL_DDRSRF);
    PFC_SPLL_DDRSRF.lpf_coeff.b0 = 66.87103117f;
    PFC_SPLL_DDRSRF.lpf_coeff.b1 = -66.8151643f;


    SPLL_3PH_SRF_init(PFC_GRID_FRE,(float)(1.0f/PFC_SPLL_FRE)
                        ,&PFC_SPLL_SRF);
    PFC_SPLL_DDRSRF.lpf_coeff.b0 = 66.87103117f;
    PFC_SPLL_DDRSRF.lpf_coeff.b1 = -66.8151643f;

    HAL_HRTIM_WaveformCounterStart_IT(&hhrtim1,HRTIM_TIMERID_TIMER_A);

    HAL_ADC_Start_DMA(&hadc1,(uint32_t*)ADC_Value.Raw_Value_Vgrid,3);
}

void PFC_InternalGenerate3PH()
{
    static float theta = 0.0f;
    static float step = 50.0f/10000.0f*2.0f*PFC_PI;
    theta += step;

    srand((unsigned)time(NULL));

    int rawrand1 = rand()%100;
    int rawrand2 = rand()%100;
    int rawrand3 = rand()%100;
    float randnum1 = (float)rawrand1/1000.0f;
    float randnum2 = (float)rawrand2/1000.0f;
    float randnum3 = (float)rawrand3/1000.0f;


    if(theta>2.0f*PFC_PI)
        theta -= 2.0f*PFC_PI;

    PFC_Auto_3Ph_Signal_Value[0] = sinf(theta) + randnum1;
    PFC_Auto_3Ph_Signal_Value[1] = sinf(theta + 2.0f/3.0f*PFC_PI) + randnum2;
    PFC_Auto_3Ph_Signal_Value[2] = sinf(theta - 2.0f/3.0f*PFC_PI) + randnum3;

    PFC_AxisTran_cos_auto = cosf(PFC_Angle_Radin_SRF);
    PFC_AxisTran_sin_auto = sinf(PFC_Angle_Radin_SRF);
    
    SEGGER_RTT_printf(0,"%d,%d\n",(int)(PFC_Auto_3Ph_Signal_Value[0]*1000.0f),
                                  (int)(PFC_Auto_3Ph_Signal_Value[1] *1000.0f));

    ABC_DQ0_NEG_run(&PFC_Vgrid_dq_neg_DDR, PFC_Auto_3Ph_Signal_Value[0],
                     PFC_Auto_3Ph_Signal_Value[1], PFC_Auto_3Ph_Signal_Value[2],
                    PFC_AxisTran_sin_auto,PFC_AxisTran_cos_auto);

    ABC_DQ0_POS_run(&PFC_Vgrid_dq_pos_DDR,PFC_Auto_3Ph_Signal_Value[0],
                    PFC_Auto_3Ph_Signal_Value[1],PFC_Auto_3Ph_Signal_Value[2],
                    PFC_AxisTran_sin_auto,PFC_AxisTran_cos_auto);

}

void PFC_AxisTransformer()
{
    ABC_DQ0_NEG_run(&PFC_Vgrid_dq_neg_DDR,ADC_Value.Vgrid[0],
                    ADC_Value.Vgrid[1],ADC_Value.Vgrid[2],
                    PFC_AxisTran_sin_DDR,PFC_AxisTran_cos_DDR);

    ABC_DQ0_POS_run(&PFC_Vgrid_dq_pos_DDR,ADC_Value.Vgrid[0],
                    ADC_Value.Vgrid[1],ADC_Value.Vgrid[2],
                    PFC_AxisTran_sin_DDR,PFC_AxisTran_cos_DDR);

    ABC_DQ0_POS_run(&PFC_Vgrid_dq_pos,ADC_Value.Vgrid[0],
                    ADC_Value.Vgrid[1],ADC_Value.Vgrid[2],
                    PFC_AxisTran_sin,PFC_AxisTran_cos);

    PFC_AxisTran_sin_DDR = sinf(PFC_Angle_Radin_DDR);
    PFC_AxisTran_cos_DDR = cosf(PFC_Angle_Radin_DDR);

    PFC_AxisTran_cos = cosf(PFC_Angle_Radin_SRF);
    PFC_AxisTran_sin = sinf(PFC_Angle_Radin_SRF);
}

void PFC_SPLL_Run(float v_d_p,float v_q_p,float v_d_n,float v_q_n)
{
    SPLL_3PH_DDSRF_run(&PFC_SPLL_DDRSRF,v_d_p,v_d_n,v_q_p,v_q_n);
    SPLL_3PH_SRF_run(v_q_p,&PFC_SPLL_SRF);

    PFC_Angle_Radin_SRF = PFC_SPLL_SRF.theta[1];
    PFC_Angle_Radin_DDR = PFC_SPLL_DDRSRF.theta[1];
}

