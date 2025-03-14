#include "MyForm.h"
#include "pch.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^ args) // Change void to int
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    project::MyForm form;
    Application::Run(% form);
    return 0; // Return an integer value
}