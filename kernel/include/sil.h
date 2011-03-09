/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2008 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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
 *  @(#) $Id: sil.h 1844 2010-07-11 12:59:26Z ertl-hiro $
 */

/*
 *		システムインタフェースレイヤ
 *
 *  システムインタフェースレイヤのサービスコールの定義・宣言とマクロな
 *  どの定義を含むヘッダファイル．
 *
 *  アセンブリ言語のソースファイルからこのファイルをインクルードする時
 *  は，TOPPERS_MACRO_ONLYを定義しておくことで，マクロ定義以外の記述を
 *  除くことができる．
 *
 *  このファイルをインクルードする前にインクルードしておくべきファイル
 *  はない．
 */

#ifndef TOPPERS_SIL_H
#define TOPPERS_SIL_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 *	TOPPERS共通のデータ型・定数・マクロ
 */
#include <t_stddef.h>

/*
 *  ターゲット依存部
 */
#include "target_sil.h"

#ifndef TOPPERS_MACRO_ONLY

/*
 *  全割込みロック状態の制御
 *
 *  SIL_PRE_LOC，SIL_LOC_INT()，SIL_UNL_INT()は，ターゲット依存部で用
 *  意する．デフォルトの定義は用意していない．
 */

/*
 *  微少時間待ち
 */
extern void	sil_dly_nse(ulong_t dlytim) throw();

/*
 *  エンディアンの反転
 */
#ifndef TOPPERS_SIL_REV_ENDIAN_UINT16
#define	TOPPERS_SIL_REV_ENDIAN_UINT16(data) \
				((((data) & 0xff) << 8) | (((data) >> 8) & 0xff))
#endif /* TOPPERS_SIL_REV_ENDIAN_UINT16 */

#ifndef TOPPERS_SIL_REV_ENDIAN_UINT32
#define	TOPPERS_SIL_REV_ENDIAN_UINT32(data) \
				((((data) & 0xff) << 24) | (((data) & 0xff00) << 8) \
					| (((data) >> 8) & 0xff00) | (((data) >> 24) & 0xff))
#endif /* TOPPERS_SIL_REV_ENDIAN_UINT32 */

/*
 *  メモリ空間アクセス関数
 */
#ifndef TOPPERS_OMIT_SIL_ACCESS

/*
 *  8ビット単位の読出し／書込み
 */
#ifdef UINT8_MAX

Inline uint8_t
sil_reb_mem(void *mem)
{
	uint8_t	data;

	data = *((volatile uint8_t *) mem);
	return(data);
}

Inline void
sil_wrb_mem(void *mem, uint8_t data)
{
	*((volatile uint8_t *) mem) = data;
}

#endif /* UINT8_MAX */

/*
 *  16ビット単位の読出し／書込み
 */

Inline uint16_t
sil_reh_mem(void *mem)
{
	uint16_t	data;

	data = *((volatile uint16_t *) mem);
	return(data);
}

Inline void
sil_wrh_mem(void *mem, uint16_t data)
{
	*((volatile uint16_t *) mem) = data;
}

#ifdef SIL_ENDIAN_BIG			/* ビッグエンディアンプロセッサ */

#define	sil_reh_bem(mem)		sil_reh_mem(mem)
#define	sil_wrh_bem(mem, data)	sil_wrh_mem(mem, data)

#ifndef TOPPERS_OMIT_SIL_REH_LEM

Inline uint16_t
sil_reh_lem(void *mem)
{
	uint16_t	data;

	data = *((volatile uint16_t *) mem);
	return(TOPPERS_SIL_REV_ENDIAN_UINT16(data));
}

#endif /* TOPPERS_OMIT_SIL_REH_LEM */
#ifndef TOPPERS_OMIT_SIL_WRH_LEM

Inline void
sil_wrh_lem(void *mem, uint16_t data)
{
	*((volatile uint16_t *) mem) = TOPPERS_SIL_REV_ENDIAN_UINT16(data);
}

#endif /* TOPPERS_OMIT_SIL_WRH_LEM */
#else /* SIL_ENDIAN_BIG */
#ifdef SIL_ENDIAN_LITTLE		/* リトルエンディアンプロセッサ */

#define	sil_reh_lem(mem)		sil_reh_mem(mem)
#define	sil_wrh_lem(mem, data)	sil_wrh_mem(mem, data)

#ifndef TOPPERS_OMIT_SIL_REH_BEM

Inline uint16_t
sil_reh_bem(void *mem)
{
	uint16_t	data;

	data = *((volatile uint16_t *) mem);
	return(TOPPERS_SIL_REV_ENDIAN_UINT16(data));
}

#endif /* TOPPERS_OMIT_SIL_REH_BEM */
#ifndef TOPPERS_OMIT_SIL_WRH_BEM

Inline void
sil_wrh_bem(void *mem, uint16_t data)
{
	*((volatile uint16_t *) mem) = TOPPERS_SIL_REV_ENDIAN_UINT16(data);
}

#endif /* TOPPERS_OMIT_SIL_WRH_BEM */
#else /* SIL_ENDIAN_LITTLE */

#error Neither SIL_ENDIAN_BIG nor SIL_ENDIAN_LITTLE is defined.

#endif /* SIL_ENDIAN_LITTLE */
#endif /* SIL_ENDIAN_BIG */

/*
 *  32ビット単位の読出し／書込み
 */

Inline uint32_t
sil_rew_mem(void *mem)
{
	uint32_t	data;

	data = *((volatile uint32_t *) mem);
	return(data);
}

Inline void
sil_wrw_mem(void *mem, uint32_t data)
{
	*((volatile uint32_t *) mem) = data;
}

#ifdef SIL_ENDIAN_BIG			/* ビッグエンディアンプロセッサ */

#define	sil_rew_bem(mem)		sil_rew_mem(mem)
#define	sil_wrw_bem(mem, data)	sil_wrw_mem(mem, data)

#ifndef TOPPERS_OMIT_SIL_REW_LEM

Inline uint32_t
sil_rew_lem(void *mem)
{
	uint32_t	data;

	data = *((volatile uint32_t *) mem);
	return(TOPPERS_SIL_REV_ENDIAN_UINT32(data));
}

#endif /* TOPPERS_OMIT_SIL_REW_LEM */
#ifndef TOPPERS_OMIT_SIL_WRW_LEM

Inline void
sil_wrw_lem(void *mem, uint32_t data)
{
	*((volatile uint32_t *) mem) = TOPPERS_SIL_REV_ENDIAN_UINT32(data);
}

#endif /* TOPPERS_OMIT_SIL_WRW_LEM */
#else /* SIL_ENDIAN_BIG */		/* リトルエンディアンプロセッサ */

#define	sil_rew_lem(mem)		sil_rew_mem(mem)
#define	sil_wrw_lem(mem, data)	sil_wrw_mem(mem, data)

#ifndef TOPPERS_OMIT_SIL_REW_BEM

Inline uint32_t
sil_rew_bem(void *mem)
{
	uint32_t	data;

	data = *((volatile uint32_t *) mem);
	return(TOPPERS_SIL_REV_ENDIAN_UINT32(data));
}

#endif /* TOPPERS_OMIT_SIL_REW_BEM */
#ifndef TOPPERS_OMIT_SIL_WRW_BEM

Inline void
sil_wrw_bem(void *mem, uint32_t data)
{
	*((volatile uint32_t *) mem) = TOPPERS_SIL_REV_ENDIAN_UINT32(data);
}

#endif /* TOPPERS_OMIT_SIL_WRW_BEM */
#endif /* SIL_ENDIAN_BIG */
#endif /* TOPPERS_OMIT_SIL_ACCESS */

#endif /* TOPPERS_MACRO_ONLY */

#ifdef __cplusplus
}
#endif

#endif /* TOPPERS_SIL_H */
