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
    Awesome,
};

class GuiStyle {
   public:
    void load();
    void loadFonts();
    void pushSelectableMenu();
    void popSelectableMenu();
    void pushWindowCategoryList();
    void popWindowCategoryList();
    void pushWindowTodoList();
    void popWindowTodoList();
    void pushWindowAddTodo();
    void popWindowAddTodo();
    void pushInputForm();
    void popInputForm();
    void pushInputText();
    void popInputText();
    void pushButton();
    void popButton();
    void pushComboBox();
    void popComboBox();
    void pushFont(FontType type);
    void popFont();

   private:
    std::map<FontType, ImFont*> fonts;
};

}  // namespace TodoApp