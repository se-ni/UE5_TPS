// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Global/GlobalEnums.h"
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
	EAniState MainPlayerAniState = EAniState::Idle; // 애니메이션 상태


	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<EAniState, class UAnimMontage*> AllAnimations; // 애니메이션 상태에 따라 애니메이션 몽타주를 저장하는 Map

protected:
	void MoveRight(float Val);
	void MoveForward(float Val);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void JumpAction();
	void AttackAction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* WeaponMesh;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;

	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* NowAnimation; // 현재 애니메이션
};
