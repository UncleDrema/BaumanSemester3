//
// Created by archdrema on 11/17/22.
//

#ifndef __QUEUE_H
#define __QUEUE_H

#include "err.h"
#include <stddef.h>

#define queue_name(subname, type) queue_ ## subname ## _ ## type ## _t
#define queue_enqueue(subname, type)  queue_enqueue_ ## subname ## _ ## type ## _t
#define queue_dequeue(subname, type)  queue_dequeue_ ## subname ## _ ## type ## _t
#define queue_alloc(subname, type)  queue_alloc_ ## subname ## _ ## type ## _t
#define queue_len(subname, type)  queue_len_ ## subname ## _ ## type ## _t
#define queue_free(subname, type)  queue_free_ ## subname ## _ ## type ## _t
#define queue_sizeof(subname, type) queue_sizeof_ ## subname ## _ ## type ## _t

#define queue_def(subname, type) \
typedef struct queue_name(subname, type) queue_name(subname, type);\
err_t queue_enqueue(subname, type) (queue_name(subname, type) *queue, type element); \
err_t queue_dequeue(subname, type) (queue_name(subname, type) *queue, type *result);   \
queue_name(subname, type) *queue_alloc(subname, type)();           \
void queue_free(subname, type)(queue_name(subname, type) *queue);  \
size_t queue_len(subname, type) (queue_name(subname, type) *queue);\
size_t queue_sizeof(subname, type)(queue_name(subname, type) *queue);

#endif
