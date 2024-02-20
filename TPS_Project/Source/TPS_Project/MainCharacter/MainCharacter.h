// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Global/GlobalEnums.h"
#include "../Global/GlobalGameInstance.h"
#include "MainCharacter.generated.h"


UCLASS()
class TPS_PROJECT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(Category = "GameModeValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EAniState MainPlayerAniState = EAniState::Idle; // �ִϸ��̼� ����


	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<EAniState, class UAnimMontage*> AllAnimations; // �ִϸ��̼� ���¿� ���� �ִϸ��̼� ��Ÿ�ָ� �����ϴ� Map

	bool bIsAttacking = false;

protected:
	void MoveRight(float Val);
	void MoveForward(float Val);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void JumpAction();
	void AttackAction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* WeaponMesh;

	UPROPERTY(Category = "WeaponValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UStaticMesh*> WeaponArrays; // WeaponMesh ������Ʈ���� �̿��� WeaponMesh(����ƽ �Ž�) �迭

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;

	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* NowAnimation; // ���� �ִϸ��̼�
};
