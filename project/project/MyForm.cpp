#include "MyForm.h"
#include "pch.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    project::MyForm form;
    Application::Run(% form);
    
    
    return 0; 
}