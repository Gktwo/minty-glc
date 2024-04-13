#include "LuaConsole.h"

namespace cheat {
	TextEditor editor;

	LuaConsole::LuaConsole() {
		editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
		editor.SetPalette(TextEditor::GetDarkPalette());

		editor.SetTabSize(4);
		editor.SetShowWhitespaces(false);
		editor.SetColorizerEnable(true);
	}

	void LuaConsole::GUI() {
		if (ImGui::Button(_("EXECUTE_TITLE")) || f_Hotkey.IsPressed())
			luahookfunc(editor.GetText().c_str());

		ImGui::SameLine();
		f_Hotkey.Draw();
		editor.Render(_("LUA_CONSOLE_TITLE"));
	}

	void LuaConsole::Status() {

	}

	void LuaConsole::Outer() {
		if (f_Hotkey.IsPressed())
			luahookfunc(editor.GetText().c_str());
	}

	LuaConsole& LuaConsole::getInstance() {
		static LuaConsole instance;
		return instance;
	}

	std::string LuaConsole::getModule() {
		return _("MODULE_LUA");
	}
}
