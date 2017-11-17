; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMouseSimulateDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MouseSimulate.h"

ClassCount=3
Class1=CMouseSimulateApp
Class2=CMouseSimulateDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_MOUSESIMULATE_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDR_NOTIFYICON_POPUP

[CLS:CMouseSimulateApp]
Type=0
HeaderFile=MouseSimulate.h
ImplementationFile=MouseSimulate.cpp
Filter=N

[CLS:CMouseSimulateDlg]
Type=0
HeaderFile=MouseSimulateDlg.h
ImplementationFile=MouseSimulateDlg.cpp
Filter=D
LastObject=CMouseSimulateDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=MouseSimulateDlg.h
ImplementationFile=MouseSimulateDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MOUSESIMULATE_DIALOG]
Type=1
Class=CMouseSimulateDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC_COMMENT,static,1342308352

[MNU:IDR_NOTIFYICON_POPUP]
Type=1
Class=?
Command1=ID_SHOW_MAIN_DLG
Command2=ID_QUIT_PROGRAM
CommandCount=2

