#pragma once
namespace cheat {

	class EngineUtils {//SHOW LOG

	public:


		static std::string GetName(app::GameObject* GameObject)
		{
			auto Object_1 = reinterpret_cast<app::Object_1*>(GameObject);
			if (Object_1 != nullptr) {
				auto name = app::Object_1_get_name(Object_1);
				//LOG_DEBUG("Engine::GetName:  %s ", name);
				return il2cppi_to_string(name);
			}
			else {
				LOG_WARNING("Engine::GetName: nullptr ");
				std::string null = "Null";
				return null;
			}
		}
		static app::GameObject* FindGameObject(const char* objname)
		{
			auto obj = app::GameObject_Find(string_to_il2cppi(objname));
			if (obj == nullptr)
			{
				LOG_WARNING("Engine::FindGameObject  %s  not found", objname);
				return nullptr;
			}
			else
			{
				LOG_DEBUG("Engine::FindGameObject %s:%p found", objname, obj);
				return obj;
			}
		}
		static app::Transform* GetTransform(app::GameObject* __this)
		{
			if (__this != nullptr)
			{
				auto transform = app::GameObject_get_transform(__this);
				//LOG_DEBUG("Engine::GetTransform:  %p ", transform);
				return transform;
			}
			else
			{
				LOG_WARNING("Engine::GetTransform:  Not found");
				return nullptr;
			}
		}
		static app::Vector3 GetPosition(app::Transform* __this)
		{
			if (__this != nullptr)
			{
				auto pos = app::Transform_get_position(__this);
				//LOG_DEBUG("Engine::GetPosition:  X:%f Y:%f Z:%f ", pos.x, pos.y, pos.z);
				return pos;
			}
			else
			{
				LOG_WARNING("Engine::GetPosition:  Not found");
				return { 0,0,0 };
			}
		}
		static app::Vector3 GetLocalPosition(app::Transform* __this)
		{
			if (__this != nullptr)
			{
				auto pos = app::Transform_get_localPosition(__this);
				//LOG_DEBUG("Engine::GetlocalPosition:  X:%f Y:%f Z:%f ", pos.x, pos.y, pos.z);
				return pos;
			}
			else
			{
				LOG_WARNING("Engine::GetPosition:  Not found");
				return { 0,0,0 };
			}
		}
		static app::Quaternion GetRotation(app::Transform* __this)
		{
			if (__this != nullptr)
			{
				auto rot = app::Transform_get_rotation(__this);
				//LOG_DEBUG("Engine::GetRotation  X:%f Y:%f Z:%f W:%f ", rot.x, rot.y, rot.z, rot.w);
				return rot;
			}
			else
			{
				LOG_WARNING("Engine::GetRotation:  Not found");
				return { 0,0,0,0 };
			}
		}
		static app::Quaternion GetLocalRotation(app::Transform* __this)
		{
			if (__this != nullptr)
			{
				auto rot = app::Transform_get_localRotation(__this);
				//LOG_DEBUG("Engine::GetlocalRotation  X:%f Y:%f Z:%f W:%f ", rot.x, rot.y, rot.z, rot.w);
				return rot;
			}
			else
			{
				LOG_WARNING("Engine::GetlocalRotation:  Not found");
				return { 0,0,0,0 };
			}
		}
		static app::Vector3 GetLocalScale(app::Transform* __this)
		{
			if (__this != nullptr)
			{
				auto scale = app::Transform_get_localScale(__this);
				//LOG_DEBUG("Engine::GetlocalScale  X:%f Y:%f Z:%f ", scale.x, scale.y, scale.z);
				return scale;
			}
			else
			{
				LOG_WARNING("Engine::GetlocalScale:  Not found");
				return { 0,0,0 };
			}
		}

		static void SetPositon(app::Transform* __this, app::Vector3 pos)
		{
			if (__this != nullptr)
			{
				app::Transform_set_position(__this, pos);
				//LOG_DEBUG("Engine::SetPositon  X:%f Y:%f Z:%f ", pos.x, pos.y, pos.z);
			}
			else
			{
				LOG_WARNING("Engine::SetPositon:  nullptr!");
			}
		}
		static void SetLocalPositon(app::Transform* __this, app::Vector3 pos)
		{
			if (__this != nullptr)
			{
				app::Transform_set_localPosition(__this, pos);
				//LOG_DEBUG("Engine::setlocalPositon  X:%f Y:%f Z:%f ", pos.x, pos.y, pos.z);
			}
			else
			{
				LOG_WARNING("Engine::setlocalPositon:  nullptr!");
			}
		}
		static void SetRotation(app::Transform* __this, app::Quaternion rot)
		{
			if (__this != nullptr)
			{
				app::Transform_set_rotation(__this, rot);
				//LOG_DEBUG("Engine::SetRotation  X:%f Y:%f Z:%f W:%f ", rot.x, rot.y, rot.z, rot.w);
			}
			else
			{
				LOG_WARNING("Engine::SetRotation:  nullptr!");
			}
		}
		static void SeteulerAngles(app::Transform* __this, app::Vector3 eulerAngles)
		{
			if (__this != nullptr)
			{
				app::Transform_set_eulerAngles(__this, eulerAngles);
				//LOG_DEBUG("Engine::seteulerAngles  X:%f Y:%f Z:%f ", rot.x, rot.y, rot.z);
			}
			else
			{
				LOG_WARNING("Engine::seteulerAngles:  nullptr!");
			}
		}
		static void SetLocaleulerAngles(app::Transform* __this, app::Vector3 eulerAngles)
		{
			if (__this != nullptr)
			{
				app::Transform_set_localeulerAngles(__this, eulerAngles);
				//LOG_DEBUG("Engine::setlocaleulerAngles  X:%f Y:%f Z:%f ", rot.x, rot.y, rot.z);
			}
			else
			{
				LOG_WARNING("Engine::setlocaleulerAngles:  nullptr!");
			}
		}
		static void SetLocalRotation(app::Transform* __this, app::Quaternion rot)
		{
			if (__this != nullptr)
			{
				app::Transform_set_localRotation(__this, rot);
				//LOG_DEBUG("Engine::SetlocalRotation  X:%f Y:%f Z:%f W:%f ", rot.x, rot.y, rot.z, rot.w);
			}
			else
			{
				LOG_WARNING("Engine::SetlocalRotation:  nullptr!");
			}
		}
		static  app::Vector3 GeteulerAngles(app::Transform* __this)
		{
			if (__this != nullptr)
			{
				auto rot = app::Transform_get_eulerAngles(__this);
				//LOG_DEBUG("Engine::GeteulerAngle  X:%f Y:%f Z:%f ", rot.x, rot.y, rot.z);
				return rot;
			}
			else
			{
				LOG_WARNING("Engine::GeteulerAngle:  nullptr!");
				return { 0,0,0 };
			}
		}
		static  app::Vector3 GetLocaleulerAngles(app::Transform* __this)
		{
			if (__this != nullptr)
			{
				auto rot = app::Transform_get_localeulerAngles(__this);
				//LOG_DEBUG("Engine::GetLocaleulerAngle  X:%f Y:%f Z:%f ", rot.x, rot.y, rot.z);
				return rot;
			}
			else
			{
				LOG_WARNING("Engine::GetLocaleulerAngle:  nullptr!");
				return { 0,0,0 };
			}
		}
		static void SetScale(app::Transform* __this, app::Vector3 scale)
		{
			if (__this != nullptr)
			{
				app::Transform_set_localScale(__this, scale);
				//LOG_DEBUG("Engine::SetScale  X:%f Y:%f Z:%f ", scale.x, scale.y, scale.z);
			}
			else
			{
				LOG_WARNING("Engine::SetScale:  nullptr!  ");
			}
		}
		static bool GetActive(app::GameObject* __this)
		{
			if (__this != nullptr)
			{
				auto active = app::GameObject_get_active(__this);
				//LOG_DEBUG("Engine::GetActive:  %d ", active);
				return active;
			}
			else
			{
				LOG_WARNING("Engine::GetActive:  nullptr");
				return false;
			}
		}
		//static app::GameObject* Instantiate1(app::Object_1* original, app::Vector3 position, app::Quaternion rotation)
		//{
		//	if (original != nullptr)
		//	{
		//		auto out = app::Object_1_Instantiate_1(original, position, rotation);
		//		auto outgobj = reinterpret_cast<app::GameObject*>(out);
		//		LOG_DEBUG("Engine::Instantiate: %s %p ", app::Object_1_get_name(out), out);
		//		return outgobj;
		//	}
		//	else
		//	{
		//		LOG_WARNING("Engine::Instantiate:  nullptr");
		//		return nullptr;
		//	}

		//}
		//static app::Vector3 GetmyPos()
		//{
		//	app::Vector3 mypos = { 0,0,0 };			
		//	mypos = app::WorldShiftManager_GetRelativePosition(app::ActorUtils_GetAvatarPos());
		//	return mypos;		
		//}
		static void Transform_set_parent(app::Transform* __this, app::Transform* value)
		{
			if (__this != nullptr && value != nullptr)
			{
				app::Transform_set_parent(__this, value);
				LOG_DEBUG("Engine::Transform_set_parent:  %p->%p", value, __this);
			}
			else
			{
				LOG_WARNING("Engine::Transform_set_parent:  nullptr");
			}
		}
		//static app::Texture2D* LoadTextureFromFile(std::string path)
		//{
		//	auto data = app::File_ReadAllBytes(string_to_il2cppi(path)); // i think it's easier and better way to read data from file
		//	if (data == nullptr)
		//	{
		//		LOG_WARNING("Failed to read file '%s'", path.c_str());
		//		return nullptr;
		//	}

		//	//auto texture2d = reinterpret_cast<app::Texture2D*>(il2cpp_object_new(reinterpret_cast<app::Il2CppClass*>(*app::Texture2D__TypeInfo)));
		//	//if (texture2d == nullptr)
		//	//{
		//	//	LOG_WARNING("Failed to get default texture for file '%s'", path.c_str());
		//	//	return nullptr;
		//	//}

		//	app::Texture2D* texture2d = nullptr;

		//	app::Texture2D_ctor(texture2d, 2, 2);

		//	if (!app::ImageConversion_LoadImage(texture2d, data))
		//	{
		//		LOG_WARNING("Failed to load image from file '%s'", path.c_str());
		//		return nullptr;
		//	}

		//	return texture2d;
		//}
		//std::vector<app::GameObject*>, GetRootGameObjects, (app::Scene* scene));
		//static app::GameObject__Array* GetRootGObjs(void* scene)
		//{
		//	if (scene != nullptr)
		//	{
		//		auto out = app::GetRootGameObjects(scene);				
		//		//LOG_DEBUG("Engine::GetRootGObjs: counts:%d", out->vector.size());
		//		return out;
		//	}
		//	else
		//	{
		//		LOG_ERROR("Engine::GetRootGObjs: nullptr");
		//		return nullptr;
		//	}	
		//}

		static app::Text* GetText(app::GameObject* __this)
		{
			if (__this != nullptr)
			{
				auto text = app::GameObject_GetComponentByName(__this, string_to_il2cppi("Text"));
				LOG_DEBUG("Engine::GetText:  %p ", text);
				return reinterpret_cast<app::Text*>(text);
			}
			else
			{
				LOG_WARNING("Engine::GetText:  nullptr");
				return nullptr;
			}
		}
		//static std::string GetTextString(app::Text* __this)
		//{
		//	if (__this != nullptr)
		//	{
		//		auto text = app::Text_get_text(__this);
		//		//LOG_DEBUG("Engine::GetTextString:  %s ", il2cppi_to_string(text));
		//		return il2cppi_to_string(text);
		//	}
		//	else
		//	{
		//		LOG_WARNING("Engine::GetTextString:  nullptr");
		//		return "";
		//	}
		//}

		static void SetTextString(app::Text* __this, std::string text)
		{
			if (__this != nullptr)
			{
				app::Text_set_text(__this, string_to_il2cppi(text));
				LOG_DEBUG("Engine::SetTextString:  %s ", text);
			}
			else
			{
				LOG_WARNING("Engine::SetTextString:  nullptr");
			}
		}
		//static void SetTextAlignment(app::Text* __this, app::TextAnchor__Enum alignment)
		//{
		//	if (__this != nullptr)
		//	{
		//		app::Text_set_alignment(__this, alignment);
		//		//LOG_DEBUG("Engine::SetTextAlignment:  %d ", alignment);
		//	}
		//	else
		//	{
		//		LOG_WARNING("Engine::SetTextAlignment:  nullptr");
		//	}
		//}
		//static void SetFontSize(app::Text* __this, int size)
		//{
		//	if (__this != nullptr)
		//	{
		//		app::Text_set_fontSize(__this, size);
		//		//LOG_DEBUG("Engine::SetFontSize:  %d ", size);
		//	}
		//	else
		//	{
		//		LOG_WARNING("Engine::SetFontSize:  nullptr");
		//	}
		//}


	};//class

}// namespacecheat