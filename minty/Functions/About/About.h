#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
	class About : public Function {
	public:
		std::string mVersion;
		void GUI() override;

		std::string getModule() override;

		About();

		static About& getInstance();
	};
}
