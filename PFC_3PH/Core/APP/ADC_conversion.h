#ifndef __ADC_CONVERSION_H__
#define __ADC_CONVERSION_H__

#define Kv0 1.0f
#define Kv1 1.0f
#define Kv2 1.0f

#define Kc0 1.0f
#define Kc1 1.0f
#define Kc2 1.0f

#define Offset_C0 1.0f
#define Offset_C1 1.0f
#define Offset_C2 1,0f

#define BASIC_VOLTAGE 3.0f
#define ADC_ACCURACY  4096.0f

#define Vget0(Raw_Value) Raw_Value*BASIC_VOLTAGE/ADC_ACCURACY*Kv0
#define Vget1(Raw_Value) Raw_Value*BASIC_VOLTAGE/ADC_ACCURACY*Kv1
#define Vget2(Raw_Value) Raw_Value*BASIC_VOLTAGE/ADC_ACCURACY*Kv2

#define Iget0(Raw_Value) Raw_Value*BASIC_VOLTAGE/ADC_ACCURACY*Kc0 + Offset_C0
#define Iget1(Raw_Value) Raw_Value*BASIC_VOLTAGE/ADC_ACCURACY*Kc1 + Offset_C1
#define Iget2(Raw_Value) Raw_Value*BASIC_VOLTAGE/ADC_ACCURACY*Kc2 + Offset_C2

typedef struct
{
    uint16_t Raw_Value_Vgrid[3];
    uint16_t Raw_Value_Igrid[3];
    float Vgrid[3];
    float Igrid[3];
}Sample_ValueType;

inline void ADC_Conversion(Sample_ValueType* ADC_Value)
{
    ADC_Value->Vgrid[0] = Vget0(ADC_Value->Raw_Value_Vgrid[0]);
    ADC_Value->Vgrid[1] = Vget0(ADC_Value->Raw_Value_Vgrid[1]);
    ADC_Value->Vgrid[2] = Vget0(ADC_Value->Raw_Value_Vgrid[2]);

    ADC_Value->Igrid[0] = Iget0(ADC_Value->Raw_Value_Vgrid[0]);
    ADC_Value->Igrid[1] = Iget0(ADC_Value->Raw_Value_Vgrid[0]);
    ADC_Value->Igrid[2] = Iget0(ADC_Value->Raw_Value_Vgrid[0]);
}




#endif // !