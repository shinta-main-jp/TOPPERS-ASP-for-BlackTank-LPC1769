/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2010 by TOPPERS/ASP for LPC project
 *              http://sourceforge.jp/projects/toppersasp4lpc/
 *
 * 
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 */
/**
 * \addtogroup TOPPERS_CHIP
 * \{
 */

/**
 * \file chip_timer.h
 * \brief タイマドライバ（NXP LPC17XX汎用）
 */

#ifndef TOPPERS_CHIP_TIMER_H
#define TOPPERS_CHIP_TIMER_H

#include "target_syssvc.h"

/**
 * \brief CPUコアクロックとタイマー割り込み周期の比
 */
#define TIMER_CLOCK		(SYS_CLOCK / 1000)

/**
 * \brief 割込み優先度
 * \details
 *  タイマ割込みハンドラ登録のための定数。コンフィギュレータが静的コンフィギュレーション時に、タイマー登録用
 *  引数として使う。
 */
#define INTPRI_TIMER    (-6)

/**
 * \brief 割込み属性
 * \details
 *  タイマ割込みハンドラ登録のための定数。コンフィギュレータが静的コンフィギュレーション時に、タイマー登録用
 *  引数として使う。この値は0でいい。
 */
#define INTATR_TIMER    0U

/*
 *  プロセッサ依存部で定義する
 */
#include "arm_m_gcc/prc_timer.h"

#endif /* TOPPERS_CHIP_TIMER_H */

/**
 * \}
 */
