// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "ChunkQuery.generated.h"

/**
 * 
 */
UCLASS()
class CHUNKGENERATION_API UChunkQuery : public UUserDefinedStruct
{
	GENERATED_BODY()
	
};


struct FChunkQuery
{
	

	bool bForwardHas = false;
	bool bBackHas = false;
	bool bTopHas = false;
	bool bBottomHas = false;
	bool bLeftHas = false;
	bool bRightHas = false;
};