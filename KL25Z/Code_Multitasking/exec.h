#ifndef __EXEC_H_
#define __EXEC_H_

#include "defs.h"
#include "list.h"
#include <stdlib.h>
#include "MKL25Z4.h"

extern volatile uint32_t ticks;
/**
 * Armazenamento de um valor de tempo (em ticks).
 */
#define timer_t uint32_t

/**
 * Retorna um timer_t para o tempo especificado.
 */
#define start_timer(X) (X+ticks)

/**
 * TRUE se o tempo especificado na criação do timer já foi transcorrido.
 */
#define timeout(X) (ticks>X?1:0)

/**
 * Estrutura de uma tarefa.
 */
typedef struct {
   list_item_t list;
   uint32_t func;                   ///< Endereço da tarefa.
   uint16_t tempo;                  ///< Tempo para execução (0 = pronto).
   uint16_t par;                    ///< Parâmetro a ser passado para a tarefa.
} task_t;


void task_init(void);
void task_run(void);
bool_t add_task(uint32_t f, uint16_t p, uint16_t t);
bool_t cancel_task(uint32_t f);
void systimer_tick(void);

#endif
