#ifndef _VECTOR3_H_
#define _VECTOR3_H_

/*
Represents a basic tri-dimensional vector. can also be interpreted as a RGB
color, a tri-dimensional Point in space
*/
namespace utils {
  class Vector3 {
    public:
      typedef float element_type;
      enum element { Cx=0, Cy=1, Cz=2, Cr=0, Cg=1, Cb=2 };
      element_type e[3];

      // Constructors
      Vector3 ( void );
      Vector3(element_type x, element_type y, element_type z);

      // Operators overloading
      element_type operator[]( size_t idx ) const;
      element_type& operator[]( size_t idx );
      Vector3& operator+=( const Vector3& );
      Vector3& operator-=( const Vector3& );
      Vector3& operator*=( const Vector3& );
      Vector3& operator/=( const Vector3& );
      Vector3& operator*=( const element_type );
      Vector3& operator/=( const element_type );
      Vector3& operator+(void);
      Vector3 operator-(void);

      // Accesors
      element_type X();
      element_type Y();
      element_type Z();
      element_type R();
      element_type G();
      element_type B();

      // Methods
      element_type Length() const;
      element_type SquaredLength() const;
      void MakeUnitVector();
  };

  typedef Vector3 RGB;
  typedef Vector3 Offset;
  typedef Vector3 Point3;
} // namespace utils

#include "Vector3.inl"

#endif
