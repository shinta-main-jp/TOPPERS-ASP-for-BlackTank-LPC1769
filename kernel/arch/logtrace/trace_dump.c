/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2007,2008 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id$
 */

/*
 *		�ȥ졼�����Υ����
 */

#include "kernel_impl.h"
#include "task.h"
#include "cyclic.h"
#include "alarm.h"
#include <log_output.h>

/* 
 *  �����ͥ����μ�Ф�
 */
static intptr_t
get_tskid(intptr_t info)
{
	TCB		*p_tcb;
	ID		tskid;

	p_tcb = (TCB *) info;
	if (p_tcb == NULL) {
		tskid = 0;
	}
	else {
		tskid = TSKID(p_tcb);
	}
	return((intptr_t) tskid);
}

static intptr_t
get_tskstat(intptr_t info)
{
	uint_t		tstat;
	const char	*tstatstr;

	tstat = (uint_t) info;

	switch (tstat & (TS_RUNNABLE|TS_WAITING|TS_SUSPENDED)) {
	case TS_DORMANT:
		tstatstr = "DORMANT";
		break;
	case TS_RUNNABLE:
		tstatstr = "RUNNABLE";
		break;
	case TS_WAITING:
		tstatstr = "WAITING";
		break;
	case TS_SUSPENDED:
		tstatstr = "SUSPENDED";
		break;
	case TS_WAITING|TS_SUSPENDED:
		tstatstr = "WAITING-SUSPENDED";
		break;
	default:
		tstatstr = "unknown state";
		break;
	}

	return((intptr_t) tstatstr);
}


/*
 *  ��������������������°Ʊ����ǽ - ������
 */
static intptr_t
trace_print_tskenter(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
          
		/* ������������ǽ */
	  case TFN_ACT_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to act_tsk tskid=%d.";
		break;
	  case TFN_IACT_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to iact_tsk tskid=%d.";
		break;
	  case TFN_CAN_ACT:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to can_act tskid=%d.";
		break;
	  case TFN_EXT_TSK:
		tracemsg = "enter to ext_tsk.";
		break;
	  case TFN_TER_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to ter_tsk tskid=%d.";
		break;
	  case TFN_CHG_PRI:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "enter to chg_pri tskid=%d. tskpri=%d.";
		break;
	  case TFN_GET_PRI:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "enter to get_pri tskid=%d. p_tskpri=%d.";
		break;
	  case TFN_GET_INF:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to get_inf p_exinf=%d.";
		break;
          case TFN_REF_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to ref_tsk tskid=%d.";
		break;
        
		/* ��������°Ʊ����ǽ */
          case TFN_SLP_TSK:
		tracemsg = "enter to slp_tsk.";
		break;
	  case TFN_TSLP_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to tslp_tsk tmout=%d.";
		break;
	  case TFN_WUP_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to wup_tsk tskid=%d.";
		break;
	  case TFN_IWUP_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to iwup_tsk tskid=%d.";
		break;
	  case TFN_CAN_WUP:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to can_wup tskid=%d.";
		break;
	  case TFN_REL_WAI:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to rel_wai tskid=%d.";
		break;
	  case TFN_IREL_WAI:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to irel_wai tskid=%d.";
		break;
	  case TFN_SUS_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to sus_tsk tskid=%d.";
		break;
	  case TFN_RSM_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to rsm_tsk tskid=%d.";
		break;
	  case TFN_DLY_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to dly_tsk dlytim=%d.";
		break;
	  default:
		tracemsg = "unknown service call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  ��������������������°Ʊ����ǽ - �и���
 */
static intptr_t
trace_print_tskleave(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {

		/* ������������ǽ */
	  case TFN_ACT_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from act_tsk ercd=%d.";
		break;
	  case TFN_IACT_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from iact_tsk ercd=%d.";
		break;
	  case TFN_CAN_ACT:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from can_act ercd=%d.";
		break;
	  case TFN_EXT_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ext_tsk ercd=%d.";
		break;
	  case TFN_TER_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ter_tsk ercd=%d.";
		break;
	  case TFN_CHG_PRI:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from chg_pri ercd=%d.";
		break;
	  case TFN_GET_PRI:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "leave from get_pri ercd=%d. tskpri=%d.";
		break;
	  case TFN_GET_INF:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "leave from get_inf ercd=%d. exinf=%d.";
		break;
	  case TFN_REF_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ref_tsk ercd=%d.";
		break;
        
		/* ��������°Ʊ����ǽ */
	  case TFN_SLP_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from slp_tsk ercd=%d.";
		break;
	  case TFN_TSLP_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from tslp_tsk ercd=%d.";
		break;
	  case TFN_WUP_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from wup_tsk ercd=%d.";
		break;
	  case TFN_IWUP_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from iwup_tsk ercd=%d.";
		break;
	  case TFN_CAN_WUP:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from can_wup ercd=%d.";
		break;
	  case TFN_REL_WAI:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from rel_wai ercd=%d.";
		break;
	  case TFN_IREL_WAI:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from irel_wai ercd=%d.";
		break;
	  case TFN_SUS_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from sus_tsk ercd=%d.";
		break;
	case TFN_RSM_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from rsm_tsk ercd=%d.";
		break;
	case TFN_DLY_TSK:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from dly_tsk ercd=%d.";
		break;
	default:
		tracemsg = "unknown tsk service call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  �������㳰������ǽ - ������
 */
static intptr_t
trace_print_texenter(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_RAS_TEX:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to ras_tex tskid=%d. rasptn=%d.";
		break;
	  case TFN_IRAS_TEX:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to iras_tex tskid=%d. rasptn=%d.";
		break;
	  case TFN_DIS_TEX:
		tracemsg = "enter to dis_tex.";
		break;
	  case TFN_ENA_TEX:
		tracemsg = "enter to ena_tex.";
		break;
	  case TFN_SNS_TEX:
		tracemsg = "enter to sns_tex.";
		break;
	  case TFN_REF_TEX:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to ref_tex tskid=%d.";
		break;
	default:
		tracemsg = "unknown service call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  �������㳰������ǽ - �и���
 */
static intptr_t
trace_print_texleave(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_RAS_TEX:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ras_tex ercd=%d.";
		break;
	  case TFN_IRAS_TEX:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from iras_tex ercd=%d.";
		break;
	  case TFN_DIS_TEX:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from dis_tex ercd=%d.";
		break;
	  case TFN_ENA_TEX:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ena_tex ercd=%d";
		break;
	  case TFN_SNS_TEX:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from sns_tex state=%d.";
		break;
	  case TFN_REF_TEX:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ref_tex ercd=%d.";
		break;
	  default:
		tracemsg = "unknown service call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  ���ޥե���ǽ - ������
 */
static intptr_t
trace_print_sementer(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	case TFN_SIG_SEM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to sig_sem semid=%d.";
		break;
        case TFN_ISIG_SEM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to isig_sem semid=%d.";
		break;
	  case TFN_WAI_SEM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to wai_sem semid=%d.";
		break;
	  case TFN_POL_SEM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to pol_sem semid=%d.";
		break;
	  case TFN_TWAI_SEM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to twai_sem semid=%d.";
		break;
	  case TFN_INI_SEM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to ini_sem semid=%d.";
		break;
	  case TFN_REF_SEM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to ref_sem semid=%d.";
		break;
	default:
		tracemsg = "unknown service call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  ���ޥե���ǽ - �и���
 */
static intptr_t
trace_print_semleave(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_SIG_SEM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from sig_sem ercd=%d.";
		break;
	  case TFN_ISIG_SEM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from isig_sem ercd=%d.";
		break;
	  case TFN_WAI_SEM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from wai_sem ercd=%d.";
		break;
	  case TFN_POL_SEM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from pol_sem ercd=%d.";
		break;
	  case TFN_TWAI_SEM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from twai_sem ercd=%d.";
		break;
	  case TFN_INI_SEM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ini_sem ercd=%d.";
		break;
	  case TFN_REF_SEM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ref_sem ercd=%d.";
		break;
	default:
		tracemsg = "unknown servic call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  ���٥�ȥե饰��ǽ - ������
 */
static intptr_t
trace_print_flgenter(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_SET_FLG:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "enter to set_flg flgid=%d. setptn=%d.";
		break;
	  case TFN_ISET_FLG:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "enter to iset_flg flgid=%d. setptn=%d.";
		break;
	  case TFN_CLR_FLG:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "enter to clr_flg flgid=%d. clrptn=%d.";
		break;
	  case TFN_WAI_FLG:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		info[2] = (intptr_t)trace->loginfo[3];
		info[3] = (intptr_t)trace->loginfo[4];
		tracemsg = "enter to wai_flg flgid=%d. waiptn=%d. wfmode=%d. p_flgptn=%d.";
		break;
	  case TFN_POL_FLG:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		info[2] = (intptr_t)trace->loginfo[3];
		info[3] = (intptr_t)trace->loginfo[4];
		tracemsg = "enter to pol_flg flgid=%d. waiptn=%d. wfmode=%d. p_flgptn=%d.";
		break;
	  case TFN_TWAI_FLG:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		info[2] = (intptr_t)trace->loginfo[3];
		info[3] = (intptr_t)trace->loginfo[4];
		info[4] = (intptr_t)trace->loginfo[5];
		tracemsg = "enter to twai_flg flgid=%d. waiptn=%d. wfmode=%d. p_flgptn=%d. tmout=%d.";
		break;
	  case TFN_INI_FLG:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to ini_flg flgid=%d.";
		break;
	  case TFN_REF_FLG:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to ref_flg flgid=%d.";
		break;
	default:
		tracemsg = "unknown service call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  ���٥�ȥե饰��ǽ - �и���
 */
static intptr_t
trace_print_flgleave(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_SET_FLG:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from set_flg ercd=%d.";
		break;
	  case TFN_ISET_FLG:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from iset_flg ercd=%d.";
		break;
	  case TFN_CLR_FLG:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from clr_flg ercd=%d.";
		break;
	  case TFN_WAI_FLG:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "leave from wai_flg ercd=%d. flgptn=%d.";
		break;
	  case TFN_POL_FLG:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "leave from pol_flg ercd=%d. flgptn=%d.";
		break;
	  case TFN_TWAI_FLG:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "leave from twai_flg ercd=%d. flgptn=%d.";
		break;
	  case TFN_INI_FLG:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ini_flg ercd=%d.";
		break;
	  case TFN_REF_FLG:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ref_flg ercd=%d.";
		break;
	default:
		tracemsg = "unknown servic call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  �ǡ������塼��ǽ - ������
 */
static intptr_t
trace_print_dtqenter(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_SND_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "enter to snd_dtq dtqid=%d. data=%d.";
		break;
	  case TFN_PSND_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "enter to psnd_dtq dtqid=%d. data=%d.";
		break;
	  case TFN_IPSND_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "enter to ipsnd_dtq dtqid=%d. data=%d.";
		break;
	  case TFN_TSND_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		info[2] = (intptr_t)trace->loginfo[3];
		tracemsg = "enter to tsnd_dtq dtqid=%d. data=%d. tmout=%d.";
		break;
	  case TFN_FSND_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "enter to fsnd_dtq dtqid=%d. data=%d.";
		break;
	  case TFN_IFSND_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "enter to ifsnd_dtq dtqid=%d. data=%d.";
		break;
	  case TFN_RCV_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "enter to rcv_dtq dtqid=%d. p_data=%d.";
		break;
	  case TFN_PRCV_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "enter to prcv_dtq dtqid=%d. p_data=%d.";
		break;
	  case TFN_TRCV_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		info[2] = (intptr_t)trace->loginfo[3];
		tracemsg = "enter to trcv_dtq dtqid=%d. p_data=%d. tmout=%d.";
		break;
	  case TFN_INI_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to ini_dtq dtqid=%d.";
		break;
	  case TFN_REF_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to ref_dtq dtqid=%d.";
		break;
	default:
		tracemsg = "unknown service call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  �ǡ������塼��ǽ - �и���
 */
static intptr_t
trace_print_dtqleave(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_SND_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from snd_dtq ercd=%d.";
		break;
	  case TFN_PSND_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from psnd_dtq ercd=%d.";
		break;
	  case TFN_IPSND_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ipsnd_dtq ercd=%d.";
		break;
	  case TFN_TSND_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from tsnd_dtq ercd=%d.";
		break;
	  case TFN_FSND_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from fsnd_dtq ercd=%d.";
		break;
	  case TFN_IFSND_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ifsnd_dtq ercd=%d.";
		break;
	  case TFN_RCV_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "leave from rcv_dtq ercd=%d. data=%d.";
		break;
	  case TFN_PRCV_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "leave from prcv_dtq ercd=%d. data=%d.";
		break;
	  case TFN_TRCV_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "leave from trcv_dtq ercd=%d. data=%d.";
		break;
	  case TFN_INI_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ini_dtq ercd=%d.";
		break;
	  case TFN_REF_DTQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ref_dtq ercd=%d.";
		break;
	default:
		tracemsg = "unknown service call";
		break;
	}

	return((intptr_t) tracemsg);
}

/*
 *  ͥ���٥ǡ������塼��ǽ -������
 */
static intptr_t
trace_print_pdqenter(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_SND_PDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		info[2] = (intptr_t)trace->loginfo[3];
		tracemsg = "enter to snd_pdq pdqid=%d. data=%d. datapri=%d.";
		break;
	  case TFN_PSND_PDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		info[2] = (intptr_t)trace->loginfo[3];
		tracemsg = "enter to psnd_pdq pdqid=%d. data=%d. datapri=%d.";
		break;
	  case TFN_IPSND_PDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		info[2] = (intptr_t)trace->loginfo[3];
		tracemsg = "enter to ipsnd_pdq pdqid=%d. data=%d. datapri=%d.";
		break;
	  case TFN_TSND_PDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		info[2] = (intptr_t)trace->loginfo[3];
		info[3] = (intptr_t)trace->loginfo[4];
		tracemsg = "enter to tsnd_pdq pdqid=%d. data=%d. datapri=%d. tmout=%d.";
		break;
	  case TFN_RCV_PDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		info[2] = (intptr_t)trace->loginfo[3];
		tracemsg = "enter to rcv_pdq pdqid=%d. p_data=%d. p_datapri=%d.";
		break;
	  case TFN_PRCV_PDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		info[2] = (intptr_t)trace->loginfo[3];
		tracemsg = "enter to prcv_pdq pdqid=%d. p_data=%d. p_datapri=%d.";
		break;
	  case TFN_TRCV_PDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		info[2] = (intptr_t)trace->loginfo[3];
		info[3] = (intptr_t)trace->loginfo[4];
		tracemsg = "enter to trcv_pdq pdqid=%d. p_data=%d. p_datapri=%d. tmout=%d.";
		break;
	  case TFN_INI_PDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to ini_pdq pdqid=%d.";
		break;
	  case TFN_REF_PDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to ref_pdq pdqid=%d.";
		break;
	default:
		tracemsg = "unknown service call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  ͥ���٥ǡ������塼��ǽ - �и���
 */
static intptr_t
trace_print_pdqleave(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_SND_PDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from snd_pdq ercd=%d.";
		break;
	  case TFN_PSND_PDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from psnd_pdq ercd=%d.";
		break;
	  case TFN_IPSND_PDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ipsnd_pdq ercd=%d.";
		break;
	  case TFN_TSND_PDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from tsnd_pdq ercd=%d.";
		break;
	  case TFN_RCV_PDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		info[2] = (intptr_t)trace->loginfo[3];
		tracemsg = "leave from rcv_pdq ercd=%d. data=%d. datapri=%d.";
		break;
	  case TFN_PRCV_PDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		info[2] = (intptr_t)trace->loginfo[3];
		tracemsg = "leave from prcv_pdq ercd=%d. data=%d. datapri=%d.";
		break;
	  case TFN_TRCV_PDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		info[2] = (intptr_t)trace->loginfo[3];
		tracemsg = "leave from trcv_pdq ercd=%d. data=%d. datapri=%d.";
		break;
	  case TFN_INI_PDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ini_pdq ercd=%d.";
		break;
	  case TFN_REF_PDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ref_pdq ercd=%d.";
		break;
	default:
		tracemsg = "unknown service call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  �᡼��ܥå�����ǽ - ������
 */
static intptr_t
trace_print_mbxenter(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_SND_MBX:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "enter to snd_mbx mbxid=%d. pk_msg=%s.";
		break;
	  case TFN_RCV_MBX:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "enter to rcv_mbx mbxid=%d. ppk_msg=%s.";
		break;
	  case TFN_PRCV_MBX:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "enter to prcv_mbx mbxid=%d. ppk_msg=%s.";
		break;
	  case TFN_TRCV_MBX:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		info[2] = (intptr_t)trace->loginfo[3];
		tracemsg = "enter to trcv_mbx mbxid=%d. ppk_msg=%s. tmout=%d.";
		break;
	  case TFN_INI_MBX:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to ini_mbx mbxid=%d.";
		break;
	  case TFN_REF_MBX:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to ref_mbx mbxid=%d.";
		break;
	default:
		tracemsg = "unknown service call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  �᡼��ܥå�����ǽ - �и���
 */
static intptr_t
trace_print_mbxleave(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_SND_MBX:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from snd_mbx ercd=%d.";
		break;
	  case TFN_RCV_MBX:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "leave from rcv_mbx ercd=%d. pk_msg=%s.";
		break;
	  case TFN_PRCV_MBX:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "leave from prcv_mbx ercd=%d. pk_msg=%s.";
		break;
	  case TFN_TRCV_MBX:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "leave from trcv_mbx ercd=%d. pk_msg=%s.";
		break;
	  case TFN_INI_MBX:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ini_mbx ercd=%d.";
		break;
	  case TFN_REF_MBX:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ref_mbx ercd=%d.";
		break;
	default:
		tracemsg = "unknown service call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  ����Ĺ����ס��뵡ǽ - ������
 */
static intptr_t
trace_print_mpfenter(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_GET_MPF:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "enter to get_mpf mpfid=%d. p_blk=%d.";
		break;
	  case TFN_PGET_MPF:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "enter to pget_mpf mpfid=%d. p_blk=%d.";
		break;
	  case TFN_TGET_MPF:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		info[2] = (intptr_t)trace->loginfo[3];
		tracemsg = "enter to tget_mpf mpfid=%d. p_blk=%d. tmout=%d.";
		break;
	  case TFN_REL_MPF:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "enter to rel_mpf mpfid=%d. blk=%d.";
		break;
	  case TFN_INI_MPF:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to ini_mpf mpfid=%d.";
		break;
	  case TFN_REF_MPF:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to ref_mpf mpfid=%d.";
		break;
	default:
		tracemsg = "unknown service call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  ����Ĺ����ס��뵡ǽ - �и���
 */
static intptr_t
trace_print_mpfleave(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_GET_MPF:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "leave from get_mpf ercd=%d. blk=%d.";
		break;
	  case TFN_PGET_MPF:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "leave from pget_mpf ercd=%d. blk=%d.";
		break;
	  case TFN_TGET_MPF:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "leave from tget_mpf ercd=%d. blk=%d.";
		break;
	  case TFN_REL_MPF:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from rel_mpf ercd=%d";
		break;
	  case TFN_INI_MPF:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ini_mpf ercd=%d.";
		break;
	  case TFN_REF_MPF:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ref_mpf ercd=%d.";
		break;
	default:
		tracemsg = "unknown service call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  �����ƥ���������ǽ - ������
 */
static intptr_t
trace_print_timenter(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_GET_TIM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to get_tim p_systim=%d.";
		break;
	  case TFN_GET_UTM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to get_utm p_systum=%d.";
		break;
	default:
		tracemsg = "unknown service call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  �����ƥ���������ǽ - �и���
 */
static intptr_t
trace_print_timleave(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_GET_TIM:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "leave from get_tim ercd=%d. systim=%d.";
		break;
	  case TFN_GET_UTM:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "leave from get_utm ercd=%d. systum=%d.";
		break;
	default:
		tracemsg = "unknown servic call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  �����ϥ�ɥ鵡ǽ - ������
 */
static intptr_t
trace_print_cycenter(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_STA_CYC:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to sta_cyc cycid=%d.";
		break;
	  case TFN_STP_CYC:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to stp_cyc cycid=%d.";
		break;
	  case TFN_REF_CYC:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to ref_cyc cycid=%d.";
		break;
	default:
		tracemsg = "unknown service call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  �����ϥ�ɥ鵡ǽ - �и���
 */
static intptr_t
trace_print_cycleave(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_STA_CYC:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from sta_cyc ercd=%d.";
		break;
	  case TFN_STP_CYC:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from stp_cyc ercd=%d.";
		break;
	  case TFN_REF_CYC:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ref_cyc ercd=%d.";
		break;
	default:
		tracemsg = "unknown servic call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  ���顼��ϥ�ɥ鵡ǽ - ������
 */
static intptr_t
trace_print_almenter(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_STA_ALM:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "enter to sta_alm almid=%d. almtim=%d.";
		break;
	  case TFN_ISTA_ALM:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "enter to ista_alm almid=%d. almtim=%d.";
		break;
	  case TFN_STP_ALM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to stp_alm almid=%d.";
		break;
	  case TFN_ISTP_ALM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to istp_alm almid=%d.";
		break;
	  case TFN_REF_ALM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to ref_alm almid=%d.";
		break;
	default:
		tracemsg = "unknown service call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  ���顼��ϥ�ɥ鵡ǽ - �и���
 */
static intptr_t
trace_print_almleave(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_STA_ALM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from sta_alm ercd=%d.";
		break;
	  case TFN_ISTA_ALM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ista_alm ercd=%d.";
		break;
	  case TFN_STP_ALM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from stp_alm ercd=%d.";
		break;
	  case TFN_ISTP_ALM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from istp_alm ercd=%d.";
		break;
	  case TFN_REF_ALM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ref_alm ercd=%d.";
		break;
	default:
		tracemsg = "unknown servic call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  ����ߴ�����ǽ - ������
 */
static intptr_t
trace_print_intenter(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_DIS_INT:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to dis_int intno=%d.";
		break;
	  case TFN_ENA_INT:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to ena_int intno=%d.";
		break;
	  case TFN_CHG_IPM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to chg_ipm intpri=%d.";
		break;
	  case TFN_GET_IPM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to get_ipm p_intpri=%d.";
		break;
	default:
		tracemsg = "unknown service call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  ����ߴ�����ǽ - �и���
 */
static intptr_t
trace_print_intleave(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_DIS_INT:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from dis_int ercd=%d.";
		break;
	  case TFN_ENA_INT:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ena_int ercd=%d.";
		break;
	  case TFN_CHG_IPM:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from chg_ipm ercd=%d.";
		break;
	  case TFN_GET_IPM:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "leave from get_ipm ercd=%d. intpri=%d.";
		break;
	  default:
		tracemsg = "unknown servic call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  CPU�㳰������ǽ - ������
 */
static intptr_t
trace_print_dpnenter(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_XSNS_DPN:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to xsns_dpn p_excinf=%d.";
		break;
	  case TFN_XSNS_XPN:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to xsns_xpn p_excinf=%d.";
		break;
	default:
		tracemsg = "unknown service call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  CPU�㳰������ǽ - �и���
 */
static intptr_t
trace_print_dpnleave(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_XSNS_DPN:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from xsns_dpn state=%d.";
		break;
	  case TFN_XSNS_XPN:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from xsns_xpn state=%d.";
		break;
	  default:
		tracemsg = "unknown servic call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  �����ƥ���ִ�����ǽ - ������
 */
static intptr_t
trace_print_sysenter(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_ROT_RDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to rot_rdq tskpri=%d.";
		break;
	  case TFN_IROT_RDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to irot_rdq tskpri=%d.";
		break;
	  case TFN_GET_TID:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to get_tid p_tskid=%d.";
		break;
	  case TFN_IGET_TID:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "enter to iget_tid p_tskid=%d.";
		break;
	  case TFN_LOC_CPU:
		tracemsg = "enter to loc_cpu.";
		break;
	  case TFN_ILOC_CPU:
		tracemsg = "enter to iloc_cpu.";
		break;
	  case TFN_UNL_CPU:
		tracemsg = "enter to unl_cpu.";
		break;
	  case TFN_IUNL_CPU:
		tracemsg = "enter to iunl_cpu.";
		break;
	  case TFN_DIS_DSP:
		tracemsg = "enter to dis_dsp.";
		break;
	  case TFN_ENA_DSP:
		tracemsg = "enter to ena_dsp.";
		break;
	  case TFN_SNS_CTX:
		tracemsg = "enter to sns_ctx.";
		break;
	  case TFN_SNS_LOC:
		tracemsg = "enter to sns_loc.";
		break;
	  case TFN_SNS_DSP:
		tracemsg = "enter to sns_dsp.";
		break;
	  case TFN_SNS_DPN:
		tracemsg = "enter to sns_dpn.";
		break;
	  case TFN_SNS_KER:
		tracemsg = "enter to sns_ker.";
		break;
	default:
		tracemsg = "unknown servic call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 * �����ƥ���ִ�����ǽ - �и���
 */
static intptr_t
trace_print_sysleave(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_ROT_RDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from rot_rdq ercd=%d.";
		break;
	  case TFN_IROT_RDQ:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from irot_rdq ercd=%d.";
		break;
	  case TFN_GET_TID:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "leave from get_tid ercd=%d. tskid=%d";
		break;
	  case TFN_IGET_TID:
		info[0] = (intptr_t)trace->loginfo[1];
		info[1] = (intptr_t)trace->loginfo[2];
		tracemsg = "leave from iget_tid ercd=%d. tskid=%d";
		break;
	  case TFN_LOC_CPU:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from loc_cpu ercd=%d.";
		break;
	  case TFN_ILOC_CPU:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from iloc_cpu ercd=%d.";
		break;
	  case TFN_UNL_CPU:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from unl_cpu ercd=%d.";
		break;
	  case TFN_IUNL_CPU:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from iunl_cpu ercd=%d.";
		break;
	  case TFN_DIS_DSP:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from dis_dsp ercd=%d.";
		break;
	  case TFN_ENA_DSP:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from ena_dsp ercd=%d.";
		break;
	  case TFN_SNS_CTX:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from sns_ctx state=%d.";
		break;
	  case TFN_SNS_LOC:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from sns_loc state=%d.";
		break;
	  case TFN_SNS_DSP:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from sns_dsp state=%d.";
		break;
	  case TFN_SNS_DPN:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from sns_dpn state=%d.";
		break;
	  case TFN_SNS_KER:
		info[0] = (intptr_t)trace->loginfo[1];
		tracemsg = "leave from sns_ker state=%d.";
		break;
	default:
		tracemsg = "unknown servic call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  �����ͥ�ν�����Ƚ�λ����
 */
static intptr_t
trace_print_kerenter(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {
	  case TFN_EXT_KER:
		tracemsg = "enter to ext_ker.";
		break;
	default:
		tracemsg = "unknown service call";
		break;
	}

	return((intptr_t) tracemsg);
}


/*
 *  �����ƥॳ�����������(LOG_TYPE_SVC|ENTER)
 */
static intptr_t
trace_print_svcenter(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {

		/*��������������������°Ʊ����ǽ */
	  case TFN_ACT_TSK:
	  case TFN_IACT_TSK:
	  case TFN_CAN_ACT:
	  case TFN_EXT_TSK:
	  case TFN_TER_TSK:
	  case TFN_CHG_PRI:
	  case TFN_GET_PRI:
	  case TFN_GET_INF:
          case TFN_REF_TSK:
	  case TFN_SLP_TSK:
	  case TFN_TSLP_TSK:
	  case TFN_WUP_TSK:
	  case TFN_IWUP_TSK:
	  case TFN_CAN_WUP:
	  case TFN_REL_WAI:
	  case TFN_IREL_WAI:
	  case TFN_SUS_TSK:
	  case TFN_RSM_TSK:
	  case TFN_DLY_TSK:
		tracemsg = (const char*)trace_print_tskenter(trace, info);
		break;

		/* �������㳰������ǽ */
	  case TFN_RAS_TEX:
	  case TFN_IRAS_TEX:
	  case TFN_DIS_TEX:
	  case TFN_ENA_TEX:
	  case TFN_SNS_TEX:
	  case TFN_REF_TEX:
		tracemsg = (const char*)trace_print_texenter(trace, info);
		break;

		/* ���ޥե���ǽ */
	  case TFN_SIG_SEM:
	  case TFN_ISIG_SEM:
	  case TFN_WAI_SEM:
	  case TFN_POL_SEM:
	  case TFN_TWAI_SEM:
	  case TFN_INI_SEM:
	  case TFN_REF_SEM:
		tracemsg = (const char*)trace_print_sementer(trace, info);
		break;

		/* ���٥�ȥե饰��ǽ */
	  case TFN_SET_FLG:
	  case TFN_ISET_FLG:
	  case TFN_CLR_FLG:
	  case TFN_WAI_FLG:
	  case TFN_POL_FLG:
	  case TFN_TWAI_FLG:
	  case TFN_INI_FLG:
	  case TFN_REF_FLG:
		tracemsg = (const char*)trace_print_flgenter(trace, info);
		break;

		/* �ǡ������塼��ǽ */
	  case TFN_SND_DTQ:
	  case TFN_PSND_DTQ:
	  case TFN_IPSND_DTQ:
	  case TFN_TSND_DTQ:
	  case TFN_FSND_DTQ:
	  case TFN_IFSND_DTQ:
	  case TFN_RCV_DTQ:
	  case TFN_PRCV_DTQ:
	  case TFN_TRCV_DTQ:
	  case TFN_INI_DTQ:
	  case TFN_REF_DTQ:
		tracemsg = (const char*)trace_print_dtqenter(trace, info);
		break;

		/* ͥ���٥ǡ������塼��ǽ */
	  case TFN_SND_PDQ:
	  case TFN_PSND_PDQ:
	  case TFN_IPSND_PDQ:
	  case TFN_TSND_PDQ:
	  case TFN_RCV_PDQ:
	  case TFN_PRCV_PDQ:
	  case TFN_TRCV_PDQ:
	  case TFN_INI_PDQ:
	  case TFN_REF_PDQ:
		tracemsg = (const char*)trace_print_pdqenter(trace, info);
		break;

		/* ����Ĺ����ס��뵡ǽ */
	  case TFN_GET_MPF:
	  case TFN_PGET_MPF:
	  case TFN_TGET_MPF:
	  case TFN_REL_MPF:
	  case TFN_INI_MPF:
	  case TFN_REF_MPF:
		tracemsg = (const char*)trace_print_mpfenter(trace, info);
		break;

		/* �����ƥ���������ǽ  */
	  case TFN_GET_TIM:
	  case TFN_GET_UTM:
		tracemsg = (const char*)trace_print_timenter(trace, info);
		break;

		/* �����ϥ�ɥ鵡ǽ */
	  case TFN_STA_CYC:
	  case TFN_STP_CYC:
	  case TFN_REF_CYC:
		tracemsg = (const char*)trace_print_cycenter(trace, info);
		break;

		/* ���顼��ϥ�ɥ鵡ǽ */
	  case TFN_STA_ALM:
	  case TFN_ISTA_ALM:
	  case TFN_STP_ALM:
	  case TFN_ISTP_ALM:
	  case TFN_REF_ALM:
		tracemsg = (const char*)trace_print_almenter(trace, info);
		break;

		/* �᡼��ܥå�����ǽ */
	  case TFN_SND_MBX:
	  case TFN_RCV_MBX:
	  case TFN_PRCV_MBX:
	  case TFN_TRCV_MBX:
	  case TFN_INI_MBX:
	  case TFN_REF_MBX:
		tracemsg = (const char*)trace_print_mbxenter(trace, info);
		break;

		/* ����ߴ�����ǽ */
	  case TFN_DIS_INT:
	  case TFN_ENA_INT:
	  case TFN_CHG_IPM:
	  case TFN_GET_IPM:
		tracemsg = (const char*)trace_print_intenter(trace, info);
		break;
          
		/* CPU�㳰���� */
	  case TFN_XSNS_DPN:
	  case TFN_XSNS_XPN:
		tracemsg = (const char*)trace_print_dpnenter(trace, info);
		break;

		/* �����ƥ���ִ�����ǽ */
	  case TFN_ROT_RDQ:
	  case TFN_IROT_RDQ:
	  case TFN_GET_TID:
	  case TFN_IGET_TID:
	  case TFN_LOC_CPU:
	  case TFN_ILOC_CPU:
	  case TFN_UNL_CPU:
	  case TFN_IUNL_CPU:
	  case TFN_DIS_DSP:
	  case TFN_ENA_DSP:
	  case TFN_SNS_CTX:
	  case TFN_SNS_LOC:
	  case TFN_SNS_DSP:
	  case TFN_SNS_DPN:
	  case TFN_SNS_KER:
		tracemsg = (const char*)trace_print_sysenter(trace, info);
		break;

                /* �����ͥ�ν�����Ƚ�λ���� */
	  case TFN_EXT_KER:
	  	tracemsg = (const char*)trace_print_kerenter(trace, info);
		break;

          
	default:
		tracemsg = "unknown LOG_TYPE_SVC|ENTER service call";
		break;
	}
	return((intptr_t) tracemsg);
}


/*
 *  �����ƥॳ����νи���(LOG_TYPE_SVC|LEAVE)
 */
static intptr_t
trace_print_svcleave(TRACE *trace, intptr_t *info)
{
	uint_t		type;
	const char	*tracemsg;

	type = (uint_t)trace->loginfo[0];

	switch (type) {

		/* ��������������������°Ʊ����ǽ */
	  case TFN_ACT_TSK:
	  case TFN_IACT_TSK:
	  case TFN_CAN_ACT:
	  case TFN_EXT_TSK:
	  case TFN_TER_TSK:
	  case TFN_CHG_PRI:
	  case TFN_GET_PRI:
	  case TFN_GET_INF:
          case TFN_REF_TSK:
	  case TFN_SLP_TSK:
	  case TFN_TSLP_TSK:
	  case TFN_WUP_TSK:
	  case TFN_IWUP_TSK:
	  case TFN_CAN_WUP:
	  case TFN_REL_WAI:
	  case TFN_IREL_WAI:
	  case TFN_SUS_TSK:
	  case TFN_RSM_TSK:
	  case TFN_DLY_TSK:
		tracemsg = (const char*)trace_print_tskleave(trace, info);
		break;

		/* �������㳰������ǽ */
	  case TFN_RAS_TEX:
	  case TFN_IRAS_TEX:
	  case TFN_DIS_TEX:
	  case TFN_ENA_TEX:
	  case TFN_SNS_TEX:
	  case TFN_REF_TEX:
		tracemsg = (const char*)trace_print_texleave(trace, info);
		break;
          
		/* ���ޥե���ǽ */
	  case TFN_SIG_SEM:
	  case TFN_ISIG_SEM:
	  case TFN_WAI_SEM:
	  case TFN_POL_SEM:
	  case TFN_TWAI_SEM:
	  case TFN_INI_SEM:
	  case TFN_REF_SEM:
		tracemsg = (const char*)trace_print_semleave(trace, info);
		break;

		/* ���٥�ȥե饰��ǽ */
	  case TFN_SET_FLG:
	  case TFN_ISET_FLG:
	  case TFN_CLR_FLG:
	  case TFN_WAI_FLG:
	  case TFN_POL_FLG:
	  case TFN_TWAI_FLG:
	  case TFN_INI_FLG:
	  case TFN_REF_FLG:
		tracemsg = (const char*)trace_print_flgleave(trace, info);
		break;

		/* �ǡ������塼��ǽ */
	  case TFN_SND_DTQ:
	  case TFN_PSND_DTQ:
	  case TFN_IPSND_DTQ:
	  case TFN_TSND_DTQ:
	  case TFN_FSND_DTQ:
	  case TFN_IFSND_DTQ:
	  case TFN_RCV_DTQ:
	  case TFN_PRCV_DTQ:
	  case TFN_TRCV_DTQ:
	  case TFN_INI_DTQ:
	  case TFN_REF_DTQ:
		tracemsg = (const char*)trace_print_dtqleave(trace, info);
		break;

		/* ͥ���٥ǡ������塼��ǽ */
	  case TFN_SND_PDQ:
	  case TFN_PSND_PDQ:
	  case TFN_IPSND_PDQ:
	  case TFN_TSND_PDQ:
	  case TFN_RCV_PDQ:
	  case TFN_PRCV_PDQ:
	  case TFN_TRCV_PDQ:
	  case TFN_INI_PDQ:
	  case TFN_REF_PDQ:
		tracemsg = (const char*)trace_print_pdqleave(trace, info);
		break;

		/* ����Ĺ����ס��뵡ǽ */
	  case TFN_GET_MPF:
	  case TFN_PGET_MPF:
	  case TFN_TGET_MPF:
	  case TFN_REL_MPF:
	  case TFN_INI_MPF:
	  case TFN_REF_MPF:
		tracemsg = (const char*)trace_print_mpfleave(trace, info);
		break;

		/* �����ƥ���������ǽ  */
	  case TFN_GET_TIM:
	  case TFN_GET_UTM:
		tracemsg = (const char*)trace_print_timleave(trace, info);
		break;

		/* �����ϥ�ɥ鵡ǽ */
	  case TFN_STA_CYC:
	  case TFN_STP_CYC:
	  case TFN_REF_CYC:
		tracemsg = (const char*)trace_print_cycleave(trace, info);
		break;

		/* ���顼��ϥ�ɥ鵡ǽ */
	  case TFN_STA_ALM:
	  case TFN_ISTA_ALM:
	  case TFN_STP_ALM:
	  case TFN_ISTP_ALM:
	  case TFN_REF_ALM:
		tracemsg = (const char*)trace_print_almleave(trace, info);
		break;

		/* �᡼��ܥå�����ǽ */
	  case TFN_SND_MBX:
	  case TFN_RCV_MBX:
	  case TFN_PRCV_MBX:
	  case TFN_TRCV_MBX:
	  case TFN_INI_MBX:
	  case TFN_REF_MBX:
		tracemsg = (const char*)trace_print_mbxleave(trace, info);
		break;

		/* ����ߴ�����ǽ */
	  case TFN_DIS_INT:
	  case TFN_ENA_INT:
	  case TFN_CHG_IPM:
	  case TFN_GET_IPM:
		tracemsg = (const char*)trace_print_intleave(trace, info);
		break;

		/* CPU�㳰������ǽ */
	  case TFN_XSNS_DPN:
	  case TFN_XSNS_XPN:
		tracemsg = (const char*)trace_print_dpnleave(trace, info);
		break;

		/* �����ƥ���ִ�����ǽ */
	  case TFN_ROT_RDQ:
	  case TFN_IROT_RDQ:
	  case TFN_GET_TID:
	  case TFN_IGET_TID:
	  case TFN_LOC_CPU:
	  case TFN_ILOC_CPU:
	  case TFN_UNL_CPU:
	  case TFN_IUNL_CPU:
	  case TFN_DIS_DSP:
	  case TFN_ENA_DSP:
	  case TFN_SNS_CTX:
	  case TFN_SNS_LOC:
	  case TFN_SNS_DSP:
	  case TFN_SNS_DPN:
	  case TFN_SNS_KER:
		tracemsg = (const char*)trace_print_sysleave(trace, info);
		break;
         
	  default:
		tracemsg = "unknown LOG_TYPE_SVC|LEAVE servic call";
		break;
	}

	return((intptr_t) tracemsg);
}


/* 
 *  �ȥ졼������ɽ��
 */
static void
trace_print(TRACE *p_trace, void (*putc)(char_t))
{
	intptr_t	traceinfo[TMAX_LOGINFO + 1];
	const char	*tracemsg;
	int_t		i;

	traceinfo[0] = (intptr_t)(p_trace->logtim);
	syslog_printf("[%d] ", traceinfo, putc);

	switch (p_trace->logtype) {
	case LOG_TYPE_INH|LOG_ENTER:
		traceinfo[0] = p_trace->loginfo[0];
		tracemsg = "enter to int handler %d.";
		break;
	case LOG_TYPE_INH|LOG_LEAVE:
		traceinfo[0] = p_trace->loginfo[0];
		tracemsg = "leave from int handler %d.";
		break;
	case LOG_TYPE_ISR|LOG_ENTER:
		traceinfo[0] = p_trace->loginfo[0];
		tracemsg = "enter to isr %d.";
		break;
	case LOG_TYPE_ISR|LOG_LEAVE:
		traceinfo[0] = p_trace->loginfo[0];
		tracemsg = "leave from isr %d.";
		break;
	case LOG_TYPE_CYC|LOG_ENTER:
		traceinfo[0] = (intptr_t)((ID)((((CYCCB*)(p_trace->loginfo[0])) - cyccb_table) + TMIN_CYCID));
		tracemsg = "enter to cyclic handler %d.";
		break;
	case LOG_TYPE_CYC|LOG_LEAVE:
		traceinfo[0] = (intptr_t)((ID)((((CYCCB*)(p_trace->loginfo[0])) - cyccb_table) + TMIN_CYCID));
		tracemsg = "leave from cyclic handler %d.";
		break;
	case LOG_TYPE_ALM|LOG_ENTER:
		traceinfo[0] = (intptr_t)((ID)((((ALMCB*)(p_trace->loginfo[0])) - almcb_table) + TMIN_ALMID));
		tracemsg = "enter to alarm handler %d.";
		break;
	case LOG_TYPE_ALM|LOG_LEAVE:
		traceinfo[0] = (intptr_t)((ID)((((ALMCB*)(p_trace->loginfo[0])) - almcb_table) + TMIN_ALMID));
		tracemsg = "leave from alarm handler %d.";
		break;
	case LOG_TYPE_EXC|LOG_ENTER:
		traceinfo[0] = p_trace->loginfo[0];
		tracemsg = "enter to exc handler %d.";
		break;
	case LOG_TYPE_EXC|LOG_LEAVE:
		traceinfo[0] = p_trace->loginfo[0];
		tracemsg = "leave from exc handler %d.";
		break;
	case LOG_TYPE_TEX|LOG_ENTER:
		traceinfo[0] = p_trace->loginfo[1];
		tracemsg = "enter to tex %d.";
		break;
	case LOG_TYPE_TEX|LOG_LEAVE:
		traceinfo[0] = p_trace->loginfo[1];
		tracemsg = "leave from tex %d.";
		break;
	case LOG_TYPE_TSKSTAT:
		traceinfo[0] = get_tskid(p_trace->loginfo[0]);
		traceinfo[1] = get_tskstat(p_trace->loginfo[1]);
		tracemsg = "task %d becomes %s.";
		break;
	case LOG_TYPE_DSP|LOG_ENTER:
		traceinfo[0] = get_tskid(p_trace->loginfo[0]);
		tracemsg = "dispatch from task %d.";
		break;
	case LOG_TYPE_DSP|LOG_LEAVE:
		traceinfo[0] = get_tskid(p_trace->loginfo[0]);
		tracemsg = "dispatch to task %d.";
		break;
	case LOG_TYPE_SVC|LOG_ENTER:
		tracemsg = (const char *)trace_print_svcenter(p_trace, traceinfo);
		break;
	case LOG_TYPE_SVC|LOG_LEAVE:
		tracemsg = (const char *)trace_print_svcleave(p_trace, traceinfo);
		break;
	case LOG_TYPE_COMMENT:
		for (i = 1; i < TMAX_LOGINFO; i++) {
			traceinfo[i-1] = p_trace->loginfo[i];
		}
		tracemsg = (const char *)(p_trace->loginfo[0]);
		break;
	case LOG_TYPE_ASSERT:
		traceinfo[0] = p_trace->loginfo[0];
		traceinfo[1] = p_trace->loginfo[1];
		traceinfo[2] = p_trace->loginfo[2];
		tracemsg = "%s:%u: Assertion `%s' failed.";
		break;
	default:
		traceinfo[0] = p_trace->logtype;
		tracemsg = "unknown trace log type: %d.";
		break;
	}
	syslog_printf(tracemsg, traceinfo, putc);
	(*putc)('\n');
}

/* 
 *  �ȥ졼�����Υ����
 */
void
trace_dump(intptr_t exinf)
{
	TRACE	trace;
	void	(*putc)(char_t);

        putc = (void (*)(char_t)) exinf;
	while (trace_rea_log(&trace) >= 0) {
		trace_print(&trace, putc);
        }
}
