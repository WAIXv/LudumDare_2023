// Fill out your copyright notice in the Description page of Project Settings.


#include "LudumHealthComponent.h"

#include <stdexcept>

#include "AbilitySystemComponent.h"

ULudumHealthComponent::ULudumHealthComponent()
{
	// Health = 100;
}

bool ULudumHealthComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool ULudumHealthComponent::ApplyHealthChange(AActor* OtherActor,float Delta)
{
	Health += Delta;
	if(Health <= 0)
	{
		Health = 0;
		OnDeadEvent.Broadcast();
		OnHealthChanged.Broadcast(OtherActor, this, Health, Delta);
		return false;
	}

	OnHealthChanged.Broadcast(OtherActor, this, Health, Delta);
	return true;
}
