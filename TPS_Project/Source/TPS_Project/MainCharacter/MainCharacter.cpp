// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	// 컴포넌트는 언리얼의 CDO 때문에 무조건 생성자에서 만들어줘야한다
	WeaponMesh->SetupAttachment(GetMesh(), TEXT("WeaponSocket")); // 생성한 무기 매쉬를 캐릭터 매쉬에 붙여준다

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		bBindingsAdded = true;

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::S, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::D, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerTurn", EKeys::MouseX, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, -1.f));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerJumpAction"), EKeys::SpaceBar));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerAttackAction"), EKeys::LeftMouseButton));

	}

	// 키와 함수를 연결합니다.
	PlayerInputComponent->BindAxis("PlayerMoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("PlayerMoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("PlayerTurn", this, &AMainCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("PlayerTurnRate", this, &AMainCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("PlayerLookUp", this, &AMainCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("PlayerLookUpRate", this, &AMainCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("PlayerJumpAction", EInputEvent::IE_Pressed, this, &AMainCharacter::JumpAction);
	PlayerInputComponent->BindAction("PlayerAttackAction", EInputEvent::IE_Pressed, this, &AMainCharacter::AttackAction);
}

void AMainCharacter::MoveRight(float Val)
{
	if (MainPlayerAniState == EAniState::Attack || MainPlayerAniState == EAniState::JumpStart)
	{
		return;
	}


	if (Val != 0.f)
	{
		if (Controller)
		{
			FRotator const ControlSpaceRot = Controller->GetControlRotation();
			// transform to world space and add it
			// 현재 내 회전을 가져와서 y축에 해당하는 축벡터를 얻어오는 것.
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), Val);

			MainPlayerAniState = Val > 0.f ? EAniState::LeftMove : EAniState::RightMove;
			UE_LOG(LogTemp, Log, TEXT("%S(%u) %f"), __FUNCTION__, __LINE__, Val);
			return;
		}
	}
	else
	{
		if (MainPlayerAniState == EAniState::RightMove || MainPlayerAniState == EAniState::LeftMove)
		{
			MainPlayerAniState = EAniState::Idle;
		}
	}


}


void AMainCharacter::MoveForward(float Val)
{

	if (MainPlayerAniState == EAniState::Attack || MainPlayerAniState == EAniState::JumpStart)
	{
		return;
	}

	if (Val != 0.f)
	{
		if (Controller)
		{
			FRotator const ControlSpaceRot = Controller->GetControlRotation();

			// transform to world space and add it // 컨트롤러의 회전=액터의 회전
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), Val);
			

			MainPlayerAniState = Val > 0.f ? EAniState::ForwardMove : EAniState::BackwardMove;

			UE_LOG(LogTemp, Log, TEXT("%S(%u) %d"), __FUNCTION__, __LINE__, MainPlayerAniState);

			if (MainPlayerAniState == EAniState::BackwardMove)
			{
				UCharacterMovementComponent* Move = Cast<UCharacterMovementComponent>(GetMovementComponent());
				Move->MaxWalkSpeed = 500.0f;
				// UE_LOG(LogTemp, Log, TEXT("%f"), Move->MaxWalkSpeed);
			}
			
			return;
		}
	}
	else
	{
		if (MainPlayerAniState == EAniState::ForwardMove || MainPlayerAniState == EAniState::BackwardMove)
		{
			MainPlayerAniState = EAniState::Idle;
		}
	}
}


void AMainCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

void AMainCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}


void AMainCharacter::JumpAction()
{
	Jump();

	MainPlayerAniState = EAniState::JumpStart;
}

void AMainCharacter::AttackAction()
{
	MainPlayerAniState = EAniState::Attack;
}
