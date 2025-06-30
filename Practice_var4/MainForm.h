#pragma once
#include "Circle.h"
#include "Octagon.h"
#include "ComplexFigure.h"
#include "FiguresContainer.h"

namespace ShapesApp {
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Windows::Forms;

    public ref class MainForm : public Form {
    private:
        FiguresContainer^ container;
        ListBox^ figuresList;
        Button^ btnAddCircle;
        Button^ btnAddOctagon;
        Button^ btnAddComplex;
        Button^ btnRemove;
        Button^ btnToggleVisible;
        Button^ btnMove;
        TextBox^ txtX;
        TextBox^ txtY;
        TextBox^ txtRadius;
        Label^ lblX;
        Label^ lblY;
        Label^ lblRadius;
        Label^ lblFigures;
        Drawing::Rectangle drawingArea;

    public:
        MainForm() {
            // Инициализация области рисования (X: 200-600, Y: 50-550)
            drawingArea = Drawing::Rectangle(200, 50, 400, 500);
            InitializeComponent();
            container = gcnew FiguresContainer();
        }

    private:
        void InitializeComponent() {
            // Настройка формы
            this->ClientSize = System::Drawing::Size(1000, 600);
            this->Text = L"Управление фигурами";
            this->DoubleBuffered = true;
            this->BackColor = Color::White;

            // Список фигур
            lblFigures = gcnew Label();
            lblFigures->Text = "Список фигур:";
            lblFigures->Location = Point(700, 20);
            lblFigures->Size = System::Drawing::Size(200, 20);
            this->Controls->Add(lblFigures);

            figuresList = gcnew ListBox();
            figuresList->Location = Point(700, 50);
            figuresList->Size = System::Drawing::Size(280, 300);
            figuresList->HorizontalScrollbar = true;
            this->Controls->Add(figuresList);

            // Поля ввода с правильными диапазонами
            lblX = gcnew Label();
            lblX->Text = String::Format("X ({0}-{1}):", drawingArea.Left, drawingArea.Right);
            lblX->Location = Point(700, 360);
            lblX->Size = System::Drawing::Size(120, 20);
            this->Controls->Add(lblX);

            txtX = gcnew TextBox();
            txtX->Location = Point(820, 360);
            txtX->Size = System::Drawing::Size(60, 20);
            this->Controls->Add(txtX);

            lblY = gcnew Label();
            lblY->Text = String::Format("Y ({0}-{1}):", drawingArea.Top, drawingArea.Bottom);
            lblY->Location = Point(700, 390);
            lblY->Size = System::Drawing::Size(120, 20);
            this->Controls->Add(lblY);

            txtY = gcnew TextBox();
            txtY->Location = Point(820, 390);
            txtY->Size = System::Drawing::Size(60, 20);
            this->Controls->Add(txtY);

            lblRadius = gcnew Label();
            lblRadius->Text = "Радиус:";
            lblRadius->Location = Point(700, 420);
            lblRadius->Size = System::Drawing::Size(50, 20);
            this->Controls->Add(lblRadius);

            txtRadius = gcnew TextBox();
            txtRadius->Location = Point(750, 420);
            txtRadius->Size = System::Drawing::Size(50, 20);
            this->Controls->Add(txtRadius);

            // Кнопки добавления фигур
            btnAddCircle = gcnew Button();
            btnAddCircle->Text = "Добавить круг";
            btnAddCircle->Location = Point(20, 20);
            btnAddCircle->Size = System::Drawing::Size(150, 30);
            btnAddCircle->Click += gcnew EventHandler(this, &MainForm::AddCircle);
            this->Controls->Add(btnAddCircle);

            btnAddOctagon = gcnew Button();
            btnAddOctagon->Text = "Добавить восьмиугольник";
            btnAddOctagon->Location = Point(20, 60);
            btnAddOctagon->Size = System::Drawing::Size(180, 35);
            btnAddOctagon->Click += gcnew EventHandler(this, &MainForm::AddOctagon);
            this->Controls->Add(btnAddOctagon);

            btnAddComplex = gcnew Button();
            btnAddComplex->Text = "Добавить комплекс";
            btnAddComplex->Location = Point(20, 100);
            btnAddComplex->Size = System::Drawing::Size(150, 30);
            btnAddComplex->Click += gcnew EventHandler(this, &MainForm::AddComplex);
            this->Controls->Add(btnAddComplex);

            // Кнопки управления
            btnRemove = gcnew Button();
            btnRemove->Text = "Удалить";
            btnRemove->Location = Point(700, 450);
            btnRemove->Size = System::Drawing::Size(100, 30);
            btnRemove->Click += gcnew EventHandler(this, &MainForm::RemoveFigure);
            this->Controls->Add(btnRemove);

            btnToggleVisible = gcnew Button();
            btnToggleVisible->Text = "Скрыть/Показать";
            btnToggleVisible->Location = Point(700, 490);
            btnToggleVisible->Size = System::Drawing::Size(120, 30);
            btnToggleVisible->Click += gcnew EventHandler(this, &MainForm::ToggleVisibility);
            this->Controls->Add(btnToggleVisible);

            btnMove = gcnew Button();
            btnMove->Text = "Переместить";
            btnMove->Location = Point(700, 530);
            btnMove->Size = System::Drawing::Size(100, 30);
            btnMove->Click += gcnew EventHandler(this, &MainForm::MoveFigure);
            this->Controls->Add(btnMove);

            this->Paint += gcnew PaintEventHandler(this, &MainForm::OnPaint);
        }

        bool ValidatePosition(Point pos, int radius) {
            if (pos.X - radius < drawingArea.Left ||
                pos.X + radius > drawingArea.Right ||
                pos.Y - radius < drawingArea.Top ||
                pos.Y + radius > drawingArea.Bottom) {
                MessageBox::Show(
                    String::Format(
                        "Фигура выходит за границы области рисования!\n"
                        "Допустимые координаты с учетом радиуса R:\n"
                        "X: {0}+R до {1}-R\nY: {2}+R до {3}-R\n"
                        "Текущие границы: X[{0}-{1}] Y[{2}-{3}]",
                        drawingArea.Left, drawingArea.Right,
                        drawingArea.Top, drawingArea.Bottom),
                    "Ошибка",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return false;
            }
            return true;
        }

        void UpdateFiguresList() {
            figuresList->Items->Clear();
            figuresList->DrawMode = DrawMode::OwnerDrawFixed;
            figuresList->DrawItem += gcnew DrawItemEventHandler(this, &MainForm::OnDrawItem);

            for each(Figure ^ fig in container->Figures) {
                figuresList->Items->Add(fig);
            }
        }

        void OnDrawItem(Object^ sender, DrawItemEventArgs^ e) {
            if (e->Index < 0) return;

            Figure^ fig = (Figure^)figuresList->Items[e->Index];
            String^ text = fig->ToString();

            // Увеличиваем ширину элемента
            RectangleF bounds = RectangleF(e->Bounds.X, e->Bounds.Y,
                e->Bounds.Width + 50, e->Bounds.Height);

            // Устанавливаем стиль текста
            System::Drawing::Font^ font;
            if (fig->Visible) {
                font = gcnew System::Drawing::Font(e->Font, FontStyle::Bold);
                e->Graphics->FillRectangle(Brushes::White, bounds);
            }
            else {
                font = gcnew System::Drawing::Font(e->Font, FontStyle::Regular);
                e->Graphics->FillRectangle(Brushes::LightGray, bounds);
            }

            // Используем StringFormat для правильного выравнивания
            StringFormat^ format = gcnew StringFormat();
            format->LineAlignment = StringAlignment::Center;

            // Рисуем текст с учетом новых границ
            e->Graphics->DrawString(text, font, Brushes::Black, bounds, format);

            // Рисуем фокус
            if ((e->State & DrawItemState::Selected) == DrawItemState::Selected) {
                e->Graphics->DrawRectangle(Pens::Blue, Rectangle::Round(bounds));
            }

            delete font;
            delete format;
        }

        void AddCircle(Object^ sender, EventArgs^ e) {
            try {
                Point pos(Int32::Parse(txtX->Text), Int32::Parse(txtY->Text));
                int r = Int32::Parse(txtRadius->Text);

                if (!ValidatePosition(pos, r)) return;

                container->Add(gcnew Circle(pos, r, Color::Red, Color::Black));
                UpdateFiguresList();
                this->Invalidate();
            }
            catch (Exception^) {
                MessageBox::Show("Ошибка ввода! Укажите числовые значения в допустимых диапазонах.");
            }
        }

        void AddOctagon(Object^ sender, EventArgs^ e) {
            try {
                Point pos(Int32::Parse(txtX->Text), Int32::Parse(txtY->Text));
                int r = Int32::Parse(txtRadius->Text);

                if (!ValidatePosition(pos, r)) return;

                container->Add(gcnew Octagon(pos, r, Color::Blue, Color::Black));
                UpdateFiguresList();
                this->Invalidate();
            }
            catch (Exception^) {
                MessageBox::Show("Ошибка ввода! Укажите числовые значения в допустимых диапазонах.");
            }
        }

        void AddComplex(Object^ sender, EventArgs^ e) {
            try {
                Point pos(Int32::Parse(txtX->Text), Int32::Parse(txtY->Text));
                int r = Int32::Parse(txtRadius->Text);

                if (!ValidatePosition(pos, r)) return;

                container->Add(gcnew ComplexFigure(pos, r,
                    Color::Green, Color::Yellow, Color::Black));
                UpdateFiguresList();
                this->Invalidate();
            }
            catch (Exception^) {
                MessageBox::Show("Ошибка ввода! Укажите числовые значения в допустимых диапазонах.");
            }
        }

        void RemoveFigure(Object^ sender, EventArgs^ e) {
            if (figuresList->SelectedIndex != -1) {
                container->RemoveAt(figuresList->SelectedIndex);
                UpdateFiguresList();
                this->Invalidate();
            }
        }

        void ToggleVisibility(Object^ sender, EventArgs^ e) {
            if (figuresList->SelectedIndex != -1) {
                container->ToggleVisibility(figuresList->SelectedIndex);
                UpdateFiguresList();
                this->Invalidate();
            }
        }

        void MoveFigure(Object^ sender, EventArgs^ e) {
            if (figuresList->SelectedIndex != -1) {
                try {
                    Point newPos(Int32::Parse(txtX->Text), Int32::Parse(txtY->Text));
                    int r = container->Figures[figuresList->SelectedIndex]->Radius;

                    if (!ValidatePosition(newPos, r)) return;

                    container->Figures[figuresList->SelectedIndex]->Move(newPos);
                    UpdateFiguresList();
                    this->Invalidate();
                }
                catch (Exception^) {
                    MessageBox::Show("Ошибка в координатах! Укажите допустимые значения.");
                }
            }
        }

        void OnPaint(Object^ sender, PaintEventArgs^ e) {
            e->Graphics->Clear(Color::White);

            // Рисуем границу области
            Pen^ areaPen = gcnew Pen(Color::LightGray, 2);
            e->Graphics->DrawRectangle(areaPen, drawingArea);

            // Подпись области
            System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", 10);
            e->Graphics->DrawString(
                String::Format("Область рисования ({0},{1})-({2},{3})",
                    drawingArea.Left, drawingArea.Top,
                    drawingArea.Right, drawingArea.Bottom),
                font, Brushes::Gray, drawingArea.Left, drawingArea.Top - 20);

            // Рисуем фигуры
            container->DrawAll(e->Graphics);
        }
    };
}