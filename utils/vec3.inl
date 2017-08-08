#include "vec3.h"
//
//=== Member function implementation.
//
inline void vec3::make_unit_vector( void )
{
    /**
     * +---> unit vector.
     * |
     *
     * ^     1
     * v = _____ * v
     *     ||v||
     *
     * ||v|| = sqrt( v dot v )
     *
     *      1
     * k =_____
     *    ||v||
     */
    // TODO
    float length = (float)this->length();
    this->vec[X] = this->vec[X] / length;
    this->vec[Y] = this->vec[Y] / length;
    this->vec[Z] = this->vec[Z] / length;
    return; 
}

//
//=== Non-member function implementation: operator overloading.
//

inline std::istream& operator>>( std::istream& is, vec3 & v )
{
    is >> v.vec[vec3::element::X]
       >> v.vec[vec3::element::Y]
       >> v.vec[vec3::element::Z];
    return is;
}

inline std::ostream& operator<<( std::ostream& os, const vec3 & v )
{
    os << "{ "
       << v.vec[vec3::element::X]
       << " "
       << v.vec[vec3::element::Y]
       << " "
       << v.vec[vec3::element::Z]
       << " }";

    return os;
}

inline vec3 operator+( const vec3 & v1, const vec3 & v2 )
{
    return vec3( v1.vec[vec3::X] + v2.vec[vec3::X],
                 v1.vec[vec3::Y] + v2.vec[vec3::Y],
                 v1.vec[vec3::Z] + v2.vec[vec3::Z] );
}

inline vec3 operator-( const vec3 & v1, const vec3 & v2 )
{
    vec3 tmp = v2;
    return v1 + (-tmp);
}

inline vec3 operator*( const vec3 & v1, const vec3 & v2 )
{
    return vec3(0, 0, 0);
}

inline vec3 operator/( const vec3 & v1, const vec3 & v2 )
{
}

// Uso: V * 4
inline vec3 operator*( const vec3 & v, vec3::element_type t )
{
    return vec3( v.vec[vec3::X] * t,
                 v.vec[vec3::Y] * t,
                 v.vec[vec3::Z] * t );
}

// Uso: 4 * V
inline vec3 operator*( vec3::element_type t, const vec3 & v )
{
    return v * t;
}

inline vec3 operator/( const vec3 & v, vec3::element_type t )
{
    return v * (1 / t);
}

inline vec3::element_type dot( const vec3 & v1, const vec3 & v2 )
{
    return v1[vec3::X]*v2[vec3::X] 
           + v1[vec3::Y]*v2[vec3::Y] 
           + v1[vec3::Z]*v2[vec3::Z];
}

inline vec3 cross( const vec3 & v1, const vec3 & v2 )
{
    return vec3 ( v1.vec[vec3::Y] * v2.vec[vec3::Z] - v1.vec[vec3::Z] * v2.vec[vec3::Y], 
                  - (v1.vec[vec3::X] * v2.vec[vec3::Z] - v1.vec[vec3::Z] * v2.vec[vec3::X]),
                  v1.vec[vec3::X] * v2.vec[vec3::Y] - v1.vec[vec3::Y] * v2.vec[vec3::X] );
}

inline vec3& vec3::operator+=( const vec3 & v )
{
    vec[vec3::X] = vec[vec3::X] + v.vec[vec3::X];
    vec[vec3::Y] = vec[vec3::Y] + v.vec[vec3::Y];
    vec[vec3::Z] = vec[vec3::Z] + v.vec[vec3::Z];

    return *this;
}

inline vec3& vec3::operator-=( const vec3 & v )
{
    vec[X] -= v.vec[X];
    vec[Y] -= v.vec[Y];
    vec[Z] -= v.vec[Z];

    return *this;
}

inline vec3& vec3::operator*=( const vec3 & v )
{
    return *this;
}

// Uso: A /= B;
inline vec3& vec3::operator/=( const vec3 & v )
{
    // TODO

    return *this;
}

// Uso: A *= 3;
inline vec3& vec3::operator*=( const element_type t )
{
    vec[X] = vec[X] * t;
    vec[Y] = vec[Y] * t;
    vec[Z] = vec[Z] * t;
    return *this;
}

// Uso: A /= 3;
inline vec3& vec3::operator/=( const element_type t )
{
    if (t != 0){
        vec[X] = vec[X] / t;
        vec[Y] = vec[Y] / t;
        vec[Z] = vec[Z] / t;
    }
    
    return *this;
}

// Uso: vec3 A = unit_vector( B );
inline vec3 unit_vector( const vec3 & v )
{
    vec3 tmp = v;
    tmp /= v.length();
    return tmp;
}

inline double get_rad(const vec3 & v1, const vec3 & v2, bool cos)
{
    float arg = (float) (dot(v1, v2) / (v1.length() * v2.length()));
    return (cos) ? (acos(arg)) : (asin(arg));
}

inline double get_degree(const vec3 & v1, const vec3 & v2, bool cos)
{
    float y = get_rad(v1, v2, cos);

    return 180 * y / 3.1415;
}

//==============================[ vec3.inl ]==============================//
