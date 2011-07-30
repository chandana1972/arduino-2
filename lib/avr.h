#ifndef _AVR_H_
#define _AVR_H_

#define CYCLES_PER_MS   (F_CPU / 1000000L)
#define CYCLES_TO_MS(a) (((a) * 1000L) / (F_CPU / 1000L))
#define MS_TO_CYCLES(a) (((a) * (F_CPU / 1000L)) / 1000L)


#endif /* _AVR_H_ */

