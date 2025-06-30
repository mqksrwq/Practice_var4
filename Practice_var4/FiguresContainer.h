#pragma once
#include "Figure.h"
#include <vcclr.h>

namespace ShapesApp {
    public ref class FiguresContainer {
    private:
        System::Collections::Generic::List<Figure^>^ figures;

    public:
        FiguresContainer() {
            figures = gcnew System::Collections::Generic::List<Figure^>();
        }

        property System::Collections::Generic::List<Figure^>^ Figures {
            System::Collections::Generic::List<Figure^>^ get() { return figures; }
        }

        void Add(Figure^ figure) {
            figures->Add(figure);
        }

        void RemoveAt(int index) {
            if (index >= 0 && index < figures->Count)
                figures->RemoveAt(index);
        }

        void ToggleVisibility(int index) {
            if (index >= 0 && index < figures->Count) {
                figures[index]->Visible = !figures[index]->Visible;
            }
        }

        void DrawAll(Graphics^ g) {
            for each (Figure ^ fig in figures) {
                if (fig->Visible)
                    fig->Draw(g);
            }
        }
    };
}