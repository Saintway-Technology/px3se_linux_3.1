#ifndef _DT_BINDINGS_CLOCK_ROCKCHIP_RK322X_H
#define _DT_BINDINGS_CLOCK_ROCKCHIP_RK322X_H

#include "rockchip.h"

/* pll id */
#define RK322X_APLL_ID			0
#define RK322X_DPLL_ID			1
#define RK322X_CPLL_ID			2
#define RK322X_GPLL_ID			3
#define RK322X_END_PLL_ID		4

/* reset id */
#define RK322X_RST_CORE0_PO		0
#define RK322X_RST_CORE1_PO		1
#define RK322X_RST_CORE2_PO		2
#define RK322X_RST_CORE3_PO		3
#define RK322X_RST_CORE0		4
#define RK322X_RST_CORE1		5
#define RK322X_RST_CORE2		6
#define RK322X_RST_CORE3		7
#define RK322X_RST_CORE0_DBG		8
#define RK322X_RST_CORE1_DBG		9
#define RK322X_RST_CORE2_DBG		10
#define RK322X_RST_CORE3_DBG		11
#define RK322X_RST_TOPDBG		12
#define RK322X_RST_ACLK_CORE		13
#define RK322X_RST_NOC_A		14
#define RK322X_RST_L2C			15

#define RK322X_RST_1RES0		16
#define RK322X_RST_1RES1		17
#define RK322X_RST_CPUSYS_H		18
#define RK322X_RST_BUSSYS_H		19
#define RK322X_RST_SPDIF		20
#define RK322X_RST_INTMEM		21
#define RK322X_RST_ROM			22
#define RK322X_RST_OTG_ADP		23
#define RK322X_RST_I2S0			24
#define RK322X_RST_I2S1			25
#define RK322X_RST_I2S2			26
#define RK322X_RST_ACODEC_P		27
#define RK322X_RST_DFIMON		28
#define RK322X_RST_MSCH			29
#define RK322X_RST_EFUSE_1024		30
#define RK322X_RST_EFUSE_256		31

#define RK322X_RST_GPIO0		32
#define RK322X_RST_GPIO1		33
#define RK322X_RST_GPIO2		34
#define RK322X_RST_GPIO3		35
#define RK322X_RST_PERIPH_NOC_A		36
#define RK322X_RST_PERIPH_NOC_H		37
#define RK322X_RST_PERIPH_NOC_P		38
#define RK322X_RST_UART0		39
#define RK322X_RST_UART1		40
#define RK322X_RST_UART2		41
#define RK322X_RST_PHYNOC		42
#define RK322X_RST_I2C0			43
#define RK322X_RST_I2C1			44
#define RK322X_RST_I2C2			45
#define RK322X_RST_I2C3			46
#define RK322X_RST_2RES15		47

#define RK322X_RST_PWM0			48
#define RK322X_RST_A53_GIC		49
#define RK322X_RST_3RES2		50
#define RK322X_RST_DAP			51
#define RK322X_RST_DAP_NOC		52
#define RK322X_RST_CRYPTO		53
#define RK322X_RST_SGRF			54
#define RK322X_RST_GRF			55
#define RK322X_RST_GMAC			56
#define RK322X_RST_3RES9		57
#define RK322X_RST_PERIPHSYS_A		58
#define RK322X_RST_3RES11		59
#define RK322X_RST_3RES12		60
#define RK322X_RST_3RES13		61
#define RK322X_RST_3RES14		62
#define RK322X_RST_MACPHY		63

#define RK322X_RST_4RES0		64
#define RK322X_RST_4RES1		65
#define RK322X_RST_4RES2		66
#define RK322X_RST_4RES3		67
#define RK322X_RST_NANDC		68
#define RK322X_RST_USBOTG0		69
#define RK322X_RST_OTGC0		70
#define RK322X_RST_USBHOST0		71
#define RK322X_RST_HOST_CTRL0		72
#define RK322X_RST_USBHOST1		73
#define RK322X_RST_HOST_CTRL1		74
#define RK322X_RST_USBHOST2		75
#define RK322X_RST_HOST_CTRL2		76
#define RK322X_RST_USBPOR0		77
#define RK322X_RST_USBPOR1		78
#define RK322X_RST_DDRMSCH		79

#define RK322X_RST_SMART_CARD		80
#define RK322X_RST_SDMMC0		81
#define RK322X_RST_SDIO			82
#define RK322X_RST_EMMC			83
#define RK322X_RST_SPI0			84
#define RK322X_RST_TSP_H		85
#define RK322X_RST_TSP			86
#define RK322X_RST_TSADC		87
#define RK322X_RST_DDRPHY		88
#define RK322X_RST_DDRPHY_P		89
#define RK322X_RST_DDRCTRL		90
#define RK322X_RST_DDRCTRL_P		91
#define RK322X_RST_HOST0_ECHI		92
#define RK322X_RST_HOST1_ECHI		93
#define RK322X_RST_HOST2_ECHI		94
#define RK322X_RST_VOP			95

#define RK322X_RST_HDMI_P		96
#define RK322X_RST_VIO_ARBI_H		97
#define RK322X_RST_IEP_NOC_A		98
#define RK322X_RST_VIO_NOC_H		99
#define RK322X_RST_VOP_A		100
#define RK322X_RST_VOP_H		101
#define RK322X_RST_VOP_D		102
#define RK322X_RST_UTMI0		103
#define RK322X_RST_UTMI1		104
#define RK322X_RST_UTMI2		105
#define RK322X_RST_UTMI3		106
#define RK322X_RST_RGA			107
#define RK322X_RST_RGA_NOC_A		108
#define RK322X_RST_RGA_A		109
#define RK322X_RST_RGA_H		110
#define RK322X_RST_HDCP_A		111

#define RK322X_RST_VPU_A		112
#define RK322X_RST_VPU_H		113
#define RK322X_RST_7RES2		114
#define RK322X_RST_7RES3		115
#define RK322X_RST_VPU_NOC_A		116
#define RK322X_RST_VPU_NOC_H		117
#define RK322X_RST_RKVDEC_A		118
#define RK322X_RST_RKVDEC_NOC_A		119
#define RK322X_RST_RKVDEC_H		120
#define RK322X_RST_RKVDEC_NOC_H		121
#define RK322X_RST_RKVDEC_CORE		122
#define RK322X_RST_RKVDEC_CABAC		123
#define RK322X_RST_IEP_A		124
#define RK322X_RST_IEP_H		125
#define RK322X_RST_GPU_A		126
#define RK322X_RST_GPU_NOC_A		127

#define RK322X_RST_CORE_DBG		128
#define RK322X_RST_DBG_P		129
#define RK322X_RST_TIMER0		130
#define RK322X_RST_TIMER1		131
#define RK322X_RST_TIMER2		132
#define RK322X_RST_TIMER3		133
#define RK322X_RST_TIMER4		134
#define RK322X_RST_TIMER5		135
#define RK322X_RST_VIO_H2P		136
#define RK322X_RST_8RES9		137
#define RK322X_RST_8RES10		138
#define RK322X_RST_HDMIPHY		139
#define RK322X_RST_VDAC			140
#define RK322X_RST_TIMER_6CH		141
#define RK322X_RST_8RES14		142
#define RK322X_RST_8RES15		143

#endif /* _DT_BINDINGS_CLOCK_ROCKCHIP_RK322X_H */
