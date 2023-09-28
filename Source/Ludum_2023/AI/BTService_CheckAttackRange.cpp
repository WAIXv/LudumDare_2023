// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComponent))
	{
		//获取TargetActor
		AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(CheckTarget.SelectedKeyName));
		if (TargetActor)
		{
			//获取自身Pawn位置
			AAIController* MyController = OwnerComp.GetAIOwner();
			if (MyController)
			{
				APawn* MyPawn = MyController->GetPawn();
				if (MyPawn)
				{
					//计算距离
					float Distance = FVector::Distance(MyPawn->GetActorLocation(),TargetActor->GetActorLocation());

					bool bInAttackRange = Distance < AttackRangeRadium;

					BlackboardComponent->SetValueAsBool(AttackRangeKey.SelectedKeyName,bInAttackRange);
				}
			}
		}
	}
}
