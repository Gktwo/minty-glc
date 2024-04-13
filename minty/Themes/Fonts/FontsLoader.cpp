#include "FontsLoader.h"


static const ImWchar ranges[] =
{
0x0020, 0x00FF, // Basic Latin + Latin Supplement
0x2000, 0x206F, // General Punctuation
0x3000, 0x30FF, // CJK Symbols and Punctuations, Hiragana, Katakana
0x31F0, 0x31FF, // Katakana Phonetic Extensions
0xFF00, 0xFFEF, // Half-width characters
0xFFFD, 0xFFFD, // Invalid
0x4e00, 0x9FAF, // CJK Ideograms
0x3131, 0x3163, // Korean alphabets
0xAC00, 0xD7A3, // Korean characters
0x3040, 0x309F, // Hiragana
0x30A0, 0x30FF, // Katakana
0x0400, 0x04FF, // Cyrillic
0x1E00, 0x1EFF, // Latin Extended Additional
0,
};


//需要加一个框架
//包含字体文件+编码范围

bool LoadFontFromResources(ImFontConfig font_cfg, const wchar_t* fontName, float fontSize) {
    HMODULE hModuleF = GetModuleHandle("minty.dll");
    //HMODULE hModuleF;
    // Find the resource handle within the DLL
    HRSRC hResource = FindResource(hModuleF, (LPCSTR)fontName, RT_RCDATA);
    if (!hResource) {
        // Resource not found
        return false;
    }

    // Load the resource data
    HGLOBAL hMemory = LoadResource(hModuleF, hResource);
    if (!hMemory) {
        // Failed to load resource
        return false;
    }

    // Get the resource data pointer and size
    LPVOID pData = LockResource(hMemory);
    DWORD dataSize = SizeofResource(hModuleF, hResource);

    // Create a memory buffer for the font data
    font_cfg.FontDataOwnedByAtlas = false; // We'll keep the memory until ImGui is shut down
    //const ImWchar* glyph_ranges = ImGui::GetIO().Fonts->GetGlyphRangesChineseFull();
    ImGui::GetIO().Fonts->AddFontFromMemoryTTF(pData, dataSize, fontSize, &font_cfg, ranges);

    // Clean up the resource handles
    UnlockResource(hMemory);
    FreeResource(hMemory);
    return true;
}
