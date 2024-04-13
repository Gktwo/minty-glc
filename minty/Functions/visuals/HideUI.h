#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class HideUI : public Function {
	public:
	    ConfigField<bool> f_Enabled;
		ConfigField<bool> f_ui_1;
		ConfigField<bool> f_ui_2;
		ConfigField<bool> f_ui_3;
		Hotkey f_Hotkey;

		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static HideUI& getInstance();

		HideUI();
	};
}
