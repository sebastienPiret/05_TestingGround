// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// Get Patrol Point
	auto AIController = OwnerComp.GetAIOwner();
	auto controlledPawn = AIController->GetPawn();
	auto PattrolingGuard = Cast<APatrollingGuard>(controlledPawn);
	auto PatrolPoint = PattrolingGuard->indexArray;

	// Set next waypoint
	auto blackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = blackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	blackboardComp->SetValueAsObject(wayPointKey.SelectedKeyName, PatrolPoint[Index]);

	// Cycle Index
	auto nextIndex = (Index + 1) % PatrolPoint.Num();
	blackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, nextIndex);

	return EBTNodeResult::Succeeded;
}
