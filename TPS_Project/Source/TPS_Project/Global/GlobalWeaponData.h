// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "GlobalWeaponData.generated.h"

/**
 * 
 */
USTRUCT()
struct TPS_PROJECT_API FGlobalWeaponData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "MeshData")
		UStaticMesh* Mesh;
};
