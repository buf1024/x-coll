/*
 * clog.c
 *
 *  Created on: 2012-5-9
 *      Author: buf1024@gmail.com
 */

#include "clog.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>

struct call_back
{
    int level;

    clog_init_callback_fun init_cb_fun;
    void* init_cb_args;

    clog_log_callback_fun log_cb_fun;
    void* log_cb_args;

    clog_uninit_callback_fun uninit_cb_fun;
    void* uninit_cb_args;

    struct call_back* next;
};

struct clog_context
{
    struct call_back* cb;
};

static struct clog_context _context   = {0};
static pthread_mutex_t     _ctx_mutex = PTHREAD_MUTEX_INITIALIZER;

int clog_get_level(const char* lvl)
{
    if (lvl) {
        if (strcasecmp(lvl, "all") == 0) {
            return CLOG_ALL;
        } else if (strcasecmp(lvl, "debug") == 0) {
            return CLOG_DEBUG;
        } else if (strcasecmp(lvl, "info") == 0) {
            return CLOG_INFO;
        } else if (strcasecmp(lvl, "warn") == 0) {
            return CLOG_WARN;
        } else if (strcasecmp(lvl, "error") == 0) {
            return CLOG_ERROR;
        } else if (strcasecmp(lvl, "fatal") == 0) {
            return CLOG_FATAL;
        } else if (strcasecmp(lvl, "off") == 0) {
            return CLOG_OFF;
        }
    }

    return CLOG_ALL;
}

static void clog_message(int lvl, const char* format, va_list ap)
{
    struct call_back* cb = _context.cb;
    while(cb){
        cb->log_cb_fun(cb->level, lvl, format, ap, cb->log_cb_args);
        cb = cb->next;
    }
}

void clog_register_callback(int lvl,
        clog_init_callback_fun init_cb, void* init_args,
        clog_log_callback_fun log_cb, void* log_args,
        clog_uninit_callback_fun uninit_cb, void* uninit_args)
{
    pthread_mutex_lock(&_ctx_mutex);
    struct call_back* cb = (struct call_back*)malloc(sizeof(struct call_back));
    if(cb){
        cb->level = lvl;//clog_get_level(lvl);
        cb->init_cb_fun = init_cb;
        cb->init_cb_args = init_args;
        cb->log_cb_fun = log_cb;
        cb->log_cb_args = log_args;
        cb->uninit_cb_fun = uninit_cb;
        cb->uninit_cb_args = uninit_args;
        cb->next = 0;

        if(_context.cb == 0){
            _context.cb = cb;
        }else{
            struct call_back* iter_cb = _context.cb;
            while(iter_cb->next){
                iter_cb = iter_cb->next;
            }
            iter_cb->next = cb;
        }
    }
    pthread_mutex_unlock(&_ctx_mutex);
}
void clog_initialize()
{
    struct call_back* cb = _context.cb;
    while(cb){
        cb->init_cb_fun(cb->init_cb_args);
        cb = cb->next;
    }
}

void clog_clearup()
{
    memset(&_context, 0, sizeof(_context));
    memset(&_ctx_mutex, 0, sizeof(_ctx_mutex)); //PTHREAD_MUTEX_INITIALIZER;
}

void clog_debug(const char* format, ...)
{
    va_list ap;

    pthread_mutex_lock(&_ctx_mutex);
    va_start(ap, format);
    clog_message(CLOG_DEBUG, format, ap);
    va_end(ap);
    pthread_mutex_unlock(&_ctx_mutex);
}
void clog_info (const char* format, ...)
{
    va_list ap;

    pthread_mutex_lock(&_ctx_mutex);
    va_start(ap, format);
    clog_message(CLOG_INFO, format, ap);
    va_end(ap);
    pthread_mutex_unlock(&_ctx_mutex);
}
void clog_warn (const char* format, ...)
{
    va_list ap;

    pthread_mutex_lock(&_ctx_mutex);
    va_start(ap, format);
    clog_message(CLOG_WARN, format, ap);
    va_end(ap);
    pthread_mutex_unlock(&_ctx_mutex);
}
void clog_error(const char* format, ...)
{
    va_list ap;

    pthread_mutex_lock(&_ctx_mutex);
    va_start(ap, format);
    clog_message(CLOG_ERROR, format, ap);
    va_end(ap);
    pthread_mutex_unlock(&_ctx_mutex);
}
void clog_fatal(const char* format, ...)
{
    va_list ap;

    pthread_mutex_lock(&_ctx_mutex);
    va_start(ap, format);
    clog_message(CLOG_FATAL, format, ap);
    va_end(ap);
    pthread_mutex_unlock(&_ctx_mutex);
}

void clog_finish()
{
    pthread_mutex_lock(&_ctx_mutex);

    struct call_back* cb = _context.cb;
    while(cb){
        struct call_back* tmp_cb = cb;
        cb->uninit_cb_fun(cb->uninit_cb_args);
        cb = cb->next;
        free(tmp_cb);
    }

    pthread_mutex_unlock(&_ctx_mutex);
}


/////////////////////////////////////
// default appender
#define CLOG_DEFAULT_BUFFER_SIZE 4096
#define CLOG_DEFAULT_HEAD_SIZE   128
#define CLOG_DEFAULT_MAX_PATH    256
static const char* clog_get_header(int lvl, char* buf, int size)
{
    const char* head = 0;
    switch(lvl)
    {
    case CLOG_DEBUG:
        head = "[D]";
        break;
    case CLOG_INFO:
        head = "[I]";
        break;
    case CLOG_WARN:
        head = "[W]";
        break;
    case CLOG_ERROR:
        head = "[E]";
        break;
    case CLOG_FATAL:
        head = "[F]";
        break;
    default:
        break;
    }
    snprintf(buf, size, "%s[%ld] ", head, (long)time(0));

    return buf;
}
void clog_console_init_callback_fun(void* args)
{
}
void clog_console_log_callback_fun(int loglvl, int reqlvl, const char* format,
        va_list ap, void* args)
{
    if(reqlvl >= loglvl){
        char head[CLOG_DEFAULT_HEAD_SIZE] = {0};
        clog_get_header(reqlvl, head, CLOG_DEFAULT_HEAD_SIZE);
        fprintf(stdout, head);
        vfprintf(stdout, format, ap);
    }
}
void clog_console_uninit_callback_fun(void* args)
{

}

static FILE* _fp = 0;
void clog_file_init_callback_fun(void* args)
{
    if(_fp != NULL){
        fclose(_fp);
    }
    char file[CLOG_DEFAULT_MAX_PATH] = {0};
    pid_t pid = getpid();
    snprintf(file, CLOG_DEFAULT_MAX_PATH, "%s.%ld", (const char*)args, (long)pid);
    _fp = fopen(file, "a+");
}
void clog_file_log_callback_fun(int loglvl, int reqlvl, const char* format,
        va_list ap, void* args)
{
    if(reqlvl >= loglvl){
        char head[CLOG_DEFAULT_HEAD_SIZE] = {0};
        clog_get_header(reqlvl, head, CLOG_DEFAULT_HEAD_SIZE);
        fprintf(_fp, head);
        vfprintf(_fp, format, ap);
    }
}
void clog_file_uninit_callback_fun(void* args)
{
    fclose(_fp);
}
