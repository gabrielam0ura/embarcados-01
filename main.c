#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "stdio.h"

// Variáveis para os resultados
int resultadoTarefa1 = 0;
int resultadoTarefa2 = 0;
int resultadoTarefa3 = 0;
int resultadoTarefa4 = 0;

// Definindo handles das tarefas
TaskHandle_t tarefa1Handle;
TaskHandle_t tarefa2Handle;
TaskHandle_t tarefa3Handle;
TaskHandle_t tarefa4Handle;

// Definindo o timer
TimerHandle_t timer4Handle;

// Variável para contar os segundos
static unsigned long contadorSegundos = 0;

// Função do temporizador para contar os segundos
void TempoTotal_TimerCallback(TimerHandle_t xTimer) {
    contadorSegundos++;
    printf("Contador de segundos: %lu segundos\n", contadorSegundos);
}

void Tarefa1(void *pvParameters) {
    resultadoTarefa1 = 5 + 3; // Operação simples de soma
    printf("Tarefa 1: Resultado da soma: %d\n", resultadoTarefa1);
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay
    vTaskDelete(tarefa1Handle);
}

void Tarefa2(void *pvParameters) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    resultadoTarefa2 = resultadoTarefa1 * 2; // Multiplicação
    printf("Tarefa 2: Resultado da multiplicação: %d\n", resultadoTarefa2);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    vTaskDelete(tarefa2Handle);
}

void Tarefa3(void *pvParameters) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    resultadoTarefa3 = resultadoTarefa2 * resultadoTarefa2; // Quadrado do valor
    printf("Tarefa 3: Resultado do quadrado: %d\n", resultadoTarefa3);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    vTaskDelete(tarefa3Handle);
}

int main(void) {
    // Criando as tarefas
    xTaskCreate(Tarefa1, "Tarefa1", configMINIMAL_STACK_SIZE, NULL, 1, &tarefa1Handle);
    xTaskCreate(Tarefa2, "Tarefa2", configMINIMAL_STACK_SIZE, NULL, 1, &tarefa2Handle);
    xTaskCreate(Tarefa3, "Tarefa3", configMINIMAL_STACK_SIZE, NULL, 1, &tarefa3Handle);
    
    timer4Handle = xTimerCreate("Timer4", pdMS_TO_TICKS(1000), pdTRUE, (void *) 0, TempoTotal_TimerCallback);

    // Iniciando o temporizador
    xTimerStart(timer4Handle, 0);

    // Iniciando o scheduler
    vTaskStartScheduler();

    return 0;
}