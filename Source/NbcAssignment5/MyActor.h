// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "MyActor.generated.h"

UCLASS()
class NBCASSIGNMENT5_API AMyActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AMyActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    void Move(const FVector& NewLocation);
    void Turn(const FRotator& NewRotation);
    void RandomMoveAndTurn();

    UPROPERTY(EditAnywhere, Category = "Settings")
    FVector StartLocation = FVector(0, 50, 0);

    UPROPERTY(EditAnywhere, Category = "Settings")
    int32 MaxMoveCount = 10;

    UPROPERTY(EditAnywhere, Category = "Settings")
    FVector MoveRangeMin = FVector(-300.f, -300.f, 0.f);

    UPROPERTY(EditAnywhere, Category = "Settings")
    FVector MoveRangeMax = FVector(300.f, 300.f, 300.f);

    UPROPERTY(EditAnywhere, Category = "Settings")
    float EventProbability = 0.5f;
private:
    FTimerHandle TimerHandle;

    int32 MoveCount = 0;
    int32 EventCount = 0;
    double TotalDistance = 0;

    bool EventTriggered();
};
