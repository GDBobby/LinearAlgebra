#pragma once

#include "TransformTemplate.h"

namespace lab{
template<std::floating_point F>
    struct Transform<F, 3> {
        Vector<F, 3> translation{F(0)};
        Vector<F, 3> scale{F(1)};
        Vector<F, 3> rotation{F(0)};

		template<uint8_t Alignment = 4> requires(Alignment >= 4)
		LAB_constexpr Matrix<F, 4, 4, Alignment> GetRotationXMatrix() const {
			Matrix<F, 4, 4, Alignment> ret{ F(0) };

			ret.columns[0][0] = F(1);
			ret.columns[3][3] = F(1);

			const F sinRet = Sin(rotation.x);
			const F cosRet = Cos(rotation.x);

			ret.columns[1][1] = cosRet;
			ret.columns[2][1] = -sinRet;
			ret.columns[1][2] = sinRet;
			ret.columns[2][2] = cosRet;

			return ret;
		}

		template<uint8_t Alignment = 4> requires(Alignment >= 4)
		LAB_constexpr Matrix<F, 4, 4, Alignment> GetRotationYMatrix() const {
			Matrix<F, 4, 4> ret{ F(0) };
			ret.columns[1][1] = F(1);
			ret.columns[3][3] = F(1);

			const F sinRet = Sin(rotation.y);
			const F cosRet = Cos(rotation.y);

			ret.columns[0][0] = cosRet;
			ret.columns[2][0] = sinRet;
			ret.columns[0][2] = -sinRet;
			ret.columns[2][2] = cosRet;

			return ret;
		}

		template<uint8_t Alignment = 4> requires(Alignment >= 4)
		LAB_constexpr Matrix<F, 4, 4, Alignment> GetRotationZMatrix() const {
			Matrix<F, 4, 4> ret{ F(0) };

			ret.columns[2][2] = F(1);
			ret.columns[3][3] = F(1);

			const F sinRet = Sin(rotation.z);
			const F cosRet = Cos(rotation.z);

			ret.columns[0][0] = cosRet;
			ret.columns[1][0] = -sinRet;
			ret.columns[0][1] = sinRet;
			ret.columns[1][1] = cosRet;

			return ret;
		}

		template<uint8_t Alignment = 4> requires(Alignment >= 4)
		LAB_constexpr Matrix<F, 4, 4, Alignment> GetScaleMatrix() const {
			Matrix<F, 4, 4, Alignment> ret{F(0)};
			ret.columns[0][0] = scale.x;
			ret.columns[1][1] = scale.y;
			ret.columns[2][2] = scale.z;
			ret.columns[3][3] = F(1);

			return ret;
		}
    
		template<uint8_t Alignment = 4> requires(Alignment >= 4)
		LAB_constexpr Matrix<F, 4, 4, Alignment> GetMatrix() const {
			Matrix<F, 4, 4, Alignment> ret;

			const F cosZ = Cos(rotation.z);
			const F sinZ = Sin(rotation.z);
			const F cosY = Cos(rotation.y);
			const F sinY = Sin(rotation.y);
			const F cosX = Cos(rotation.x);
			const F sinX = Sin(rotation.x);

			ret.columns[0][0] = scale.x * (cosY * cosZ + sinY * sinX * sinZ);
			ret.columns[0][1] = scale.x * (cosX * sinZ);
			ret.columns[0][2] = scale.x * (cosY * sinX * sinZ - cosZ * sinY);
			ret.columns[0][3] = F(0);

			ret.columns[1][0] = scale.y * (cosZ * sinY * sinX - cosY * sinZ);
			ret.columns[1][1] = scale.y * (cosX * cosZ);
			ret.columns[1][2] = scale.y * (cosY * cosZ * sinX + sinY * sinZ);
			ret.columns[1][3] = F(0);

			ret.columns[2][0] = scale.z * (cosX * sinY);
			ret.columns[2][1] = scale.z * (-sinX);
			ret.columns[2][2] = scale.z * (cosY * cosX);
			ret.columns[2][3] = F(0);

			ret.columns[3][0] = translation.x;
			ret.columns[3][1] = translation.y;
			ret.columns[3][2] = translation.z;
			ret.columns[3][3] = F(1);

			return ret;
		}

		template<uint8_t Alignment = 4> requires(Alignment >= 4)
		LAB_constexpr Matrix<F, 4, 4, Alignment> ToMatrixNoRotation() const {
			Matrix<F, 4, 4, Alignment> ret{F(0)};
			ret.columns[0][0] = scale.x;
			ret.columns[1][1] = scale.y;
			ret.columns[2][2] = scale.z;
			ret.columns[3][0] = translation.x;
			ret.columns[3][1] = translation.y;
			ret.columns[3][2] = translation.z;
			ret.columns[3][3] = F(1);
			return ret;
        }
	
		template<uint8_t Alignment = 4> requires(Alignment >= 3)
		LAB_constexpr Matrix<F, 3, 3, Alignment> GetNormalMatrix() const {
			Matrix<F, 3, 3, Alignment> ret{F(0)};
			const F cosZ = Cos(rotation.z);
			const F sinZ = Sin(rotation.z);
			const F cosY = Cos(rotation.y);
			const F sinY = Sin(rotation.y);
			const F cosX = Cos(rotation.x);
			const F sinX = Sin(rotation.x);

			ret.columns[0][0] = scale.x * (cosY * cosZ + sinY * sinX * sinZ);
			ret.columns[0][1] = scale.x * (cosX * sinZ);
			ret.columns[0][2] = scale.x * (cosY * sinX * sinZ - cosZ * sinY);

			ret.columns[1][0] = scale.y * (cosZ * sinY * sinX - cosY * sinZ);
			ret.columns[1][1] = scale.y * (cosX * cosZ);
			ret.columns[1][2] = scale.y * (cosY * cosZ * sinX + sinY * sinZ);

			ret.columns[2][0] = scale.z * (cosX * sinY);
			ret.columns[2][1] = scale.z * (-sinX);
			ret.columns[2][2] = scale.z * (cosY * cosX);

			return ret.Invert().Transposed();
		}

		//this needs coordinate system branching
		LAB_constexpr Vector<F, 3> GetForwardDir() const {
			return Vector<F, 3>{
				lab::Sin(rotation.y), 
				-lab::Sin(rotation.x), 
				lab::Cos(rotation.y)
			};
		}
		LAB_constexpr Vector<F, 3> GetNormalizedForwardDir() const {
			Vector<F, 3> ret{
				lab::Sin(rotation.y), 
				-lab::Sin(rotation.x), 
				lab::Cos(rotation.y)
			};
			//x^2 + z^2 is always 1, sin^2  cos^2 == 1
			return ret / (F(1) + Abs(ret.y));
		}
		LAB_constexpr Vector<F, 3> GetHorizontalForwardDir() const {
			return Vector<F, 3>{
				lab::Sin(rotation.y), 
				F(0),
				lab::Cos(rotation.y)
			};
		}
	};
} //namespace lab