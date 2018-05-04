
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

/* Begin of <includes> initialization, DO NOT MODIFY LINES BELOW */

#include "TSK1.h"
#include "FRTOS1.h"
#include "frtos_tasks.h"

/* End <includes> initialization, DO NOT MODIFY LINES ABOVE */
#include "Bit1.h"
#include "Bit2.h"
#include "Bit3.h"

static portTASK_FUNCTION(Task_1, pvParameters) {

  /* Write your task initialization code here ... */

  for(;;) {
    /* Write your task code here ... */
	  Bit1_NegVal();
	  vTaskDelay(1000/portTICK_RATE_MS);
    /* You can use a task delay like
       vTaskDelay(1000/portTICK_RATE_MS);
     */
  }
  /* Destroy the task */
  vTaskDelete(Task_1);
}

static portTASK_FUNCTION(Task_2, pvParameters) {

  /* Write your task initialization code here ... */

  for(;;) {
    /* Write your task code here ... */
	  Bit2_NegVal();
	  vTaskDelay(1000/portTICK_RATE_MS);
    /* You can use a task delay like
       vTaskDelay(1000/portTICK_RATE_MS);
     */
  }
  /* Destroy the task */
  vTaskDelete(Task_2);
}

static portTASK_FUNCTION(Task_3, pvParameters) {

  /* Write your task initialization code here ... */

  for(;;) {
    /* Write your task code here ... */
	  Bit3_NegVal();
	  vTaskDelay(1000/portTICK_RATE_MS);
    /* You can use a task delay like
       vTaskDelay(1000/portTICK_RATE_MS);
     */
  }
  /* Destroy the task */
  vTaskDelete(Task_3);
}

void CreateTasks(void) {
  if (FRTOS1_xTaskCreate(
     Task_1,  /* pointer to the task */
      "", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE + 0, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY + 1,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
      /*lint -e527 */
      for(;;){}; /* error! probably out of memory */
      /*lint +e527 */
  }
  if (FRTOS1_xTaskCreate(
     Task_2,  /* pointer to the task */
      "", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE + 0, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY + 1,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
      /*lint -e527 */
      for(;;){}; /* error! probably out of memory */
      /*lint +e527 */
  }
  if (FRTOS1_xTaskCreate(
     Task_3,  /* pointer to the task */
      "", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE + 0, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY + 1,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
      /*lint -e527 */
      for(;;){}; /* error! probably out of memory */
      /*lint +e527 */
  }
}

