// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "MainCharacter.h"

void UMainAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OnMontageBlendingOut.AddDynamic(this, &UMainAnimInstance::MontageEnd);

	AMainCharacter* Chracter = Cast<AMainCharacter>(GetOwningActor()); // ���� ���� ���͸� ���⼭ �����´�.

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	AllAnimations = Chracter->AllAnimations; // ĳ���Ϳ��� �𸮾� ������ â���� ���� �����.
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
			// �÷��̾ ���� ���� ��, �ش� ��Ÿ�ָ� 2�� ���� ���
			Montage_Play(Montage, 2.0f);
		}
		else
		{
			// �ٸ� ���¿����� �⺻������ ��Ÿ�ָ� 1������� ���
			Montage_Play(Montage, 1.0f);
		}
	}
}

void UMainAnimInstance::MontageEnd(UAnimMontage* Anim, bool _Inter) // ��Ÿ�� ��� ������ ��
{
	AMainCharacter* Chracter = Cast<AMainCharacter>(GetOwningActor());

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	// �ִϸ��̼��� ���� ������ State�� �����̰ų� ����������
	if (AllAnimations[EAniState::Attack] == Anim)
	{
		MainPlayerAniState = EAniState::Idle; // ����->Idle �� �������ְ�
		Chracter->MainPlayerAniState = MainPlayerAniState;
		Montage_Play(AllAnimations[EAniState::Idle], 1.0f);
	}

	if (AllAnimations[EAniState::JumpStart] == Anim)
	{
		MainPlayerAniState = EAniState::Idle; // ����->Idle �� �������ְ�
		Chracter->MainPlayerAniState = MainPlayerAniState;
		Montage_Play(AllAnimations[EAniState::Idle], 1.0f);
	}
}