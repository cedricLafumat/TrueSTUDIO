/*
 * thread.h
 *
 *  Created on: 24 Apr 2020
 *      Author: cedric
 */

#ifndef INC_THREAD_H_
#define INC_THREAD_H_

void thread_red(void *argument);
void thread_blue(void *argument);
void thread_green(void  *argument);
void thread_timer(void *argument);

#endif /* INC_THREAD_H_ */
