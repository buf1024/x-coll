/*
 * myserver.c
 *
 *  Created on: 2012-6-8
 *      Author: buf1024@gmail.com
 */

#include "jmm.h"


static const char* my_name()
{
    return "jmm";
}
static const char* my_version()
{
    return "0.01";
}
static const char* my_desc()
{
    return "process pool server";
}

static void myserver_init_hook(jmm_hook* hook)
{
    hook->prog_desc = my_desc;
    hook->prog_name = my_name;
    hook->prog_version = my_version;
}
REG_INIT_HOOK_FUN(myserver_init_hook)
