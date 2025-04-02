#ifndef __LOG_H  //用于条件编译是否启动下位机日志系统
#define __LOG_H

#include "main.h"
	#define USER_MAIN_DEBUG //条件定义
	#ifdef  USER_MAIN_DEBUG  //条件编译,如果定义了USER_MAIN_DEBUG在下面四个宏被调用时就能打印不同

	#define user_main_printf(format, ...)   printf(format "\r\n",##__VA_ARGS__)//可变参数宏，##无参时传，
	#define user_main_info(format, ...)			printf("[main]info: " format "\r\n", ##__VA_ARGS__)
	#define user_main_debug(format, ...)		printf("[main]debug: " format "\r\n", ##__VA_ARGS__)
	#define user_main_error(format, ...)		printf("[main]error: " format "\r\n", ##__VA_ARGS__)

	#else    //如果没有定义USER_MAIN_DEBUG将不会打印任何东西，因为没有传参

	#define user_main_printf(format, ...)
	#define user_main_info(format, ...)
	#define user_main_debug(format, ...)
	#define user_main_error(format, ...)

	#endif

	#define LOG 1  //1为启用 0为禁用
	
#endif
//日志系统在delay.c中触发
