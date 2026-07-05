#pragma once

#include "TransformTemplate.h"

namespace lab {
    template<std::floating_point F>
    struct Transform<F, 2> {
        Vector<F, 2> translation{F(0)};
        Vector<F, 2> scale{F(1)};
        F rotation{F(0)};

		template<uint8_t Alignment = 3> requires(Alignment >= 3)
		LAB_constexpr Matrix<F, 3, 3, Alignment> ToMatrix() const{
			const float cosine = Cos(rotation);
			const float sine = Sin(rotation);
			Matrix<F, 3, 3, Alignment> ret;
			ret.columns[0][0] = scale.x * cosine;
			ret.columns[0][1] = scale.x * sine;
			ret.columns[0][2] = 0.f;

			ret.columns[1][0] = scale.y * -sine;
			ret.columns[1][1] = scale.y * cosine;
			ret.columns[1][2] = 0.f;

			ret.columns[2][0] = translation.x;
			ret.columns[2][1] = translation.y;
			ret.columns[2][2] = 1.f;

			return ret;
		}

		LAB_constexpr Matrix<F, 4, 4> ToMat4(const float depth) const {
			const float cosine = Cos(rotation);
			const float sine = Sin(rotation);
			Matrix<F, 4, 4> ret;
			ret.columns[0][0] = scale.x * cosine;
			ret.columns[0][1] = scale.x * sine;
			ret.columns[0][2] = 0.f;
			ret.columns[0][3] = 0.f;

			ret.columns[1][0] = scale.y * -sine;
			ret.columns[1][1] = scale.y * cosine;
			ret.columns[1][2] = 0.f;
			ret.columns[1][3] = 0.f;

			ret.columns[2][0] = 0.f;
			ret.columns[2][1] = 0.f;
			ret.columns[2][2] = 1.f;
			ret.columns[2][3] = 0.f;

			ret.columns[3][0] = translation.x;
			ret.columns[3][1] = translation.y;
			ret.columns[3][2] = depth;
			ret.columns[3][3] = 1.f;
			return ret;
		}
	
		template<uint8_t Alignment = 3> requires(Alignment >= 3)
		LAB_constexpr Matrix<F, 3, 3, Alignment> ToMatrixNoRotation() const {
			//const float cosine = glm::cos(rotation);
			//const float sine = glm::sin(rotation);
			Matrix<F, 3, 3, Alignment> ret{F(0)};
			ret.columns[0][0] = scale.x;
			ret.columns[1][1] = scale.y;

			ret.columns[2][0] = translation.x;
			ret.columns[2][1] = translation.y;
			ret.columns[2][2] = 1.f;

        	return ret;
    	}
    };
}//namespace lab