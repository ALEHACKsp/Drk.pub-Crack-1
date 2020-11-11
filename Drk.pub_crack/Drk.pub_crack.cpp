#include <windows.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <stdio.h>
#include <shlwapi.h>
#include <accctrl.h>
#include <aclapi.h>
#include <shlobj_core.h>
#include <tlhelp32.h>

#include "kdmapper.hpp"
#include "driver_eac.h"

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "version.lib")

bool success = false;

extern "C" void clean();

void eac()
{
	SetConsoleTitleA("Drk.Pub Cracked By ZeraX             Charlootus you're a fucking skid lmfao             EAC DRIVER");

	std::cout << "[+] Stopping And Removing Service!" << std::endl;
	service::StopAndRemove("Drk.Pub_EASYANTICHEAT-DRIVER.sys");
	std::cout << "[+] Deleting File: C:\\Drk.Pub_EASYANTICHEAT-DRIVER.sys!" << std::endl;
	remove("C:\\Drk.Pub_EASYANTICHEAT-DRIVER.sys");

	std::cout << "[+] Opening Ofstream To Write C:\\Drk.Pub_EASYANTICHEAT-DRIVER.sys!" << std::endl;
	std::ofstream B("C:\\Drk.Pub_EASYANTICHEAT-DRIVER.sys", std::ios::binary);
	std::cout << "[+] Writing Driver Data To C:\\Drk.Pub_EASYANTICHEAT-DRIVER.sys!" << std::endl;
	B.write((char*)DrkPub_EAC, sizeof(DrkPub_EAC));
	std::cout << "[+] Closing Handle To C:\\Drk.Pub_EASYANTICHEAT-DRIVER.sys!" << std::endl;
	B.close();

	std::cout << "[+] Registering And Starting Service!" << std::endl;
	if (!service::RegisterAndStart("C:\\Drk.Pub_EASYANTICHEAT-DRIVER.sys"))
		std::cout << "[-] Failed To Start Service For File: C:\\Drk.Pub_EASYANTICHEAT-DRIVER.sys!" << std::endl;
	else
		success = true;
}

void be()
{
	SetConsoleTitleA("Drk.Pub Cracked By ZeraX             Charlootus you're a fucking skid lmfao             BE DRIVER");

	service::StopAndRemove("iqvw64e.sys");
	system("del /f /q C:\\Users\\%username%\\AppData\\Local\\Temp\\iqvw64e.sys");

	HANDLE iqvw64e_device_handle = intel_driver::Load();
	if (!iqvw64e_device_handle || iqvw64e_device_handle == INVALID_HANDLE_VALUE)
	{
		std::cout << "[-] Failed To Start Intel Vulner Driver Service!" << std::endl;
		success = false;
		return;
	}

	if (!kdmapper::MapDriver(iqvw64e_device_handle))
	{
		std::cout << "[-] Failed To Map Driver!" << std::endl;
		intel_driver::Unload(iqvw64e_device_handle);
		success = false;
		return;
	}

	intel_driver::Unload(iqvw64e_device_handle);

	success = true;
}

int main()
{
	LABEL_1:
	int A = 0;

	system("cls");

	SetConsoleTitleA("Drk.Pub Cracked By ZeraX             Charlootus you're a fucking skid lmfao");

	std::cout << R"([1] EAC DRIVER
[2] BE DRIVER
[3] CLEAN

[+] Option: )";

	std::cin >> A;

	switch (A)
	{
	case 1:
		eac();
		break;
	case 2:
		be();
		break;
	case 3:
		clean();
		break;
	default:
		goto LABEL_1;
		break;
	}

	if (A == 1 || A == 2)
	{
		if (success)
			std::cout << "\n\n[+] Done Mapped Driver And Spoofed!\n\nExiting In 5 Seconds!";
		else
			std::cout << "\n\n[-] Failed To Map Driver!\n\nExiting In 5 Seconds!";
	}
	else
		std::cout << "\n\n[+] Done Cleaned!\n\nExiting In 5 Seconds!";

	Sleep(5000);

	exit(0);
}