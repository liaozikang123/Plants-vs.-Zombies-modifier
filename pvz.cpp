#include "pvz.h"
int pvz::InithWnd()
{
	hWnd = FindWindow(NULL, L"植物大战僵尸中文版");
	if (hWnd == NULL) {	//如果无法获取句柄则报错
		return false;
	}
	return true;
}
int pvz::InitProcId()
{
	GetWindowThreadProcessId(hWnd, &this->pro_id);	//获取进程Ihis->pro_iD  
	if (this->pro_id == 0) {
		throw std::runtime_error("无法获取窗口id,请检查进程是否存在!");
		return false;
	}
	return true;
}
int pvz::InitObject()
{
	this->hpro = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, pro_id);
	if (hpro == 0) {
		throw std::runtime_error("无法获取进程id,请检查进程是否存在!");
	}
	int bRet = EnumProcessModulesEx(hpro, (HMODULE*)(hModule), sizeof(hModule), &dwRet, NULL);
	if (bRet == 0) {
		throw std::runtime_error("EnumProcessModules");
	}
	pro_base = (DWORD)hModule[0];
	sun_addr = pro_base + 0x002A9EC0;
	new_sun_value = 2000;
	code_3 = 0xE85308EB;
	code_4 = 0xE853087B;
	kill_1 = pro_base + 0x0013130F; //
	sun_collect = 0x0043158F; //0x0053130F
	code_1 = 0x9090ff29; //0x20247c2b
	kill_2 = pro_base + 0x00131044; //0x00531044
	code_2 = 0xC929;	//0xc82b
	ReadProcessMemory(this->hpro, (PVOID)sun_addr, &sun_addr, 4, 0);
	this->sun_addr = this->sun_addr + 0x768;
	ReadProcessMemory(this->hpro, (PVOID)sun_addr, &sun_addr, 4, 0);
	this->sun_addr = this->sun_addr + 0x5560;
	ReadProcessMemory(this->hpro, (PVOID)sun_addr, &sun_value, 4, 0);
}
void pvz::Editsun()
{
	ReadProcessMemory(this->hpro, (PVOID)sun_addr, &sun_value, 4, 0);
	int new_sun_value = sun_value + 1000;
	WriteProcessMemory(hpro, (LPVOID)sun_addr, &new_sun_value, 4, 0); //修改阳光
}
void pvz::AotuCollect()
{
	ReadProcessMemory(hpro, (PVOID)sun_collect, &sun_collect_value, 4, 0);
	WriteProcessMemory(hpro, (LPVOID)sun_collect, &code_3, 4, 0); //修改阳光  7B->EB
}
void pvz::DownAotuCollect()
{
	ReadProcessMemory(hpro, (PVOID)sun_collect, &sun_collect_value, 4, 0);
	WriteProcessMemory(hpro, (LPVOID)sun_collect, &code_4, 4, 0); //修改阳光  7B->EB
}
void pvz::Kill_Common()
{
	WriteProcessMemory(hpro, (LPVOID)kill_1, (LPVOID)&code_1, 4, 0); //普通僵尸秒杀
}
void pvz::Kill_Second()
{
	WriteProcessMemory(hpro, (LPVOID)kill_2, (LPVOID)&code_2, 2, 0); //帽子僵尸秒杀
}


pvz::pvz()
{
	if (!InithWnd())
	{
		return;
	}
	InitProcId();
	InitObject();
}

pvz::~pvz()
{

}
