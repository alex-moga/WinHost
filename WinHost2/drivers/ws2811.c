/*
 * ws2811.c
 *
 * Created: 29.10.2017 13:57:34
 *  Author: Alex
 */ 

#include "ws2811.h"

const uint8_t g_log_color_tbl[] PROGMEM;
RgbColor g_leds[LED_COUNT];

void set_color(uint8_t nled, RgbColor rgbc) {
	g_leds[nled].red = rgbc.green; //pgm_read_word(&g_log_color_tbl[rgbc.red]);
	g_leds[nled].green = rgbc.red; //pgm_read_word(&g_log_color_tbl[rgbc.green]);
	g_leds[nled].blue = rgbc.blue; //pgm_read_word(&g_log_color_tbl[rgbc.blue]);
}

void init_led_driver() {
	WS2811_DDR |= _BV(WS2811_PIN);
}

void refresh() {
	const uint8_t mask =_BV(WS2811_PIN);
	uint8_t low_val = WS2811_PORT & (~mask);
	uint8_t high_val = WS2811_PORT | mask;
	
	cli();
	WS2811_PORT = high_val;
	_delay_us(50);
	WS2811_PORT = low_val;
	sei();
	_delay_ms(10);
}

void send_buffer() {
	 const uint8_t mask =_BV(WS2811_PIN);
	 uint8_t low_val = WS2811_PORT & (~mask);
	 uint8_t high_val = WS2811_PORT | mask;
	 uint16_t size = LED_COUNT * sizeof(RgbColor);
	 
	 cli();
	 uint8_t bitcount = 7;
	 WS2811_PORT = low_val;
	 _delay_loop_1(107);

	 asm volatile(
		 "start:  LDI %[bits], 7                          \n" // start code, load bit count
		 "        LD __tmp_reg__, %a[dataptr]+            \n" // fetch first byte
		 "cont06: NOP                                     \n"
		 "cont07: NOP                                     \n"
		 "        OUT %[portout], %[downreg]              \n" // Force line down, even if it already was down
		 "cont09: LSL __tmp_reg__                         \n" // Load next bit into carry flag.
		 "s00:    OUT %[portout], %[upreg]                \n" // Start of bit, bit value is in carry flag
		 "        BRCS skip03                             \n" // only lower the line if the bit...
		 "        OUT %[portout], %[downreg]              \n" // ...in the carry flag was zero.
		 "skip03: SUBI %[bits], 1                         \n" // Decrease bit count...
		 "        BRNE cont06                             \n" // ...and loop if not zero
		 "        LSL __tmp_reg__                         \n" // Load the last bit into the carry flag
		 "        BRCC Lx008                              \n" // Jump if last bit is zero
		 "        LDI %[bits], 7                          \n" // Reset bit counter to 7
		 "        OUT %[portout], %[downreg]              \n" // Force line down, even if it already was down
		 "        NOP                                     \n"
		 "        OUT %[portout], %[upreg]                \n" // Start of last bit of byte, which is 1
		 "        SBIW %[bytes], 1                        \n" // Decrease byte count
		 "        LD __tmp_reg__, %a[dataptr]+            \n" // Load next byte
		 "        BRNE cont07                             \n" // Loop if byte count is not zero
		 "        RJMP brk18                              \n" // Byte count is zero, jump to the end
		 "Lx008:  OUT %[portout], %[downreg]              \n" // Last bit is zero
		 "        LDI %[bits], 7                          \n" // Reset bit counter to 7
		 "        OUT %[portout], %[upreg]                \n" // Start of last bit of byte, which is 0
		 "        NOP                                     \n"
		 "        OUT %[portout], %[downreg]              \n" // We know we're transmitting a 0
		 "        SBIW %[bytes], 1                        \n" // Decrease byte count
		 "        LD __tmp_reg__, %a[dataptr]+            \n"
		 "        BRNE cont09                             \n" // Loop if byte count is not zero
		 "brk18:  OUT %[portout], %[downreg]              \n"
		 "                                                \n" // used to be a NOP here, but returning from the function takes long enough
		 "                                                \n" // We're done.
		 : /* no output */
		 : /* inputs */
		 [dataptr] "e" (g_leds), 	// pointer to grb values
		 [upreg]   "r" (high_val),	// register that contains the "up" value for the output port (constant)
		 [downreg] "r" (low_val),	// register that contains the "down" value for the output port (constant)
		 [bytes]   "w" (size),		// number of bytes to send
		 [bits]    "d" (bitcount),       // number of bits/2
		 [portout] "I" (_SFR_IO_ADDR(WS2811_PORT)) // The port to use
	 );
	 
	 sei();
}

const uint8_t g_log_color_tbl[] PROGMEM = {
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	3,
	4,
	4,
	4,
	4,
	4,
	4,
	4,
	4,
	4,
	4,
	4,
	4,
	5,
	5,
	5,
	5,
	5,
	5,
	5,
	5,
	5,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	7,
	7,
	7,
	7,
	7,
	7,
	7,
	8,
	8,
	8,
	8,
	8,
	9,
	9,
	9,
	9,
	9,
	10,
	10,
	10,
	10,
	10,
	11,
	11,
	11,
	11,
	12,
	12,
	12,
	12,
	13,
	13,
	13,
	13,
	14,
	14,
	14,
	15,
	15,
	15,
	16,
	16,
	16,
	17,
	17,
	17,
	18,
	18,
	19,
	19,
	19,
	20,
	20,
	21,
	21,
	22,
	22,
	23,
	23,
	24,
	24,
	25,
	25,
	26,
	26,
	27,
	27,
	28,
	29,
	29,
	30,
	31,
	31,
	32,
	33,
	33,
	34,
	35,
	36,
	36,
	37,
	38,
	39,
	40,
	41,
	41,
	42,
	43,
	44,
	45,
	46,
	47,
	48,
	49,
	50,
	52,
	53,
	54,
	55,
	56,
	57,
	59,
	60,
	61,
	63,
	64,
	65,
	67,
	68,
	70,
	71,
	73,
	74,
	76,
	78,
	79,
	81,
	83,
	85,
	87,
	89,
	91,
	92,
	95,
	97,
	99,
	101,
	103,
	105,
	108,
	110,
	112,
	115,
	117,
	120,
	123,
	125,
	128,
	131,
	134,
	137,
	140,
	143,
	146,
	149,
	152,
	156,
	159,
	162,
	166,
	170,
	173,
	177,
	181,
	185,
	189,
	193,
	197,
	202,
	206,
	211,
	215,
	220,
	225,
	230,
	235,
	240,
	245,
	251
};