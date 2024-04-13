#include "HideUI.h"

namespace cheat {
	static void Global_Update2_Hook(app::UnityEngine_EventSystems_EventSystem_o* __this, app::MethodInfo* method);

	HideUI::HideUI() : Function() {
		f_Enabled = config::getValue("functions:HideUI", "enabled", false);
		f_ui_1 = config::getValue("functions:HideUI:ui_1", "enabled", false);
		f_ui_2 = config::getValue("functions:HideUI:ui_2", "enabled", false);
		f_ui_3 = config::getValue("functions:HideUI:ui_3", "enabled", false);
		f_Hotkey = Hotkey("functions:HideUI");

		HookManager::install(app::Global_Update, Global_Update2_Hook);
	}

	HideUI& HideUI::getInstance() {
		static HideUI instance;
		return instance;
	}

	void HideUI::GUI() {
		ImGui::SeparatorText(_("HideUI"));
		ConfigCheckbox(_("Hide UI"), f_Enabled, _("Hide in-game UI."));
		ImGui::SameLine();
		f_Hotkey.Draw();

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			ConfigCheckbox(_("GlobalMenu"), f_ui_1, _("Hide in-game UI."));
			ConfigCheckbox(_("GlobalHeader"), f_ui_2, _("Hide in-game UI."));
			ConfigCheckbox(_("HomeWindow"), f_ui_3, _("Hide in-game UI."));
			ImGui::Unindent();
		}
	}

	void HideUI::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void HideUI::Status() {
		if (f_Enabled.getValue())
			ImGui::Text("Hide UI");
	}

	std::string HideUI::getModule() {
		return _("Visuals");
	}

	app::GameObject* ui_1{};
	app::GameObject* ui_2{};
	app::GameObject* ui_3{};

	//GlobalMenu(Clone)
	//GlobalHeader(Clone)
	//HomeWindow(Clone)
	void HideeUI(app::GameObject*& ui, const std::string& name, bool isEnabled, bool isUIValue) {
		if (isEnabled && isUIValue) {
			if (ui == nullptr) {
				ui = app::GameObject_Find(string_to_il2cppi(name));
				if (ui == nullptr) {
					// Handle the case where the game object does not exist.
					// For example, you might want to log an error message.
					return;
				}
			}

			if (ui->fields._.m_CachedPtr != nullptr)
				app::GameObject_SetActive(ui, false);
		}
		else {
			if (ui != nullptr && ui->fields._.m_CachedPtr != nullptr) {
				app::GameObject_SetActive(ui, true);
				ui = nullptr;
			}
		}
	}

	void Global_Update2_Hook(app::UnityEngine_EventSystems_EventSystem_o* __this, app::MethodInfo* method) {
		auto& hideUI = HideUI::getInstance();

		HideeUI(ui_1, "/GlobalMenu(Clone)", hideUI.f_Enabled.getValue(), hideUI.f_ui_1.getValue());
		HideeUI(ui_2, "/GlobalHeader(Clone)", hideUI.f_Enabled.getValue(), hideUI.f_ui_2.getValue());
		HideeUI(ui_3, "/HomeWindow(Clone)", hideUI.f_Enabled.getValue(), hideUI.f_ui_3.getValue());


		CALL_ORIGIN(Global_Update2_Hook, __this, method);
	}
}
