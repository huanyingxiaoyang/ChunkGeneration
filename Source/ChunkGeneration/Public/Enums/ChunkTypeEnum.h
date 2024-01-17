// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "ChunkTypeEnum.generated.h"

/**
 * 
 */
UCLASS()
class CHUNKGENERATION_API UChunkTypeEnum : public UUserDefinedEnum
{
	GENERATED_BODY()
	
};

UENUM(BlueprintType)
enum class EChunkType : uint8
{
	Null = 0,
	Stone = 1 UMETA(DisplayName = "Stone"),
	Soil = 2 UMETA(DisplayName = "Soil"),
	Grass = 3 UMETA(DisplayName = "Grass"),
	Iron = 4 UMETA(DisplayName = "Iron")
};