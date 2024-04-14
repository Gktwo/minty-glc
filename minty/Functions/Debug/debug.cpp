#include "Debug.h"

namespace cheat {
	//static void BattleLogic_BattleMatch__Update_HookDebug(app::BattleLogic_BattleMatch_o* __this);

	Debug::Debug() {
		//f_Enabled = config::getValue("functions:Debug", "enabled", false);

		f_Resolution = Hotkey("functions:Debug:SetResolution");
		f_Resolutionwidth = config::getValue("functions:Settings:Resolution", "widthvalue", 1920);
		f_Resolutionheight = config::getValue("functions:Settings:Resolution", "heightvalue", 1080);
		f_Resolutionfullscreen = config::getValue("functions:Settings:Resolution", "fullscreenvalue", false);

	}


	Debug& Debug::getInstance() {
		static Debug instance;
		return instance;
	}

	void Debug::GUI() {
		ImGui::SeparatorText(_("Debug"));

		if (ImGui::Button("SetResolution"))
			SetResolution();
		ImGui::SameLine();
		f_Resolution.Draw();
		ConfigInputInt(_("Screen width"), f_Resolutionwidth, _("RESOLUTION_WIDTH_DESCRIPTION"));
		ConfigInputInt(_("Screen height"), f_Resolutionheight, _("RESOLUTION_HEIGHT_DESCRIPTION"));
		ConfigCheckbox(_("Fullscreen"), f_Resolutionfullscreen, _("Fullscreen"));

		//testdebugfunc
		if (ImGui::Button("find cam"))
		{
			auto maincam = app::Camera_get_main(nullptr);
			//auto currcam = app::Camera_get_current(nullptr);
			LOG_DEBUG("mainCam Component %p", maincam);
			auto maincamgobj = app::Component_get_gameObject(reinterpret_cast<app::Component_1*>(maincam));
			auto name = app::Object_get_name(reinterpret_cast<app::Object_1*>(maincamgobj));//Main Camera
			LOG_DEBUG("mainCam Gameobject:%s ,%p", il2cppi_to_string(name), maincamgobj);
			app::String* findname= string_to_il2cppi("Main Camera");
			auto findcam = app::GameObject_Find(findname);
			LOG_DEBUG("mainCam namefindtest:%p", findcam);
			auto maincamtr = app::GameObject_get_transform(maincamgobj);
			LOG_DEBUG("mainCam tranform:%p", maincamtr);
			auto CinemachineBrain = app::GameObject_GetComponentByName(maincamgobj, string_to_il2cppi("CinemachineBrain"));
			auto CinemachineExternalCamera =app::GameObject_GetComponentByName(maincamgobj, string_to_il2cppi("CinemachineExternalCamera"));
			LOG_DEBUG("mainCam CB:%p,CEC:%p", CinemachineBrain, CinemachineExternalCamera);
		}





	}




	void Debug::Outer() {
		//if (f_Hotkey.IsPressed())
		//	f_Enabled.setValue(!f_Enabled.getValue());
		if (f_Resolution.IsPressed())
			SetResolution();


	}



	void Debug::Status() {
		//if (f_Enabled.getValue())
		//	ImGui::Text(_("Debug"));
	}

	std::string Debug::getModule() {
		return _("Debug");
	}






	void Debug::SetResolution() {
		if (f_Resolutionwidth.getValue() != 0 && f_Resolutionheight.getValue() != 0)
		{
			app::Screen_SetResolution(f_Resolutionwidth.getValue(), f_Resolutionheight.getValue(), f_Resolutionfullscreen.getValue());
		
		}

		LOG_INFO("SetResolution to %d x %d, fullscreen: %s", f_Resolutionwidth.getValue(), f_Resolutionheight.getValue(), f_Resolutionfullscreen.getValue() ? "true" : "false");
	}

}
