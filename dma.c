
void DMA_Configure()
{
    __HAL_RCC_DMA2_CLK_ENABLE();
    DmaHandle.Instance = DMA2_Stream0;

    DmaHandle.Init.Channel             = DMA_CHANNEL_0;
    DmaHandle.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    DmaHandle.Init.PeriphInc           = DMA_PINC_DISABLE;
    DmaHandle.Init.MemInc              = DMA_MINC_ENABLE;
    DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    DmaHandle.Init.MemDataAlignment    = DMA_PDATAALIGN_BYTE;
    DmaHandle.Init.Mode                = DMA_CIRCULAR;
    DmaHandle.Init.Priority            = DMA_PRIORITY_HIGH;
    DmaHandle.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
    DmaHandle.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_HALFFULL;
    DmaHandle.Init.MemBurst            = DMA_MBURST_SINGLE;
    DmaHandle.Init.PeriphBurst         = DMA_PBURST_SINGLE;

    HAL_DMA_Init(&DmaHandle);

    __HAL_LINKDMA(&AdcHandle, DMA_Handle, DmaHandle);

    HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
}
