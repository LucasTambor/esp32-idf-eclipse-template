//Includes de libs gerais C/C++
#include <stdio.h>
//Include de libs de drivers de sistema
#include "driver/gpio.h"
//Include do freeRTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//Referencias do ESP
#include "esp_system.h"
#include "esp_log.h"


//Definições de suporte
#define LED_PIN		GPIO_NUM_2
#define BTN_PIN		GPIO_NUM_13

//Variaveis globais

//Prototypes
void taskBlink(void *pvParameters);
void taskButton(void *pvParameters);
//Rotina principal da aplicação
void app_main()
{
	esp_chip_info_t chipInfo;
	esp_chip_info(&chipInfo);
	printf("Iniciando ESP32...\n");
	printf("Chip ESP32 com %d nucleos, WIFI%s%s\n",
			chipInfo.cores,
			(chipInfo.features & CHIP_FEATURE_BT) ? "/BT" : "",
			(chipInfo.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
	printf("Revisao do chip: %d\n", chipInfo.revision);



	printf("inicializando taskBlink");
	xTaskCreate(taskBlink, "taskBlink", 1024, NULL, 5, NULL);
	printf("taskBlink inicializada com sucesso");

}

void taskBlink(void *pvParameter)
{
	bool level = 0;
	gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
	while(1)
	{
		gpio_set_level(LED_PIN, level);
		level = !level;
		vTaskDelay(500/ portTICK_PERIOD_MS);

	}
}

void taskButton(void *pvParameters)
{
	bool state, lastState;

	gpio_set_direction(BTN_PIN, GPIO_MODE_INPUT);
	gpio_pullup_en(BTN_PIN);
	//TODO
}
