
#include <LPC17xx.h>
#include <kernel.h>
#include <t_syslog.h>

#include "kernel_cfg.h"
#include "task_menu.h"
#include "task_led.h"
#include "task_display.h"
#include "task_audio.h"
#include "oled.h"

#define MSG_DEVICE(n) (((n) & 0xF000) >> 12)
#define MSG_TYPE(n)   (((n) & 0x0C00) >> 10)
#define MSG_VALUE(n)  (((n) & 0x03FF) >>  0)

/*
 * $B%a%K%e!<%?%9%/$N?w7A!#(B
 * $B4JC1$K3,AX2=$,$G$-$k!#(B
 */

typedef enum {
    PAGE_TOP,
    PAGE_100,
    PAGE_200,
    PAGE_300,
    PAGE_VER
} PAGEID;

typedef enum {
    PAGE_IN,
    PAGE_TICK,
    PAGE_OUT
} ACTION;

typedef struct {
    PAGEID curr_page;
    PAGEID next_page[4];
    void (*func)(ACTION act);
} menu_t;

static PAGEID curr_page = PAGE_TOP;

#define DISP_MENUNAME(NAME) \
    do { \
        DISP_FILLBOX(0, 0, OLED_X - 1, 8, \
                0x00, 0x00, 0x00, \
                0x00, 0x00, 0x00); \
        DISP_TEXT(0, 0, 0xFF, 0xFF, 0xFF, (NAME)); \
    } while(0)

#define DISP_MENUTAG(A,B,C,D) \
    do { \
        DISP_FILLBOX(0, 52, OLED_X - 1, OLED_Y - 1, \
                0x00, 0x00, 0x00, \
                0x00, 0x00, 0x00); \
        DISP_TEXT(2 + (24 * 0), 52, 0xFF, 0xFF, 0xFF, (A)); \
        DISP_TEXT(2 + (24 * 1), 52, 0xFF, 0xFF, 0xFF, (B)); \
        DISP_TEXT(2 + (24 * 2), 52, 0xFF, 0xFF, 0xFF, (C)); \
        DISP_TEXT(2 + (24 * 3), 52, 0xFF, 0xFF, 0xFF, (D)); \
    } while(0)

void page_splash(ACTION act)
{
    /* $BB>$N%?%9%/$,=i4|2=>uBV$rI=<($9$k$?$a(B
     * $B$3$N%?%9%/$G$O2?$bI=<($7$J$$!#(B
     */
}

void page_top(ACTION act)
{
    if (act == PAGE_IN) {
        DISP_CLEAR(0x00, 0x00, 0x00);
        DISP_MENUNAME("[TOP]");
        DISP_MENUTAG("M-1", "M-2", "M-3", "VER");
    }
    if (act == PAGE_OUT) {
        DISP_CLEAR(0x00, 0x00, 0x00);
    }
}

void page_100(ACTION act)
{
    if (act == PAGE_IN) {
        DISP_CLEAR(0x00, 0x00, 0x00);
        DISP_MENUNAME("[MENU-1]");
        DISP_TEXT(20, 30, 0xFF, 0xFF, 0xFF, "-- MENU 1 --");
        DISP_MENUTAG("", "", "", "RET");
    }
    if (act == PAGE_OUT) {
        DISP_CLEAR(0x00, 0x00, 0x00);
    }
}

void page_200(ACTION act)
{
    if (act == PAGE_IN) {
        DISP_CLEAR(0x00, 0x00, 0x00);
        DISP_MENUNAME("[MENU-2]");
        DISP_TEXT(20, 30, 0xFF, 0xFF, 0xFF, "-- MENU 2 --");
        DISP_MENUTAG("", "", "", "RET");
    }
    if (act == PAGE_OUT) {
        DISP_CLEAR(0x00, 0x00, 0x00);
    }
}

void page_300(ACTION act)
{
    if (act == PAGE_IN) {
        DISP_CLEAR(0x00, 0x00, 0x00);
        DISP_MENUNAME("[MENU-3]");
        DISP_TEXT(20, 30, 0xFF, 0xFF, 0xFF, "-- MENU 3 --");
        DISP_MENUTAG("", "", "", "RET");
    }
    if (act == PAGE_OUT) {
        DISP_CLEAR(0x00, 0x00, 0x00);
    }
}

void page_ver(ACTION act)
{
    if (act == PAGE_IN) {
        DISP_CLEAR(0x00, 0x00, 0x00);
        DISP_MENUNAME("[Version]");
        DISP_TEXT(20, 30, 0xFF, 0xFF, 0xFF, "Preliminary");
        DISP_MENUTAG("", "", "", "RET");
    }
    if (act == PAGE_OUT) {
        DISP_CLEAR(0x00, 0x00, 0x00);
    }
}

static const menu_t menu[6] = {
    {PAGE_TOP, {PAGE_100, PAGE_200, PAGE_300, PAGE_VER}, page_top},
    {PAGE_100, {PAGE_100, PAGE_100, PAGE_100, PAGE_TOP}, page_100},
    {PAGE_200, {PAGE_200, PAGE_200, PAGE_200, PAGE_TOP}, page_200},
    {PAGE_300, {PAGE_300, PAGE_300, PAGE_300, PAGE_TOP}, page_300},
    {PAGE_VER, {PAGE_VER, PAGE_VER, PAGE_VER, PAGE_TOP}, page_ver}
};

void execute_pagefunc(PAGEID page, ACTION act)
{
    int i;
    for (i = 0; i < sizeof(menu) / sizeof(menu[0]); i++) {
        if (menu[i].curr_page == page) {
            if (menu[i].func != NULL) {
                menu[i].func(act);
                return;
            }
        }
    }
}

PAGEID get_next_page(PAGEID page, int sw)
{
    int i;
    for (i = 0; i < sizeof(menu) / sizeof(menu[0]); i++) {
        if (menu[i].curr_page == page) {
            return menu[i].next_page[sw];
        }
    }
    return page;
}

void task_menu(intptr_t exinf)
{
    uint16_t msg;

    DISP_CLEAR(0x00, 0x00, 0x00);

    execute_pagefunc(curr_page, PAGE_IN);
    while(1)
    {
        execute_pagefunc(curr_page, PAGE_TICK);
        while (prcv_dtq(DTQ_USERINPUT, (intptr_t *)&msg) == E_OK) {
            if ((SW0 <= MSG_DEVICE(msg)) && (MSG_DEVICE(msg) <= SW3)) {
                if (MSG_VALUE(msg)) {
                    PAGEID next_page = get_next_page(
                            curr_page, MSG_DEVICE(msg));
                    if (next_page != curr_page) {
                        execute_pagefunc(curr_page, PAGE_OUT);
                        curr_page = next_page;
                        execute_pagefunc(curr_page, PAGE_IN);
                    }
                }
                switch (MSG_DEVICE(msg)) {
                    case SW0:
                        LEDMSG(SWLED0, MSG_VALUE(msg));
                        break;
                    case SW1:
                        LEDMSG(SWLED1, MSG_VALUE(msg));
                        break;
                    case SW2:
                        LEDMSG(SWLED2, MSG_VALUE(msg));
                        break;
                    case SW3:
                        LEDMSG(SWLED3, MSG_VALUE(msg));
                        break;
                }
            }
            if ((VOL0 <= MSG_DEVICE(msg)) && (MSG_DEVICE(msg) <= VOL3)) {
                /*
                 * Draw the level meter.
                 */
                if (curr_page == PAGE_TOP) {
                    static const int MAXVAL = (1024/ 32);
                    static const int XOFS = 10;
                    static const int YOFS = 15;
                    int ch = MSG_DEVICE(msg) - VOL0;
                    int val = MAXVAL - (MSG_VALUE(msg) / 32);
                    DISP_FILLBOX(
                            XOFS + ch * 20, YOFS + 0,
                            XOFS + ch * 20 + 10, YOFS + val,
                            0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00);
                    DISP_FILLBOX(
                            XOFS + ch * 20, YOFS + val,
                            XOFS + ch * 20 + 10, YOFS + MAXVAL,
                            0xFF, 0xFF, 0xFF,
                            0xFF, 0xFF, 0xFF);
                }
                /*
                 * Call the parameter setup interface.
                 */
                switch (MSG_DEVICE(msg)) {
                    case VOL0:
                        AUDIO_PARAM(AUDIO_PARAM_VAR0, MSG_VALUE(msg));
                        break;
                    case VOL1:
                        AUDIO_PARAM(AUDIO_PARAM_VAR1, MSG_VALUE(msg));
                        break;
                    case VOL2:
                        AUDIO_PARAM(AUDIO_PARAM_VAR2, MSG_VALUE(msg));
                        break;
                    case VOL3:
                        AUDIO_PARAM(AUDIO_PARAM_VAR3, MSG_VALUE(msg));
                        break;
                    default:
                        break;
                }
            }
        }
        tslp_tsk(100);
    }
}

