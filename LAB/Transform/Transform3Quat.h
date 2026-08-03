#pragma once

#include "TransformTemplate.h"

#include "../Quaternion.h"

namespace lab{
    template<std::floating_point F = float>
    struct TransformQuat {
        Vector<F, 3> translation{F(0)};
        Vector<F, 3> scale{F(1)};
        Quaternion<F> rotation{F(0), F(0), F(0), F(1)};

		LAB_constexpr Matrix<F, 4, 4> GetRotationMatrix() const {
			return rotation.ToMat4();
		}
		
		LAB_constexpr Matrix<F, 4, 4> GetScaleMatrix() const {
			Matrix<F, 4, 4> ret{F(0)};
			ret.columns[0][0] = scale.x;
			ret.columns[1][1] = scale.y;
			ret.columns[2][2] = scale.z;
			ret.columns[3][3] = F(1);

			return ret;
		}
    
		LAB_constexpr Matrix<F, 4, 4> GetMatrix() const {
            Matrix<F, 4, 4> ret;

            const F x = rotation.x;
            const F y = rotation.y;
            const F z = rotation.z;
            const F w = rotation.w;

            const F xx = F(2) * x * x;
            const F yy = F(2) * y * y;
            const F zz = F(2) * z * z;
            const F xy = F(2) * x * y;
            const F xz = F(2) * x * z;
            const F yz = F(2) * y * z;
            const F wx = F(2) * w * x;
            const F wy = F(2) * w * y;
            const F wz = F(2) * w * z;

            ret.columns[0][0] = scale.x * (F(1) - (yy + zz));
            ret.columns[0][1] = scale.x * (xy + wz);
            ret.columns[0][2] = scale.x * (xz - wy);
            ret.columns[0][3] = F(0);

            ret.columns[1][0] = scale.y * (xy - wz);
            ret.columns[1][1] = scale.y * (F(1) - (xx + zz));
            ret.columns[1][2] = scale.y * (yz + wx);
            ret.columns[1][3] = F(0);

            ret.columns[2][0] = scale.z * (xz + wy);
            ret.columns[2][1] = scale.z * (yz - wx);
            ret.columns[2][2] = scale.z * (F(1) - (xx + yy));
            ret.columns[2][3] = F(0);

            ret.columns[3][0] = translation.x;
            ret.columns[3][1] = translation.y;
            ret.columns[3][2] = translation.z;
            ret.columns[3][3] = F(1);

            return ret;
        }
	
		LAB_constexpr Matrix<F, 3, 3> GetNormalMatrix() const {
            auto ret = GetMatrix();

			return ret.Invert().Transposed();
		}

		//this needs coordinate system branching
		LAB_constexpr Vector<F, 3> GetForwardDir() const {
            return Vector<F, 3>{F(0)};
		}
		LAB_constexpr Vector<F, 3> GetNormalizedForwardDir() const {
            return Vector<F, 3>{F(0)};
		}
		LAB_constexpr Vector<F, 3> GetHorizontalForwardDir() const {
            return Vector<F, 3>{F(0)};
		}
	};
} //namespace lab