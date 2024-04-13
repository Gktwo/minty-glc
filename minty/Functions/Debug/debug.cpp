#include "Debug.h"

namespace cheat {
	static void BattleLogic_BattleMatch__Update_HookDebug(app::BattleLogic_BattleMatch_o* __this);

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

		//if (f_time.getValue()) {
		//	ImGui::Indent();
		//	ImGui::Unindent();
		//}
		//if (f_Enabled.getValue()) {
		//	ImGui::Indent();
		//	f_Hotkey.Draw();
		//	ImGui::Unindent();
		//}

		if (f_Resolution.IsPressed())
			SetResolution();

		//if (f_WipeEnemies.getValue()) {
		//	ImGui::Indent();
		//	ImGui::Text("Wipe:");
		//	ImGui::SameLine();
		//	f_Wipe.Draw();
		//	ImGui::Unindent();
		//}



	}




	void Debug::Outer() {
		//if (f_Hotkey.IsPressed())
		//	f_Enabled.setValue(!f_Enabled.getValue());


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
			//The game will get stuck,How to refresh?
		}

		LOG_INFO("SetResolution to %d x %d, fullscreen: %s", f_Resolutionwidth.getValue(), f_Resolutionheight.getValue(), f_Resolutionfullscreen.getValue() ? "true" : "false");
	}

}
