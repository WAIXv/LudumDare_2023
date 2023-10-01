// Fill out your copyright notice in the Description page of Project Settings.


#include "LudumHealthComponent.h"

#include <stdexcept>

#include "AbilitySystemComponent.h"

ULudumHealthComponent::ULudumHealthComponent()
{
	Health = 100;
}

bool ULudumHealthComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool ULudumHealthComponent::ApplyHealthChange(float Delta)
{
	UE_LOG(LogTemp, Log, TEXT("ApplyHealthChange:%d"),Delta)
	Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}
