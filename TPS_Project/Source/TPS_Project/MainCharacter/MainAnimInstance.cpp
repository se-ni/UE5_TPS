// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h" // UGameplayStatics 헤더 파일

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

	// UGameplayStatics를 사용하여 플레이어 컨트롤러 가져오기
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (!Montage_IsPlaying(Montage))
	{
		if (MainPlayerAniState == EAniState::Attack)
		{
			if (PlayerController->IsInputKeyDown(EKeys::LeftMouseButton))
			{
				Montage_Play(AllAnimations[EAniState::Attack], 1.0f);
			}
		}

		if (MainPlayerAniState == EAniState::JumpStart)
		{
			// 플레이어가 점프 중일 때, 해당 몽타주를 2배속 재생
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
	
	// UGameplayStatics를 사용하여 플레이어 컨트롤러 가져오기
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	// 애니메이션이 종료 됐을때 State가 공격이거나 점프였으면
	if (AllAnimations[EAniState::Attack] == Anim)
	{
		if (PlayerController->IsInputKeyDown(EKeys::LeftMouseButton))
		{
			MainPlayerAniState = EAniState::Attack;
		}
		else
		{
			MainPlayerAniState = EAniState::Idle; // 공격->Idle 로 변경해주고
			Chracter->MainPlayerAniState = MainPlayerAniState;
			Montage_Play(AllAnimations[EAniState::Idle], 1.0f);
		}
	}

	if (AllAnimations[EAniState::JumpStart] == Anim)
	{
		MainPlayerAniState = EAniState::Idle; // 점프->Idle 로 변경해주고
		Chracter->MainPlayerAniState = MainPlayerAniState;
		Montage_Play(AllAnimations[EAniState::Idle], 1.0f);
	}
}