#pragma once
#include <map>

struct ImFont;

namespace TodoApp {

enum FontType {
    Normal,
    Bold,
    Header1,
    Header2,
    Header3,
};

class GuiStyle {
   public:
    void load();
    void loadFonts();
    void pushFont(FontType type);
    void popFont();

   private:
    std::map<FontType, ImFont*> fonts;
};

}  // namespace TodoApp