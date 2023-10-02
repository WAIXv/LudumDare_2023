// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LudumHealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, ULudumHealthComponent*, OwningComp, float, NewHealth, float, Delta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUDUM_2023_API ULudumHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	 ULudumHealthComponent();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health;

public:	

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnDead OnDeadEvent;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(AActor* OtherActor,float Delta);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHealth() { return Health; }

};
