#pragma once

#include "Matrix3x3.h"
#include "Matrix4x4.h"

//i havent tested this

namespace lab{
    template<std::floating_point F>
    Matrix<F, 4, 4> Promote(Matrix<F, 3, 3> const& mat){
        return Matrix<F, 4, 4>{
            Vector<F, 4>{mat.At(0, 0), mat.At(0, 1), F(0), F(0)},
            Vector<F, 4>{mat.At(1, 0), mat.At(1, 1), F(0), F(0)},
            Vector<F, 4>{F(0),         F(0),         F(1), F(0)},
            Vector<F, 4>{mat.At(2, 0), mat.At(2, 1), F(0), F(1)}
        };
    }

    template<std::floating_point F>
    Matrix<F, 3, 3> Demote(Matrix<F, 4, 4> const& mat){
        return Matrix<F, 3, 3>{
            Vector<F, 4>{mat.At(0, 0), mat.At(0, 1), F(0)},
            Vector<F, 4>{mat.At(1, 0), mat.At(1, 1), F(0)},
            Vector<F, 4>{mat.At(2, 0), mat.At(2, 1), F(1)}
        };
    }
}