
#include "stm32f7xx.h"
#include "lvgl/lvgl.h"

#include "hal_stm_lvgl/tft/tft.h"
#include "hal_stm_lvgl/touchpad/touchpad.h"

#include "lv_examples/lv_examples.h"

#include "stm32f746xx.h"
#include "stm32746g_discovery_qspi.h"
#include "stm32746g_discovery_sdram.h"

#include "digitalcam_gui/inc/digitalcam_gui.h"
#include "cam/inc/cam.h"
#include "Utilities/STM32746G-Discovery/stm32746g_discovery_lcd.h"
#include "stm32746g_discovery.h"


#define DISP_FRAME_BUFFER			0xC0200000

static void SystemClock_Config(void);


int main(void)
{
    HAL_Init();

    /* Configure the system clock to 216 MHz */
    SystemClock_Config();

    /* Enable I-Cache */
    SCB_EnableICache();

    /* Enable D-Cache */
    SCB_EnableDCache();

    BSP_LCD_Init();
    BSP_LCD_LayerRgb565Init(1, (uint32_t)DISP_FRAME_BUFFER);
    BSP_LCD_SetLayerWindow(1, 0, 0, 480, 272);
    BSP_LCD_DisplayOn();


//    BSP_QSPI_Init();
//    BSP_QSPI_MemoryMappedMode();

//    BSP_SDRAM_Init();
//    HAL_EnableFMCMemorySwapping();
//    lv_init();

//    tft_init();
//    touchpad_init();

//    lv_demo_benchmark();
//    lv_demo_widgets();
//    digitalcam_gui_init();

    cam_init();
    cam_live_feed();

    while (1)
    {
//        HAL_Delay(5);
//        lv_task_handler();
    }
}

static void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    /* Enable Power Control clock */
    __HAL_RCC_PWR_CLK_ENABLE();

    /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /*##-1- System Clock Configuration #########################################*/
    /* Enable HSE Oscillator and activate PLL with HSE as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;
    RCC_OscInitStruct.PLL.PLLN = 400;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 8;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    /* Activate the Over-Drive mode */
    HAL_PWREx_EnableOverDrive();

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6);
}

