/*
 * jmm_log.c
 *
 *  Created on: 2012-6-11
 *      Author: buf1024@gmail.com
 */

#include "jmm_cmmhdr.h"
#include "jmm_log.h"
#include "jmm_conf.h"

extern jmm_conf conf;

int jmm_init_log()
{
    CLOG_INITIALIZE_DEFAULT(conf.log_term_lvl, conf.log_file_lvl, conf.log_file_path);
    return JMM_SUCCESS;
}
int jmm_uninit_log()
{
    CLOG_FINISH();
    return JMM_SUCCESS;
}

int jmm_init_log_wf()
{
    CLOG_CLEARUP();
    CLOG_INITIALIZE_DEFAULT(conf.log_term_lvl, conf.log_file_lvl, conf.log_file_path);
    return JMM_SUCCESS;
}
int jmm_uninit_log_wf()
{
    CLOG_FINISH();
    return JMM_SUCCESS;
}

