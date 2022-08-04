/*
MIT License

Copyright (c) 2017 Berendea Nicolae

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, qExpRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARIqSinG FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

https://github.com/berendeanicolae/ColorSpace
*/

#include "colorcomparison.h"
#include "helper.h"


namespace ColorSpace {
	double EuclideanComparison::Compare(IColorSpace *a, IColorSpace *b) {
		Rgb rgb_a;
		Rgb rgb_b;

		a->ToRgb(&rgb_a);
		b->ToRgb(&rgb_b);

        return  qSqrt(qPow(rgb_a.r - rgb_b.r, 2) + qPow(rgb_a.g - rgb_b.g, 2) + qPow(rgb_a.b - rgb_b.b, 2));
	}

	double Cie1976Comparison::Compare(IColorSpace *a, IColorSpace *b) {
		Lab lab_a;
		Lab lab_b;

		a->To<Lab>(&lab_a);
		b->To<Lab>(&lab_b);

        return  qSqrt(qPow(lab_a.l - lab_b.l, 2) + qPow(lab_a.a - lab_b.a, 2) + qPow(lab_a.b - lab_b.b, 2));
	}

	Cie94Comparison::Application::Application(Cie94Comparison::APPLICATION appType) {
		switch (appType) {
		case GRAPHIC_ARTS:
			kl = 1.0;
			k1 = 0.045;
			k2 = 0.015;
			break;
		case TEXTILES:
			kl = 2.0;
			k1 = 0.048;
			k2 = 0.014;
			break;
		}
	}

	double Cie94Comparison::Compare(IColorSpace *a, IColorSpace *b, APPLICATION appType) {
		Application app(appType);
		Lab lab_a;
		Lab lab_b;

		a->To<Lab>(&lab_a);
		b->To<Lab>(&lab_b);

		double deltaL = lab_a.l - lab_b.l;
		double deltaA = lab_a.a - lab_b.a;
		double deltaB = lab_a.b - lab_b.b;

        double c1 =  qSqrt(qPow(lab_a.a, 2) + qPow(lab_a.b, 2));
        double c2 =  qSqrt(qPow(lab_b.a, 2) + qPow(lab_b.b, 2));
		double deltaC = c1 - c2;

        double deltaH = qPow(deltaA, 2) + qPow(deltaB, 2) - qPow(deltaC, 2);

		double sl = 1.0;
		double sc = 1.0 + app.k1*c1;
		double sh = 1.0 + app.k2*c1;

		deltaL /= app.kl*sl;
		deltaC /= sc;

        return  qSqrt(qPow(deltaL, 2) + qPow(deltaC, 2) + deltaH/qPow(sh, 2));
	}

	double Cie2000Comparison::Compare(IColorSpace *a, IColorSpace *b) {
		const double eps = 1e-5;
		Lab lab_a;
		Lab lab_b;

		a->To<Lab>(&lab_a);
		b->To<Lab>(&lab_b);

		// calculate ci, hi, i=1,2
        double c1 =  qSqrt(qPow(lab_a.a, 2) + qPow(lab_a.b, 2));
        double c2 =  qSqrt(qPow(lab_b.a, 2) + qPow(lab_b.b, 2));
		double meanC = (c1 + c2) / 2.0;
        double meanC7 = qPow(meanC, 7);

        double g = 0.5*(1 -  qSqrt(meanC7 / (meanC7 + 6103515625.))); // 0.5*(1- qSqrt(meanC^7/(meanC^7+25^7)))
		double a1p = lab_a.a * (1 + g);
		double a2p = lab_b.a * (1 + g);

        c1 =  qSqrt(qPow(a1p, 2) + qPow(lab_a.b, 2));
        c2 =  qSqrt(qPow(a2p, 2) + qPow(lab_b.b, 2));
        double h1 = fmod(qAtan2(lab_a.b, a1p) + 2*M_PI, 2*M_PI);
        double h2 = fmod(qAtan2(lab_b.b, a2p) + 2*M_PI, 2*M_PI);

		// compute deltaL, deltaC, deltaH
		double deltaL = lab_b.l - lab_a.l;
		double deltaC = c2 - c1;
		double deltah;

		if (c1*c2 < eps) {
			deltah = 0;
		}
		if (std::abs(h2 - h1) <= M_PI) {
			deltah = h2 - h1;
		}
		else if (h2 > h1) {
			deltah = h2 - h1 - 2* M_PI;
		}
		else {
			deltah = h2 - h1 + 2 * M_PI;
		}

        double deltaH = 2 *  qSqrt(c1*c2)*qSin(deltah / 2);

		// calculate CIEDE2000
		double meanL = (lab_a.l + lab_b.l) / 2;
		meanC = (c1 + c2) / 2.0;
        meanC7 = qPow(meanC, 7);
		double meanH;

		if (c1*c2 < eps) {
			meanH = h1 + h2;
		}
		if (std::abs(h1 - h2) <= M_PI + eps) {
			meanH = (h1 + h2) / 2;
		}
		else if (h1 + h2 < 2*M_PI) {
			meanH = (h1 + h2 + 2*M_PI) / 2;
		}
		else {
			meanH = (h1 + h2 - 2*M_PI) / 2;
		}

		double T = 1
            - 0.17*qCos(meanH - DegToRad(30))
            + 0.24*qCos(2 * meanH)
            + 0.32*qCos(3 * meanH + DegToRad(6))
            - 0.2*qCos(4 * meanH - DegToRad(63));
        double sl = 1 + (0.015*qPow(meanL - 50, 2)) / qPow(20 + qPow(meanL - 50, 2), 2);
		double sc = 1 + 0.045*meanC;
		double sh = 1 + 0.015*meanC*T;
        double rc = 2 *  qSqrt(meanC7 / (meanC7 + 6103515625.));
        double rt = -qSin(DegToRad(60 * qExp(-qPow((RadToDeg(meanH) - 275) / 25, 2)))) * rc;

        return  qSqrt(qPow(deltaL / sl, 2) + qPow(deltaC / sc, 2) + qPow(deltaH / sh, 2) + rt * deltaC / sc * deltaH / sh);
	}


	const double CmcComparison::defaultLightness = 2.;
	const double CmcComparison::defaultChroma = 1.;
	double CmcComparison::Compare(IColorSpace *a, IColorSpace *b) {
		Lch lch_a;
		Lch lch_b;

		a->To<Lch>(&lch_a);
		b->To<Lch>(&lch_b);

		double deltaL = lch_a.l - lch_b.l;
		double deltaC = lch_a.c - lch_b.c;
		double deltaH = 0;

        double f =  qSqrt(qPow(lch_a.c, 4) / (qPow(lch_a.c, 4) + 1900));
        double t = (164 <= lch_a.h && lch_a.h <= 345) ? (0.56 + std::abs(0.2*qCos(lch_a.h + 168))) : (0.36 + std::abs(0.4*qCos(lch_a.h + 35)));

		double sl = (lch_a.l < 16) ? 0.511 : (0.040975*lch_a.l / (1 + 0.01765*lch_a.l));
		double sc = 0.0638*lch_a.c / (1 + 0.0131*lch_a.c) + 0.638;
		double sh = sc*(f*t + 1 - f);

        return  qSqrt(qPow(deltaL / (defaultLightness*sl), 2) + qPow(deltaC / (defaultChroma*sc), 2) + qPow(deltaH / sh, 2));
	}
}

