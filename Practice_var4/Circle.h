#pragma once
#include "Figure.h"

namespace PracticeVar4 {
    public ref class Circle : public Figure {
    public:
        Circle(Point pos, int r, Color fill, Color border)
            : Figure(pos, r, fill, border) {
        }

        virtual void Draw(Graphics^ g) override {
            if (!visible) return;
            g->FillEllipse(gcnew SolidBrush(fillColor),
                position.X - radius, position.Y - radius,
                radius * 2, radius * 2);
            g->DrawEllipse(gcnew Pen(borderColor, 2),
                position.X - radius, position.Y - radius,
                radius * 2, radius * 2);
        }

        virtual String^ ToString() override {
            return String::Format("Круг [X:{0} Y:{1} R:{2}]", position.X, position.Y, radius);
        }
    };
}