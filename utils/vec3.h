#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <cassert>

namespace utility {

    class vec3 
    {
        public:
            typedef float element_type;
            enum element { X=0, Y=1, Z=2, R=0, G=1, B=2 };

            element_type vec[3];

            vec3(element_type x = 0.f, element_type y = 0.f, element_type z=0.f) : vec{ x, y, z }
            { 

            }

            inline element_type x() { return vec[X]; }
            inline element_type y() { return vec[Y]; }
            inline element_type z() { return vec[Z]; }
            inline element_type r() { return vec[R]; }
            inline element_type g() { return vec[G]; }
            inline element_type b() { return vec[B]; }

            // indexed access operator (rhs)
            inline element_type operator[]( size_t idx ) const { 
                return vec[ idx ]; 
            }
            // indexed access operator (lhs)
            inline element_type& operator[]( size_t idx ) { 
                return vec[ idx ]; 
            }

            inline vec3& operator+=( const vec3& );
            inline vec3& operator-=( const vec3& );
            inline vec3& operator*=( const vec3& );
            inline vec3& operator/=( const vec3& );
            inline vec3& operator*=( const element_type );
            inline vec3& operator/=( const element_type );

            inline vec3& operator+(void) {
                return *this;
            }

            inline vec3 operator-(void) { 
                return vec3(-vec[X], -vec[Y], -vec[Z] );
            }

            inline element_type length( void ) const {
                return sqrt( this->squared_length() );
            }

            inline element_type squared_length( void ) const
            {
                return vec[X] * vec[X] + vec[Y] * vec[Y] + vec[Z] * vec[Z];
            }

            inline void make_unit_vector( void );
    };

    typedef vec3 rgb;
    typedef vec3 offset;
    typedef vec3 point3;
}

#include "vec3.inl"

#endif