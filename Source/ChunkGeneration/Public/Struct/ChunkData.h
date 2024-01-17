// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"

#include "Enums/ChunkTypeEnum.h"
#include "Struct/ChunkQuery.h"

#include "ChunkData.generated.h"

/**
 * 
 */
UCLASS()
class CHUNKGENERATION_API UChunkData : public UUserDefinedStruct
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
struct FHChunkData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Index ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EChunkType ChunkType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector GeometricalCenter;

	
};
