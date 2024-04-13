#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class Browser : public Function {
	public:


		ConfigField <std::string> f_URL;
		Hotkey f_Hotkey;

		ConfigField<float> f_planeWidth;
		ConfigField<float> f_planeHeight;
		ConfigField<int> f_Resolutionwidth;
		ConfigField<int> f_Resolutionheight;
		void GUI() override;
		void Outer() override;
		void Status() override;

		std::string getModule() override;

		static Browser& getInstance();

		void SetBrowser();
		Browser();
	};
}
