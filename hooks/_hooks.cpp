#include "pch-il2cpp.h"
#include "_hooks.h"
#include "detours/detours.h"
#include "DirectX.h"
#include <iostream>
#include "main.h"
#include "SignatureScan.hpp"
#include "game.h"

using namespace Game;

bool HookFunction(PVOID* ppPointer, PVOID pDetour, const char* functionName) {
	if (DetourAttach(ppPointer, pDetour) != 0) {
		std::cout << "Failed to hook " << functionName << std::endl;
		return false;
	}
	//std::cout << "Hooked " << functionName << std::endl;
	return true;
}

#define HOOKFUNC(n) if (!HookFunction(&(PVOID&)n, d ## n, #n)) return;

bool UnhookFunction(PVOID* ppPointer, PVOID pDetour, const char* functionName) {
	if (DetourDetach(ppPointer, pDetour) != 0) {
		std::cout << "Failed to unhook " << functionName << std::endl;
		return false;
	}
	//std::cout << "Unhooked " << functionName << std::endl;
	return true;
}

#define UNHOOKFUNC(n) if (!UnhookFunction(&(PVOID&)n, d ## n, #n)) return;

void DetourInitilization() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	directx11 d3d11 = directx11();
	if (!d3d11.presentFunction) {
		std::cout << "Unable to retrieve IDXGISwapChain::Present method" << std::endl;
		return;
	} else {
		HMODULE steamApiModule = GetModuleHandleA("GameOverlayRenderer.dll");
		if (steamApiModule != NULL)
			oPresent = SignatureScan<D3D_PRESENT_FUNCTION>("55 8B EC 53 8B 5D ? F6 C3 01 74 ? 53 FF 75 ? FF 75 ? FF 15 ? ? ? ? 5B 5D C2", steamApiModule);
		if (!oPresent)
		{
			if (steamApiModule && MessageBox(NULL, L"Failed to hook the Steam overlay D3DPresent function.  This may cause the menu to be visible to streaming applications.  Do you wish to continue?", L"Error", MB_YESNO | MB_ICONERROR) == IDNO)
			{
#ifndef _VERSION
				SetEvent(hUnloadEvent); //Might as well unload the DLL if we're not going to render anything
#endif
				return;
			}
			oPresent = d3d11.presentFunction;
		}
	}

	HOOKFUNC(HatManager_c__GetUnlockedHats_b__11_0);
	HOOKFUNC(HatManager_c__GetUnlockedSkins_b__12_0);
	HOOKFUNC(HatManager_c__GetUnlockedPets_b__9_0);
	HOOKFUNC(HatManager_c__GetUnlockedVisors_b__15_0);
	HOOKFUNC(HatManager_c__GetUnlockedNamePlates_b__17_0);

	HOOKFUNC(SceneManager_Internal_ActiveSceneChanged);
	HOOKFUNC(PlayerControl_FixedUpdate);
	HOOKFUNC(PlayerControl_RpcSyncSettings);
	HOOKFUNC(PlayerControl_Shapeshift);
	HOOKFUNC(PlayerControl_ProtectPlayer);
	HOOKFUNC(MeetingHud_Update);
	HOOKFUNC(ShipStatus_CalculateLightRadius);
	HOOKFUNC(AirshipStatus_CalculateLightRadius);
	HOOKFUNC(ShipStatus_OnEnable);
	HOOKFUNC(PolusShipStatus_OnEnable);
	HOOKFUNC(AirshipStatus_OnEnable);
	HOOKFUNC(Vent_CanUse);
	HOOKFUNC(Vent_EnterVent);
	HOOKFUNC(Vent_ExitVent);
	HOOKFUNC(StatsManager_get_AmBanned);
	HOOKFUNC(StatsManager_get_BanMinutesLeft);
	HOOKFUNC(StatsManager_get_BanPoints);
	HOOKFUNC(AutoOpenDoor_DoUpdate);
	HOOKFUNC(ChatBubble_SetName);
	HOOKFUNC(ChatController_AddChat);
	HOOKFUNC(ChatController_SetVisible);
	HOOKFUNC(HudManager_ShowMap);
	HOOKFUNC(HudManager_Update);
	HOOKFUNC(Camera_ScreenToWorldPoint);
	HOOKFUNC(KeyboardJoystick_Update);
	HOOKFUNC(ScreenJoystick_FixedUpdate);
	HOOKFUNC(PlainDoor_SetDoorway);
	HOOKFUNC(GameOptionsData_Deserialize);
	HOOKFUNC(GameOptionsData_Deserialize_1);
	HOOKFUNC(PlayerControl_MurderPlayer);
	HOOKFUNC(PlayerControl_CompleteTask);
	HOOKFUNC(PlayerControl_CmdReportDeadBody);
	HOOKFUNC(PlayerControl_ReportDeadBody);
	HOOKFUNC(RoleManager_AssignRolesFromList);
	HOOKFUNC(PlayerControl_HandleRpc);
	HOOKFUNC(Renderer_set_enabled);
	HOOKFUNC(MeetingHud_Awake);
	HOOKFUNC(MeetingHud_Close);
	HOOKFUNC(InnerNetClient_Update);
	HOOKFUNC(AmongUsClient_OnPlayerLeft);
	HOOKFUNC(CustomNetworkTransform_SnapTo);
	HOOKFUNC(Constants_ShouldFlipSkeld);
	HOOKFUNC(LobbyBehaviour_Start);
	HOOKFUNC(GameObject_SetActive);
	HOOKFUNC(NoShadowBehaviour_LateUpdate);
	HOOKFUNC(FollowerCamera_Update);
	HOOKFUNC(DoorBreakerGame_Start);
	HOOKFUNC(DoorCardSwipeGame_Begin);
	HOOKFUNC(Debug_Log);
	HOOKFUNC(Debug_LogError);
	HOOKFUNC(Debug_LogException);
	HOOKFUNC(Debug_LogWarning);
	HOOKFUNC(VersionShower_Start);
	HOOKFUNC(EOSManager_LoginFromAccountTab);
	HOOKFUNC(EOSManager_LoginForKWS);
	HOOKFUNC(EOSManager_InitializePlatformInterface);
	HOOKFUNC(EOSManager_BeginLoginFlow);
	HOOKFUNC(EOSManager_ReallyBeginFlow);
	HOOKFUNC(EOSManager_IsFreechatAllowed);
	HOOKFUNC(ChatController_Update);
	HOOKFUNC(InnerNetClient_EnqueueDisconnect);
	HOOKFUNC(PlayerPhysics_FixedUpdate);

	if (!HookFunction(&(PVOID&)oPresent, dPresent, "D3D_PRESENT_FUNCTION")) return;

	DetourTransactionCommit();
}

void DetourUninitialization()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	UNHOOKFUNC(HatManager_c__GetUnlockedHats_b__11_0);
	UNHOOKFUNC(HatManager_c__GetUnlockedSkins_b__12_0);
	UNHOOKFUNC(HatManager_c__GetUnlockedPets_b__9_0);
	UNHOOKFUNC(HatManager_c__GetUnlockedVisors_b__15_0);
	UNHOOKFUNC(HatManager_c__GetUnlockedNamePlates_b__17_0);

	UNHOOKFUNC(PlayerPhysics_FixedUpdate);
	UNHOOKFUNC(GameObject_SetActive);
	UNHOOKFUNC(SceneManager_Internal_ActiveSceneChanged);
	UNHOOKFUNC(PlayerControl_FixedUpdate);
	UNHOOKFUNC(PlayerControl_RpcSyncSettings);
	UNHOOKFUNC(PlayerControl_Shapeshift);
	UNHOOKFUNC(PlayerControl_ProtectPlayer);
	UNHOOKFUNC(MeetingHud_Update);
	UNHOOKFUNC(AirshipStatus_CalculateLightRadius);
	UNHOOKFUNC(ShipStatus_CalculateLightRadius);
	UNHOOKFUNC(ShipStatus_OnEnable);
	UNHOOKFUNC(PolusShipStatus_OnEnable);
	UNHOOKFUNC(AirshipStatus_OnEnable);
	UNHOOKFUNC(Vent_CanUse);
	UNHOOKFUNC(Vent_EnterVent);
	UNHOOKFUNC(Vent_ExitVent);
	UNHOOKFUNC(StatsManager_get_AmBanned);
	UNHOOKFUNC(StatsManager_get_BanMinutesLeft);
	UNHOOKFUNC(StatsManager_get_BanPoints);
	UNHOOKFUNC(AutoOpenDoor_DoUpdate);
	UNHOOKFUNC(ChatBubble_SetName);
	UNHOOKFUNC(ChatController_AddChat);
	UNHOOKFUNC(ChatController_SetVisible);
	UNHOOKFUNC(HudManager_ShowMap);
	UNHOOKFUNC(HudManager_Update);
	UNHOOKFUNC(ScreenJoystick_FixedUpdate);
	UNHOOKFUNC(KeyboardJoystick_Update);
	UNHOOKFUNC(Camera_ScreenToWorldPoint);
	UNHOOKFUNC(PlainDoor_SetDoorway);
	UNHOOKFUNC(GameOptionsData_Deserialize);
	UNHOOKFUNC(GameOptionsData_Deserialize_1);
	UNHOOKFUNC(PlayerControl_MurderPlayer);
	UNHOOKFUNC(PlayerControl_CompleteTask);
	UNHOOKFUNC(PlayerControl_CmdReportDeadBody);
	UNHOOKFUNC(PlayerControl_ReportDeadBody);
	UNHOOKFUNC(RoleManager_AssignRolesFromList);
	UNHOOKFUNC(PlayerControl_HandleRpc);
	UNHOOKFUNC(Renderer_set_enabled);
	UNHOOKFUNC(MeetingHud_Awake);
	UNHOOKFUNC(MeetingHud_Close);
	UNHOOKFUNC(InnerNetClient_Update);
	UNHOOKFUNC(AmongUsClient_OnPlayerLeft);
	UNHOOKFUNC(CustomNetworkTransform_SnapTo);
	UNHOOKFUNC(Constants_ShouldFlipSkeld);
	UNHOOKFUNC(LobbyBehaviour_Start);
	UNHOOKFUNC(NoShadowBehaviour_LateUpdate);
	UNHOOKFUNC(FollowerCamera_Update);
	UNHOOKFUNC(DoorBreakerGame_Start);
	UNHOOKFUNC(DoorCardSwipeGame_Begin);
	UNHOOKFUNC(Debug_Log);
	UNHOOKFUNC(Debug_LogError);
	UNHOOKFUNC(Debug_LogException);
	UNHOOKFUNC(Debug_LogWarning);
	UNHOOKFUNC(VersionShower_Start);
	UNHOOKFUNC(EOSManager_LoginFromAccountTab);
	UNHOOKFUNC(EOSManager_LoginForKWS);
	UNHOOKFUNC(EOSManager_InitializePlatformInterface);
	UNHOOKFUNC(EOSManager_BeginLoginFlow);
	UNHOOKFUNC(EOSManager_ReallyBeginFlow);
	UNHOOKFUNC(EOSManager_IsFreechatAllowed);
	UNHOOKFUNC(ChatController_Update);
	UNHOOKFUNC(InnerNetClient_EnqueueDisconnect);

	if (DetourDetach(&(PVOID&)oPresent, dPresent) != 0) return;

	DetourTransactionCommit();
	DirectX::Shutdown();
}