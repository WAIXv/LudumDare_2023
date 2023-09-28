// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetDesiredAiming.h"

#include "AIController.h"
#include "AlsCharacter.h"

EBTNodeResult::Type UBTTask_SetDesiredAiming::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();
	if (ensure(MyController))
	{
		AAlsCharacter* AlsCharacter = Cast<AAlsCharacter>(MyController->GetCharacter());
		if (ensure(AlsCharacter))
		{
			AlsCharacter->SetDesiredAiming(bDesiredAiming);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
