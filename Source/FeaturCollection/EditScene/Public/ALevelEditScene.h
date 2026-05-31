// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "ALevelEditScene.generated.h"


USTRUCT(BlueprintType)
struct FSceneObjectData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;
};

USTRUCT(BlueprintType)
struct FLevelSceneData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSceneObjectData Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSceneObjectData> Walls;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSceneObjectData> Boxs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSceneObjectData> Targets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSceneObjectData> Traps;
};

USTRUCT(BlueprintType)
struct FActorDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ActorType;
};

UCLASS()
class FEATURCOLLECTION_API AALevelEditScene : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AALevelEditScene();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ActorType; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "LevelEditScene")
	void ExportLevelConfig(TArray<AActor*> AllActor);
	
	UFUNCTION(BlueprintCallable, Category = "LevelEditScene")
	void ImportLevelConfig(FString CongfigPath);
	
	UFUNCTION(BlueprintCallable, Category = "LevelEditScene")
	void CreateActorOfType(UDataTable* ActorData, FString ActorName, FVector Location);
};

