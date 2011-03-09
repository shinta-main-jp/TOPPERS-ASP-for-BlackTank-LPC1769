/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2008 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *      ���դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 *  @(#) $Id: trace_config.h 264 2007-07-12 08:23:10Z hiro $
 */

/*
 *		�ȥ졼�����˴ؤ�������
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�target_config.h�����target_syssvc.h��
 *  �ߤ��饤�󥯥롼�ɤ���롥¾�Υե����뤫��ľ�ܥ��󥯥롼�ɤ��ƤϤ�
 *  ��ʤ���
 */

#ifndef TOPPERS_TRACE_CONFIG_H
#define TOPPERS_TRACE_CONFIG_H

/*
 *  ��ǽ�����ɤ��ɤ߹���
 */
#include "kernel_fncode.h"

/*
 *  �ȥ졼�����Хåե��Υ�����
 */
#ifndef TCNT_TRACE_BUFFER
#define TCNT_TRACE_BUFFER	512
#endif /* TCNT_TRACE_BUFFER */

/*
 *  �ȥ졼����������ѥϡ��ɥ������ν����
 */
#ifndef TRACE_HW_INIT
#define TRACE_HW_INIT()
#endif  /* TRACE_HW_INIT */

/*
 *  �ȥ졼������μ�����ˡ
 */
#ifndef TRACE_GET_TIM
#ifdef TOPPERS_SUPPORT_GET_UTM
#define TRACE_GET_TIM()		(trace_get_tim_utime())
#else
#define TRACE_GET_TIM()		(current_time)
#endif /* TOPPERS_SUPPORT_GET_UTM */
#endif /* TRACE_GET_TIM */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  �ȥ졼�����Υǡ�����¤
 *
 *  �����ƥ����ǽ�Υ�����Υǡ�����¤��Ʊ����Τ��Ѥ��롥
 */
#include <t_syslog.h>
typedef	SYSLOG	TRACE;

/*
 *  �ȥ졼�����Хåե��Ȥ���˥����������뤿��Υݥ���
 */
extern TRACE	trace_buffer[];		/* �ȥ졼�����Хåե� */
extern uint_t	trace_count;		/* �ȥ졼�����Хåե���Υ��ο� */
extern uint_t	trace_head;			/* ��Ƭ�Υȥ졼�����γ�Ǽ���� */
extern uint_t	trace_tail;			/* ���Υȥ졼�����γ�Ǽ���� */
extern uint_t	trace_lost;			/* ����줿�ȥ졼���ο� */

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  �ȥ졼���⡼�ɤ����
 */
#define TRACE_STOP			UINT_C(0x00)	/* �ȥ졼����� */
#define TRACE_RINGBUF		UINT_C(0x01)	/* ��󥰥Хåե��⡼�� */
#define TRACE_AUTOSTOP		UINT_C(0x02)	/* ��ư��ߥ⡼�� */
#define TRACE_CLEAR			UINT_C(0x04)	/* �ȥ졼�����Υ��ꥢ */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  �ȥ졼������ǽ�ν����
 *
 *  �ȥ졼������ǽ���������롥������롼����Ȥ�����Ͽ���뤳�Ȥ���
 *  �ꤷ�Ƥ��롥�����ˤ�꼡��ư���Ԥ���
 *
 *  TRACE_STOP��������Τߤǥȥ졼���ϳ��Ϥ��ʤ���
 *  TRACE_RINGBUF����󥰥Хåե��⡼�ɤǥȥ졼���򳫻ϡ�
 *  TRACE_AUTOSTOP����ư��ߥ⡼�ɤǥȥ졼���򳫻ϡ�
 */
extern void	trace_initialize(intptr_t exinf);

/*
 *  �ȥ졼�����γ���
 *
 *  �ȥ졼�����ε�Ͽ�򳫻ϡ���ߤ��롥�����ˤ�꼡��ư���Ԥ���
 *
 *  TRACE_STOP���ȥ졼������ߡ�
 *  TRACE_RINGBUF����󥰥Хåե��⡼�ɤǥȥ졼���򳫻ϡ�
 *  TRACE_AUTOSTOP����ư��ߥ⡼�ɤǥȥ졼���򳫻ϡ�
 *  TRACE_CLEAR���ȥ졼�����򥯥ꥢ��
 */
extern ER	trace_sta_log(MODE mode);

/*
 *  �ȥ졼�����ν����
 */
extern ER	trace_wri_log(TRACE *p_trace);

/*
 *  �ȥ졼�������ɽФ�
 */
extern ER	trace_rea_log(TRACE *p_trace);

/* 
 *  �ȥ졼�����Υ���ס�trace_dump.c��
 *
 *  �ȥ졼���������פ��롥��λ�����롼����Ȥ�����Ͽ���뤳�Ȥ�����
 *  ���Ƥ��롥�����Ȥ��ơ��������Ȥʤ�ʸ�����ϴؿ��ؤΥݥ��󥿤��Ϥ���
 *  �������åȰ�¸�����٥�ʸ�����Ϥ����Ѥ�����ˤϡ�target_putc����
 *  ����
 */
extern void	trace_dump(intptr_t exinf);

/*
 *  �ȥ졼��������Ϥ��뤿��Υ饤�֥��ؿ�
 */
extern void	trace_write_0(uint_t type);
extern void	trace_write_1(uint_t type, intptr_t arg1);
extern void	trace_write_2(uint_t type, intptr_t arg1, intptr_t arg2);
extern void	trace_write_3(uint_t type, intptr_t arg1, intptr_t arg2, intptr_t arg3);
extern void	trace_write_4(uint_t type, intptr_t arg1, intptr_t arg2, intptr_t arg3, \
                              intptr_t arg4);
extern void	trace_write_5(uint_t type, intptr_t arg1, intptr_t arg2, intptr_t arg3, \
                              intptr_t arg4, intptr_t arg5);
extern void	trace_write_6(uint_t type, intptr_t arg1, intptr_t arg2, intptr_t arg3, \
                              intptr_t arg4, intptr_t arg5, intptr_t arg6);

/*
 *  �ȥ졼��������Ϥ��뤿��Υޥ���
 */

#define trace_0(type) \
				trace_write_0(type)

#define trace_1(type, arg1) \
				trace_write_1(type, (intptr_t)(arg1))

#define trace_2(type, arg1, arg2) \
				trace_write_2(type, (intptr_t)(arg1), (intptr_t)(arg2))

#define trace_3(type, arg1, arg2, arg3) \
				trace_write_3(type, (intptr_t)(arg1), (intptr_t)(arg2), \
						(intptr_t)(arg3))

#define trace_4(type, arg1, arg2, arg3, arg4) \
				trace_write_4(type, (intptr_t)(arg1), (intptr_t)(arg2), \
						(intptr_t)(arg3), (intptr_t)(arg4))

#define trace_5(type, arg1, arg2, arg3, arg4, arg5) \
				trace_write_5(type, (intptr_t)(arg1), (intptr_t)(arg2), \
						(intptr_t)(arg3), (intptr_t)(arg4), \
                                              (intptr_t)(arg5))

#define trace_6(type, arg1, arg2, arg3, arg4, arg5, arg6) \
				trace_write_6(type, (intptr_t)(arg1), (intptr_t)(arg2), \
						(intptr_t)(arg3), (intptr_t)(arg4), \
                                              (intptr_t)(arg5), (intptr_t)(arg6))

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  �ȥ졼������ˡ������
 */

/*
 *  ����ߥϥ�ɥ������
 */
#define LOG_INH_ENTER(inhno) trace_1(LOG_TYPE_INH|LOG_ENTER, inhno)
#define LOG_INH_LEAVE(inhno) trace_1(LOG_TYPE_INH|LOG_LEAVE, inhno)

/*
 *  ����ߥ����ӥ��롼���������
 */
#define LOG_ISR_ENTER(intno) trace_1(LOG_TYPE_ISR|LOG_ENTER, intno)
#define LOG_ISR_LEAVE(intno) trace_1(LOG_TYPE_ISR|LOG_LEAVE, intno)

/*
 *  �����ϥ�ɥ������
 */
#define LOG_CYC_ENTER(p_cyccb) trace_1(LOG_TYPE_CYC|LOG_ENTER, p_cyccb)
#define LOG_CYC_LEAVE(p_cyccb) trace_1(LOG_TYPE_CYC|LOG_LEAVE, p_cyccb)

/*
 *  ���顼��ϥ�ɥ������
 */
#define LOG_ALM_ENTER(p_almcb) trace_1(LOG_TYPE_ALM|LOG_ENTER, p_almcb)
#define LOG_ALM_LEAVE(p_almcb) trace_1(LOG_TYPE_ALM|LOG_LEAVE, p_almcb)

/*
 *  CPU�㳰�ϥ�ɥ������
 */
// #define LOG_EXC_ENTER(excno) trace_1(LOG_TYPE_EXC|LOG_ENTER, excno)
// #define LOG_EXC_LEAVE(excno) trace_1(LOG_TYPE_EXC|LOG_LEAVE, excno)

/*
 *  �������㳰�����롼����
 */
#define LOG_TEX_ENTER(p_tcb, texptn) trace_2(LOG_TYPE_TEX|LOG_ENTER, p_tcb, texptn)
#define LOG_TEX_LEAVE(p_tcb) trace_2(LOG_TYPE_TEX|LOG_LEAVE, p_tcb, texptn)

/*
 *  �������ξ����ѹ�
 */
#define LOG_TSKSTAT(p_tcb) trace_2(LOG_TYPE_TSKSTAT, p_tcb, p_tcb->tstat)

/*
 *  �ǥ����ѥå��������
 */
#define LOG_DSP_ENTER(p_tcb) trace_1(LOG_TYPE_DSP|LOG_ENTER, p_tcb)
#define LOG_DSP_LEAVE(p_tcb) trace_1(LOG_TYPE_DSP|LOG_LEAVE, p_tcb)

/*
 *  �����ƥ���ؤν񤭽Ф�
 */
#define LOG_SYSLOG_WRI_LOG_ENTER(prio, p_syslog) trace_wri_log((TRACE *) p_syslog)

/*
 *  �����ƥॳ����
 */

/*
 *  ������������ǽ
 */
#define LOG_ACT_TSK_ENTER(tskid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_ACT_TSK, tskid)
#define LOG_ACT_TSK_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_ACT_TSK, ercd)

#define LOG_IACT_TSK_ENTER(tskid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_IACT_TSK, tskid)
#define LOG_IACT_TSK_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_IACT_TSK, ercd)

#define LOG_CAN_ACT_ENTER(tskid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_CAN_ACT, tskid)
#define LOG_CAN_ACT_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_CAN_ACT, ercd)

#define LOG_EXT_TSK_ENTER() trace_1(LOG_TYPE_SVC|LOG_ENTER, TFN_EXT_TSK)
#define LOG_EXT_TSK_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_EXT_TSK, ercd)

#define LOG_TER_TSK_ENTER(tskid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_TER_TSK, tskid)
#define LOG_TER_TSK_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_TER_TSK, ercd)

#define LOG_CHG_PRI_ENTER(tskid, tskpri) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_CHG_PRI, tskid, tskpri)
#define LOG_CHG_PRI_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_CHG_PRI, ercd)

#define LOG_GET_PRI_ENTER(tskid, p_tskpri) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_GET_PRI, tskid, p_tskpri)
#define LOG_GET_PRI_LEAVE(ercd, tskpri) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_GET_PRI, ercd, tskpri)

#define LOG_GET_INF_ENTER(p_exinf) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_GET_INF, p_exinf)
#define LOG_GET_INF_LEAVE(ercd, exinf) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_GET_INF, ercd, exinf)


/*
 *  ���������ֻ��ȵ�ǽ
 */
#define LOG_REF_TSK_ENTER(tskid, pk_rtsk) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_REF_TSK, tskid, pk_rtsk)
#define LOG_REF_TSK_LEAVE(ercd, pk_rtsk) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_REF_TSK, ercd, pk_rtsk)


/*
 *  ��������°Ʊ����ǽ
 */
#define LOG_SLP_TSK_ENTER() trace_1(LOG_TYPE_SVC|LOG_ENTER, TFN_SLP_TSK)
#define LOG_SLP_TSK_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_SLP_TSK, ercd)

#define LOG_TSLP_TSK_ENTER(tmout) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_TSLP_TSK, tmout)
#define LOG_TSLP_TSK_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_TSLP_TSK, ercd)

#define LOG_WUP_TSK_ENTER(tskid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_WUP_TSK, tskid)
#define LOG_WUP_TSK_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_WUP_TSK, ercd)

#define LOG_IWUP_TSK_ENTER(tskid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_IWUP_TSK, tskid) 
#define LOG_IWUP_TSK_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_IWUP_TSK, ercd)

#define LOG_CAN_WUP_ENTER(tskid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_CAN_WUP, tskid)
#define LOG_CAN_WUP_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_CAN_WUP, ercd)

#define LOG_REL_WAI_ENTER(tskid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_REL_WAI, tskid)
#define LOG_REL_WAI_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_REL_WAI, ercd)

#define LOG_IREL_WAI_ENTER(tskid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_IREL_WAI, tskid)
#define LOG_IREL_WAI_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_IREL_WAI, ercd)

#define LOG_SUS_TSK_ENTER(tskid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_SUS_TSK, tskid)
#define LOG_SUS_TSK_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_SUS_TSK, ercd)

#define LOG_RSM_TSK_ENTER(tskid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_RSM_TSK, tskid)
#define LOG_RSM_TSK_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_RSM_TSK, ercd)

#define LOG_DLY_TSK_ENTER(dlytim) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_DLY_TSK, dlytim)
#define LOG_DLY_TSK_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_DLY_TSK, ercd)


/*
 *  �������㳰������ǽ
 */
#define LOG_RAS_TEX_ENTER(tskid, rasptn) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_RAS_TEX, tskid, rasptn)
#define LOG_RAS_TEX_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_RAS_TEX, ercd)

#define LOG_IRAS_TEX_ENTER(tskid, rasptn) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_IRAS_TEX, tskid, rasptn)
#define LOG_IRAS_TEX_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_IRAS_TEX, ercd)

#define LOG_DIS_TEX_ENTER() trace_1(LOG_TYPE_SVC|LOG_ENTER, TFN_DIS_TEX)
#define LOG_DIS_TEX_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_DIS_TEX, ercd)

#define LOG_ENA_TEX_ENTER() trace_1(LOG_TYPE_SVC|LOG_ENTER, TFN_ENA_TEX)
#define LOG_ENA_TEX_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_ENA_TEX, ercd)

#define LOG_SNS_TEX_ENTER() trace_1(LOG_TYPE_SVC|LOG_ENTER, TFN_SNS_TEX)
#define LOG_SNS_TEX_LEAVE(state) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_SNS_TEX, state)

#define LOG_REF_TEX_ENTER(tskid, pk_rtex) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_REF_TEX, tskid, pk_rtex)
#define LOG_REF_TEX_LEAVE(ercd, pk_rtex) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_REF_TEX, ercd, pk_rtex)


/*
 *  ���ޥե���ǽ
 */
#define LOG_SIG_SEM_ENTER(semid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_SIG_SEM, semid)
#define LOG_SIG_SEM_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_SIG_SEM, ercd)

#define LOG_ISIG_SEM_ENTER(semid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_ISIG_SEM, semid)
#define LOG_ISIG_SEM_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_ISIG_SEM, ercd)

#define LOG_WAI_SEM_ENTER(semid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_WAI_SEM, semid)
#define LOG_WAI_SEM_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_WAI_SEM, ercd)

#define LOG_POL_SEM_ENTER(semid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_POL_SEM, semid)
#define LOG_POL_SEM_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_POL_SEM, ercd)

#define LOG_TWAI_SEM_ENTER(semid, tmout) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_TWAI_SEM, semid, tmout)
#define LOG_TWAI_SEM_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_TWAI_SEM, ercd)

#define LOG_INI_SEM_ENTER(semid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_INI_SEM, semid)
#define LOG_INI_SEM_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_INI_SEM, ercd)

#define LOG_REF_SEM_ENTER(semid, pk_rsem) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_REF_SEM, semid, pk_rsem)
#define LOG_REF_SEM_LEAVE(ercd, pk_rsem) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_REF_SEM, ercd, pk_rsem)


/*
 *  ���٥�ȥե饰
 */
#define LOG_SET_FLG_ENTER(flgid, setptn) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_SET_FLG, flgid, setptn)
#define LOG_SET_FLG_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_SET_FLG, ercd)

#define LOG_ISET_FLG_ENTER(flgid, setptn) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_ISET_FLG, flgid, setptn)
#define LOG_ISET_FLG_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_ISET_FLG, ercd)

#define LOG_CLR_FLG_ENTER(flgid, clrptn) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_CLR_FLG, flgid, clrptn)
#define LOG_CLR_FLG_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_CLR_FLG, ercd)

#define LOG_WAI_FLG_ENTER(flgid, waiptn, wfmode, p_flgptn) trace_5(LOG_TYPE_SVC|LOG_ENTER, TFN_WAI_FLG, flgid, waiptn, wfmode, p_flgptn)
#define LOG_WAI_FLG_LEAVE(ercd, flgptn) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_WAI_FLG, ercd, flgptn)

#define LOG_POL_FLG_ENTER(flgid, waiptn, wfmode, p_flgptn) trace_5(LOG_TYPE_SVC|LOG_ENTER, TFN_POL_FLG, flgid, waiptn, wfmode, p_flgptn)
#define LOG_POL_FLG_LEAVE(ercd, flgptn) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_POL_FLG, ercd, flgptn)

#define LOG_TWAI_FLG_ENTER(flgid, waiptn, wfmode, p_flgptn, tmout) trace_6(LOG_TYPE_SVC|LOG_ENTER, TFN_TWAI_FLG, flgid, waiptn, wfmode, p_flgptn, tmout)
#define LOG_TWAI_FLG_LEAVE(ercd, flgptn) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_TWAI_FLG, ercd, flgptn)

#define LOG_INI_FLG_ENTER(flgid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_INI_FLG, flgid)
#define LOG_INI_FLG_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_INI_FLG, ercd)

#define LOG_REF_FLG_ENTER(flgid, pk_rflg) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_REF_FLG, flgid, pk_rflg)
#define LOG_REF_FLG_LEAVE(ercd, pk_rflg) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_REF_FLG, ercd, pk_rflg)


/*
 *  �ǡ������塼����
 */
#define LOG_SND_DTQ_ENTER(dtqid, data) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_SND_DTQ, dtqid, data)
#define LOG_SND_DTQ_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_SND_DTQ, ercd)

#define LOG_PSND_DTQ_ENTER(dtqid, data) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_PSND_DTQ, dtqid, data)
#define LOG_PSND_DTQ_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_PSND_DTQ, ercd)

#define LOG_IPSND_DTQ_ENTER(dtqid, data) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_IPSND_DTQ, dtqid, data)
#define LOG_IPSND_DTQ_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_IPSND_DTQ, ercd)

#define LOG_TSND_DTQ_ENTER(dtqid, data, tmout) trace_4(LOG_TYPE_SVC|LOG_ENTER, TFN_TSND_DTQ, dtqid, data, tmout)
#define LOG_TSND_DTQ_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_TSND_DTQ, ercd)

#define LOG_FSND_DTQ_ENTER(dtqid, data) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_FSND_DTQ, dtqid, data)
#define LOG_FSND_DTQ_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_FSND_DTQ, ercd)

#define LOG_IFSND_DTQ_ENTER(dtqid, data) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_IFSND_DTQ, dtqid, data)
#define LOG_IFSND_DTQ_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_IFSND_DTQ, ercd)

#define LOG_RCV_DTQ_ENTER(dtqid, p_data) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_RCV_DTQ, dtqid, p_data)
#define LOG_RCV_DTQ_LEAVE(ercd, data) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_RCV_DTQ, ercd, data)

#define LOG_PRCV_DTQ_ENTER(dtqid, p_data) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_PRCV_DTQ, dtqid, p_data)
#define LOG_PRCV_DTQ_LEAVE(ercd, data) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_PRCV_DTQ, ercd, data)

#define LOG_TRCV_DTQ_ENTER(dtqid, p_data, tmout) trace_4(LOG_TYPE_SVC|LOG_ENTER, TFN_TRCV_DTQ, dtqid, p_data, tmout)
#define LOG_TRCV_DTQ_LEAVE(ercd, data) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_TRCV_DTQ, ercd, data)

#define LOG_INI_DTQ_ENTER(dtqid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_INI_DTQ, dtqid)
#define LOG_INI_DTQ_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_INI_DTQ, ercd)

#define LOG_REF_DTQ_ENTER(dtqid, pk_rdtq) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_REF_DTQ, dtqid, pk_rdtq)
#define LOG_REF_DTQ_LEAVE(ercd, pk_rdtq) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_REF_DTQ, ercd, pk_rdtq)


/*
 *  ͥ���٥ǡ������塼��ǽ
 */
#define LOG_SND_PDQ_ENTER(pdqid, data, datapri) trace_4(LOG_TYPE_SVC|LOG_ENTER, TFN_SND_PDQ, pdqid, data, datapri)
#define LOG_SND_PDQ_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_SND_PDQ, ercd)

#define LOG_PSND_PDQ_ENTER(pdqid, data, datapri) trace_4(LOG_TYPE_SVC|LOG_ENTER, TFN_PSND_PDQ, pdqid, data, datapri)
#define LOG_PSND_PDQ_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_PSND_PDQ, ercd)

#define LOG_IPSND_PDQ_ENTER(pdqid, data, datapri) trace_4(LOG_TYPE_SVC|LOG_ENTER, TFN_IPSND_PDQ, pdqid, data, datapri)
#define LOG_IPSND_PDQ_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_IPSND_PDQ, ercd)

#define LOG_TSND_PDQ_ENTER(pdqid, data, datapri, tmout) trace_5(LOG_TYPE_SVC|LOG_ENTER, TFN_TSND_PDQ, pdqid, data, datapri, tmout)
#define LOG_TSND_PDQ_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_TSND_PDQ, ercd)

#define LOG_RCV_PDQ_ENTER(pdqid, p_data, p_datapri) trace_4(LOG_TYPE_SVC|LOG_ENTER, TFN_RCV_PDQ, pdqid, p_data, p_datapri)
#define LOG_RCV_PDQ_LEAVE(ercd, data, datapri) trace_4(LOG_TYPE_SVC|LOG_LEAVE, TFN_RCV_PDQ, ercd, data, datapri)

#define LOG_PRCV_PDQ_ENTER(pdqid, p_data, p_datapri) trace_4(LOG_TYPE_SVC|LOG_ENTER, TFN_PRCV_PDQ, pdqid, p_data, p_datapri)
#define LOG_PRCV_PDQ_LEAVE(ercd, data, datapri) trace_4(LOG_TYPE_SVC|LOG_LEAVE, TFN_PRCV_PDQ, ercd, data, datapri)

#define LOG_TRCV_PDQ_ENTER(pdqid, p_data, p_datapri, tmout) trace_5(LOG_TYPE_SVC|LOG_ENTER, TFN_TRCV_PDQ, pdqid, p_data, p_datapri, tmout)
#define LOG_TRCV_PDQ_LEAVE(ercd, data, datapri) trace_4(LOG_TYPE_SVC|LOG_LEAVE, TFN_TRCV_PDQ, ercd, data, datapri)

#define LOG_INI_PDQ_ENTER(pdqid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_INI_PDQ, pdqid)
#define LOG_INI_PDQ_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_INI_PDQ, ercd)

#define LOG_REF_PDQ_ENTER(pdqid, pk_rpdq) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_REF_PDQ, pdqid, pk_rpdq)
#define LOG_REF_PDQ_LEAVE(ercd, pk_rpdq) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_REF_PDQ, ercd, pk_rpdq)


/*
 *  �᡼��ܥå�����ǽ
 */
#define LOG_SND_MBX_ENTER(mbxid, pk_msg) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_SND_MBX, mbxid, pk_msg)
#define LOG_SND_MBX_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_SND_MBX, ercd)

#define LOG_RCV_MBX_ENTER(mbxid, ppk_msg) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_RCV_MBX, mbxid, ppk_msg)
#define LOG_RCV_MBX_LEAVE(ercd, pk_msg) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_RCV_MBX, ercd, pk_msg)

#define LOG_PRCV_MBX_ENTER(mbxid, ppk_msg) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_PRCV_MBX, mbxid, ppk_msg)
#define LOG_PRCV_MBX_LEAVE(ercd, pk_msg) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_PRCV_MBX, ercd, pk_msg)

#define LOG_TRCV_MBX_ENTER(mbxid, ppk_msg, tmout) trace_4(LOG_TYPE_SVC|LOG_ENTER, TFN_TRCV_MBX, mbxid, ppk_msg, tmout)
#define LOG_TRCV_MBX_LEAVE(ercd, pk_msg) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_TRCV_MBX, ercd, pk_msg)

#define LOG_INI_MBX_ENTER(mbxid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_INI_MBX, mbxid)
#define LOG_INI_MBX_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_INI_MBX, ercd)

#define LOG_REF_MBX_ENTER(mbxid, pk_rmbx) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_REF_MBX, mbxid, pk_rmbx)
#define LOG_REF_MBX_LEAVE(ercd, pk_rmbx) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_REF_MBX, ercd, pk_rmbx)


/*
 *  ����Ĺ����ס��뵡ǽ
 */
#define LOG_GET_MPF_ENTER(mpfid, p_blk) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_GET_MPF, mpfid, p_blk)
#define LOG_GET_MPF_LEAVE(ercd, blk) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_GET_MPF, ercd, blk)

#define LOG_PGET_MPF_ENTER(mpfid, p_blk) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_PGET_MPF, mpfid, p_blk)
#define LOG_PGET_MPF_LEAVE(ercd, blk) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_PGET_MPF, ercd, blk)

#define LOG_TGET_MPF_ENTER(mpfid, p_blk, tmout) trace_4(LOG_TYPE_SVC|LOG_ENTER, TFN_TGET_MPF, mpfid, p_blk, tmout)
#define LOG_TGET_MPF_LEAVE(ercd, blk) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_TGET_MPF, ercd, blk)

#define LOG_REL_MPF_ENTER(mpfid, blk) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_REL_MPF, mpfid, blk)
#define LOG_REL_MPF_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_REL_MPF, ercd)

#define LOG_INI_MPF_ENTER(mpfid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_INI_MPF, mpfid)
#define LOG_INI_MPF_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_INI_MPF, ercd)

#define LOG_REF_MPF_ENTER(mpfid, pk_rmpf) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_REF_MPF, mpfid, pk_rmpf)
#define LOG_REF_MPF_LEAVE(ercd, pk_rmpf) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_REF_MPF, ercd, pk_rmpf)


/*
 *  �����ƥ���������ǽ
 */
#define LOG_GET_TIM_ENTER(p_systim) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_GET_TIM, p_systim)
#define LOG_GET_TIM_LEAVE(ercd, systim) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_GET_TIM, ercd, systim)

//����¸����get_utm����Ѥ��뤿�ᡤ����ͭ���ˤ���Ƚ۴Ĥ��Ƥ��ޤ�����̵���ˤ���
//#define LOG_GET_UTM_ENTER(p_sysutm) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_GET_UTM, p_sysutm)
//#define LOG_GET_UTM_LEAVE(ercd, sysutm) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_GET_UTM, ercd, sysutm)


/*
 *  �����ϥ�ɥ鵡ǽ
 */
#define LOG_STA_CYC_ENTER(cycid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_STA_CYC, cycid)
#define LOG_STA_CYC_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_STA_CYC, ercd)

#define LOG_STP_CYC_ENTER(cycid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_STP_CYC, cycid)
#define LOG_STP_CYC_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_STP_CYC, ercd)

#define LOG_REF_CYC_ENTER(cycid, pk_rcyc) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_REF_CYC, cycid, pk_rcyc)
#define LOG_REF_CYC_LEAVE(ercd, pk_rcyc) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_REF_CYC, ercd, pk_rcyc)


/*
 *  ���顼��ϥ�ɥ鵡ǽ
 */
#define LOG_STA_ALM_ENTER(almid, almtim) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_STA_ALM, almid, almtim)
#define LOG_STA_ALM_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_STA_ALM, ercd)

#define LOG_ISTA_ALM_ENTER(almid, almtim) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_ISTA_ALM, almid, almtim)
#define LOG_ISTA_ALM_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_ISTA_ALM, ercd)

#define LOG_STP_ALM_ENTER(almid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_STP_ALM, almid)
#define LOG_STP_ALM_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_STP_ALM, ercd)

#define LOG_ISTP_ALM_ENTER(almid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_ISTP_ALM, almid)
#define LOG_ISTP_ALM_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_ISTP_ALM, ercd)

#define LOG_REF_ALM_ENTER(almid, pk_ralm) trace_3(LOG_TYPE_SVC|LOG_ENTER, TFN_REF_ALM, almid, pk_ralm)
#define LOG_REF_ALM_LEAVE(ercd, pk_ralm) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_REF_ALM, ercd, pk_ralm)


/*
 *  ����ߴ�����ǽ
 */
#define LOG_DIS_INT_ENTER(intno) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_DIS_INT, intno)
#define LOG_DIS_INT_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_DIS_INT, ercd)

#define LOG_ENA_INT_ENTER(intno) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_ENA_INT, intno)
#define LOG_ENA_INT_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_ENA_INT, ercd)

#define LOG_CHG_IPM_ENTER(intpri) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_CHG_IPM, intpri)
#define LOG_CHG_IPM_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_CHG_IPM, ercd)

#define LOG_GET_IPM_ENTER(p_intpri) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_GET_IPM, p_intpri)
#define LOG_GET_IPM_LEAVE(ercd, intpri) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_GET_IPM, ercd, intpri)


/*
 *  CPU�㳰������ǽ
 */
#define LOG_XSNS_DPN_ENTER(p_excinf) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_XSNS_DPN, p_excinf)
#define LOG_XSNS_DPN_LEAVE(state) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_XSNS_DPN, state)

#define LOG_XSNS_XPN_ENTER(p_excinf) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_XSNS_XPN, p_excinf)
#define LOG_XSNS_XPN_LEAVE(state) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_XSNS_XPN, state)


/*
 *  �����ƥ���ִ�����ǽ
 */
#define LOG_ROT_RDQ_ENTER(tskpri) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_ROT_RDQ, tskpri)
#define LOG_ROT_RDQ_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_ROT_RDQ, ercd)

#define LOG_IROT_RDQ_ENTER(tskpri) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_IROT_RDQ, tskpri)
#define LOG_IROT_RDQ_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_IROT_RDQ, ercd)

//#define LOG_GET_TID_ENTER(p_tskid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_GET_TID, p_tskid)
//#define LOG_GET_TID_LEAVE(ercd, tskid) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_GET_TID, ercd, tskid)

//#define LOG_IGET_TID_ENTER(p_tskid) trace_2(LOG_TYPE_SVC|LOG_ENTER, TFN_IGET_TID, p_tskid)
//#define LOG_IGET_TID_LEAVE(ercd, tskid) trace_3(LOG_TYPE_SVC|LOG_LEAVE, TFN_IGET_TID, ercd, tskid)

//#define LOG_LOC_CPU_ENTER() trace_1(LOG_TYPE_SVC|LOG_ENTER, TFN_LOC_CPU)
//#define LOG_LOC_CPU_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_LOC_CPU, ercd)

//#define LOG_ILOC_CPU_ENTER() trace_1(LOG_TYPE_SVC|LOG_ENTER, TFN_ILOC_CPU)
//#define LOG_ILOC_CPU_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_ILOC_CPU, ercd)

//#define LOG_UNL_CPU_ENTER() trace_1(LOG_TYPE_SVC|LOG_ENTER, TFN_UNL_CPU)
//#define LOG_UNL_CPU_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_UNL_CPU, ercd)

//#define LOG_IUNL_CPU_ENTER() trace_1(LOG_TYPE_SVC|LOG_ENTER, TFN_IUNL_CPU)
//#define LOG_IUNL_CPU_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_IUNL_CPU, ercd)

//#define LOG_DIS_DSP_ENTER() trace_1(LOG_TYPE_SVC|LOG_ENTER, TFN_DIS_DSP)
//#define LOG_DIS_DSP_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_DIS_DSP, ercd)

//#define LOG_ENA_DSP_ENTER() trace_1(LOG_TYPE_SVC|LOG_ENTER, TFN_ENA_DSP)
//#define LOG_ENA_DSP_LEAVE(ercd) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_ENA_DSP, ercd)

//#define LOG_SNS_CTX_ENTER() trace_1(LOG_TYPE_SVC|LOG_ENTER, TFN_SNS_CTX)
//#define LOG_SNS_CTX_LEAVE(state) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_SNS_CTX, state)

//#define LOG_SNS_LOC_ENTER() trace_1(LOG_TYPE_SVC|LOG_ENTER, TFN_SNS_LOC)
//#define LOG_SNS_LOC_LEAVE(state) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_SNS_LOC, state)

//#define LOG_SNS_DSP_ENTER() trace_1(LOG_TYPE_SVC|LOG_ENTER, TFN_SNS_DSP)
//#define LOG_SNS_DSP_LEAVE(state) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_SNS_DSP, state)

//#define LOG_SNS_DPN_ENTER() trace_1(LOG_TYPE_SVC|LOG_ENTER, TFN_SNS_DPN)
//#define LOG_SNS_DPN_LEAVE(state) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_SNS_DPN, state)

//#define LOG_SNS_KER_ENTER() trace_1(LOG_TYPE_SVC|LOG_ENTER, TFN_SNS_KER)
//#define LOG_SNS_KER_LEAVE(state) trace_2(LOG_TYPE_SVC|LOG_LEAVE, TFN_SNS_KER, state)


/*
 *  �����ͥ�ν�����Ƚ�λ����
 */
#define LOG_KER_ENTER()
#define LOG_KER_LEAVE()
#define LOG_EXT_KER_ENTER() trace_1(LOG_TYPE_SVC|LOG_ENTER, TFN_EXT_KER)
#define LOG_EXT_KER_LEAVE()


/*
 *  �����ƥ����ǽ
 */
#define LOG_SYSLOG_WRI_LOG_LEAVE(ercd)
#define LOG_SYSLOG_REA_LOG_ENTER(p_syslog)
#define LOG_SYSLOG_REA_LOG_LEAVE(ercd, p_syslog)
#define LOG_SYSLOG_MSK_LOG_ENTER(logmask, lowmask)
#define LOG_SYSLOG_MSK_LOG_LEAVE(ercd)
#define LOG_SYSLOG_REF_LOG_ENTER(pk_rlog)
#define LOG_SYSLOG_REF_LOG_LEAVE(pk_rlog)

#endif /* TOPPERS_TRACE_CONFIG_H */
