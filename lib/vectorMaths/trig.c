/**
 * @file trig.c
 * @author Vic Degraeve
 * @author Victor-Louis De Gusseme
 */

#include "trig.h"

const uint8_t sin_table[91] = {
	0,   /*    sin(0 degrees) * 100    */
	2,   /*    sin(1 degrees) * 100    */
	4,   /*    sin(2 degrees) * 100    */
	5,   /*    sin(3 degrees) * 100    */
	7,   /*    sin(4 degrees) * 100    */
	9,   /*    sin(5 degrees) * 100    */
	11,  /*    sin(6 degrees) * 100    */
	12,  /*    sin(7 degrees) * 100    */
	14,  /*    sin(8 degrees) * 100    */
	16,  /*    sin(9 degrees) * 100    */
	17,  /*    sin(10 degrees) * 100    */
	19,  /*    sin(11 degrees) * 100    */
	21,  /*    sin(12 degrees) * 100    */
	23,  /*    sin(13 degrees) * 100    */
	24,  /*    sin(14 degrees) * 100    */
	26,  /*    sin(15 degrees) * 100    */
	28,  /*    sin(16 degrees) * 100    */
	29,  /*    sin(17 degrees) * 100    */
	31,  /*    sin(18 degrees) * 100    */
	33,  /*    sin(19 degrees) * 100    */
	34,  /*    sin(20 degrees) * 100    */
	36,  /*    sin(21 degrees) * 100    */
	38,  /*    sin(22 degrees) * 100    */
	39,  /*    sin(23 degrees) * 100    */
	41,  /*    sin(24 degrees) * 100    */
	42,  /*    sin(25 degrees) * 100    */
	44,  /*    sin(26 degrees) * 100    */
	45,  /*    sin(27 degrees) * 100    */
	47,  /*    sin(28 degrees) * 100    */
	49,  /*    sin(29 degrees) * 100    */
	50,  /*    sin(30 degrees) * 100    */
	52,  /*    sin(31 degrees) * 100    */
	53,  /*    sin(32 degrees) * 100    */
	55,  /*    sin(33 degrees) * 100    */
	56,  /*    sin(34 degrees) * 100    */
	57,  /*    sin(35 degrees) * 100    */
	59,  /*    sin(36 degrees) * 100    */
	60,  /*    sin(37 degrees) * 100    */
	62,  /*    sin(38 degrees) * 100    */
	63,  /*    sin(39 degrees) * 100    */
	64,  /*    sin(40 degrees) * 100    */
	66,  /*    sin(41 degrees) * 100    */
	67,  /*    sin(42 degrees) * 100    */
	68,  /*    sin(43 degrees) * 100    */
	70,  /*    sin(44 degrees) * 100    */
	71,  /*    sin(45 degrees) * 100    */
	72,  /*    sin(46 degrees) * 100    */
	73,  /*    sin(47 degrees) * 100    */
	74,  /*    sin(48 degrees) * 100    */
	76,  /*    sin(49 degrees) * 100    */
	77,  /*    sin(50 degrees) * 100    */
	78,  /*    sin(51 degrees) * 100    */
	79,  /*    sin(52 degrees) * 100    */
	80,  /*    sin(53 degrees) * 100    */
	81,  /*    sin(54 degrees) * 100    */
	82,  /*    sin(55 degrees) * 100    */
	83,  /*    sin(56 degrees) * 100    */
	84,  /*    sin(57 degrees) * 100    */
	85,  /*    sin(58 degrees) * 100    */
	86,  /*    sin(59 degrees) * 100    */
	87,  /*    sin(60 degrees) * 100    */
	88,  /*    sin(61 degrees) * 100    */
	88,  /*    sin(62 degrees) * 100    */
	89,  /*    sin(63 degrees) * 100    */
	90,  /*    sin(64 degrees) * 100    */
	91,  /*    sin(65 degrees) * 100    */
	91,  /*    sin(66 degrees) * 100    */
	92,  /*    sin(67 degrees) * 100    */
	93,  /*    sin(68 degrees) * 100    */
	93,  /*    sin(69 degrees) * 100    */
	94,  /*    sin(70 degrees) * 100    */
	95,  /*    sin(71 degrees) * 100    */
	95,  /*    sin(72 degrees) * 100    */
	96,  /*    sin(73 degrees) * 100    */
	96,  /*    sin(74 degrees) * 100    */
	97,  /*    sin(75 degrees) * 100    */
	97,  /*    sin(76 degrees) * 100    */
	97,  /*    sin(77 degrees) * 100    */
	98,  /*    sin(78 degrees) * 100    */
	98,  /*    sin(79 degrees) * 100    */
	99,  /*    sin(80 degrees) * 100    */
	99,  /*    sin(81 degrees) * 100    */
	99,  /*    sin(82 degrees) * 100    */
	99,  /*    sin(83 degrees) * 100    */
	100,  /*    sin(84 degrees) * 100    */
	100,  /*    sin(85 degrees) * 100    */
	100,  /*    sin(86 degrees) * 100    */
	100,  /*    sin(87 degrees) * 100    */
	100,  /*    sin(88 degrees) * 100    */
	100, /*    sin(89 degrees) * 100    */
	100, /*    sin(90 degrees) * 100    */
};

int8_t sin100(int16_t degrees) {
	int sign = 1;
	if(degrees < 0) {
		degrees = -degrees;
		sign = -1;
	}
	if(degrees > 90 && degrees <= 180) {
		degrees = 180 - degrees;
	}
	else if(degrees > 180) {
		degrees -= 180;
		sign = -1;
	}
	return sign * sin_table[degrees];
}

int8_t cos100(int16_t degrees) {
	return sin100(90 - degrees);
}
