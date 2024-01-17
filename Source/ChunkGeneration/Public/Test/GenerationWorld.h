// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Enums/ChunkTypeEnum.h"

#include "Struct/ChunkData.h"


#include "GenerationWorld.generated.h"

class UProceduralMeshComponent;
class FastNoiseLite;

UCLASS()
class CHUNKGENERATION_API AGenerationWorld : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerationWorld();

	

	TObjectPtr<UProceduralMeshComponent> Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region CoreVariable

	TArray<FHChunkData> ChunkTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoreSetting)
	int WorldLength = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoreSetting)
	int WorldDeep = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoreSetting)
	int WorldHeight = 10;

	//ChunkSide ÊÇ2µÄ±¶Êý
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoreSetting)
	int ChunkSide = 100;

	

#pragma endregion

#pragma region Material

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
	TObjectPtr<UMaterialInterface> Stone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
	TObjectPtr<UMaterialInterface> Soil;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
	TObjectPtr<UMaterialInterface> Grass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
	TObjectPtr<UMaterialInterface> Iron;
#pragma endregion


#pragma region CoreFunction
	
	void InitChunkTable();

	void InitChunkTableGeometricalCenter();

	void CreateChunk(int Index, EChunkType ChunkType);
	
	void ApplyMaterial(int Index, EChunkType ChunkType);

#pragma endregion



#pragma region BluePrintCallable

public:
	UFUNCTION(BlueprintCallable)
	void CreateChunkAsIndex(FVector Index, EChunkType ChunkType);

	UFUNCTION(BlueprintCallable)
	void CreateChunkAsLocation(FVector Location, int FaceIndex, EChunkType ChunkType);


	UFUNCTION(BlueprintCallable)
	void DeleteChunkAsIndex(FVector Index);

	UFUNCTION(BlueprintCallable)
	void DeleteChunkAsLocation(FVector Location, int FaceIndex);


	UFUNCTION(BlueprintCallable)
	void ModifyChunkAsIndex(FVector Index, EChunkType ChunkType);

	UFUNCTION(BlueprintCallable)
	void ModifyChunkAsLocation(FVector Location, int FaceIndex, EChunkType ChunkType);


	UFUNCTION(BlueprintCallable)
	FHChunkData QueryChunkAsIndex(FVector Index) const;

	UFUNCTION(BlueprintCallable)
	FHChunkData QueryChunkAsLocation(FVector Location, int FaceIndex);

#pragma endregion


};
