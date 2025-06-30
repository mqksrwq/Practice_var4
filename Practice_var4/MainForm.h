#pragma once
#include "Circle.h"
#include "Octagon.h"
#include "ComplexFigure.h"
#include "FiguresContainer.h"

namespace PracticeVar4 {
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

        // �������� ��� ���������� �������
        ColorDialog^ colorDialog;
        Button^ btnChangeFill;
        Button^ btnChangeOctagonFill;  // ������ ������� (��� ����������� ������)
        Button^ btnChangeBorder;       // ������ ����� ��� ���������
        Color currentFillColor;
        Color currentBorderColor;
        Color currentOctagonFillColor;

    public:
        MainForm() {
            // ������������� ������ �� ���������
            currentFillColor = Color::Red;
            currentBorderColor = Color::Black;
            currentOctagonFillColor = Color::Yellow;

            // ������������� ������� ���������
            drawingArea = Drawing::Rectangle(200, 50, 400, 500);
            InitializeComponent();
            container = gcnew FiguresContainer();
        }

    private:
        void InitializeComponent() {
            // ��������� �����
            this->ClientSize = System::Drawing::Size(1000, 600);
            this->Text = L"���������� ��������";
            this->DoubleBuffered = true;
            this->BackColor = Color::White;

            // ������ �����
            lblFigures = gcnew Label();
            lblFigures->Text = "������ �����:";
            lblFigures->Location = Point(700, 20);
            lblFigures->Size = System::Drawing::Size(200, 20);
            this->Controls->Add(lblFigures);

            figuresList = gcnew ListBox();
            figuresList->Location = Point(700, 50);
            figuresList->Size = System::Drawing::Size(280, 300);
            figuresList->HorizontalScrollbar = true;
            this->Controls->Add(figuresList);

            // ���� �����
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
            lblRadius->Text = "������:";
            lblRadius->Location = Point(700, 420);
            lblRadius->Size = System::Drawing::Size(50, 20);
            this->Controls->Add(lblRadius);

            txtRadius = gcnew TextBox();
            txtRadius->Location = Point(820, 420);
            txtRadius->Size = System::Drawing::Size(60, 20);
            this->Controls->Add(txtRadius);

            // ������ ���������� �����
            btnAddCircle = gcnew Button();
            btnAddCircle->Text = "�������� ����";
            btnAddCircle->Location = Point(20, 20);
            btnAddCircle->Size = System::Drawing::Size(150, 30);
            btnAddCircle->Click += gcnew EventHandler(this, &MainForm::AddCircle);
            this->Controls->Add(btnAddCircle);

            btnAddOctagon = gcnew Button();
            btnAddOctagon->Text = "�������� ��������������";
            btnAddOctagon->Location = Point(20, 60);
            btnAddOctagon->Size = System::Drawing::Size(170, 30);
            btnAddOctagon->Click += gcnew EventHandler(this, &MainForm::AddOctagon);
            this->Controls->Add(btnAddOctagon);

            btnAddComplex = gcnew Button();
            btnAddComplex->Text = "�������� ��������";
            btnAddComplex->Location = Point(20, 100);
            btnAddComplex->Size = System::Drawing::Size(150, 30);
            btnAddComplex->Click += gcnew EventHandler(this, &MainForm::AddComplex);
            this->Controls->Add(btnAddComplex);

            // ������ ���������� �������
            colorDialog = gcnew ColorDialog();
            colorDialog->FullOpen = true;

            // ������ ������ ������� (������� ���)
            btnChangeFill = gcnew Button();
            btnChangeFill->Text = "������� (���.)";
            btnChangeFill->Location = Point(20, 150);  // ������ ������
            btnChangeFill->Size = System::Drawing::Size(100, 30);
            btnChangeFill->BackColor = currentFillColor;
            btnChangeFill->Click += gcnew EventHandler(this, &MainForm::ChangeFillColor);
            this->Controls->Add(btnChangeFill);

            // ������ ������ ������� (��� ����������� ������)
            btnChangeOctagonFill = gcnew Button();
            btnChangeOctagonFill->Text = "������� (�.�)";
            btnChangeOctagonFill->Location = Point(20, 250); // ����� � ������
            btnChangeOctagonFill->Size = System::Drawing::Size(100, 30);
            btnChangeOctagonFill->BackColor = currentOctagonFillColor;
            btnChangeOctagonFill->Click += gcnew EventHandler(this, &MainForm::ChangeOctagonFillColor);
            this->Controls->Add(btnChangeOctagonFill);

            // ������ ������ ������� (������ �� ������ ������)
            btnChangeBorder = gcnew Button();
            btnChangeBorder->Text = "������";
            btnChangeBorder->Location = Point(20, 190);  // ������ ������
            btnChangeBorder->Size = System::Drawing::Size(100, 30);
            btnChangeBorder->BackColor = currentBorderColor;
            btnChangeBorder->Click += gcnew EventHandler(this, &MainForm::ChangeBorderColor);
            this->Controls->Add(btnChangeBorder);

            // ������ ����������
            btnRemove = gcnew Button();
            btnRemove->Text = "�������";
            btnRemove->Location = Point(700, 450);
            btnRemove->Size = System::Drawing::Size(100, 30);
            btnRemove->Click += gcnew EventHandler(this, &MainForm::RemoveFigure);
            this->Controls->Add(btnRemove);

            btnToggleVisible = gcnew Button();
            btnToggleVisible->Text = "������/��������";
            btnToggleVisible->Location = Point(700, 490);
            btnToggleVisible->Size = System::Drawing::Size(120, 30);
            btnToggleVisible->Click += gcnew EventHandler(this, &MainForm::ToggleVisibility);
            this->Controls->Add(btnToggleVisible);

            btnMove = gcnew Button();
            btnMove->Text = "�����������";
            btnMove->Location = Point(700, 530);
            btnMove->Size = System::Drawing::Size(100, 30);
            btnMove->Click += gcnew EventHandler(this, &MainForm::MoveFigure);
            this->Controls->Add(btnMove);

            this->Paint += gcnew PaintEventHandler(this, &MainForm::OnPaint);
        }

        // ������ ��� ������ � �������
        void ChangeFillColor(Object^ sender, EventArgs^ e) {
            if (colorDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                currentFillColor = colorDialog->Color;
                btnChangeFill->BackColor = currentFillColor;
                UpdateSelectedFigureColors();
            }
        }

        void ChangeBorderColor(Object^ sender, EventArgs^ e) {
            if (colorDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                currentBorderColor = colorDialog->Color;
                btnChangeBorder->BackColor = currentBorderColor;
                UpdateSelectedFigureColors();
            }
        }

        void ChangeOctagonFillColor(Object^ sender, EventArgs^ e) {
            if (colorDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                currentOctagonFillColor = colorDialog->Color;
                btnChangeOctagonFill->BackColor = currentOctagonFillColor;
                UpdateSelectedFigureColors();
            }
        }

        void UpdateSelectedFigureColors() {
            if (figuresList->SelectedIndex == -1) return;

            Figure^ selected = container->Figures[figuresList->SelectedIndex];

            if (dynamic_cast<ComplexFigure^>(selected) == nullptr) {
                // ������� ������
                selected->FillColor = currentFillColor;
                selected->BorderColor = currentBorderColor;
            }
            else {
                // ����������� ������
                ComplexFigure^ complex = (ComplexFigure^)selected;
                complex->CircleFigure->FillColor = currentFillColor;
                complex->OctagonFigure->FillColor = currentOctagonFillColor;
                complex->CircleFigure->BorderColor = currentBorderColor;
                complex->OctagonFigure->BorderColor = currentBorderColor;
            }

            UpdateFiguresList();
            this->Invalidate();
        }

        // ��������� ���������
        bool ValidatePosition(Point pos, int radius) {
            if (pos.X - radius < drawingArea.Left ||
                pos.X + radius > drawingArea.Right ||
                pos.Y - radius < drawingArea.Top ||
                pos.Y + radius > drawingArea.Bottom) {
                MessageBox::Show(
                    String::Format(
                        "������ ������� �� ������� ������� ���������!\n"
                        "���������� ���������� � ������ ������� R:\n"
                        "X: {0}+R �� {1}-R\nY: {2}+R �� {3}-R\n"
                        "������� �������: X[{0}-{1}] Y[{2}-{3}]",
                        drawingArea.Left, drawingArea.Right,
                        drawingArea.Top, drawingArea.Bottom),
                    "������",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Warning);
                return false;
            }
            return true;
        }

        // ���������� ������ �����
        void UpdateFiguresList() {
            figuresList->Items->Clear();
            figuresList->DrawMode = DrawMode::OwnerDrawFixed;
            figuresList->DrawItem += gcnew DrawItemEventHandler(this, &MainForm::OnDrawItem);

            for each(Figure ^ fig in container->Figures) {
                figuresList->Items->Add(fig);
            }
        }

        // ��������� ��������� ������
        void OnDrawItem(Object^ sender, DrawItemEventArgs^ e) {
            if (e->Index < 0) return;

            Figure^ fig = (Figure^)figuresList->Items[e->Index];
            String^ text = fig->ToString();

            RectangleF bounds = RectangleF(e->Bounds.X, e->Bounds.Y,
                e->Bounds.Width + 50, e->Bounds.Height);

            System::Drawing::Font^ font;
            Brush^ background;
            Brush^ textBrush;

            if (fig->Visible) {
                font = gcnew System::Drawing::Font(e->Font, FontStyle::Bold);
                background = Brushes::White;
                textBrush = Brushes::Black;
            }
            else {
                font = gcnew System::Drawing::Font(e->Font, FontStyle::Italic);
                background = Brushes::LightGray;
                textBrush = Brushes::Gray;
            }

            e->Graphics->FillRectangle(background, bounds);

            StringFormat^ format = gcnew StringFormat();
            format->LineAlignment = StringAlignment::Center;

            e->Graphics->DrawString(text, font, textBrush, bounds, format);

            if ((e->State & DrawItemState::Selected) == DrawItemState::Selected) {
                e->Graphics->DrawRectangle(Pens::Blue, Rectangle::Round(bounds));
            }

            delete font;
            delete format;
        }

        // ���������� �����
        void AddCircle(Object^ sender, EventArgs^ e) {
            try {
                Point pos(Int32::Parse(txtX->Text), Int32::Parse(txtY->Text));
                int r = Int32::Parse(txtRadius->Text);

                if (!ValidatePosition(pos, r)) return;

                container->Add(gcnew Circle(pos, r, currentFillColor, currentBorderColor));
                UpdateFiguresList();
                this->Invalidate();
            }
            catch (Exception^) {
                MessageBox::Show("������ �����! ������� �������� �������� � ���������� ����������.");
            }
        }

        void AddOctagon(Object^ sender, EventArgs^ e) {
            try {
                Point pos(Int32::Parse(txtX->Text), Int32::Parse(txtY->Text));
                int r = Int32::Parse(txtRadius->Text);

                if (!ValidatePosition(pos, r)) return;

                container->Add(gcnew Octagon(pos, r, currentFillColor, currentBorderColor));
                UpdateFiguresList();
                this->Invalidate();
            }
            catch (Exception^) {
                MessageBox::Show("������ �����! ������� �������� �������� � ���������� ����������.");
            }
        }

        void AddComplex(Object^ sender, EventArgs^ e) {
            try {
                Point pos(Int32::Parse(txtX->Text), Int32::Parse(txtY->Text));
                int r = Int32::Parse(txtRadius->Text);

                if (!ValidatePosition(pos, r)) return;

                container->Add(gcnew ComplexFigure(pos, r,
                    currentFillColor, currentOctagonFillColor, currentBorderColor));
                UpdateFiguresList();
                this->Invalidate();
            }
            catch (Exception^) {
                MessageBox::Show("������ �����! ������� �������� �������� � ���������� ����������.");
            }
        }

        // ���������� ��������
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
                    MessageBox::Show("������ � �����������! ������� ���������� ��������.");
                }
            }
        }

        // ��������� �� �����
        void OnPaint(Object^ sender, PaintEventArgs^ e) {
            e->Graphics->Clear(Color::White);

            // ������ ������� ������� ���������
            Pen^ areaPen = gcnew Pen(Color::LightGray, 2);
            e->Graphics->DrawRectangle(areaPen, drawingArea);
            delete areaPen;

            // ������� ������� ���������
            System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", 10);
            e->Graphics->DrawString(
                String::Format("������� ��������� ({0},{1})-({2},{3})",
                    drawingArea.Left, drawingArea.Top,
                    drawingArea.Right, drawingArea.Bottom),
                font, Brushes::Gray, drawingArea.Left, drawingArea.Top - 20);
            delete font;

            // ��������� ���� �����
            container->DrawAll(e->Graphics);
        }
    };
}