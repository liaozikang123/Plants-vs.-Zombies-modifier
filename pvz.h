#pragma once
#include<Windows.h>
#include<psapi.h>
#include<iostream>
using namespace std;
class pvz
{
private:
	HWND hWnd;
	HANDLE hpro;
	DWORD pro_id;
	DWORD pro_base = NULL;
	HMODULE hModule[100] = { 0 };
	DWORD dwRet = 0;
private:
	DWORD sun_addr;
	DWORD sun_value;
	DWORD new_sun_value;
	DWORD code_3;
	DWORD code_4;
	DWORD kill_1; //
	DWORD sun_collect; //0x0053130F
	DWORD sun_collect_value;
	DWORD code_1; //0x20247c2b
	DWORD kill_2; //0x00531044
	WORD code_2;	//0xc82b
public:
	int InithWnd();
	int InitProcId();
	int InitObject();
	void Editsun();
	void AotuCollect();
	void Kill_Common();
	void Kill_Second();
	void DownAotuCollect();

public:
	pvz();
	~pvz();
};
