#include "Vec3.h"

namespace utility {

    //
    //=== Member function implementation.
    //
    inline void Vec3::make_unit_vector( void )
    {
        float length = (float)this->length();
        this->vec[X] = this->vec[X] / length;
        this->vec[Y] = this->vec[Y] / length;
        this->vec[Z] = this->vec[Z] / length;
        return; 
    }

    //
    //=== Non-member function implementation: operator overloading.
    //

    inline std::istream& operator>>( std::istream& is, Vec3 & v )
    {
        is >> v.vec[Vec3::element::X]
           >> v.vec[Vec3::element::Y]
           >> v.vec[Vec3::element::Z];
        return is;
    }

    inline std::ostream& operator<<( std::ostream& os, const Vec3 & v )
    {
        os << "{ "
           << v.vec[Vec3::element::X]
           << " "
           << v.vec[Vec3::element::Y]
           << " "
           << v.vec[Vec3::element::Z]
           << " }";

        return os;
    }

    inline Vec3 operator+( const Vec3 & v1, const Vec3 & v2 )
    {
        return Vec3( v1.vec[Vec3::X] + v2.vec[Vec3::X],
                     v1.vec[Vec3::Y] + v2.vec[Vec3::Y],
                     v1.vec[Vec3::Z] + v2.vec[Vec3::Z] );
    }

    inline Vec3 operator-( const Vec3 & v1, const Vec3 & v2 )
    {
        return Vec3( v1.vec[Vec3::X] - v2.vec[Vec3::X],
                     v1.vec[Vec3::Y] - v2.vec[Vec3::Y],
                     v1.vec[Vec3::Z] - v2.vec[Vec3::Z] );
    }

    inline Vec3 operator*( const Vec3 & v1, const Vec3 & v2 )
    {
        return Vec3( v1.vec[Vec3::X] * v2.vec[Vec3::X],
                     v1.vec[Vec3::Y] * v2.vec[Vec3::Y],
                     v1.vec[Vec3::Z] * v2.vec[Vec3::Z] );
    }

    inline Vec3 operator/( const Vec3 & v1, const Vec3 & v2 )
    {
        return Vec3( v1.vec[Vec3::X] / v2.vec[Vec3::X],
                     v1.vec[Vec3::Y] / v2.vec[Vec3::Y],
                     v1.vec[Vec3::Z] / v2.vec[Vec3::Z] );
    }

    // Uso: V * 4
    inline Vec3 operator*( const Vec3 & v, Vec3::element_type t )
    {
        return Vec3( v.vec[Vec3::X] * t,
                     v.vec[Vec3::Y] * t,
                     v.vec[Vec3::Z] * t );
    }

    // Uso: 4 * V
    inline Vec3 operator*( Vec3::element_type t, const Vec3 & v )
    {
        return v * t;
    }

    inline Vec3 operator/( const Vec3 & v, Vec3::element_type t )
    {
        return v * (1 / t);
    }

    inline Vec3::element_type dot( const Vec3 & v1, const Vec3 & v2 )
    {
        return v1[Vec3::X] * v2[Vec3::X] + v1[Vec3::Y] * v2[Vec3::Y] + v1[Vec3::Z] * v2[Vec3::Z];
    }

    inline Vec3 cross( const Vec3 & v1, const Vec3 & v2 )
    {
        return Vec3 ( v1.vec[Vec3::Y] * v2.vec[Vec3::Z] - v1.vec[Vec3::Z] * v2.vec[Vec3::Y], 
                      - (v1.vec[Vec3::X] * v2.vec[Vec3::Z] - v1.vec[Vec3::Z] * v2.vec[Vec3::X]),
                      v1.vec[Vec3::X] * v2.vec[Vec3::Y] - v1.vec[Vec3::Y] * v2.vec[Vec3::X] );
    }

    inline Vec3& Vec3::operator+=( const Vec3 & v )
    {
        vec[Vec3::X] = vec[Vec3::X] + v.vec[Vec3::X];
        vec[Vec3::Y] = vec[Vec3::Y] + v.vec[Vec3::Y];
        vec[Vec3::Z] = vec[Vec3::Z] + v.vec[Vec3::Z];

        return *this;
    }

    inline Vec3& Vec3::operator-=( const Vec3 & v )
    {
        vec[X] -= v.vec[X];
        vec[Y] -= v.vec[Y];
        vec[Z] -= v.vec[Z];

        return *this;
    }

    inline Vec3& Vec3::operator*=( const Vec3 & v )
    {
        return *this;
    }

    // For Colors
    inline Vec3& Vec3::operator/=( const Vec3 & v )
    {
        vec[X] = vec[X] / v.vec[X];
        vec[Y] = vec[Y] / v.vec[Y];
        vec[Z] = vec[Z] / v.vec[Z];
        return *this;
    }

    // Uso: A *= 3;
    inline Vec3& Vec3::operator*=( const element_type t )
    {
        vec[X] = vec[X] * t;
        vec[Y] = vec[Y] * t;
        vec[Z] = vec[Z] * t;
        return *this;
    }

    // Uso: A /= 3;
    inline Vec3& Vec3::operator/=( const element_type t )
    {
        if (t != 0){
            vec[X] = vec[X] / t;
            vec[Y] = vec[Y] / t;
            vec[Z] = vec[Z] / t;
        }
        
        return *this;
    }

    // Uso: Vec3 A = unit_vector( B );
    inline Vec3 unit_vector( const Vec3 & v )
    {
        return v / v.length();
    }

    inline RGB normalize( const RGB & color ) {
        return RGB (color[Vec3::X] / 255.0, color[Vec3::Y] / 255.0, color[Vec3::Z] / 255.0);
    }

    inline double get_rad(const Vec3 & v1, const Vec3 & v2, bool cos)
    {
        float arg = (float) (dot(v1, v2) / (v1.length() * v2.length()));
        return (cos) ? (acos(arg)) : (asin(arg));
    }

    inline double get_degree(const Vec3 & v1, const Vec3 & v2, bool cos)
    {
        float y = get_rad(v1, v2, cos);

        return 180 * y / 3.1415;
    }
}

//==============================[ Vec3.inl ]==============================//
