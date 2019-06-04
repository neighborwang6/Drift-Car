#include "bsp_dma.h"

//Test data  用来测试DMA的传输
unsigned char Source[10]={1,2,3,4,5,6,7,8,9,10};
unsigned char Destination[10];

//DMA initlization
void DMA_Init_(void)
{
  DMA_InitTypeDef DMA_InitStruct;
  
  DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)Source;
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)Destination;
  DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStruct.DMA_BufferSize = 10;
  DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
  DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStruct.DMA_Priority = DMA_Priority_High;
  DMA_InitStruct.DMA_M2M = DMA_M2M_Enable;
  
  DMA_Init(DMA1_Channel1,&DMA_InitStruct);
                              

}
