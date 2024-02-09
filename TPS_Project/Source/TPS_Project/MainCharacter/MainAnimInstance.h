// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../Global/GlobalEnums.h"
#include "MainAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TPS_PROJECT_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EAniState MainPlayerAniState = EAniState::Idle;

	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap <EAniState, class UAnimMontage* > AllAnimations;

	UFUNCTION()
	void MontageEnd(UAnimMontage* Anim, bool _Inter);

protected:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float _DeltaTime) override;
};
