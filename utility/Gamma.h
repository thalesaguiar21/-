#ifndef _GAMMA_H_
#define _GAMMA_H_

#include <cmath>

namespace utils {
  RGB GammaCorrection( RGB color, float power ) {
    RGB gamaCrr ( pow(color.R(), 1.0/power),
                  pow(color.B(), 1.0/power),
                  pow(color.G(), 1.0/power));
    return gamaCrr;
  }
}// namespace utils


#endif
