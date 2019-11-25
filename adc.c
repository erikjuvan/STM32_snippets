
void ADC_Configure()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // ADC Channel / GPIO Pin
    //  ADC1_CH-0  / GPIOA_0
    //  ADC1_CH-1  / GPIOA_1
    //  ADC1_CH-2  / GPIOA_2

    //  ADC1_CH-3  / GPIOA_3
    //  ADC1_CH-8  / GPIOB_0
    //  ADC1_CH-9  / GPIOB_1

    //  ADC1_CH-11 / GPIOC_1
    //  ADC1_CH-12 / GPIOC_2
    //  ADC1_CH-14 / GPIOC_4

    //  ADC1_CH-15 / GPIOC_5

    __HAL_RCC_ADC1_CLK_ENABLE();

    // PORT A
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStructure.Pin  = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    // PORT B
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    // PORT B
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitStructure.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

    AdcHandle.Instance                   = ADC1;
    AdcHandle.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV4;
    AdcHandle.Init.Resolution            = ADC_RESOLUTION_8B;
    AdcHandle.Init.ScanConvMode          = ENABLE;
    AdcHandle.Init.ContinuousConvMode    = DISABLE;
    AdcHandle.Init.DiscontinuousConvMode = DISABLE;
    AdcHandle.Init.NbrOfDiscConversion   = 0;
    AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_RISING;
    AdcHandle.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T2_TRGO;
    AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    AdcHandle.Init.NbrOfConversion       = numOfChannels;
    AdcHandle.Init.DMAContinuousRequests = ENABLE;
    AdcHandle.Init.EOCSelection          = ADC_EOC_SEQ_CONV;
    HAL_ADC_Init(&AdcHandle);

    ADC_ChannelConfTypeDef adcChannelConfig;

    // Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
    adcChannelConfig.Channel      = ADC_CHANNEL_0;
    adcChannelConfig.Rank         = 1;
    adcChannelConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES; // ADC_SAMPLETIME_84CYCLES
    if (HAL_ADC_ConfigChannel(&AdcHandle, &adcChannelConfig) != HAL_OK) {
    }

    adcChannelConfig.Channel = ADC_CHANNEL_1;
    adcChannelConfig.Rank    = 2;
    if (HAL_ADC_ConfigChannel(&AdcHandle, &adcChannelConfig) != HAL_OK) {
    }

    adcChannelConfig.Channel = ADC_CHANNEL_2;
    adcChannelConfig.Rank    = 3;
    if (HAL_ADC_ConfigChannel(&AdcHandle, &adcChannelConfig) != HAL_OK) {
    }

    adcChannelConfig.Channel = ADC_CHANNEL_3;
    adcChannelConfig.Rank    = 4;
    if (HAL_ADC_ConfigChannel(&AdcHandle, &adcChannelConfig) != HAL_OK) {
    }

    adcChannelConfig.Channel = ADC_CHANNEL_8;
    adcChannelConfig.Rank    = 5;
    if (HAL_ADC_ConfigChannel(&AdcHandle, &adcChannelConfig) != HAL_OK) {
    }

    adcChannelConfig.Channel = ADC_CHANNEL_9;
    adcChannelConfig.Rank    = 6;
    if (HAL_ADC_ConfigChannel(&AdcHandle, &adcChannelConfig) != HAL_OK) {
    }

    adcChannelConfig.Channel = ADC_CHANNEL_11;
    adcChannelConfig.Rank    = 7;
    if (HAL_ADC_ConfigChannel(&AdcHandle, &adcChannelConfig) != HAL_OK) {
    }

    adcChannelConfig.Channel = ADC_CHANNEL_12;
    adcChannelConfig.Rank    = 8;
    if (HAL_ADC_ConfigChannel(&AdcHandle, &adcChannelConfig) != HAL_OK) {
    }

    adcChannelConfig.Channel = ADC_CHANNEL_14;
    adcChannelConfig.Rank    = 9;
    if (HAL_ADC_ConfigChannel(&AdcHandle, &adcChannelConfig) != HAL_OK) {
    }

    adcChannelConfig.Channel = ADC_CHANNEL_15;
    adcChannelConfig.Rank    = 10;
    if (HAL_ADC_ConfigChannel(&AdcHandle, &adcChannelConfig) != HAL_OK) {
    }
}