#pragma once
#include "Circle.h"
#include "Octagon.h"

namespace PracticeVar4 {
    public ref class ComplexFigure : public Figure {
    private:
        Circle^ circle;
        Octagon^ octagon;

    public:
        ComplexFigure(Point pos, int r, Color circleFill, Color octagonFill, Color border)
            : Figure(pos, r, Color::Empty, border) {
            circle = gcnew Circle(pos, r, circleFill, border);
            octagon = gcnew Octagon(pos, r, octagonFill, border);
        }

        property Circle^ CircleFigure{
            Circle ^ get() { return circle; }
        }

            property Octagon^ OctagonFigure{
                Octagon ^ get() { return octagon; }
        }

            virtual property Color FillColor{
                Color get() override { return Figure::FillColor; }
                void set(Color value) override {
                    circle->FillColor = value;
                    octagon->FillColor = octagon->FillColor; // Сохраняем оригинальный цвет
                }
        }

            virtual property Color BorderColor{
                Color get() override { return Figure::BorderColor; }
                void set(Color value) override {
                    circle->BorderColor = value;
                    octagon->BorderColor = value;
                }
        }

            virtual void Show() override {
            Figure::Show();
            circle->Show();
            octagon->Show();
        }

        virtual void Hide() override {
            Figure::Hide();
            circle->Hide();
            octagon->Hide();
        }

        virtual void Move(Point newPos) override {
            Figure::Move(newPos);
            circle->Move(newPos);
            octagon->Move(newPos);
        }

        virtual void Draw(Graphics^ g) override {
            if (!visible) return;
            circle->Draw(g);
            octagon->Draw(g);
        }

        virtual String^ ToString() override {
            return String::Format("Комплексная фигура [X:{0} Y:{1} R:{2}]",
                position.X, position.Y, radius);
        }
    };
}