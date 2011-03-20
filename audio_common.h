#ifndef AUDIO_COMMON_H
#define AUDIO_COMMON_H

/**
 * \brief $B%*!<%G%#%*%G!<%?7?(B
 * \details
 * $B%W%m%0%i%`FbIt$G;H$&%*!<%G%#%*$N4pK\7?!#:85M$a$NId9fIU$-8GDj>.?tE@7?$G$"$k!#>.?tE@$O(BMSB$B$N(B
 * $B$9$01&$K$"$k!#(B
 */
typedef int AUDIOSAMPLE;

/**
 * \brief I2S DMA$B%P%C%U%!$ND9$5(B
 * \details
 * $B0l2s$N(BDMA$BE>Aw$K;H$&%G!<%?%P%C%U%!$ND9$5!#(BAUDIOBUFSIZE$B$,(BN$B$J$i$P!"%9%F%l%*$J$N$G!"(B
 * N/2$B%5%s%W%k$N%G!<%?$r0l2s$N(BDMA$B$GE>Aw$9$k$3$H$K$J$k!#(B
 */
#define	AUDIOBUFSIZE	64	 /* I2S$B%P%C%U%!$ND9$5!#(B48kHz$B%5%s%W%k$N;~!"(B1mS$B$K$9$k$K$O(B96$B$rA*$V(B */

#endif

