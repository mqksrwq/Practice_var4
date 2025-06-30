#pragma once
#include <Windows.h>

namespace PracticeVar4 {
    using namespace System;
    using namespace System::Drawing;

    public ref class Figure abstract {
    protected:
        Point position;
        int radius;
        Color fillColor;
        Color borderColor;
        bool visible;

    public:
        Figure(Point pos, int r, Color fill, Color border)
            : position(pos), radius(r), fillColor(fill), borderColor(border), visible(true) {
        }

        property Point Position {
            Point get() { return position; }
            void set(Point value) { position = value; }
        }

        property int Radius {
            int get() { return radius; }
            void set(int value) { radius = value; }
        }

        property bool Visible {
            bool get() { return visible; }
            void set(bool value) { visible = value; }
        }

        virtual void Show() { visible = true; }
        virtual void Hide() { visible = false; }
        virtual void Move(Point newPos) { position = newPos; }
        virtual void Draw(Graphics^ g) abstract;
        virtual String^ ToString() override {
            return String::Format("{0} [X:{1} Y:{2} R:{3}] {4}",
                GetType()->Name,
                position.X, position.Y, radius,
                visible ? "(Видима)" : "(Скрыта)");
        }
    };
}