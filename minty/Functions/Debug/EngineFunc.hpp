#pragma once

namespace cheat {

	class EngineFunc {

	public:

		static bool Vector3_Compare(app::Vector3 Vector3_1, app::Vector3 Vector3_2)
		{
			if (Vector3_1.x == Vector3_2.x && Vector3_1.y == Vector3_2.y && Vector3_1.z == Vector3_2.z)
				return true;
			else
				return false;	
		}
		static bool Vector3_Equal0(app::Vector3 Vector3_1)
		{
			if (Vector3_1.x == 0.f && Vector3_1.y == 0.f && Vector3_1.z == 0.f)
				return true;
			else
				return false;
		}

		static bool Quaternion_Equal0(app::Quaternion Quaternion_1)
		{
			if (Quaternion_1.x == 0.f && Quaternion_1.y == 0.f && Quaternion_1.z == 0.f && Quaternion_1.w == 0.f)
				return true;
			else
				return false;
		}

		static bool Quaternion_Compare(app::Quaternion Quaternio_1, app::Quaternion Quaternio_2)
		{
			if (Quaternio_1.x == Quaternio_2.x && Quaternio_1.y == Quaternio_2.y && Quaternio_1.z == Quaternio_2.z&& Quaternio_1.w == Quaternio_2.w)
				return true;
			else
				return false;
		}


		static app::Vector3 SetTargetPosition(app::Vector3 targetpos, app::Transform* activeTransform)
		{
			auto& Engine = cheat::Engine::getInstance();
			if (Engine.f_forward.IsDown())
				targetpos = targetpos - app::Transform_get_forward(activeTransform) * Engine.f_moveSpeed.getValue();
			if (Engine.f_backward.IsDown())
				targetpos = targetpos + app::Transform_get_forward(activeTransform) * Engine.f_moveSpeed.getValue();
			if (Engine.f_left.IsDown())
				targetpos = targetpos + app::Transform_get_right(activeTransform) * Engine.f_moveSpeed.getValue();
			if (Engine.f_right.IsDown())
				targetpos = targetpos - app::Transform_get_right(activeTransform) * Engine.f_moveSpeed.getValue();
			if (Engine.f_up.IsDown())
				targetpos = targetpos - app::Transform_get_up(activeTransform) * Engine.f_moveSpeed.getValue();
			if (Engine.f_down.IsDown())
				targetpos = targetpos + app::Transform_get_up(activeTransform) * Engine.f_moveSpeed.getValue();
			return targetpos;
		}

		// class Rotation {

		//public:
		//	float pitch, yaw, roll;

		//	void InitializeFromTransform(app::Transform* Transform)
		//	{
		//		auto Transform_eulerAngles = app::Transform_get_eulerAngles(Transform);
		//		pitch = Transform_eulerAngles.x;
		//		yaw = Transform_eulerAngles.y;
		//		roll = Transform_eulerAngles.z;
		//	}

		//	void LerpTowards(Rotation target, float lookRotationLerpPct, float rollRotationLerpPct)
		//	{
		//		yaw = app::Mathf_Lerp(yaw, target.yaw, lookRotationLerpPct);
		//		pitch = app::Mathf_Lerp(pitch, target.pitch, lookRotationLerpPct);
		//		roll = app::Mathf_Lerp(roll, target.roll, rollRotationLerpPct);
		//	}

		//	void SetEulerAngles(app::Transform* t)
		//	{
		//		app::Transform_set_eulerAngles(t, app::Vector3{ pitch, yaw, roll });
		//	}
		//};
	};




}//namespacecheat