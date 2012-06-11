/*
 * clog.h
 *
 *  Created on: 2012-5-9
 *      Author: buf1024@gmail.com
 */

#ifndef __48SLOTS_CLOG_H__
#define __48SLOTS_CLOG_H__

#include <stdarg.h>

#define CLOG_DEBUG(...)                                              \
do{                                                                  \
    clog_debug(__VA_ARGS__);                                         \
}while(0)                                                            \

#define CLOG_INFO(...)                                               \
do{                                                                  \
    clog_info(__VA_ARGS__);                                          \
}while(0)                                                            \

#define CLOG_WARN(...)                                               \
do{                                                                  \
    clog_warn(__VA_ARGS__);                                          \
}while(0)                                                            \

#define CLOG_ERROR(...)                                              \
do{                                                                  \
    clog_error(__VA_ARGS__);                                         \
}while(0)                                                            \

#define CLOG_FATAL(...)                                              \
do{                                                                  \
    clog_fatal(__VA_ARGS__);                                         \
}while(0)                                                            \

#define CLOG_FINISH()                                                \
do{                                                                  \
    clog_finish();                                                   \
}while(0)                                                            \

#define CLOG_REGISTER_CALLBACK(lvl, init_fun, init_args,             \
        log_fun, log_args, uninit_fun, uninit_args)                  \
    clog_register_callback(#lvl, init_fun, init_args,                \
            log_fun, log_args, uninit_fun, uninit_args);             \
}while(0)                                                            \

#define CLOG_INITIALIZE()                                            \
do{                                                                  \
    clog_initialize();                                               \
}while(0)                                                            \

#define CLOG_INITIALIZE_DEFAULT(con_lvl, file_lvl, file_path)        \
do{                                                                  \
    clog_register_callback(#con_lvl,                                 \
            clog_console_init_callback_fun, 0,                       \
            clog_console_log_callback_fun, 0,                        \
            clog_console_uninit_callback_fun, 0);                    \
    clog_register_callback(#file_lvl,                                \
            clog_file_init_callback_fun, file_path,                  \
            clog_file_log_callback_fun, 0,                           \
            clog_file_uninit_callback_fun, 0);                       \
    clog_initialize();                                               \
}while(0)                                                            \


enum LogLevel
{
    CLOG_ALL     = 0,
    CLOG_DEBUG   = 100,
    CLOG_INFO    = 200,
    CLOG_WARN    = 300,
    CLOG_ERROR   = 400,
    CLOG_FATAL   = 500,
    CLOG_OFF     = 600
};

/* 回调函数原型 */
typedef void (*clog_init_callback_fun)(void* args);
typedef void (*clog_log_callback_fun)(int loglvl, int reqlvl, const char* format,
        va_list ap, void* args);
typedef void (*clog_uninit_callback_fun)(void* args);

/* 注册回调函数 */
void clog_register_callback(const char* lvl,
        clog_init_callback_fun init_cb, void* init_args,
        clog_log_callback_fun log_cb, void* log_args,
        clog_uninit_callback_fun uninit_cb, void* uninit_args);
/* 日志初始化，在主线程初始化 */
void clog_initialize();

/* 写日志 */
void clog_debug(const char* format, ...);
void clog_info (const char* format, ...);
void clog_warn (const char* format, ...);
void clog_error(const char* format, ...);
void clog_fatal(const char* format, ...);

/* 日志结束，在主线程调用 */
void clog_finish();

/* 默认的控制台回调整函数 */
void clog_console_init_callback_fun(void* args);
void clog_console_log_callback_fun(int loglvl, int reqlvl, const char* format,
        va_list ap, void* args);
void clog_console_uninit_callback_fun(void* args);

int clog_get_level(const char* lvl);

/* 默认的文件回调整函数 */
void clog_file_init_callback_fun(void* args);
void clog_file_log_callback_fun(int loglvl, int reqlvl, const char* format,
        va_list ap, void* args);
void clog_file_uninit_callback_fun(void* args);

#endif /* __48SLOTS_CLOG_H__ */
