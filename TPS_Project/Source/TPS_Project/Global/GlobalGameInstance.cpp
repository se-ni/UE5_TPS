// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalGameInstance.h"
#include "GlobalWeaponData.h"
#include "UObject/ConstructorHelpers.h"

UGlobalGameInstance::UGlobalGameInstance()
{
		// ConstructorHelpers : CDO를 제작하는 생성자 코드에서 에셋에 관련된 정보를 불러올 때 사용하는 클래스
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Global/DT_WeaponData.DT_WeaponData'");
		static ConstructorHelpers::FObjectFinder<UDataTable> MeshDataTable(*DataPath);

		if (true == MeshDataTable.Succeeded())
		{
			MeshDatas = MeshDataTable.Object;
		}
}

UGlobalGameInstance::~UGlobalGameInstance()
{

}

UStaticMesh* UGlobalGameInstance::GetMesh(FName _Name)
{
	if (nullptr == MeshDatas)
	{
		return nullptr;
	}

	FGlobalWeaponData* FindTable = MeshDatas->FindRow<FGlobalWeaponData>(_Name, _Name.ToString()); // FName에서 String으로 형변환

	if (nullptr == FindTable)
	{
		return nullptr;
	}

	return FindTable->Mesh;
}