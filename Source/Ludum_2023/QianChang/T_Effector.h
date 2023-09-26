// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T_Effector.generated.h"

class USphereComponent;
UCLASS()
class LUDUM_2023_API AT_Effector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AT_Effector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public://Location
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInvertLocation = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRandomPosDirection = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinLocation = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxLocation = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Lot_X_Mul = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Lot_Y_Mul = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Lot_Z_Mul = 1.f;
public://Rotation
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInvertRotation = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRandomRotDirection = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinRotation = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxRotation = 180.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Rot_X_Mul = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Rot_Y_Mul = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Rot_Z_Mul = 1.f;
public://Scale
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInvertScale = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinScale = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxScale = 1.f;
public://Main
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPauseSimuation = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bON_OFF = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bLocation = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRotation = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bScale = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBillboardComponent> BillBoardComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USphereComponent> SphereMax;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USphereComponent> SphereMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanceMax = 1500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanceMin = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHelpersVisualInGame;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> DefaultLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> DefaultRelativeScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRotator> DefaultRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> RandomDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> DefaultActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Tag;
protected:
	UFUNCTION()
	void ClearArrays();
	UFUNCTION()
	void StoreTransformValue(TArray<AActor*>& OutActors);
	UFUNCTION()
	void ResetToDefaultValue();
	UFUNCTION()
	void TransformLocation(AActor* ArrayElement, int32 ArrayIndex);
	UFUNCTION()
	void TransformRotation(AActor* ArrayElement, int32 ArrayIndex);
	UFUNCTION()
	void TransformScale(AActor* ArrayElement, int32 ArrayIndex);
};
