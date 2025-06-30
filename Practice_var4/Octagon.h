#pragma once
#include "Figure.h"
#include <math.h>

namespace ShapesApp {
    public ref class Octagon : public Figure {
    public:
        Octagon(Point pos, int r, Color fill, Color border)
            : Figure(pos, r, fill, border) {
        }

        virtual void Draw(Graphics^ g) override {
            if (!visible) return;
            array<Point>^ points = gcnew array<Point>(8);
            for (int i = 0; i < 8; i++) {
                double angle = 45.0 * i * Math::PI / 180.0;
                points[i] = Point(
                    position.X + (int)(radius * Math::Cos(angle)),
                    position.Y + (int)(radius * Math::Sin(angle))
                );
            }
            g->FillPolygon(gcnew SolidBrush(fillColor), points);
            g->DrawPolygon(gcnew Pen(borderColor, 2), points);
        }

        virtual String^ ToString() override {
            return String::Format("Восьмиугольник [X:{0} Y:{1} R:{2}]", position.X, position.Y, radius);
        }
    };
}