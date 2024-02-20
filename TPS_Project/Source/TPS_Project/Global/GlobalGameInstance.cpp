// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalGameInstance.h"
#include "GlobalWeaponData.h"
#include "UObject/ConstructorHelpers.h"

UGlobalGameInstance::UGlobalGameInstance()
{
		// ConstructorHelpers : CDO�� �����ϴ� ������ �ڵ忡�� ���¿� ���õ� ������ �ҷ��� �� ����ϴ� Ŭ����
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

	FGlobalWeaponData* FindTable = MeshDatas->FindRow<FGlobalWeaponData>(_Name, _Name.ToString()); // FName���� String���� ����ȯ

	if (nullptr == FindTable)
	{
		return nullptr;
	}

	return FindTable->Mesh;
}