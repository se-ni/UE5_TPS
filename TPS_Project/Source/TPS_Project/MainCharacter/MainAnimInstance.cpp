// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "MainCharacter.h"

void UMainAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OnMontageBlendingOut.AddDynamic(this, &UMainAnimInstance::MontageEnd);

	AMainCharacter* Chracter = Cast<AMainCharacter>(GetOwningActor()); // 나를 가진 액터를 여기서 가져온다.

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	AllAnimations = Chracter->AllAnimations; // 캐릭터에게 언리얼 디테일 창에서 세팅 해줬다.
}

void UMainAnimInstance::NativeUpdateAnimation(float _DeltaTime)
{
	Super::NativeUpdateAnimation(_DeltaTime);

	if (0 == AllAnimations.Num())
	{
		return;
	}

	AMainCharacter* Chracter = Cast<AMainCharacter>(GetOwningActor());

	if (nullptr == Chracter || !Chracter->IsValidLowLevel())
	{
		return;
	}

	MainPlayerAniState = Chracter->MainPlayerAniState;

	class UAnimMontage* Montage = AllAnimations[MainPlayerAniState];

	if (nullptr == Montage)
	{
		return;
	}

	if (!Montage_IsPlaying(Montage))
	{
		if (MainPlayerAniState == EAniState::JumpStart)
		{
			// 플레이어가 점프 중일 때, 해당 몽타주를 2초 동안 재생
			Montage_Play(Montage, 2.0f);
		}
		else
		{
			// 다른 상태에서는 기본적으로 몽타주를 1배속으로 재생
			Montage_Play(Montage, 1.0f);
		}
	}
}

void UMainAnimInstance::MontageEnd(UAnimMontage* Anim, bool _Inter) // 몽타주 재생 끝났을 때
{
	AMainCharacter* Chracter = Cast<AMainCharacter>(GetOwningActor());

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	// 애니메이션이 종료 됐을때 State가 공격이거나 점프였으면
	if (AllAnimations[EAniState::Attack] == Anim)
	{
		MainPlayerAniState = EAniState::Idle; // 공격->Idle 로 변경해주고
		Chracter->MainPlayerAniState = MainPlayerAniState;
		Montage_Play(AllAnimations[EAniState::Idle], 1.0f);
	}

	if (AllAnimations[EAniState::JumpStart] == Anim)
	{
		MainPlayerAniState = EAniState::Idle; // 점프->Idle 로 변경해주고
		Chracter->MainPlayerAniState = MainPlayerAniState;
		Montage_Play(AllAnimations[EAniState::Idle], 1.0f);
	}
}