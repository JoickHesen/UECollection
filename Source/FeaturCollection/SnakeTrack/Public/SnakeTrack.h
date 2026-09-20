// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeTrack.generated.h"


UCLASS()
class FEATURCOLLECTION_API ASnakeTrack : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASnakeTrack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> SnakeTrackArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> SnakeBodyActor;

	UFUNCTION(BlueprintCallable)
	void SnakeBodyUpdate();

	//更新蛇轨迹，并返回蛇头下一坐标，蛇速度
	UFUNCTION(BlueprintCallable)
	void SnakeTrackUpdate(const FVector& Point);

	UFUNCTION(BlueprintCallable)
	void FormatFactory();
};
