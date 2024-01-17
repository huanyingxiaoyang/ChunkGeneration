// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/GenerationWorld.h"

#include "FastNoiseLite.h"
#include "DebugHelper/DebugHelper.h"
#include<math.h>

#include "ProceduralMeshComponent.h"

// Sets default values
AGenerationWorld::AGenerationWorld()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>("Mesh");
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void AGenerationWorld::BeginPlay()
{
	Super::BeginPlay();
	/*ChunkTable.SetNum(100);
	ChunkTable[0].GeometricalCenter = FVector(0, 0, 0);
	CreateChunk(0,EChunkType::Stone);
	ChunkTable[3].GeometricalCenter = FVector(300, 0, 0);
	CreateChunk(3, EChunkType::Stone);
	ChunkTable[5 + 10].GeometricalCenter = FVector(500, 100, 0);
	CreateChunk(15, EChunkType::Stone);*/
	InitChunkTable();
	CreateChunk(1, EChunkType::Stone);
		CreateChunk(0, EChunkType::Stone);

	CreateChunk(3, EChunkType::Stone);
	CreateChunk(2, EChunkType::Stone);
	CreateChunk(4, EChunkType::Stone);
	CreateChunk(6, EChunkType::Stone);

	CreateChunk(8, EChunkType::Stone);
	CreateChunk(9, EChunkType::Stone);
	
	
}


#pragma region CoreFunction
	
void AGenerationWorld::InitChunkTable()
{
	ChunkTable.SetNum(WorldLength * WorldDeep * WorldHeight, false);

	InitChunkTableGeometricalCenter();
}

void AGenerationWorld::InitChunkTableGeometricalCenter() 
{
	for (int z = 0; z < WorldHeight; ++z)
	{
		
		for (int y = 0; y < WorldDeep; ++y)
		{
			
			for (int x = 0; x < WorldLength; ++x)
			{
				ChunkTable[x + y * WorldLength + z * WorldLength * WorldDeep].GeometricalCenter.X = x * ChunkSide;

				ChunkTable[x + y * WorldLength + z * WorldLength * WorldDeep].GeometricalCenter.Y = y * ChunkSide;

				ChunkTable[x + y * WorldLength + z * WorldLength * WorldDeep].GeometricalCenter.Z = z * ChunkSide;
			}
			
		}
		
	}
}



void AGenerationWorld::CreateChunk(int Index, EChunkType ChunkType)
{ 
	TArray<FVector> Vertices;
	TArray<int32> Triangles;

	const TArray<FVector> Normals;
	const TArray<FVector2D> UV0;
	const TArray<FColor> VertexColors;
	const TArray<FProcMeshTangent> Tangents;

#pragma region Write Vertices and Triangles

	//caculate vertices
	int HalfChunkSide = ChunkSide / 2;
	FVector V0 = ChunkTable[Index].GeometricalCenter;
	V0.X -= HalfChunkSide;
	V0.Y += HalfChunkSide;
	V0.Z -= HalfChunkSide;

	FVector V1 = ChunkTable[Index].GeometricalCenter;
	V1.X += HalfChunkSide;
	V1.Y += HalfChunkSide;
	V1.Z -= HalfChunkSide;

	FVector V2 = ChunkTable[Index].GeometricalCenter;
	V2.X -= HalfChunkSide;
	V2.Y -= HalfChunkSide;
	V2.Z -= HalfChunkSide;

	FVector V3 = ChunkTable[Index].GeometricalCenter;
	V3.X += HalfChunkSide;
	V3.Y -= HalfChunkSide;
	V3.Z -= HalfChunkSide;

	FVector V4 = ChunkTable[Index].GeometricalCenter;
	V4.X -= HalfChunkSide;
	V4.Y += HalfChunkSide;
	V4.Z += HalfChunkSide;

	FVector V5 = ChunkTable[Index].GeometricalCenter;
	V5.X += HalfChunkSide;
	V5.Y += HalfChunkSide;
	V5.Z += HalfChunkSide;

	FVector V6 = ChunkTable[Index].GeometricalCenter;
	V6.X -= HalfChunkSide;
	V6.Y -= HalfChunkSide;
	V6.Z += HalfChunkSide;

	FVector V7 = ChunkTable[Index].GeometricalCenter;
	V7.X += HalfChunkSide;
	V7.Y -= HalfChunkSide;
	V7.Z += HalfChunkSide;

	Vertices.Emplace(V0);
	Vertices.Emplace(V1);
	Vertices.Emplace(V2);
	Vertices.Emplace(V3);
	Vertices.Emplace(V4);
	Vertices.Emplace(V5);
	Vertices.Emplace(V6);
	Vertices.Emplace(V7);

	//write triangles
	//back
	Triangles.Emplace(0);
	Triangles.Emplace(1);
	Triangles.Emplace(4);

	Triangles.Emplace(5);
	Triangles.Emplace(4);
	Triangles.Emplace(1);

	//top
	Triangles.Emplace(4);
	Triangles.Emplace(5);
	Triangles.Emplace(6);

	Triangles.Emplace(7);
	Triangles.Emplace(6);
	Triangles.Emplace(5);

	//bottom
	Triangles.Emplace(0);
	Triangles.Emplace(2);
	Triangles.Emplace(1);

	Triangles.Emplace(3);
	Triangles.Emplace(1);
	Triangles.Emplace(2);

	//left
	Triangles.Emplace(0);
	Triangles.Emplace(4);
	Triangles.Emplace(2);

	Triangles.Emplace(6);
	Triangles.Emplace(2);
	Triangles.Emplace(4);

	//right
	Triangles.Emplace(1);
	Triangles.Emplace(3);
	Triangles.Emplace(5);

	Triangles.Emplace(7);
	Triangles.Emplace(5);
	Triangles.Emplace(3);

	
	
	
#pragma endregion


	Mesh->CreateMeshSection(Index, Vertices, Triangles, Normals, UV0, VertexColors, Tangents, true);
	

	ApplyMaterial(Index, ChunkType);
}

void AGenerationWorld::ApplyMaterial(int Index, EChunkType ChunkType)
{
	ChunkTable[Index].ChunkType = ChunkType;

	UMaterialInterface* MaterialTemp = Stone;

#pragma region Selete Material

	switch (ChunkType)
	{
	case EChunkType::Null:
		
		break;
	case EChunkType::Stone:
		MaterialTemp = Stone;
		break;
	case EChunkType::Soil:
		MaterialTemp = Soil;
		break;
	case EChunkType::Grass:
		MaterialTemp = Grass;
		break;
	case EChunkType::Iron:
		MaterialTemp = Iron;
		break;
	default:
		break;
	}

#pragma endregion

	Mesh->SetMaterial(Index, MaterialTemp);
}


#pragma endregion


#pragma region BluePrintCallable



void AGenerationWorld::CreateChunkAsIndex(FVector Index, EChunkType ChunkType)
{
	int IndexToCreate = Index.X + Index.Y * WorldLength + Index.Z * WorldLength * WorldDeep;
	CreateChunk(IndexToCreate, ChunkType);
}

void AGenerationWorld::CreateChunkAsLocation(FVector Location, int FaceIndex, EChunkType ChunkType)
{
	FVector RootLocation = GetActorLocation();
	//original location offset
	RootLocation.X -= ChunkSide / 2;
	RootLocation.Y -= ChunkSide / 2;
	RootLocation.Z -= ChunkSide / 2;


	Location.X -= RootLocation.X;
	Location.Y -= RootLocation.Y;
	Location.Z -= RootLocation.Z;


	//caculate offset (when x or y or z eqal n*ChunkSide)
#pragma region CaculateOffset 

	int RemainderFaceIndex = fmod(FaceIndex, 10);
	switch (RemainderFaceIndex)
	{
	case 0:
		Location.Y -= 1;
		Location.Y += ChunkSide;
		break;

	case 1:
		Location.Y -= 1;
		Location.Y += ChunkSide;
		break;

	case 2:
		Location.Z -= 1;
		Location.Z += ChunkSide;
		break;

	case 3:
		Location.Z -= 1;
		Location.Z += ChunkSide;
		break;

	case 4:
		Location.Z += 1;
		Location.Z -= ChunkSide;
		break;

	case 5:
		Location.Z += 1;
		Location.Z -= ChunkSide;
		break;

	case 6:
		Location.X += 1;
		Location.X -= ChunkSide;
		break;

	case 7:
		Location.X += 1;
		Location.X -= ChunkSide;
		break;

	case 8:
		Location.X -= 1;
		Location.X += ChunkSide;
		break;

	case 9:
		Location.X -= 1;
		Location.X += ChunkSide;
		break;
	default:
		break;
	}

#pragma endregion


	int IndexX = floor((Location.X / ChunkSide));
	int IndexY = floor((Location.Y / ChunkSide));
	int IndexZ = floor((Location.Z / ChunkSide));



	FVector IndexToCreate;
	IndexToCreate.X = IndexX;
	IndexToCreate.Y = IndexY;
	IndexToCreate.Z = IndexZ;

	CreateChunkAsIndex(IndexToCreate, ChunkType);
}

void AGenerationWorld::DeleteChunkAsIndex(FVector Index)
{
	int IndexToDelete = Index.X + Index.Y * WorldLength + Index.Z * WorldLength * WorldDeep;
	Mesh->ClearMeshSection(IndexToDelete);

}

void AGenerationWorld::DeleteChunkAsLocation(FVector Location, int FaceIndex)
{
	FVector RootLocation = GetActorLocation();
	//original location offset
	RootLocation.X -= ChunkSide / 2;
	RootLocation.Y -= ChunkSide / 2;
	RootLocation.Z -= ChunkSide / 2;


	Location.X -= RootLocation.X;
	Location.Y -= RootLocation.Y;
	Location.Z -= RootLocation.Z;

	
	//caculate offset (when x or y or z eqal n*ChunkSide)
#pragma region CaculateOffset 
	
	int RemainderFaceIndex = fmod(FaceIndex, 10);
	switch (RemainderFaceIndex)
	{
		case 0:
			Location.Y -= 1;
			break;

		case 1:
			Location.Y -= 1;
			break;

		case 2:
			Location.Z -= 1;
			break;

		case 3:
			Location.Z -= 1;
			break;
		case 4:
			Location.Z += 1;
			break;

		case 5:
			Location.Z += 1;
			break;
		
		case 6:
			Location.X += 1;
			break;

		case 7:
			Location.X += 1;
			break;

		case 8:
			Location.X -= 1;
			break;

		case 9:
			Location.X -= 1;
			break;
	default:
		break;
	}
	
#pragma endregion


	int IndexX = floor((Location.X / ChunkSide));
	int IndexY = floor((Location.Y / ChunkSide));
	int IndexZ = floor((Location.Z / ChunkSide));
	

	
	FVector IndexToDelete;
	IndexToDelete.X = IndexX;
	IndexToDelete.Y = IndexY;
	IndexToDelete.Z = IndexZ;

	DeleteChunkAsIndex(IndexToDelete);

}

void AGenerationWorld::ModifyChunkAsIndex(FVector Index, EChunkType ChunkType)
{
	int IndexToModify = Index.X + Index.Y * WorldLength + Index.Z * WorldLength * WorldDeep;
	ApplyMaterial( IndexToModify, ChunkType);
}

void AGenerationWorld::ModifyChunkAsLocation(FVector Location, int FaceIndex, EChunkType ChunkType)
{
	FVector RootLocation = GetActorLocation();
	//original location offset
	RootLocation.X -= ChunkSide / 2;
	RootLocation.Y -= ChunkSide / 2;
	RootLocation.Z -= ChunkSide / 2;


	Location.X -= RootLocation.X;
	Location.Y -= RootLocation.Y;
	Location.Z -= RootLocation.Z;


	//caculate offset (when x or y or z eqal n*ChunkSide)
#pragma region CaculateOffset 

	int RemainderFaceIndex = fmod(FaceIndex, 10);
	switch (RemainderFaceIndex)
	{
	case 0:
		Location.Y -= 1;
		break;

	case 1:
		Location.Y -= 1;
		break;

	case 2:
		Location.Z -= 1;
		break;

	case 3:
		Location.Z -= 1;
		break;
	case 4:
		Location.Z += 1;
		break;

	case 5:
		Location.Z += 1;
		break;

	case 6:
		Location.X += 1;
		break;

	case 7:
		Location.X += 1;
		break;

	case 8:
		Location.X -= 1;
		break;

	case 9:
		Location.X -= 1;
		break;
	default:
		break;
	}

#pragma endregion


	int IndexX = floor((Location.X / ChunkSide));
	int IndexY = floor((Location.Y / ChunkSide));
	int IndexZ = floor((Location.Z / ChunkSide));



	FVector IndexToModify;
	IndexToModify.X = IndexX;
	IndexToModify.Y = IndexY;
	IndexToModify.Z = IndexZ;

	ModifyChunkAsIndex(IndexToModify,  ChunkType);
}

FHChunkData AGenerationWorld::QueryChunkAsIndex(FVector Index) const
{
	int IndexToQuery = Index.X + Index.Y * WorldLength + Index.Z * WorldLength * WorldDeep;
	return ChunkTable[IndexToQuery];
}

FHChunkData AGenerationWorld::QueryChunkAsLocation(FVector Location, int FaceIndex)
{
	FVector RootLocation = GetActorLocation();
	//original location offset
	RootLocation.X -= ChunkSide / 2;
	RootLocation.Y -= ChunkSide / 2;
	RootLocation.Z -= ChunkSide / 2;


	Location.X -= RootLocation.X;
	Location.Y -= RootLocation.Y;
	Location.Z -= RootLocation.Z;


	//caculate offset (when x or y or z eqal n*ChunkSide)
#pragma region CaculateOffset 

	int RemainderFaceIndex = fmod(FaceIndex, 10);
	switch (RemainderFaceIndex)
	{
	case 0:
		Location.Y -= 1;
		break;

	case 1:
		Location.Y -= 1;
		break;

	case 2:
		Location.Z -= 1;
		break;

	case 3:
		Location.Z -= 1;
		break;
	case 4:
		Location.Z += 1;
		break;

	case 5:
		Location.Z += 1;
		break;

	case 6:
		Location.X += 1;
		break;

	case 7:
		Location.X += 1;
		break;

	case 8:
		Location.X -= 1;
		break;

	case 9:
		Location.X -= 1;
		break;
	default:
		break;
	}

#pragma endregion


	int IndexX = floor((Location.X / ChunkSide));
	int IndexY = floor((Location.Y / ChunkSide));
	int IndexZ = floor((Location.Z / ChunkSide));



	FVector IndexToQuery;
	IndexToQuery.X = IndexX;
	IndexToQuery.Y = IndexY;
	IndexToQuery.Z = IndexZ;
	return QueryChunkAsIndex(IndexToQuery);
}

#pragma endregion


