#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

// ������� ������ - 24��1

[STAThread]
int main() {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew PracticeVar4::MainForm());
    return 0;
}