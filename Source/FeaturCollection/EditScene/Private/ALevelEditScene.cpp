// Fill out your copyright notice in the Description page of Project Settings.


#include "FeaturCollection/EditScene/Public/ALevelEditScene.h"

#include "JsonObjectConverter.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AALevelEditScene::AALevelEditScene()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AALevelEditScene::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AALevelEditScene::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AALevelEditScene::ExportLevelConfig(TArray<AActor*> AllActors)
{
	FLevelSceneData LevelSceneData;
	
	for (int i = 0; i < AllActors.Num(); i++)
	{
		FSceneObjectData ObjectData;
		ObjectData.Location = AllActors[i]->GetActorLocation();
		if (AllActors[i]->Tags.Contains("Player"))
		{
			LevelSceneData.Player = ObjectData;
		}
		if (AllActors[i]->Tags.Contains("Wall"))
		{
			LevelSceneData.Walls.Add(ObjectData);
		}
		if (AllActors[i]->Tags.Contains("Box"))
		{
			LevelSceneData.Boxs.Add(ObjectData);
		}
		if (AllActors[i]->Tags.Contains("Target"))
		{
			LevelSceneData.Targets.Add(ObjectData);
		}
		if (AllActors[i]->Tags.Contains("Tarp"))
		{
			LevelSceneData.Traps.Add(ObjectData);
		}
	}

	FString JsonString;
	if (FJsonObjectConverter::UStructToJsonObjectString(LevelSceneData,JsonString))
	{
		FString FilePath = TEXT("G:\\UEGitProject\\UEBasicModel\\PushBoxSceneConfig\\scene.json");
		FFileHelper::SaveStringToFile(JsonString, *FilePath);
		UE_LOG(LogTemp,Log,TEXT("导出配置文件成功:%s"),*FilePath);
	}
	else
	{
		UE_LOG(LogTemp,Log,TEXT("导出配置文件失败:Json转化失败"));
	}

	// // 创建一个 JSON 对象
  //   TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
  //
  //   // 序列化 Player 数据
  //   TSharedPtr<FJsonObject> PlayerObject = MakeShareable(new FJsonObject());
  //   PlayerObject->SetNumberField("X", LevelSceneData.Player.Location.X);
  //   PlayerObject->SetNumberField("Y", LevelSceneData.Player.Location.Y);
  //   PlayerObject->SetNumberField("Z", LevelSceneData.Player.Location.Z);
  //   JsonObject->SetObjectField("Player", PlayerObject);
  //
  //   // 序列化 Walls 数据
  //   TArray<TSharedPtr<FJsonValue>> WallsArray;
  //   for (const FSceneObjectData& Wall : LevelSceneData.Walls)
  //   {
  //       TSharedPtr<FJsonObject> WallObject = MakeShareable(new FJsonObject());
  //       WallObject->SetNumberField("X", Wall.Location.X);
  //       WallObject->SetNumberField("Y", Wall.Location.Y);
  //       WallObject->SetNumberField("Z", Wall.Location.Z);
  //       WallsArray.Add(MakeShareable(new FJsonValueObject(WallObject)));
  //   }
  //   JsonObject->SetArrayField("Walls", WallsArray);
  //
  //   // 序列化 Boxs 数据
  //   TArray<TSharedPtr<FJsonValue>> BoxsArray;
  //   for (const FSceneObjectData& Box : LevelSceneData.Boxs)
  //   {
  //       TSharedPtr<FJsonObject> BoxObject = MakeShareable(new FJsonObject());
  //       BoxObject->SetNumberField("X", Box.Location.X);
  //       BoxObject->SetNumberField("Y", Box.Location.Y);
  //       BoxObject->SetNumberField("Z", Box.Location.Z);
  //       BoxsArray.Add(MakeShareable(new FJsonValueObject(BoxObject)));
  //   }
  //   JsonObject->SetArrayField("Boxs", BoxsArray);
  //
  //   // 序列化 Targets 数据
  //   TArray<TSharedPtr<FJsonValue>> TargetsArray;
  //   for (const FSceneObjectData& Target : LevelSceneData.Targets)
  //   {
  //       TSharedPtr<FJsonObject> TargetObject = MakeShareable(new FJsonObject());
  //       TargetObject->SetNumberField("X", Target.Location.X);
  //       TargetObject->SetNumberField("Y", Target.Location.Y);
  //       TargetObject->SetNumberField("Z", Target.Location.Z);
  //       TargetsArray.Add(MakeShareable(new FJsonValueObject(TargetObject)));
  //   }
  //   JsonObject->SetArrayField("Targets", TargetsArray);
  //
  //   // 序列化 Traps 数据
  //   TArray<TSharedPtr<FJsonValue>> TrapsArray;
  //   for (const FSceneObjectData& Trap : LevelSceneData.Traps)
  //   {
  //       TSharedPtr<FJsonObject> TrapObject = MakeShareable(new FJsonObject());
  //       TrapObject->SetNumberField("X", Trap.Location.X);
  //       TrapObject->SetNumberField("Y", Trap.Location.Y);
  //       TrapObject->SetNumberField("Z", Trap.Location.Z);
  //       TrapsArray.Add(MakeShareable(new FJsonValueObject(TrapObject)));
  //   }
  //   JsonObject->SetArrayField("Traps", TrapsArray);
  //
  //   // 将 JSON 对象序列化为字符串
  //   FString JsonString;
  //   TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&JsonString);
  //   if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer))
  //   {
  //       // 保存为文件
  //       FString FilePath = TEXT("G:\\UEGitProject\\UEBasicModel\\PushBoxSceneConfig\\scene.json");
  //       if (FFileHelper::SaveStringToFile(JsonString, *FilePath))
  //       {
  //           UE_LOG(LogTemp, Log, TEXT("导出配置文件成功:%s"), *FilePath);
  //       }
  //       else
  //       {
  //           UE_LOG(LogTemp, Log, TEXT("保存配置文件失败"));
  //       }
  //   }
  //   else
  //   {
  //       UE_LOG(LogTemp, Log, TEXT("JSON序列化失败"));
  //   }
}

void AALevelEditScene::ImportLevelConfig(FString CongfigPath)
{
	FString ConfigContent;
	if (!FFileHelper::LoadFileToString(ConfigContent, *CongfigPath))
	{
		UE_LOG(LogTemp,Log,TEXT("读取配置文件失败"));
		return;
	}

	//解析Json字符串
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ConfigContent);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		// 获取 DataTable
		UDataTable* ActorData;
		ActorData = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/PushBoxActorDataTable.PushBoxActorDataTable'"));

		if (!ActorData)
		{
			return;
		}
		
		// 解析 Player 数据
		const TSharedPtr<FJsonObject> PlayerData = JsonObject->GetObjectField("player");
		const TSharedPtr<FJsonObject> PlayerLocation = PlayerData->GetObjectField("location");

		FVector PlayerLocationVec = FVector(
			PlayerLocation->GetNumberField("x"),
			PlayerLocation->GetNumberField("y"),
			PlayerLocation->GetNumberField("z")
		);
		CreateActorOfType(ActorData, "Player", PlayerLocationVec);

		// 解析 Wall 数据
		const TArray<TSharedPtr<FJsonValue>> WallArray = JsonObject->GetArrayField("walls");
		for (const TSharedPtr<FJsonValue>& WallValue : WallArray)
		{
			const TSharedPtr<FJsonObject> WallLocation = WallValue->AsObject()->GetObjectField("location");

			FVector WallLocationVec = FVector(
				WallLocation->GetNumberField("x"),
				WallLocation->GetNumberField("y"),
				WallLocation->GetNumberField("z")
			);
			CreateActorOfType(ActorData, "Wall", WallLocationVec);
		}

		// 解析 Box数据
		const TArray<TSharedPtr<FJsonValue>> BoxArray = JsonObject->GetArrayField("boxs");
		for (const TSharedPtr<FJsonValue>& BoxValue : BoxArray)
		{
			const TSharedPtr<FJsonObject> BoxLocation = BoxValue->AsObject()->GetObjectField("location");

			FVector BoxLocationVec = FVector(
				BoxLocation->GetNumberField("x"),
				BoxLocation->GetNumberField("y"),
				BoxLocation->GetNumberField("z")
			);
			CreateActorOfType(ActorData, "Box", BoxLocationVec);
		}

		// 解析 Target数据
		const TArray<TSharedPtr<FJsonValue>> TargetArray = JsonObject->GetArrayField("targets"); 
		for (const TSharedPtr<FJsonValue>& WallValue : WallArray)
		{
			const TSharedPtr<FJsonObject> WallLocation = WallValue->AsObject()->GetObjectField("location");

			FVector WallLocationVec = FVector(
				WallLocation->GetNumberField("x"),
				WallLocation->GetNumberField("y"),
				WallLocation->GetNumberField("z")
			);
			CreateActorOfType(ActorData, "Target", WallLocationVec);
		}

		//解析 Tarp数据
		const TArray<TSharedPtr<FJsonValue>> TarpArray = JsonObject->GetArrayField("traps"); 
		for (const TSharedPtr<FJsonValue>& TarpValue : TarpArray)
		{
			const TSharedPtr<FJsonObject> TarpLocation = TarpValue->AsObject()->GetObjectField("location");

			FVector TrapLocationVec = FVector(
				TarpLocation->GetNumberField("x"),
				TarpLocation->GetNumberField("y"),
				TarpLocation->GetNumberField("z")
			);
			CreateActorOfType(ActorData, "Tarp", TrapLocationVec);
		}
	}
}

void AALevelEditScene::CreateActorOfType(UDataTable* ActorData, FString ActorName, FVector Location)
{
	if (!ActorData)
		return;

	const FActorDataTableRow* Row = ActorData->FindRow<FActorDataTableRow>(FName(ActorName), TEXT("Lookup"));

	if (!Row)
		return;

	ActorType = Row->ActorType;
	
	UClass* CreateClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *ActorType));
	if (CreateClass)
	{
		GetWorld()->SpawnActor<AActor>(CreateClass, Location, FRotator::ZeroRotator);
	}
}