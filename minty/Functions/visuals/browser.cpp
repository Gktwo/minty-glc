#include "browser.h"

namespace cheat {
	app::GameObject* planeObject = nullptr;
	app::Component* BrowserComponents = nullptr;

	Browser::Browser() {

		f_Hotkey = Hotkey("functions:Browser");
		f_planeWidth = config::getValue("functions:Browser", "planeWidth", 0.16f);
		f_planeHeight = config::getValue("functions:Browser", "planeHeight", 0.09f);
		f_Resolutionwidth = config::getValue("functions:Browser", "Resolutionwidth", 1920);
		f_Resolutionheight = config::getValue("functions:Browser", "Resolutionheight", 1080);
		std::string  url = "https://genshin.hoyoverse.com/en";
		f_URL = config::getValue("functions:Browser", "URL", url);
	}

	Browser& Browser::getInstance() {
		static Browser instance;
		return instance;
	}

	void Browser::GUI() {
		ImGui::SeparatorText(_("Browser"));
		if (ImGui::Button(_("Set a browser")))
			SetBrowser();
		ImGui::SameLine();
		HelpMarker(_("Set a browser in scene when you press the Button"));
		ImGui::SameLine();
		f_Hotkey.Draw();
		ImGui::TextWrapped("use the set a browser feature in conjunction with the free function for an optimal experience");
		ConfigInputText(_("URL"), f_URL, _("Browser URL"));
		ConfigDragFloat(_("Plane width"), f_planeWidth, 0.01f, 0.01f, 20.0f, _("Change the plane width"));
		ConfigDragFloat(_("Plane height"), f_planeHeight, 0.01f, 0.01f, 20.0f, _("Change the plane height"));
		ConfigInputInt(_("Resolution width"), f_Resolutionwidth, _("Browser Resolution width"));
		ConfigInputInt(_("Resolution height"), f_Resolutionheight, _("Browser Resolution width"));

	}

	void Browser::Outer() {
		if (f_Hotkey.IsPressed())
			SetBrowser();

	}

	void Browser::Status() {

	}

	std::string Browser::getModule() {
		return _("Visuals");
	}



	void Browser::SetBrowser() {
		//auto currentTime = util::GetCurrentTimeMillisec();
		//if (currentTime < nextUpdate)
		//	return;

		auto entityRoot = app::GameObject_Find(string_to_il2cppi("MapRoot"));
		if (!app::GameObject_get_active(entityRoot))
		{
			LOG_DEBUG("entityRoot not found");
			return;
		}
		else
			LOG_DEBUG("entityRoot: %p found", entityRoot);

		if (planeObject == nullptr)
		{
			auto PrimitiveType = app::PrimitiveType__Enum::Plane;
			planeObject = app::GameObject_CreatePrimitive(PrimitiveType);
			app::Transform* planeObject_Transform = app::GameObject_get_transform(planeObject);
			app::Quaternion planeObject_Transform_Quaternion = { 0.5f, 0.5f, -0.5f, 0.5f };

			app::Vector3 getPos = { 10.0f,5.0f ,1.0f };
			app::Vector3 relativePos = getPos;

			app::Vector3 planeObject_Transform_Vector3 = getPos;

			app::Vector3 planeObject_Transform_Scale = { f_planeWidth.getValue(), 1.0f, f_planeHeight.getValue() };

			app::Transform_set_localPosition(planeObject_Transform, planeObject_Transform_Vector3);
			app::Transform_set_localScale(planeObject_Transform, planeObject_Transform_Scale);
			app::Transform_set_localRotation(planeObject_Transform, planeObject_Transform_Quaternion);
			LOG_DEBUG("set planeObj: %p  ", planeObject_Transform);
		}

		if (planeObject != nullptr)
		{
			if (BrowserComponents == nullptr)
			{
				std::string custom_url = f_URL.getValue();
				if (custom_url.empty())
					std::string custom_url = "https://genshin.hoyoverse.com/en";

				Sleep(3);
				BrowserComponents = app::GameObject_AddComponentInternal(planeObject, string_to_il2cppi("Browser"));
				auto Browser = reinterpret_cast<app::ZenFulcrum_EmbeddedBrowser_Browser*>(BrowserComponents);
				Browser->fields._url = string_to_il2cppi(custom_url);
				Browser->fields._width = f_Resolutionwidth.getValue();
				Browser->fields._height = f_Resolutionheight.getValue();
				//reinterpret_cast<app::ZenFulcrum_EmbeddedBrowser_Browser*>(BrowserComponents)->fields.forceNextRender = true;
				//reinterpret_cast<app::ZenFulcrum_EmbeddedBrowser_Browser*>(BrowserComponents)->fields._EnableInput_k__BackingField = true;
				LOG_DEBUG("set Browser: %p  ", planeObject);
			}
			else
			{
				// Set the scale at update interval for dynamic scaling instead of re-initialize the plane again
                //以更新间隔设置比例以进行动态缩放，而不是再次初始化平面
				app::Transform* planeobject_transform = app::GameObject_get_transform(planeObject);
				app::Vector3 planeobject_transform_scale = { f_planeWidth.getValue(), 1.0f, f_planeHeight.getValue() };
				app::Transform_set_localScale(planeobject_transform, planeobject_transform_scale);

				LOG_DEBUG("Browser refresh");
			}

		}
		else
		{
			LOG_DEBUG("3 ");
			if (planeObject != nullptr && BrowserComponents != nullptr)
			{
				LOG_DEBUG("4 ");
				app::Object_DestroyImmediate_1(reinterpret_cast<app::Object*>(planeObject));
				app::Object_DestroyImmediate_1(reinterpret_cast<app::Object*>(BrowserComponents));
				planeObject = nullptr;
				BrowserComponents = nullptr;
				LOG_DEBUG(" Browser Destroyed  ");
			}
		}

		//nextUpdate = currentTime + (int)f_DelayUpdate;
		LOG_DEBUG("5 ");
	}

}// namespace cheat




