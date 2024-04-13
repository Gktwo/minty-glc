#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
    class BattleMatch : public Function {
    public:
	ConfigField<bool> f_Speed;
	ConfigField<float> f_Speedvalue;

	Hotkey f_Hotkey;

	void GUI() override;
	void Outer() override;
	void Status() override;

	std::string getModule() override;

	static BattleMatch& getInstance();

	BattleMatch();
    };
}
#pragma once
