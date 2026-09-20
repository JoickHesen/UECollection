// Fill out your copyright notice in the Description page of Project Settings.


#include "FeaturCollection/SnakeTrack/Public/SnakeTrack.h"


// Sets default values
ASnakeTrack::ASnakeTrack()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASnakeTrack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASnakeTrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASnakeTrack::SnakeBodyUpdate()
{
	// 轨迹至少需要：
	// [0]     即将被舍弃的尾部轨迹
	// [1..N]  蛇身位置
	// [N+1]   蛇头位置
	if (SnakeTrackArray.Num() < SnakeBodyActor.Num() + 2)
	{
		return;
	}

	for (int32 i = 0; i < SnakeBodyActor.Num(); i++)
	{
		if (IsValid(SnakeBodyActor[i]))
		{
			const int32 TrackIndex = i + 1;

			if (SnakeTrackArray.IsValidIndex(TrackIndex))
			{
				SnakeBodyActor[i]->SetActorLocation(SnakeTrackArray[TrackIndex]);
			}
		}
	}
}

void ASnakeTrack::SnakeTrackUpdate(const FVector& Point)
{
	//一节蛇身的长度
	const float TrackSpacing = 20.0f;
	
	//第一次记录轨迹
	if (SnakeTrackArray.IsEmpty())
	{
		SnakeTrackArray.Add(Point);
		return;
	}

	//防止重复记录相同位置
	if (SnakeTrackArray.Last().Equals(Point, 0.1f))
	{
		return;
	}

	if (FVector::Dist(Point, SnakeTrackArray.Last()) < TrackSpacing)
	{
		return;
	}
	
	//添加蛇头的新轨迹点
	SnakeTrackArray.Add(Point);

	//最大轨迹数量为：
	//1个旧尾部点
	// +N 个蛇身点
	// +1 个蛇头点
	// 总共N+2个
	const int32 MaxTrackNum = SnakeBodyActor.Num() + 2;

	while (SnakeTrackArray.Num() > MaxTrackNum)
	{
		SnakeTrackArray.RemoveAt(0);
	}
}

void ASnakeTrack::FormatFactory()
{
	
}
