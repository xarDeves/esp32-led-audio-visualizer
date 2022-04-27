#pragma once

#include "debug.h"

#include "Colors.h"

namespace ColorConvertions {

	static float HueToRGB(float v1, float v2, float vH) {

		if (vH < 0)
			vH += 1;

		if (vH > 1)
			vH -= 1;

		if ((6 * vH) < 1)
			return (v1 + (v2 - v1) * 6 * vH);

		if ((2 * vH) < 1)
			return v2;

		if ((3 * vH) < 2)
			return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);

		return v1;
	}

	static void HSVtoRGB(Colors::ABSTRACT &hsx, Colors::RGB &rgb) {

		double r = 0, g = 0, b = 0;

		if (hsx.b == 0) {
			r = hsx.c;
			g = hsx.c;
			b = hsx.c;
		}
		else {
			int i;
			double f, p, q, t;

			if (hsx.a == 360)
				hsx.a = 0;
			else
				hsx.a = hsx.a / 60;

			i = (int)trunc(hsx.a);
			f = hsx.a - i;

			p = hsx.c * (1.0 - hsx.b);
			q = hsx.c * (1.0 - (hsx.b * f));
			t = hsx.c * (1.0 - (hsx.b * (1.0 - f)));

			switch (i) {
			case 0:
				r = hsx.c;
				g = t;
				b = p;
				break;

			case 1:
				r = q;
				g = hsx.c;
				b = p;
				break;

			case 2:
				r = p;
				g = hsx.c;
				b = t;
				break;

			case 3:
				r = p;
				g = q;
				b = hsx.c;
				break;

			case 4:
				r = t;
				g = p;
				b = hsx.c;
				break;

			default:
				r = hsx.c;
				g = p;
				b = q;
				break;
			}
		}

		rgb.r = r * 255;
		rgb.g = g * 255;
		rgb.b = b * 255;
	}

	static void HSLtoRGB(Colors::ABSTRACT &hsx, Colors::RGB &rgb) {

		if (hsx.b == 0) rgb.r = rgb.g = rgb.b = (unsigned char)(hsx.c * 255);
		else {
			float v1, v2;
			float hue = (float)hsx.a / 360;

			v2 = (hsx.c < 0.5) ? (hsx.c * (1 + hsx.b)) : ((hsx.c + hsx.b) - (hsx.c * hsx.b));
			v1 = 2 * hsx.c - v2;

			rgb.r = (unsigned char)(255 * HueToRGB(v1, v2, hue + (1.0f / 3)));
			rgb.g = (unsigned char)(255 * HueToRGB(v1, v2, hue));
			rgb.b = (unsigned char)(255 * HueToRGB(v1, v2, hue - (1.0f / 3)));
		}
	}

	static void LABtoRGB(Colors::ABSTRACT &lab, Colors::RGB &rgb) {
		float X, Y, Z, fX, fY, fZ;
		int RR, GG, BB;

		fY = pow((lab.a + 16.0) / 116.0, 3.0);
		if (fY < 0.008856)
			fY = lab.a / 903.3;
		Y = fY;

		if (fY > 0.008856)
			fY = powf(fY, 1.0 / 3.0);
		else
			fY = 7.787 * fY + 16.0 / 116.0;

		fX = lab.a / 500.0 + fY;
		if (fX > 0.206893)
			X = powf(fX, 3.0);
		else
			X = (fX - 16.0 / 116.0) / 7.787;

		fZ = fY - lab.c / 200.0;
		if (fZ > 0.206893)
			Z = powf(fZ, 3.0);
		else
			Z = (fZ - 16.0 / 116.0) / 7.787;

		X *= (0.950456 * 255);
		Y *= 255;
		Z *= (1.088754 * 255);

		RR = (int)(3.240479 * X - 1.537150 * Y - 0.498535 * Z + 0.5);
		GG = (int)(-0.969256 * X + 1.875992 * Y + 0.041556 * Z + 0.5);
		BB = (int)(0.055648 * X - 0.204043 * Y + 1.057311 * Z + 0.5);

		rgb.r = (unsigned char)(RR < 0 ? 0 : RR > 255 ? 255 : RR);
		rgb.g = (unsigned char)(GG < 0 ? 0 : GG > 255 ? 255 : GG);
		rgb.b = (unsigned char)(BB < 0 ? 0 : BB > 255 ? 255 : BB);
	}
}
