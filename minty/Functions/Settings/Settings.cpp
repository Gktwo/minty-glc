#include "Settings.h"

namespace cheat {
	static void DrawFPS();

	Settings::Settings() {
		//f_DisableProtection = config::getValue("functions:Settings", "disableProtection", true);
		//f_DisableLog = config::getValue("functions:Settings", "disableLog", true);
		//f_SpoofACResult = config::getValue("functions:Settings", "spoofACResult", true);
		//f_UseSignature = config::getValue("functions:Settings", "useSignature", true);
		f_ShowFps = config::getValue("functions:Settings", "showFps", true);
		f_ShowRpc = config::getValue("functions:Settings", "showRpc", true);
		f_ShowConsole = config::getValue("functions:Settings", "showConsole", true);
		f_InitDelay = config::getValue("functions:Settings", "initDelay", 15000);
		f_Language = config::getValue("functions:Settings", "language", 0);
		//f_MobileMode = config::getValue("functions:Settings", "mobileMode", false);
		f_StartupArguments = config::getValue<std::string>("functions:Settings", "startupArguments", "");
		f_AnimationDuration = config::getValue("functions:Settings", "animationDuration", 0.2f);
		f_Status = config::getValue("functions:Settings", "status", true);
		f_StatusMove = config::getValue("functions:Settings", "statusMove", true);
		f_ShowMenu = config::getValue("functions:Settings", "showMenu", true);

		f_Hotkey = Hotkey("functions:Settings:Menu", VK_F12);
		f_HotkeyConsole = Hotkey("functions:Settings:Console", VK_HOME);
	}

	Settings& Settings::getInstance() {
		static Settings instance;
		return instance;
	}

	const char* languages[] = { "English", "Russian", "Chinese", "Indonesian" };

	void Settings::GUI() {
		//ImGui::SeparatorText(_("SETTINGS_LANGUAGE"));
		//ConfigComboLanguage(f_Language);

		ImGui::SeparatorText(_("SETTINGS_GENERAL"));

		f_Hotkey.Draw(_("MENU_HOTKEY_TITLE"));

		ConfigCheckbox(_("CONSOLE_HOTKEY_TITLE"), f_ShowConsole, _("CONSOLE_HOTKEY_DESCRIPTION"));

		if (f_Status.getValue()) {
			ImGui::Indent();
			f_HotkeyConsole.Draw();
			ImGui::Unindent();
		}

		//ConfigCheckbox(_("DISABLE_PROTECTION_TITLE"), f_DisableProtection, _("DISABLE_PROTECTION_DESCRIPTION"));
		//ConfigCheckbox(_("DISABLE_LOG_TITLE"), f_DisableLog, _("DISABLE_LOG_DESCRIPTION"));
		//ConfigCheckbox(_("DISABLE_SPOOF_ANTICHEAT_TITLE"), f_SpoofACResult, _("DISABLE_SPOOF_ANTICHEAT_DESCRIPTION"));
		//ConfigCheckbox(_("USE_FILE_SIGNATURE_TITLE"), f_UseSignature, _("USE_FILE_SIGNATURE_DESCRIPTION"));

		ConfigCheckbox(_("SHOW_STATUS_WINDOW_TITLE"), f_Status, _("SHOW_STATUS_WINDOW_DESCRIPTION"));

		if (f_Status.getValue()) {
			ImGui::Indent();
			ConfigCheckbox(_("MOVE_STATUS_TITLE"), f_StatusMove);
			ImGui::Unindent();
		}

		ConfigCheckbox(_("SHOW_FPS_TITLE"), f_ShowFps, _("SHOW_FPS_DESCRIPTION"));
		ConfigCheckbox(_("SHOW_RPC_TITLE"), f_ShowRpc, _("SHOW_RPC_DESCRIPTION"));

		ConfigSliderInt(_("INIT_DELAY_TITLE"), f_InitDelay, 0, 60000, _("INIT_DELAY_DESCRIPTION"));

		//ConfigCheckbox(_("MODILE_MODE_TITLE"), f_MobileMode, _("MODILE_MODE_DESCRIPTION"));

		ConfigInputText(_("STARTUP_ARGS_TITLE"), f_StartupArguments, _("STARTUP_ARGS_DESCRIPTION"));
		TextURL(_("LIST_UNITY_COMMAND_TITLE"), "https://docs.unity3d.com/Manual/PlayerCommandLineArguments.html", false, false);

		ImGui::SeparatorText(_("SETTINGS_THEME"));

		static int themeIndex = 1;

		if (ImGui::RadioButton(_("THEME_DARK_TITLE"), &themeIndex, 1))
			setTheme(1);

		if (ImGui::RadioButton(_("THEME_LIGHT_TITLE"), &themeIndex, 2))
			setTheme(2);

		ImGui::SeparatorText(_("SETTINGS_STYLE"));

		static int styleIndex = 1;

		if (ImGui::RadioButton(_("STYLE_COZY_TITLE"), &styleIndex, 1))
			setStyle(1);

		if (ImGui::RadioButton(_("STYLE_COZY_SQUARED_TITLE"), &styleIndex, 2))
			setStyle(2);

		ImGui::SeparatorText(_("SETTINGS_FONT"));

		static int fontIndex = 1;

		if (ImGui::RadioButton(_("FONT_NORMAL_TITLE"), &fontIndex, 1))
			setFont(1);

		if (ImGui::RadioButton(_("FONT_BOLD_TITLE"), &fontIndex, 2))
			setFont(2);

		ImGui::SeparatorText(_("SETTINGS_CUSTOMIZE"));
		ConfigSliderFloat(_("DURATION_ANIMATION_TITLE"), f_AnimationDuration, 0, 5.0f, _("DURATION_ANIMATION_DESCRIPTION"));
		ImGui::Checkbox(_("SHOW_STYLE_EDITOR_TITLE"), &show_style_editor);
	}

	void Settings::Outer() {
		if (f_Hotkey.IsPressed()) {
			f_ShowMenu.setValue(!f_ShowMenu.getValue());
			config::setValue("functions:Settings", "showMenu", f_ShowMenu.getValue());
		}

		if (f_HotkeyConsole.IsPressed())
			f_ShowConsole.setValue(!f_ShowConsole.getValue());

		if (f_ShowConsole.getValue())
			ShowWindow(GetConsoleWindow(), SW_SHOW);
		else
			ShowWindow(GetConsoleWindow(), SW_HIDE);

		if (f_ShowFps.getValue())
			DrawFPS();

		if (show_style_editor) {
			ImGui::Begin(_("STYLE_EDITOR_TITLE"), &show_style_editor);
			ImGui::ShowStyleEditor();
			ImGui::End();
		}
	}

	std::string Settings::getModule() {
		return _("Settings");
	}

	void DrawFPS() {
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus |
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;

		ImGui::Begin("##FPS", NULL, flags);
		ImGui::Text("%s: %.1f", _("FPS_TITLE"), ImGui::GetIO().Framerate);
		ImGui::End();
	}
}
