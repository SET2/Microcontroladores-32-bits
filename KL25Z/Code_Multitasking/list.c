/**
 * @file list.c
 * @brief Gerenciamento de listas ligadas.
 *
 * Estruturas de dados dinâmicas para uso do sistema.
 * @author Bruno Basseto (bruno@openmind.net.br)
 * @version 0
 */

/*********************************************************************************
 *
 *   Este programa é Software Livre: você pode redistribui-lo e/ou modificá-lo
 *   nos termos da licença MIT.
 *
 *   Este programa é distribuído na esperança de que seja útil, porém
 *   SEM QUALQUER TIPO DE GARANTIA.
 *
 *   Veja o arquivo LICENSE na raiz do projeto.
 *
 *********************************************************************************/

#include "defs.h"
#include <stdlib.h>
#include "list.h"

#define LISTPTR(x)      ((list_item_t*)x)

/**
 * Insere um elemento no final de uma lista.
 * @param list Ponteiro para o primeiro objeto da lista.
 * @param item Item para ser inserido.
 */
void list_add(void *list, void *item)
{
   register list_item_t *p;
   register list_item_t **lst;

   lst = (list_item_t**)list;

   if(*lst == NULL) {
      /*
       * Primeiro item da lista.
       */
      *lst = item;
      (*lst)->next = NULL;
      (*lst)->prev = NULL;
      return;
   }

   /*
    * Insere elemento no final da lista.
    * list->prev é o último elemento.
    */
   p = (*lst)->prev;
   if(p == NULL) p = *lst;
   (*lst)->prev = (list_item_t*)item;
   LISTPTR(item)->prev = p;
   LISTPTR(item)->next = NULL;
   p->next = item;
}

/**
 * Insere um elemento no começo de uma lista.
 * @param list Ponteiro para o primeiro objeto da lista.
 * @param item Item para ser inserido.
 */
void list_push(void *list, void *item)
{
   register list_item_t **lst;

   lst = (list_item_t**)list;

   if(*lst == NULL) {
      /*
       * Primeiro item da lista.
       */
      *lst = item;
      (*lst)->next = NULL;
      (*lst)->prev = NULL;
      return;
   }

   /*
    * Insere elemento no começo da lista.
    */
   LISTPTR(item)->prev = (*lst)->prev;
   LISTPTR(item)->next = *lst;
   *lst = item;
}

/**
 * Remove um elemento da lista.
 * @param list Ponteiro para o primeiro objeto da lista.
 * @param item Item a ser removido.
 */
void list_remove(void *list, void *item)
{
   list_item_t *p, *q;
   register list_item_t **lst;

   lst = (list_item_t**)list;
   if(item == NULL) return;
   if(*lst == NULL) return;

   /*
    * Aponta item->next para item->prev e vice-versa.
    */
   p = LISTPTR(item)->next;
   q = LISTPTR(item)->prev;

   if(*lst == item) {
      /*
       * Remover o primeiro elemento da lista.
       */
       *lst = p;
       if(p != NULL) p->prev = q;
       return;
   }

   if(p != NULL) p->prev = q;
   else {
      /*
       * Remover último elemento da lista.
       */
      (*lst)->prev = q;
   }
   if(q != NULL) q->next = p;
}

/**
 * Remove e retorna o primeiro elemento da lista.
 * @param list Ponteiro para o primeiro objeto da lista.
 * @return Item removido ou NULL se a lista estava vazia.
 */
void *list_pop(void *list)
{
   register list_item_t *p;
   register list_item_t **lst;

   lst = (list_item_t**)list;
   if(*lst == NULL) return NULL;

   p = (*lst)->next;
   if(p != NULL) p->prev = (*lst)->prev;
   p = *lst;
   *lst = p->next;
   return p;
}

/**
 * Verifica se um elemento faz parte da lista.
 * @param list Ponteiro para o primeiro objeto da lista.
 * @param item Item a verificar.
 * @return TRUE se a lista contém item.
 */
bool_t list_contains(void *list, void *item)
{
   list_item_t *p;
   for(p = (list_item_t*)list; p != NULL; p = p->next) {
      if(item == p) return TRUE;
   }
   return FALSE;
}

/**
 * Retorna a quantidade de elementos em uma lista.
 * @param list Lista a verificar.
 * @return Quantidade de elementos na lista.
 */
uint16_t list_length(void *list)
{
   list_item_t *p;
   int i;
   for(i = 0, p = (list_item_t*)list; p != NULL; p = p->next) i++;
   return i;
}
