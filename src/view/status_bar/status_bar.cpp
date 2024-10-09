#include "status_bar.h"

// TODO status bar: what do we even wanna show?
StatusBar::StatusBar(wxWindow* parent) : wxStatusBar(parent) {
    m_elements["Total Tasks"] = "13";
    m_elements["Uncompleted Tasks"] = "2";
    m_elements["Completed Tasks"] = "5";

    std::string status_text = CreateStatusText(m_elements);

    SetStatusText(status_text, 0);
}

std::string StatusBar::CreateStatusText(const std::map<std::string, std::string>& elements) {
    std::string status_text = "   ";
    for (auto it = elements.begin(); it != elements.end(); ++it) {
        status_text += it->first + ": " + it->second;
        if (std::next(it) != elements.end()) {
            status_text += "  |  ";
        }
    }
    return status_text;
}

void StatusBar::SetElement(std::string key, std::string value) { m_elements[key] = value; }

void StatusBar::Update() {
    std::string status_text = CreateStatusText(m_elements);
    SetStatusText(status_text, 0);
}