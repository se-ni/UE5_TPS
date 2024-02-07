// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GlobalEnums.generated.h"

UENUM(BlueprintType)
enum class EAniState : uint8
{
	None,
	Idle, //0
	LeftMove,
	RightMove,
	ForwardMove,
	BackwardMove,
	JumpStart,
	Attack, //6
	Patrol,
	Death,
	Hit,
	Return,
};