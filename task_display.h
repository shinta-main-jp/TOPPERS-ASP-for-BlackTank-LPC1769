/**
 * \file task_ledblink.h
 * \brief $B%"%W%j%1!<%7%g%sMQ%$%s%/%k!<%I%U%!%$%k!#%3%s%U%#%.%e%l!<%?$bFI$_9~$`!#(B
 */
#ifndef _TASK_DISPLAY_H_
#define _TASK_DISPLAY_H_

/*
 *  $B%?!<%2%C%H0MB8$NDj5A(B
 */
#include "target_test.h"

/*
 *  $B3F%?%9%/$NM%@hEY$NDj5A(B
 */

#define TSKPRI_DISPLAY    13

/*
 *  $B4X?t$N%W%m%H%?%$%W@k8@(B
 */
#ifndef TOPPERS_MACRO_ONLY

extern void	task_display(intptr_t exinf);

#endif /* TOPPERS_MACRO_ONLY */

#endif /* _TASK_DISPLAY_H_ */

