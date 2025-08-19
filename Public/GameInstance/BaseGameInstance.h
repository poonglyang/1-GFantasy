// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

/**
 * 
 */
//class IOnlineSubsystem;	// ���漱��

UCLASS()
class GFANTASY_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// ���̺�ε� �Լ�
	UFUNCTION(BlueprintCallable, Category = "Save")
	void SavePlayerData();

	UFUNCTION(BlueprintCallable, Category = "Save")
	FString GetSavedNickname() const;

	UFUNCTION(BlueprintCallable, Category = "Save")
	TArray<FQuestSaveData> GetSavedQuests() const;

	UFUNCTION(BlueprintCallable, Category = "Save")
	TArray<FInventorySaveData> GetSavedInventory() const;

	UFUNCTION(BlueprintCallable, Category = "Save")
	TArray<FCustomizerSaveData> GetSavedCustomizer() const;

private:
	// ���ο��� �������� SaveGame�� �ε��Ͽ� ��ȯ�ϴ� ����
	class UGFSaveGame* LoadSaveGame() const;

	// ���� �̸�, �ε��� (�ʿ�� �����Ϳ��� ���� ����)
	UPROPERTY(EditDefaultsOnly, Category = "Save")
	FString SlotName = TEXT("PlayerSaveSlot");

	UPROPERTY(EditDefaultsOnly, Category = "Save")
	uint32 UserIndex = 0;





	/// <summary>
	/// �⺻ ���� �Լ� �������̵� ���� OSS�� �������� ���� �߰���
	/// </summary>
	virtual void Init() override;
//
//	void GetSteamOSS();
//
//	/// <summary>
//	/// ID��������
//	/// </summary>
//	/// <returns>���� ID FString</returns>
//	UFUNCTION(BlueprintCallable, BlueprintPure)
//	FString GetUserID();
//
//	/// <summary>
//	/// ���� �г��� ��������
//	/// </summary>
//	/// <returns>�г��� FString</returns>
//	UFUNCTION(BlueprintCallable, BlueprintPure)
//	FString GetUserNickName();
//
//	/// <summary>
//	/// OSS��ü�� ��������
//	/// </summary>
//	/// <returns>������ �� �Է¹��� OSS</returns>
//	IOnlineSubsystem* GetUserOSS();
//
//public:
//	/// <summary>
//	/// �¶��� ���� �ý����� ������� �ʰ� ���� ���� ������
//	/// </summary>
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OSS")
//	bool bUseSteamOSS = false;
public:

	// TitleWidget���� ȣ���ؼ� ������ �̵��ϴ� �Լ�
	UFUNCTION(BlueprintCallable)
	void TravelToServer(const FString& InputIP);

//protected:
//	IOnlineSubsystem* UserOSS;
};
