#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

// Бояркин Максим - 24ВП1

[STAThread]
int main() {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew PracticeVar4::MainForm());
    return 0;
}