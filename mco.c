void OutputMCO() {
	__GPIOA_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();
	
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	GPIO_InitStructure.Pin = GPIO_PIN_8;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStructure.Alternate = 0;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.Pin = GPIO_PIN_9;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

	__HAL_RCC_MCO1_CONFIG(RCC_MCO1SOURCE_PLLCLK, RCC_MCODIV_5);
	__HAL_RCC_MCO2_CONFIG(RCC_MCO2SOURCE_SYSCLK, RCC_MCODIV_5);
}


