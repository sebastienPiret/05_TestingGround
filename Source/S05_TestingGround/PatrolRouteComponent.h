// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRouteComponent.generated.h"

/**
* A route card to help AI choose their next waypoint
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class S05_TESTINGGROUND_API UPatrolRouteComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	TArray<AActor*> GetPatrolPoint() const;

private:
	UPROPERTY(EditInstanceOnly, Category = "PatrolRoute")
		TArray<AActor*> indexArray;
	
};
