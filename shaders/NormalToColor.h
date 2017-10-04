#ifndef _NORMALTOCOLOR_H_
#define _NORMALTOCOLOR_H_

class NormalToColor : public Shader {
public:
  RGB GetColor( Ray r_, World world ) override;
};

#endif
