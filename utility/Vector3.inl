#include "Vector3.h"

namespace utils {

  // Member functions
  Vector3::Vector3 ( void ) {
    e[Cx] = 0.f;
    e[Cy] = 0.f;
    e[Cz] = 0.f;
  }

  Vector3::Vector3( Vector3::element_type x, Vector3::element_type y ,
                    Vector3::element_type z ) {
    e[Cx] = x;
    e[Cy] = y;
    e[Cz] = z;
  }

  inline Vector3::element_type Vector3::operator[]( size_t idx ) const {
    return e[idx];
  }

  inline Vector3::element_type& Vector3::operator[]( size_t idx ) {
    return e[idx];
  }

  inline Vector3& Vector3::operator+(void) {
    return *this;
  }

  inline Vector3 Vector3::operator-(void) {
    return Vector3(-e[Cx], -e[Cy], -e[Cz]);
  }

  inline Vector3 operator+( const Vector3 & v1, const Vector3 & v2 ) {
    return Vector3( v1.e[Vector3::Cx] + v2.e[Vector3::Cx],
                    v1.e[Vector3::Cy] + v2.e[Vector3::Cy],
                    v1.e[Vector3::Cz] + v2.e[Vector3::Cz] );
  }

  inline Vector3 operator-( const Vector3 & v1, const Vector3 & v2 ) {
    return Vector3( v1.e[Vector3::Cx] - v2.e[Vector3::Cx],
                    v1.e[Vector3::Cy] - v2.e[Vector3::Cy],
                    v1.e[Vector3::Cz] - v2.e[Vector3::Cz] );
  }

  inline Vector3 operator*( const Vector3 & v1, const Vector3 & v2 ) {
    return Vector3( v1.e[Vector3::Cx] * v2.e[Vector3::Cx],
                    v1.e[Vector3::Cy] * v2.e[Vector3::Cy],
                    v1.e[Vector3::Cz] * v2.e[Vector3::Cz] );
  }

  inline Vector3 operator/( const Vector3 & v1, const Vector3 & v2 ) {
    return Vector3( v1.e[Vector3::Cx] / v2.e[Vector3::Cx],
                    v1.e[Vector3::Cy] / v2.e[Vector3::Cy],
                    v1.e[Vector3::Cz] / v2.e[Vector3::Cz] );
  }

  // Uso: V * 4
  inline Vector3 operator*( const Vector3 & v, Vector3::element_type t ) {
      return Vector3( v.e[Vector3::Cx] * t,
                      v.e[Vector3::Cy] * t,
                      v.e[Vector3::Cz] * t );
  }

  // Uso: 4 * V
  inline Vector3 operator*( Vector3::element_type t, const Vector3 & v ) {
    return v * t;
  }

  inline Vector3 operator/( const Vector3 & v, Vector3::element_type t ) {
    return v * (1 / t);
  }

  inline Vector3::element_type dot( const Vector3 & v1, const Vector3 & v2 ) {
    return  v1[Vector3::Cx] * v2[Vector3::Cx] +
            v1[Vector3::Cy] * v2[Vector3::Cy] +
            v1[Vector3::Cz] * v2[Vector3::Cz];
  }

  inline Vector3& Vector3::operator+=( const Vector3& u ) {
    *this = *this + u;
    return *this;
  }

  inline Vector3& Vector3::operator-=( const Vector3& u ) {
    *this = *this - u;
    return *this;
  }

  inline Vector3& Vector3::operator*=( const Vector3& u ) {
    *this = *this * u;
    return *this;
  }

  inline Vector3& Vector3::operator/=( const Vector3& u ) {
    *this = *this / u;
    return *this;
  }

  inline Vector3& Vector3::operator*=( const Vector3::element_type t ) {
    *this = *this * t;
    return *this;
  }

  inline Vector3& Vector3::operator/=( const Vector3::element_type t ) {
    *this = *this / t;
    return *this;
  };

  // Accesors
  inline Vector3::element_type Vector3::X() {
    return e[Cx];
  }

  inline Vector3::element_type Vector3::Y() {
    return e[Cy];
  }

  inline Vector3::element_type Vector3::Z() {
    return e[Cz];
  }

  inline Vector3::element_type Vector3::R() {
    return Vector3::X();
  }

  inline Vector3::element_type Vector3::G() {
    return Vector3::Y();
  }

  inline Vector3::element_type Vector3::B() {
    return Vector3::Z();
  }

  // Non member functions
  inline std::istream& operator>>( std::istream& is, Vector3 & v ) {
    is >> v.e[Vector3::Cx] >> v.e[Vector3::Cy] >> v.e[Vector3::Cz];
    return is;
  }

  inline std::ostream& operator<<( std::ostream& os, const Vector3 & v ) {
    os  <<  "{ " << v.e[Vector3::Cx]
        << " " << v.e[Vector3::Cy]
        << " " << v.e[Vector3::Cz] << " }";
    return os;
  }

  // Methods
  inline Vector3::element_type Vector3::Length( void ) const {
    return sqrt(e[Cx]*e[Cx] + e[Cy]*e[Cy] + e[Cz]*e[Cz]);
  }

  inline Vector3::element_type Vector3::SquaredLength( void ) const {
    return pow(Length(), 2.0);
  }

  inline void Vector3::MakeUnitVector( void ) {
    float length = (float)this->Length();
    this->e[Vector3::Cx] = this->e[Vector3::Cx] / length;
    this->e[Vector3::Cy] = this->e[Vector3::Cy] / length;
    this->e[Vector3::Cz] = this->e[Vector3::Cz] / length;
  }

  inline Vector3 Cross( const Vector3 & v1, const Vector3 & v2 ) {
    return Vector3 ( v1.e[Vector3::Cy] * v2.e[Vector3::Cz] - v1.e[Vector3::Cz] * v2.e[Vector3::Cy],
                    (- (v1.e[Vector3::Cx] * v2.e[Vector3::Cz] - v1.e[Vector3::Cz] * v2.e[Vector3::Cx])),
                    v1.e[Vector3::Cx] * v2.e[Vector3::Cy] - v1.e[Vector3::Cy] * v2.e[Vector3::Cx] );
  }

  // Uso: Vector3 A = unit_vector( B );
  inline Vector3 UnitVector( const Vector3 & v ) {
    Vector3::element_type length = v.Length();
    if (length != 0.0)
      return v / v.Length();
    else
      return Vector3(0.0, 0.0, 0.0);
  }

  inline RGB NormRgb( const RGB & color ) {
    return RGB (color[Vector3::Cr] / 255.0,
                color[Vector3::Cg] / 255.0,
                color[Vector3::Cb] / 255.0);
  }

  inline double GetRad(const Vector3 & v1, const Vector3 & v2, bool cos) {
    float arg = (float) (dot(v1, v2) / (v1.Length() * v2.Length()));
    return (cos) ? (acos(arg)) : (asin(arg));
  }

  inline double DegreeBetwenn(const Vector3 & v1, const Vector3 & v2, bool cos) {
    float y = GetRad(v1, v2, cos);
    return 180 * y / 3.1415;
  }

  inline RGB TruncateRgb(const RGB & color_) {
    RGB aux = color_;
    if(color_[Vector3::Cx] > 1.0) aux.e[Vector3::Cx] = 1.0;
    if(color_[Vector3::Cy] > 1.0) aux.e[Vector3::Cy] = 1.0;
    if(color_[Vector3::Cz] > 1.0) aux.e[Vector3::Cz] = 1.0;
    if(color_[Vector3::Cx] < 0.0) aux.e[Vector3::Cx] = 0.0;
    if(color_[Vector3::Cy] < 0.0) aux.e[Vector3::Cy] = 0.0;
    if(color_[Vector3::Cz] < 0.0) aux.e[Vector3::Cz] = 0.0;
    return aux;
  }
}
