/*
 * Dma_cfg.h
 *
 *  Created on: Apr 22, 2022
 *      Author: modata7
 */

#ifndef DMA_CFG_H_
#define DMA_CFG_H_

/*DMA Controller*/
#define DMA1	((void*)0x40026000)
#define DMA2	((void*)0x40026400)

/*Stream Number*/
/*
DMA_u8STREAM_0
DMA_u8STREAM_1
DMA_u8STREAM_2
DMA_u8STREAM_3
DMA_u8STREAM_4
DMA_u8STREAM_5
DMA_u8STREAM_6
DMA_u8STREAM_7
*/

/*Channel Selection*/
#define DMA_u32Channel_0	0x00000000
#define DMA_u32Channel_1	0x02000000
#define DMA_u32Channel_2	0x04000000
#define DMA_u32Channel_3	0x06000000
#define DMA_u32Channel_4	0x08000000
#define DMA_u32Channel_5	0x0A000000
#define DMA_u32Channel_6	0x0C000000
#define DMA_u32Channel_7	0x0E000000

/*Channel Direction*/
#define	DMA_u8PERIPHERAL_TO_MEMORY	0x00
#define	DMA_u8MEMORY_TO_PERIPHERAL	0x40
#define	DMA_u8MEMORY_TO_MEMORY		0x80

/*Memory Data Size*/
#define	DMA_u16MEMORY_BYTE			0x0000
#define	DMA_u16MEMORY_HALF_WORD		0x0800
#define	DMA_u16MEMORY_WORD			0x1000

/*Peripheral Data Size*/
#define	DMA_u16PERIPHERAL_BYTE			0x0000
#define	DMA_u16PERIPHERAL_HALF_WORD     0x2000
#define	DMA_u16PERIPHERAL_WORD          0x4000

/*Memory Increment Mode*/
#define	DMA_u16MEMORY_FIXED_POINTER		0x0000
#define	DMA_u16MEMORY_INC_POINTER		0x0400

/*Peripheral Increment Mode*/
#define	DMA_u16PERIPHERAL_FIXED_POINTER		0x0000
#define	DMA_u16PERIPHERAL_INC_POINTER		0x0200

/*DMA Mode*/
#define DMA_u32NORMAL_MODE				0x00000000
#define DMA_u32DOUBLE_BUFFER_MODE		0x00080000
#define DMA_u32CIRCULAR_MODE			0x00000100

/*DMA Priority*/
#define DMA_u32LOW						0x00000000
#define DMA_u32MEDIUM					0x00010000
#define DMA_u32HIGH						0x00020000
#define DMA_u32VERY_HIGH				0x00030000


#endif /* DMA_CFG_H_ */
