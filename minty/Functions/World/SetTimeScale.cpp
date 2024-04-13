#include "SetTimeScale.h"

namespace cheat {
	static void Global_Update_timescale_Hook(app::EventSystem* __this, MethodInfo* method);

	SetTimeScale::SetTimeScale() {
		f_Enabled = config::getValue("functions:SetTimeScale", "enabled", false);
		f_Hotkey = Hotkey("functions:SetTimeScale");
		f_Speed = config::getValue("functions:SetTimeScale", "speed value", 5.0f);
		HookManager::install(app::EventSystem_Update, Global_Update_timescale_Hook);

	}

	SetTimeScale& SetTimeScale::getInstance() {
		static SetTimeScale instance;
		return instance;
	}

	void SetTimeScale::GUI() {
		ImGui::SeparatorText(_("Game Speed"));
		ConfigCheckbox(_("Game Speed"), f_Enabled, _("Change game speed ."));
		ImGui::SameLine();
		f_Hotkey.Draw();

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			ConfigSliderFloat(_("speed value"), f_Speed, 0.1f, 20.0f, _("Change the value of game speed"));
			ImGui::Unindent();
		}
	}

	void SetTimeScale::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void SetTimeScale::Status() {
		if (f_Enabled.getValue())
			ImGui::Text("SetTimeScale | %f", f_Speed.getValue());
	}

	std::string SetTimeScale::getModule() {
		return _("World");
	}




	void Global_Update_timescale_Hook(app::EventSystem* __this, MethodInfo* method) {
		auto& SetTimeScale = SetTimeScale::getInstance();


		app::Time_set_timeScale(SetTimeScale.f_Enabled.getValue() ? SetTimeScale.f_Speed.getValue() : 1.0f);

		return CALL_ORIGIN(Global_Update_timescale_Hook, __this, method);
	}

}
