// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRouteComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// Get Patrol Point
	auto controlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto patrolRoute = controlledPawn->FindComponentByClass<UPatrolRouteComponent>();

	// protect against no patrol route component
	if (!ensure(patrolRoute)) { return EBTNodeResult::Failed; }

	// Warn against empty patrol route
	auto PatrolPoint = patrolRoute->GetPatrolPoint();
	if (!PatrolPoint.Num()) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("There is no patrol point assigned")); 
		return EBTNodeResult::Failed;
	}

	// Set next waypoint
	auto blackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = blackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	blackboardComp->SetValueAsObject(wayPointKey.SelectedKeyName, PatrolPoint[Index]);

	// Cycle Index
	auto nextIndex = (Index + 1) % PatrolPoint.Num();
	blackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, nextIndex);

	return EBTNodeResult::Succeeded;
}
