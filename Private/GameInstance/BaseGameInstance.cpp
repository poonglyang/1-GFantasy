// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/BaseGameInstance.h"
//#include "OnlineSubsystem.h"
//#include "Interfaces/OnlineIdentityInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SaveGame.h"
#include "SaveGame/GFSaveGame.h"
#include "Controller/GASWorldPlayerController.h"
#include "PlayerState/GASWorldPlayerState.h"
#include "Inventory/Crafting/CraftManagerComponent.h"
#include "Quest/QuestManagerComponent.h"
#include "Character/Customization/CustomizerComponent.h"

void UBaseGameInstance::SavePlayerData()
{
    // 1) SaveGame ��ü ����
    UGFSaveGame* SaveObj = Cast<UGFSaveGame>(
        UGameplayStatics::CreateSaveGameObject(UGFSaveGame::StaticClass())
    );
    if (!SaveObj)
    {
        UE_LOG(LogTemp, Warning, TEXT("SavePlayerData: No SaveGame "));
        return;
    }

    // 2) ���� ���� ����
    // ���� �÷��̾� ��Ʈ�ѷ� �� PlayerState ��������
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        if (AGASWorldPlayerState* PS = Cast<AGASWorldPlayerState>(PC->PlayerState))
        {
            // �г��� ����
            SaveObj->PlayerData.Nickname = PS->GetPlayerNickname();

            // ����Ʈ ������� ����
            if (UQuestManagerComponent* QuestComp = PS->FindComponentByClass<UQuestManagerComponent>())
            {
                QuestComp->SaveQuestData(SaveObj->PlayerData.QuestData);
            }
            else
            {
                UE_LOG(LogTemp, Log, TEXT("Save : No Quest"));
            }

            // Ŀ���� ����¡ ����
            if (UCustomizerComponent* CusComp = PS->FindComponentByClass<UCustomizerComponent>())
            {
                CusComp->SaveCustomizerData(SaveObj->PlayerData.CustomizerSaveData);
            }
            else
            {
                UE_LOG(LogTemp, Log, TEXT("Save : No Custom"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("Save : No PS for Quest, Custom"));
        }

        if (AGASPlayerController* MyPC = Cast<AGASPlayerController>(PC))
        {
            if (UInventoryComponent* InvenComp = MyPC->FindComponentByClass<UInventoryComponent>())
            {
                // �κ��丮 ����
                InvenComp->SaveInventoryData(SaveObj->PlayerData.InventorySaveData);
            }
            else
            {
                UE_LOG(LogTemp, Log, TEXT("Save : No Inven"));
            }

            if (UCraftManagerComponent* CraftComp = MyPC->FindComponentByClass<UCraftManagerComponent>())
            {
                // ���۹� ����
                CraftComp->SaveCraftData(SaveObj->PlayerData.CraftSaveData);
            }
            else
            {
                UE_LOG(LogTemp, Log, TEXT("Save : No Craft"));
            }
 
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("Save : No PC for Inventory, Craft"));
        }
    }

    // 3) ���Կ� ����
    if (UGameplayStatics::SaveGameToSlot(SaveObj, SlotName, UserIndex))
    {
        UE_LOG(LogTemp, Log, TEXT("SavePlayerData: Save Success"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SavePlayerData: Save Fail"));
    }
}

FString UBaseGameInstance::GetSavedNickname() const
{
    if (UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
    {
        if (UGFSaveGame* SG = Cast<UGFSaveGame>(
            UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex)))
        {
            // ����ü ���: SG->PlayerData.Nickname
            // Ȥ�� �÷� ���: SG->PlayerNickname
            return SG->PlayerData.Nickname;
        }
    }

    return TEXT("NoSave");
}

TArray<FQuestSaveData> UBaseGameInstance::GetSavedQuests() const
{
    if (UGFSaveGame* SG = LoadSaveGame())
    {
        // PlayerData.QuestData�� TArray<FQuestSaveData>
        return SG->PlayerData.QuestData;
    }
    // �ε� ���� �� �� �迭 ��ȯ
    return TArray<FQuestSaveData>();
}

TArray<FInventorySaveData> UBaseGameInstance::GetSavedInventory() const
{
    if (UGFSaveGame* SG = LoadSaveGame())
    {
        return SG->PlayerData.InventorySaveData;
    }
    // ����� �����Ͱ� ������ �� �迭 ��ȯ
    return TArray<FInventorySaveData>();
}

TArray<FCustomizerSaveData> UBaseGameInstance::GetSavedCustomizer() const
{
    if (UGFSaveGame* SG = LoadSaveGame())
    {
        return SG->PlayerData.CustomizerSaveData;
    }
    // ����� �����Ͱ� ������ �� �迭 ��ȯ
    return TArray<FCustomizerSaveData>();
}

UGFSaveGame* UBaseGameInstance::LoadSaveGame() const
{
    // ���� ���� ���� Ȯ��
    if (!UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
    {
        UE_LOG(LogTemp, Warning, TEXT("LoadSaveGame: No Slot (%s, %d)"),
            *SlotName, UserIndex);
        return nullptr;
    }

    // �ε� �õ�
    USaveGame* Loaded = UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex);
    UGFSaveGame* SG = Cast<UGFSaveGame>(Loaded);
    if (!SG)
    {
        UE_LOG(LogTemp, Error, TEXT("LoadSaveGame: LoadGameFromSlot Failed"));
    }
    return SG;
}


void UBaseGameInstance::Init()
{
    Super::Init();

    //if (bUseSteamOSS) {
    //    GetSteamOSS();
    //}
}
//
//void UBaseGameInstance::GetSteamOSS()
//{
//    // �����ڰ� ���� OSS�� ����Ѵٰ� �ϸ�
//    IOnlineSubsystem* OSS = IOnlineSubsystem::Get(); // ���� OSS�� �޾ƿ� (�⺻ ������ �����̱⿡ ������ ��
//    if (OSS) {
//        // OSS�� ������
//        UKismetSystemLibrary::PrintString(this,
//            *OSS->GetSubsystemName().ToString(),
//            true,
//            true,
//            FLinearColor(0.0f, 0.66f, 1.0f),
//            2.f); // ���� ����ý����� �������� ���
//
//        //UKismetSystemLibrary::PrintString(this, OSS->GetOnlineEnvironmentName(), true, true, FLinearColor(0.0f, 0.66f, 1.0f), 2.f);
//
//        UserOSS = OSS;  // ����
//
//        IOnlineIdentityPtr Identity = OSS->GetIdentityInterface();  // OSS���� ������ ������ ������
//
//        if (Identity.IsValid())
//        {
//            // ������ ������
//            TSharedPtr<const FUniqueNetId> Id = Identity->GetUniquePlayerId(0); // ���� ����� index
//
//            if (Id.IsValid())
//            {
//                //ID�� ������ ���
//                FString SteamIdStr = Id->ToString();
//                UKismetSystemLibrary::PrintString(this, SteamIdStr, true, true, FLinearColor(0.0f, 0.66f, 1.0f), 2.f);  // ID���
//
//                FString DisplayName = Identity->GetPlayerNickname(*Id);
//                UKismetSystemLibrary::PrintString(this, DisplayName, true, true, FLinearColor(0.0f, 0.66f, 1.0f), 2.f); // �г��� ���
//            }
//            else {
//                UKismetSystemLibrary::PrintString(this, TEXT("Id is NotValid"), true, true, FLinearColor(0.0f, 0.66f, 1.0f), 2.f);
//            }
//        }
//        else {
//            UKismetSystemLibrary::PrintString(this, TEXT("Identity is NotValid"), true, true, FLinearColor(0.0f, 0.66f, 1.0f), 2.f);
//        }
//    }
//}
//
///// <summary>
///// ID��������
///// </summary>
///// <returns>���� ID FString</returns>
//FString UBaseGameInstance::GetUserID()
//{
//    // INIT�� �ִ� �ڵ�� ����
//    IOnlineIdentityPtr Identity = UserOSS->GetIdentityInterface();
//    TSharedPtr<const FUniqueNetId> Id = Identity->GetUniquePlayerId(0); // ���� ����� index
//
//    if (Id.IsValid())
//    {
//        UKismetSystemLibrary::PrintString(this, Id->ToString());
//        return Id->ToString();
//    }
//    else {
//        return FString();
//    }
//}
//
///// <summary>
///// ���� �г��� ��������
///// </summary>
///// <returns>�г��� FString</returns>
//FString UBaseGameInstance::GetUserNickName()
//{
//    // INIT�� �ִ� �ڵ�� ����
//    IOnlineIdentityPtr Identity = UserOSS->GetIdentityInterface();
//    if (Identity.IsValid()) {
//        TSharedPtr<const FUniqueNetId> Id = Identity->GetUniquePlayerId(0); // ���� ����� index
//        if (Id.IsValid()) {
//            UKismetSystemLibrary::PrintString(this, Identity->GetPlayerNickname(*Id));
//            return Identity->GetPlayerNickname(*Id);
//        }
//        else {
//            return FString();
//        }
//    }
//    else {
//        return FString();
//    }
//}
//
///// <summary>
///// OSS��ü�� ��������
///// </summary>
///// <returns>������ �� �Է¹��� OSS</returns>
//IOnlineSubsystem* UBaseGameInstance::GetUserOSS()
//{
//	return UserOSS;
//}

void UBaseGameInstance::TravelToServer(const FString& InputIP)
{
    UE_LOG(LogTemp, Log, TEXT("BaseGameInstance : TravelToServer"));

    if (UWorld* World = GetWorld())
    {
        // FName���� ��ȯ�� ���� ���(���� �ּ�)�� �̵�
        UGameplayStatics::OpenLevel(World, FName(*InputIP), true);
    }
}
