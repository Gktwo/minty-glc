#include "Translations.h"

#include "../functions/Settings/Settings.h"

#include <optional>
#include <charconv>

std::string result;
static bool ifParse;
int LangTR = 0;

std::string LoadResourceString(int resourceId, LPCSTR resourceType) {
	HMODULE handle = GetModuleHandle("minty.dll");
	HRSRC resource = FindResource(handle, MAKEINTRESOURCE(resourceId), resourceType);
	if (!resource) {
		LOG_ERROR("Resource not found.");
		return "";
	}

	HGLOBAL loadedResource = LoadResource(handle, resource);
	if (!loadedResource) {
		LOG_ERROR("Failed to load resource.");
		return "";
	}

	DWORD size = SizeofResource(handle, resource);
	LPCSTR data = static_cast<LPCSTR>(LockResource(loadedResource));

	if (size == 0 || !data) {
		LOG_ERROR("Resource data is invalid.");
		return "";
	}

	return std::string(data, size);
}

auto& settings = cheat::Settings::getInstance();

std::optional<std::string> safeGet(nlohmann::json& json, const std::string& key, const std::string& lang) {
	if (json.contains(lang) && json[lang].is_object() && json[lang].contains(key))
		return json[lang][key].get<std::string>();
	return key;
}

std::u8string u8result;

enum class Lang {
	EN,
	RU,
	ID,
	RO
};

const char* _(const char* code) {
	static nlohmann::json trJson;

	if (result.empty()) {
		result = LoadResourceString(R_LANGUAGES, RT_RCDATA);

		if (result.empty())
			return code;

		try {
			trJson = nlohmann::json::parse(result);
		}
		catch (nlohmann::json::parse_error& e) {
			LOG_ERROR("JSON parsing error: %s", e.what());
			return code;
		}
	}

	std::string retStr = code;
	int languageValue = settings.f_Language.getValue();
	std::optional<std::string> ret = safeGet(trJson, code, magic_enum::enum_name(static_cast<Lang>(languageValue)).data());

	if (ret.has_value())
		retStr = ret.value();

	u8result = std::u8string(retStr.begin(), retStr.end());
	return reinterpret_cast<const char*>(u8result.c_str());
}
