#include "pch.h"

BOOL isElementalGem(DWORD& pVector) {
	if (std::find(vFireGems.begin(), vFireGems.end(), pVector) != vFireGems.end()) {
		return FIRE;
	}
	if (std::find(vWaterGems.begin(), vWaterGems.end(), pVector) != vWaterGems.end()) {
		return WATER;
	}
	if (std::find(vEarthGems.begin(), vEarthGems.end(), pVector) != vEarthGems.end()) {
		return EARTH;
	}
	if (std::find(vWindGems.begin(), vWindGems.end(), pVector) != vWindGems.end()) {
		return WIND;
	}
	return FALSE;
}

BOOL isElementalItem(DWORD& pArray) {
	if (std::find(aFireItems.begin(), aFireItems.end(), pArray) != aFireItems.end()) {
		return FIRE;
	}
	if (std::find(aWaterItems.begin(), aWaterItems.end(), pArray) != aWaterItems.end()) {
		return WATER;
	}
	if (std::find(aEarthItems.begin(), aEarthItems.end(), pArray) != aEarthItems.end()) {
		return EARTH;
	}
	if (std::find(aWindItems.begin(), aWindItems.end(), pArray) != aWindItems.end()) {
		return WIND;
	}
	return FALSE;
}

void __declspec(naked) BagHook() {
	__asm {
		pushad
		//first slot
		lea edx,[eax+0x90E2FE]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//second slot
		lea edx,[eax+0x90E2FF]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//third slot
		lea edx,[eax+0x90E300]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//fourth slot
		lea edx,[eax+0x90E301]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//fifth slot
		lea edx,[eax+0x90E302]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//sixth slot
		lea edx,[eax+0x90E303]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//ecx = Types 
		//edx = TypeIds
		movzx ecx,byte ptr[eax+0x90E2F9]
		imul ecx,0x3E8
		movzx edx,byte ptr[eax+0x90E2FA]
		add ecx,edx
		//save ItemIds
		mov[eax+aBagItems],ecx
		//ebx = pArray
		lea ebx,[eax+aBagItems]
		push ebx
		call isElementalItem
		add esp,0x4
		mov ebx,eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		popad
		//original code
		mov edx,dword ptr ss:[esp+0x1C]
		mov eax,dword ptr ss:[esp+0x10]
		jmp dwBagRetn

		_fire:
		popad
		mov edx,dword ptr ss:[esp+0x1C]
		mov eax,dword ptr ss:[esp+0x10]
		push 0x1
		push 0x0
		push edx
		push ebx
		push edi
		push eax
		push ebp
		push ecx
		lea ecx,dword ptr ds:[esi+0x30]
		call dwIconPos
		mov ecx,dword ptr ss:[esp+0x10]
		push 0x20
		push 0x20
		push ecx
		push ebp
		push 0x50FF0000
		call dwOverlay
		add esp,0x14
		jmp dwBagJump

		_water:
		popad
		mov edx,dword ptr ss:[esp+0x1C]
		mov eax,dword ptr ss:[esp+0x10]
		push 0x1
		push 0x0
		push edx
		push ebx
		push edi
		push eax
		push ebp
		push ecx
		lea ecx,dword ptr ds:[esi+0x30]
		call dwIconPos
		mov ecx,dword ptr ss:[esp+0x10]
		push 0x20
		push 0x20
		push ecx
		push ebp
		push 0x5000FFFF
		call dwOverlay
		add esp,0x14
		jmp dwBagJump

		_earth:
		popad
		mov edx,dword ptr ss:[esp+0x1C]
		mov eax,dword ptr ss:[esp+0x10]
		push 0x1
		push 0x0
		push edx
		push ebx
		push edi
		push eax
		push ebp
		push ecx
		lea ecx,dword ptr ds:[esi+0x30]
		call dwIconPos
		mov ecx,dword ptr ss:[esp+0x10]
		push 0x20
		push 0x20
		push ecx
		push ebp
		push 0x5000FF00
		call dwOverlay
		add esp,0x14
		jmp dwBagJump

		_wind:
		popad
		mov edx,dword ptr ss:[esp+0x1C]
		mov eax,dword ptr ss:[esp+0x10]
		push 0x1
		push 0x0
		push edx
		push ebx
		push edi
		push eax
		push ebp
		push ecx
		lea ecx,dword ptr ds:[esi+0x30]
		call dwIconPos
		mov ecx,dword ptr ss:[esp+0x10]
		push 0x20
		push 0x20
		push ecx
		push ebp
		push 0x50FFFFFF
		call dwOverlay
		add esp,0x14
		jmp dwBagJump
	}
}

void __declspec(naked) BarHook() {
	__asm {
		pushad
		//first slot
		lea edx,[esi+0x90E2FE]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//second slot
		lea edx,[esi+0x90E2FF]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//third slot
		lea edx,[esi+0x90E300]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//fourth slot
		lea edx,[esi+0x90E301]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//fifth slot
		lea edx,[esi+0x90E302]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//sixth slot
		lea edx,[esi+0x90E303]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//ecx = Types 
		//edx = TypeIds
		movzx ecx,byte ptr[esi+0x90E2F9]
		imul ecx,0x3E8
		movzx edx,byte ptr[esi+0x90E2FA]
		add ecx,edx
		//save ItemIds
		mov[esi+aBarItems],ecx
		//ebx = pArray
		lea ebx,[esi+aBarItems]
		push ebx
		call isElementalItem
		add esp,0x4
		mov ebx,eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		popad
		//original code
		push 0x1
		push 0x0
		push eax
		jmp dwBarRetn

		_fire:
		popad
		push 0x1
		push 0x0
		push eax
		push ebx
		push ebp
		push ecx
		mov ecx,dword ptr ss:[esp+0x28]
		push edx
		push -0x1
		call dwIconPos
		mov eax,dword ptr ss:[esp+0x18]
		mov ecx,dword ptr ss:[esp+0x1C]
		push 0x20
		push 0x20
		push eax
		push ecx
		push 0x50FF0000
		call dwOverlay
		add esp,0x14
		jmp dwBarJump

		_water:
		popad
		push 0x1
		push 0x0
		push eax
		push ebx
		push ebp
		push ecx
		mov ecx,dword ptr ss:[esp+0x28]
		push edx
		push -0x1
		call dwIconPos
		mov eax,dword ptr ss:[esp+0x18]
		mov ecx,dword ptr ss:[esp+0x1C]
		push 0x20
		push 0x20
		push eax
		push ecx
		push 0x5000FFFF
		call dwOverlay
		add esp,0x14
		jmp dwBarJump

		_earth:
		popad
		push 0x1
		push 0x0
		push eax
		push ebx
		push ebp
		push ecx
		mov ecx,dword ptr ss:[esp+0x28]
		push edx
		push -0x1
		call dwIconPos
		mov eax,dword ptr ss:[esp+0x18]
		mov ecx,dword ptr ss:[esp+0x1C]
		push 0x20
		push 0x20
		push eax
		push ecx
		push 0x5000FF00
		call dwOverlay
		add esp,0x14
		jmp dwBarJump

		_wind:
		popad
		push 0x1
		push 0x0
		push eax
		push ebx
		push ebp
		push ecx
		mov ecx,dword ptr ss:[esp+0x28]
		push edx
		push -0x1
		call dwIconPos
		mov eax,dword ptr ss:[esp+0x18]
		mov ecx,dword ptr ss:[esp+0x1C]
		push 0x20
		push 0x20
		push eax
		push ecx
		push 0x50FFFFFF
		call dwOverlay
		add esp,0x14
		jmp dwBarJump
	}
}

void Init() {
	Hook((LPVOID)0x51826D, BagHook, 8);
	Hook((LPVOID)0x4FFCE3, BarHook, 5);
}