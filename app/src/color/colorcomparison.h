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

#ifndef COLORCOMPARISON_H
#define COLORCOMPARISON_H

#include "colorspace.h"

namespace ColorSpace {
	struct EuclideanComparison {
		static double Compare(IColorSpace *a, IColorSpace *b);
	};

	struct Cie1976Comparison {
		static double Compare(IColorSpace *a, IColorSpace *b);
	};


	struct Cie94Comparison {
		enum APPLICATION {
			GRAPHIC_ARTS = 0,
			TEXTILES
		};

		struct Application {
			double kl, k1, k2;
			Application(APPLICATION appType);
		};

		static double Compare(IColorSpace *a, IColorSpace *b, APPLICATION appType=GRAPHIC_ARTS);
	};


	struct Cie2000Comparison {
		static double Compare(IColorSpace *a, IColorSpace *b);
	};


	struct CmcComparison {
		static const double defaultLightness;
		static const double defaultChroma;
		static double Compare(IColorSpace *a, IColorSpace *b);
	};
}

#endif // COLORCOMPARISON_H

