/*
 * jcc.c
 *
 *  Created on: 2012-6-13
 *      Author: buf1024@gmail.com
 */

#include "jcc_cmmhdr.h"
#include "jcc_event.h"
#include "jcc_proc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/socket.h>
#include <event2/event.h>

#define JCC_VERSION        "0.01"
#define JCC_NAME           "jcc"

static int jcc_is_runas_root();
static void jcc_daemonlize();
static void jcc_version();
static void jcc_usage();

int main(int argc, char **argv)
{
    struct event_base* base = NULL;
    const char* optstr = "i:p:ehv";
    struct option optlong[] = {
            { "ip", 1, NULL, 'i' },
            { "port", 1, NULL, 'p' },
            { "exclude", 0, NULL, 'e' },
            { "version", 0, NULL, 'v' },
            { "help", 0, NULL, 'h' },
            { NULL, 0, NULL, 0 }
    };

    int daemon = 1;
    char host[JCC_MAX_IP_LEN] = "";
    int port = 0;

    // no root
    if (jcc_is_runas_root() == JCC_TRUE) {
        fprintf(stderr, "%s is not allow to run as root!\n", JCC_NAME);
        exit(JCC_FAIL);
    }

    int opt;
    while ((opt = getopt_long(argc, argv, optstr, optlong, NULL)) != -1) {
        switch (opt) {
        case 'i':
            strncpy(host, optarg, JCC_MAX_IP_LEN - 1);
            break;
        case 'p':
            port = atoi(optarg);
            break;
        case 'e':
            daemon = 0;
            break;
        case 'v':
            jcc_version();
            exit(JCC_SUCCESS);
            break;
        case 'h':
            jcc_usage();
            exit(JCC_SUCCESS);
            break;
        case ':':
        case '?':
            jcc_usage();
            exit(JCC_FAIL);
            break;
        default:
            break;
        }
    }

    if(strlen(host) == 0 || port <= 0 || port >= USHRT_MAX){
        fprintf(stdout, "address or port is not valid. address=%s, port=%d\n",
                host, port);
        exit(JCC_FAIL);
    }

    if(daemon){
        jcc_daemonlize();
    }

    base = event_base_new();
    if(base == NULL){
        fprintf(stdout, "fail to create event_base!\n");
        exit(JCC_FAIL);
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if(jcc_init_event(base, (struct sockaddr*)&addr, sizeof(addr)) == JCC_FAIL){
        event_base_free(base);
        exit(JCC_FAIL);
    }

    if(jcc_init_worker() == JCC_FAIL){
        fprintf(stdout, "fail to create worker thread.\n");
        jcc_uninit_event();
        event_base_loopexit(base, NULL);
        exit(JCC_FAIL);
    }

    event_base_dispatch(base);

    jcc_uninit_event();
    jcc_uninit_workder();

    event_base_free(base);

    return JCC_SUCCESS;
}


static int jcc_is_runas_root()
{
    if(getuid() == 0 || geteuid() == 0){
        return JCC_TRUE;
    }
    return JCC_FALSE;
}
static void jcc_daemonlize()
{
    int pid = 0;
    if((pid = fork()) > 0)
    {
        exit(0);
    }
    setsid();
    if((pid = fork()) > 0)
    {
        exit(0);
    }
}
static void jcc_version()
{
    printf("%s version : %s\n", JCC_NAME, JCC_VERSION);
}
static void jcc_usage()
{
    printf("%s ---- %s\n\n", JCC_NAME, JCC_VERSION);
    printf("  -i, --ip=ip/host address            Specific the ip/host address\n");
    printf("  -p, --port=port number              Specific the port number\n");
    printf("  -e, --exclude                       Don't start as daemon process\n");
    printf("  -v, --version                       Print the program version message\n");
    printf("  -h, --help                          Print this help message\n");
}

