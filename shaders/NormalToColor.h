#ifndef _NORMALTOCOLOR_H_
#define _NORMALTOCOLOR_H_

namespace shade {
  class NormalToColor : public Shader {
  public:
    RGB GetColor( Ray r_, World world ) override;
  };
} // namespace shade

#endif
