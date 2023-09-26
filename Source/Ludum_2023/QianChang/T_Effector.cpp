// Fill out your copyright notice in the Description page of Project Settings.

#include "T_Effector.h"
#include "Components/BillboardComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AT_Effector::AT_Effector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = BillBoardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("AsRootComponent"));
	BillBoardComponent->bHiddenInGame = false;
	SphereMax = CreateDefaultSubobject<USphereComponent>(TEXT("SphereMax"));
	SphereMin = CreateDefaultSubobject<USphereComponent>(TEXT("SphereMin"));
	SphereMax->SetupAttachment(RootComponent);
	SphereMin->SetupAttachment(RootComponent);
	SphereMax->InitSphereRadius(1);
	SphereMin->InitSphereRadius(1);
	FVector LocalMax = { DistanceMax,DistanceMax,DistanceMax };
	SphereMax->SetWorldScale3D(LocalMax);
	SphereMax->bHiddenInGame = false;
	SphereMax->SetCollisionProfileName(TEXT("NoCollision"));
	FVector LocalMin = { DistanceMin,DistanceMin,DistanceMin };
	SphereMin->SetWorldScale3D(LocalMin);
	SphereMin->bHiddenInGame = false;
	SphereMin->SetCollisionProfileName(TEXT("NoCollision"));
	if (bHelpersVisualInGame)
	{
		BillBoardComponent->bHiddenInGame = false;
		SphereMax->bHiddenInGame = false;
		SphereMin->bHiddenInGame = false;
	}
	else
	{
		BillBoardComponent->bHiddenInGame = true;
		SphereMax->bHiddenInGame = true;
		SphereMin->bHiddenInGame = true;
	}

}

// Called when the game starts or when spawned
void AT_Effector::BeginPlay()
{
	Super::BeginPlay();
	ClearArrays();
	StoreTransformValue(DefaultActors);
}

// Called every frame
void AT_Effector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bPauseSimuation)
	{
		if (bON_OFF)
		{
			for (int32 i = 0; i < DefaultActors.Num(); ++i)
			{
				if (bLocation)
				{
					TransformLocation(DefaultActors[i], i);
				}
				if (bRotation)
				{
					TransformRotation(DefaultActors[i], i);
				}
				if (bScale)
				{
					TransformScale(DefaultActors[i], i);
				}
			}
		}
		else
		{
			ResetToDefaultValue();
		}
	}
}


void AT_Effector::ClearArrays()
{
	DefaultRelativeScale.Empty();
	DefaultLocation.Empty();
	DefaultRotation.Empty();
	RandomDirection.Empty();
}

void AT_Effector::StoreTransformValue(TArray<AActor*>& OutActors)
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), Tag, OutActors);
	for (AActor* Actor : OutActors)
	{
		Actor->GetRootComponent()->SetMobility(EComponentMobility::Movable);
		FVector Pos = Actor->GetActorLocation();
		FRotator Rot = Actor->GetActorRotation();
		FVector Scale = Actor->GetActorRelativeScale3D();
		DefaultLocation.Add(Pos);
		DefaultRotation.Add(Rot);
		DefaultRelativeScale.Add(Scale);
		bool bLocalBool = UKismetMathLibrary::RandomBool();
		int32 LocalInt = UKismetMathLibrary::SelectInt(1, -1, bLocalBool);
		RandomDirection.Add(LocalInt);
	}
}

void AT_Effector::ResetToDefaultValue()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), Tag, DefaultActors);
	for (int32 i = 0; i < DefaultActors.Num(); ++i)
	{
		DefaultActors[i]->SetActorRotation(DefaultRotation[i]);
		DefaultActors[i]->SetActorLocation(DefaultLocation[i]);
		DefaultActors[i]->SetActorRelativeScale3D(DefaultRelativeScale[i]);
	}
}

void AT_Effector::TransformLocation(AActor* ArrayElement, int32 ArrayIndex)
{
	if (!bInvertLocation)
	{
		if (!bRandomPosDirection)
		{
			float Distance = UKismetMathLibrary::Vector_Distance(GetActorLocation(), DefaultLocation[ArrayIndex]);
			float Offset = UKismetMathLibrary::FClamp(Distance, DistanceMin, DistanceMax);
			float BaseOffset = UKismetMathLibrary::MapRangeClamped(Offset, DistanceMin, DistanceMax, MinLocation, MaxLocation);
			FVector BaseLocation = UKismetMathLibrary::MakeVector(UKismetMathLibrary::Multiply_FloatFloat(BaseOffset, Lot_X_Mul), UKismetMathLibrary::Multiply_FloatFloat(BaseOffset, Lot_Y_Mul), UKismetMathLibrary::Multiply_FloatFloat(BaseOffset, Lot_Z_Mul));
			float Lot_X = UKismetMathLibrary::Add_FloatFloat(DefaultLocation[ArrayIndex].X, BaseLocation.X);
			float Lot_Y = UKismetMathLibrary::Add_FloatFloat(DefaultLocation[ArrayIndex].Y, BaseLocation.Y);
			float Lot_Z = UKismetMathLibrary::Add_FloatFloat(DefaultLocation[ArrayIndex].Z, BaseLocation.Z);
			ArrayElement->SetActorLocation(FVector{ Lot_X,Lot_Y,Lot_Z });
		}
		else
		{
			float Distance = UKismetMathLibrary::Vector_Distance(GetActorLocation(), DefaultLocation[ArrayIndex]);
			float Offset = UKismetMathLibrary::FClamp(Distance, DistanceMin, DistanceMax);
			float BaseOffset = UKismetMathLibrary::MapRangeClamped(Offset, DistanceMin, DistanceMax, MinLocation, MaxLocation);
			FVector BaseLocation = UKismetMathLibrary::MakeVector(UKismetMathLibrary::Multiply_FloatFloat(BaseOffset, Lot_X_Mul), UKismetMathLibrary::Multiply_FloatFloat(BaseOffset, Lot_Y_Mul), UKismetMathLibrary::Multiply_FloatFloat(BaseOffset, Lot_Z_Mul));
			FVector RandomLocation = UKismetMathLibrary::MakeVector(UKismetMathLibrary::Multiply_FloatFloat(BaseOffset, Lot_X_Mul * (-1.f)), UKismetMathLibrary::Multiply_FloatFloat(BaseOffset, Lot_Y_Mul * (-1.f)), UKismetMathLibrary::Multiply_FloatFloat(BaseOffset, Lot_Z_Mul * (-1.f)));
			float RandomLot_X = UKismetMathLibrary::Add_FloatFloat(DefaultLocation[ArrayIndex].X, RandomLocation.X);
			float RandomLot_Y = UKismetMathLibrary::Add_FloatFloat(DefaultLocation[ArrayIndex].Y, RandomLocation.Y);
			float RandomLot_Z = UKismetMathLibrary::Add_FloatFloat(DefaultLocation[ArrayIndex].Z, RandomLocation.Z);
			float Lot_X = UKismetMathLibrary::Add_FloatFloat(DefaultLocation[ArrayIndex].X, BaseLocation.X);
			float Lot_Y = UKismetMathLibrary::Add_FloatFloat(DefaultLocation[ArrayIndex].Y, BaseLocation.Y);
			float Lot_Z = UKismetMathLibrary::Add_FloatFloat(DefaultLocation[ArrayIndex].Z, BaseLocation.Z);
			bool Select = UKismetMathLibrary::EqualEqual_IntInt(RandomDirection[ArrayIndex], 1);
			float RandLot_X = UKismetMathLibrary::SelectFloat(Lot_X, RandomLot_X, Select);
			float RandLot_Y = UKismetMathLibrary::SelectFloat(Lot_Y, RandomLot_Y, Select);
			float RandLot_Z = UKismetMathLibrary::SelectFloat(Lot_Z, RandomLot_Z, Select);
			ArrayElement->SetActorLocation(FVector{ RandLot_X,RandLot_Y,RandLot_Z });

		}
	}
	else
	{
		if (!bRandomPosDirection)
		{
			float Distance = UKismetMathLibrary::Vector_Distance(GetActorLocation(), DefaultLocation[ArrayIndex]);
			float Offset = UKismetMathLibrary::FClamp(Distance, DistanceMin, DistanceMax);
			float InvertOffset = UKismetMathLibrary::MapRangeClamped(Offset, DistanceMin, DistanceMax, MaxLocation, MinLocation);
			FVector InvertLocation = UKismetMathLibrary::MakeVector(UKismetMathLibrary::Multiply_FloatFloat(InvertOffset, Lot_X_Mul), UKismetMathLibrary::Multiply_FloatFloat(InvertOffset, Lot_Y_Mul), UKismetMathLibrary::Multiply_FloatFloat(InvertOffset, Lot_Z_Mul));
			float Lot_X = UKismetMathLibrary::Add_FloatFloat(DefaultLocation[ArrayIndex].X, InvertLocation.X);
			float Lot_Y = UKismetMathLibrary::Add_FloatFloat(DefaultLocation[ArrayIndex].Y, InvertLocation.Y);
			float Lot_Z = UKismetMathLibrary::Add_FloatFloat(DefaultLocation[ArrayIndex].Z, InvertLocation.Z);
			ArrayElement->SetActorLocation(FVector{ Lot_X,Lot_Y,Lot_Z });
		}
		else
		{
			float Distance = UKismetMathLibrary::Vector_Distance(GetActorLocation(), DefaultLocation[ArrayIndex]);
			float Offset = UKismetMathLibrary::FClamp(Distance, DistanceMin, DistanceMax);
			float InvertOffset = UKismetMathLibrary::MapRangeClamped(Offset, DistanceMin, DistanceMax, MaxLocation, MinLocation);
			FVector InvertLocation = UKismetMathLibrary::MakeVector(UKismetMathLibrary::Multiply_FloatFloat(InvertOffset, Lot_X_Mul), UKismetMathLibrary::Multiply_FloatFloat(InvertOffset, Lot_Y_Mul), UKismetMathLibrary::Multiply_FloatFloat(InvertOffset, Lot_Z_Mul));
			FVector RandomLocation = UKismetMathLibrary::MakeVector(UKismetMathLibrary::Multiply_FloatFloat(InvertOffset, Lot_X_Mul * (-1.f)), UKismetMathLibrary::Multiply_FloatFloat(InvertOffset, Lot_Y_Mul * (-1.f)), UKismetMathLibrary::Multiply_FloatFloat(InvertOffset, Lot_Z_Mul * (-1.f)));
			float RandomLot_X = UKismetMathLibrary::Add_FloatFloat(DefaultLocation[ArrayIndex].X, RandomLocation.X);
			float RandomLot_Y = UKismetMathLibrary::Add_FloatFloat(DefaultLocation[ArrayIndex].Y, RandomLocation.Y);
			float RandomLot_Z = UKismetMathLibrary::Add_FloatFloat(DefaultLocation[ArrayIndex].Z, RandomLocation.Z);
			float Lot_X = UKismetMathLibrary::Add_FloatFloat(DefaultLocation[ArrayIndex].X, InvertLocation.X);
			float Lot_Y = UKismetMathLibrary::Add_FloatFloat(DefaultLocation[ArrayIndex].Y, InvertLocation.Y);
			float Lot_Z = UKismetMathLibrary::Add_FloatFloat(DefaultLocation[ArrayIndex].Z, InvertLocation.Z);
			bool Select = UKismetMathLibrary::EqualEqual_IntInt(RandomDirection[ArrayIndex], 1);
			float RandLot_X = UKismetMathLibrary::SelectFloat(Lot_X, RandomLot_X, Select);
			float RandLot_Y = UKismetMathLibrary::SelectFloat(Lot_Y, RandomLot_Y, Select);
			float RandLot_Z = UKismetMathLibrary::SelectFloat(Lot_Z, RandomLot_Z, Select);
			ArrayElement->SetActorLocation(FVector{ RandLot_X,RandLot_Y,RandLot_Z });
		}
	}
}

void AT_Effector::TransformRotation(AActor* ArrayElement, int32 ArrayIndex)
{
	if (!bInvertRotation)
	{
		if (!bRandomRotDirection)
		{
			float Distance = UKismetMathLibrary::Vector_Distance(GetActorLocation(), DefaultLocation[ArrayIndex]);
			float Offset = UKismetMathLibrary::FClamp(Distance, DistanceMin, DistanceMax);
			float BaseOffset = UKismetMathLibrary::MapRangeClamped(Offset, DistanceMin, DistanceMax, MinRotation, MaxRotation);
			FRotator BaseRotation = UKismetMathLibrary::MakeRotator(UKismetMathLibrary::Multiply_FloatFloat(BaseOffset, Rot_X_Mul), UKismetMathLibrary::Multiply_FloatFloat(BaseOffset, Rot_Y_Mul), UKismetMathLibrary::Multiply_FloatFloat(BaseOffset, Rot_Z_Mul));
			float Roll = UKismetMathLibrary::Add_FloatFloat(DefaultRotation[ArrayIndex].Roll, BaseRotation.Roll);
			float Pitch = UKismetMathLibrary::Add_FloatFloat(DefaultRotation[ArrayIndex].Pitch, BaseRotation.Pitch);
			float Yaw = UKismetMathLibrary::Add_FloatFloat(DefaultRotation[ArrayIndex].Yaw, BaseRotation.Yaw);
			ArrayElement->SetActorRotation(FRotator{ Roll,Pitch,Yaw });
		}
		else
		{
			float Distance = UKismetMathLibrary::Vector_Distance(GetActorLocation(), DefaultLocation[ArrayIndex]);
			float Offset = UKismetMathLibrary::FClamp(Distance, DistanceMin, DistanceMax);
			float BaseOffset = UKismetMathLibrary::MapRangeClamped(Offset, DistanceMin, DistanceMax, MinRotation, MaxRotation);
			FRotator BaseRotation = UKismetMathLibrary::MakeRotator(UKismetMathLibrary::Multiply_FloatFloat(BaseOffset, Rot_X_Mul), UKismetMathLibrary::Multiply_FloatFloat(BaseOffset, Rot_Y_Mul), UKismetMathLibrary::Multiply_FloatFloat(BaseOffset, Rot_Z_Mul));
			float Roll = UKismetMathLibrary::Add_FloatFloat(DefaultRotation[ArrayIndex].Roll, BaseRotation.Roll);
			float Pitch = UKismetMathLibrary::Add_FloatFloat(DefaultRotation[ArrayIndex].Pitch, BaseRotation.Pitch);
			float Yaw = UKismetMathLibrary::Add_FloatFloat(DefaultRotation[ArrayIndex].Yaw, BaseRotation.Yaw);
			float RandomRoll = UKismetMathLibrary::Subtract_FloatFloat(DefaultRotation[ArrayIndex].Roll, BaseRotation.Roll);
			float RandomPitch = UKismetMathLibrary::Subtract_FloatFloat(DefaultRotation[ArrayIndex].Pitch, BaseRotation.Pitch);
			float RandomYaw = UKismetMathLibrary::Subtract_FloatFloat(DefaultRotation[ArrayIndex].Yaw, BaseRotation.Yaw);
			bool RandomSelect = UKismetMathLibrary::EqualEqual_IntInt(RandomDirection[ArrayIndex], 1);
			float SelectRoll = UKismetMathLibrary::SelectFloat(Roll, RandomRoll, RandomSelect);
			float SelectPitch = UKismetMathLibrary::SelectFloat(Pitch, RandomPitch, RandomSelect);
			float SelectYaw = UKismetMathLibrary::SelectFloat(Yaw, RandomYaw, RandomSelect);
			ArrayElement->SetActorRotation(FRotator{ SelectRoll,SelectPitch,SelectYaw });
		}
	}
	else
	{
		if (!bRandomRotDirection)
		{
			float Distance = UKismetMathLibrary::Vector_Distance(GetActorLocation(), DefaultLocation[ArrayIndex]);
			float Offset = UKismetMathLibrary::FClamp(Distance, DistanceMin, DistanceMax);
			float InvertOffset = UKismetMathLibrary::MapRangeClamped(Offset, DistanceMin, DistanceMax, MaxRotation, MinRotation);
			FRotator InvertRotation = UKismetMathLibrary::MakeRotator(UKismetMathLibrary::Multiply_FloatFloat(InvertOffset, Rot_X_Mul), UKismetMathLibrary::Multiply_FloatFloat(InvertOffset, Rot_Y_Mul), UKismetMathLibrary::Multiply_FloatFloat(InvertOffset, Rot_Z_Mul));
			float Roll = UKismetMathLibrary::Add_FloatFloat(DefaultRotation[ArrayIndex].Roll, InvertRotation.Roll);
			float Pitch = UKismetMathLibrary::Add_FloatFloat(DefaultRotation[ArrayIndex].Pitch, InvertRotation.Pitch);
			float Yaw = UKismetMathLibrary::Add_FloatFloat(DefaultRotation[ArrayIndex].Yaw, InvertRotation.Yaw);
			ArrayElement->SetActorRotation(FRotator{ Roll,Pitch,Yaw });
		}
		else
		{
			float Distance = UKismetMathLibrary::Vector_Distance(GetActorLocation(), DefaultLocation[ArrayIndex]);
			float Offset = UKismetMathLibrary::FClamp(Distance, DistanceMin, DistanceMax);
			float InvertOffset = UKismetMathLibrary::MapRangeClamped(Offset, DistanceMin, DistanceMax, MaxRotation, MinRotation);
			FRotator InvertRotation = UKismetMathLibrary::MakeRotator(UKismetMathLibrary::Multiply_FloatFloat(InvertOffset, Rot_X_Mul), UKismetMathLibrary::Multiply_FloatFloat(InvertOffset, Rot_Y_Mul), UKismetMathLibrary::Multiply_FloatFloat(InvertOffset, Rot_Z_Mul));
			float Roll = UKismetMathLibrary::Add_FloatFloat(DefaultRotation[ArrayIndex].Roll, InvertRotation.Roll);
			float Pitch = UKismetMathLibrary::Add_FloatFloat(DefaultRotation[ArrayIndex].Pitch, InvertRotation.Pitch);
			float Yaw = UKismetMathLibrary::Add_FloatFloat(DefaultRotation[ArrayIndex].Yaw, InvertRotation.Yaw);
			float RandomRoll = UKismetMathLibrary::Subtract_FloatFloat(DefaultRotation[ArrayIndex].Roll, InvertRotation.Roll);
			float RandomPitch = UKismetMathLibrary::Subtract_FloatFloat(DefaultRotation[ArrayIndex].Pitch, InvertRotation.Pitch);
			float RandomYaw = UKismetMathLibrary::Subtract_FloatFloat(DefaultRotation[ArrayIndex].Yaw, InvertRotation.Yaw);
			bool RandomSelect = UKismetMathLibrary::EqualEqual_IntInt(RandomDirection[ArrayIndex], 1);
			float SelectRoll = UKismetMathLibrary::SelectFloat(Roll, RandomRoll, RandomSelect);
			float SelectPitch = UKismetMathLibrary::SelectFloat(Pitch, RandomPitch, RandomSelect);
			float SelectYaw = UKismetMathLibrary::SelectFloat(Yaw, RandomYaw, RandomSelect);
			ArrayElement->SetActorRotation(FRotator{ SelectRoll,SelectPitch,SelectYaw });
		}
	}
}

void AT_Effector::TransformScale(AActor* ArrayElement, int32 ArrayIndex)
{
	if (!bInvertScale)
	{
		float Distance = UKismetMathLibrary::Vector_Distance(GetActorLocation(), DefaultLocation[ArrayIndex]);
		float Clamp = UKismetMathLibrary::FClamp(Distance, DistanceMin, DistanceMax);
		float BaseOffset = UKismetMathLibrary::MapRangeClamped(Clamp, DistanceMin, DistanceMax, MinScale, MaxScale);
		FVector BaseVectorOffset{ BaseOffset,BaseOffset,BaseOffset };
		FVector BaseVector = UKismetMathLibrary::Multiply_VectorVector(DefaultRelativeScale[ArrayIndex], BaseVectorOffset);
		ArrayElement->GetRootComponent()->SetRelativeScale3D(BaseVector);
	}
	else
	{
		float Distance = UKismetMathLibrary::Vector_Distance(GetActorLocation(), DefaultLocation[ArrayIndex]);
		float Clamp = UKismetMathLibrary::FClamp(Distance, DistanceMin, DistanceMax);
		float InvertOffset = UKismetMathLibrary::MapRangeClamped(Clamp, DistanceMin, DistanceMax, MaxScale, MinScale);
		FVector InvertVectorOffset{ InvertOffset,InvertOffset,InvertOffset };
		FVector InvertVector = UKismetMathLibrary::Multiply_VectorVector(DefaultRelativeScale[ArrayIndex], InvertVectorOffset);
		ArrayElement->GetRootComponent()->SetRelativeScale3D(InvertVector);
	}
}
