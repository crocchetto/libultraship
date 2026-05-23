#include "ship/window/gui/ComponentHierarchyWindow.h"

#include "ship/Context.h"
#include "ship/TickableComponent.h"

namespace Ship {

ComponentHierarchyWindow::ComponentHierarchyWindow(std::shared_ptr<ConsoleVariable> consoleVariable,
                                                   std::shared_ptr<Window> window, std::shared_ptr<Context> context,
                                                   const std::string& visibilityCvar, const std::string& name)
    : GuiWindow(std::move(consoleVariable), std::move(window), visibilityCvar, false, name, ImVec2{ 600, 400 },
                ImGuiWindowFlags_None),
      mContext(std::move(context)) {
}

ComponentHierarchyWindow::~ComponentHierarchyWindow() {
}

void ComponentHierarchyWindow::DrawElement() {
    if (!mContext) {
        ImGui::TextUnformatted("No context available.");
        return;
    }

    if (ImGui::BeginChild("##component_tree", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), true)) {
        ImGui::SeparatorText("Component Hierarchy");
        std::string tree = mContext->ToTreeString();
        ImGui::TextUnformatted(tree.c_str());

        ImGui::Spacing();
        ImGui::SeparatorText("Tickable Components");
        for (const auto& tickable : *mContext->GetTickableComponents().Get()) {
            ImGui::BulletText("%s", tickable->GetName().c_str());
        }
    }
    ImGui::EndChild();
}

} // namespace Ship
