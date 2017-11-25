/*
 * Color.c
 *
 * Created: 28.10.2017 21:14:06
 * Author: Alex
 */ 

#include "color.h"

void toRgb(HsvColor hsvc, RgbColor* p_rgbc) {
	if(!hsvc.sat) {
		//Белый цвет
		p_rgbc->red = p_rgbc->green = p_rgbc->blue = hsvc.val;
	} else {
		//Вычисляем цветовой сектант 
		uint8_t sextant = hsvc.hue >> 8;
		if(sextant > 5) {
			sextant = 5;
		}
		
		//Устанавливаем верхний уровень
		p_rgbc->green = hsvc.val;
		
		//Расчет нижнего уровня: (v * (255 - s) + error_corr + 1) / 256
		uint16_t ww;
		ww = hsvc.val * (uint8_t)(~hsvc.sat);
		ww += 1;
		ww += ww >> 8;
		p_rgbc->blue = ww >> 8;
		
		//Вычисляем позицию в сектанте
		uint8_t h_fraction = hsvc.hue & 0xff;
		uint32_t d;
		
		if(!(sextant & 1)) {
			// r = ...slope_up...
			// --> r = (v * ((255 << 8) - s * (256 - h)) + error_corr1 + error_corr2) / 65536
			d = hsvc.val * (uint32_t)(0xff00 - (uint16_t)(hsvc.sat * (256 - h_fraction)));
			d += d >> 8;
			d += hsvc.val;
			p_rgbc->red = d >> 16;
		} else {
			// r = ...slope_down...
			// --> r = (v * ((255 << 8) - s * h) + error_corr1 + error_corr2) / 6553
			d = hsvc.val * (uint32_t)(0xff00 - (uint16_t)(hsvc.sat * h_fraction));
			d += d >> 8;
			d += hsvc.val;
			p_rgbc->red = d >> 16;
		}
		
		// Установка значений RGB в зависимости от сектаната. 
		if(!(sextant & 6)) {
			if(!(sextant & 1)) {
				uint8_t tmp = p_rgbc->red;
				p_rgbc->red = p_rgbc->green;
				p_rgbc->green = tmp;
			}
			} else {
			if(sextant & 1) {
				uint8_t tmp = p_rgbc->red;
				p_rgbc->red = p_rgbc->green;
				p_rgbc->green = tmp;
			}
			if(sextant & 4) {
				uint8_t tmp = p_rgbc->green;
				p_rgbc->green = p_rgbc->blue;
				p_rgbc->blue = tmp;
			}
			if(sextant & 2) {
				uint8_t tmp = p_rgbc->red;
				p_rgbc->red = p_rgbc->blue;
				p_rgbc->blue = tmp;
			}
		}
	}
}

RgbColor colorFromPallete(uint8_t index, const RgbColor* p_pallete) {
	 RgbColor resc;
	 
	 uint8_t hi4 = index >> 4;
	 uint8_t lo4 = index & 0x0F;
	 const RgbColor *p_entry = &(p_pallete[hi4]);
	 
	 uint8_t red1   = p_entry->red;
	 uint8_t green1 = p_entry->green;
	 uint8_t blue1  = p_entry->blue;
	 
	 if(lo4) {
		 if( hi4 == 15 ) {
			p_entry = &(p_pallete[0]);
		 } else {
			p_entry++;
		 }
		 
		 uint8_t f2 = lo4 << 4;
		 uint8_t f1 = 255 - f2;
		 
		 uint8_t red2   = p_entry->red;
		 red1   = scale8( red1,   f1);
		 red2   = scale8( red2,   f2);
		 red1   += red2;

		 uint8_t green2 = p_entry->green;
		 green1 = scale8( green1, f1);
		 green2 = scale8( green2, f2);
		 green1 += green2;

		 uint8_t blue2  = p_entry->blue;
		 blue1  = scale8( blue1,  f1);
		 blue2  = scale8( blue2,  f2);
		 blue1  += blue2;
	 }
	 
	 resc.red = red1;
	 resc.green = green1;
	 resc.blue = blue1;
	 
	 return resc;
}