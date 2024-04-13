#include "BattleMatch.h"

namespace cheat {
	static void BattleLogic_BattleMatch__Update_Hook1(app::BattleLogic_BattleMatch_o* __this);

	BattleMatch::BattleMatch() {
		f_Speed = config::getValue("functions:BattleMatchSpeed", "Speed", false);
		f_Hotkey = Hotkey("functions:BattleMatchSpeed");
		f_Speedvalue = config::getValue("functions:BattleMatchSpeed", "speed value", 5.0f);
		HookManager::install(app::BattleLogic_BattleMatch__Update, BattleLogic_BattleMatch__Update_Hook1);

	}

	BattleMatch& BattleMatch::getInstance() {
		static BattleMatch instance;
		return instance;
	}

	void BattleMatch::GUI() {
		ImGui::SeparatorText(_("BattleMatch"));
		ConfigCheckbox(_("BattleMatchSpeed"), f_Speed, _("Change BattleMatch speed ."));
		ImGui::SameLine();
		f_Hotkey.Draw();

		if (f_Speed.getValue()) {
			ImGui::Indent();
			ConfigSliderFloat(_("speed value"), f_Speedvalue, 0.1f, 20.0f, _("Change the value of BattleMatch Speed"));
			ImGui::Unindent();
		}
	}

	void BattleMatch::Outer() {
		if (f_Hotkey.IsPressed())
			f_Speed.setValue(!f_Speed.getValue());
	}

	void BattleMatch::Status() {
		if (f_Speed.getValue())
			ImGui::Text("BattleMatchSpeed | %f", f_Speedvalue.getValue());
	}

	std::string BattleMatch::getModule() {
		return _("World");
	}




	void BattleLogic_BattleMatch__Update_Hook1(app::BattleLogic_BattleMatch_o* __this) {
		auto& BattleMatch = BattleMatch::getInstance();


		app::Time_set_timeScale(BattleMatch.f_Speed.getValue() ? BattleMatch.f_Speedvalue.getValue() : 1.0f);

		return CALL_ORIGIN(BattleLogic_BattleMatch__Update_Hook1, __this);
	}

}
