#pragma once

#include <wx/wx.h>

#include <map>


class StatusBar : public wxStatusBar {
   public:
    StatusBar(wxWindow* parent);

    void SetElement(std::string key, std::string value);
    void Update();

   private:
    std::string CreateStatusText(const std::map<std::string, std::string>& elements);

    std::map<std::string, std::string> m_elements;
};