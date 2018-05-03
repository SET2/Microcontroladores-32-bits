  #define DMAMUX_CHCFG_SOURCE_DISABLED       0                           // 0x00                        
  #define DMAMUX_CHCFG_SOURCE_UART0_RX       2                           // 0x02 UART0 RX - DMAMUX_CHCFG_xx are available on DMA MUX 0 and on DMA MUX 1 (when available)
  #define DMAMUX_CHCFG_SOURCE_UART0_TX       3                           // 0x03 UART0 TX
  #define DMAMUX_CHCFG_SOURCE_UART1_RX       4                           // 0x04 UART1 RX
  #define DMAMUX_CHCFG_SOURCE_UART1_TX       5                           // 0x05 UART1 TX
  #define DMAMUX_CHCFG_SOURCE_UART2_RX       6                           // 0x06 UART2 RX
  #define DMAMUX_CHCFG_SOURCE_UART2_TX       7                           // 0x07 UART2 TX
  #define DMAMUX_CHCFG_SOURCE_UART3_RX       8                           // 0x08 UART3 RX
  #define DMAMUX_CHCFG_SOURCE_UART3_TX       9                           // 0x09 UART3 TX
  #define DMAMUX_CHCFG_SOURCE_UART4_RX       10                          // 0x0a UART4 RX
  #define DMAMUX_CHCFG_SOURCE_UART4_TX       11                          // 0x0b UART4 TX
  #define DMAMUX_CHCFG_SOURCE_UART5_RX       12                          // 0x0c UART5 RX
  #define DMAMUX_CHCFG_SOURCE_UART5_TX       13                          // 0x0d UART5 TX
  #define DMAMUX_CHCFG_SOURCE_I2S0_RX        14                          // 0x0e I2S0 RX
  #define DMAMUX_CHCFG_SOURCE_I2S0_TX        15                          // 0x0f I2S0 TX
  #define DMAMUX_CHCFG_SOURCE_SPI0_RX        16                          // 0x10 SPI0 RX
  #define DMAMUX_CHCFG_SOURCE_SPI0_TX        17                          // 0x11 SPI0 TX
  #define DMAMUX_CHCFG_SOURCE_SPI1_RX        18                          // 0x12 SPI1 RX
  #define DMAMUX_CHCFG_SOURCE_SPI1_TX        19                          // 0x13 SPI1 TX
  #define DMAMUX_CHCFG_SOURCE_SPI2_RX        20                          // 0x14 SPI2 RX
  #define DMAMUX_CHCFG_SOURCE_SPI2_TX        21                          // 0x15 SPI2 TX
  #define DMAMUX0_CHCFG_SOURCE_I2C0          22                          // 0x16 I2C0 - DMAMUX0_CHCFG_xx are only available on DMA MUX 0
  #define DMAMUX0_CHCFG_SOURCE_I2C1_2        23                          // 0x17 I2C1 (or I2C2)
  #define DMAMUX_CHCFG_SOURCE_FTM0_C0        24                          // 0x18 FTM0/TPM0 channel 0
  #define DMAMUX_CHCFG_SOURCE_FTM0_C1        25                          // 0x19 FTM0/TPM0 channel 1
  #define DMAMUX_CHCFG_SOURCE_FTM0_C2        26                          // 0x1a FTM0/TPM0 channel 2
  #define DMAMUX_CHCFG_SOURCE_FTM0_C3        27                          // 0x1b FTM0/TPM0 channel 3
  #define DMAMUX_CHCFG_SOURCE_FTM0_C4        28                          // 0x1c FTM0/TPM0 channel 4
  #define DMAMUX_CHCFG_SOURCE_FTM0_C5        29                          // 0x1d FTM0/TPM0 channel 5
  #define DMAMUX_CHCFG_SOURCE_FTM0_C6        30                          // 0x1e FTM0/TPM0 channel 6
  #define DMAMUX_CHCFG_SOURCE_FTM0_C7        31                          // 0x1f FTM0/TPM0 channel 7
  #define DMAMUX0_CHCFG_SOURCE_FTM1_C0       32                          // 0x20 FTM1/TPM1 channel 0
  #define DMAMUX0_CHCFG_SOURCE_FTM1_C1       33                          // 0x21 FTM1/TPM1 channel 1
  #define DMAMUX0_CHCFG_SOURCE_FTM2_C0       34                          // 0x22 FTM2/TPM2 channel 0
  #define DMAMUX0_CHCFG_SOURCE_FTM2_C1       35                          // 0x23 FTM2/TPM2 channel 1
  #define DMAMUX_CHCFG_SOURCE_IEEE1588_T0    36                          // 0x24 IEEE 1588 timer 0 (alternative)
  #define DMAMUX0_CHCFG_SOURCE_FTM3_C1       36                          // 0x24 FTM3 channel 1
  #define DMAMUX_CHCFG_SOURCE_IEEE1588_T1    37                          // 0x25 IEEE 1588 timer 1 (alternative)
  #define DMAMUX0_CHCFG_SOURCE_FTM3_C2       37                          // 0x25 FTM3 channel 2
  #define DMAMUX_CHCFG_SOURCE_IEEE1588_T2    38                          // 0x26 IEEE 1588 timer 2 (alternative)
  #define DMAMUX0_CHCFG_SOURCE_FTM3_C3       38                          // 0x26 FTM3 channel 3
  #define DMAMUX_CHCFG_SOURCE_IEEE1588_T3    39                          // 0x27 IEEE 1588 timer 3 (alternative)
  #define DMAMUX_CHCFG_SOURCE_ADC0           40                          // 0x28 ADC0
  #define DMAMUX_CHCFG_SOURCE_ADC1           41                          // 0x29 ADC1
  #define DMAMUX0_CHCFG_SOURCE_CMP0          42                          // 0x2a CMP0
  #define DMAMUX0_CHCFG_SOURCE_CMP1          43                          // 0x2b CMP1
  #define DMAMUX0_CHCFG_SOURCE_CMP2          44                          // 0x2c CMP2
  #define DMAMUX_CHCFG_SOURCE_DAC0           45                          // 0x2d DAC0
  #define DMAMUX_CHCFG_SOURCE_DAC1           46                          // 0x2e DAC1
  #define DMAMUX0_CHCFG_SOURCE_CMT           47                          // 0x2f CMT
  #define DMAMUX0_CHCFG_SOURCE_PDB           48                          // 0x30 PDB
  #define DMAMUX0_CHCFG_SOURCE_PORTA         49                          // 0x31 port A
  #define DMAMUX0_CHCFG_SOURCE_PORTB         50                          // 0x32 port B
  #define DMAMUX0_CHCFG_SOURCE_PORTC         51                          // 0x33 port C
  #define DMAMUX0_CHCFG_SOURCE_PORTD         52                          // 0x34 port D
  #define DMAMUX0_CHCFG_SOURCE_PORTE         53                          // 0x35 port E
