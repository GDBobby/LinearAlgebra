#pragma once
#include "VectorTemplate.h"

#ifdef USING_SIMD
#include <immintrin.h>
#endif

namespace lab{
    template<std::floating_point F>
    struct Vector<F, 4> {
        F x;
        F y;
        F z;
        F w;

        LAB_constexpr Vector() {}
        [[nodiscard]] explicit LAB_constexpr Vector(F const _x, F const _y, F const _z, F const _w) : x{ _x }, y{ _y }, z{ _z }, w{ _w } {}
        [[nodiscard]] explicit LAB_constexpr Vector(F const all) : x{ all }, y{ all }, z{ all }, w{ all } {}

        //constructing piece wise with vec2
        [[nodiscard]] explicit LAB_constexpr Vector(Vector<F, 2> const vec1, Vector<F, 2> const vec2) : x{vec1.x}, y{vec1.y}, z{vec2.x}, w{vec2.y} {}
        [[nodiscard]] explicit LAB_constexpr Vector(Vector<F, 2> const vec, F const _z, F const _w) : x{vec.x}, y{vec.y}, z{_z}, w{_w} {}
        [[nodiscard]] explicit LAB_constexpr Vector(F const _x, Vector<F, 2> const vec, F const _w) : x{_x}, y{vec.x}, z{vec.y}, w{_w} {}
        [[nodiscard]] explicit LAB_constexpr Vector(F const _x, F const _y, Vector<F, 2> const vec) : x{_x}, y{_y}, z{vec.x}, w{vec.y} {}
        //constructing piecewise with vec3
        [[nodiscard]] explicit LAB_constexpr Vector(Vector<F, 3> const vec, F const _w) : x{vec.x}, y{vec.y}, z{vec.z}, w{_w} {}
        [[nodiscard]] explicit LAB_constexpr Vector(F const _x, Vector<F, 3> const vec) : x{_x}, y{vec.x}, z{vec.y}, w{vec.z} {}
        //copy constructors, including vec2 and vec3
        //do i need to make these explicit?
        [[nodiscard]] explicit  LAB_constexpr Vector(Vector<F, 2> const& other) : x{ other.x }, y{ other.y }, z{ F(0)}, w{F(0)} {}
        [[nodiscard]] explicit  LAB_constexpr Vector(Vector<F, 3> const& other) : x{ other.x }, y{ other.y }, z{ other.z }, w{ F(0) } {}
        LAB_constexpr Vector(Vector const& other) : x{ other.x }, y{ other.y }, z{ other.z }, w{ other.w } {}

#ifdef USING_SIMD
        using SIMD_Type = typename std::conditional<
            std::is_same_v<F, float>,
            __m128,
            typename std::conditional<
                std::is_same_v<F, double>,
                __m256,
                __m256 //error
            >::type
        >::type;

        Vector(SIMD_Type vec) {
            _mm_storeu_ps(&x, vec);
        }
        IMD_Type ToSIMD() const{
            return _mm_loadu_ps(&x);
        }
#endif
        
        LAB_constexpr Vector& operator=(Vector const& other){
            x = other.x;
            y = other.y;
            z = other.z;
            w = other.w;
            return *this;
        }
        
        LAB_constexpr Vector operator-() const{
            return Vector{
                -x,
                -y,
                -z,
                -w
            };
        }

        LAB_constexpr F& operator[](uint8_t const row) {
            if (row == 0) {
                return x;
            }
            else if (row == 1) {
                return y;
            }
            else if (row == 2) {
                return z;
            }
            else if (row == 3) {
                return w;
            }
            LAB_UNREACHABLE;
        }
        LAB_constexpr F operator[](uint8_t const row) const {
            if (row == 0) {
                return x;
            }
            else if (row == 1) {
                return y;
            }
            else if (row == 2) {
                return z;
            }
            else if (row == 3) {
                return w;
            }
            LAB_UNREACHABLE;
        }

        template<uint8_t DimensionsOther>
        LAB_constexpr Vector& operator=(Vector<F, DimensionsOther> const& other) {
                x = other.x;
                y = other.y;
            if constexpr (DimensionsOther == 3) {
                z = other.z;
            }
            static_assert(DimensionsOther != 4 && "this should be getting caught by the copy assignment operator");
            return *this;
        }

        LAB_constexpr bool operator==(Vector const other) const {
            return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
        }
        LAB_constexpr void operator+=(Vector const other) {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
        }
        LAB_constexpr Vector operator+(Vector const other) const {
            return Vector{
                x + other.x,
                y + other.y,
                z + other.z,
                w + other.w
            };
        }
        LAB_constexpr Vector operator*(Vector const other) const {
            return Vector{
                x * other.x,
                y * other.y,
                z * other.z,
                w * other.w
            };
        }

        LAB_constexpr void operator-=(Vector const other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            w -= other.w;
        }
        LAB_constexpr Vector operator-(Vector const other) const {
            return Vector{
                x - other.x,
                y - other.y,
                z - other.z,
                w - other.w
            };
        }
        LAB_constexpr Vector& operator*=(F const multiplier) {
            x *= multiplier;
            y *= multiplier;
            z *= multiplier;
            w *= multiplier;
            return *this;
        }
        LAB_constexpr Vector operator*(F const multiplier) const {
            return Vector{
                x * multiplier,
                y * multiplier,
                z * multiplier,
                w * multiplier
            };
        }
        LAB_constexpr Vector& operator/=(F const divisor) {
            x /= divisor;
            y /= divisor;
            z /= divisor;
            w /= divisor;
            return *this;
        }
        LAB_constexpr Vector operator/(F const divisor) const {
            return Vector{
                x / divisor,
                y / divisor,
                z / divisor,
                w / divisor
            };
        }
        LAB_constexpr Vector& operator*=(Vector const other){
            x *= other.x;
            y *= other.y;
            z *= other.z;
            w *= other.w;
            return *this;
        }

        LAB_constexpr F SquaredMagnitude() const {
            return x * x + y * y + z * z + w * w;
        }

        LAB_constexpr F Magnitude() const {
            return Sqrt(SquaredMagnitude());
        }

        LAB_constexpr Vector& Normalize() {
            const F invMag = InverseSqrt(SquaredMagnitude());
            operator*=(invMag);
            return *this;
        }
        LAB_constexpr Vector Normalized() const{
            const auto invMag = InverseSqrt(SquaredMagnitude());
            return operator*(invMag);
        }

        LAB_constexpr F Dot(Vector const other) const {
            return x * other.x + y * other.y + z * other.z + w * other.w;
        }
    };
}
