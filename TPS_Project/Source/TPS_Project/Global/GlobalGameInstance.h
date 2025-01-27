// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "GlobalGameInstance.generated.h"

/**
 * 게임 내에서 공통적으로(전역으로) 사용되는 변수들의 집합
 */
UCLASS()
class TPS_PROJECT_API UGlobalGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UGlobalGameInstance();
	~UGlobalGameInstance();

	UStaticMesh* GetMesh(FName _Name);

	UPROPERTY()
		UDataTable* MeshDatas;
};
