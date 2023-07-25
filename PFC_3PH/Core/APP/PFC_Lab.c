#include "PFC_3PH.h"

void SPLL_lab1()
{
    PFC_InternalGenerate3PH();
    PFC_SPLL_Run(PFC_Vgrid_dq_pos_DDR.d,PFC_Vgrid_dq_pos_DDR.q,
                PFC_Vgrid_dq_neg_DDR.d,PFC_Vgrid_dq_neg_DDR.q);

}
