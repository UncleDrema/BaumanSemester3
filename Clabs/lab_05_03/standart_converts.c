#include "standart_converts.h"

GEN_IO_BODY(long, "%ld", "%ld")

GEN_IO_BODY(int, "%d", "%d")

GEN_IO_BODY(int64_t, "%"SCNd64, "%"PRId64)

GEN_IO_BODY(int32_t, "%"SCNd32, "%"PRId32)

GEN_IO_BODY(int16_t, "%"SCNd16, "%"PRId16)

GEN_IO_BODY(float, "%f", "%f")

GEN_IO_BODY(double, "%lf", "%lf")

GEN_IO_BODY(char, "%c", "%c")
